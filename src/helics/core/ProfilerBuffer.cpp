/*
Copyright (c) 2017-2021,
Battelle Memorial Institute; Lawrence Livermore National Security, LLC; Alliance for Sustainable
Energy, LLC.  See the top-level NOTICE for additional details. All rights reserved.
SPDX-License-Identifier: BSD-3-Clause
*/

#include "ProfilerBuffer.hpp"

#include <cstring>
#include <fstream>
namespace helics {

void ProfilerBuffer::addMessage(const std::string& data)
{
    mBuffers.emplace_back(data);
}

void ProfilerBuffer::addMessage(std::string&& data)
{
    mBuffers.push_back(std::move(data));
}

ProfilerBuffer::~ProfilerBuffer()
{
    try {
        if (!mBuffers.empty()) {
            writeFile();
        }
    }
    catch (const std::ios_base::failure&) {
    }
}

void ProfilerBuffer::writeFile()
{
    std::ofstream file;
    // can't enable exception now because of gcc bug that raises ios_base::failure with useless
    // message file.exceptions(file.exceptions() | std::ios::failbit);
    file.open(mFileName, std::ios::out | std::ios::app);
    if (file.fail()) {
        throw std::ios_base::failure(std::strerror(errno));
    }

    // make sure write fails with exception if something is wrong
    file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

    for (auto& m : mBuffers) {
        if (!m.empty()) {
            file << m << std::endl;
        }
        m.clear();
    }
    mBuffers.clear();
}

}  // namespace helics
