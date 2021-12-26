/**
 * @file httpprotocol.cpp
 * @author Krisna Pranav
 * @brief 
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021 Apache-2.0
 * 
 */

#include "httpprotocol.hpp"
#include "exceptions.hpp"
#include <sstream>
#include <cstring>

using namespace Network;

HttpProtocol::HttpProtocol()
    : socket_ptr_{new Sockets::TcpSocket(AF_INET, 0)}
{
}

const Protocol::Host HttpProtocol::GetHost() const
{
    return host_;
}

void HttpProtocol::SetHost(const Host& host)
{
    host_ = host;
}

const Protocol::Port HttpProtocol::GetPort() const
{
    return port_;
}

void HttpProtocol::SetPort(const Port& port)
{
    port_ = port;
}