#include "VirtualCamera.h"
#include <dirent.h>
#include <algorithm>
#include <stdexcept>
#include "json.hpp"
#include <fstream>
#include <iostream>


void VirtualCamera::init(const std::string& config_file_path)
{

    // Read JSON data from the file
    std::ifstream configFile(config_file_path);
    if (!configFile.is_open()) {
        std::cerr << "Error opening JSON configuration file: " << config_file_path << std::endl;
        return;
    }

    nlohmann::json j;
    configFile >> j;
    configFile.close();

    config_s.device=j["DEVICE"];
    config_s.width = j["WIDTH"];
    config_s.height = j["HEIGHT"];
    config_s.fps = j["FPS"];
    config_s.pixelFormat= j["PIXELFMT"];
    config_s.extention= j["EXT"];
    config_s.img_dir= j["IMG_DIR"];
    
}

void VirtualCamera::start()
{
    //TO_DO
    //loadImgs
    //iterate to write imgs in the loopback device
}

std::vector<std::string> VirtualCamera::loadImgs(const std::string& directory, const std::string& extension){
  
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