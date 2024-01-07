

#ifndef _CEGUIRadioButton_h_
#define _CEGUIRadioButton_h_

#include "CEGUIBase.h"
#include "elements/CEGUIButtonBase.h"
#include "elements/CEGUIRadioButtonProperties.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT RadioButton : public ButtonBase
{
public:
	static const String EventNamespace;				


	
	
	static const String EventSelectStateChanged;			


	 
	
	bool	isSelected(void) const				{return d_selected;}

	
	
	ulong	getGroupID(void) const				{return d_groupID;}


	
	RadioButton*	getSelectedButtonInGroup(void) const;


	
	
	void	setSelected(bool select);

	
	
	void	setGroupID(ulong group);


	
	RadioButton(const String& type, const String& name);
	virtual ~RadioButton(void);


protected:
	

	
	void	deselectOtherButtonsInGroup(void) const;


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"RadioButton")	return true;
		return ButtonBase::testClassName_impl(class_name);
	}


	
	
	virtual void	onSelectStateChanged(WindowEventArgs& e);


	
	virtual void	onMouseButtonUp(MouseEventArgs& e);


	
	bool		d_selected;				
	ulong		d_groupID;				


private:
	
	static RadioButtonProperties::Selected	d_selectedProperty;
	static RadioButtonProperties::GroupID	d_groupIDProperty;


	
	void	addRadioButtonProperties(void);
};


} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
