#include <DHT.h>
#include <DHT_U.h>

#include <SoftwareSerial.h>

// Define software serial pins
SoftwareSerial BTSerial(10, 11); // RX, TX

// Define DHT sensor pin
#define DHTPIN 2

// Define DHT sensor type
#define DHTTYPE DHT11

// Initialize DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }

  // Initialize software serial communication with Bluetooth module
  BTSerial.begin(9600);

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Read temperature and humidity from DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Send temperature and humidity to Bluetooth module
  BTSerial.print("Temperature: ");
  BTSerial.print(temperature);
  BTSerial.print(" °C\t");
  BTSerial.print("Humidity: ");
  BTSerial.print(humidity);
  BTSerial.println(" %");

  // Wait a short period before sending the next reading
  delay(1000);
}
