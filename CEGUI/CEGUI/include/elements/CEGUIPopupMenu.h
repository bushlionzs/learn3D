

#ifndef _CEGUIPopupMenu_h_
#define _CEGUIPopupMenu_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIPopupMenuProperties.h"
#include "elements/CEGUIMenuBase.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT PopupMenu : public MenuBase
{
public:
	static const String EventNamespace;				

	
	
	float	getFadeInTime(void) const			{return d_fadeInTime;}


	
	float	getFadeOutTime(void) const			{return d_fadeOutTime;}


	
	
	void	setFadeInTime(float fadetime)		{d_fadeInTime=fadetime;}


	
	void	setFadeOutTime(float fadetime)		{d_fadeOutTime=fadetime;}

	
	void	openPopupMenu(void);


	
	void	closePopupMenu(void);

	
	Window* addPopItem(ItemEntry* pItem,const String& text);
	void removePopItem(size_t positon);

	
	void removeAllPopItem();


	
	
	PopupMenu(const String& type, const String& name);


	
	virtual ~PopupMenu(void);


protected:
	
	
	virtual void	updateSelf(float elapsed);


	
	virtual void	layoutItemWidgets(void);


	
	virtual Size getContentSize(void);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"PopupMenu")	return true;
		return MenuBase::testClassName_impl(class_name);
	}


	
	virtual void onAlphaChanged(WindowEventArgs& e);


	virtual void onParentSized( WindowEventArgs& e );
	
	float d_origAlpha;			

	float d_fadeElapsed;		
	float d_fadeOutTime;		
	float d_fadeInTime;			
	bool d_fading;				
	bool d_fadingOut;			

private:
	
	static PopupMenuProperties::FadeInTime	d_fadeInTimeProperty;
	static PopupMenuProperties::FadeOutTime	d_fadeOutTimeProperty;


	
	void	addPopupMenuProperties(void);
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif


#endif	
