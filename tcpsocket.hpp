/**
 * @file tcpsocket.hpp
 * @author Krisna Pranav
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021 Apache-2.0
 * 
 */

#pragma once

#include <string>
#include <memory>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>

namespace Sockets {
    using SocketDescriptor = int;
    
    class TcpSocket {
    public:
        TcpSocket(int family, int flags);
        virtual ~TcpSocket();
        
        TcpSocket(const TcpSocket &socket) = delete;
        TcpSocket& operator=(const TcpSocket &socket) = delete;
        
        void connect(std::string adress, int port);
        
        void send(const char *data, unsigned int length, int flags);
        long receive(char* msg, int len, int flags);
        
    private:
        struct CloseSocketDescriptor
        {
            void operator()(SocketDescriptor* socket_desc_) const;
        };
        
        struct sockaddr_in sockaddr_in_;
        
        std::unique_ptr<SocketDescriptor, CloseSocketDescriptor> socket_desc_ptr_;
        std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> addr_info_ptr_;
    };
}