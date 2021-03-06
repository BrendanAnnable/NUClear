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

#ifndef NUCLEAR_EXTENSIONS_OPTIONAL_H
#define NUCLEAR_EXTENSIONS_OPTIONAL_H

#include "nuclear"

namespace NUClear {
    
    /**
     * @brief As a raw, we want to trigger when our real type is emitted.
     */
    template <typename TData>
    struct Reactor::TriggerType<dsl::Optional<TData>> {
        typedef TData type;
    };
    
    /**
     * @brief When getting, instead of getting the data normally, return a const pointer to it.
     */
    template <typename TData>
    struct PowerPlant::CacheMaster::Get<dsl::Optional<TData>> {
        static std::shared_ptr<std::shared_ptr<const TData>> get(PowerPlant& p) {
            
            std::shared_ptr<const TData> result(nullptr);
            
            try {
                result = PowerPlant::CacheMaster::Get<TData>::get(std::forward<PowerPlant&>(p));
            }
            catch (metaprogramming::NoDataException) {
            }
            
            return std::make_shared<std::shared_ptr<const TData>>(result);
        }
    };
}

#endif
