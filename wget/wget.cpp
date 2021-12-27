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
    
    const std::string& outfilename = GetOutputFilename(path);
    std::ofstream outfile;
    outfile.open (outfilename);
    
    if(!outfile.is_open())
    {
        throw WgetException{"Can't create output file"};
    }
    
    try
    {
        http_->ProcessResponse(outfile);
    }catch(...)
    {
        outfile.close();
        throw;
    }
    
    outfile.close();
    
    return GetOutputFilePath(outfilename);
}

std::unique_ptr<Network::Protocol> Wget::BuildProtocol(Wget::ProtocolType protocolType) const
{
    if(protocolType == Wget::ProtocolType::HTTP)
    {
        return std::make_unique<Network::HttpProtocol>();
    }
    
    throw WgetException{"Wrong protocol type"};
}

const std::string Wget::GetOutputFilename(const std::string& path) const
{
    if(path.length() == 0)
    {
        throw WgetException{"Can't extract filename"};
    }
    
    const auto& position = path.find_last_of('/');
    if(position == path.npos)
    {
        return path;
    }else
    {
        return path.substr(position + 1);
    }
}

const std::string Wget::GetOutputFilePath(const std::string& filename) const
{
    char cwd[255];
    getcwd(cwd, sizeof(cwd));
    
    return std::string(cwd) + "/" + filename;
}