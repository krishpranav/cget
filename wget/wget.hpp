/**
 * @file wget.hpp
 * @author Krisna Pranav
 * @brief 
 * @version 0.1
 * @date 2021-12-27
 * 
 * @copyright Copyright (c) 2021 Apache-2.0
 * 
 */

#pragma once

#include <string>
#include <fstream>
#include <regex>
#include "tcpsocket.hpp"
#include "protocol.h"
#include <sstream>

class Wget {
public:
    enum class ProtocolType
    {
        HTTP
    };

    Wget(ProtocolType protocolType);
    ~Wget() = default;

    Wget(const Wget &wget) = delete;
    Wget& operator=(const Wget &wget) = delete;

    std::string Download(const std::string& url);
};