/*******************************************
 * 
 * File Name    :   String.cpp
 * 
 * Description  :   File constain the deffination of custom String class.
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/

 #include "String.hpp"

#include <memory>
#include <utility>
#include <cstring>

//Default Constructor
String::String()
    : m_str(nullptr),
      m_length(Constants::ZERO),
      m_capacity(Constants::ZERO)
{
}

//Parameterize Constructor 
String::String(const char* p_str)
    : m_str(nullptr),
      m_length(Constants::ZERO),
      m_capacity(Constants::ZERO)
{
    if (p_str == nullptr)
    {
        return;
    }
    m_length    = strlen(p_str);
    m_capacity  = m_length + Constants::ONE;
    m_str       = std::make_unique<char[]>(m_capacity);
    strcpy(m_str.get(), p_str);
}

//Copy Constructor 
String::String(const String& lrefString)
    : m_str(nullptr),
      m_length(lrefString.m_length),
      m_capacity(lrefString.m_capacity)
{
    if (lrefString.m_str != nullptr)
    {
        m_str = std::make_unique<char[]>(m_capacity);
        strcpy(m_str.get(), lrefString.m_str.get());
    }
}

//Move Constructor
String::String(String&& rrefString) noexcept
    : m_str(std::move(rrefString.m_str)),
      m_length(rrefString.m_length),
      m_capacity(rrefString.m_capacity)
{
    rrefString.m_length     = Constants::ZERO;
    rrefString.m_capacity   = Constants::ZERO;
}

//Destructor 
String::~String()
{
    //std::unique_ptr automatically releases memory 
}

//Copy-assignment operator
String& String::operator=(const String& lrefString)
{
    if (this != &lrefString)
    {
        if (lrefString.m_str != nullptr)
        {
            m_str = std::make_unique<char[]>(lrefString.m_capacity);
            std::strcpy(m_str.get(), lrefString.m_str.get());
        }
        else
        {
            m_str.reset();
        }
        m_length    = lrefString.m_length;
        m_capacity  = lrefString.m_capacity;
    }
    return *this;
}

//Move Assignemnt operator
String& String::operator=(String&& rrefString)
{
    if (this != &rrefString)
    {
        m_str       = std::move(rrefString.m_str);
        m_length    = rrefString.m_length;
        m_capacity  = rrefString.m_capacity;

        rrefString.m_length     = Constants::ZERO;
        rrefString.m_capacity   = Constants::ZERO;
    }
    return *this;
}

//Helper Functions 
int String::compare(const String& lrefString) const
{
    int compareOutput;

    do
    {
        if ((m_str == nullptr) &&
            (lrefString.m_str == nullptr))
        {
            compareOutput = Constants::ZERO;
            break;
        }

        if (m_str == nullptr)
        {
            compareOutput = Constants::INVALID_INDEX;
            break;
        }

        if (lrefString.m_str == nullptr)
        {
            compareOutput = Constants::ONE;
            break;
        }
        compareOutput = std::strcmp(m_str.get(), lrefString.m_str.get());
    
    }while(Constants::ZERO);

    return compareOutput;
}

bool String::allocate(std::size_t maxCapacity)
{
    bool result = true;
    do 
    {
        if (maxCapacity == Constants::ZERO)
        {
            result = false;
            break;
        }

        m_str       = std::make_unique<char[]>(maxCapacity);
        m_capacity  = maxCapacity;
        m_length    = Constants::ZERO;
        m_str[Constants::ZERO] = '\0';

    }while(Constants::ZERO);

    return result;
}

char String::operator[](int index) const
{
    if ((index < Constants::ZERO) ||
        (index >= m_length))
    {
        return '\0';
    }
    return m_str[index];
}

std::size_t String::getLength() const
{
    return m_length;
}

std::size_t String::getCapacity() const
{
    return m_capacity;
}

bool String::isEmpty() const
{
    return (m_length == Constants::ZERO);
}

bool String::isEqual(const String& lrefString) const
{
    return (compare(lrefString) == Constants::ZERO);
}

char* String::getBuffer()
{
    return m_str.get();
}

const char* String::getBuffer() const
{
    return m_str.get();
}

bool String::operator==(const String& other) const
{
    return isEqual(other);
}