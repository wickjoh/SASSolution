/******************************************************************************
 *
 * File Name      : RingQueue.hpp
 *
 * Description    :  File constain Hash Set class.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <cstddef>

#include "Constant.hpp"
#include "SinglyLinkedList.hpp"

template<typename HST>
class HashSet
{
    private:

        SinglyLinkedList<HST>*  m_p_bucket;
        std::size_t             m_bucket_count;
        std::size_t             m_size;

        std::size_t hashIndex(const HST& value) const;

    public:

        HashSet();
        explicit HashSet(std::size_t bucketCount);
        HashSet(const HashSet& other);
        HashSet(HashSet&& other) noexcept;

        ~HashSet();

        HashSet& operator=(const HashSet& other);
        HashSet& operator=(HashSet&& other) noexcept;

        bool insert(const HST& value);
        bool contains(const HST& value) const;
        void clear();
        bool isEmpty() const;
        std::size_t size() const;
        std::size_t bucketCount() const;
        SinglyLinkedList<HST>& getBucket(std::size_t index);
};

#include "HashSet.tpp"
#endif