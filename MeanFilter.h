#ifndef MEANFILTER_H
#define MEANFILTER_H

#include "Arduino.h"

class MeanFilter : public Printable {
public:
    MeanFilter(int size);
    ~MeanFilter();
    
    void addValue(float value);         // 添加新值时直接返回平均值
    void reset();
    float getAverage() const;           // 核心计算方法
    virtual size_t printTo(Print& p) const override;

private:
    float* buffer;
    int size;
    int index;
    int count;
};

#endif