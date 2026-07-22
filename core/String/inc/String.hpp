/*******************************************
 * 
 * File Name    :   String.h
 * 
 * Description  :   File constain the declaration of custom String class.
 *           
 * Author       :   NA       
 * 
 * Date         :   21-07-2026
 ******************************************/

#ifndef STRING_HPP
#define STRING_HPP

#include "Constant.hpp"

#include<memory>
#include<cstddef>

class String
{
    private :

        std::unique_ptr<char[]> m_str;
        std::size_t             m_length;
        std::size_t             m_capacity;
    
    public :

        String();
        explicit String(const char *p_str);
        String(const String &lrefString);
        String(String &&rrefString) noexcept;

        ~String();

        String& operator=(const String &lrefString);
        String& operator=(String &&rrefString);
        bool operator==(const String& other) const;
        char operator[](int index) const;
        
        std::size_t getLength() const;
        std::size_t getCapacity() const;
        bool isEmpty() const;
        bool isEqual(const String &lrefString) const;
        int  compare(const String& lrefString) const;
        bool allocate(std::size_t maxCapacity);

        char* getBuffer();
};


#endif