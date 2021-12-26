/**
 * @file httpprotocol.hpp
 * @author Krisna Pranav
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021 Apache-2.0
 * 
 */

#pragma once

#include "protocol.h"
#include "tcpsocket.hpp"
#include <regex>
#include <string>
#include <fstream>

namespace Network {
    class HttpProtcol : public Protocol {
    public:
        using Domain = Protocol::Host;
        using Path = std::string;

        HttpProtcol();
        ~HttpProtcol() = default;

        const Host GetHost() const override;
        void SetHost(const Host& host) override;

        const Port GetPort() const override;
        void SetPort(const Port& port) override;

        void SendRequest(const Path& path) const override;
        void ProcessResponse(std::ofstream& out_stream) const override;

    private:
        Protocol::Host host_;
        Protocol::Port port_;
        Path path_;

        std::unique_ptr<Sockets::TcpSocket> socket_ptr;
    
    public:
        const static Protocol::Port default_http_port;
        const static size_t buffer_size_;
    };
}