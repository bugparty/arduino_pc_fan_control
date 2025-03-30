#ifndef MEANFILTER_H
#define MEANFILTER_H

#include "Arduino.h"

class MeanFilter : public Printable {
public:
    MeanFilter(int size);
    ~MeanFilter();
    
    void addValue(float value);         // Returns average immediately when adding new value
    void reset();
    float getAverage() const;           // Core calculation method
    virtual size_t printTo(Print& p) const override;

private:
    float* buffer;
    int size;
    int index;
    int count;
};

#endif
