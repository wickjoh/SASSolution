/******************************************************************************
 *
 * File Name      : DateTimeParser.h
 *
 * Description    : Parses DataBlock into date-time records.
 * 
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#ifndef DATE_TIME_PARSER_HPP
#define DATE_TIME_PARSER_HPP

#include "Constant.hpp"
#include "DataBlock.hpp"
#include "String.hpp"
#include "SynchronizedQueue.hpp"

constexpr std::size_t MAX_DATE_TIME_LENGTH = 32U;

class DateTimeParser
{
    private:
        char    m_record_buffer[MAX_DATE_TIME_LENGTH];
 
        bool readLine(const DataBlock& dataBlock, std::size_t& currentIndex);
        void trimLine();
        bool isLineEmpty() const;

    public:
        DateTimeParser();
        ~DateTimeParser();

        bool getNextRecord(const DataBlock& dataBlock, std::size_t& currentIndex, String& record);
};
#endif