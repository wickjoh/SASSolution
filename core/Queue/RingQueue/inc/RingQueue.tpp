/*******************************************
 * 
 * File Name    :   RingQueueu.tpp
 * 
 * Description  :   File constain implementation of Ring Q class.
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/


#ifndef RING_QUEUE_TPP
#define RING_QUEUE_TPP

#include <utility>
#include <stdexcept>

//Default Constructor
template<typename RQT>
RingQueue<RQT>::RingQueue()
    : m_p_buffer(nullptr),
      m_capacity(Constants::DEFAULT_QUEUE_CAPACITY),
      m_front(Constants::ZERO),
      m_rear(Constants::ZERO),
      m_size(Constants::ZERO)
{
    m_p_buffer = std::make_unique<RQT[]>(m_capacity);
}

//Parameterized Constructor
template<typename RQT>
RingQueue<RQT>::RingQueue(std::size_t capacity)
    : m_p_buffer(nullptr),
      m_capacity(capacity),
      m_front(Constants::ZERO),
      m_rear(Constants::ZERO),
      m_size(Constants::ZERO)
{
    if (m_capacity == Constants::ZERO)
    {
        m_capacity = Constants::DEFAULT_QUEUE_CAPACITY;
    }

    m_p_buffer = std::make_unique<RQT[]>(m_capacity);
}


 //Copy Constructor
template<typename RQT>
RingQueue<RQT>::RingQueue(const RingQueue& other)
    : m_p_buffer(std::make_unique<RQT[]>(other.m_capacity)),
      m_capacity(other.m_capacity),
      m_front(other.m_front),
      m_rear(other.m_rear),
      m_size(other.m_size)
{
    for(std::size_t index = Constants::ZERO;
        index < m_capacity;
        ++index)
    {
        m_p_buffer[index] = other.m_p_buffer[index];
    }
}

//Move Constructor
template<typename RQT>
RingQueue<RQT>::RingQueue(RingQueue&& other) noexcept
    : m_p_buffer(std::move(other.m_p_buffer)),
      m_capacity(other.m_capacity),
      m_front(other.m_front),
      m_rear(other.m_rear),
      m_size(other.m_size)
{
    other.m_capacity = Constants::ZERO;
    other.m_front = Constants::ZERO;
    other.m_rear = Constants::ZERO;
    other.m_size = Constants::ZERO;
}

//Destructor
template<typename RQT>
RingQueue<RQT>::~RingQueue() noexcept
{
}

//Copy Assignment Operator
template<typename RQT>
RingQueue<RQT>& RingQueue<RQT>::operator=(const RingQueue& other)
{
    if(this != &other)
    {
        m_capacity = other.m_capacity;
        m_front = other.m_front;
        m_rear = other.m_rear;
        m_size = other.m_size;

        m_p_buffer = std::make_unique<RQT[]>(m_capacity);

        for(std::size_t index = Constants::ZERO;
            index < m_capacity;
            ++index)
        {
            m_p_buffer[index] = other.m_p_buffer[index];
        }
    }

    return *this;
}

//Move Assignment Operator
template<typename RQT>
RingQueue<RQT>& RingQueue<RQT>::operator=(RingQueue&& other) noexcept
{
    if(this != &other)
    {
        m_p_buffer = std::move(other.m_p_buffer);

        m_capacity = other.m_capacity;
        m_front = other.m_front;
        m_rear = other.m_rear;
        m_size = other.m_size;

        other.m_capacity = Constants::ZERO;
        other.m_front = Constants::ZERO;
        other.m_rear = Constants::ZERO;
        other.m_size = Constants::ZERO;
    }
    return *this;
}

//Enqueue
template<typename RQT>
bool RingQueue<RQT>::enqueue(RQT&& value)
{
    if(isFull())
    {
        return false;
    }

    m_p_buffer[m_rear] = std::move(value);
    m_rear = (m_rear + Constants::ONE) % m_capacity;
    m_size++;
    return true;
}

template<typename RQT>
bool RingQueue<RQT>::dequeue(RQT& value)
{
    if(isEmpty())
    {
        return false;
    }
    value = std::move(m_p_buffer[m_front]);
    m_front = (m_front + Constants::ONE) % m_capacity;
    m_size--;
    return true;
}

template<typename RQT>
bool RingQueue<RQT>::front(RQT& value) const
{
    if(isEmpty())
    {
        return false;
    }
    value = m_p_buffer[m_front];
    return true;
}

template<typename RQT>
bool RingQueue<RQT>::isEmpty() const 
{
    return (m_size == Constants::ZERO);
}

template<typename RQT>
bool RingQueue<RQT>::isFull() const 
{
    return (m_size == m_capacity);
}

template<typename RQT>
std::size_t RingQueue<RQT>::size() const 
{
    return m_size;
}

template<typename RQT>
std::size_t RingQueue<RQT>::capacity() const 
{
    return m_capacity;
}

template<typename RQT>
void RingQueue<RQT>::clear() 
{
    m_front = Constants::ZERO;
    m_rear = Constants::ZERO;
    m_size = Constants::ZERO;
}
#endif