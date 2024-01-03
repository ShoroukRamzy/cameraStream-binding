#include"FramesPublisher.h"
 
FramePublisher::FramePublisher(const afb::event & camera_event)
{
    camera_event_=camera_event;
}
 
void FramePublisher::publish(std::vector<unsigned char> binary_img) 
{

    afb::data img_data = afb::data(afb::BYTEARRAY(),
                                 static_cast<unsigned char*>(binary_img.data()),
                                 binary_img.size());
    camera_event_.push(img_data);

}

      
FramePublisher::~FramePublisher(){

}