#include"unity.h"
#include"Main.h"
#include "ExceptionTests.h";
#include "VerseTests.h"
#include<stdio.h>
#include<iostream>

using namespace KuwagataDLL;

int main(void) {
	UNITY_BEGIN();
	Main::Initialize("verses.json");
	RunVerseTests();
	RunExceptionTests();
	return UNITY_END();
}


