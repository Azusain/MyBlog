#include <vector>
#include <string>
#include <sstream>

#include "utils.h"

namespace CRequest {

namespace Utils {

std::vector<std::string>* split(const std::string& str, const std::string& delimiter) {
    auto result = new std::vector<std::string>();
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result -> push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }
    result -> push_back(str.substr(start, end));
    return result;
}






} // namesapce Utils

} // namespace CRequest