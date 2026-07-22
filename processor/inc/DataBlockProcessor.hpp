/******************************************************************************
 *
 * File Name      : DataBlockProcessor.hpp
 *
 * Description    : Processes DataBlock objects received from the shared queue.
 *                  Each DataBlock is parsed, validated and unique valid
 *                  date-time records are stored.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#ifndef DATA_BLOCK_PROCESSOR_HPP
#define DATA_BLOCK_PROCESSOR_HPP

#include "DataBlock.hpp"
#include "String.hpp"
#include "DateTimeParser.hpp"
#include "DateTimeValidator.hpp"
#include "SynchronizedQueue.hpp"
#include "HashSet.hpp"
#include "Constant.hpp"

class DataBlockProcessor
{
    private:

        SynchronizedQueue<DataBlock>*   m_p_queue;
        HashSet<String>*                m_p_hash_set;
        DateTimeParser                  m_parser;
        DateTimeValidator               m_validator;

    public:

        DataBlockProcessor();
        DataBlockProcessor(
                SynchronizedQueue<DataBlock>* p_queue,
                HashSet<String>* p_hash_set);

        ~DataBlockProcessor();
        void process();
};
#endif
