#include "MeanFilter.h"

MeanFilter::MeanFilter(int s) {
    size = s;
    buffer = new float[size];
    index = 0;
    count = 0;
}

MeanFilter::~MeanFilter() {
    delete[] buffer;
}

float MeanFilter::addValue(float value) {
    buffer[index] = value;
    index = (index + 1) % size;

    if (count < size) count++;

    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += buffer[i];
    }

    return sum / count;
}

size_t MeanFilter::printTo(Print& p) const {
    // 输出当前滤波器的平均值
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += buffer[i];
    }
    float average = sum / count;
    return p.print(average);  // 返回平均值作为字符串输出
}
