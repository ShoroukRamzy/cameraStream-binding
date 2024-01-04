#include <stdexcept>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include<cstdlib>
#include <linux/videodev2.h>
#include "VirtualCamera.h"

void VirtualCamera::init( const camera_stream_types::VirtualCamConfig& config_s){

    fd_device = open(config_s.device.c_str(), O_RDWR);
    if (-1==fd_device) {
        throw std::runtime_error("Could not open " + config_s.device);
    }
    
    input_device=config_s.device;
    frame_time_ms=1000/config_s.fps;
    //set camera format and resolution
    v4l2_format fmt = {0};
    fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    fmt.fmt.pix.width = config_s.width;
    fmt.fmt.pix.height = config_s.height;
    fmt.fmt.pix.pixelformat = config_s.pixelFormat;
    fmt.fmt.pix.field = V4L2_FIELD_NONE;
    if (xioctl(fd_device, VIDIOC_S_FMT, &fmt)==-1) {
        throw std::runtime_error("Error setting camera format for this device"+config_s.device);
     }

    img_loader_=std::make_unique<ImageLoader>();
    writeImgs(img_loader_->loadImgs(config_s.img_dir,config_s.extention));
}

void VirtualCamera::writeImgs(const std::vector<std::string> & img_names)
{
        for (const auto &imgName : img_names) {
            cv::Mat frame = cv::imread(imgName);
            cv::Mat dst;
            cv::cvtColor(frame, dst, cv::COLOR_BGR2RGB);
            write(fd_device, dst.data, dst.total() * dst.elemSize());
            cv::waitKey(frame_time_ms);
        }
         close(fd_device);
}

void VirtualCamera::openCamera()
{
    cap.open(input_device);
    if(!cap.isOpened())
        throw std::runtime_error("can not open "+input_device);
}

cv::Mat VirtualCamera::read()
{
    cap.read(frame);
    if(frame.empty())
        throw std::runtime_error("can not read frames from"+input_device);
    return frame;
   
}

int VirtualCamera::xioctl(int fh, unsigned long request, void *arg) {
    int r;
    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);
    return r;
}


VirtualCamera::~VirtualCamera() {
    if(fcntl ( fd_device, F_GETFL )>0)// device is open
        close(fd_device);
}