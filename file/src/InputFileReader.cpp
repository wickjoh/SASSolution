/******************************************************************************
 *
 * File Name      : InputFileReader.cpp
 *
 * Description    : Impl of InputFileReader class
 * 
 * Author         : NA
 *
 * Date           : 21-07-2026
 ******************************************************************************/

#include "InputFileReader.hpp"

#include <cstring>

InputFileReader::InputFileReader()
    : m_p_input_file(nullptr),
      m_p_queue(nullptr),
      m_block_size(Constants::DATA_BLOCK_SIZE)
{
}

InputFileReader::InputFileReader(
    const String& file_name,
    SynchronizedQueue<DataBlock>* p_queue,
    std::size_t block_size)
    : m_p_input_file(nullptr),
      m_file_name(file_name),
      m_p_queue(p_queue),
      m_block_size(block_size),
      m_partial_record()
{
}

InputFileReader::~InputFileReader()
{
    close();
}

bool InputFileReader::open()
{
    if (m_p_input_file != nullptr)
    {
        return true;
    }

    m_p_input_file = fopen(m_file_name.getBuffer(), "rb");
    return (m_p_input_file != nullptr);
}

void InputFileReader::close()
{
    if (m_p_input_file != nullptr)
    {
        fclose(m_p_input_file);
        m_p_input_file = nullptr;
    }
}

bool InputFileReader::isOpen() const
{
    return (m_p_input_file != nullptr);
}

std::size_t InputFileReader::findLastNewLine(
    const char* p_buffer,
    std::size_t data_size) const
{
    if ((p_buffer == nullptr) || (data_size == Constants::ZERO))
    {
        return static_cast<std::size_t>(-1);
    }

    for (std::size_t index = data_size; 
        index > Constants::ZERO; 
        index--)
    {
        if (p_buffer[index - 1U] == '\n')
        {
            return (index - 1U);
        }
    }
    return static_cast<std::size_t>(-1);
}
bool InputFileReader::process()
{
    if (!open())
    {
        return false;
    }

    while (true)
    {
        DataBlock block(m_block_size);

        std::size_t bytesRead = fread(block.data(),
                                    sizeof(char),
                                    m_block_size,
                                    m_p_input_file);

        if (bytesRead == Constants::ZERO)
        {
            break;
        }

        block.setDataSize(bytesRead);

        if (feof(m_p_input_file))
        {
            block.setLastBlock(true);
        }

        if (!m_p_queue->enqueue(std::move(block)))
        {
            close();
            return false;
        }

        if (feof(m_p_input_file))
        {
            break;
        }
    }
    m_p_queue->shutdown();
    close();
    return true;
}