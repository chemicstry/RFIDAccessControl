#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "JsonDataInterface.h"
#include "JsonEventEmitter.h"

// To prevent include loop
class ServiceManager;

class Service
{
public:
    Service(ServiceManager& mgr);

private:
    void _OnDownstreamData(JsonObject& data);

    JsonBidirectionalDataInterface _dataif;
    JsonEventEmitter evt;
    ServiceManager& _mgr;
};

#endif
