/******************************************************************************
 *
 * File Name      : OutputFileWriter.cpp
 *
 * Description    : Impl of OutputFileWriter class
 * 
 * Author         : NA
 *
 * Date           : 21-07-2026
 ******************************************************************************/
#include "OutputFileWriter.hpp"

OutputFileWriter::OutputFileWriter()
    : m_p_output_file(nullptr),
      m_p_hash_set(nullptr)
{
}

OutputFileWriter::OutputFileWriter(
        const String& output_file_name,
        HashSet<String>* p_hash_set)
    : m_p_output_file(nullptr),
      m_output_file_name(output_file_name),
      m_p_hash_set(p_hash_set)
{
}

OutputFileWriter::~OutputFileWriter()
{
    close();
}

bool OutputFileWriter::open()
{
    if (m_p_output_file != nullptr)
    {
        return true;
    }
    m_p_output_file = fopen(m_output_file_name.getBuffer(), "w");
    return (m_p_output_file != nullptr);
}

void OutputFileWriter::close()
{
    if (m_p_output_file != nullptr)
    {
        fclose(m_p_output_file);
        m_p_output_file = nullptr;
    }
}

bool OutputFileWriter::isOpen() const
{
    return (m_p_output_file != nullptr);
}

bool OutputFileWriter::write()
{
    if (!open())
    {
        return false;
    }
    std::size_t totalBuckets =
            m_p_hash_set->bucketCount();

    for (std::size_t bucketIndex = Constants::ZERO;
         bucketIndex < totalBuckets;
         bucketIndex++)
    {
        SinglyLinkedList<String>& bucket =
            m_p_hash_set->getBucket(bucketIndex);

        const typename SinglyLinkedList<String>::Node* pNode =
            bucket.getHead();

        while (pNode != nullptr)
        {
            fprintf(m_p_output_file, "%s\n", pNode->m_data.getBuffer());
            pNode = pNode->m_p_next.get();
        }
    }
    close();
    return true;
}