/*******************************************
 * 
 * File Name    :   SynchronizedQueue.hpp
 * 
 * Description  :   File constain Impl Synchronized Queue class
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/

 
#ifndef SYNCHRONIZED_QUEUE_TPP
#define SYNCHRONIZED_QUEUE_TPP

#include <utility>

template<typename SQT>
SynchronizedQueue<SQT>::SynchronizedQueue()
    : m_shutdown(false)
{
}

template<typename SQT>
SynchronizedQueue<SQT>::SynchronizedQueue(std::size_t capacity)
    : m_queue(capacity),
      m_shutdown(false)
{
}

template<typename SQT>
SynchronizedQueue<SQT>::~SynchronizedQueue()
{
    shutdown();
}

template<typename SQT>
void SynchronizedQueue<SQT>::shutdown()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_shutdown = true;
    }

    /* Wake up all waiting threads */
    m_not_empty_condition.notify_all();
    m_not_full_condition.notify_all();
}

template<typename SQT>
bool SynchronizedQueue<SQT>::enqueue(const SQT& value)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_not_full_condition.wait(lock,
        [this]()
        {
            return (!m_queue.isFull() || m_shutdown);
        });

    if (m_shutdown)
    {
        return false;
    }

    m_queue.enqueue(value);
    lock.unlock();
    m_not_empty_condition.notify_one();
    return true;
}

template<typename SQT>
bool SynchronizedQueue<SQT>::dequeue(SQT& value)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_not_empty_condition.wait(lock,
        [this]()
        {
            return (!m_queue.isEmpty() || m_shutdown);
        });

    if (m_shutdown && m_queue.isEmpty())
    {
        return false;
    }
    m_queue.dequeue(value);
    lock.unlock();
    m_not_full_condition.notify_one();
    return true;
}

template<typename SQT>
void SynchronizedQueue<SQT>::clear()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.clear();
}

template<typename SQT>
bool SynchronizedQueue<SQT>::isEmpty()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.isEmpty();
}

template<typename SQT>
bool SynchronizedQueue<SQT>::isFull()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.isFull();
}

template<typename SQT>
std::size_t SynchronizedQueue<SQT>::size()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_queue.size();
}
#endif