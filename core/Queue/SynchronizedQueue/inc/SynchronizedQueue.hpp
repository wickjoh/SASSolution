/*******************************************
 * 
 * File Name    :   SynchronizedQueue.hpp
 * 
 * Description  :   File constain Synchronized Queue class
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/

#ifndef SYNCHRONIZED_QUEUE_HPP
#define SYNCHRONIZED_QUEUE_HPP

#include <mutex>
#include <condition_variable>

#include "RingQueue.hpp"

template<typename SQT>
class SynchronizedQueue
{
    private:

        RingQueue<SQT>                 m_queue;
        mutable std::mutex             m_mutex;
        std::condition_variable        m_not_empty_condition;
        std::condition_variable        m_not_full_condition;
        bool                           m_shutdown;

    public:

        SynchronizedQueue();
        explicit SynchronizedQueue(std::size_t capacity);

        SynchronizedQueue(const SynchronizedQueue&) = delete;
        SynchronizedQueue& operator=(const SynchronizedQueue&) = delete;
        SynchronizedQueue(SynchronizedQueue&&) = delete;
        SynchronizedQueue& operator=(SynchronizedQueue&&) = delete;
        ~SynchronizedQueue();

        bool enqueue(const SQT& value);
        bool dequeue(SQT& value);
        void shutdown();
        bool isEmpty();
        bool isFull();
        std::size_t size();
        void clear();
};

#include "SynchronizedQueue.tpp"

#endif
