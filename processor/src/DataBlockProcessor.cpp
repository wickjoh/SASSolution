/******************************************************************************
 *
 * File Name      : DataBlockProcessor.cpp
 *
 * Description    : Imp of DataBlockProcessor.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 ******************************************************************************/

#include "DataBlockProcessor.hpp"

DataBlockProcessor::DataBlockProcessor()
    : m_p_queue(nullptr),
      m_p_hash_set(nullptr)
{
}

DataBlockProcessor::DataBlockProcessor(
        SynchronizedQueue<DataBlock>* p_queue,
        HashSet<String>* p_hash_set)
    : m_p_queue(p_queue),
      m_p_hash_set(p_hash_set)
{
}

DataBlockProcessor::~DataBlockProcessor()
{
}

void DataBlockProcessor::process()
{
    DataBlock dataBlock;
    while (m_p_queue->dequeue(dataBlock))
    {
        std::size_t currentIndex = Constants::ZERO;
        String record;

        while (m_parser.getNextRecord(
                    dataBlock,
                    currentIndex,
                    record))
        {
            if (m_validator.validate(record))
            {
                m_p_hash_set->insert(record);
            }
        }

        if (dataBlock.isLastBlock())
        {
            break;
        }
    }
}
