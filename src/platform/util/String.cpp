#include "platform/String.h"
namespace Platform {

const std::vector<std::string> Explode(const char& c, const std::string& s) {
    std::string buff{""};
    std::vector<std::string> v;

    for (auto n:s) {
        if (n != c) buff+=n; else
        if (n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);

    return v;
}

const std::vector<int> StringToIntegers(const std::string& s) {
    std::vector<std::string> tokens = Explode(',', s);
    std::vector<int> values;
    for (auto t : tokens)
        values.push_back(std::stoi(t));
    return values;
}

}
