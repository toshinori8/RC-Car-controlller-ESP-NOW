
// 9C:1F:46:63:3B  MAC ADRESS OF this device
#include <ESP8266WiFi.h>
#include <AnalogSmooth.h>


//#include <WiFiClient.h>
//#include <ESPAsyncWebServer.h>
//#include <ESP8266mDNS.h>
//#include <ESPAsyncTCP.h>
uint8_t reciverMac[] = { 0xCC, 0x50, 0xE3, 0x56, 0xB7, 0x36 };

AnalogSmooth smoothTurn = AnalogSmooth(6);
AnalogSmooth smoothDrive = AnalogSmooth(10);


//#include <WiFiUdp.h>
//#include <ArduinoOTA.h>
#include <espnow.h>

/////// OLED DISPLAY
//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
//#define SCREEN_WIDTH 128
//#define SCREEN_HEIGHT 32
//#define OLED_RESET -1
//#define SCREEN_ADDRESS 0x3C
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//



#include <Timers.h>

#include <Servo.h>

Servo myservo;

// These are the pins used to control the motor shield
#define DRIVE_MOTOR_POWER D2      //  D2 nodeMCU D2
#define DRIVE_MOTOR_DIRECTION D4  // D4 nodeMCU
//#define STEER_MOTOR_POWER D1 // Motor A   gpio 5
//#define STEER_MOTOR_DIRECTION D3 // gpio0

// ANALOG INPUT
const int pot = 0;

const char minAngle = 0;
const char maxAngle = 100;




///// .  ESP NOW
typedef struct dataStruct {

  /// CAR STERING DATA

  int pot;
  int drive;
  int ster;
  String dirDrive;
  String dirSter;

  /// CAR OPTIONS

  bool short_lights;
  bool long_lights;
  bool haloo_lights;
  bool autoOff_lights;
  bool turn_lights;
  bool alarm_lights;
  bool error_lights;



} dataStruct;
dataStruct dataBeam;

void OnDataRecv(uint8_t* mac, uint8_t* incomingData, uint8_t len) {
  int curR;
  int curL;

  memcpy(&dataBeam, incomingData, sizeof(dataBeam));

  //Serial.println("RECIVIG DATA ON ESP_NOW");

  //  Serial.print("Ster: ");
  // Serial.println(dataBeam.pot);
  //  Serial.print("Drive: ");
  //  Serial.println(dataBeam.drive);
  // Serial.print("Ster: ");
  //  Serial.println(dataBeam.dirSter);
  //  Serial.print("Drive: ");
  // Serial.println(dataBeam.dirDrive);


  if (dataBeam.dirDrive == "^") {
    digitalWrite(DRIVE_MOTOR_DIRECTION, LOW);
    turnLightFW(1);
  }
  if (dataBeam.dirDrive == "V") {
    digitalWrite(DRIVE_MOTOR_DIRECTION, HIGH);
    turnLightFW(2);
  }
  analogWrite(DRIVE_MOTOR_POWER, smoothDrive.smooth(dataBeam.drive) * 10);
  //int servos = map(dataBeam.pot, 754,427, 75, 106 );




  int servos = map(smoothTurn.smooth(dataBeam.pot), 754, 427, 0, 180);

  //servos=servos*180.0/1023;

   Serial.println(dataBeam.dirDrive);

  if (servos > 70) {
    turnLightLeft();
  } else if (servos < 110) {
    turnLightRight();
  }

  myservo.write(servos);
}







//AsyncWebServer server(80);

String wifiMacString;


//void otaStart();





// drivePower sets how fast the car goes
// Can be set between 0 and 1023 (although car problaly wont move if values are too low)
// int drivePower = 1023;

// uint8_t driveDirection = HIGH;

// int steeringPower = 1023;

// uint8_t steerDirection = HIGH;

const char* ssid = "oooooio";
const char* password = "pmgana921";

const char* PARAM_INPUT_1 = "ajaxDrive";
const char* PARAM_INPUT_2 = "ajaxSter";
String inputMessage1;
String inputMessage2;
//#include "motorPage.h"
//String processor(const String& var)
//{
//  if(var == "MAC_ADDR")
//    return wifiMacString();
//}





//
//
//void notFound(AsyncWebServerRequest *request) {
//  request->send(404, "text/plain", "Not found");
//}
//



//
//void displayData(void) {
//  display.clearDisplay();
//  display.setTextSize(1);
//  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
//  display.setCrsor(0,10);
//  display.println(PARAM_INPUT_1);
//
//  display.setTextColor(SSD1306_WHITE);
//  display.setCursor(0,20);
//  display.println(inputMessage1);
//
//  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
//  display.setCursor(50, 10);
//  display.print(PARAM_INPUT_2);
//  display.setCursor(50, 10);
//  display.setTextColor(SSD1306_WHITE);
//  display.print(inputMessage2);
//
//
//  display.display();
//
//
//
//
//
//
//
//}


void initESP_NOW();



void setup(void) {
  Serial.begin(115200);
  delay(1000);
  //analogWrite(15, 1023);
  myservo.attach(5);  // digital PIN D1 on nodeMCU /

  delay(200);
  //myservo.write(90);


  delay(200);
 // myservo.write(0);

  delay(200);

  digitalWrite(LED_BUILTIN, LOW);


  myservo.write(180);

  //Wire.begin(D5, D6);

  pinMode(DRIVE_MOTOR_POWER, OUTPUT);
  pinMode(DRIVE_MOTOR_DIRECTION, OUTPUT);
  // pinMode(STEER_MOTOR_POWER, OUTPUT);
  //STEER_MOTOR_DIRECTION  pinMode(STEER_MOTOR_DIRECTION, OUTPUT);

  //analogWrite(STEER_MOTOR_POWER, 0);
  analogWrite(DRIVE_MOTOR_POWER, 0);




  /////////////////////////////////////     OLED DISOPLAY


  //
  //   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  //    Serial.println(F("SSD1306 allocation failed"));
  //    for(;;); // Don't proceed, loop forever
  //    }
  //

  // displayData();
  /////////////////////////////////////     OLED DISOPLAY


 initI2Cbus(); 


  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);


  //  WiFi.begin(ssid, password);


  initESP_NOW();

  // Wait for connection
  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(200);
  //    Serial.print(".");
  //  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  wifiMacString = WiFi.macAddress();
  Serial.print('MAC ADDRES :: ');
  Serial.println(wifiMacString);
  //  if (MDNS.begin("Rancho")) {
  //
  //    Serial.println("MDNS Responder Started");
  //      //server.begin();
  //      //u8g2.begin();
  //  }
  //otaStart();



  //server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  // request->send_P(200, "text/html", webpage, processor);
  //});

  // server.on("/ajaxSter", [](AsyncWebServerRequest *request){



  //  if (request->hasParam(PARAM_INPUT_2)) {
  //     inputMessage2 = request->getParam(PARAM_INPUT_2)->value();

  //  }
  //Serial.println(PARAM_INPUT_2);
  // Serial.println(inputMessage2);

  // displayData();
  // request->send_P(200, "text/html", "ajaxSterOK");


  // });


  // server.on("/ajaxDrive", [](AsyncWebServerRequest *request){



  // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
  //if (request->hasParam(PARAM_INPUT_1)) {
  // inputMessage1 = request->getParam(PARAM_INPUT_1)->value();


  //Serial.println(PARAM_INPUT_1);
  //Serial.println(inputMessage1);


  // displayData();

  // }

  //  request->send_P(200, "text/html", "ajaxOK");


  // });


  //  server.on("/right", [](AsyncWebServerRequest *request){
  //    Serial.println("right");
  //    analogWrite(STEER_MOTOR_POWER, steeringPower);
  //    digitalWrite(STEER_MOTOR_DIRECTION, steerDirection);
  //    request->send_P(200, "text/html", "right");
  //  });


  //   server.onNotFound(notFound);


  //  Serial.println("HTTP Server Started");
}



void loop(void) {
  //ArduinoOTA.handle();
}
