#include <WiFi.h>
#include <WiFiMulti.h>

#include "src/arduinoWebSockets/WebSocketsClient.h"

#include "ServiceManager.h"

JsonBidirectionalDataInterface jif;
ServiceManager svcMgr(jif.Downstream);

WiFiMulti wifiMulti;
WebSocketsClient webSocket;

char buf[200];


#define USE_SERIAL Serial

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {


    switch(type) {
        case WStype_DISCONNECTED:
            USE_SERIAL.printf("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED:
            {
                USE_SERIAL.printf("[WSc] Connected to url: %s\n",  payload);
            }
            break;
        case WStype_TEXT:
        {
            USE_SERIAL.printf("[WSc] get text: %s\n", payload);
            StaticJsonBuffer<512> jsonBuffer;
            JsonObject& root = jsonBuffer.parseObject(payload);
            jif.Upstream.Send(root);
            break;
        }
        case WStype_BIN:
            USE_SERIAL.printf("[WSc] get binary length: %u\n", length);

            // send data to server
            // webSocket.sendBIN(payload, length);
            break;
    }

}

void setup() {
    // USE_SERIAL.begin(921600);
    USE_SERIAL.begin(115200);

    //Serial.setDebugOutput(true);
    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }

    wifiMulti.addAP("TuRgElIs", "TREX600NPRO");

    //WiFi.disconnect();
    while(wifiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    //webSocket.beginSSL("192.168.1.175", 8080);
    webSocket.begin("192.168.1.175", 8080);
    webSocket.onEvent(webSocketEvent);

jif.Upstream.SetCb([](JsonObject& data) {
  data.printTo(buf);
  webSocket.sendTXT(buf);
});
}

void loop() {
    webSocket.loop();
}
