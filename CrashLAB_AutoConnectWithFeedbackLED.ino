#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

#include <ESP8266mDNS.h>
#include <WiFiUdp.h>


const char* apssid = "CrashLAB WeMos D1";
const char* password = "espconfig";
const char* host = "crashlab-wemos-d1";


//for LED status
#include <Ticker.h>
Ticker ticker;

void tick()
{
  //toggle state
  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.2, tick);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //set led pin as output
  pinMode(BUILTIN_LED, OUTPUT);
  // start ticker with 0.5 because we start in AP mode and try to connect
  ticker.attach(0.5, tick);

  wifi_station_set_hostname((char *)host);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset settings - for testing
  //wifiManager.resetSettings();

  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //and goes into a blocking loop awaiting configuration
  //if (!wifiManager.autoConnect()) {
  if (!wifiManager.autoConnect(apssid, password)) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  ticker.detach();


  // MDNS responder
  if (MDNS.begin(host)) {
    Serial.println("MDNS responder started");
  }

}

void loop() {

  // put your main code here, to run repeatedly:
  digitalWrite(BUILTIN_LED, HIGH);
  delay(800);
  digitalWrite(BUILTIN_LED, LOW);
  delay(85);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(85);
  digitalWrite(BUILTIN_LED, LOW);
  delay(85);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(85);
  digitalWrite(BUILTIN_LED, LOW);
  delay(85);
  digitalWrite(BUILTIN_LED, HIGH);
  delay(85);
  digitalWrite(BUILTIN_LED, LOW);
  delay(85);

}
