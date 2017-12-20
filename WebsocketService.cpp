#include "WebsocketService.h"
#include "Arduino.h"

using namespace std::placeholders;

WebsocketService::WebsocketService(JsonDataInterface& dataif): JsonEventInterface(dataif), _rfidService(*this)
{
    On("hello", std::bind(&WebsocketService::OnServerHello, this, _1));
}

void WebsocketService::OnServerHello(const JsonObject& data)
{
    Serial.println("Server hello!");

    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& args = jsonBuffer.createObject();
    args["hello"] = "world";
    Send("hello", args);
}

void WebsocketService::Reset()
{
}

void WebsocketService::Update()
{
    _rfidService.Update();
}
