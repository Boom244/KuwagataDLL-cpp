#include"Main.h"
#include"unity.h"
#pragma once
using namespace KuwagataDLL;

std::vector<int>* ids;
std::vector<String>* verses;
std::vector<String>* refs;

void LoadReference(String reference) {
	Main::StartNewRequest(reference);

	ids = Main::GetVerseIDs();
	verses = Main::GetVerses();
	refs = Main::GetReferences();
}

void tearDown() {

}

void setUp()
{

}