

#ifndef _CEGUICheckbox_h_
#define _CEGUICheckbox_h_

#include "CEGUIBase.h"
#include "elements/CEGUIButtonBase.h"
#include "elements/CEGUICheckboxProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT Checkbox : public ButtonBase
{
public:
	static const String EventNamespace;				

	
	
	static const String EventCheckStateChanged;			


	
	
	bool	isSelected(void) const						{return d_selected;}


	
	
	void	setSelected(bool select);


	
	
	Checkbox(const String& type, const String& name);


	
	virtual ~Checkbox(void);


protected:
	
	
	virtual void	onSelectStateChange(WindowEventArgs& e);


	
	virtual void	onMouseButtonUp(MouseEventArgs& e);


	

	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Checkbox")	return true;
		return ButtonBase::testClassName_impl(class_name);
	}


	
	bool		d_selected;					

private:
	
	static CheckboxProperties::Selected	d_selectedProperty;


	
	void	addCheckboxProperties(void);
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
