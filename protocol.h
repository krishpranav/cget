/**
 * @file protocol.h
 * @author Krisna Pranav
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021 Apache-2.0
 * 
 */

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
        
        virtual const Port GetPort() const = 0;
        virtual void SetPort(const Port& port) = 0;
        
        virtual void SendRequest(const Path& path) const = 0;
        virtual void ProcessResponse(std::ofstream& out_stream) const = 0;
        
        virtual ~Protocol() {};
    };
}