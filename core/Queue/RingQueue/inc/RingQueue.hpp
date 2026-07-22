/******************************************************************************
 *
 * File Name      : RingQueue.hpp
 *
 * Description    : Generic fixed-size Ring Queue implementation.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#ifndef RING_QUEUE_HPP
#define RING_QUEUE_HPP

#include <memory>
#include <cstddef>

#include "Constant.hpp"

template<typename RQT>
class RingQueue
{
    private:

        std::unique_ptr<RQT[]>   m_p_buffer;
        std::size_t              m_capacity;
        std::size_t              m_front;
        std::size_t              m_rear;
        std::size_t              m_size;

    public:

        RingQueue();
        explicit RingQueue(std::size_t capacity);
        RingQueue(const RingQueue& other);
        RingQueue(RingQueue&& other) noexcept;

        ~RingQueue() noexcept;

        RingQueue& operator=(const RingQueue& other);
        RingQueue& operator=(RingQueue&& other) noexcept;

        bool enqueue(RQT&& value);
        bool dequeue(RQT& value);
        bool front(RQT& value) const;
        bool isEmpty() const;
        bool isFull() const;
        std::size_t size() const;
        std::size_t capacity() const;
        void clear();
};

#include "RingQueue.tpp";

#endif