#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include<vector>
#include <opencv2/opencv.hpp>
class FrameProcessor{

    public:
    FrameProcessor()=default;
    ~FrameProcessor()=default;

    std::vector<unsigned char> encodeImgToBinary(const cv::Mat& img, const std::string & extension);
    cv::Mat decodeBinaryToImg( const std::vector<unsigned char>& binary_img);
    
};

#endif