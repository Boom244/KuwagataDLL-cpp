#ifndef KUWAGATA_DLL_MAIN
#define KUWAGATA_DLL_MAIN

#include"BibleIndexes.h"
#include"OSISReader.h"

#ifndef KUWAGATA_DLL_EXPORTS
#define KUWAGATA_DLL __declspec(dllexport)
#else 
#define KUWAGATA_DLL __declspec(dllimport)
#endif

namespace KuwagataDLL {
	class Kuwagata {
	public:
		KUWAGATA_DLL static void Initialize(String OSISpath);
		KUWAGATA_DLL static void ChangeOSISPath(String newOSISPath);
		KUWAGATA_DLL static void StartNewRequest(String Verse);
		KUWAGATA_DLL static String GetCurrentVersion();
		KUWAGATA_DLL static std::vector<UserException> GetRaisedExceptions();
		KUWAGATA_DLL static std::vector<String>* GetVerses();
		KUWAGATA_DLL static std::vector<String>* GetReferences();
		KUWAGATA_DLL static std::vector<int>* GetVerseIDs();
		KUWAGATA_DLL static void Release();
	private:
		static std::vector<String>* verses;
		static std::vector<String>* plainVerseReferences;
		static std::vector<int>* verseIds;
		static OSISReader* reader;
	};
}

#endif;