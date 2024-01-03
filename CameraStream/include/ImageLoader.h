#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include<vector>
#include<string>

class ImageLoader{

    public:
    ImageLoader()=default;
    ~ImageLoader()=default;
    std::vector<std::string> loadImgs(const std::string& directory, const std::string& extension);

};

#endif