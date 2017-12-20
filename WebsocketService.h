#ifndef _WEBSOCKETSERVICE_H_
#define _WEBSOCKETSERVICE_H_

#include "JsonDataInterface.h"
#include "ArduinoJson.h"
#include "JsonEventInterface.h"
#include "RFIDService.h"

class WebsocketService : public JsonEventInterface
{
public:
    WebsocketService(JsonDataInterface& dataif);
    void OnServerHello(const JsonObject& args);

    void Reset();
    void Update();

private:
    RFIDService _rfidService;
};

#endif
