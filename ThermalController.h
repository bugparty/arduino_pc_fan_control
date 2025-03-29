#ifndef THERMALCONTROLLER_H
#define THERMALCONTROLLER_H

class ThermalController {
public:
    int computePWM(float temperature) {
        temperature = constrain(temperature, 0, 100);  // 确保温度在合理范围
        
        if (temperature <= 35.0) {
            return 50;  // 最低转速占空比
        } else if (temperature <= 40.0) {
            return 50 + (temperature - 35.0) * (87 - 50) / 5.0;
        } else if (temperature <= 50.0) {
            return 87 + (temperature - 40.0) * (255 - 87) / 10.0;
        } else {
            return 255;  // 最大占空比
        }
    }
};

#endif
