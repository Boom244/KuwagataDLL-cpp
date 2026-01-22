#include "OSISReader.h"
#include "util.h"

#include<format>
#include<fstream>
#include<iostream>



namespace KuwagataDLL {
	OSISReader::OSISReader(String OSISpath)
	{
		this->OSISPath = OSISpath;
		//this->Version = whatever...
        std::ifstream file(OSISpath);

        try {
            this->verses = JSON::parse(file);
        }
        catch (const JSON::parse_error& ex) {
            std::cout << "Parse error at byte " << ex.byte << ": " << ex.what() << std::endl;
        }
		

	}
	void OSISReader::ChangeOSISPath(String newOSISPath)
	{
		this->OSISPath = newOSISPath;
		delete &this->verses;
		this->verses = JSON::parse(std::ifstream(newOSISPath));

	}

    /*
    Preprocesses an individual GetReferencesFromString request.
    @param currentRequest the current request to process.
    @param outElements a reference to the elements to return.
    @returns a boolean determining whether the current request is invalid or otherwise unprocessable. 
    */
    bool PreprocessRequest(String& currentRequest, std::vector<String>*& outElements) {
        while (currentRequest.at(0) == ' ') {
            currentRequest = currentRequest.substr(1);
        }

        if (currentRequest == "") {
            return true;
        }

        outElements = Util::split(currentRequest, ' ');

        return false;
    }

    /*
    Discerns the multiple of BibleIndexes::SelectionOption::Book corresponding to the first
    element of a reference.
    @param returnNumber A pointer to the number in which to return the multiple of SelectionOption::Book.
    @param elements The space-separated elements of the reference.
    @param currentRequest the entire reference.
    @returns A boolean determining whether GetReferencesFromString should terminate this loop iteration early.
    */
    bool DiscernReferenceBook(int* returnNumber, std::vector<String>* elements, String currentRequest) {
        
        *returnNumber = BibleIndexes::GetBibleIndexFromArray(elements->at(0)) * BibleIndexes::Book; 

        if (BibleIndexes::IsOneChapterBook(*returnNumber) && currentRequest.find(":") == std::string::npos) { 
            (*elements)[1] = "1:" + (*elements)[1]; 
        }

        if (*returnNumber == 0) {
            elements->insert(elements->begin(), elements->at(0) + " " + elements->at(1));
            elements->erase(elements->begin() + 1, elements->begin() + 3);
            *returnNumber = BibleIndexes::GetBibleIndexFromArray(elements->at(0)) * BibleIndexes::Book;
            return true; 
        }
        return false;
    }

    /*
    Determines whether the reference denoted by space-separated elements is "compound" -- that is, 
    multiple comma-separated verse references in one statement (i.e, "John 3:16,17,8,9")
    @param elements The space-separated elements of the reference.
    @return a boolean reflecting whether the reference is a compound reference. 
    */
     bool IsCompoundReference(std::vector<String>* elements) {
        if (elements->size() > 1) {
            if (elements->at(1).find(",") != String::npos) {
                return true;
            }
        }
        return false;
    }

     /*
     Processes cross-book references.
     @param currentRequest The current request being processed by GetReferencesFromString.
     @param returnList A pointer to the return list being output by GetReferencesFromString.
     @return A boolean reflecting whether the reference in question is Cross-Book (also, a continue call in disguise!)
     */
     bool OSISReader::ProcessedCrossBookReferences(String currentRequest, std::vector<int>* returnList) {
         std::vector<String>* potentialCrossBookReference = Util::split(currentRequest, '-');
         if (potentialCrossBookReference->size() > 1) {
             if (BibleIndexes::GetBibleIndexFromArray((*potentialCrossBookReference)[0]) != 0 
                 && BibleIndexes::GetBibleIndexFromArray((*potentialCrossBookReference)[1]) != 0) {
                    int startPos = GetReferencesFromString((*potentialCrossBookReference)[0], true)->at(0);
                    int endPos = GetReferencesFromString((*potentialCrossBookReference)[1], true)->at(0);
                    std::vector<int>* allMarkers = GetVersesBetweenMarkers(startPos, endPos+1, BibleIndexes::Chapter, true);
                    returnList->insert(returnList->end(), allMarkers->begin(), allMarkers->end());
                    delete potentialCrossBookReference;
                    delete allMarkers;

                    return true; 
             }
         }
         return false;
    }

     /*
     Processes whole-chapter references.
     @param returnList A pointer to the return list being output by GetReferencesFromString.
     @param chapterAndVerse A vector containing what could(?) be a chapter OR a chapter and verse.
     @param returnNumber the current state of GetReferencesFromString's returnNumber.
     @return A boolean reflecting whether the reference in question is Cross-Book (also, a continue call in disguise!)
     */
     bool OSISReader::ProcessedWholeChapter(std::vector<int>* returnList, std::vector<String>* chapterAndVerse, int returnNumber) {

         if (chapterAndVerse->size() == 1) {
             int nextChapter = BibleIndexes::IncreaseBibleReference(returnNumber, BibleIndexes::Chapter);
             std::vector<int>* chapter = GetVersesBetweenMarkers(returnNumber + 1, nextChapter, BibleIndexes::Verse, false);
             returnList->insert(returnList->end(), chapter->begin(), chapter->end());
             delete chapter;
             return true;
         }
         return false;
    }

     /*
     Handles a hyphenated reference.
     @param firstandPossSecond the first (and possibly second?) elements as a result of splitting the reference by "-"s.
     @param firstElement the first element as a result of splitting the reference by spaces.
     @param returnList GetReferencesByString's current return list. 
     */
     void OSISReader::HandleHyphenatedReference(std::vector<String>* firstandPossSecond, String firstElement, std::vector<int>* returnList) {
         std::vector<String>* firstChapterAndVerse = Util::split(firstandPossSecond->at(0), ':');

         String startPosition = std::format("{} {}", firstElement, firstandPossSecond->at(0));

         String endPosition = std::format("{} {}:{}", firstElement, firstChapterAndVerse->at(0),
             firstandPossSecond->at(1));

         startPosition = std::format("{};{}", startPosition, endPosition);

         std::vector<int>* numRefs = GetReferencesFromString(startPosition, false);
         std::vector<int>* refList = GetVersesBetweenMarkers(numRefs->at(0), numRefs->at(1) + 1,
             BibleIndexes::Chapter, false);

         returnList->insert(returnList->end(), refList->begin(), refList->end());

         delete numRefs;
         delete refList;
         delete firstChapterAndVerse;
     }

    /*
    * Formats references from a string into numerical OSIS-style references.
    * @param request The string with references to be parsed.
    * @param recursive Flag indicating a special recursive call.
    * @returns A pointer to a Vector containing all referenced verses in String request.
    */
	std::vector<int>* OSISReader::GetReferencesFromString(String request, bool recursive) {
        std::vector<String>* requests = Util::split(request,';');

        std::vector<int>* returnList = new std::vector<int>();

        std::vector<String>* elements = {};
        std::vector<String>* chapterAndVerse;
        std::vector<String>* firstandPossSecond;
        int returnNumber = 0;

        for (int i = 0; i < (*requests).size(); i++) {
            String currentRequest = requests->at(i);

            if (PreprocessRequest(currentRequest, elements)) {
                continue;
            }

            DiscernReferenceBook(&returnNumber, elements, requests->at(i));
            
            if (IsCompoundReference(elements)) {
                std::vector<int>* csv = SplitCommaSeparatedVerses(*elements);
                returnList->insert(returnList->end(), csv->begin(), csv->end());
                delete csv;
                continue;
            }

            //CONCERN 2.2 -- WHOLE-BOOK-REFERENCES
            //If we are simply referencing an entire book
            //TODO: Triage this concern more effectively. 
            if ((elements->size() == 1) && requests->at(i).find("-") == String::npos) {
                //gotta check for the special condition (explained later)
                if (recursive) {
                    returnList->push_back(returnNumber + BibleIndexes::Chapter + BibleIndexes::Verse);
                } else {
                    int nextBook = BibleIndexes::IncreaseBibleReference(returnNumber, BibleIndexes::Book);
                    std::vector<int>* gvbm = GetVersesBetweenMarkers(returnNumber, nextBook, BibleIndexes::Chapter, false);
                    returnList->insert(returnList->end(), gvbm->begin(), gvbm->end());
                    delete gvbm;
                }
                continue;
            }

            if (ProcessedCrossBookReferences(currentRequest, returnList)) {
                continue;
            }
  
            firstandPossSecond = Util::split(elements->at(1), '-');
            chapterAndVerse = Util::split(firstandPossSecond->at(0), ':');
            returnNumber += std::stoi(chapterAndVerse->at(0)) * 1000;

            if (ProcessedWholeChapter(returnList,chapterAndVerse, returnNumber)) {
                continue;
            }

            if (firstandPossSecond->size() >= 2) { //If a second element exists, branch and get all the verses between the first and second number.

                if (firstandPossSecond->at(1).find(':') != String::npos) { // If the split string contains a reference to another verse, in another chapter:
                    std::vector<int>* csv = GetVersesBetweenChapters(*elements, *firstandPossSecond);
                    returnList->insert(returnList->end(), csv->begin(), csv->end());
                    delete csv;
                } else {
                    HandleHyphenatedReference(firstandPossSecond, elements->at(0), returnList);
                }

                delete firstandPossSecond;
                delete elements;
            } else {
                returnList->push_back(returnNumber + std::stoi(chapterAndVerse->at(1)));
                delete chapterAndVerse;
            }
        }
        return returnList;
	}

    /*
    Exchanges references for their respective verses.
    @param verseIds A Vector of OSIS-Styled verse ID integers.
    @returns A Vector of Strings representing the verses in the currently selected document corresponding to said IDs.
    */
	std::vector<String>* OSISReader::GetVersesFromReferences(std::vector<int> verseIds) {
		std::vector<String>* ret = new std::vector<String>();
		for (int i = 0; i < verseIds.size(); i++) {
			ret->push_back(verses[std::to_string(verseIds.at(i))]);
		}
		return ret;

	}
    /*
    Decodes Verse IDs into human-readable verse references.
    @param references A Vector of OSIS-Styled verse ID integers.
    @returns a Vector of Strings representing the corresponding references.
    */
	std::vector<String>* OSISReader::BatchDecodeAllReferences(std::vector<int> references) {
		int books = BibleIndexes::Book;
		int chapters = BibleIndexes::Chapter;

		std::vector<String>* ret_refs = new std::vector<String>();

		//This is ugly.
		//Come back and work your magic on it once we're done here.
		for (int i = 0; i < references.size(); i++) {
			ret_refs->push_back(DecodeReference(references.at(i)));
		}
		return ret_refs;
	}

    /*
        Decodes a singular numerical reference into a human-readable reference.
        @param reference The numerical reference to decode.
        @returns a String representing the corresponding reference.
    */
    String OSISReader::DecodeReference(int reference)
    {
        int books = BibleIndexes::Book;
        int chapters = BibleIndexes::Chapter;

        int bookIdent = floor(reference / books);
        String Book = BibleIndexes::GetFromBiblePlainArray(bookIdent);
        String Chapter = std::to_string((int)floor((reference - (bookIdent * books)) / 1000));
        String  VerseIdentifier = std::to_string((reference - ((bookIdent * books) + (std::stoi(Chapter) * 1000))));
        return (Book + " " + Chapter + ":" + VerseIdentifier);
    }
	
    /*
    Gets the current path of this OSISReader.
    */
    String OSISReader::getOSISPath() {
		return OSISPath;
	}

    /*
    Gets the Bible Version this OSISReader is using. 
    */
	String OSISReader::getVersion() {
		return Version;
	}

    /*
    Retrieves all valid OSIS IDs between two markers.
    @param startMarker The beginning marker.
    @param endMarker The ending marker.
    @param so The initial BibleIndexes::SelectionOption by which to escalate the reference if it's not in the document.
    @param escalate a flag for whether or not to do said escalation.
    @return A Vector of all verse references between the two markers.
    */
	std::vector<int>* OSISReader::GetVersesBetweenMarkers(int startMarker, int endMarker, BibleIndexes::SelectionOption so, bool escalate) {
		std::vector<int>* ret = new std::vector<int>();
		if (startMarker > endMarker) {
			int temp;
			temp = startMarker;
			startMarker = endMarker;
			endMarker = temp;
		}
		for (int i = startMarker; i < endMarker; i++) {
			if (verses.contains(std::to_string(i))) {
				ret->push_back(i);
			} else {
				i = BibleIndexes::IncreaseBibleReference(i, so) + 1;
				if (!verses.contains(std::to_string(i)) && escalate) {
					i = BibleIndexes::IncreaseBibleReference(i, BibleIndexes::Book);
				}
				if (verses.contains(std::to_string(i))) {
					ret->push_back(i);
				}
			}
		}
		return ret;
	}

    /*
    Gets all verses between two chapters, as are described by the book title and tokens.
    @param elements An array of elements, of which the first is the title of the book that both chapters are in.
    @param tokens The two chapter numbers, in String form.
    @returns A Vector of OSIS-styled IDs representing all verses between the two chapters.
    */
	std::vector<int>* OSISReader::GetVersesBetweenChapters(std::vector<String> elements, std::vector<String> tokens) {

		String bookTitle =  elements[0];
		int startRef =  GetReferencesFromString(std::format("{} {}", bookTitle, tokens[0]), false)->at(0);
		int endRef = GetReferencesFromString(std::format("{} {}", bookTitle, tokens[1]), false)->at(0);
		return GetVersesBetweenMarkers(startRef, endRef, BibleIndexes::Chapter, false);
	}

    /*
    Processes comma-separation between verses.
    @param elements the elements being processed by GetReferencesFromString.
    @returns A pointer to a vector of integers representing all comma-separated verse numerical references.
    */
	std::vector<int>* OSISReader::SplitCommaSeparatedVerses(std::vector<String> elements) {
		std::vector<String>* subElements = Util::split(elements[1], ',');
        String book = elements[0];
		String chapter = Util::split(subElements->at(0), ':')->at(0);
		std::vector<int>* ret = new std::vector<int>();
		for (int i = 0; i < subElements->size(); i++) {
			String submittanceString;
			String subelement = subElements->at(i);
			//do a check: does it contain a verse and a chapter or just a verse?
			if (subelement.find(":") != String::npos) {
				submittanceString = std::format("{} {}", book, subelement);
			} else {
				submittanceString = std::format("{} {}:{}", book, chapter, subelement);
			}
			std::vector<int>* v = GetReferencesFromString(submittanceString, false);
			ret->insert(ret->end(), v->begin(), v->end());
		}
        delete subElements;
		return ret;
	}

}

