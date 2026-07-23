/******************************************************************************
 *
 * File Name      : DataBlock.hpp
 *
 * Description    : Class represents Data Block of data read from the input file
 *             
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#ifndef DATA_BLOCK_HPP
#define DATA_BLOCK_HPP

#include <memory>
#include <cstddef>
#include "Constant.hpp"

/******************************************************************************
 * Class Name     : DataBlock
 *
 * Description    : Stores one fixed-size block of data and its associated
 *                  metadata.
 ******************************************************************************/
class DataBlock
{
    private:

        std::unique_ptr<char[]>  m_p_buffer;
        std::size_t              m_capacity;
        std::size_t              m_data_size;
        bool                     m_is_last_block;

    public:

        DataBlock();
        explicit DataBlock(std::size_t capacity);
        DataBlock(const DataBlock &other);
        DataBlock(DataBlock &&other) noexcept;
 
        ~DataBlock();

        DataBlock& operator=(const DataBlock &other);
        DataBlock& operator=(DataBlock &&other) noexcept;

        char* data();
        std::size_t capacity() const;
        std::size_t dataSize() const;
        void setDataSize(std::size_t size);
        bool isLastBlock() const;
        void setLastBlock(bool value);
};
#endif