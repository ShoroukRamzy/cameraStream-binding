
#include "CircQProcessedFrames.h"

CircQProcessedFrames::CircQProcessedFrames(const size_t& q_size):capacity_{q_size}
{
    
}

void CircQProcessedFrames::push(const std::vector<unsigned char> &BinaryImg){
    std::unique_lock<std::mutex> lock(mtx_);
    if(capacity_==msg_q.size())
    {
        //remove the oldest item
        msg_q.pop();

    }
 msg_q.push(BinaryImg);
 has_data_.notify_all();
}

std::vector<unsigned char> CircQProcessedFrames::pop()
{   
    std::unique_lock<std::mutex> lock(mtx_);
    //wait for data to be added 
    has_data_.wait(lock,[this]{return !msg_q.empty();});
    std::vector<unsigned char> binaryImg;
    binaryImg=msg_q.front();
    msg_q.pop();
    return binaryImg;

}

std::vector<unsigned char> CircQProcessedFrames::front()
{
    return msg_q.front();

}

CircQProcessedFrames::~CircQProcessedFrames()
{

}