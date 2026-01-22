#include "UserException.h"

namespace KuwagataDLL {

	/*
	Constructor for a UserException pertaining to a certain reference.
	@param type the type of exception.
	@param exceptionReference The numerical reference associated with this exception.
	*/
	UserException::UserException(ExceptionType type, int exceptionReference){
		this->type = type;
		this->offendingUserInput = "";
		this->exceptionReference = exceptionReference;
	}

	/*
	Constructor for a UserException pertaining to user input..
	@param type the type of exception.
	@param offendingUserInput the user input that raised this exception.
	*/
	UserException::UserException(ExceptionType type, String offendingUserInput){
		this->type = type;
		this->offendingUserInput = offendingUserInput;
		this->exceptionReference = 0;
	}

	/*
	Outputs a string based on the internal data in this exception object.
	*/
	std::string UserException::AsString()
	{
		switch (type) {
		case MANGLED_REFERENCE:
			return String("Mangled reference: \"" + offendingUserInput + "\" is not in the form that Kuwagata accepts.");
			break;
		case CHAPTER_OUT_OF_RANGE:
			{
				String reference = OSISReader::DecodeReference(exceptionReference);
				return String("Chapter selection \"" + reference + "\" out of range for book "
					+ BibleIndexes::GetFromBiblePlainArray(exceptionReference / BibleIndexes::SelectionOption::Book));
			}
			break;
		case VERSE_OUT_OF_RANGE:
			{
				String reference = OSISReader::DecodeReference(exceptionReference);
				return String("Reference \"" + reference + "\" out of range for selected chapter.");
			}
			break;
		default:
			break;
		}
	}

	ExceptionType UserException::getExceptionType()
	{
		return type;
	}

}