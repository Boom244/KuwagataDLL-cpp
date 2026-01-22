#ifndef OSIS_READER
#define OSIS_READER

#include "BibleIndexes.h"
#include<vector>
#include<math.h>
#include<nlohmann/json.hpp>
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
		String getOSISPath();
		String getVersion();
	private:
		String OSISPath;
		String Version;
		JSON verses;
		std::vector<int>* GetVersesBetweenMarkers(int startMarker, int endMarker, BibleIndexes::SelectionOption so, bool escalate);
		std::vector<int>* GetVersesBetweenChapters(std::vector<String> elements, std::vector<String> tokens);
		std::vector<int>* SplitCommaSeparatedVerses(std::vector<String> elements);
		bool ProcessedCrossBookReferences(String currentRequest, std::vector<int>* returnList);
		bool ProcessedWholeChapter(std::vector<int>* returnList, std::vector<String>* chapterAndVerse, int returnNumber);
		void HandleHyphenatedReference(std::vector<String>* firstandPossSecond, String firstElement, std::vector<int>* returnList);
	};
}

#endif;