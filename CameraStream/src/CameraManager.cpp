#include "CameraManager.h"

CameraManager::CameraManager(std::unique_ptr<StreamHandlerIF> && stream_ptr,
camera_stream_types::VirtualCamConfig &&config,
const afb::event &camera_event):stream_handler_ptr_(std::move(stream_ptr)),
                               config_s_(std::move(config)),
                               frame_publisher_(camera_event)
                               
{
    processed_frames_q=std::make_shared<CircQProcessedFrames>(config_s_.frameStoreSize);
   
}

void CameraManager::run()
{
    image_writer_thread=std::thread(&StreamHandlerIF::init,stream_handler_ptr_.get(),std::cref(config_s_));
    image_processing_thread=std::thread(&CameraManager::process_frames ,this );
    image_publisher_thread=std::thread(&CameraManager::publish_frames ,this );
}

void CameraManager::process_frames()
{
    stream_handler_ptr_->openCamera();
    cv::Mat frame;
    do{

        frame=stream_handler_ptr_->read();
        processed_frames_q->push(frame_processor_.encodeImgToBinary(frame,config_s_.extention));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        
    }while(!frame.empty());

}


void CameraManager::publish_frames()
{
    while(true)
    {
        frame_publisher_.publish(processed_frames_q->pop());
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
}

CameraManager::~CameraManager(){

    if(image_writer_thread.joinable())
        image_writer_thread.join();

    if(image_processing_thread.joinable())
        image_processing_thread.join();

    if(image_publisher_thread.joinable())
        image_publisher_thread.join();
    
}
