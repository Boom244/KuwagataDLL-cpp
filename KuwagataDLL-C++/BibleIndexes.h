#ifndef BIBLE_INDEXES
#define BIBLE_INDEXES
#include<string>
#include<regex>
using String = std::string;
using Regex = std::regex;

namespace KuwagataDLL {

	class BibleIndexes {

		public:
			enum SelectionOption {
				Verse = 1,
				Chapter = 1000,
				Book = 1000000
			};
			static int IncreaseBibleReference(int reference, SelectionOption so);
			static int GetBibleIndexFromArray(String element);
			static std::string GetFromBiblePlainArray(int index);
			static bool IsOneChapterBook(int book);
		
	};

	

}
/*
	Considering all this thing does
	is hold data, this should have probably
	been a mostly static class...
	Wish someone told me that when I wrote the C# implementation
	when I was 16...
*/
#endif