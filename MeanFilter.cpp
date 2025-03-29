#include "MeanFilter.h"

MeanFilter::MeanFilter(int s) 
    : size(s), index(0), count(0) {
    buffer = new float[size]();
}

MeanFilter::~MeanFilter() {
    delete[] buffer;
}

void MeanFilter::addValue(float value) {
    buffer[index] = value;
    index = (index + 1) % size;
    if(count < size) count++;
}

void MeanFilter::reset() {
    index = 0;
    count = 0;
}

float MeanFilter::getAverage() const {
    if(count == 0) return 0;
    
    float sum = 0;
    for(int i = 0; i < count; i++) {
        sum += buffer[(index - count + i + size) % size];  // 正确访问环形缓冲区
    }
    return sum / count;
}

size_t MeanFilter::printTo(Print& p) const {
    return p.print(getAverage());  // 复用核心方法
}