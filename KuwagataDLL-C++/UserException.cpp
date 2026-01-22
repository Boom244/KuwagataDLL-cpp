#include "UserException.h"

namespace KuwagataDLL {
	UserException::UserException(ExceptionType type, int exceptionReference){
		this->type = type;
		this->offendingUserInput = "";
		this->exceptionReference = exceptionReference;
	}

	UserException::UserException(ExceptionType type, String offendingUserInput){
		this->type = type;
		this->offendingUserInput = offendingUserInput;
		this->exceptionReference = 0;
	}

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