#pragma once
#include"TestBase.h"

void TestBasicReference() {
	LoadReference("Genesis 1:1");

	TEST_ASSERT_EQUAL(ids->size(), 1);
	TEST_ASSERT_EQUAL(ids->at(0), 1001001);
	TEST_ASSERT_EQUAL(refs->size(), 1);
	TEST_ASSERT_EQUAL_STRING(refs->at(0).c_str(), "Genesis 1:1");
	TEST_ASSERT_EQUAL_STRING(verses->at(0).c_str(), "In the beginning God created the heaven and the earth.");
}

void TestMultiReference() {
	LoadReference("Genesis 1:1-5");

	TEST_ASSERT_EQUAL(ids->size(), 5);
	for (int i = 1; i <= 5; i++) {
		TEST_ASSERT_EQUAL(ids->at(i - 1), 1001000 + i);
		TEST_ASSERT_EQUAL_STRING(refs->at(i - 1).c_str(), ("Genesis 1:" + std::to_string(i)).c_str());
	}
	TEST_ASSERT_EQUAL(refs->size(), 5);
}

void TestCrossChapterReference() {
	LoadReference("Genesis 1:1-2:1");
	TEST_ASSERT_EQUAL(ids->size(), 32);
	TEST_ASSERT_EQUAL_STRING(refs->back().c_str(), "Genesis 2:1");


}

void TestCompoundReference() {
	LoadReference("Genesis 2:3,4,5,6:7,7:6");
	TEST_ASSERT_EQUAL(ids->size(), 5);
	TEST_ASSERT_EQUAL_STRING(refs->front().c_str(), "Genesis 2:3");
	TEST_ASSERT_EQUAL_STRING(refs->back().c_str(), "Genesis 7:6");
}

void TestSingleChapterBooks() {
	LoadReference("Philemon 4");
	TEST_ASSERT_EQUAL(ids->size(), 1);
	TEST_ASSERT_EQUAL_STRING(refs->front().c_str(), "Philemon 1:4");

}

void TestSingleChapter() {
	LoadReference("Genesis 1");
	TEST_ASSERT_EQUAL(ids->size(), 31);
	TEST_ASSERT_EQUAL_STRING(refs->front().c_str(), "Genesis 1:1");
	TEST_ASSERT_EQUAL_STRING(refs->back().c_str(), "Genesis 1:31");
}

void TestMultiWordBooks() {
	LoadReference("1 Corinthians 1");
	TEST_ASSERT_EQUAL(ids->size(), 31);
	TEST_ASSERT_EQUAL_STRING(refs->front().c_str(), "1 Corinthians 1:1");
	TEST_ASSERT_EQUAL_STRING(refs->back().c_str(), "1 Corinthians 1:31");
}

void TestCrossBookReferences() {
	LoadReference("Genesis 1:1-Exodus 2:1");
	TEST_ASSERT_EQUAL(ids->size(), 1556);
	TEST_ASSERT_EQUAL_STRING(refs->front().c_str(), "Genesis 1:1");
	TEST_ASSERT_EQUAL_STRING(refs->back().c_str(), "Exodus 2:1");
}

void RunVerseTests() {
	RUN_TEST(TestBasicReference);
	RUN_TEST(TestMultiReference);
	RUN_TEST(TestCompoundReference);
	RUN_TEST(TestSingleChapterBooks);
	RUN_TEST(TestSingleChapter);
	RUN_TEST(TestMultiWordBooks);
	RUN_TEST(TestCrossBookReferences);
}