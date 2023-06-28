#include <Adafruit_VL53L0X.h>

#define LOX1_ADDRESS 0x30

#define LOX2_ADDRESS 0x31

// set the pins to shutdown
#define SHT_LOX1 30
#define SHT_LOX2 31

class LRF {
    public:
        LRF();
        void read_dual_sensors();
        void setID();
        void setup();

    private:
        Adafruit_VL53L0X lox1;
        Adafruit_VL53L0X lox2;
        VL53L0X_RangingMeasurementData_t measure1;
        VL53L0X_RangingMeasurementData_t measure2;
            
};