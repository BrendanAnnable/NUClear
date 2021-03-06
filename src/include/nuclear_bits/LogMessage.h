/*
 * Copyright (C) 2013 Trent Houliston <trent@houliston.me>, Jake Woods <jake.f.woods@gmail.com>
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

#ifndef NUCLEAR_MESSAGES_LOGMESSAGE_H
#define NUCLEAR_MESSAGES_LOGMESSAGE_H

#include "LogLevel.h"

namespace NUClear {
    
    /**
     * @brief This type is a NUClear message type that holds a log message.
     */
    struct LogMessage {
        
        
        /// @brief The logging level of the log.
        LogLevel level;
        
        /// @brief The string contents of the message.
        std::string message;
        
        /// @brief The ID of the task that made this (or 0 if there was none)
        uint64_t taskId;
        
        /// @brief The ID of the reaction that made this (or 0 if there was none)
        uint64_t reactionId;
        
        /**
         * @brief Constructs a new LogMessage.
         *
         * @param level the logging level to set.
         * @param message the message to set.
         */
        LogMessage(const LogLevel& level
                   , const std::string& message
                   , const uint64_t& taskId
                   , const uint64_t& reactionId)
        : level(level)
        , message(message)
        , taskId(taskId)
        , reactionId(reactionId) {}
    };
}
#endif
