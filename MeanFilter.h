#ifndef MEANFILTER_H
#define MEANFILTER_H

#include "Arduino.h"

class MeanFilter : public Printable {
public:
    MeanFilter(int size);
    ~MeanFilter();
    float addValue(float value);
    virtual size_t printTo(Print& p) const override;  // 实现 Printable 接口

private:
    float* buffer;
    int size;
    int index;
    int count;
};

#endif
