#include"BibleIndexes.h"
#include"OSISReader.h"

#ifndef KUWAGATA_DLL_EXPORTS
#define KUWAGATA_DLL __declspec(dllexport)
#else 
#define KUWAGATA_DLL __declspec(dllimport)
#endif

namespace KuwagataDLL {
	class Main {
	public:
		KUWAGATA_DLL static void Initialize(String OSISpath);
		KUWAGATA_DLL static void ChangeOSISPath(String newOSISPath);
		KUWAGATA_DLL static void StartNewRequest(String Verse);
		KUWAGATA_DLL static OSISReader* GetOSISReader();
		KUWAGATA_DLL static std::vector<String>* GetVerses();
		KUWAGATA_DLL static std::vector<String>* GetReferences();
		KUWAGATA_DLL static std::vector<int>* GetVerseIDs();
	private:
		static std::vector<String>* verses;
		static std::vector<String>* plainVerseReferences;
		static std::vector<int>* verseIds;
		static int currentIndex;
		static OSISReader* reader;
	};
}