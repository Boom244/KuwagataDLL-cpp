#include"Kuwagata.h"
#include"unity.h"
#pragma once
using namespace KuwagataDLL;

std::vector<int>* ids;
std::vector<String>* verses;
std::vector<String>* refs;

void LoadReference(String reference) {
	Kuwagata::StartNewRequest(reference);

	ids = Kuwagata::GetVerseIDs();
	verses = Kuwagata::GetVerses();
	refs = Kuwagata::GetReferences();
}

void tearDown() {
	
}

void setUp()
{
	ids = nullptr;
	verses = nullptr;
	refs = nullptr;
}