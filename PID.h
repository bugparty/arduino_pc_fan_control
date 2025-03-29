#ifndef PID_H
#define PID_H

class PID {
private:
    float Kp, Ki, Kd;
    float setpoint;
    float integral;
    float prevError;
    unsigned long lastTime;
    int outputMin;
    int outputMax;

public:
    PID(float kp, float ki, float kd, float setpt, int minOut, int maxOut)
        : Kp(kp), Ki(ki), Kd(kd), setpoint(setpt), integral(0), prevError(0),
          outputMin(minOut), outputMax(maxOut) {
        lastTime = millis();
    }

    int compute(float input) {
        unsigned long now = millis();
        float dt = (now - lastTime) / 1000.0f;
        
        if (dt <= 0 || dt > 1.0f) {  // 过滤异常时间值
            dt = 0.1f;
        }

        float error = input - setpoint;  // 正向控制：温度越高输出越大
        float newIntegral = integral + error * dt;
        float derivative = (error - prevError) / dt;

        // 计算未限制的输出
        float output = Kp * error + Ki * newIntegral + Kd * derivative;

        // 抗积分饱和处理
        if (output > outputMax) {
            output = outputMax;
        } else if (output < outputMin) {
            output = outputMin;
        } else {
            integral = newIntegral;  // 只有输出未饱和时才更新积分
        }

        prevError = error;
        lastTime = now;
        
        return constrain(static_cast<int>(output + 0.5f), outputMin, outputMax);
    }

    void setSetpoint(float setpt) { setpoint = setpt; }
    void setParams(float kp, float ki, float kd) { Kp = kp; Ki = ki; Kd = kd; }
};

#endif
