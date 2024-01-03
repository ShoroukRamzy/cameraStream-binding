#include"Config.h"
#include "json.hpp"
#include <fstream>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include <linux/videodev2.h>


 camera_stream_types::VirtualCamConfig Config::read(std::string &&config_file_path)
 {
    camera_stream_types::VirtualCamConfig config_s;

    // Read JSON data from the file
    std::ifstream configFile(config_file_path);
    if (!configFile.is_open()) {
        throw std::runtime_error("Error opening JSON configuration file:"+config_file_path);
        
    }
    nlohmann::json j;
    configFile >> j;
    configFile.close();
    config_s.type=j["TYPE"];
    config_s.device=j["DEVICE"];
    config_s.width = j["WIDTH"];
    config_s.height = j["HEIGHT"];
    config_s.fps = j["FPS"];
    config_s.frameStoreSize=j["FRAME_STORE_SIZE"];
    if(V4L2_PIX_FMT_BGR24==j["PIXELFMT"])
    {
       config_s.pixelFormat= V4L2_PIX_FMT_BGR24;
    } 
    else if (V4L2_PIX_FMT_RGB24==j["PIXELFMT"])
    {
        config_s.pixelFormat= V4L2_PIX_FMT_RGB24;
    }
    
    config_s.extention= j["EXT"];
    config_s.img_dir= j["IMG_DIR"];
    return config_s;
 }