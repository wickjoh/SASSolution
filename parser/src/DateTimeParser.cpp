/******************************************************************************
 *
 * File Name      : DateTimeParser.cpp
 *
 * Description    : Implementation of DateTimeParser.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 ******************************************************************************/

#include "DateTimeParser.hpp"
#include <cstring>

DateTimeParser::DateTimeParser()
{
    std::memset(m_record_buffer, Constants::ZERO, sizeof(m_record_buffer));
}

DateTimeParser::~DateTimeParser()
{
}

bool DateTimeParser::getNextRecord(const DataBlock& dataBlock,
                                   std::size_t& currentIndex,
                                   String& record)
{
    bool result = false;

    do 
    {
        /*FiX_Issue_1_S*/
        while (readLine(dataBlock, currentIndex))
        {
            trimLine();
            
            if (isLineEmpty())
            {
                continue;
            }

            record = String(m_record_buffer);
            result = true;
            break;
        }
        /*FiX_Issue_1_E*/

    }while(Constants::ZERO);

    return result;
}

bool DateTimeParser::readLine(const DataBlock& dataBlock,
                              std::size_t& currentIndex)
{
    std::size_t recordIndex = Constants::ZERO;
    const char* pBuffer = dataBlock.data();

    while (currentIndex < dataBlock.dataSize())
    {
        char ch = pBuffer[currentIndex++];
        if (ch == '\n')
        {
            break;
        }
        if (recordIndex < (MAX_DATE_TIME_LENGTH - 1U))
        {
            m_record_buffer[recordIndex++] = ch;
        }
    }

    m_record_buffer[recordIndex] = '\0';
    return (recordIndex != Constants::ZERO);
}

void DateTimeParser::trimLine()
{
    std::size_t length = std::strlen(m_record_buffer);
    if (length == Constants::ZERO)
    {
        return;
    }
    if (m_record_buffer[length - 1U] == '\r')
    {
        m_record_buffer[length - 1U] = '\0';
    }
}

bool DateTimeParser::isLineEmpty() const
{
    return (m_record_buffer[Constants::ZERO] == '\0');
}