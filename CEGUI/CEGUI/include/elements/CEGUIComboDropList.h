

#ifndef _CEGUIComboDropList_h_
#define _CEGUIComboDropList_h_

#include "elements/CEGUIListbox.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT ComboDropList : public Listbox
{
public:
	static const String EventNamespace;				


	
	
	static const String EventListSelectionAccepted;		


	
	virtual void	initialise(void);


	
	void	setArmed(bool setting)		{ d_armed = setting; }


	
	bool	isArmed(void) const		{ return d_armed; }


	
	void	setAutoArmEnabled(bool setting)		{ d_autoArm = setting; }


	
	bool	isAutoArmEnabled(void) const		{ return d_autoArm; }

	
	void	resizeSelf(void);

	
	void repositionSelf(Window *);
	
	
	ComboDropList(const String& type, const String& name);


	
	virtual ~ComboDropList(void);


protected:

	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"ComboDropList")	return true;
		return Listbox::testClassName_impl(class_name);
	}
	
	
	
	void	onListSelectionAccepted(WindowEventArgs& e);


	
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseButtonUp(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);
	virtual void	onActivated(ActivationEventArgs& e);
	virtual void	onSized(WindowEventArgs& e);


	
	bool	d_autoArm;		
	bool	d_armed;		
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
