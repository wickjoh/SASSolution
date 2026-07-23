/******************************************************************************
 *
 * File Name      : DateTimeValidator.cpp
 *
 * Description    : Implementation of DateTimeValidator.
 *
 * Author         : NA
 *
 * Date           : 22-07-2026
 *
 ******************************************************************************/

#include "DateTimeValidator.hpp"


DateTimeValidator::DateTimeValidator()
{
}

DateTimeValidator::~DateTimeValidator()
{
}

bool DateTimeValidator::validate(const String& dateTime) const
{
    if (!validateLength(dateTime))
    {
        return false;
    }

    if (!validateSeparator(dateTime))
    {
        return false;
    }

    if (!validateNumeric(dateTime))
    {
        return false;
    }

    if (!validateDate(dateTime))
    {
        return false;
    }

    if (!validateTime(dateTime))
    {
        return false;
    }

    if (!validateTimeZone(dateTime))
    {
        return false;
    }

    return true;
}

bool DateTimeValidator::validateLength(const String& dateTime) const
{
    std::size_t length = dateTime.getLength();

    //TO DO : Implement Length formater or constant to remove Hard Coded values 
    if ((length != 20U) &&
        (length != 25U))
    {
        return false;
    }
    return true;
}

bool DateTimeValidator::validateSeparator(const String& dateTime) const
{
    if (dateTime[4] != '-')
    {
        return false;
    }

    if (dateTime[7] != '-')
    {
        return false;
    }

    if (dateTime[10] != 'T')
    {
        return false;
    }

    if (dateTime[13] != ':')
    {
        return false;
    }

    if (dateTime[16] != ':')
    {
        return false;
    }

    if (dateTime.getLength() == 20U)
    {
        if (dateTime[19] != 'Z')
        {
            return false;
        }
    }
    else
    {
        if ((dateTime[19] != '+') &&
            (dateTime[19] != '-'))
        {
            return false;
        }

        if (dateTime[22] != ':')
        {
            return false;
        }
    }
    return true;
}

bool DateTimeValidator::validateNumeric(const String& dateTime) const
{
    std::size_t index = Constants::ZERO;

    while (index < dateTime.getLength())
    {
        switch (index)
        {
            case 4:
            case 7:
            case 10:
            case 13:
            case 16:
                        index++;
                        continue;

            case 19:

                if (dateTime.getLength() == 20U)
                {
                    index++;
                    continue;
                }

                if ((dateTime[index] == '+') ||
                    (dateTime[index] == '-'))
                {
                    index++;
                    continue;
                }

                return false;

            case 22:

                if (dateTime.getLength() == 25U)
                {
                    index++;
                    continue;
                }

                break;

            default:
                break;
        }

        if ((dateTime[index] < '0') ||
            (dateTime[index] > '9'))
        {
            return false;
        }
        index++;
    }

    return true;
}

bool DateTimeValidator::validateDate(const String& dateTime) const
{
    int month = ((dateTime[5] - '0') * 10) +
                 (dateTime[6] - '0');

    int day = ((dateTime[8] - '0') * 10) +
               (dateTime[9] - '0');

    if ((month < 1) || (month > 12))
    {
        return false;
    }

    if ((day < 1) || (day > 31))
    {
        return false;
    }
    return true;
}

bool DateTimeValidator::validateTime(const String& dateTime) const
{
    int hour = ((dateTime[11] - '0') * 10) +
                (dateTime[12] - '0');

    int minute = ((dateTime[14] - '0') * 10) +
                  (dateTime[15] - '0');

    int second = ((dateTime[17] - '0') * 10) +
                  (dateTime[18] - '0');

    if ((hour < 0) || (hour > 23))
    {
        return false;
    }

    if ((minute < 0) || (minute > 59))
    {
        return false;
    }

    if ((second < 0) || (second > 59))
    {
        return false;
    }
    return true;
}

bool DateTimeValidator::validateTimeZone(const String& dateTime) const
{
    bool result = true;

    do 
    {
        if (dateTime.getLength() == 20U)
        {
            break;
        }

        int hour = ((dateTime[20] - '0') * 10) +
                    (dateTime[21] - '0');

        int minute = ((dateTime[23] - '0') * 10) +
                    (dateTime[24] - '0');

        if ((hour < 0) || (hour > 23))
        {
            result = false;
            break;
        }

        if ((minute < 0) || (minute > 59))
        {   
            result = false;
            break;
        }
    }while(Constants::ZERO);
    
    return result;
}