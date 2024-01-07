

#include "CEGUIString.h"

#include <iostream>


namespace CEGUI
{


const String::size_type String::npos = (String::size_type)(-1);





String::~String(void)
{
	if (d_reserve > STR_QUICKBUFF_SIZE)
	{
		delete[] d_buffer;
	}
	if (d_encodedbufflen > 0)
	{
		delete[] d_encodedbuff;
	}

	if(d_unicodebuff)
	{
		delete [] d_unicodebuff;
		d_unicodebuff = 0;
		d_unicodebufflen = 0;
	}

    
}

bool String::grow(size_type new_size)
{
    
    if (max_size() <= new_size)
        std::length_error("Resulting CEGUI::String would be too big");

    
    ++new_size;

    if (new_size > d_reserve)
    {
        utf32* temp = new utf32[new_size];

        if (d_reserve > STR_QUICKBUFF_SIZE)
        {
            memcpy(temp, d_buffer, (d_cplength + 1) * sizeof(utf32));
            delete[] d_buffer;
        }
        else
        {
            memcpy(temp, d_quickbuff, (d_cplength + 1) * sizeof(utf32));
        }

        d_buffer = temp;
        d_reserve = new_size;

        return true;
    }

    return false;
}


void String::trim(void)
{
    size_type min_size = d_cplength + 1;

    
    if ((d_reserve > STR_QUICKBUFF_SIZE) && (d_reserve > min_size))
    {
            
        if (min_size <= STR_QUICKBUFF_SIZE)
        {
            memcpy(d_quickbuff, d_buffer, min_size * sizeof(utf32));
            delete[] d_buffer;
            d_reserve = STR_QUICKBUFF_SIZE;
        }
        
        else
        {
            utf32* temp = new utf32[min_size];
            memcpy(temp, d_buffer, min_size * sizeof(utf32));
            delete[] d_buffer;
            d_buffer = temp;
            d_reserve = min_size;
        }

    }

}


utf8* String::build_utf8_buff(void) const
{
    size_type buffsize = encoded_size(ptr(), d_cplength) + 1;

    if (buffsize > d_encodedbufflen) {

        if (d_encodedbufflen > 0)
        {
            delete[] d_encodedbuff;
        }

        d_encodedbuff = new utf8[buffsize];
        d_encodedbufflen = buffsize;
    }

    encode(ptr(), d_encodedbuff, buffsize, d_cplength);

    
    d_encodedbuff[buffsize-1] = ((utf8)0);
    d_encodeddatlen = buffsize;

    return d_encodedbuff;
}




wchar_t* String::build_unicode_buff() const
{
	size_type src_len = utf_length(ptr());
	size_type new_len = src_len + 1;
	if(new_len > d_unicodebufflen)
	{
		if(d_unicodebuff)
			delete [] d_unicodebuff;
		d_unicodebuff = new wchar_t[new_len];
		d_unicodebufflen = new_len;
	}
	uint idx, i = 0;
	for ( idx = 0; idx < src_len; ++idx)
	{
		utf32	cp = ptr()[idx];
		if(cp & 0xff000000)
		{
			d_unicodebuff[i++] = L'^';//control symbol
			continue;
		}
		d_unicodebuff[i++] = (cp & 0xffff);
	}
	d_unicodebuff[i] = L'\0';
	return d_unicodebuff;
}



bool	operator==(const String& str1, const String& str2)
{
	return (str1.compare(str2) == 0);
}

bool	operator==(const String& str, const std::string& std_str)
{
	return (str.compare(std_str) == 0);
}

bool	operator==(const std::string& std_str, const String& str)
{
	return (str.compare(std_str) == 0);
}

bool	operator==(const String& str, const utf8* utf8_str)
{
	return (str.compare(utf8_str) == 0);
}

bool	operator==(const utf8* utf8_str, const String& str)
{
	return (str.compare(utf8_str) == 0);
}


bool	operator!=(const String& str1, const String& str2)
{
	return (str1.compare(str2) != 0);
}

bool	operator!=(const String& str, const std::string& std_str)
{
	return (str.compare(std_str) != 0);
}

bool	operator!=(const std::string& std_str, const String& str)
{
	return (str.compare(std_str) != 0);
}

bool	operator!=(const String& str, const utf8* utf8_str)
{
	return (str.compare(utf8_str) != 0);
}

bool	operator!=(const utf8* utf8_str, const String& str)
{
	return (str.compare(utf8_str) != 0);
}


bool	operator<(const String& str1, const String& str2)
{
	return (str1.compare(str2) < 0);
}

bool	operator<(const String& str, const std::string& std_str)
{
	return (str.compare(std_str) < 0);
}

bool	operator<(const std::string& std_str, const String& str)
{
	return (str.compare(std_str) >= 0);
}

bool	operator<(const String& str, const utf8* utf8_str)
{
	return (str.compare(utf8_str) < 0);
}

bool	operator<(const utf8* utf8_str, const String& str)
{
	return (str.compare(utf8_str) >= 0);
}


bool	operator>(const String& str1, const String& str2)
{
	return (str1.compare(str2) > 0);
}

bool	operator>(const String& str, const std::string& std_str)
{
	return (str.compare(std_str) > 0);
}

bool	operator>(const std::string& std_str, const String& str)
{
	return (str.compare(std_str) <= 0);
}

bool	operator>(const String& str, const utf8* utf8_str)
{
	return (str.compare(utf8_str) > 0);
}

bool	operator>(const utf8* utf8_str, const String& str)
{
	return (str.compare(utf8_str) <= 0);
}


bool	operator<=(const String& str1, const String& str2)
{
	return (str1.compare(str2) <= 0);
}

bool	operator<=(const String& str, const std::string& std_str)
{
	return (str.compare(std_str) <= 0);
}

bool	operator<=(const std::string& std_str, const String& str)
{
	return (str.compare(std_str) >= 0);
}

bool	operator<=(const String& str, const utf8* utf8_str)
{
	return (str.compare(utf8_str) <= 0);
}

bool	operator<=(const utf8* utf8_str, const String& str)
{
	return (str.compare(utf8_str) >= 0);
}


bool	operator>=(const String& str1, const String& str2)
{
	return (str1.compare(str2) >= 0);
}

bool	operator>=(const String& str, const std::string& std_str)
{
	return (str.compare(std_str) >= 0);
}

bool	operator>=(const std::string& std_str, const String& str)
{
	return (str.compare(std_str) <= 0);
}

bool	operator>=(const String& str, const utf8* utf8_str)
{
	return (str.compare(utf8_str) >= 0);
}

bool	operator>=(const utf8* utf8_str, const String& str)
{
	return (str.compare(utf8_str) <= 0);
}




bool operator==(const String& str, const char* c_str)
{
	return (str.compare(c_str) == 0);
}

bool operator==(const char* c_str, const String& str)
{
	return (str.compare(c_str) == 0);
}

bool operator!=(const String& str, const char* c_str)
{
	return (str.compare(c_str) != 0);
}

bool operator!=(const char* c_str, const String& str)
{
	return (str.compare(c_str) != 0);
}

bool operator<(const String& str, const char* c_str)
{
	return (str.compare(c_str) < 0);
}

bool operator<(const char* c_str, const String& str)
{
	return (str.compare(c_str) >= 0);
}

bool operator>(const String& str, const char* c_str)
{
	return (str.compare(c_str) > 0);
}

bool operator>(const char* c_str, const String& str)
{
	return (str.compare(c_str) <= 0);
}

bool operator<=(const String& str, const char* c_str)
{
	return (str.compare(c_str) <= 0);
}

bool operator<=(const char* c_str, const String& str)
{
	return (str.compare(c_str) >= 0);
}

bool operator>=(const String& str, const char* c_str)
{
	return (str.compare(c_str) >= 0);
}

bool operator>=(const char* c_str, const String& str)
{
	return (str.compare(c_str) <= 0);
}




String	operator+(const String& str1, const String& str2)
{
	String temp(str1);
	temp.append(str2);
	return temp;
}

String	operator+(const String& str, const std::string& std_str)
{
	String temp(str);
	temp.append(std_str);
	return temp;
}

String	operator+(const std::string& std_str, const String& str)
{
	String temp(std_str);
	temp.append(str);
	return temp;
}

String	operator+(const String& str, const utf8* utf8_str)
{
	String temp(str);
	temp.append(utf8_str);
	return temp;
}

String	operator+(const utf8* utf8_str, const String& str)
{
	String temp(utf8_str);
	temp.append(str);
	return temp;
}

String	operator+(const String& str, utf32 code_point)
{
	String temp(str);
	temp.append(1, code_point);
	return temp;
}

String	operator+(utf32 code_point, const String& str)
{
	String temp(1, code_point);
	temp.append(str);
	return temp;
}

String operator+(const String& str, const char* c_str)
{
	String tmp(str);
	tmp.append(c_str);
	return tmp;
}

String operator+(const char* c_str, const String& str)
{
	String tmp(c_str);
	tmp.append(str);
	return tmp;
}




std::ostream& operator<<(std::ostream& s, const String& str)
{
	return s << str.c_str();
}





void	swap(String& str1, String& str2)
{
	str1.swap(str2);
}


} 
