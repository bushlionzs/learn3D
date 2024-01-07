

#ifndef _CEGUIString_h_
#define _CEGUIString_h_

#include "CEGUIBase.h"
#include <string>
#include <string.h>
#include <stdexcept>


namespace CEGUI
{
#define STR_QUICKBUFF_SIZE	32
	
	typedef		uint8	utf8;
	typedef     uint16  utf16;
	typedef		uint32	utf32;
	

class CEGUIEXPORT String
{
public:
	
	typedef		utf32			value_type;					
	typedef		size_t			size_type;					
	typedef		ptrdiff_t		difference_type;			
	typedef		utf32&			reference;					
	typedef		const utf32&	const_reference;			
	typedef		utf32*			pointer;					
	typedef		const utf32*	const_pointer;				

	static const size_type		npos;						

private:
	
	size_type	d_cplength;			
	size_type	d_reserve;			

	mutable utf8*		d_encodedbuff;		
	mutable size_type	d_encodeddatlen;	
	mutable size_type	d_encodedbufflen;	
	utf32		d_quickbuff[STR_QUICKBUFF_SIZE];	
	utf32*		d_buffer;							


	mutable wchar_t*     d_unicodebuff;
	mutable size_type    d_unicodebufflen;



public:
	
	
#if defined(_MSC_VER) && (_MSC_VER <= 1200)
	class const_iterator : public std::iterator<std::random_access_iterator_tag, utf32>
#else
	class const_iterator : public std::iterator<std::random_access_iterator_tag, utf32, std::ptrdiff_t, const utf32*, const utf32&>
#endif
	{

	public:
		
		
		
		const utf32*	d_ptr;


		
		
		
		const_iterator(void)
		{
			d_ptr = 0;
		}
		const_iterator(const_pointer ptr)
		{
			d_ptr = ptr;
		}

		const_reference	operator*() const
		{
			return *d_ptr;
		}

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#	pragma warning (push)
#	pragma warning (disable : 4284)
#endif
		const_pointer	operator->() const		
		{
			return &**this;
		}

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#	pragma warning (pop)
#endif

		const_iterator&	operator++()
		{
			++d_ptr;
			return *this;
		}

		const_iterator	operator++(int)		
		{
			const_iterator temp = *this;
			++*this;
			return temp;
		}

		const_iterator&	operator--()
		{
			--d_ptr;
			return *this;
		}

		const_iterator	operator--(int)		
		{
			const_iterator temp = *this;
			--*this;
			return temp;
		}

		const_iterator& operator+=(difference_type offset)
		{
			d_ptr += offset;
			return *this;
		}

		const_iterator operator+(difference_type offset) const
		{
			const_iterator temp = *this;
			return temp += offset;
		}

		const_iterator& operator-=(difference_type offset)
		{
			return *this += -offset;
		}

		const_iterator operator-(difference_type offset) const
		{
			const_iterator temp = *this;
			return temp -= offset;
		}

		difference_type operator-(const const_iterator& iter) const
		{
			return d_ptr - iter.d_ptr;
		}

		const_reference operator[](difference_type offset) const
		{
			return *(*this + offset);
		}

		bool operator==(const const_iterator& iter) const
		{
			return d_ptr == iter.d_ptr;
		}

		bool operator!=(const const_iterator& iter) const
		{
			return !(*this == iter);
		}

		bool operator<(const const_iterator& iter) const
		{
			return d_ptr < iter.d_ptr;
		}

		bool operator>(const const_iterator& iter) const
		{
			return (!(iter < *this));
		}

		bool operator<=(const const_iterator& iter) const
		{
			return (!(iter < *this));
		}

		bool operator>=(const const_iterator& iter) const
		{
			return (!(*this < iter));
		}

		friend const_iterator operator+(difference_type offset, const const_iterator& iter)
		{
			return iter + offset;
		}

	};

	
	class iterator : public const_iterator
	{
	public:
		iterator(void) {}
		iterator(pointer ptr) : const_iterator(ptr) {}


		reference operator*() const
		{
			return ((reference)**(const_iterator *)this);
		}

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#	pragma warning (push)
#	pragma warning (disable : 4284)
#endif

		pointer operator->() const
		{
			return &**this;
		}

#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#	pragma warning (pop)
#endif

		iterator& operator++()
		{
			++this->d_ptr;
			return *this;
		}

		iterator operator++(int)
		{
			iterator temp = *this;
			++*this;
			return temp;
		}

		iterator& operator--()
		{
			--this->d_ptr;
			return *this;
		}

		iterator operator--(int)
		{
			iterator temp = *this;
			--*this;
			return temp;
		}

		iterator& operator+=(difference_type offset)
		{
			this->d_ptr += offset;
			return *this;
		}

		iterator operator+(difference_type offset) const
		{
			iterator temp = *this;
			return temp + offset;
		}

		iterator& operator-=(difference_type offset)
		{
			return *this += -offset;
		}

		iterator operator-(difference_type offset) const
		{
			iterator temp = *this;
			return temp -= offset;
		}

		difference_type operator-(const const_iterator& iter) const
		{
			return ((const_iterator)*this - iter);
		}

		reference operator[](difference_type offset) const
		{
			return *(*this + offset);
		}

		friend iterator operator+(difference_type offset, const iterator& iter)
		{
			return iter + offset;
		}

	};

	
#if defined(_MSC_VER) && ((_MSC_VER <= 1200) || ((_MSC_VER <= 1300) && defined(_STLPORT_VERSION)))
	typedef	std::reverse_iterator<const_iterator, const_pointer, const_reference, difference_type>	const_reverse_iterator;
#else
	typedef	std::reverse_iterator<const_iterator>	const_reverse_iterator;
#endif

	
#if defined(_MSC_VER) && ((_MSC_VER <= 1200) || ((_MSC_VER <= 1300) && defined(_STLPORT_VERSION)))
	typedef std::reverse_iterator<iterator, pointer, reference, difference_type>			reverse_iterator;
#else
	typedef std::reverse_iterator<iterator>			reverse_iterator;
#endif

public:
    
    struct FastLessCompare
    {
        bool operator() (const String& a, const String& b) const
        {
            const size_t la = a.length();
            const size_t lb = b.length();
            if (la == lb)
                return (memcmp(a.ptr(), b.ptr(), la*sizeof(utf32)) < 0);
            return (la < lb);
        }
    };

public:
	
	
	
	
	String(void)
	{
		init();
	}

	
	~String(void);

	
	
	
	
	String(const String& str)
	{
		init();
		assign(str);
	}
	

	
	String(const String& str, size_type str_idx, size_type str_num = npos)
	{
		init();
		assign(str, str_idx, str_num);
	}

	
	
	
	
	String(const std::string& std_str)
	{
		init();
		assign(std_str);
	}
		
	
	String(const std::string& std_str, size_type str_idx, size_type str_num = npos)
	{
		init();
		assign(std_str, str_idx, str_num);
	}


	
	
	
	
	String(const utf8* utf8_str)
	{
		init();
		assign(utf8_str);
	}

	
	String(const utf8* utf8_str, size_type chars_len)
	{
		init();
		assign(utf8_str, chars_len);
	}

	
	
	
	
	String(size_type num, utf32 code_point)
	{
		init();
		assign(num, code_point);
	}

	
	
	
	
	
	String(const_iterator iter_beg, const_iterator iter_end)
	{
		init();
		append(iter_beg, iter_end);
	}


	
	
	
	
	String(const char* cstr)
	{
		init();
		assign(cstr);
	}

	
	String(const char* chars, size_type chars_len)
	{
		init();
		assign(chars, chars_len);
	}


	
	
	
	
	size_type	size(void) const
	{
		return d_cplength;
	}

	
	size_type	length(void) const
	{
		return d_cplength;
	}

	
	bool	empty(void) const
	{
		return	(d_cplength == 0);
	}

	
	static size_type	max_size(void)
	{
		return (((size_type)-1) / sizeof(utf32));
	}

	
	
	
	
	
	
	size_type capacity(void) const
	{
		return d_reserve - 1;
	}

	
	
	void	reserve(size_type num = 0)
	{
		if (num == 0)
			trim();
		else
			grow(num);
	}

	
	
	
	
	int		compare(const String& str) const
	{
		return compare(0, d_cplength, str);
	}

	
	int		compare(size_type idx, size_type len, const String& str, size_type str_idx = 0, size_type str_len = npos) const
	{
		if ((d_cplength < idx) || (str.d_cplength < str_idx))
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if ((len == npos) || (idx + len > d_cplength))
			len = d_cplength - idx;

		if ((str_len == npos) || (str_idx + str_len > str.d_cplength))
			str_len = str.d_cplength - str_idx;

		int val = (len == 0) ? 0 : utf32_comp_utf32(&ptr()[idx], &str.ptr()[str_idx], (len < str_len) ? len : str_len);

		return (val != 0) ? ((val < 0) ? -1 : 1) : (len < str_len) ? -1 : (len == str_len) ? 0 : 1;
	}


	
	int		compare(const std::string& std_str) const
	{
		return compare(0, d_cplength, std_str);
	}


	
	int		compare(size_type idx, size_type len, const std::string& std_str, size_type str_idx = 0, size_type str_len = npos) const
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (std_str.size() < str_idx)
			throw std::out_of_range("Index is out of range for std::string");

		if ((len == npos) || (idx + len > d_cplength))
			len = d_cplength - idx;

		if ((str_len == npos) || (str_idx + str_len > std_str.size()))
			str_len = (size_type)std_str.size() - str_idx;

		int val = (len == 0) ? 0 : utf32_comp_char(&ptr()[idx], &std_str.c_str()[str_idx], (len < str_len) ? len : str_len);

		return (val != 0) ? ((val < 0) ? -1 : 1) : (len < str_len) ? -1 : (len == str_len) ? 0 : 1;
	}


	
	int		compare(const utf8* utf8_str) const
	{
		return compare(0, d_cplength, utf8_str, encoded_size(utf8_str));
	}


	
	int		compare(size_type idx, size_type len, const utf8* utf8_str) const
	{
		return compare(idx, len, utf8_str, encoded_size(utf8_str));
	}

	
	int		compare(size_type idx, size_type len, const utf8* utf8_str, size_type str_cplen) const
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (str_cplen == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		if ((len == npos) || (idx + len > d_cplength))
			len = d_cplength - idx;

		int val = (len == 0) ? 0 : utf32_comp_utf8(&ptr()[idx], utf8_str, (len < str_cplen) ? len : str_cplen);

		return (val != 0) ? ((val < 0) ? -1 : 1) : (len < str_cplen) ? -1 : (len == str_cplen) ? 0 : 1;
	}


	
	int		compare(const char* cstr) const
	{
		return compare(0, d_cplength, cstr, strlen(cstr));
	}


	
	int		compare(size_type idx, size_type len, const char* cstr) const
	{
		return compare(idx, len, cstr, strlen(cstr));
	}


	
	int		compare(size_type idx, size_type len, const char* chars, size_type chars_len) const
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (chars_len == npos)
			throw std::length_error("Length for char array can not be 'npos'");

		if ((len == npos) || (idx + len > d_cplength))
			len = d_cplength - idx;

		int val = (len == 0) ? 0 : utf32_comp_char(&ptr()[idx], chars, (len < chars_len) ? len : chars_len);

		return (val != 0) ? ((val < 0) ? -1 : 1) : (len < chars_len) ? -1 : (len == chars_len) ? 0 : 1;
	}


	
	
	
	
	reference	operator[](size_type idx)
	{
		return (ptr()[idx]);
	}

	
	value_type	operator[](size_type idx) const
	{
		return ptr()[idx];
	}

	
	reference	at(size_type idx)
	{
		if (d_cplength <= idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		return ptr()[idx];
	}

	
	const_reference	at(size_type idx) const
	{
		if (d_cplength <= idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		return ptr()[idx];
	}


	
	
	
	
	const char* c_str(void) const
	{
		return (const char*)build_utf8_buff();
	}

	
	const utf8* data(void) const
	{
		return build_utf8_buff();
	}

	wchar_t* unicode() const
	{
		return build_unicode_buff();
	}

	wchar_t* build_unicode_buff() const;

	
	
	
	size_type	copy(utf8* buf, size_type len = npos, size_type idx = 0) const
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (len == npos)
			len = d_cplength;

		return encode(&ptr()[idx], buf, npos, len);
	}

	
	
	
	
	
	size_type	utf8_stream_len(size_type num = npos, size_type idx = 0) const
	{
		using namespace std;

		if (d_cplength < idx)
			throw out_of_range("Index was out of range for CEGUI::String object");

		size_type	maxlen = d_cplength - idx;

		return encoded_size(&ptr()[idx], std::min(num, maxlen));
	}

	
	
	
	
	String&	operator=(const String& str)
	{
		return assign(str);
	}

	
	String&	assign(const String& str, size_type str_idx = 0, size_type str_num = npos)
	{
		if (str.d_cplength < str_idx)
			throw std::out_of_range("Index was out of range for CEGUI::String object");

		if (str_num == npos)
			str_num = str.d_cplength - str_idx;
		
		//syq:对输入参数校验，防止拷贝buffer越界.
		if(str_idx + str_num > str.length())
			str_num = str.length() - str_idx;
			
		grow(str_num);
		setlen(str_num);
		memcpy(ptr(), &str.ptr()[str_idx], str_num * sizeof(utf32));
		
		return *this;
	}

	
	String&	operator=(const std::string& std_str)
	{
		return assign(std_str);
	}

	
	String&	assign(const std::string& std_str, size_type str_idx = 0, size_type str_num = npos)
	{
		if (std_str.size() < str_idx)
			throw std::out_of_range("Index was out of range for std::string object");

		if (str_num == npos)
			str_num = (size_type)std_str.size() - str_idx;

		grow(str_num);
		setlen(str_num);

		while(str_num--)
		{
			((*this)[str_num]) = static_cast<utf32>(static_cast<unsigned char>(std_str[str_num + str_idx]));
		}

		return *this;
	}

	
	String&	operator=(const utf8* utf8_str)
	{
		return assign(utf8_str, utf_length(utf8_str));
	}

	
	String&	assign(const utf8* utf8_str)
	{
		return assign(utf8_str, utf_length(utf8_str));
	}

	
	String&	assign(const utf8* utf8_str, size_type str_num)
	{
		if (str_num == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		size_type enc_sze = encoded_size(utf8_str, str_num);

		grow(enc_sze);
		encode(utf8_str, ptr(), d_reserve, str_num);
		setlen(enc_sze);
		return *this;
	}

	
	String&	operator=(utf32 code_point)
	{
		return assign(1, code_point);
	}

	
	String&	assign(size_type num, utf32 code_point)
	{
		if (num == npos)
			throw std::length_error("Code point count can not be 'npos'");

		grow(num);
		setlen(num);
		utf32* p = ptr();

		while(num--)
			*p++ = code_point;

		return *this;
	}


	
	String&	operator=(const char* cstr)
	{
		return assign(cstr, strlen(cstr));
	}


	
	String&	assign(const char* cstr)
	{
		return assign(cstr, strlen(cstr));
	}


	
	String&	assign(const char* chars, size_type chars_len)
	{
		grow(chars_len);
		utf32* pt = ptr();

		for (size_type i = 0; i < chars_len; ++i)
		{
			*pt++ = static_cast<utf32>(static_cast<unsigned char>(*chars++));
		}

		setlen(chars_len);
		return *this;
	}


	
	void	swap(String& str)
	{
		size_type	temp_len	= d_cplength;
		d_cplength = str.d_cplength;
		str.d_cplength = temp_len;

		size_type	temp_res	= d_reserve;
		d_reserve = str.d_reserve;
		str.d_reserve = temp_res;

		utf32*		temp_buf	= d_buffer;
		d_buffer = str.d_buffer;
		str.d_buffer = temp_buf;

		
		if (temp_res <= STR_QUICKBUFF_SIZE)
		{
			utf32		temp_qbf[STR_QUICKBUFF_SIZE];

			memcpy(temp_qbf, d_quickbuff, STR_QUICKBUFF_SIZE * sizeof(utf32));
			memcpy(d_quickbuff, str.d_quickbuff, STR_QUICKBUFF_SIZE * sizeof(utf32));
			memcpy(str.d_quickbuff, temp_qbf, STR_QUICKBUFF_SIZE * sizeof(utf32));
		}

	}

	
	
	
	
	String&	operator+=(const String& str)
	{
		return append(str);
	}

	
	String& append(const String& str, size_type str_idx = 0, size_type str_num = npos)
	{
		if (str.d_cplength < str_idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (str_num == npos)
			str_num = str.d_cplength - str_idx;

		grow(d_cplength + str_num);
		memcpy(&ptr()[d_cplength], &str.ptr()[str_idx], str_num * sizeof(utf32));
		setlen(d_cplength + str_num);
		return *this;
	}


	
	String&	operator+=(const std::string& std_str)
	{
		return append(std_str);
	}

	
	String& append(const std::string& std_str, size_type str_idx = 0, size_type str_num = npos)
	{
		if (std_str.size() < str_idx)
			throw std::out_of_range("Index is out of range for std::string");

		if (str_num == npos)
			str_num = (size_type)std_str.size() - str_idx;

		size_type newsze = d_cplength + str_num;

		grow(newsze);
		utf32* pt = &ptr()[newsze-1];

		while(str_num--)
			*pt-- = static_cast<utf32>(static_cast<unsigned char>(std_str[str_num]));

		setlen(newsze);
		return *this;
	}


	
	String&	operator+=(const utf8* utf8_str)
	{
		return append(utf8_str, utf_length(utf8_str));
	}

	
	String& append(const utf8* utf8_str)
	{
		return append(utf8_str, utf_length(utf8_str));
	}


	
	String& append(const utf8* utf8_str, size_type len)
	{
		if (len == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		size_type encsz = encoded_size(utf8_str, len);
		size_type newsz = d_cplength + encsz;

		grow(newsz);
		encode(utf8_str, &ptr()[d_cplength], encsz, len);
		setlen(newsz);

		return *this;
	}


	
	String& operator+=(utf32 code_point)
	{
		return append(1, code_point);
	}

	
	String& append(size_type num, utf32 code_point)
	{
		if (num == npos)
			throw std::length_error("Code point count can not be 'npos'");

		size_type newsz = d_cplength + num;
		grow(newsz);

		utf32* p = &ptr()[d_cplength];

		while(num--)
			*p++ = code_point;

		setlen(newsz);

		return *this;
	}

	
	void	push_back(utf32 code_point)
	{
		append(1, code_point);
	}

	
	String&	append(const_iterator iter_beg, const_iterator iter_end)
	{
		return replace(end(), end(), iter_beg, iter_end);
	}


	
	String&	operator+=(const char* cstr)
	{
		return append(cstr, strlen(cstr));
	}


	
	String& append(const char* cstr)
	{
		return append(cstr, strlen(cstr));
	}


	
	String& append(const char* chars, size_type chars_len)
	{
		if (chars_len == npos)
			throw std::length_error("Length for char array can not be 'npos'");

		size_type newsz = d_cplength + chars_len;

		grow(newsz);

		utf32* pt = &ptr()[newsz-1];

		while(chars_len--)
			*pt-- = static_cast<utf32>(static_cast<unsigned char>(chars[chars_len]));

		setlen(newsz);

		return *this;
	}


	
	
	
	
	String&	insert(size_type idx, const String& str)
	{
		return insert(idx, str, 0, npos);
	}

	
	String& insert(size_type idx, const String& str, size_type str_idx, size_type str_num)
	{
		if ((d_cplength < idx) || (str.d_cplength < str_idx))
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (str_num == npos)
			str_num = str.d_cplength - str_idx;

		size_type newsz = d_cplength + str_num;
		grow(newsz);
		memmove(&ptr()[idx + str_num], &ptr()[idx], (d_cplength - idx) * sizeof(utf32));
		memcpy(&ptr()[idx], &str.ptr()[str_idx], str_num * sizeof(utf32));
		setlen(newsz);

		return *this;
	}

	
	String&	insert(size_type idx, const std::string& std_str)
	{
		return insert(idx, std_str, 0, npos);
	}

	
	String& insert(size_type idx, const std::string& std_str, size_type str_idx, size_type str_num)
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (std_str.size() < str_idx)
			throw std::out_of_range("Index is out of range for std::string");

		if (str_num == npos)
			str_num = (size_type)std_str.size() - str_idx;

		size_type newsz = d_cplength + str_num;
		grow(newsz);

		memmove(&ptr()[idx + str_num], &ptr()[idx], (d_cplength - idx) * sizeof(utf32));

		utf32* pt = &ptr()[idx + str_num - 1];
		
		while(str_num--)
			*pt-- = static_cast<utf32>(static_cast<unsigned char>(std_str[str_idx + str_num]));

		setlen(newsz);

		return *this;
	}

	
	String&	insert(size_type idx, const utf8* utf8_str)
	{
		return insert(idx, utf8_str, utf_length(utf8_str));
	}

	
	String& insert(size_type idx, const utf8* utf8_str, size_type len)
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (len == npos)
			throw std::length_error("Length of utf8 encoded string can not be 'npos'");

		size_type encsz = encoded_size(utf8_str, len);
		size_type newsz = d_cplength + encsz;

		grow(newsz);
		memmove(&ptr()[idx + encsz], &ptr()[idx], (d_cplength - idx) * sizeof(utf32));
		encode(utf8_str, &ptr()[idx], encsz, len);
		setlen(newsz);

		return *this;
	}

	
	String& insert(size_type idx, size_type num, utf32 code_point)
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (num == npos)
			throw std::length_error("Code point count can not be 'npos'");

		size_type newsz = d_cplength + num;
		grow(newsz);

		memmove(&ptr()[idx + num], &ptr()[idx], (d_cplength - idx) * sizeof(utf32));

		utf32* pt = &ptr()[idx + num - 1];

		while(num--)
			*pt-- = code_point;

		setlen(newsz);

		return *this;
	}

	
	void insert(iterator pos, size_type num, utf32 code_point)
	{
		insert(safe_iter_dif(pos, begin()), num, code_point);
	}

	
	iterator insert(iterator pos, utf32 code_point)
	{
		insert(pos, 1, code_point);
		return pos;
	}

	
	void	insert(iterator iter_pos, const_iterator iter_beg, const_iterator iter_end)
	{
		replace(iter_pos, iter_pos, iter_beg, iter_end);
	}


	
	String&	insert(size_type idx, const char* cstr)
	{
		return insert(idx, cstr, strlen(cstr));
	}


	
	String& insert(size_type idx, const char* chars, size_type chars_len)
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (chars_len == npos)
			throw std::length_error("Length of char array can not be 'npos'");

		size_type newsz = d_cplength + chars_len;

		grow(newsz);
		memmove(&ptr()[idx + chars_len], &ptr()[idx], (d_cplength - idx) * sizeof(utf32));

		utf32* pt = &ptr()[idx + chars_len - 1];

		while(chars_len--)
			*pt-- = static_cast<utf32>(static_cast<unsigned char>(chars[chars_len]));

		setlen(newsz);

		return *this;
	}


	
	
	
	
	void	clear(void)
	{
		setlen(0);
		trim();
	}

	
	String& erase(void)
	{
		clear();
		return *this;
	}

	
	String&	erase(size_type idx)
	{
		return erase(idx, 1);
	}

	
	String& erase(size_type idx, size_type len = npos)
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range foe CEGUI::String");

		if (len == npos)
			len = d_cplength - idx;

		size_type newsz = d_cplength - len;

		memmove(&ptr()[idx], &ptr()[idx + len], (d_cplength - idx - len) * sizeof(utf32));
		setlen(newsz);
		return	*this;
	}

	
	String& erase(iterator pos)
	{
		return erase(safe_iter_dif(pos, begin()), 1);
	}

	
	String& erase(iterator iter_beg, iterator iter_end)
	{
		return erase(safe_iter_dif(iter_beg, begin()), safe_iter_dif(iter_end, iter_beg));
	}

	
	
	
	
	void	resize(size_type num)
	{
		resize(num, utf32());
	}

	
	size_type mbcs_length(void) const
	{
		const char* code = c_str();
		const char* code_dead_end = code+utf_length((utf8*)code);

		size_type ret = 0;
		while(code!=0 && *code!=0 && *code!=10 && code < code_dead_end)
		{
			if(	(*code >= 0x20 &&	
				*code <= 0x7f0) )	
						
			{
				ret++;
				code++;
			}
			else
			{
				ret+=2;
				code+=3;
			}
		}
		return ret;
	}

	
	void	resize(size_type num, utf32 code_point)
	{
		if (num < d_cplength)
		{
			setlen(num);
		}
		else
		{
			append(num - d_cplength, code_point);
		}

	}

	
	
	
	
	String& replace(size_type idx, size_type len, const String& str)
	{
		return replace(idx, len, str, 0, npos);
	}

	
	String& replace(iterator iter_beg, iterator iter_end, const String& str)
	{
		return replace(safe_iter_dif(iter_beg, begin()), safe_iter_dif(iter_end, iter_beg), str, 0, npos);
	}

	
	String& replace(size_type idx, size_type len, const String& str, size_type str_idx, size_type str_num)
	{
		if ((d_cplength < idx) || (str.d_cplength < str_idx))
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (((str_idx + str_num) > str.d_cplength) || (str_num == npos))
			str_num = str.d_cplength - str_idx;

		if (((len + idx) > d_cplength) || (len == npos))
			len = d_cplength - idx;

		size_type newsz = d_cplength + str_num - len;

		grow(newsz);

		if ((idx + len) < d_cplength)
			memmove(&ptr()[idx + str_num], &ptr()[len + idx], (d_cplength - idx - len) * sizeof(utf32));

		memcpy(&ptr()[idx], &str.ptr()[str_idx], str_num * sizeof(utf32));
		setlen(newsz);

		return *this;
	}


	
	String& replace(size_type idx, size_type len, const std::string& std_str)
	{
		return replace(idx, len, std_str, 0, npos);
	}

	
	String& replace(iterator iter_beg, iterator iter_end, const std::string& std_str)
	{
		return replace(safe_iter_dif(iter_beg, begin()), safe_iter_dif(iter_end, iter_beg), std_str, 0, npos);
	}

	
	String& replace(size_type idx, size_type len, const std::string& std_str, size_type str_idx, size_type str_num)
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (std_str.size() < str_idx)
			throw std::out_of_range("Index is out of range for std::string");

		if (((str_idx + str_num) > std_str.size()) || (str_num == npos))
			str_num = (size_type)std_str.size() - str_idx;

		if (((len + idx) > d_cplength) || (len == npos))
			len = d_cplength - idx;

		size_type newsz = d_cplength + str_num - len;

		grow(newsz);

		if ((idx + len) < d_cplength)
			memmove(&ptr()[idx + str_num], &ptr()[len + idx], (d_cplength - idx - len) * sizeof(utf32));

		utf32* pt = &ptr()[idx + str_num - 1];

		while (str_num--)
			*pt-- = static_cast<utf32>(static_cast<unsigned char>(std_str[str_idx + str_num]));

		setlen(newsz);

		return *this;
	}


	
	String& replace(size_type idx, size_type len, const utf8* utf8_str)
	{
		return replace(idx, len, utf8_str, utf_length(utf8_str));
	}

	
	String& replace(iterator iter_beg, iterator iter_end, const utf8* utf8_str)
	{
		return replace(iter_beg, iter_end, utf8_str, utf_length(utf8_str));
	}

	
	String& replace(size_type idx, size_type len, const utf8* utf8_str, size_type str_len)
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (str_len == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		if (((len + idx) > d_cplength) || (len == npos))
			len = d_cplength - idx;

		size_type encsz = encoded_size(utf8_str, str_len);
		size_type newsz = d_cplength + encsz - len;

		grow(newsz);

		if ((idx + len) < d_cplength)
			memmove(&ptr()[idx + encsz], &ptr()[len + idx], (d_cplength - idx - len) * sizeof(utf32));

		encode(utf8_str, &ptr()[idx], encsz, str_len);

		setlen(newsz);
		return *this;
	}

	
	String& replace(iterator iter_beg, iterator iter_end, const utf8* utf8_str, size_type str_len)
	{
		return replace(safe_iter_dif(iter_beg, begin()), safe_iter_dif(iter_end, iter_beg), utf8_str, str_len);
	}

	
	String& replace(size_type idx, size_type len, size_type num, utf32 code_point)
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (num == npos)
			throw std::length_error("Code point count can not be 'npos'");

		if (((len + idx) > d_cplength) || (len == npos))
			len = d_cplength - idx;

		size_type newsz = d_cplength + num - len;

		grow(newsz);

		if ((idx + len) < d_cplength)
			memmove(&ptr()[idx + num], &ptr()[len + idx], (d_cplength - idx - len) * sizeof(utf32));

		utf32* pt = &ptr()[idx + num - 1];

		while (num--)
			*pt-- = code_point;

		setlen(newsz);

		return *this;
	}

	
	String& replace(iterator iter_beg, iterator iter_end, size_type num, utf32 code_point)
	{
		return replace(safe_iter_dif(iter_beg, begin()), safe_iter_dif(iter_end, iter_beg), num, code_point);
	}


	
	String& replace(iterator iter_beg, iterator iter_end, const_iterator iter_newBeg, const_iterator iter_newEnd)
	{
		if (iter_beg == iter_end)
		{
			erase(safe_iter_dif(iter_beg, begin()), safe_iter_dif(iter_end, iter_beg));
		}
		else
		{
			size_type str_len = safe_iter_dif(iter_newEnd, iter_newBeg);
			size_type idx = safe_iter_dif(iter_beg, begin());
			size_type len = safe_iter_dif(iter_end, iter_beg);

			if ((len + idx) > d_cplength)
				len = d_cplength - idx;

			size_type newsz = d_cplength + str_len - len;

			grow(newsz);

			if ((idx + len) < d_cplength)
				memmove(&ptr()[idx + str_len], &ptr()[len + idx], (d_cplength - idx - len) * sizeof(utf32));

			memcpy(&ptr()[idx], iter_newBeg.d_ptr, str_len * sizeof(utf32));
			setlen(newsz);
		}

		return *this;
	}


	
	String& replace(size_type idx, size_type len, const char* cstr)
	{
		return replace(idx, len, cstr, strlen(cstr));
	}


	
	String& replace(iterator iter_beg, iterator iter_end, const char* cstr)
	{
		return replace(iter_beg, iter_end, cstr, strlen(cstr));
	}


	
	String& replace(size_type idx, size_type len, const char* chars, size_type chars_len)
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for CEGUI::String");

		if (chars_len == npos)
			throw std::length_error("Length for the char array can not be 'npos'");

		if (((len + idx) > d_cplength) || (len == npos))
			len = d_cplength - idx;

		size_type newsz = d_cplength + chars_len - len;

		grow(newsz);

		if ((idx + len) < d_cplength)
			memmove(&ptr()[idx + chars_len], &ptr()[len + idx], (d_cplength - idx - len) * sizeof(utf32));

		utf32* pt = &ptr()[idx + chars_len - 1];

		while (chars_len--)
			*pt-- = static_cast<utf32>(static_cast<unsigned char>(chars[chars_len]));

		setlen(newsz);
		return *this;
	}


	
	String& replace(iterator iter_beg, iterator iter_end, const char* chars, size_type chars_len)
	{
		return replace(safe_iter_dif(iter_beg, begin()), safe_iter_dif(iter_end, iter_beg), chars, chars_len);
	}


	
	
	
	
	size_type	find(utf32 code_point, size_type idx = 0) const
	{
		if (idx < d_cplength)
		{
			const utf32* pt = &ptr()[idx];

			while (idx < d_cplength)
			{
				if (*pt++ == code_point)
					return idx;

				++idx;
			}

		}

		return npos;
	}

	
	size_type	rfind(utf32 code_point, size_type idx = npos) const
	{
		if (idx >= d_cplength)
			idx = d_cplength - 1;

		if (d_cplength > 0)
		{
			const utf32* pt = &ptr()[idx];

			do
			{
				if (*pt-- == code_point)
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}

	
	
	
	
	size_type	find(const String& str, size_type idx = 0) const
	{
		if ((str.d_cplength == 0) && (idx < d_cplength))
			return idx;

		if (idx < d_cplength)
		{
			
			while (d_cplength - idx >= str.d_cplength)
			{
				if (0 == compare(idx, str.d_cplength, str))
					return idx;

				++idx;
			}

		}

		return npos;
	}

	
	size_type	rfind(const String& str, size_type idx = npos) const
	{
		if (str.d_cplength == 0)
			return (idx < d_cplength) ? idx : d_cplength;

		if (str.d_cplength <= d_cplength)
		{
			if (idx > (d_cplength - str.d_cplength))
				idx = d_cplength - str.d_cplength;

			do
			{
				if (0 == compare(idx, str.d_cplength, str))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}

	
	size_type	find(const std::string& std_str, size_type idx = 0) const
	{
		std::string::size_type sze = std_str.size();

		if ((sze == 0) && (idx < d_cplength))
			return idx;

		if (idx < d_cplength)
		{
			
			while (d_cplength - idx >= sze)
			{
				if (0 == compare(idx, (size_type)sze, std_str))
					return idx;

				++idx;
			}

		}

		return npos;
	}

	
	size_type	rfind(const std::string& std_str, size_type idx = npos) const
	{
		std::string::size_type sze = std_str.size();

		if (sze == 0)
			return (idx < d_cplength) ? idx : d_cplength;

		if (sze <= d_cplength)
		{
			if (idx > (d_cplength - sze))
				idx = d_cplength - sze;

			do
			{
				if (0 == compare(idx, (size_type)sze, std_str))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}

	
	size_type	find(const utf8* utf8_str, size_type idx = 0) const
	{
		return find(utf8_str, idx, utf_length(utf8_str));
	}

	
	size_type	rfind(const utf8* utf8_str, size_type idx = npos) const
	{
		return rfind(utf8_str, idx, utf_length(utf8_str));
	}

	
	size_type	find(const utf8* utf8_str, size_type idx, size_type str_len) const
	{
		if (str_len == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		size_type sze = encoded_size(utf8_str, str_len);

		if ((sze == 0) && (idx < d_cplength))
			return idx;

		if (idx < d_cplength)
		{
			
			while (d_cplength - idx >= sze)
			{
				if (0 == compare(idx, sze, utf8_str, sze))
					return idx;

				++idx;
			}

		}

		return npos;
	}

	
	size_type	rfind(const utf8* utf8_str, size_type idx, size_type str_len) const
	{
		if (str_len == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		size_type sze = encoded_size(utf8_str, str_len);

		if (sze == 0)
			return (idx < d_cplength) ? idx : d_cplength;

		if (sze <= d_cplength)
		{
			if (idx > (d_cplength - sze))
				idx = d_cplength - sze;

			do
			{
				if (0 == compare(idx, sze, utf8_str, sze))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}


	
	size_type	find(const char* cstr, size_type idx = 0) const
	{
		return find(cstr, idx, strlen(cstr));
	}


	
	size_type	rfind(const char* cstr, size_type idx = npos) const
	{
		return rfind(cstr, idx, strlen(cstr));
	}


	
	size_type	find(const char* chars, size_type idx, size_type chars_len) const
	{
		if (chars_len == npos)
			throw std::length_error("Length for char array can not be 'npos'");

		if ((chars_len == 0) && (idx < d_cplength))
			return idx;

		if (idx < d_cplength)
		{
			
			while (d_cplength - idx >= chars_len)
			{
				if (0 == compare(idx, chars_len, chars, chars_len))
					return idx;

				++idx;
			}

		}

		return npos;
	}


	
	size_type	rfind(const char* chars, size_type idx, size_type chars_len) const
	{
		if (chars_len == npos)
			throw std::length_error("Length for char array can not be 'npos'");

		if (chars_len == 0)
			return (idx < d_cplength) ? idx : d_cplength;

		if (chars_len <= d_cplength)
		{
			if (idx > (d_cplength - chars_len))
				idx = d_cplength - chars_len;

			do
			{
				if (0 == compare(idx, chars_len, chars, chars_len))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}


	
	
	
	
	size_type	find_first_of(const String& str, size_type idx = 0) const
	{
		if (idx < d_cplength)
		{
			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos != str.find(*pt++))
					return idx;

			} while (++idx != d_cplength);

		}

		return npos;
	}

	
	size_type	find_first_not_of(const String& str, size_type idx = 0) const
	{
		if (idx < d_cplength)
		{
			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos == str.find(*pt++))
					return idx;

			} while (++idx != d_cplength);

		}

		return npos;
	}


	
	size_type	find_first_of(const std::string& std_str, size_type idx = 0) const
	{
		if (idx < d_cplength)
		{
			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos != find_codepoint(std_str, *pt++))
					return idx;

			} while (++idx != d_cplength);

		}

		return npos;
	}

	
	size_type	find_first_not_of(const std::string& std_str, size_type idx = 0) const
	{
		if (idx < d_cplength)
		{
			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos == find_codepoint(std_str, *pt++))
					return idx;

			} while (++idx != d_cplength);

		}

		return npos;
	}


	
	size_type	find_first_of(const utf8* utf8_str, size_type idx = 0) const
	{
		return find_first_of(utf8_str, idx, utf_length(utf8_str));
	}

	
	size_type	find_first_not_of(const utf8* utf8_str, size_type idx = 0) const
	{
		return find_first_not_of(utf8_str, idx, utf_length(utf8_str));
	}

	
	size_type	find_first_of(const utf8* utf8_str, size_type idx, size_type str_len) const
	{
		if (str_len == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		if (idx < d_cplength)
		{
			size_type encsze = encoded_size(utf8_str, str_len);

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos != find_codepoint(utf8_str, encsze, *pt++))
					return idx;

			} while (++idx != d_cplength);

		}

		return npos;
	}

	
	size_type	find_first_not_of(const utf8* utf8_str, size_type idx, size_type str_len) const
	{
		if (str_len == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		if (idx < d_cplength)
		{
			size_type encsze = encoded_size(utf8_str, str_len);

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos == find_codepoint(utf8_str, encsze, *pt++))
					return idx;

			} while (++idx != d_cplength);

		}

		return npos;
	}


	
	size_type	find_first_of(utf32 code_point, size_type idx = 0) const
	{
		return find(code_point, idx);
	}

	
	size_type	find_first_not_of(utf32 code_point, size_type idx = 0) const
	{
		if (idx < d_cplength)
		{
			do
			{
				if ((*this)[idx] != code_point)
					return idx;

			} while(idx++ < d_cplength);

		}

		return npos;
	}


	
	size_type	find_first_of(const char* cstr, size_type idx = 0) const
	{
		return find_first_of(cstr, idx, strlen(cstr));
	}


	
	size_type	find_first_not_of(const char* cstr, size_type idx = 0) const
	{
		return find_first_not_of(cstr, idx, strlen(cstr));
	}


	
	size_type	find_first_of(const char* chars, size_type idx, size_type chars_len) const
	{
		if (chars_len == npos)
			throw std::length_error("Length for char array can not be 'npos'");

		if (idx < d_cplength)
		{
			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos != find_codepoint(chars, chars_len, *pt++))
					return idx;

			} while (++idx != d_cplength);

		}

		return npos;
	}


	
	size_type	find_first_not_of(const char* chars, size_type idx, size_type chars_len) const
	{
		if (chars_len == npos)
			throw std::length_error("Length for char array can not be 'npos'");

		if (idx < d_cplength)
		{
			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos == find_codepoint(chars, chars_len, *pt++))
					return idx;

			} while (++idx != d_cplength);

		}

		return npos;
	}


	
	
	
	
	size_type	find_last_of(const String& str, size_type idx = npos) const
	{
		if (d_cplength > 0)
		{
			if (idx >= d_cplength)
				idx = d_cplength - 1;

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos != str.find(*pt--))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}

	
	size_type	find_last_not_of(const String& str, size_type idx = npos) const
	{
		if (d_cplength > 0)
		{
			if (idx >= d_cplength)
				idx = d_cplength - 1;

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos == str.find(*pt--))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}


	
	size_type	find_last_of(const std::string& std_str, size_type idx = npos) const
	{
		if (d_cplength > 0)
		{
			if (idx >= d_cplength)
				idx = d_cplength - 1;

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos != find_codepoint(std_str, *pt--))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}

	
	size_type	find_last_not_of(const std::string& std_str, size_type idx = npos) const
	{
		if (d_cplength > 0)
		{
			if (idx >= d_cplength)
				idx = d_cplength - 1;

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos == find_codepoint(std_str, *pt--))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}


	
	size_type	find_last_of(const utf8* utf8_str, size_type idx = npos) const
	{
		return find_last_of(utf8_str, idx, utf_length(utf8_str));
	}

	
	size_type	find_last_not_of(const utf8* utf8_str, size_type idx = npos) const
	{
		return find_last_not_of(utf8_str, idx, utf_length(utf8_str));
	}

	
	size_type	find_last_of(const utf8* utf8_str, size_type idx, size_type str_len) const
	{
		if (str_len == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		if (d_cplength > 0)
		{
			if (idx >= d_cplength)
				idx = d_cplength - 1;

			size_type encsze = encoded_size(utf8_str, str_len);

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos != find_codepoint(utf8_str, encsze, *pt--))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}

	
	size_type	find_last_not_of(const utf8* utf8_str, size_type idx, size_type str_len) const
	{
		if (str_len == npos)
			throw std::length_error("Length for utf8 encoded string can not be 'npos'");

		if (d_cplength > 0)
		{
			if (idx >= d_cplength)
				idx = d_cplength - 1;

			size_type encsze = encoded_size(utf8_str, str_len);

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos == find_codepoint(utf8_str, encsze, *pt--))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}


	
	size_type	find_last_of(utf32 code_point, size_type idx = npos) const
	{
		return rfind(code_point, idx);
	}

	
	size_type	find_last_not_of(utf32 code_point, size_type idx = npos) const
	{
		if (d_cplength > 0)
		{
			if (idx >= d_cplength)
				idx = d_cplength - 1;

			do
			{
				if ((*this)[idx] != code_point)
					return idx;

			} while(idx-- != 0);

		}

		return npos;
	}


	
	size_type	find_last_of(const char* cstr, size_type idx = npos) const
	{
		return find_last_of(cstr, idx, strlen(cstr));
	}


	
	size_type	find_last_not_of(const char* cstr, size_type idx = npos) const
	{
		return find_last_not_of(cstr, idx, strlen(cstr));
	}


	
	size_type	find_last_of(const char* chars, size_type idx, size_type chars_len) const
	{
		if (chars_len == npos)
			throw std::length_error("Length for char array can not be 'npos'");

		if (d_cplength > 0)
		{
			if (idx >= d_cplength)
				idx = d_cplength - 1;

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos != find_codepoint(chars, chars_len, *pt--))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}


	
	size_type	find_last_not_of(const char* chars, size_type idx, size_type chars_len) const
	{
		if (chars_len == npos)
			throw std::length_error("Length for char array can not be 'npos'");

		if (d_cplength > 0)
		{
			if (idx >= d_cplength)
				idx = d_cplength - 1;

			const utf32* pt = &ptr()[idx];

			do
			{
				if (npos == find_codepoint(chars, chars_len, *pt--))
					return idx;

			} while (idx-- != 0);

		}

		return npos;
	}


	
	
	
	
	String	substr(size_type idx = 0, size_type len = npos) const
	{
		if (d_cplength < idx)
			throw std::out_of_range("Index is out of range for this CEGUI::String");

		return String(*this, idx, len);
	}

	
	
	
	
	iterator		begin(void)
	{
		return iterator(ptr());
	}

	
	const_iterator	begin(void) const
	{
		return const_iterator(ptr());
	}

	
	iterator		end(void)
	{
		return iterator(&ptr()[d_cplength]);
	}

	
	const_iterator	end(void) const
	{
		return const_iterator(&ptr()[d_cplength]);
	}

	
	reverse_iterator		rbegin(void)
	{
		return reverse_iterator(end());
	}

	
	const_reverse_iterator	rbegin(void) const
	{
		return const_reverse_iterator(end());
	}

	
	reverse_iterator		rend(void)
	{
		return reverse_iterator(begin());
	}

	
	const_reverse_iterator	rend(void) const
	{
		return const_reverse_iterator(begin());
	}

private:
	
	

	
	
	
    bool	grow(size_type new_size);

	
    void	trim(void);

	
	void	setlen(size_type len)
	{
		d_cplength = len;
		ptr()[len] = (utf32)(0);
	}

	
	utf32*	ptr(void)
	{
		return (d_reserve > STR_QUICKBUFF_SIZE) ? d_buffer : d_quickbuff;
	}

	
	const utf32*	ptr(void) const
	{
		return (d_reserve > STR_QUICKBUFF_SIZE) ? d_buffer : d_quickbuff;
	}

	
	void	init(void)
	{
		d_reserve			= STR_QUICKBUFF_SIZE;
		d_encodedbuff		= 0;
		d_encodedbufflen	= 0;
		d_encodeddatlen		= 0;
		setlen(0);

		d_unicodebuff = 0;
		d_unicodebufflen = 0;
	}

	
	bool	inside(utf32* inptr)
	{
		if (inptr < ptr() || ptr() + d_cplength <= inptr)
			return false;
		else
			return true;
	}

	
	size_type safe_iter_dif(const const_iterator& iter1, const const_iterator& iter2) const
	{
		return (iter1.d_ptr == 0) ? 0 : (iter1 - iter2);
	}
	
	
	
	
	
	
	size_type encode(const utf32* src, utf8* dest, size_type dest_len, size_type src_len = 0) const
	{
		
		if (src_len == 0)
		{
			src_len = utf_length(src);
		}

		size_type destCapacity = dest_len;

		
		for (uint idx = 0; idx < src_len; ++idx)
		{
			utf32	cp = src[idx];

			
			if (destCapacity < encoded_size(cp))
			{
				break;
			}

			if (cp < 0x80)
			{
				*dest++ = (utf8)cp;
				--destCapacity;
			}
			else if (cp < 0x0800)
			{
				*dest++ = (utf8)((cp >> 6) | 0xC0);
				*dest++ = (utf8)((cp & 0x3F) | 0x80);
				destCapacity -= 2;
			}
			else if (cp < 0x10000)
			{
				*dest++ = (utf8)((cp >> 12) | 0xE0);
				*dest++ = (utf8)(((cp >> 6) & 0x3F) | 0x80);
				*dest++ = (utf8)((cp & 0x3F) | 0x80);
				destCapacity -= 3;
			}
			else
			{
				*dest++ = (utf8)((cp >> 18) | 0xF0);
				*dest++ = (utf8)(((cp >> 12) & 0x3F) | 0x80);
				*dest++ = (utf8)(((cp >> 6) & 0x3F) | 0x80);
				*dest++ = (utf8)((cp & 0x3F) | 0x80);
				destCapacity -= 4;
			}

		}

		return dest_len - destCapacity;
	}

	size_type encode(const utf8* src, utf32* dest, size_type dest_len, size_type src_len = 0) const
	{
		
		if (src_len == 0)
		{
			src_len = utf_length(src);
		}

		size_type destCapacity = dest_len;

		
		for (uint idx = 0; ((idx < src_len) && (destCapacity > 0));)
		{
			utf32	cp;
			utf8	cu = src[idx++];

			if (cu < 0x80)
			{
				cp = (utf32)(cu);
			}
			else if (cu < 0xE0)
			{
				cp = ((cu & 0x1F) << 6);
				cp |= (src[idx++] & 0x3F);
			}
			else if (cu < 0xF0)
			{
				cp = ((cu & 0x0F) << 12);
				cp |= ((src[idx++] & 0x3F) << 6);
				cp |= (src[idx++] & 0x3F);
			}
			else
			{
				cp = ((cu & 0x07) << 18);
				cp |= ((src[idx++] & 0x3F) << 12);
				cp |= ((src[idx++] & 0x3F) << 6);
				cp |= (src[idx++] & 0x3F);
			}

			*dest++ = cp;
			--destCapacity;
		}

		return dest_len - destCapacity;
	}

	
	size_type encoded_size(utf32 code_point) const
	{
		if (code_point < 0x80)
			return 1;
		else if (code_point < 0x0800)
			return 2;
		else if (code_point < 0x10000)
			return 3;
		else
			return 4;
	}

	
	size_type encoded_size(const utf32* buf) const
	{
		return encoded_size(buf, utf_length(buf));
	}

	
	size_type encoded_size(const utf32* buf, size_type len) const
	{
		size_type count = 0;

		while (len--)
		{
			count += encoded_size(*buf++);
		}

		return count;
	}

	
	size_type encoded_size(const utf8* buf) const
	{
		return encoded_size(buf, utf_length(buf));
	}

	
	size_type encoded_size(const utf8* buf, size_type len) const
	{
		utf8 tcp;
		size_type count = 0;

		while (len--)
		{
			tcp = *buf++;
			++count;

			if (tcp < 0x80)
			{
			}
			else if (tcp < 0xE0)
			{
				--len;
				++buf;
			}
			else if (tcp < 0xF0)
			{
				len -= 2;
				buf += 2;
			}
			else
			{
				len -= 2;
				buf += 3;
			}

		}

		return count;
	}

	
	size_type utf_length(const utf8* utf8_str) const
	{
		size_type cnt = 0;
		while (*utf8_str++)
			cnt++;

		return cnt;
	}

	
	size_type utf_length(const utf32* utf32_str) const
	{
		size_type cnt = 0;
		while (*utf32_str++)
			cnt++;

		return cnt;
	}

	
    utf8* build_utf8_buff(void) const;

	
	int	utf32_comp_utf32(const utf32* buf1, const utf32* buf2, size_type cp_count) const
	{
		if (!cp_count)
			return 0;

		while ((--cp_count) && (*buf1 == *buf2))
			buf1++, buf2++;
		
		return *buf1 - *buf2;
	}

	
	int utf32_comp_char(const utf32* buf1, const char* buf2, size_type cp_count) const
	{
		if (!cp_count)
			return 0;

		while ((--cp_count) && (*buf1 == static_cast<utf32>(static_cast<unsigned char>(*buf2))))
			buf1++, buf2++;

		return *buf1 - static_cast<utf32>(static_cast<unsigned char>(*buf2));
	}

	
	int utf32_comp_utf8(const utf32* buf1, const utf8* buf2, size_type cp_count) const
	{
		if (!cp_count)
			return 0;

		utf32	cp;
		utf8	cu;

		do
		{
			cu = *buf2++;

			if (cu < 0x80)
			{
				cp = (utf32)(cu);
			}
			else if (cu < 0xE0)
			{
				cp = ((cu & 0x1F) << 6);
				cp |= (*buf2++ & 0x3F);
			}
			else if (cu < 0xF0)
			{
				cp = ((cu & 0x0F) << 12);
				cp |= ((*buf2++ & 0x3F) << 6);
				cp |= (*buf2++ & 0x3F);
			}
			else
			{
				cp = ((cu & 0x07) << 18);
				cp |= ((*buf2++ & 0x3F) << 12);
				cp |= ((*buf2++ & 0x3F) << 6);
				cp |= (*buf2++ & 0x3F);
			}

		} while ((*buf1++ == cp) && (--cp_count));

		return (*--buf1) - cp;
	}

	
	size_type find_codepoint(const std::string& str, utf32 code_point) const
	{
		size_type idx = 0, sze = (size_type)str.size();

		while (idx != sze)
		{
			if (code_point == static_cast<utf32>(static_cast<unsigned char>(str[idx])))
				return idx;

			++idx;
		}

		return npos;
	}

	
	size_type find_codepoint(const utf8* str, size_type len, utf32 code_point) const 
	{
		size_type idx = 0;

		utf32	cp;
		utf8	cu;

		while (idx != len) {
			cu = *str++;

			if (cu < 0x80)
			{
				cp = (utf32)(cu);
			}
			else if (cu < 0xE0)
			{
				cp = ((cu & 0x1F) << 6);
				cp |= (*str++ & 0x3F);
			}
			else if (cu < 0xF0)
			{
				cp = ((cu & 0x0F) << 12);
				cp |= ((*str++ & 0x3F) << 6);
				cp |= (*str++ & 0x3F);
			}
			else
			{
				cp = ((cu & 0x07) << 18);
				cp |= ((*str++ & 0x3F) << 12);
				cp |= ((*str++ & 0x3F) << 6);
				cp |= (*str++ & 0x3F);
			}

			if (code_point == cp)
				return idx;

			++idx;
		}

		return npos;
	}


	
	size_type find_codepoint(const char* chars, size_type chars_len, utf32 code_point) const
	{
		for (size_type idx = 0; idx != chars_len; ++idx)
		{
			if (code_point == static_cast<utf32>(static_cast<unsigned char>(chars[idx])))
				return idx;
		}

		return npos;
	}

};






bool CEGUIEXPORT	operator==(const String& str1, const String& str2);


bool CEGUIEXPORT	operator==(const String& str, const std::string& std_str);


bool CEGUIEXPORT	operator==(const std::string& std_str, const String& str);


bool CEGUIEXPORT	operator==(const String& str, const utf8* utf8_str);


bool CEGUIEXPORT	operator==(const utf8* utf8_str, const String& str);


bool CEGUIEXPORT	operator!=(const String& str1, const String& str2);


bool CEGUIEXPORT	operator!=(const String& str, const std::string& std_str);


bool CEGUIEXPORT	operator!=(const std::string& std_str, const String& str);


bool CEGUIEXPORT	operator!=(const String& str, const utf8* utf8_str);


bool CEGUIEXPORT	operator!=(const utf8* utf8_str, const String& str);


bool CEGUIEXPORT	operator<(const String& str1, const String& str2);


bool CEGUIEXPORT	operator<(const String& str, const std::string& std_str);


bool CEGUIEXPORT	operator<(const std::string& std_str, const String& str);


bool CEGUIEXPORT	operator<(const String& str, const utf8* utf8_str);


bool CEGUIEXPORT	operator<(const utf8* utf8_str, const String& str);


bool CEGUIEXPORT	operator>(const String& str1, const String& str2);


bool CEGUIEXPORT	operator>(const String& str, const std::string& std_str);


bool CEGUIEXPORT	operator>(const std::string& std_str, const String& str);


bool CEGUIEXPORT	operator>(const String& str, const utf8* utf8_str);


bool CEGUIEXPORT	operator>(const utf8* utf8_str, const String& str);


bool CEGUIEXPORT	operator<=(const String& str1, const String& str2);


bool CEGUIEXPORT	operator<=(const String& str, const std::string& std_str);


bool CEGUIEXPORT	operator<=(const std::string& std_str, const String& str);


bool CEGUIEXPORT	operator<=(const String& str, const utf8* utf8_str);


bool CEGUIEXPORT	operator<=(const utf8* utf8_str, const String& str);


bool CEGUIEXPORT	operator>=(const String& str1, const String& str2);


bool CEGUIEXPORT	operator>=(const String& str, const std::string& std_str);


bool CEGUIEXPORT	operator>=(const std::string& std_str, const String& str);


bool CEGUIEXPORT	operator>=(const String& str, const utf8* utf8_str);


bool CEGUIEXPORT	operator>=(const utf8* utf8_str, const String& str);


bool CEGUIEXPORT	operator==(const String& str, const char* c_str);


bool CEGUIEXPORT	operator==(const char* c_str, const String& str);


bool CEGUIEXPORT	operator!=(const String& str, const char* c_str);


bool CEGUIEXPORT	operator!=(const char* c_str, const String& str);


bool CEGUIEXPORT	operator<(const String& str, const char* c_str);


bool CEGUIEXPORT	operator<(const char* c_str, const String& str);


bool CEGUIEXPORT	operator>(const String& str, const char* c_str);


bool CEGUIEXPORT	operator>(const char* c_str, const String& str);


bool CEGUIEXPORT	operator<=(const String& str, const char* c_str);


bool CEGUIEXPORT	operator<=(const char* c_str, const String& str);


bool CEGUIEXPORT	operator>=(const String& str, const char* c_str);


bool CEGUIEXPORT	operator>=(const char* c_str, const String& str);





String CEGUIEXPORT	operator+(const String& str1, const String& str2);


String CEGUIEXPORT	operator+(const String& str, const std::string& std_str);


String CEGUIEXPORT	operator+(const std::string& std_str, const String& str);


String CEGUIEXPORT	operator+(const String& str, const utf8* utf8_str);


String CEGUIEXPORT	operator+(const utf8* utf8_str, const String& str);


String CEGUIEXPORT	operator+(const String& str, utf32 code_point);


String CEGUIEXPORT	operator+(utf32 code_point, const String& str);


String CEGUIEXPORT	operator+(const String& str, const char* c_str);


String CEGUIEXPORT	operator+(const char* c_str, const String& str);





CEGUIEXPORT std::ostream& operator<<(std::ostream& s, const String& str);






void CEGUIEXPORT swap(String& str1, String& str2);


} 


#endif	
