#include <vector>
#include <string>
#include <sstream>

#include "utils.h"

namespace CRequest {

namespace Utils {

std::vector<std::string>* split(const std::string& str, char delimiter) {
    auto result = new std::vector<std::string>();
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        result -> push_back(token);
    }
    return result;
}





} // namesapce Utils

} // namespace CRequest