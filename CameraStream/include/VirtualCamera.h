#ifndef VIRTUALCAMERA_H
#define VIRTUALCAMERA_H
#include <string>
#include <vector>
#include <memory>
#include "Types.h"
#include "StreamHandlerIF.h"
#include "ImageLoader.h"


class VirtualCamera : public StreamHandlerIF
{
    public:

     VirtualCamera()=default;
    ~VirtualCamera();
    void init(const camera_stream_types::VirtualCamConfig& config_s)override;
    void openCamera() override;
    cv::Mat read()override;
    void writeImgs(const std::vector<std::string> & img_names);

    private:
    std::string input_device;
    unsigned int frame_time_ms;
    int fd_device;
    cv::Mat frame;
    cv::VideoCapture cap;
    std::unique_ptr<ImageLoader> img_loader_;

};

#endif

