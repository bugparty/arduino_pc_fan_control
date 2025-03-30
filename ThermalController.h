#ifndef THERMALCONTROLLER_H
#define THERMALCONTROLLER_H

/*
// Quiet mode configuration
ThermalController quietMode(
  35.0,   // Keep minimum speed below 40°C
  45.0,   // Start accelerating at 45°C
  55.0,   // Full speed at 55°C
  30,     // Minimum 30% duty cycle
  150,    // Mid-range 150
  200     // Maximum not exceeding 200
);

// Performance mode configuration
ThermalController performanceMode(
  30.0,   // Start accelerating at 30°C
  40.0,   // Enter mid-range at 40°C
  50.0,   // Full speed at 50°C
  80,     // Minimum 80 duty cycle
  180,    // Mid-range 180
  255     // Full speed
);
*/
class ThermalController {
private:
    // Temperature threshold configuration
    float minComfortTemp = 35.0;  // Minimum speed temperature threshold
    float midThreshold = 40.0;    // Mid-range temperature start
    float maxThreshold = 50.0;    // Full speed temperature threshold
    
    // PWM configuration
    uint8_t minDuty = 50;         // Minimum speed duty cycle
    uint8_t midDuty = 87;         // Mid-range duty cycle
    uint8_t maxDuty = 255;        // Full speed duty cycle

public:
    // Optional constructor for custom parameters
    ThermalController() = default;  // Use built-in parameters by default
    
    ThermalController(float t1, float t2, float t3, 
                     uint8_t d1, uint8_t d2, uint8_t d3) :
        minComfortTemp(t1),
        midThreshold(t2),
        maxThreshold(t3),
        minDuty(d1),
        midDuty(d2),
        maxDuty(d3) {}

    int computePWM(float temperature) {
        temperature = constrain(temperature, 0, 100);
        
        if (temperature <= minComfortTemp) {
            return minDuty;
        } 
        else if (temperature <= midThreshold) {
            // Calculate linear transition between 35-40°C
            return minDuty + (temperature - minComfortTemp) * 
                   (midDuty - minDuty) / (midThreshold - minComfortTemp);
        } 
        else if (temperature <= maxThreshold) {
            // Calculate linear transition between 40-50°C
            return midDuty + (temperature - midThreshold) * 
                   (maxDuty - midDuty) / (maxThreshold - midThreshold);
        } 
        else {
            return maxDuty;
        }
    }

    // Optional parameter setting methods
    void setThresholds(float t1, float t2, float t3) {
        minComfortTemp = t1;
        midThreshold = t2;
        maxThreshold = t3;
    }

    void setDutyCycles(uint8_t d1, uint8_t d2, uint8_t d3) {
        minDuty = constrain(d1, 0, 255);
        midDuty = constrain(d2, minDuty, 255);
        maxDuty = constrain(d3, midDuty, 255);
    }
};

#endif
