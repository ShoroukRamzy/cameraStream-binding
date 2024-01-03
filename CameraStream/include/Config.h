#ifndef CONFIG_H
#define CONFIG_H


#include "Types.h"
#include <string>

class Config{

    public:
     Config()=default;
    ~Config()=default;
    camera_stream_types::VirtualCamConfig read(std::string &&config_file_path);
    
};

#endif