/******************************************************************************
 *
 * File Name      : ValidationManager.cpp
 *
 * Description    : Implementation of ValidationManager.
 * 
 * Author         : NA
 *
 * Date           : 21-07-2026
 ******************************************************************************/

#include "ValidationManager.hpp"

ValidationManager::ValidationManager(
        const String& input_file,
        const String& output_file,
        std::size_t thread_count,
        std::size_t queue_capacity,
        std::size_t block_size) :
        m_queue(queue_capacity), 
        m_input_reader(input_file,&m_queue,block_size),
        m_worker_pool(thread_count,&m_queue,&m_hash_set),
        m_output_writer(output_file,&m_hash_set)
{
}
ValidationManager::~ValidationManager()
{
}
bool ValidationManager::execute()
{
    bool result = true;
    do 
    {
        if (!m_worker_pool.start())
        {
            result = false;
            break;
        }

        if (!m_input_reader.process())
        {
            result = false;
            break;
        }

        m_worker_pool.join();

        if (!m_output_writer.write())
        {
            result = false;
            break;
        }

    }while(Constants::ZERO);

    return result;
}
