/******************************************************************************
 *
 * File Name      : WorkerPool.hpp
 *
 * Description    : Creates and manages worker threads responsible for
 *                  processing DataBlock objects.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#ifndef WORKER_POOL_HPP
#define WORKER_POOL_HPP

#include <thread>
#include <memory>

#include "DataBlockProcessor.hpp"
#include "SynchronizedQueue.hpp"
#include "HashSet.hpp"
#include "String.hpp"
#include "Constant.hpp"

class WorkerPool
{
    private:

        std::unique_ptr<std::thread[]>              m_p_threads;
        std::unique_ptr<DataBlockProcessor[]>       m_p_processors;
        std::size_t                                 m_thread_count;

    public:
        WorkerPool();
        WorkerPool(std::size_t thread_count,
                   SynchronizedQueue<DataBlock>* p_queue,
                   HashSet<String>* p_hash_set);
        ~WorkerPool();

        bool start();
        void join();
};

#endif