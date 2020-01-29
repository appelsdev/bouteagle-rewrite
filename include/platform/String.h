#include <vector>
#include <string>
#ifndef UNICODE
    typedef std::string String;
#else
    typedef std::wstring String;
#endif

namespace Platform {
    const std::vector<std::string> Explode(const char& c, const std::string& s);
    const std::vector<int> StringToIntegers(const std::string& s);
}
