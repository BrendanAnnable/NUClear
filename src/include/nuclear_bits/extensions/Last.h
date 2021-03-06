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

#ifndef NUCLEAR_EXTENSIONS_LAST_H
#define NUCLEAR_EXTENSIONS_LAST_H

#include <deque>
#include <unordered_set>

#include "nuclear"

namespace NUClear {
    
    /**
     * @brief Last datatypes should trigger on the emission of a DataFor element of the
     *          requested last type.
     *
     * @tparam num      The number of elements we are storing data for.
     * @tparam TData    The datatype we are storing the lasts for.
     */
    template <int num, typename TData>
    struct Reactor::TriggerType<dsl::Last<num, TData>> {
        typedef DataFor<dsl::Last<num, TData>, std::vector<std::shared_ptr<const TData>>> type;
    };
    
    /**
     * @brief Data for a last is obtained by proxy, as are most DSL types.
     *
     * @tparam num      The number of elements we are storing data for.
     * @tparam TData    The datatype we are storing the lasts for.
     */
    template <int num, typename TData>
    struct PowerPlant::CacheMaster::Get<dsl::Last<num, TData>> {
        static std::shared_ptr<std::vector<std::shared_ptr<const TData>>> get(PowerPlant&) {
            
            return ValueCache<DataFor<dsl::Last<num, TData>, std::vector<std::shared_ptr<const TData>>>>::get()->data;
        }
    };
    
    /**
     * @brief Sets up the required machinery for when a last is used.
     *
     * @details
     *  When a last is used, this exists sets up a system to cache the last n
     *  of a datatype. It uses the requesting reactor as the provider for
     *  controlling the emissions.
     *
     * @tparam num      The number of elements we are storing data for.
     * @tparam TData    The datatype we are storing the lasts for.
     */
    template <int num, typename TData>
    struct Reactor::Exists<dsl::Last<num, TData>> {
        static void exists(Reactor& context) {
            
            // This map tracks what lasts are already looked after
            static std::unordered_set<std::type_index> inserted;
            
            // Check if we are already looking after this type
            if(inserted.find(typeid(dsl::Last<num, TData>)) == inserted.end()) {
                
                // Make a new reaction
                context.on<Trigger<Raw<TData>>, Options<Sync<dsl::Last<num, TData>>>>([&context] (const std::shared_ptr<const TData>& d) {
                    
                    // This holds the last elements that are needed
                    static std::deque<std::shared_ptr<const TData>> elements;
                    
                    // Push back our new element
                    elements.push_back(d);
                    
                    // If we have too many elements, then remove the first one
                    if(elements.size() > num) {
                        elements.pop_front();
                    }
                    
                    // Copy the data into a vector on a last
                    auto data = std::make_unique<DataFor<dsl::Last<num, TData>, std::vector<std::shared_ptr<const TData>>>>();
                    data->data->insert(data->data->begin(), elements.begin(), elements.end());
                    
                    // Emit the object for use
                    context.emit(std::move(data));
                });
            }
            
        }
    };
}

#endif
