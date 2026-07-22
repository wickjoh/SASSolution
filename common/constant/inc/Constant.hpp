#ifndef CONSTANTS_H
#define CONSTANTS_H

/*******************************************
 * File Name    :   constant.h
 * 
 * Description  :   File constains all the constant that we are 
 *                  using inside this project
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/
#include <cstddef>

namespace Constants
{
    constexpr int ZERO            = 0;
    constexpr int ONE             = 1;
    constexpr int INVALID_INDEX   = -1;
    
    constexpr int SAS_SUCCESS = 0;
    constexpr int SAS_FAILURE = 1;

    //TO DO : Impl Condif file to strore all configuration level parameters
    constexpr std::size_t DEFAULT_BUCKET_COUNT      = 101U;
    constexpr std::size_t DEFAULT_QUEUE_CAPACITY    = 1024U;
    constexpr std::size_t DATA_BLOCK_SIZE           = 4096U;
}
#endif