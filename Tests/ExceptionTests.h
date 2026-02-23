#include"TestBase.h"
#pragma once
using namespace KuwagataDLL;


void TestUnknownBookException() {
	LoadReference("Lua 1:2-12;Genesis 1:1-12;Sol 2:1-22");
	std::vector<UserException> exceptions = Kuwagata::GetRaisedExceptions();
	TEST_ASSERT_EQUAL(exceptions.size(), 2);
	TEST_ASSERT_EQUAL(verses->size(), 12);
	TEST_ASSERT_EQUAL_STRING(exceptions.at(0).asString().c_str(),
		"Unknown book: \"Lua 1:2-12\" did not match any of the 66 books loaded.");
	TEST_ASSERT_EQUAL_STRING(exceptions.at(1).asString().c_str(),
		"Unknown book: \"Sol 2:1-22\" did not match any of the 66 books loaded.");
}

void TestUnknownChapterException() {
	LoadReference("Genesis 2;Genesis 110");
	std::vector<UserException> exceptions = Kuwagata::GetRaisedExceptions();
	TEST_ASSERT_EQUAL(exceptions.size(), 1);
	TEST_ASSERT_EQUAL(verses->size(), 25);
	TEST_ASSERT_EQUAL_STRING(exceptions.at(0).asString().c_str(),
		"Chapter selection \"Genesis 110\" out of range for book Genesis");
}

void TestUnknownVerseException() {
	LoadReference("Exodus 10:1;Genesis 2:96;Leviticus 10:13");
	std::vector<UserException> exceptions = Kuwagata::GetRaisedExceptions();
	TEST_ASSERT_EQUAL(exceptions.size(), 1);
	TEST_ASSERT_EQUAL(verses->size(), 2);
	TEST_ASSERT_EQUAL_STRING(exceptions.at(0).asString().c_str(),
		"Reference \"Genesis 2:96\" out of range for selected chapter.");

}

void RunExceptionTests() {
	RUN_TEST(TestUnknownBookException);
	RUN_TEST(TestUnknownChapterException);
	RUN_TEST(TestUnknownVerseException);
}