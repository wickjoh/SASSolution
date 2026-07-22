/******************************************************************************
 *
 * File Name      : WorkerPool.cpp
 *
 * Description    : Implementation of WorkerPool.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#include "WorkerPool.hpp"

WorkerPool::WorkerPool()
    : m_p_threads(nullptr),
      m_p_processors(nullptr),
      m_thread_count(Constants:ZERO)
{
}

WorkerPool::WorkerPool(
        std::size_t thread_count,
        SynchronizedQueue<DataBlock>* p_queue,
        HashSet<String>* p_hash_set)
    : m_thread_count(thread_count)
{
    m_p_threads     = std::make_unique<std::thread[]>(m_thread_count);
    m_p_processors  = std::make_unique<DataBlockProcessor[]>(m_thread_count);

    for (std::size_t index = Constants::ZERO;
         index < m_thread_count;
         index++)
    {
        m_p_processors[index] = DataBlockProcessor( p_queue, p_hash_set);
    }
}

WorkerPool::~WorkerPool()
{
    join();
}

bool WorkerPool::start()
{
    for (std::size_t index = Constants::ZERO;
         index < m_thread_count;
         index++)
    {
        m_p_threads[index] = std::thread( &DataBlockProcessor::process, &m_p_processors[index]);
    }
    return true;
}

void WorkerPool::join()
{
    for (std::size_t index = Constants::ZERO;
         index < m_thread_count;
         index++)
    {
        if (m_p_threads[index].joinable())
        {
            m_p_threads[index].join();
        }
    }
}