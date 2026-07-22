/******************************************************************************
 *
 * File Name      : OutputFileWriter.hpp
 *
 * Description    : Writes unique valid date-time records to output file.
 * 
 * Author         : NA
 *
 * Date           : 21-07-2026
 ******************************************************************************/

#ifndef OUTPUT_FILE_WRITER_HPP
#define OUTPUT_FILE_WRITER_HPP

#include <cstdio>

#include "String.hpp"
#include "HashSet.hpp"

class OutputFileWriter
{
    private:

        FILE*               m_p_output_file;
        String              m_output_file_name;
        HashSet<String>*    m_p_hash_set;

    public:
        OutputFileWriter();
        OutputFileWriter(const String& output_file_name,
                        HashSet<String>* p_hash_set);


        ~OutputFileWriter();

        bool open();
        void close();
        bool isOpen() const;
        bool write();
};

#endif