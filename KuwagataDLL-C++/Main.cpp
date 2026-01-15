#include "Main.h"

namespace KuwagataDLL {
	std::vector<String>* Main::verses;
	std::vector<String>* Main::plainVerseReferences;
	std::vector<int>* Main::verseIds;
	int Main::currentIndex = 0;
	OSISReader* Main::reader;

	KUWAGATA_DLL void Main::Initialize(String OSISpath){
		reader = new OSISReader(OSISpath);
	}
	KUWAGATA_DLL void Main::ChangeOSISPath(String newOSISPath){
		reader->ChangeOSISPath(newOSISPath);
	}
	KUWAGATA_DLL void Main::StartNewRequest(String Verse){
		//Reset the current index
		currentIndex = 0;

		//Give the user their verses.
		if (verseIds != nullptr) {
			delete verseIds;
			delete plainVerseReferences;
			delete verses;
		}

		verseIds = reader->GetReferencesFromString(Verse, false);
		verses = reader->GetVersesFromReferences(*verseIds);

		plainVerseReferences = reader->BatchDecodeAllReferences(*verseIds);
	}
	KUWAGATA_DLL OSISReader* Main::GetOSISReader()
	{
		return reader;
	}
	KUWAGATA_DLL std::vector<String>* Main::GetVerses()
	{
		return verses;
	}
	KUWAGATA_DLL std::vector<String>* Main::GetReferences()
	{
		return plainVerseReferences;
	}
	KUWAGATA_DLL std::vector<int>* Main::GetVerseIDs()
	{
		return verseIds;
	}
}
