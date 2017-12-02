#include "ServiceManager.h"
#include "Arduino.h"

using namespace std::placeholders;

ServiceManager::ServiceManager(JsonDataInterface& dataif): _evtif(dataif), _serviceIdItr(0)
{
    _evtif.On("hello", std::bind(&ServiceManager::OnServerHello, this, _1));
}

void ServiceManager::OnServerHello(JsonObject& data)
{
    Serial.println("Server hello!");

    StaticJsonBuffer<200> jsonBuffer;

    JsonObject& object = jsonBuffer.createObject();
    object["hello"] = "world";
    _evtif.Send("test", object);
}

void ServiceManager::_RegisterService(Service* svc)
{
    uint32_t serviceId = _serviceIdItr++;

    _services.emplace(serviceId, svc);


}