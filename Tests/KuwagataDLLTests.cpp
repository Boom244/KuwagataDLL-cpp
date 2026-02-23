#include"unity.h"
#include"Kuwagata.h"
#include "ExceptionTests.h";
#include "VerseTests.h"
#include "OSISReaderTests.h"
#include<stdio.h>
#include<iostream>

using namespace KuwagataDLL;


int main(void) {
	UNITY_BEGIN();
	Kuwagata::Initialize("OSISBibles/kjv");
	RunVerseTests();
	RunExceptionTests();
	RunOSISReaderTests();
	Kuwagata::Release();
	return UNITY_END();
}


