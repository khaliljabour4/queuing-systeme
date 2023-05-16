#include<Wire.h>
#include <WiFiClient.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <StreamString.h>
#include <AsyncJson.h>
#include <ArduinoJson.h>
#include <ESPAsyncWiFiManager.h>
#include <LiquidCrystal.h>
#include "WQueue.h"
#include "screen.h"
#include "counter.h"

const int rs = D6, en = D5, d4 = D4, d5 = D3, d6 = D2, d7 = D1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const char* ssid = "NodeMCU";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

const char* http_username = "admin";
const char* http_password = "admin";

AsyncWebServer server(80);
DNSServer dns;

AsyncEventSource events("/events");

String title = "";
String subtitle = "";

const int led = 13;

const char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
WQueue* q = new WQueue("main");

void setup() {
  lcd.begin(16, 2);
  lcd.print("Now Serving :");
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.mode(WIFI_AP_STA);
  IPAddress myIP = WiFi.softAPIP(); // 192.168.4.1 default IP for esp....
  Serial.print("Access Point IP: ");
  Serial.println(myIP);
  // 192.168.4.1 default IP for esp....
  Serial.print("Access Point IP: ");
  Serial.println(myIP);
  WiFi.begin("TP-Link_0C74","79054768");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
   if (MDNS.begin("queue")) { Serial.println("MDNS responder started"); }

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", R"HTML(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Welcome</title>
    <style>
    p{
      font-family: Georgia, 'Times New Roman', Times, serif;
      font-weight: bold;
      color:dodgerblue;
      font-size: 36px;
      text-align: center;
      margin-bottom:50px;
    }
    #ttl{
        text-decoration-line: underline;
    }
    label{
      font-size:24px;
      color: #000;
      }
    input{
      margin-bottom: 30px; 
      border: 1px solid black; 
      border-radius: 20px;   
      width: 60%;   
      height: 35px;
      font-size: 18px;
      text-align: center;
      box-shadow: 2px 2px 6px 2px rgba(82,74,74,1);
      -webkit-box-shadow: 2px 2px 6px 2px rgba(82,74,74,1);
      -moz-box-shadow: 2px 2px 6px 2px rgba(82,74,74,1);
    }
    #firstname{
        margin-bottom: 10px;
    }
    select{
      margin-bottom: 50px;
      width:60%;
      height:40px;
      border-radius:20px;
      border: 1px solid black;
      box-shadow: 2px 2px 6px 2px rgba(82,74,74,1);
      -webkit-box-shadow: 2px 2px 6px 2px rgba(82,74,74,1);
      -moz-box-shadow: 2px 2px 6px 2px rgba(82,74,74,1);
      text-align: center;
    }
    button{
        height: 40px;
        width: 100px;
        border: 2px solid #000;
        background-color: #FFF;
        border-radius: 20px;
        font-size: 18px;
        font-weight: bold;
    } 
    button:hover{
        background-color: dodgerblue;
        color: #FFF;
    }
    option{
    }
    </style>
  </head>
  <body>
    <p id="ttl">Take a Ticket<p>
    <label for="name">First name:</label><br>
    <input type="text" id="firstname" name="name" /><br>
    <label for="name">Last name:</label><br>
    <input type="text" id="lastname" name="name" /><br>
    <label for="counter">Counter:</label><br>
    <select id="counter" name="counter">
      <option >choose a guishet</option>
      <option value="0">Guishet 1</option>
      <option value="1">Guishet 2</option>
      <option value="2">Guishet 3</option>
      <option value="3">Guishet 4</option>
      <option value="4">Guishet 5</option>
      <option value="5">Guishet 6</option>
      <option value="6">Guishet 7</option>
      <option value="7">Guishet 8</option>
      <option value="8">Guishet 9</option>
      <option value="9">Guishet 10</option>
      <option value="10">Guishet 11</option>
      <option value="11">Guishet 12</option>
      <option value="12">Guishet 13</option>
      <option value="13">Guishet 14</option>
      <option value="14">Guishet 15</option>
      <option value="15">Guishet 16</option>
    </select><br>  
    <button type="submit" id="submit">Submit</button>
    <div></div>
    <script>
      document.getElementById("submit").addEventListener("click", () => {
        const fname = document.getElementById("firstname").value;
        const lname = document.getElementById("lastname").value;
        const value = counter.value;
        fetch("/api/push", {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify({
            counter: value,
          })
        }).then((res) => res.text()).then((data) => {
          alert(data);
          //location.href = "https://queue.surge.sh/ticket?id=" + data + "&fname=" + fname + "&lname=" + lname + "&counter=" + value;
        }).catch(()=>{
          alert("Error!")
        })
      })
    </script>
  </body>
</html>
)HTML");
  });

  server.on("/screen", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", screen_html);
  });

  server.on("/counter", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", counter_html);
  });

  AsyncCallbackJsonWebHandler* handler_next = new AsyncCallbackJsonWebHandler("/api/next", [](AsyncWebServerRequest *request, JsonVariant &json) {
    if(request->method() == HTTP_POST){
      JsonObject jsonObj = json.as<JsonObject>();
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument doc(1024);
      int id = jsonObj["id"];
      int next = q->next(id);
      int qid = q->getQueue(id);
      doc["remaining"] = q->remaining(id);
      doc["current"] = q->getCurrent(id);
      StreamString temp;
      temp.reserve(20);
      temp.printf("%c",letters[qid]);
      doc["queue"] = temp.c_str();
      serializeJson(doc, *response);
      request->send(response);
      if(next >= 0) {
        temp.clear();
        temp.printf("%d %c%d",id+1,letters[qid],next);
        events.send(temp.c_str(),"queue");
        if(id == 0){
        temp.clear();
        temp.printf("%c%03d",letters[qid],next);
        lcd.setCursor(0, 1);
        lcd.print(temp.c_str());
        }
      }
      temp.clear();
    }
  });

  server.addHandler(handler_next);
  AsyncCallbackJsonWebHandler* handler_push = new AsyncCallbackJsonWebHandler("/api/push", [](AsyncWebServerRequest *request, JsonVariant &json) {
    if(request->method() == HTTP_POST){
      JsonObject jsonObj = json.as<JsonObject>();
      int c = jsonObj["counter"];
      int num = q->push(c);
      if (num >= 0) {
        StreamString temp;
        temp.reserve(20);
        temp.printf("%c%03d",letters[c],num);
        request->send(200,"text/plain",temp.c_str());
      } else {
        request->send(500,"text/plain","Queue full");
      }
    }
  });

  server.addHandler(handler_push);
  server.on("/api/counter", HTTP_GET, [](AsyncWebServerRequest *request){
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();
    int len = q->getLast();
    StreamString temp;
    temp.reserve(20);
    for (int i = 0; i < len; i++) {
      temp.printf("%c%d",letters[q->getQueue(i)],q->getCurrent(i));
      array.add(temp.c_str());
      temp.clear();
    }
    serializeJson(doc, *response);
    request->send(response);
    temp.clear();
  });

  AsyncCallbackJsonWebHandler* handler_news = new AsyncCallbackJsonWebHandler("/api/news", [](AsyncWebServerRequest *request, JsonVariant &json) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonDocument doc(1024);
    if(request->method() == HTTP_POST){
      JsonObject jsonObj = json.as<JsonObject>();
      title = jsonObj["title"].as<String>();
      subtitle = jsonObj["subtitle"].as<String>();
      doc["title"] = title;
      doc["subtitle"] = subtitle;
      serializeJson(doc, *response);
      request->send(response);
      String output;
      serializeJson(doc, output);
      events.send(output.c_str(),"news");
    }
  });

  server.addHandler(handler_news);
  server.on("/api/news", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonDocument doc(1024);
    doc["title"] = title;
    doc["subtitle"] = subtitle;
    serializeJson(doc, *response);
    request->send(response);
  });

  server.on("/api/stat", [](AsyncWebServerRequest *request) {
    if(request->hasParam("id")){
      AsyncWebParameter* p = request->getParam("id");
      int id = p->value().toInt();
      int qid = q->getQueue(id);
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument doc(1024);
      doc["remaining"] = q->remaining(id);
      doc["current"] = q->getCurrent(id);
      StreamString temp;
      temp.reserve(20);
      temp.printf("%c",letters[qid]);
      doc["queue"] = temp.c_str();
      serializeJson(doc, *response);
      request->send(response);
      temp.clear();
    }
  });

  AsyncCallbackJsonWebHandler* handler_event = new AsyncCallbackJsonWebHandler("/api/event", [](AsyncWebServerRequest *request, JsonVariant &json) {
    if(request->method() == HTTP_POST){
      JsonObject jsonObj = json.as<JsonObject>();
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      events.send(jsonObj["data"],jsonObj["event"],jsonObj["id"],jsonObj["reconnect"]);
      serializeJson(jsonObj, *response);
      request->send(response);
    }
  });

  server.addHandler(handler_event);
  AsyncCallbackJsonWebHandler* handler_setup = new AsyncCallbackJsonWebHandler("/api/setup", [](AsyncWebServerRequest *request, JsonVariant &json) {
    if(request->method() == HTTP_POST){
      JsonArray jsonArray = json.as<JsonArray>();
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      for (size_t i = 0; i < jsonArray.size(); i++) {
        q->setQueue(i,jsonArray[i].as<int>());
      }
      if (q->flush()) {
          serializeJson(jsonArray, *response);
      }
      request->send(response);
    }
  });

  server.addHandler(handler_setup);
  server.on("/api/setup", HTTP_GET, [](AsyncWebServerRequest *request) {
    AsyncResponseStream *response = request->beginResponseStream("application/json");
    DynamicJsonDocument doc(1024);
    JsonArray array = doc.to<JsonArray>();
    for (size_t i = 0; i < 16; i++) {
      array.add(q->getQueue(i));
    }
    serializeJson(doc, *response);
    request->send(response);
  });

  server.addHandler(&events);
  server.begin();
  Serial.println("HTTP server started");
  }

void loop() {
  MDNS.update();
  //lcd.setCursor(0, 1);
  //lcd.print(millis() / 1000);
  }
