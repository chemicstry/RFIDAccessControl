#include "Service.h"
#include "ServiceManager.h"

Service::Service(ServiceManager& mgr): _mgr(mgr)
{
    _mgr._RegisterService(this);
}