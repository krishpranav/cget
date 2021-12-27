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

void HttpProtocol::SendRequest(const Path& path) const
{
    std::stringstream request_string_stream;
    
    request_string_stream << "GET /"  << path   << " HTTP/1.1\r\n";
    request_string_stream << "Host: " << host_  << "\r\n\r\n";
    request_string_stream << "Connection: keep-alive\r\n\r\n";
    request_string_stream << "Keep-Alive: 300\r\n";
    
    auto request = request_string_stream.str();
    const auto& requst_c_string = request.c_str();
    
    socket_ptr_->connect(GetHost().c_str(), GetPort());
    socket_ptr_->send(requst_c_string,
                      static_cast<unsigned int>(strlen(requst_c_string)),
                      0);
}

void HttpProtocol::ProcessResponse(std::ofstream& out_stream) const
{
    char response[HttpProtocol::buffer_size_];
    long received_len;
    char * ptr;
    
    bool found_headers = false;
    
    while((received_len = socket_ptr_->receive(response,
                                               static_cast<int>(sizeof(response)),
                                               0)) > 0)
    {
        if(!found_headers && (ptr = std::strstr(response, "\r\n\r\n")))
        {
            found_headers = true;
            auto delta = ptr - response + sizeof("\r\n\r\n") - 1;
            
            out_stream.write(response + delta, received_len - delta);
        }
        else{
            out_stream.write(response, received_len);
        }
    }
}

std::pair<std::string, std::string> Utils::parseUrl(const std::string& url)
{
    if (std::smatch smatch;
        regex_search(url, smatch, Utils::url_regex))
    {
        return {smatch[1], smatch[2]};
    }else
    {
        throw HttpProtocolException{"Can't parse url"};
    }
}

const Protocol::Port HttpProtocol::default_http_port{80};
const size_t HttpProtocol::buffer_size_{10000};