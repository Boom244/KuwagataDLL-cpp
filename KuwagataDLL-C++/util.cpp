#include "util.h"
//Too tired to figure out how to do this otherwise. We'll just write some
//C-like C++ instead and go with that.

namespace KuwagataDLL {
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


