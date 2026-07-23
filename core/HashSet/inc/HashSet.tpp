/*******************************************
 * 
 * File Name    :   SynchronizedQueue.hpp
 * 
 * Description  :   File constain Impl Hash Set Class
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/
#ifndef HASH_SET_TPP
#define HASH_SET_TPP

#include <memory>
#include <utility>
#include <stdexcept>

template<typename HST>
HashSet<HST>::HashSet()
    : m_p_bucket(nullptr),
      m_bucket_count(Constants::DEFAULT_BUCKET_COUNT),
      m_size(Constants::ZERO)
{
    m_p_bucket = new SinglyLinkedList<HST>[m_bucket_count];
}

template<typename HST>
HashSet<HST>::HashSet(std::size_t bucketCount)
    : m_p_bucket(nullptr),
      m_bucket_count(bucketCount),
      m_size(Constants::ZERO)
{
    if (m_bucket_count == Constants::ZERO)
    {
        m_bucket_count = Constants::DEFAULT_BUCKET_COUNT;
    }

    m_p_bucket = new SinglyLinkedList<HST>[m_bucket_count];
}

template<typename HST>
HashSet<HST>::HashSet(const HashSet& other)
    : m_p_bucket(nullptr),
      m_bucket_count(other.m_bucket_count),
      m_size(other.m_size)
{
    m_p_bucket = new SinglyLinkedList<HST>[m_bucket_count];

    for(std::size_t index = Constants::ZERO;
        index < m_bucket_count;
        ++index)
    {
        m_p_bucket[index] = other.m_p_bucket[index];
    }
}

template<typename HST>
HashSet<HST>::HashSet(HashSet&& other) noexcept
    : m_p_bucket(other.m_p_bucket),
      m_bucket_count(other.m_bucket_count),
      m_size(other.m_size)
{
    other.m_p_bucket = nullptr;
    other.m_bucket_count = Constants::ZERO;
    other.m_size = Constants::ZERO;
}

template<typename HST>
HashSet<HST>::~HashSet()
{
    delete[] m_p_bucket;
    m_p_bucket = nullptr;
}

template<typename HST>
HashSet<HST>& HashSet<HST>::operator=(const HashSet& other)
{
    if(this != &other)
    {
        delete[] m_p_bucket;
        m_p_bucket = nullptr;

        m_bucket_count  = other.m_bucket_count;
        m_size          = other.m_size;

        m_p_bucket = new SinglyLinkedList<HST>[m_bucket_count];
        for(std::size_t index = Constants::ZERO;
            index < m_bucket_count;
            index++)
        {
            m_p_bucket[index] = other.m_p_bucket[index];
        }
    }
    return *this;
}

template<typename HST>
HashSet<HST>& HashSet<HST>::operator=(HashSet&& other) noexcept
{
    if(this != &other)
    {
        delete[] m_p_bucket;
        m_p_bucket = nullptr;

        m_p_bucket      = other.m_p_bucket;
        m_bucket_count  = other.m_bucket_count;
        m_size          = other.m_size;

        other.m_p_bucket        = nullptr;
        other.m_bucket_count    = Constants::ZERO;
        other.m_size            = Constants::ZERO;
    }
    return *this;
}

template<typename HST>
std::size_t HashSet<HST>::hashIndex(const HST& value) const
{
    //TOD DO : Impl index calculcation, check corner scenario 
    const char* pBuffer = value.getBuffer();
    std::size_t hash = Constant::ZERO;

    while (*pBuffer != '\0')
    {
        hash = (hash * 31U) + static_cast<unsigned char>(*pBuffer);
        pBuffer++;
    }
    return hash % m_bucket_count;
}

template<typename HST>
bool HashSet<HST>::insert(const HST& value)
{
    std::size_t index = hashIndex(value);
    
    std::lock_guard<std::mutex> guard(bucketMutexes[index]);
    if(m_p_bucket[index].contains(value))
    {
        return false;
    }

    m_p_bucket[index].pushBack(value);
    m_size++;
    return true;
}

template<typename HST>
bool HashSet<HST>::contains(const HST& value) const
{
    std::size_t index = hashIndex(value);
    return m_p_bucket[index].contains(value);
}

template<typename HST>
void HashSet<HST>::clear()
{
    for(std::size_t index = Constants::ZERO;
        index < m_bucket_count;
        index++)
    {
        m_p_bucket[index].clear();
    }
    m_size = Constants::ZERO;
}

template<typename HST>
bool HashSet<HST>::isEmpty() const
{
    return (m_size == Constants::ZERO);
}

template<typename HST>
std::size_t HashSet<HST>::size() const
{
    return m_size;
}

template<typename HST>
std::size_t HashSet<HST>::bucketCount() const
{
    return m_bucket_count;
}

template<typename HST>
SinglyLinkedList<HST>& HashSet<HST>::getBucket(std::size_t index)
{
    return m_p_bucket[index];
}

#endif