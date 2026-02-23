#include "Kuwagata.h"

namespace KuwagataDLL {
	std::vector<String>* Kuwagata::verses;
	std::vector<String>* Kuwagata::plainVerseReferences;
	std::vector<int>* Kuwagata::verseIds;
	OSISReader* Kuwagata::reader;

	/*
	Initializes the DLL.
	@param OSISpath the path to the current verses.json that the
	DLL should read.
	*/
	KUWAGATA_DLL void Kuwagata::Initialize(String OSISpath){
		reader = new OSISReader(OSISpath);
	}

	/*
	Releases all dynamically allocated memory held by the DLL.
	De-initializes the current OSISReader. 
	*/
	KUWAGATA_DLL void Kuwagata::Release()
	{
		delete verseIds;
		delete verses;
		delete plainVerseReferences;
		delete reader;
	}

	/*
	* Gets the current vector of UserExceptions.
	* @return the vector of UserExceptions held by the current OSISReader.
	*/
	KUWAGATA_DLL std::vector<UserException> Kuwagata::GetRaisedExceptions()
	{
		return reader->getRaisedExceptions();
	}

	/*
	Changes the OSIS path.
	@param newOSISPath the path to the new verses.json that the
	DLL should read.
	*/
	KUWAGATA_DLL void Kuwagata::ChangeOSISPath(String newOSISPath){
		reader->ChangeOSISPath(newOSISPath);
	}

	/*
	Starts a new verse request. 
	@param Verse the reference to retrieve.
	*/
	KUWAGATA_DLL void Kuwagata::StartNewRequest(String Verse){

		if (verseIds != nullptr) {
			delete verseIds;
			delete plainVerseReferences;
			delete verses;
		}

		verseIds = reader->GetReferencesFromString(Verse, false);
		verses = reader->GetVersesFromReferences(*verseIds);

		plainVerseReferences = reader->BatchDecodeAllReferences(*verseIds);
	}

	/*
	Returns the OSISReader.
	*/
	KUWAGATA_DLL OSISReader* Kuwagata::GetOSISReader()
	{
		return reader;
	}

	/*
	Returns a pointer to the verses retrieved by this DLL.
	*/
	KUWAGATA_DLL std::vector<String>* Kuwagata::GetVerses()
	{
		return verses;
	}

	/*
	Returns a pointer to the references retrieved by this DLL.
	*/
	KUWAGATA_DLL std::vector<String>* Kuwagata::GetReferences()
	{
		return plainVerseReferences;
	}

	/*
	Returns a pointer to the verse IDs retrieved by this DLL.
	*/
	KUWAGATA_DLL std::vector<int>* Kuwagata::GetVerseIDs()
	{
		return verseIds;
	}
}
