

#ifndef _CEGUIPushButton_h_
#define _CEGUIPushButton_h_

#include "CEGUIBase.h"
#include "elements/CEGUIButtonBase.h"
#include "elements/CEGUIPushButtonProperties.h"
#include "CEGUIRenderableImage.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif


namespace CEGUI
{

class CEGUIEXPORT PushButton : public ButtonBase
{
public:
	static const String EventNamespace;				


	
	
	static const String EventClicked;					

	
	
	PushButton(const String& type, const String& name);


	
	virtual ~PushButton(void);

    
	
	bool	isStandardImageryEnabled(void) const;


	
	bool	isCustomImageryAutoSized(void) const;

    
	const RenderableImage*	getNormalImage(void) const;

	
	const RenderableImage*	getHoverImage(void) const;

	
	const RenderableImage*	getPushedImage(void) const;

	
	const RenderableImage*	getDisabledImage(void) const;

    
    float   getTextXOffset(void) const;

	
	void	setStandardImageryEnabled(bool setting);

	
	void	setCustomImageryAutoSized(bool setting);

	
	void	setNormalImage(const RenderableImage* image);

	
	void	setHoverImage(const RenderableImage* image);

	
	void	setPushedImage(const RenderableImage* image);

	
	void	setDisabledImage(const RenderableImage* image);

    
    void   setTextXOffset(float offset);

	
	virtual bool	isActive(void) const {	return d_active; }
	
	
	void resizeWithText();

protected:
	
	
	virtual void	onClicked(WindowEventArgs& e);


	
	virtual void	onMouseButtonUp(MouseEventArgs& e);
    virtual void    onSized(WindowEventArgs& e);


	

	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"PushButton")	return true;
		return ButtonBase::testClassName_impl(class_name);
	}


    
    
    bool	d_autoscaleImages;				
    bool	d_useStandardImagery;			
    bool	d_useNormalImage;				
    bool	d_useHoverImage;				
    bool	d_usePushedImage;				
    bool	d_useDisabledImage;				

    
    RenderableImage		d_normalImage;		
    RenderableImage		d_hoverImage;		
    RenderableImage		d_pushedImage;		
    RenderableImage		d_disabledImage;	

    
    float d_textXOffset;		

private:
    
    static PushButtonProperties::NormalImage    d_normalImageProperty;
    static PushButtonProperties::PushedImage    d_pushedImageProperty;
    static PushButtonProperties::HoverImage     d_hoverImageProperty;
    static PushButtonProperties::DisabledImage  d_disabledImageProperty;
    static PushButtonProperties::UseStandardImagery d_useStandardImageryProperty;
    static PushButtonProperties::TextXOffset    d_textXOffsetProperty;

    
    void	addPushButtonProperties(void);
};


} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
