/**
 * @file tcpsocket.cpp
 * @author your name (you@domain.com)
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021 Apache-2.0
 * 
 */

#include "exceptions.hpp"
#include "tcpsocket.hpp"
#include <unistd.h>

using namespace Sockets;

TcpSocket::TcpSocket(int family, int flags)
    : addr_info_ptr_{new addrinfo, &freeaddrinfo}
{
    memset(addr_info_ptr_.get(), 0, sizeof(*addr_info_ptr_));
    
    addr_info_ptr_->ai_family   = family;
    addr_info_ptr_->ai_socktype = SOCK_STREAM;
    addr_info_ptr_->ai_flags    = flags;
    
    if(SocketDescriptor socket_desc_
       = ::socket(addr_info_ptr_->ai_family,
                  addr_info_ptr_->ai_socktype,
                  IPPROTO_IP);
       socket_desc_ != -1)
    {
        socket_desc_ptr_.reset(new SocketDescriptor{socket_desc_});
    }else
    {
        throw SocketException{"Can't create socket descriptor"};
    }
}

TcpSocket::~TcpSocket()
{
    
}