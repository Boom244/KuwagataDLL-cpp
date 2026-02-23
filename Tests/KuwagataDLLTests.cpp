#include"unity.h"
#include"Main.h"
#include "ExceptionTests.h";
#include "VerseTests.h"
#include<stdio.h>
#include<iostream>

using namespace KuwagataDLL;


int main(void) {
	UNITY_BEGIN();
	Main::Initialize("OSISBibles/kjv/verses.json");
	RunVerseTests();
	RunExceptionTests();
	Main::Release();
	return UNITY_END();
}


