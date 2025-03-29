#include "MeanFilter.h"
#include "PID.h"

// 硬件定义
const int pwmPin = 5;
const int tachPin = 2;
const int thermistorPin = 23;

// 全局变量
volatile unsigned long pulseCount = 0;
unsigned long lastTime = 0;
float rpm = 0;
int pwmValue = 50;  // 初始占空比设为最低有效值
float targetTemp = 28.0;  // 初始目标温度

MeanFilter fanRPMFilter(10);
PID myPID(15.0, 2.0, 1.0, targetTemp, 50, 255);  // PID参数需要根据实际系统调整

void setup() {
    pinMode(pwmPin, OUTPUT);
    pinMode(tachPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(tachPin), countPulse, FALLING);
    Serial.begin(9600);
    analogWrite(pwmPin, pwmValue);  // 初始化PWM输出
}

void loop() {
    static unsigned long lastPIDTime = 0;
    unsigned long currentTime = millis();

    // PID控制周期（200ms）
    if (currentTime - lastPIDTime >= 200) {
        float currentTemp = readTemp();
        pwmValue = myPID.compute(currentTemp);
        analogWrite(pwmPin, pwmValue);
        lastPIDTime = currentTime;
    }

    // 转速计算和打印周期（1s）
    if (currentTime - lastTime >= 1000) {
        rpm = (pulseCount / 2.0) * 60.0;
        fanRPMFilter.addValue(rpm);
        pulseCount = 0;
        
        Serial.print("Temp: ");
        Serial.print(readTemp());
        Serial.print("°C | RPM: ");
        Serial.print(fanRPMFilter.getAverage());
        Serial.print(" | PWM: ");
        Serial.println(pwmValue);
        
        lastTime = currentTime;
    }
}

// 中断服务函数
void countPulse() { pulseCount++; }

// 温度读取函数
float readTemp() {
    int tempReading = analogRead(thermistorPin);
    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
    float tempC = tempK - 273.15;
    //float tempF = (tempC * 9.0)/ 5.0 + 32.0;
    return tempC;
}
