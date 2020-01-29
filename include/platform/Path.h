#include <vector>
namespace Platform {
    namespace Path {
        String GetFontPath();
        std::vector<String> ListFiles(String directory, bool excludePath = false);
    }
}
