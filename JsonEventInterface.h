#ifndef _JSONEVENTINTERFACE_H_
#define _JSONEVENTINTERFACE_H_

#include "JsonEventEmitter.h"
#include "JsonDataInterface.h"

class JsonEventInterface : public JsonEventEmitter
{
public:
    JsonEventInterface(JsonDataInterface& dataif);
    void Send(std::string name, JsonObject& args);

private:
    void _OnReceiveData(JsonObject& data);
    JsonDataInterface& _dataif;
};

#endif
