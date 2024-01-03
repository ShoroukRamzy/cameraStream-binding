#include "ImageLoader.h"
#include <dirent.h>
#include <algorithm>
#include <stdexcept>

 std::vector<std::string> ImageLoader::loadImgs(const std::string& directory, const std::string& extension)
 {
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> fileNames;
    if ((dir = opendir(directory.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            std::string fileName = ent->d_name;
            if (fileName != "." && fileName != ".." && fileName.substr(fileName.find_last_of(".") + 1) == extension) {
                fileNames.push_back(directory + "/" + fileName);
            }
        }
        closedir(dir);
    } else {
        throw std::runtime_error("Could not open directory: " + directory);
    }

    std::sort(fileNames.begin(), fileNames.end());
    return fileNames;
 }