#include "MeanFilter.h"
#include "ThermalController.h"
// 硬件定义
const int pwmPin = 5;
const int tachPin = 2;
const int thermistorPin = 23;

volatile unsigned long pulseCount = 0;
unsigned long lastTime = 0;
float rpm = 0;
int pwmValue = 50;
MeanFilter fanRPMFilter(10);
MeanFilter tempFilter(5);  // 温度滤波器
ThermalController thermalController;

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

    analogWrite(pwmPin, pwmValue);
      
    // 转速计算和打印周期（1s）
    if (currentTime - lastTime >= 1000) {
        rpm = (pulseCount / 2.0) * 60.0;
        fanRPMFilter.addValue(rpm);
        pulseCount = 0;
         // 温度读取和滤波
        tempFilter.addValue(readTemp());
        float currentTemp = tempFilter.getAverage();
         // 计算PWM值并约束范围
         pwmValue = thermalController.computePWM(currentTemp);
         pwmValue = constrain(pwmValue, 0, 255);
         analogWrite(pwmPin, pwmValue);

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
