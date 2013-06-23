/**
 * Copyright (C) 2013 Jake Woods <jake.f.woods@gmail.com>, Trent Houliston <trent@houliston.me>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "NUClear/PowerPlant.h"

namespace NUClear {
    
    PowerPlant::NetworkMaster::NetworkMaster(PowerPlant* parent) :
    PowerPlant::BaseMaster(parent),
    m_context(1),
    m_pub(m_context, ZMQ_PUB),
    m_sub(m_context, ZMQ_SUB) {
        
        // Get our PGM address
        std::string address = addressForName(m_parent->configuration.networkGroup,
                                             m_parent->configuration.networkPort);
        
        // Bind our publisher to this address
        m_pub.bind(address.c_str());
        
        // Connect our subscriber to this address
        m_sub.connect(address.c_str());
        
        // Build a task
        Internal::ThreadWorker::InternalTask task(std::bind(&NetworkMaster::run, this),
                                                  std::bind(&NetworkMaster::kill, this));
        
        m_parent->threadmaster.internalTask(task);
    }
    
    void PowerPlant::NetworkMaster::run() {
        
        while (m_running) {
            
            zmq::message_t* message = new zmq::message_t();
            m_sub.recv(message);
            
            size_t type = Networking::Hash::hashToStdHash(static_cast<uint8_t*>(message->data()));
            
            auto it = m_deserialize.find(type);
            
            if(it != std::end(m_deserialize)) {
                it->second(static_cast<uint8_t*>(message->data()) + Networking::Hash::SIZE);
            }
            
            delete message;
            
            // Receive a message
            
            // Get the deserializer for this message
            
        }
        
        // TODO setup an internal task to run here from the thread master
        
        // Repeatedly recieve messages, find their type, run their deserialization functor and continue
    
    }
    
    void PowerPlant::NetworkMaster::kill() {
        // TODO kill this thread somehow
    }
    
    std::string PowerPlant::NetworkMaster::addressForName(std::string name, unsigned port) {
        
        // Hash our string
        std::hash<std::string> hash_fn;
        size_t hash = hash_fn(name);
        
        // Convert our hash into a multicast address
        uint32_t addr = 0xE0000200 + (hash % (0xEFFFFFFF - 0xE0000200));
        
        // Split our mulitcast address into a epgm address
        std::stringstream out;
        
        // Build our string
        out << "epgm://"
        << ((addr >> 24) & 0xFF) << "."
        << ((addr >> 16) & 0xFF) << "."
        << ((addr >>  8) & 0xFF) << "."
        << (addr & 0xFF) << ":"
        << port;
        
        return out.str();
    }
}
