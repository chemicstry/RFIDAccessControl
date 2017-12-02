#ifndef _EVENTEMITTER_H_
#define _EVENTEMITTER_H_

#include <map>
#include <vector>
#include <string>
#include <functional>

template<typename T>
class EventEmitter
{
public:
    typedef std::function<void(T&)> EventCb;

    void On(std::string name, EventCb listener)
    {
        _events[name].push_back(listener);
    }

    void Emit(std::string name, T& data)
    {
        auto event = _events.find(name);

        if (event != _events.end())
        {
            // Fire all callbacks
            for (EventCb& cb : event->second)
                cb(data);
        }
    }

private:
    std::map<std::string, std::vector<EventCb>> _events;
};

#endif
