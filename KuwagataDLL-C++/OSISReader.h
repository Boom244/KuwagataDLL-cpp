#ifndef OSIS_READER
#define OSIS_READER


#include<vector>
#include<math.h>
#include<nlohmann/json.hpp>
#include "UserException.h"
#include "BibleIndexes.h"
using JSON = nlohmann::json;



namespace KuwagataDLL {

	//The OSISReader class, designed to parse JSON files in Open Scripture Information Standard format.
	class OSISReader {
	public: 
		OSISReader(String OSISpath);
		void ChangeOSISPath(String newOSISPath);
		std::vector<int>* GetReferencesFromString(String request, bool recursive);
		std::vector<String>* GetVersesFromReferences(std::vector<int> verseIds);
		static std::vector<String>* BatchDecodeAllReferences(std::vector<int> references);
		static String DecodeReference(int reference);
		std::vector<UserException> getRaisedExceptions();
		String getOSISPath();
		String getVersion();
	private:
		String OSISPath;
		String Version;
		JSON verses;
		std::vector<UserException>* raisedExceptions;
		void AddInputException(ExceptionType type, String offendingInput);
		void AddReferenceException(ExceptionType type, int offendingReference);
		std::vector<int>* GetVersesBetweenMarkers(int startMarker, int endMarker, BibleIndexes::SelectionOption so, bool escalate);
		std::vector<int>* GetVersesBetweenChapters(std::vector<String> elements, std::vector<String> tokens);
		std::vector<int>* SplitCommaSeparatedVerses(std::vector<String> elements);
		bool DiscernReferenceBook(int* returnNumber, std::vector<String>* elements, String currentRequest);
		bool ProcessedCrossBookReferences(String currentRequest, std::vector<int>* returnList);
		bool ProcessedWholeChapter(std::vector<int>* returnList, std::vector<String>* chapterAndVerse, int returnNumber);
		void HandleHyphenatedReference(std::vector<String>* firstandPossSecond, String firstElement, std::vector<int>* returnList);
	};
}

#endif;