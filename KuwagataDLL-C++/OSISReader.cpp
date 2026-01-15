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
	std::vector<int>* OSISReader::GetReferencesFromString(String request, bool recursive)
	{
        //First, split the string by semicolons into individual requests;
        std::vector<String>* requests = Util::split(request,';');

        //Next, initialize an array of numbers to return after processing the requests.
        std::vector<int>* returnList = new std::vector<int>();

        std::vector<String>* elements;
        std::vector<String>* chapterAndVerse;
        std::vector<String>* firstandPossSecond;
        int returnNumber = 0;

        for (int i = 0; i < (*requests).size(); i++)
        {

            bool multiWordBook = false;
            //Error catch that happens if someone does something like put a space between separated references so I'm doing this:
            while (requests->at(i).at(0) == ' ')
            {
                requests->at(i) = requests->at(i).substr(1);
            }

            //Stylistic choice; If you end a reference with a semicolon and put nothing after it, then an error pops up.
            if (requests->at(i) == "")
            {
                continue;
            }

            //First, split the resulting string further by its spaces to get the book and chapter/verses. 
            elements = Util::split(requests->at(i), ' ');



            //Second, turn the first element of *that* resulting string into a number using BibleIndexes' GetBibleIndexFromArray.

            returnNumber = BibleIndexes::GetBibleIndexFromArray(elements->at(0)) * BibleIndexes::Book; //x1000000 because that's the scheme the JSON uses.

            if ( BibleIndexes::IsOneChapterBook(returnNumber) && requests->at(i).find(":") == std::string::npos) //if it's a one-chapter book being referenced knowingly by the user (e.g: Philemon 24 instead of Philemon 1:24)
            {
                (*elements)[1] = "1:" + (*elements)[1]; //Simple solutions to simple problems:
            }

            //Accomodations for multi-word books
            if (returnNumber == 0)
            {
                returnNumber = BibleIndexes::GetBibleIndexFromArray(elements->at(0) + " " + elements->at(1)) * BibleIndexes::Book;
                multiWordBook = true; //flag the next subscript to shift down one element
            }

            //New clause; Sometimes you might want to reference a bunch of new verses within the same book, a la, for example,
            //"Jonah 1:3-4,14,17,2:1". So, here's what we're gonna do:
            if (elements->size() > (multiWordBook ? 2 : 1))
            {
                if (elements->at(multiWordBook ? 2 : 1).find(",") != String::npos)
                {
                    std::vector<int>* csv = SplitCommaSeparatedVerses(*elements, multiWordBook);
                    returnList->insert(returnList->end(), csv->begin(), csv->end());
                    delete csv;
                    continue;
                }
            }

            //If we are simply referencing an entire book
            if (((elements->size() == 1) || (elements->size() == 2 && multiWordBook)) && requests->at(i).find("-") == String::npos)
            {
                //gotta check for the special condition (explained later)
                if (recursive)
                {
                    returnList->push_back(returnNumber + BibleIndexes::Chapter + BibleIndexes::Verse);
                    continue; //simply return a starting point (or an end point)
                }

                int nextBook = BibleIndexes::IncreaseBibleReference(returnNumber, BibleIndexes::Book);
                std::vector<int>* gvbm = GetVersesBetweenMarkers(returnNumber, nextBook, BibleIndexes::Chapter, false);
                for (int GVBMref : *gvbm)
                {
                    returnList->push_back(GVBMref);
                }
                delete gvbm;
                continue;
            }

            std::vector<String>* potentialCrossBookReference = Util::split((*requests)[i], '-');
            if (potentialCrossBookReference->size() > 1)
            {
                if (BibleIndexes::GetBibleIndexFromArray((*potentialCrossBookReference)[0]) != 0 && BibleIndexes::GetBibleIndexFromArray((*potentialCrossBookReference)[1]) != 0)
                {
                    int startPos = GetReferencesFromString((*potentialCrossBookReference)[0], true)->at(0);
                    int endPos = GetReferencesFromString((*potentialCrossBookReference)[1], true)->at(0);

                    for(int GVBMref : *GetVersesBetweenMarkers(startPos, endPos, BibleIndexes::Chapter, true))
                    {
                        returnList->push_back(GVBMref);
                    }
                    returnList->push_back(endPos);
                    continue;
                }
            }

            firstandPossSecond = Util::split(elements->at(multiWordBook ? 2 : 1), '-');

            chapterAndVerse = Util::split(firstandPossSecond->at(0), ':');

            returnNumber += std::stoi(chapterAndVerse->at(0)) * 1000;

            //If there's just a chapter and no verse:
            if (chapterAndVerse->size() == 1)
            {
                int nextBook = BibleIndexes::IncreaseBibleReference(returnNumber, BibleIndexes::Chapter);
                for (int a = returnNumber; a < nextBook; a++)
                {
                    if (verses.contains(std::to_string(a)))
                    {
                        returnList->push_back(a);
                    }
                }
                continue;
            }


            if (firstandPossSecond->size() >= 2) //If a second element exists, branch and get all the verses between the first and second number. 
            {
                std::vector<String>* nums = Util::split(chapterAndVerse->at(1), '-');


                if (firstandPossSecond->at(1).find(':') != String::npos) // If the split string contains a reference to another verse, in another chapter:
                {
                    std::vector<int>* csv = GetVersesBetweenChapters(multiWordBook, *elements, *firstandPossSecond);
                    returnList->insert(returnList->end(), csv->begin(), csv->end());
                }
                else
                {
                    std::vector<String>* firstChapterAndVerse = Util::split(firstandPossSecond->at(0), ':');

                    String startPosition = multiWordBook ? std::format("{} {} {}", elements->at(0), elements->at(1), firstandPossSecond->at(0)) : std::format("{} {}", elements->at(0), firstandPossSecond->at(0));
                    String endPosition = multiWordBook ? std::format("{} {} {}:{}", elements->at(0), elements->at(1), firstChapterAndVerse->at(0), firstandPossSecond->at(1)) : std::format("{} {}:{}", elements->at(0), firstChapterAndVerse->at(0), firstandPossSecond->at(1));

                    startPosition = std::format("{};{}", startPosition, endPosition);

                    std::vector<int>* tempHolder = GetReferencesFromString(startPosition, false);
                    for (int k = tempHolder->at(0); k < tempHolder->at(1) + 1; k++) //Loop through the resulting numbers
                    {
                        returnList->push_back(k);
                    }
                }

                delete firstandPossSecond;
                delete elements;
            }
            else
            {
                returnList->push_back(returnNumber + std::stoi(chapterAndVerse->at(1)));
                delete chapterAndVerse;
            }
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
	std::vector<int>* OSISReader::GetVersesBetweenChapters(bool multiWordBook, std::vector<String> elements, std::vector<String> tokens)
	{

		String bookTitle = multiWordBook ? std::format("{} {}", elements[0], elements[1]) : elements[0];
		int startRef =  GetReferencesFromString(std::format("{} {}", bookTitle, tokens[0]), false)->at(0);
		int endRef = GetReferencesFromString(std::format("{} {}", bookTitle, tokens[1]), false)->at(0);
		return GetVersesBetweenMarkers(startRef, endRef, BibleIndexes::Chapter, false);
	}
	std::vector<int>* OSISReader::SplitCommaSeparatedVerses(std::vector<String> elements, bool multiWordBook)
	{
		std::vector<String>* subElements = Util::split(elements[multiWordBook ? 2 : 1], ',');
		String book = elements[0] + (multiWordBook ? elements[1] : "");
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
		return ret;
	}
}

