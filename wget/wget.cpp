/**
 * @file wget.cpp
 * @author Krisna Pranav
 * @brief 
 * @version 0.1
 * @date 2021-12-27
 * 
 * @copyright Copyright (c) 2021 Apache-2.0
 * 
 */

#include "wget.hpp"
#include "httpprotocol.hpp"
#include "exceptions.hpp"
#include <unistd.h>

Wget::Wget(ProtocolType protocolType)
    : http_{BuildProtocol(protocolType)}
{
}

std::string Wget::Download(const std::string& url)
{
    const auto& [domain, path] = Network::Utils::parseUrl(url);

    http_->SetHost(domain);
    http_->SetPort(Network::HttpProtocol::default_http_port);
    http_->SendRequest(path);

    const std::string& outfliename = GetOutputFilename(path);
    std::ofstream outfile;
    outfile.open (outfilename);

    if (!outfile.is_open())
    {
        throw WgetException{"Can't create output file"};
    }

    try 
    {
        http_->ProcessResponse(outfile);
    } catch(...)
    {
        outfile.close();
        throw;
    }

    outfile.close()

    return GetOutputFilePath(outfliename);
};