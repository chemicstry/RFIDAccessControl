#ifndef _SERVICEMANAGER_H_
#define _SERVICEMANAGER_H_

#include "JsonDataInterface.h"
#include "ArduinoJson.h"
#include "JsonEventInterface.h"
#include "Service.h"

class ServiceManager
{
public:
    ServiceManager(JsonDataInterface& dataif);
    void OnServerHello(JsonObject& data);

private:
    void _RegisterService(Service* svc);

    JsonEventInterface _evtif;

    uint32_t _serviceIdItr;
    std::map<uint32_t, Service*> _services;

    friend Service;
};

#endif
