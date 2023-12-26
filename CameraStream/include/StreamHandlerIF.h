#ifndef STREAMHANDLERIF_H
#define STREAMHANDLERIF_H
#include<string>

class StreamHandler{

    public:
    StreamHandler()=default;
    ~StreamHandler()=default;

    virtual void init(const std::string& config_file_path)=0;
    virtual void start()=0;
    

};
#endif