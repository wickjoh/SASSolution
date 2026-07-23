/*******************************************
 * 
 * File Name    :   SinglyLinkedList.hpp
 * 
 * Description  :   File constain the declaration of custom Singly Linked List class.
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/

#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP

#include "String.hpp"
#include "Constant.hpp"

template<typename SLLT>
class SinglyLinkedList
{
    public:

        struct Node
        {
            SLLT                    m_data;
            std::unique_ptr<Node>   m_p_next;

            Node() = default;
            explicit Node(const SLLT& value);
            explicit Node(SLLT&& value);
            ~Node();
        };

        std::unique_ptr<Node>   m_p_head;
        Node*                   m_p_tail;
        std::size_t             m_size;

        SinglyLinkedList();
        SinglyLinkedList(const SinglyLinkedList& other);
        SinglyLinkedList(SinglyLinkedList&& other) noexcept;

        ~SinglyLinkedList() noexcept;

        SinglyLinkedList& operator=(const SinglyLinkedList& other);
        SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept;

        void pushFront(const SLLT& value);
        void pushBack(const SLLT& value);
        bool remove(const SLLT& value);
        void clear() noexcept;
        bool isEmpty() const noexcept;
        std::size_t size() const noexcept;
        const Node* getHead() const;
        bool contains(const SLLT& value) const;
};

#include "SinglyLinkedList.tpp"

#endif