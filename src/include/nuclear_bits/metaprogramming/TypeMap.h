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

#ifndef NUCLEAR_METAPROGRAMMING_TYPEMAP_H
#define NUCLEAR_METAPROGRAMMING_TYPEMAP_H

#include <mutex>
#include <memory>
#include <vector>

namespace NUClear {
    namespace metaprogramming {
        
        /**
         * @brief This exception is thrown when there is no data in the map to return.
         */
        struct NoDataException : public std::exception {};
        
        /**
         * @brief The simplest and fastest map format, It stores a single value and returns it when requested later.
         *
         * @details
         *  This map stores a single value in it's store when the set function is called, and when get is later called
         *  this object will be returned. This map is accessed by template paramters, because of this when the compiler
         *  compiles this map. It can resolve each of the map accesses into a direct function call. This allows the map to
         *  be looked up at compile time and optimized to very efficent code. There are several variations of the Map
         *  provided through the MapType parameter the operation of each of these is described in their individual
         *  documentation.
         *
         * @attention
         *  Note that because this is an entirely static class, if two maps with the same TMapID are used, they access the
         *  same map
         *
         * @author Trent Houliston
         *
         * @see CompiledMap
         */
        template <typename TMapID, typename TKey, typename TValue>
        class TypeMap {
        private:
            /// @brief Deleted constructor as this class is a static class.
            TypeMap() = delete;
            /// @brief Deleted destructor as this class is a static class.
            ~TypeMap() = delete;
            /// @brief the data variable where the data is stored for this map key.
            
            static std::shared_ptr<TValue> data;
            static std::mutex mutex;
            
        public:
            /**
             * @brief Stores the passed value in this map.
             *
             * @param d a pointer to the data to be stored (the map takes ownership)
             */
            static void set(std::shared_ptr<TValue> d) {
                
                // Do this once G++ supports it
                //std::atomic_store_explicit(&data, d, std::memory_order_relaxed);
                
                // Lock a mutex and set our data
                std::lock_guard<std::mutex> lock(mutex);
                data = d;
                
            }
            
            /**
             * @brief Gets the value that was previously stored.
             *
             * @return a shared_ptr to the data that was previously stored
             *
             * @throws NoDataException if there is no data that was previously stored
             */
            static std::shared_ptr<TValue> get() {
                
                // TODO do this when gcc supports it
                // std::atomic_load_explicit(&data, std::memory_order_relaxed);
                
                std::shared_ptr<TValue> d;
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    d = data;
                }
                
                
                //If the pointer is not a nullptr
                if(d) {
                    return d;
                }
                else {
                    throw NoDataException();
                }
            }
        };
        
        template <typename TMapID, typename TKey, typename TValue>
        class TypeList {
        private:
            /// @brief Deleted constructor as this class is a static class.
            TypeList() = delete;
            /// @brief Deleted destructor as this class is a static class.
            ~TypeList() = delete;
            /// @brief the data variable where the data is stored for this map key.
            static std::vector<TValue> data;
            
        public:
            
            /**
             * @brief Gets the list that is stored in this type location
             *
             * @return A reference to the vector stored in this location
             */
            static std::vector<TValue>& get() {
                return data;
            }
        };
        
        /// Initialize our shared_ptr data
        template <typename TMapID, typename TKey, typename TValue>
        std::shared_ptr<TValue> TypeMap<TMapID, TKey, TValue>::data;
        template <typename TMapID, typename TKey, typename TValue>
        std::mutex TypeMap<TMapID, TKey, TValue>::mutex;
        
        /// Initialize our type list data
        template <typename TMapID, typename TKey, typename TValue>
        std::vector<TValue> TypeList<TMapID, TKey, TValue>::data;
    }
}

#endif
