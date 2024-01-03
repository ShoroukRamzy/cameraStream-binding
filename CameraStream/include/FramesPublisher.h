#ifndef FRAMEPUBLISHER_H
#define FRAMEPUBLISHER_H
#include<memory>
#include <vector>
#define AFB_BINDING_X4R1_ITF_REVISION 5 
#define AFB_BINDING_VERSION 4
#include <afb/afb-binding>


class FramePublisher{
  public:
      FramePublisher(const afb::event & camera_event);
      ~FramePublisher();

      void publish(std::vector<unsigned char> binary_img);


   private:
      afb::event camera_event_;
};

#endif