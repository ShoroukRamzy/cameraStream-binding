#ifndef VIRTUALCAMERA_H
#define VIRTUALCAMERA_H

#include "StreamHandlerIF.h"
#include <string>
#include <vector>
#include "Types.h"

class VirtualCamera : public StreamHandler
{
    public:
    void init(const std::string& config_file_path)override;
    void start()override;

    private:

    std::vector<std::string> loadImgs(const std::string& directory, const std::string& extension);
    camera_stream_types::VirtualCamConfig config_s;
};

#endif

