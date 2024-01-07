

#ifndef _CEGUITextItem_h_
#define _CEGUITextItem_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIItemEntry.h"
#include "elements/CEGUITextItemProperties.h"
#include "CEGUIFont.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT TextItem : public ItemEntry
{
public:
	
	static const colour		DefaultTextColour;		


	
	
	TextFormatting getTextFormatting() const		{return d_textFormatting;}


	
    float   getTextXOffset(void) const				{return d_textXOffset;}


	
	colour getTextColour(void) const			{return d_textColour;}


	
	
	void setTextFormatting(TextFormatting format)	{d_textFormatting=format;}


	
	void setTextColour(const colour& col)			{d_textColour=col;}


	
    void   setTextXOffset(float offset)				{d_textXOffset=offset;}


	
	
	virtual Size getItemPixelSize(void);


	
	
	TextItem(const String& type, const String& name);


	
	virtual ~TextItem(void);


protected:
	

	
	
	virtual void	onTextChanged(WindowEventArgs& e);


	
    virtual void populateRenderCache();


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"TextItem")	return true;
		return ItemEntry::testClassName_impl(class_name);
	}


	

	
	colour d_textColour;				
	TextFormatting d_textFormatting;	

	
    float d_textXOffset;		


private:
	
	static TextItemProperties::TextColour		d_textColourProperty;
	static TextItemProperties::TextFormatting	d_textFormattingProperty;
	static TextItemProperties::TextXOffset		d_textXOffsetProperty;

	
	void	addTextItemProperties(void);
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif


#endif	
