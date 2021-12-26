#pragma once

#include <string>

namespace Network {
    class Protocol {
    public:
        using Host = std::string;
        using Path = std::string;
        using Port = int;

        virtual const Host GetHost() const = 0;
        virtual void SetHost(const Host& host) = 0;
    };
}