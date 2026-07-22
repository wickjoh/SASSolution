/*******************************************
 * 
 * File Name    :   SinglyLinkedList.tpp
 * 
 * Description  :   File constain implementation of Singly Linked List Templte Class.
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/

#ifndef SINGLY_LINKED_LIST_TPP
#define SINGLY_LINKED_LIST_TPP

#include <utility>

//copy constructor
template<typename SLLT>
SinglyLinkedList<SLLT>::Node::Node(const SLLT& value)
    : m_data(value),
      m_p_next(nullptr)
{
}

//Move Constructor
template<typename SLLT>
SinglyLinkedList<SLLT>::Node::Node(SLLT&& value)
    : m_data(std::move(value)),
      m_p_next(nullptr)
{
}

//Destructor
template<typename SLLT>
SinglyLinkedList<SLLT>::Node::~Node()
{
}

//Default Constructor
template<typename SLLT>
SinglyLinkedList<SLLT>::SinglyLinkedList()
    : m_p_head(nullptr),
      m_p_tail(nullptr),
      m_size(Constants::ZERO)
{
}

//Param Constrcutor
template<typename SLLT>
SinglyLinkedList<SLLT>::SinglyLinkedList(const SinglyLinkedList& other)
    : m_p_head(nullptr),
      m_p_tail(nullptr),
      m_size(Constants::ZERO)
{
    Node* pCurrent = other.m_p_head.get();
    while (pCurrent != nullptr)
    {
        pushBack(pCurrent->m_data);
        pCurrent = pCurrent->m_p_next.get();
    }
}

//Move Constructor
template<typename SLLT>
SinglyLinkedList<SLLT>::SinglyLinkedList(SinglyLinkedList&& other) noexcept
    : m_p_head(std::move(other.m_p_head)),
      m_p_tail(other.m_p_tail),
      m_size(other.m_size)
{
    other.m_p_tail = nullptr;
    other.m_size = Constants::ZERO;
}

//Destcutor
template<typename SLLT>
SinglyLinkedList<SLLT>::~SinglyLinkedList() noexcept
{
    clear();
}

template<typename SLLT>
SinglyLinkedList<SLLT>& SinglyLinkedList<SLLT>::operator=( const SinglyLinkedList& other)
{
    if (this != &other)
    {
        clear();
        Node* pCurrent = other.m_p_head.get();
        while (pCurrent != nullptr)
        {
            pushBack(pCurrent->m_data);
            pCurrent = pCurrent->m_p_next.get();
        }
    }
    return *this;
}

template<typename SLLT>
SinglyLinkedList<SLLT>& SinglyLinkedList<SLLT>::operator=(SinglyLinkedList&& other) noexcept
{
    if (this != &other)
    {
        clear();
        m_p_head = std::move(other.m_p_head);
        m_p_tail = other.m_p_tail;
        m_size   = other.m_size;

        other.m_p_tail = nullptr;
        other.m_size   = Constants::ZERO;
    }
    return *this;
}

template<typename SLLT>
void SinglyLinkedList<SLLT>::pushFront(const SLLT& value)
{
    std::unique_ptr<Node> pNewNode = std::make_unique<Node>(value);

    if (m_p_head == nullptr)
    {
        m_p_tail = pNewNode.get();
    }

    pNewNode->m_p_next = std::move(m_p_head);
    m_p_head = std::move(pNewNode);
    m_size++;
}

template<typename SLLT>
void SinglyLinkedList<SLLT>::pushBack(const SLLT& value)
{
    std::unique_ptr<Node> pNewNode = std::make_unique<Node>(value);

    if (m_p_head == nullptr)
    {
        m_p_tail = pNewNode.get();
        m_p_head = std::move(pNewNode);
        m_size++;
        return;
    }

    m_p_tail->m_p_next = std::move(pNewNode);
    m_p_tail = m_p_tail->m_p_next.get();
    m_size++;
}

template<typename SLLT>
bool SinglyLinkedList<SLLT>::remove(const SLLT& value)
{
    Node* pPrevious = nullptr;
    Node* pCurrent  = m_p_head.get();
    bool result = false;

    while (pCurrent != nullptr)
    {
        if (pCurrent->m_data.isEqual(value))
        {
            if (pPrevious == nullptr)
            {
                m_p_head = std::move(m_p_head->m_p_next);
                if (m_p_head == nullptr)
                {
                    m_p_tail = nullptr;
                }
            }
            else
            {
                std::unique_ptr<Node> pTemp =
                    std::move(pPrevious->m_p_next);

                pPrevious->m_p_next =
                    std::move(pTemp->m_p_next);

                if (pPrevious->m_p_next == nullptr)
                {
                    m_p_tail = pPrevious;
                }
            }
            m_size--;
            result = true;
            break;
        }
        pPrevious = pCurrent;
        pCurrent = pCurrent->m_p_next.get();
    }
    return result;
}

template<typename SLLT>
void SinglyLinkedList<SLLT>::clear() noexcept
{
    m_p_head.reset();
    m_p_tail = nullptr;
    m_size = Constants::ZERO;
}

template<typename SLLT>
bool SinglyLinkedList<SLLT>::isEmpty() const noexcept
{
    return (m_size == Constants::ZERO);
}

template<typename SLLT>
std::size_t SinglyLinkedList<SLLT>::size() const noexcept
{
    return m_size;
}

template<typename SLLT>
const typename SinglyLinkedList<SLLT>::Node*
SinglyLinkedList<SLLT>::getHead() const 
{
    return m_p_head.get();
}

template<typename SLLT>
bool SinglyLinkedList<SLLT>::contains(const SLLT& value) const
{
    const Node* current = m_p_head.get();
    while(current != nullptr)
    {
        if(current->m_data == value)
        {
            return true;
        }
        current = current->m_p_next.get();
    }
    return false;
}
#endif