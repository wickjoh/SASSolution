/*******************************************
 * 
 * File Name    :   DataBlock.cpp
 * 
 * Description  :   File constain the deffination of Data Blcok class.
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/
#include <cstring>
#include <utility>

#include "DataBlock.hpp"

DataBlock::DataBlock()
    : m_p_buffer(std::make_unique<char[]>(Constants::DATA_BLOCK_SIZE)),
      m_capacity(Constants::DATA_BLOCK_SIZE),
      m_data_size(Constant::ZERO),
      m_is_last_block(false)
{
}

DataBlock::DataBlock(std::size_t capacity)
    : m_p_buffer(std::make_unique<char[]>(capacity)),
      m_capacity(capacity),
      m_data_size(Constant::ZERO),
      m_is_last_block(false)
{
}

DataBlock::DataBlock(const DataBlock& other)
    : m_p_buffer(std::make_unique<char[]>(other.m_capacity)),
      m_capacity(other.m_capacity),
      m_data_size(other.m_data_size),
      m_is_last_block(other.m_is_last_block)
{
    std::memcpy(m_p_buffer.get(),
                other.m_p_buffer.get(),
                m_data_size);
}

DataBlock::DataBlock(DataBlock&& other) noexcept
    : m_p_buffer(std::move(other.m_p_buffer)),
      m_capacity(other.m_capacity),
      m_data_size(other.m_data_size),
      m_is_last_block(other.m_is_last_block)
{
    other.m_capacity      = Constant::ZERO;
    other.m_data_size     = Constant::ZERO;
    other.m_is_last_block = false;
}

DataBlock::~DataBlock()
{
    //unique_ptr releases memory automatically
}

DataBlock& DataBlock::operator=(const DataBlock& other)
{
    if (this != &other)
    {
        m_capacity      = other.m_capacity;
        m_data_size     = other.m_data_size;
        m_is_last_block = other.m_is_last_block;

        m_p_buffer = std::make_unique<char[]>(m_capacity);

        std::memcpy(m_p_buffer.get(),
                    other.m_p_buffer.get(),
                    m_data_size);
    }
    return *this;
}

DataBlock& DataBlock::operator=(DataBlock&& other) noexcept
{
    if (this != &other)
    {
        m_p_buffer = std::move(other.m_p_buffer);

        m_capacity      = other.m_capacity;
        m_data_size     = other.m_data_size;
        m_is_last_block = other.m_is_last_block;

        other.m_capacity      = 0U;
        other.m_data_size     = 0U;
        other.m_is_last_block = false;
    }
    return *this;
}

char* DataBlock::data()
{
    return m_p_buffer.get();
}

void DataBlock::setDataSize(std::size_t size)
{
    if (size <= m_capacity)
    {
        m_data_size = size;
    }
}

std::size_t DataBlock::dataSize() const
{
    return m_data_size;
}

std::size_t DataBlock::capacity() const
{
    return m_capacity;
}

void DataBlock::setLastBlock(bool value)
{
    m_is_last_block = value;
}

bool DataBlock::isLastBlock() const
{
    return m_is_last_block;
}
