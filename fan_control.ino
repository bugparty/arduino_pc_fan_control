#include "MeanFilter.h"
MeanFilter fanRPMFilter(10); // 创建一个窗口大小为10的滤波器
// 定义控制风扇PWM信号的引脚
const int pwmPin = 5;  // PWM控制引脚，连接到风扇的PWM控制引脚
// 定义测速信号引脚
const int tachPin = 2;  // Tachometer引脚，连接到风扇的转速反馈引脚
const int thermistorPin= 23; //A1
volatile unsigned long pulseCount = 0;  // 用于计数脉冲的变量
unsigned long lastTime = 0;  // 记录上次计时的变量
float rpm = 0;  // 存储转速（转每分钟）
float readTemp(){

int tempReading = analogRead(thermistorPin);

double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));

tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );

float tempC = tempK - 273.15;

//float tempF = (tempC * 9.0)/ 5.0 + 32.0;

return tempC;

}
void setup() {
  pinMode(pwmPin, OUTPUT);  // 设置PWM引脚为输出
  pinMode(tachPin, INPUT);  // 设置Tachometer引脚为输入
  attachInterrupt(digitalPinToInterrupt(tachPin), countPulse, FALLING);  // 当Tachometer引脚发生下降沿时调用countPulse()
  Serial.begin(9600);  // 初始化串口，波特率为9600
}
void loop() {
  // 设置PWM信号的占空比，控制风扇的转速（0-255，0为停止，255为最大转速）
  int pwmValue = 100;  // 设置PWM占空比为128，表示中等转速
  analogWrite(pwmPin, pwmValue);  // 输出PWM信号到风扇

  // 每秒钟计算一次转速（RPM）
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= 1000) {
    rpm = (pulseCount / 2.0) * 60.0;  // 计算转速：每两个脉冲代表一圈，乘以60得到转每分钟（RPM）
    fanRPMFilter.addValue(rpm);
    pulseCount = 0;  // 重置脉冲计数
    lastTime = currentTime;  // 更新上次计时
    Serial.print(readTemp());
    Serial.print(" , ");
    Serial.println(fanRPMFilter);  // 打印转速
    

  }
}

// 计数脉冲，每当Tachometer引脚发生下降沿时被调用
void countPulse() {
  pulseCount++;  // 每次脉冲计数器加1
}
