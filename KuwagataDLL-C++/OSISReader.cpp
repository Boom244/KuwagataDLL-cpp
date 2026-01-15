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


    bool PreprocessRequest(String& currentRequest, std::vector<String>*& outElements) {
        //---CONCERN 1: Flushing the garbage out of a request and splitting it up.---

            //Error catch that happens if someone does something like put a space between separated references so I'm doing this:
        while (currentRequest.at(0) == ' ')
        {
            currentRequest = currentRequest.substr(1);
        }

        //Stylistic choice; If you end a reference with a semicolon and put nothing after it, then an error pops up.
        if (currentRequest == "")
        {
            return true;
        }

        //First, split the resulting string further by its spaces to get the book and chapter/verses. 
        outElements = Util::split(currentRequest, ' ');

        //END CONCERN
        return false;
    }

    bool DiscernReferenceBook(int* returnNumber, std::vector<String>* elements, String currentRequest) {
        
        //--CONCERN 2: DISCERNING THE BOOK
            //Second, turn the first element of *that* resulting string into a number using BibleIndexes' GetBibleIndexFromArray.
        *returnNumber = BibleIndexes::GetBibleIndexFromArray(elements->at(0)) * BibleIndexes::Book; //x1000000 because that's the scheme the JSON uses.

        if (BibleIndexes::IsOneChapterBook(*returnNumber) && currentRequest.find(":") == std::string::npos) //if it's a one-chapter book being referenced knowingly by the user (e.g: Philemon 24 instead of Philemon 1:24)
        {
            (*elements)[1] = "1:" + (*elements)[1]; //Simple solutions to simple problems:
        }

        //Accomodations for multi-word books
        if (*returnNumber == 0)
        {
            elements->insert(elements->begin(), elements->at(0) + " " + elements->at(1));
            elements->erase(elements->begin() + 1, elements->begin() + 3);
            *returnNumber = BibleIndexes::GetBibleIndexFromArray(elements->at(0)) * BibleIndexes::Book;
            return true; //flag the next subscript to shift down one element
        }
        return false;
        //END CONCERN
    }

     bool IsCompoundReference(std::vector<String>* elements) {
        //CONCERN 2.1 -- COMPOUND REFERENCE?
            //Sub-concerns will be early-terminating concerns that terminate the loop iteration early and move next.

            //New clause; Sometimes you might want to reference a bunch of new verses within the same book, a la, for example,
            //"Jonah 1:3-4,14,17,2:1". So, here's what we're gonna do:
        if (elements->size() > 1)
        {
            if (elements->at(1).find(",") != String::npos)
            {
                return true;
            }
        }
        return false;
        //END CONCERN
    }

     bool OSISReader::ProcessedCrossBookReferences(String currentRequest, std::vector<int>* returnList) {
         //CONCERN 2.3 -- CROSS-BOOK REFERENCES
         std::vector<String>* potentialCrossBookReference = Util::split(currentRequest, '-');
         if (potentialCrossBookReference->size() > 1)
         {
             if (BibleIndexes::GetBibleIndexFromArray((*potentialCrossBookReference)[0]) != 0 && BibleIndexes::GetBibleIndexFromArray((*potentialCrossBookReference)[1]) != 0)
             {
                 int startPos = GetReferencesFromString((*potentialCrossBookReference)[0], true)->at(0);
                 int endPos = GetReferencesFromString((*potentialCrossBookReference)[1], true)->at(0);
                 std::vector<int>* allMarkers = GetVersesBetweenMarkers(startPos, endPos+1, BibleIndexes::Chapter, true);
                 returnList->insert(returnList->end(), allMarkers->begin(), allMarkers->end());
                 delete potentialCrossBookReference;
                 delete allMarkers;

                 return true; //continue in disguise!
             }
         }
         return false;

         //END CONCERN
    }

     bool OSISReader::ProcessedWholeChapter(std::vector<int>* returnList, std::vector<String>* chapterAndVerse, int returnNumber) {
         //CONCERN 2.4 -- WHOLE-CHAPTER REFERENCES

            //If there's just a chapter and no verse:
         if (chapterAndVerse->size() == 1)
         {
             int nextChapter = BibleIndexes::IncreaseBibleReference(returnNumber, BibleIndexes::Chapter);
             std::vector<int>* chapter = GetVersesBetweenMarkers(returnNumber + 1, nextChapter, BibleIndexes::Verse, false);
             returnList->insert(returnList->end(), chapter->begin(), chapter->end());
             delete chapter;
             return true;
         }
         return false;
    }

	std::vector<int>* OSISReader::GetReferencesFromString(String request, bool recursive)
	{
        //First, split the string by semicolons into individual requests;
        std::vector<String>* requests = Util::split(request,';');

        //Next, initialize an array of numbers to return after processing the requests.
        std::vector<int>* returnList = new std::vector<int>();

        std::vector<String>* elements = {};
        std::vector<String>* chapterAndVerse;
        std::vector<String>* firstandPossSecond;
        int returnNumber = 0;

        for (int i = 0; i < (*requests).size(); i++)
        {
            String currentRequest = requests->at(i);
            //OK, let's start by splitting up this function into scopes and concerns:

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
            if ((elements->size() == 1) && requests->at(i).find("-") == String::npos)
            {
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

            //END CONCERN

            if (ProcessedCrossBookReferences(currentRequest, returnList)) {
                continue;
            }
            

            firstandPossSecond = Util::split(elements->at(1), '-');

            chapterAndVerse = Util::split(firstandPossSecond->at(0), ':');

            returnNumber += std::stoi(chapterAndVerse->at(0)) * 1000;

            if (ProcessedWholeChapter(returnList,chapterAndVerse, returnNumber)) {
                continue;
            }

            //CONCERNS 3 AND 4 -- HYPHENATED ELEMENTS

            if (firstandPossSecond->size() >= 2) //If a second element exists, branch and get all the verses between the first and second number. 
            {

                if (firstandPossSecond->at(1).find(':') != String::npos) // If the split string contains a reference to another verse, in another chapter:
                {
                    std::vector<int>* csv = GetVersesBetweenChapters(*elements, *firstandPossSecond);
                    returnList->insert(returnList->end(), csv->begin(), csv->end());
                    delete csv;
                }
                else
                {
                    std::vector<String>* firstChapterAndVerse = Util::split(firstandPossSecond->at(0), ':');

                    String startPosition = std::format("{} {}", elements->at(0), firstandPossSecond->at(0));

                    String endPosition =  std::format("{} {}:{}", elements->at(0), firstChapterAndVerse->at(0),
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

                delete firstandPossSecond;
                delete elements;
            }
            else
            {
                returnList->push_back(returnNumber + std::stoi(chapterAndVerse->at(1)));
                delete chapterAndVerse;
            }

        //END CONCERN
        }
        return returnList;
        //So hopefully, as a result of this function, an input of {"Genesis 1:1", "Genesis 1:2"} should return {1001001, 1001002}.
	}
	std::vector<String>* OSISReader::GetVersesFromReferences(std::vector<int> verseIds)
	{
		std::vector<String>* ret = new std::vector<String>();
		for (int i = 0; i < verseIds.size(); i++) {
			ret->push_back(verses[std::to_string(verseIds.at(i))]);
		}
		return ret;

	}
	std::vector<String>* OSISReader::BatchDecodeAllReferences(std::vector<int> references)
	{
		int books = BibleIndexes::Book;
		int chapters = BibleIndexes::Chapter;

		std::vector<String>* ret_refs = new std::vector<String>();

		//This is ugly.
		//Come back and work your magic on it once we're done here.
		for (int i = 0; i < references.size(); i++) {
			int ref = references.at(i);
			int bookIdent = floor(ref / books);
			String Book = BibleIndexes::GetFromBiblePlainArray(bookIdent);
			String Chapter = std::to_string((int)floor((ref - (bookIdent * books)) / 1000));
			String  VerseIdentifier = std::to_string((ref - ((bookIdent * books) + (std::stoi(Chapter) * 1000))));
			ret_refs->push_back(Book + " " + Chapter + ":" + VerseIdentifier);
		}
		return ret_refs;
	}
	String OSISReader::getOSISPath()
	{
		return OSISPath;
	}
	String OSISReader::getVersion()
	{
		return Version;
	}

	std::vector<int>* OSISReader::GetVersesBetweenMarkers(int startMarker, int endMarker, BibleIndexes::SelectionOption so, bool escalate)
	{
		std::vector<int>* ret = new std::vector<int>();
		if (startMarker > endMarker)
		{
			int temp;
			temp = startMarker;
			startMarker = endMarker;
			endMarker = temp;
		}
		for (int i = startMarker; i < endMarker; i++) {
			if (verses.contains(std::to_string(i))) {
				ret->push_back(i);
			}
			else {
				i = BibleIndexes::IncreaseBibleReference(i, so) + 1;
				if (!verses.contains(std::to_string(i)) && escalate)
				{
					i = BibleIndexes::IncreaseBibleReference(i, BibleIndexes::Book);
				}
				if (verses.contains(std::to_string(i)))
				{
					ret->push_back(i);
				}
			}
		}
		return ret;
	}
	std::vector<int>* OSISReader::GetVersesBetweenChapters(std::vector<String> elements, std::vector<String> tokens)
	{

		String bookTitle =  elements[0];
		int startRef =  GetReferencesFromString(std::format("{} {}", bookTitle, tokens[0]), false)->at(0);
		int endRef = GetReferencesFromString(std::format("{} {}", bookTitle, tokens[1]), false)->at(0);
		return GetVersesBetweenMarkers(startRef, endRef, BibleIndexes::Chapter, false);
	}
	std::vector<int>* OSISReader::SplitCommaSeparatedVerses(std::vector<String> elements)
	{
		std::vector<String>* subElements = Util::split(elements[1], ',');
        String book = elements[0];
		String chapter = Util::split(subElements->at(0), ':')->at(0);
		std::vector<int>* ret = new std::vector<int>();
		for (int i = 0; i < subElements->size(); i++) {
			String submittanceString;
			String subelement = subElements->at(i);
			//do a check: does it contain a verse and a chapter or just a verse?
			if (subelement.find(":") != String::npos)
			{
				submittanceString = std::format("{} {}", book, subelement);
			}
			else
			{
				submittanceString = std::format("{} {}:{}", book, chapter, subelement);
			}
			std::vector<int>* v = GetReferencesFromString(submittanceString, false);
			ret->insert(ret->end(), v->begin(), v->end());
		}
        delete subElements;
		return ret;
	}

}

