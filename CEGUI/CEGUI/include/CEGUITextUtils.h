

#ifndef _CEGUITextUtils_h_
#define _CEGUITextUtils_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"


namespace CEGUI
{

class CEGUIEXPORT TextUtils
{
public:
	
	static const String	DefaultWhitespace;		
	static const String	DefaultAlphanumerical;	
	static const String	DefaultWrapDelimiters;	
	static const String	DefaultBreakDelimiters;	


	
	
	static	String	getNextWord(const String& str, String::size_type start_idx = 0, const String& delimiters = DefaultWhitespace);


	
	static	String::size_type	getWordStartIdx(const String& str, String::size_type idx);


	
	static	String::size_type	getNextWordStartIdx(const String& str, String::size_type idx);


	
	static	void	trimLeadingChars(String& str, const String& chars);


	
	static	void	trimTrailingChars(String& str, const String& chars);


private:
	
	static	String		d_delimiters;			
	static	String		d_whitespace;			


	
	
	TextUtils(void);
	~TextUtils(void);
};

} 


#endif	
