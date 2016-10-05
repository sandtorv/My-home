// This #include statement was automatically added by the Particle IDE.
#include "CE_BME280/CE_BME280.h"

// This #include statement was automatically added by the Particle IDE.
#include "DS18B20/DS18B20.h"

// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_SSD1306/Adafruit_SSD1306.h"

// Setup screen
#define OLED_RESET D4
Adafruit_SSD1306 oled(OLED_RESET);

// Setup temp
DS18B20 ds18b20 = DS18B20(D2);

CE_BME280 bme;

double temp = 0;
double lastTemp = 0;
double baro = 0;
double lastBaro = 0;
double humid = 0;
double lastHumid = 0;
String objToSend;

bool dataChanged = false;

int counter = 0;
int dsAttempts = 0;

void setup() {
    // Start screen
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    getTemp();
    updateScreen();
    // Setup variables
    Particle.variable("temp", temp);
    Particle.variable("baro", baro);
    Particle.variable("humid", humid);
    Particle.variable("object", objToSend);
    
    if (!bme.begin()) {
        Particle.publish("Error", "Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
}

void loop() {
    getTemp();
    updateScreen();
    // Global delay
    delay(2500);
}

void updateScreen(){
    oled.clearDisplay();
    oled.setTextSize(0);
    oled.setTextColor(WHITE);
    oled.setCursor(0,0);
    oled.print("Temp ");
    oled.setTextSize(3);
    oled.print(String(temp, 1));
    oled.setTextSize(0);
    oled.print("o");
    oled.setTextSize(2);
    oled.print("C\n");
    oled.setTextSize(0);
    oled.print("Humi ");
    oled.setTextSize(2);
    oled.print(String(humid,1));
    oled.print("%\n");
    oled.setTextSize(0);
    oled.print("Baro ");
    oled.setTextSize(2);
    oled.print(String(baro, 1));
    oled.setTextSize(0);
    oled.print("hPa");
    oled.display();
}

void getTemp(){
    temp = bme.readTemperature()-3.8; // Calibration hack
    if(temp != lastTemp){
        lastTemp = temp;
        dataChanged = true;
    }

    baro = bme.readPressure() / 100.0F;
    if(baro != lastBaro){
        lastBaro = baro;
        dataChanged = true;
    }
    
    humid = bme.readHumidity();
    if(humid != lastHumid){
        lastHumid = humid;
        dataChanged = true;
    }
    
    objToSend = "{ \"temp\": \" " + String(temp, 2) + "\", \"humid\": \"" + String(humid, 2) +"\", \"baro\": \"" + String(baro, 2) +  "\" }";

    if(dataChanged){
        Particle.publish("object", objToSend);
        dataChanged = false;
    }
}