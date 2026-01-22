#ifndef USER_EXCEPTION
#define USER_EXCEPTION

/*
	A major design flaw of the first iteration of Kuwagata was that if you messed up any part of a reference,
	you were basically stuck with an unhelpful error message that left you no clue what part you messed up,
	and messing up any part of a reference halted interpretation immediately, leaving you with 0 verses to display
	even if you only messed up the verse on the end. This is cumbersome, especially for long and large references that
	require scrolling back and forth in order to understand where you messed up.
	Hopefully, implementing a class like this will help mitigate both of these issues. 
	
*/


#include"OSISReader.h"

namespace KuwagataDLL {

	enum ExceptionType {
		UNKNOWN_BOOK, //You referenced a book that we don't have.
		CHAPTER_OUT_OF_RANGE, //Your chapter is out of range for the book we have.
		VERSE_OUT_OF_RANGE, //Your verse is out of range for the chapter we have.
		MANGLED_REFERENCE //Your reference is mangled and uninterpretable. 
	};

	/*
	The UserException class, designed to allow users to understand errors returned by KuwagataDLL more comprehensively
	and to increase program fault-tolerance. 
	*/
	class UserException {
	public:
		UserException(ExceptionType type, int exceptionReference);
		UserException(ExceptionType type, String offendingUserInput);
		String AsString();
		ExceptionType getExceptionType();
	private:
		ExceptionType type;
		int exceptionReference;
		String offendingUserInput;

	};
}

#endif