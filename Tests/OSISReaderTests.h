#pragma once
#include "TestBase.h"

void TestCurrentReader() {
	TEST_ASSERT_EQUAL_STRING(Kuwagata::GetCurrentVersion().c_str(), "kjv");
}

void TestAlternateVersion() {
	try {
		Kuwagata::ChangeOSISPath("OSISBibles/asv");
		TEST_ASSERT_EQUAL_STRING(Kuwagata::GetCurrentVersion().c_str(), "asv");
	} catch (std::exception e) {
		TEST_FAIL();
	}
	LoadReference("Genesis 1:1");
	TEST_ASSERT_EQUAL(ids->size(), 1);
	TEST_ASSERT_EQUAL(ids->at(0), 1001001);
	TEST_ASSERT_EQUAL(refs->size(), 1);
	TEST_ASSERT_EQUAL_STRING(refs->at(0).c_str(), "Genesis 1:1");
	TEST_ASSERT_EQUAL_STRING(verses->at(0).c_str(), "In the beginning God created the heavens and the earth.");
}

void TestInvalidPath() {
	try {
		Kuwagata::ChangeOSISPath("OSISBibles/niv");
		TEST_FAIL();
	} catch (std::invalid_argument e) {

	}
}

void TestEmptyPath() {
	try {
		Kuwagata::ChangeOSISPath("OSISBibles/darby");
		TEST_FAIL();
	} catch (std::invalid_argument e) {

	}
}

void RunOSISReaderTests() {
	RUN_TEST(TestCurrentReader);
	RUN_TEST(TestAlternateVersion);
	RUN_TEST(TestEmptyPath);
	RUN_TEST(TestInvalidPath);
}
