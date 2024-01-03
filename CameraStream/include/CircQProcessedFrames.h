#ifndef FRAMEPROCESSEDCIRCQ_H
#define FRAMEPROCESSEDCIRCQ_H

#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>

class CircQProcessedFrames{
    public:
    CircQProcessedFrames(const size_t& q_size);
    ~CircQProcessedFrames();

    void push(const std::vector<unsigned char> &BinaryImg);
    std::vector<unsigned char> pop();
    std::vector<unsigned char> front();

    private:
    size_t capacity_;
    std::queue<std::vector<unsigned char>> msg_q;
    std::mutex mtx_;
    std::condition_variable has_data_;

};

#endif