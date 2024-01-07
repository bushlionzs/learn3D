

#ifndef _CEGUIMultiLineEditbox_h_
#define _CEGUIMultiLineEditbox_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "CEGUIFont.h"
#include "elements/CEGUIMultiLineEditboxProperties.h"
#include "elements/CEGUIEditBoxInterface.h"

#include <vector>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT MultiLineEditbox : public Window, public EditboxInterface
{
public:
	static const String EventNamespace;				


	
	
	static const String EventReadOnlyModeChanged;			
	static const String EventWordWrapModeChanged;			
	static const String EventMaximumTextLengthChanged;	
	static const String EventCaratMoved;					
	static const String EventTextSelectionChanged;		
	static const String EventEditboxFull;					
	static const String EventVertScrollbarModeChanged;	
	static const String EventHorzScrollbarModeChanged;	

	
	static const argb_t	DefaultNormalTextColour;			
	static const argb_t	DefaultSelectedTextColour;			
	static const argb_t	DefaultNormalSelectionColour;		
	static const argb_t	DefaultInactiveSelectionColour;		


	
	
	virtual bool	hasInputFocus(void) const;


	
	bool	isReadOnly(void) const		{return d_readOnly;}

	bool	isLostFocus(void) const		{return d_lostFocus;}
	
	size_t	getCaratIndex(void) const		{return d_caratPos;}


	
	virtual size_t	getSelectionStartIndex(void) const;


	
	virtual size_t	getSelectionEndIndex(void) const;

	
	
	virtual size_t	getSelectionLength(void) const;


	
	virtual size_t	getMaxTextLength(void) const		{return d_maxTextLen;}


	
	colour	getNormalTextColour(void) const				{return d_normalTextColour;}


	
	colour	getSelectedTextColour(void) const			{return d_selectTextColour;}


	
	colour	getNormalSelectBrushColour(void) const		{return d_selectBrushColour;}


	
	colour	getInactiveSelectBrushColour(void) const	{return d_inactiveSelectBrushColour;}


	
	bool	isWordWrapped(void) const;

	bool	isWordBreaked(void) const;


	
	
	virtual void	initialise(void);


	
	void	setReadOnly(bool setting);

	void	setLostFocus(bool setting) { d_lostFocus = setting; }

	
	virtual void	setCaratIndex(size_t carat_pos);


	
	virtual void	setSelection(size_t start_pos, size_t end_pos);
	

	
	void	setMaxTextLength(size_t max_len);


	
	void	setNormalTextColour(const colour& col);


	
	void	setSelectedTextColour(const colour& col);


	
	void	setNormalSelectBrushColour(const colour& col);


	
	void	setInactiveSelectBrushColour(const colour& col);


	
	void	ensureCaratIsVisible(void);


	
	void	setWordWrapping(bool setting);
	void	setWordBreaking(bool setting);

	
	virtual bool	isTextMasked(void) const { return false; }

	
	
	MultiLineEditbox(const String& type, const String& name);


	
	virtual ~MultiLineEditbox(void);


	void			setReturnEnable( bool bReturnEnable ){ d_ReturnEnable = bReturnEnable; };

	
	virtual void	onCaratMoved(WindowEventArgs& e);

	const String	getRealText(void) const;

protected:
	
	
	virtual	Rect	getTextRenderArea(void) const		= 0;


	
	virtual Scrollbar*	createVertScrollbar(const String& name) const		= 0;
 

	
	virtual Scrollbar*	createHorzScrollbar(const String& name) const		= 0;


	
	virtual	void	cacheEditboxBaseImagery()		= 0;


	
	virtual void	cacheCaratImagery(const Rect& textArea)	= 0;


	

	
	void	cacheTextLines(const Rect& dest_area);


	
	void	formatText(void);


	
	size_t	getNextTokenLength(const String& text, size_t start_idx) const;


	virtual	void populateRenderCache();


	
	void	configureScrollbars(void);


	
	size_t	getTextIndexFromPosition(const Point& pt) const;


	
	size_t	getLineNumberFromIndex(size_t index) const;


	
	void	clearSelection(void);


	
	void	eraseSelectedText(bool modify_text = true);


	
	void	handleBackspace(void);


	
	void	handleDelete(void);


	
	void	handleCharLeft(uint sysKeys);


	
	void	handleWordLeft(uint sysKeys);


	
	void	handleCharRight(uint sysKeys);


	
	void	handleWordRight(uint sysKeys);


	
	void	handleDocHome(uint sysKeys);


	
	void	handleDocEnd(uint sysKeys);


	
	void	handleLineHome(uint sysKeys);


	
	void	handleLineEnd(uint sysKeys);


	
	void	handleLineUp(uint sysKeys);


	
	void	handleLineDown(uint sysKeys);


	
	void	handleNewLine(uint sysKeys);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if ((class_name==(const utf8*)"MultiLineEditBox") ||
			(class_name==(const utf8*)"MultiLineEditbox"))
		{
			return true;
		}

		return Window::testClassName_impl(class_name);
	}

	
    bool handle_scrollChange(const EventArgs& args);


	
	
	void	onReadOnlyChanged(WindowEventArgs& e);


	
	void	onWordWrapModeChanged(WindowEventArgs& e);


	
	void	onMaximumTextLengthChanged(WindowEventArgs& e);


	
	void	onTextSelectionChanged(WindowEventArgs& e);


	
	void	onEditboxFullEvent(WindowEventArgs& e);


	
	void	onVertScrollbarModeChanged(WindowEventArgs& e);


	
	void	onHorzScrollbarModeChanged(WindowEventArgs& e);


	
	virtual	void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseButtonUp(MouseEventArgs& e);
	virtual	void	onMouseDoubleClicked(MouseEventArgs& e);
	virtual	void	onMouseTripleClicked(MouseEventArgs& e);
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);
	virtual void	onCharacter(KeyEventArgs& e);
	virtual void	onKeyDown(KeyEventArgs& e);
	virtual void	onTextChanged(WindowEventArgs& e);
	virtual void	onSized(WindowEventArgs& e);
	virtual	void	onMouseWheel(MouseEventArgs& e);


	
	
	struct LineInfo
	{
		size_t	d_startIdx;		
		size_t	d_length;		
		float	d_extent;		
		utf32	d_color;		
		utf32	d_bakcolor;
	};


	
	bool	d_readOnly;			
	size_t	d_maxTextLen;		
	size_t	d_caratPos;			
	size_t	d_selectionStart;	
	size_t	d_selectionEnd;		
	bool	d_dragging;			
	size_t	d_dragAnchorIdx;	

	typedef	std::vector<LineInfo>	LineList;	
	static String d_lineBreakChars;	
	bool		d_wordWrap;			
	bool		d_wordBreak;			
	LineList	d_lines;			
	float		d_widestExtent;		

	
	Scrollbar*	d_vertScrollbar;	
	Scrollbar*	d_horzScrollbar;	
	bool	d_forceVertScroll;		
	bool	d_forceHorzScroll;		

	
	const Image*	d_selectionBrush;	

	
	colour	d_normalTextColour;				
	colour	d_selectTextColour;				
	colour	d_selectBrushColour;			
	colour	d_inactiveSelectBrushColour;	

	bool    d_ReturnEnable;
	bool	d_lostFocus;

private:
	
	static MultiLineEditboxProperties::ReadOnly					d_readOnlyProperty;
	static MultiLineEditboxProperties::WordWrap					d_wordWrapProperty;
	static MultiLineEditboxProperties::WordBreak				d_wordBreakProperty;
	static MultiLineEditboxProperties::CaratIndex				d_caratIndexProperty;
	static MultiLineEditboxProperties::SelectionStart			d_selectionStartProperty;
	static MultiLineEditboxProperties::SelectionLength			d_selectionLengthProperty;
	static MultiLineEditboxProperties::MaxTextLength			d_maxTextLengthProperty;
	static MultiLineEditboxProperties::NormalTextColour			d_normalTextColourProperty;
	static MultiLineEditboxProperties::SelectedTextColour		d_selectedTextColourProperty;
	static MultiLineEditboxProperties::ActiveSelectionColour	d_activeSelectionColourProperty;
	static MultiLineEditboxProperties::InactiveSelectionColour	d_inactiveSelectionColourProperty;
	static MultiLineEditboxProperties::OnReturnEnable			d_ReturnEnableProperty;
	static MultiLineEditboxProperties::LostFocus				d_lostFocusProperty;


	
	void	addMultiLineEditboxProperties(void);
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
