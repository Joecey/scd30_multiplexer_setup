/* Arduino code used to send data from three SCD-30 sensors to Excel
 * With the particular multiplexer i used before (tca9548a), you should be able to have 
 * up to 8 sensors controlled by the one arduino nano (refer to arduino NANO pin guide attached in 
 * github OR online for board you are using when plugging in SDA and SCL pins)
 */

// import packages used for I2C communication and SCD-30 sensing
#include <Wire.h>
#include <Adafruit_SCD30.h>

// create co2 sensor objects (Create one for each sensor connected to arduino)
Adafruit_SCD30  scd30; 
Adafruit_SCD30  scd30_2; 
Adafruit_SCD30  scd30_3; 

// global variables for co2 levels
float co2_level1, co2_level2, co2_level3;

// Select I2C BUS function --> used to select respective bus on multiplexer 
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

/* initilaise serial monitoring --> program won't start unless serial monitor in arduino
or data streaming in excel starts */

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // pause code until Serial monitor is open

// Start I2C communication with the Multiplexer and co2 sensors and intialise
  TCA9548A(2);
  scd30.begin(0x61, &Wire);

  TCA9548A(3);
  scd30_2.begin(0x61, &Wire);

  TCA9548A(4);
  scd30_3.begin(0x61, &Wire);
  
}

void loop() {
  // switch to 1st co2 bus (in my case, bus 2 on multiplexer) and record co2 data
  // for each co2 sensor, go to respective multiplex bus --> get co2 readings
  
  TCA9548A(2);
  // if data is available, retrieve data from co2 sensor
  if (scd30.dataReady()){
    scd30.read();

    // store co2 reading in global variable
    co2_level1 = scd30.CO2;
  
  } else{
  }

  /// REPEAT ABOVE FOR THE OTHER TWO SENSORS ///

  TCA9548A(3);
  // print just co2 data
  if (scd30_2.dataReady()){
    scd30_2.read();
    co2_level2 = scd30_2.CO2;
    
  } else{
  }

  TCA9548A(4);
  // print just co2 data
  if (scd30_3.dataReady()){
    scd30_3.read();
    co2_level3 = scd30_3.CO2;
    
  } else{
  }

  // print recorded values 
  // Have to be laid out in <value>, <value>, <value> etc... layout for excel data streaming
  Serial.print(co2_level1);
  Serial.print(", ");
  Serial.print(co2_level2);
  Serial.print(", ");
  Serial.println(co2_level3);

  // set delay of 3 seconds (in one minute, 20 readings total)
  delay(3000);
}
