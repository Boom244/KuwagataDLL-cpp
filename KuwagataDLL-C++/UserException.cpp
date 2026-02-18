#include "UserException.h"
#include"OSISReader.h"
namespace KuwagataDLL {

	/*
	Constructor for a UserException pertaining to a certain reference.
	@param type the type of exception.
	@param exceptionReference The numerical reference associated with this exception.
	*/
	UserException::UserException(ExceptionType eType, int reference){
		type = eType;
		offendingUserInput = "";
		exceptionReference = reference;
	}

	/*
	Constructor for a UserException pertaining to user input..
	@param type the type of exception.
	@param offendingUserInput the user input that raised this exception.
	*/
	UserException::UserException(ExceptionType eType, std::string  userInput){
		type = eType;
		offendingUserInput = userInput;
		exceptionReference = 0;
	}

	/*
	Outputs a string based on the internal data in this exception object.
	*/
	std::string UserException::asString()
	{
		switch (this->type) {
		case UNKNOWN_BOOK:
			return std::string("Unknown book: \"" + offendingUserInput + "\" did not match any of the 66 books loaded.");
			break;
		case CHAPTER_OUT_OF_RANGE:
			{
			std::string  reference = OSISReader::DecodeReference(exceptionReference);
				return std::string("Chapter selection \"" + reference + "\" out of range for book "
					+ BibleIndexes::GetFromBiblePlainArray(exceptionReference / BibleIndexes::SelectionOption::Book));
			}
			break;
		case VERSE_OUT_OF_RANGE:
			{
			std::string  reference = OSISReader::DecodeReference(exceptionReference);
				return std::string("Reference \"" + reference + "\" out of range for selected chapter.");
			}
			break;
		default:
			return NULL;
			break;
		}
	}

	ExceptionType UserException::getExceptionType()
	{
		return type;
	}

}