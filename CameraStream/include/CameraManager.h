#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H
#include<memory>
#include<thread>
#include "Config.h"
#include "StreamHandlerIF.h"
#include "CircQProcessedFrames.h"
#include "FrameProcessor.h"
#include "FramesPublisher.h"

class CameraManager{
     public:
     CameraManager(std::unique_ptr<StreamHandlerIF> && stream_ptr,camera_stream_types::VirtualCamConfig &&config,const afb::event &camera_event);
     ~CameraManager();

     void run();

     private:

     std::unique_ptr<StreamHandlerIF> stream_handler_ptr_;
     camera_stream_types::VirtualCamConfig config_s_;
     FramePublisher frame_publisher_;
     FrameProcessor frame_processor_;
     std::shared_ptr<CircQProcessedFrames>processed_frames_q;
     
    // CircQProcessedFrames processed_frames_q;//this is to be passed by reference to both the processor and the publisher or to be handled by the camera manager directly
     std::thread image_writer_thread;
     std::thread image_processing_thread;
     std::thread image_publisher_thread;

     void process_frames();
     void publish_frames();

};

#endif
