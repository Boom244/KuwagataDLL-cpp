#include"unity.h"
#include"Main.h"
#include "ExceptionTests.h";
#include "VerseTests.h"
#include<stdio.h>
#include<iostream>

using namespace KuwagataDLL;

void TestMemLeaks() {
	LoadReference("Genesis 1");
	LoadReference("Genesis 1");
	LoadReference("Genesis 1");
	LoadReference("Genesis 1");
	LoadReference("Genesis 1");

}

int main(void) {
	UNITY_BEGIN();
	Main::Initialize("verses.json");
	RunVerseTests();
	RunExceptionTests();
	TestMemLeaks();
	Main::Release();
	return UNITY_END();
}


