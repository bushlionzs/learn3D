

#ifndef _CEGUIMouseCursor_h_
#define _CEGUIMouseCursor_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUISingleton.h"
#include "CEGUIVector.h"
#include "CEGUIRect.h"
#include "CEGUIEventSet.h"
#include "CEGUIInputEvent.h"
#include "CEGUIUDim.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


enum MouseCursorImage
{		
	BlankMouseCursor	= 0,		
	DefaultMouseCursor	= -1		
};



class CEGUIEXPORT MouseCursor : public EventSet, public Singleton<MouseCursor>
{
public:
	static const String EventNamespace;				

	typedef bool CursorCallback(int nCursorType);
	
	
	static const String EventImageChanged;			


	
	MouseCursor(void);


	
	~MouseCursor(void);


	
	static	MouseCursor&	getSingleton(void);


	
	static	MouseCursor*	getSingletonPtr(void);


	
	void	setImage(const String& imageset, const String& image_name);


	
	void	setImage(const Image* image);


	
	const Image*	getImage(void) const	{return d_cursorImage;}


	
	void	draw(void) const;


	
	void	setPosition(const Point& position);


	
	void	offsetPosition(const Point& offset);


	
	void	setConstraintArea(const Rect* area);


	
	void	setUnifiedConstraintArea(const URect* area);


	
	void	hide(void)		{d_visible = false;}


	
	void	show(void)		{d_visible = true;}


	
	bool	isVisible(void) const	{return d_visible;}


	
	Point	getPosition(void) const		{return Point(d_position.d_x, d_position.d_y);}


	
	Rect	getConstraintArea(void) const;


	
	const URect& getUnifiedConstraintArea(void) const;


	
	Point	getDisplayIndependantPosition(void) const;

	void	setGameCursorPointer(CursorCallback* pCursor) {d_cursorCallback = pCursor;}
	void	setGameCursor(int nCursor);


protected:
	
	
	virtual void	onImageChanged(MouseCursorEventArgs& e);


	
	
	void	addMouseCursorEvents(void);


private:
	
	
	void	constrainPosition(void);


	
	const Image*	d_cursorImage;		
	Vector3	d_position;					
	bool	d_visible;					
	URect	d_constraints;				

	CursorCallback*		d_cursorCallback; 
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
