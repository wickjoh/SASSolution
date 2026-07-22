/******************************************************************************
 *
 * File Name      : DateTimeValidator.h
 *
 * Description    : Validates ISO-8601 date-time values.
 *
 * Author         : NA
 *
 * Date           : 21-07-2026
 *
 ******************************************************************************/

#ifndef DATE_TIME_VALIDATOR_HPP
#define DATE_TIME_VALIDATOR_HPP

#include "Constant.hpp"
#include "String.hpp"

class DateTimeValidator
{

    private :
        bool validateLength(const String& dateTime) const;
        bool validateSeparator(const String& dateTime) const;
        bool validateNumeric(const String& dateTime) const;
        bool validateDate(const String& dateTime) const;
        bool validateTime(const String& dateTime) const;
        bool validateTimeZone(const String& dateTime) const;

    public:
        DateTimeValidator();
        ~DateTimeValidator();
        bool validate(const String& dateTime) const;

};
#endif
