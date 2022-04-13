// Basic demo for readings from Adafruit SCD30 

// Refer to https://learn.adafruit.com/adafruit-scd30/arduino for additional info 
// Demo below is also from above link

/*  This code only uses one SCD-30 sensor and has the Adafruit DEMO
 *   as well as an excel data transfer demo for one sensor*/
#include <Adafruit_SCD30.h>

// setup scd-30 object
Adafruit_SCD30  scd30;

// sda -> nano pin 4
// scl -> nano pin 5

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // pause until serial monitor is open

//  Serial.println("Adafruit SCD30 test!");

  // Try to initialize! Continue until SCD-30 chip is found
  if (!scd30.begin()) {
    Serial.println("Failed to find SCD30 chip");
    while (1) { delay(10); }
  }
  Serial.println("SCD30 Found!");
  
}

void loop() {
  if (scd30.dataReady()){
    Serial.println("Data available!");

    if (!scd30.read()){ Serial.println("Error reading sensor data"); return; }

    // **
    Serial.print("Temperature: ");
    Serial.print(scd30.temperature);
    Serial.println(" degrees C");
    
    Serial.print("Relative Humidity: ");
    Serial.print(scd30.relative_humidity);
    Serial.println(" %");


//  print full infromation to serial monitor
    Serial.print("CO2: ");
    Serial.print(scd30.CO2, 3);
    Serial.println(" ppm");
    Serial.println("");

    /* If you want to do excel streaming, leave the below Serial print command and 
     * comment out everything above this line up to the ** mark. Otherwise, leave commented
     */
    // print just co2 data
//    Serial.println(scd30.CO2, 3);
    
  } else {
    Serial.println("No data");
  }

  // 6 second delay (10 data points per minute)
  delay(6000);
}
