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

#include "nuclear_bits/threading/ThreadWorker.h"

namespace NUClear {
    namespace threading {
        
        ThreadWorker::ThreadWorker(ServiceTask task) :
        task(task),
        thread(std::bind(&ThreadWorker::core, this)) {
        }
        
        ThreadWorker::~ThreadWorker() {
            // If you put code in here, all sorts of madness happens (don't do it)
        }
        
        void ThreadWorker::kill() {
            task.kill();
        }
        
        void ThreadWorker::join() {
            
            // only join the thread if it's joinable (or errors!)
            try {
                if(thread.joinable()) {
                    thread.join();
                }
            }
            // Why this is thrown if you try to join an unjoinable thread, i'll never know
            catch (const std::system_error e) { }
        }
        
        std::thread::id ThreadWorker::getThreadId() {
            // get the thread id from our internal thread
            return thread.get_id();
        }
        
        void ThreadWorker::core() {
            
            // Run our main task
            task.run();
        }
    }
}
