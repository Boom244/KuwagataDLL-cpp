#include<string>
#include<vector>
#include <cstdlib>
#ifndef UTIL
#define UTIL
namespace KuwagataDLL {

	class Util {
	public:
		static std::vector<std::string>* split(std::string string, char splitter);
	};

}

#endif