/******************************************************************************
 *
 * File Name      : main.cpp
 *
 * Description    : main entry point.
 *
 * Author         : NA
 *
 * Date           : 22-07-2026
 *
 ******************************************************************************/

#include <iostream>

#include "ValidationManager.hpp"
#include "Constant.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    int result = Constants::SAS_SUCCESS;

    do 
    {
        if (argc != 3)
        {
            std::cout << "Usage : Validator <input_file> <output_file>" << endl;
            result = Constants::SAS_FAILURE;
            break;
        }

        ValidationManager manager(
                String(argv[1]),
                String(argv[2]),
                Constants::DEFAULT_THREAD_COUNT,
                Constants::DEFAULT_QUEUE_CAPACITY,
                Constants::DATA_BLOCK_SIZE);

        if (!manager.execute())
        {
            std::cout << "Validation failed." << endl;
            result = Constants::SAS_FAILURE;
            break;
        }

        std::cout << "Validation completed successfully." << endl;
    
    }while(Constants::ZERO);

    return result;
}
