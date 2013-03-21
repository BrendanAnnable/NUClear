#include "ReactionQueue.h"
#include <iostream>

namespace NUClear {

    void ReactionQueue::enqueue(Reaction const& value) {
        {
            std::unique_lock<std::mutex> lock(this->mutex);
            queue.push_front(value);
            std::cout << value.emitTime << std::endl;
        }
        this->condition.notify_one();
    }
    
    Reaction ReactionQueue::dequeue() {
        std::unique_lock<std::mutex> lock(this->mutex);
        this->condition.wait(lock, [this]() {
            std::cout << !this->queue.empty() << std::endl;
            return !this->queue.empty();
        });
        Reaction r = queue.back();
        std::cout << r.type.name() << std::endl;
        queue.pop_back();
        return r;
    }
}