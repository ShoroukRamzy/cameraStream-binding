#ifndef TYPES_H
#define TYPES_H

#include <string>

namespace camera_stream_types{

    using VirtualCamConfig=struct virtual_camera_configurations
    {
            
        std::string device;
        std::string pixelFormat;
        std::string extention;
        std::string img_dir;
        int width;
        int height;
        int fps;
        
    };
        

}

#endif
