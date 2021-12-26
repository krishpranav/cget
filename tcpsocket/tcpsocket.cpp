/**
 * @file tcpsocket.hpp
 * @author Krisna Pranav
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021 Apache-2.0
 * 
 */

#include "tcpsocket.hpp"
#include "exceptions.hpp"
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

void TcpSocket::connect(std::string address, int port)
{
    addrinfo* ptr = nullptr;
    if(getaddrinfo(address.c_str(),
                   std::to_string(port).c_str(),
                   addr_info_ptr_.get(),
                   &ptr) != 0)
    {
        throw SocketException{"Domain or port is wrong"};
    }
    
    bool connected = false;
    
    for(auto p = ptr; p != NULL; p = p->ai_next) {
        if (::connect(*socket_desc_ptr_, p->ai_addr, p->ai_addrlen) == -1) {
            continue;
        }
        
        connected = true;
        break; 
    }
    
    freeaddrinfo(ptr);
    if(!connected)
    {
        throw SocketException{"Connection error"};
    }
}

void TcpSocket::send(const char *data, unsigned int length, int flags)
{
    const char * buff = data;
    ssize_t status = 0;
    int total_sent = 0;
    int left_to_send = length;
    
    while(total_sent < length)
    {
        status = ::send(*socket_desc_ptr_,
                        buff + total_sent,
                        left_to_send,
                        flags);
        
        if(status == -1)
        {
            throw SocketException{"Error while sending"};
        }
        else
        {
            total_sent += status;
            left_to_send -= status;
        }
    }
}

long TcpSocket::receive(char* msg, int len, int flags)
{
    long received_len;
    if((received_len = ::recv(*socket_desc_ptr_, msg, len, flags)) == -1)
    {
        throw SocketException{"Error while receiving"};
    }
    else if(received_len == 0)
    {
        return received_len;
    }
    
    return received_len;
}

void TcpSocket::CloseSocketDescriptor::operator()(SocketDescriptor* socket_desc_) const
{
    close(*socket_desc_);
}