#include <stdexcept>
#include"FrameProcessor.h"  

std::vector<unsigned char> FrameProcessor::encodeImgToBinary(const cv::Mat& img, const std::string & extension){
   
   //may need . before the extension
   std::vector<unsigned char> encodedBuffer;
   if (cv::imencode(extension , img, encodedBuffer))
        return encodedBuffer;
   else
        throw std::runtime_error("can not incode the image!");
       
}

cv::Mat FrameProcessor::decodeBinaryToImg( const std::vector<unsigned char>& binary_img){
    
    //In the case of color images, the decoded images will have the channels stored in B G R order.
    cv::Mat decodedImg=cv::imdecode(binary_img, cv::IMREAD_COLOR);
    if(decodedImg.empty())
    {
        throw std::runtime_error("can not dencode the binary image!");
    }
    else{
        cv::imshow("Decoded Image", decodedImg);
        return decodedImg;
    }
}