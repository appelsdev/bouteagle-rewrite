#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
#include "platform/String.h"
#include "system/Exception.h"

namespace Platform {
    namespace Path {
        String GetFontPath() {
            TCHAR path[MAX_PATH];
            GetWindowsDirectory(path, MAX_PATH);
            return String(path) + "\\Fonts\\";
        }

        /**
         * List filenames within specified directory.
         * @TODO: Recursive find files.
         *
         * @param String directory   Directory to search in.
         * @param bool   excludePath Whether to exclude the path from the filenames.
         *
         * @return String
         */
        std::vector<String> ListFiles(String directory, bool excludePath = false) {
            std::vector<String> filenames;
            String searchPath = directory + "/*.*";
            WIN32_FIND_DATA fd;
            HANDLE hFind = FindFirstFile(searchPath.c_str(), &fd);
            if (INVALID_HANDLE_VALUE == hFind) {
                THROW_EXCEPTION(IOException, "Unable to list files in directory '" + directory + "'");
            }
            do {
                if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    filenames.push_back((excludePath ? "" : directory) + fd.cFileName);
                }
            } while (FindNextFile(hFind, &fd));
            FindClose(hFind);
            return filenames;
        }
    }
}
