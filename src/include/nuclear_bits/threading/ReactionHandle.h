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

#ifndef NUCLEAR_THREADING_REACTIONHANDLE_H
#define NUCLEAR_THREADING_REACTIONHANDLE_H

#include <typeindex>
#include <queue>
#include <vector>
#include <mutex>
#include <memory>
#include <string>

#include "Reaction.h"

namespace NUClear {
    namespace threading {

        /**
         * @brief Gives user code access to control the reaction object.
         *
         * @details
         *  This object is given to user code when they create a reaction.
         *  It contains functions which allow changing of the reaction after it has
         *  been created such as enabling and disabling its execution.
         *
         * @author Trent Houliston
         */
        class ReactionHandle {
        public:
            /// @brief the reaction that we are managing
            Reaction* context;

            /**
             * @brief Creates a new ReactionHandle for the reaction that is passed in.
             *
             * @param context the reaction that we are interacting with.
             */
            ReactionHandle(Reaction* context = nullptr);

            /**
             * @brief Enables the reaction and allows it to run.
             */
            ReactionHandle& enable();

            /**
             * @brief Disables the reaction, preventing it from running.
             */
            ReactionHandle& disable();

            /**
             * @brief Sets the enable status to the passed boolean.
             *
             * @param set the run status of the handle handle to be of the boolean
             */
            ReactionHandle& enable(bool set);

            /**
             * @brief Returns if this reaction is currently enabled.
             *
             * @return true if the reaction is enabled, false otherwise.
             */
            bool enabled();
        };
    }
}
#endif
