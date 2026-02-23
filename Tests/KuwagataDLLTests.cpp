#include"unity.h"
#include"Kuwagata.h"
#include "ExceptionTests.h";
#include "VerseTests.h"
#include<stdio.h>
#include<iostream>

using namespace KuwagataDLL;


int main(void) {
	UNITY_BEGIN();
	Kuwagata::Initialize("OSISBibles/kjv/verses.json");
	RunVerseTests();
	RunExceptionTests();
	Kuwagata::Release();
	return UNITY_END();
}


