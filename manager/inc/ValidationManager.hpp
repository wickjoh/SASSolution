/******************************************************************************
 *
 * File Name      : ValidationManager.h
 *
 * Description    : Coordinates complete validation workflow.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#ifndef VALIDATION_MANAGER_HPP
#define VALIDATION_MANAGER_HPP

#include <cstddef>

#include "Constant.hpp"
#include "String.hpp"
#include "HashSet.hpp"
#include "DataBlock.hpp"
#include "WorkerPool.hpp"
#include "InputFileReader.hpp"
#include "OutputFileWriter.hpp"
#include "SynchronizedQueue.hpp"

class ValidationManager
{
    private:

        SynchronizedQueue<DataBlock>      m_queue;
        HashSet<String>                   m_hash_set;
        InputFileReader                   m_input_reader;
        WorkerPool                        m_worker_pool;
        OutputFileWriter                  m_output_writer;

    public:
        ValidationManager(const String& input_file,
                          const String& output_file,
                          std::size_t thread_count,
                          std::size_t queue_capacity,
                          std::size_t block_size);

        ~ValidationManager();
        bool execute();
};

#endif
