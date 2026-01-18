#include "util.h"


namespace KuwagataDLL {

	

	/*
	Splits a string by the presence of a character.
	@param string The string to split.
	@param splitter The character by which to split the string.
	@return A pointer to a vector including all the split pieces of the String.
	If there are no occurrences of character splitter in the string, then
	this vector will just contain the input string. */
	std::vector<std::string>* Util::split(std::string string, char splitter) {
		std::vector<std::string>* ret = new std::vector<std::string>();
		int caret = string.find(splitter);
		while (caret != std::string::npos) {
			ret->push_back(string.substr(0, caret));
			string = string.substr(caret+1);
			caret = string.find(splitter);
		}
		ret->push_back(string);
		return ret;
	}
}


