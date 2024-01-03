#ifndef TYPES_H
#define TYPES_H

#include <string>

namespace camera_stream_types{

    using VirtualCamConfig=struct virtual_camera_configurations
    {

        unsigned int width;
        unsigned int height;
        unsigned int fps;    
        unsigned int pixelFormat;
        unsigned int frameStoreSize;
        std::string type;
        std::string device;
        std::string extention;
        std::string img_dir;

    };
        

}

#endif
