#ifndef STREAMHANDLERIF_H
#define STREAMHANDLERIF_H

#include<string>
#include "Types.h"
#include <opencv2/opencv.hpp>
class StreamHandlerIF{

    public:
    StreamHandlerIF()=default;
    ~StreamHandlerIF()=default;
    
    virtual void init( const camera_stream_types::VirtualCamConfig& config_s)=0;
    virtual void openCamera()=0;
    virtual cv::Mat read()=0;
    
    
    

};
#endif