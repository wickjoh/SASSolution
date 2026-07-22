/******************************************************************************
 *
 * File Name      : InputFileReader.hpp
 *
 * Description    : Reads input file in fixed-size data blocks and pushes
 *                  complete records into SynchronizedQueue.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#ifndef INPUT_FILE_READER_HPP
#define INPUT_FILE_READER_HPP

#include <cstdio>

#include "String.hpp"
#include "DataBlock.hpp"
#include "SynchronizedQueue.hpp"
#include "Constant.hpp"

class InputFileReader
{
    private:

        FILE*                               m_p_input_file;
        String                              m_file_name;
        SynchronizedQueue<DataBlock>*       m_p_queue;
        std::size_t                         m_block_size;
        String                              m_partial_record;

        
        //Find last newline character in the buffer.
        std::size_t findLastNewLine(const char* p_buffer,
                                    std::size_t data_size) const;

        //Copies remaining partial record to internal buffer.
        void savePartialRecord(const char* p_buffer,
                               std::size_t start_index,
                               std::size_t end_index);

        //Prepends previous partial record to current block.
        void prependPartialRecord(DataBlock& data_block);

    public:
        InputFileReader();
        InputFileReader(const String& file_name,
                        SynchronizedQueue<DataBlock>* p_queue,
                        std::size_t block_size);
        ~InputFileReader();

        bool open();
        void close();
        bool isOpen() const;
        bool process();
};

#endif