

#include "CEGUITextUtils.h"


namespace CEGUI
{

const String	TextUtils::DefaultWhitespace		= (utf8*)" \n\t\r";
const String	TextUtils::DefaultAlphanumerical	= (utf8*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
const String	TextUtils::DefaultWrapDelimiters	= (utf8*)" \n\t\r";
const String	TextUtils::DefaultBreakDelimiters	= (utf8*)"\n\t\r";



String TextUtils::getNextWord(const String& str, String::size_type start_idx, const String& delimiters)
{
	String::size_type	word_start = str.find_first_not_of(delimiters, start_idx);

	if (word_start == String::npos)
	{
		word_start = start_idx;
	}

	

	
	
	
	

	
	return str.substr(start_idx, 1);
}



String::size_type TextUtils::getWordStartIdx(const String& str, String::size_type idx)
{
	String	temp = str.substr(0, idx);

	trimTrailingChars(temp, DefaultWhitespace);

	if (temp.length() <= 1) {
		return 0;
	}

	
	if (String::npos != DefaultAlphanumerical.find(temp[temp.length() - 1]))
	{
		idx = temp.find_last_not_of(DefaultAlphanumerical);
	}
	
	else
	{
		idx = temp.find_last_of(DefaultAlphanumerical + DefaultWhitespace);
	}

	
	if (idx == String::npos)
	{
		return 0;
	}
	else
	{
		return idx + 1;
	}

}



String::size_type TextUtils::getNextWordStartIdx(const String& str, String::size_type idx)
{
	String::size_type str_len = str.length();

	
	if ((idx >= str_len) || (str_len == 0))
	{
		return str_len;
	}

	
	if (String::npos != DefaultAlphanumerical.find(str[idx]))
	{
		
		idx = str.find_first_not_of(DefaultAlphanumerical, idx);
	}
	
	else if (String::npos == DefaultWhitespace.find(str[idx]))
	{
		
		idx = str.find_first_of(DefaultAlphanumerical + DefaultWhitespace, idx);
	}

	
	if (String::npos == idx)
	{
		idx = str_len;
	}
	else
	{
		
		if (String::npos != DefaultWhitespace.find(str[idx]))
		{
			
			idx = str.find_first_not_of(DefaultWhitespace, idx);
		}

		if (String::npos == idx)
		{
			idx = str_len;
		}

	}

	return idx;
}



void TextUtils::trimLeadingChars(String& str, const String& chars)
{
	String::size_type idx = str.find_first_not_of(chars);

	if (idx != String::npos)
	{
		str.erase(0, idx);
	}
	else
	{
		str.erase();
	}

}



void TextUtils::trimTrailingChars(String& str, const String& chars)
{
	String::size_type idx = str.find_last_not_of(chars);

	if (idx != String::npos)
	{
		str.resize(idx + 1);
	}
	else
	{
		str.erase();
	}

}

} 
