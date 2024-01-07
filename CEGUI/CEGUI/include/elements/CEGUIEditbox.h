

#ifndef _CEGUIEditbox_h_
#define _CEGUIEditbox_h_

#include "CEGUIBase.h"
#include "CEGUIWindow.h"
#include "elements/CEGUIEditboxProperties.h"
#include "elements/CEGUIEditBoxInterface.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

struct RegexValidator;



class CEGUIEXPORT Editbox : public Window, public EditboxInterface
{
public:
	static const String EventNamespace;				


	
	
	static const argb_t	DefaultNormalTextColour;			
	static const argb_t	DefaultSelectedTextColour;			
	static const argb_t	DefaultNormalSelectionColour;		
	static const argb_t	DefaultInactiveSelectionColour;		


	
	static const String EventReadOnlyModeChanged;			
	static const String EventMaskedRenderingModeChanged;	
	static const String EventMaskCodePointChanged;		
	static const String EventValidationStringChanged;		
	static const String EventMaximumTextLengthChanged;	
	static const String EventTextInvalidated;				
	static const String EventInvalidEntryAttempted;		
	static const String EventCaratMoved;					
	static const String EventTextSelectionChanged;		
	static const String EventEditboxFull;					
	static const String EventTextAccepted;				
	static const String EventTabPressed;				


	
	
	virtual bool	hasInputFocus(void) const;


	
	bool	isReadOnly(void) const		{return d_readOnly;}

	bool	isForbidInput(void) const	{return d_forbidInput;}

	bool	isLostFocus(void) const		{return d_lostFocus;}

	
	bool	isTextMasked(void) const	{return	d_maskText;}


	
	bool	isTextValid(void) const;


	
	const String&	getValidationString(void) const		{return d_validationString;}


	
	size_t	getCaratIndex(void) const		{return d_caratPos;}


	
	virtual size_t	getSelectionStartIndex(void) const;


	
	virtual size_t	getSelectionEndIndex(void) const;

	
	
	virtual size_t	getSelectionLength(void) const;


	
	utf32	getMaskCodePoint(void) const		{return d_maskCodePoint;}


	
	virtual size_t	getMaxTextLength(void) const		{return d_maxTextLen;}


	
	colour	getNormalTextColour(void) const				{return d_normalTextColour;}


	
	colour	getSelectedTextColour(void) const			{return d_selectTextColour;}


	
	colour	getNormalSelectBrushColour(void) const		{return d_selectBrushColour;}


	
	colour	getInactiveSelectBrushColour(void) const	{return d_inactiveSelectBrushColour;}


	
	
	void	setReadOnly(bool setting);
	void	setForbidInput(bool setting) {d_forbidInput = setting; }
	void	setUseRegex(bool setting) { d_useRegex = setting; }
	void	setLostFocus(bool setting) { d_lostFocus = setting; }

	
	void	setTextMasked(bool setting);


	
	void	setValidationString(const String& validation_string);


	
	virtual void	setCaratIndex(size_t carat_pos);


	
	virtual void	setSelection(size_t start_pos, size_t end_pos);
	

	
	void	setMaskCodePoint(utf32 code_point);


	
	void	setMaxTextLength(size_t max_len);


	
	void	setNormalTextColour(const colour& col);


	
	void	setSelectedTextColour(const colour& col);


	
	void	setNormalSelectBrushColour(const colour& col);


	
	void	setInactiveSelectBrushColour(const colour& col);


	
	
	Editbox(const String& type, const String& name);


	
	virtual ~Editbox(void);


	void     addCharater( const utf32 &codepoint );

	
	void	handleBackspace(void);

	void	selectAll(void);

	virtual void	setText(const String& text);

	void	clearText( void );

protected:
	

	
	virtual	size_t	getTextIndexFromPosition(const Point& pt) const		= 0;


	
	void	clearSelection(void);


	
	void	eraseSelectedText(bool modify_text = true);


	
	bool	isStringValid(const String& str) const;





	
	void	handleDelete(void);


	
	void	handleCharLeft(uint sysKeys);


	
	void	handleWordLeft(uint sysKeys);


	
	void	handleCharRight(uint sysKeys);


	
	void	handleWordRight(uint sysKeys);


	
	void	handleHome(uint sysKeys);


	
	void	handleEnd(uint sysKeys);


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Editbox")	return true;
		return Window::testClassName_impl(class_name);
	}


	
	
	virtual	void	onReadOnlyChanged(WindowEventArgs& e);


	
	virtual	void	onMaskedRenderingModeChanged(WindowEventArgs& e);


	
	virtual	void	onMaskCodePointChanged(WindowEventArgs& e);


	
	virtual	void	onValidationStringChanged(WindowEventArgs& e);


	
	virtual	void	onMaximumTextLengthChanged(WindowEventArgs& e);


	
	virtual	void	onTextInvalidatedEvent(WindowEventArgs& e);


	
	virtual	void	onInvalidEntryAttempted(WindowEventArgs& e);


	
	virtual	void	onCaratMoved(WindowEventArgs& e);


	
	virtual	void	onTextSelectionChanged(WindowEventArgs& e);


	
	virtual	void	onEditboxFullEvent(WindowEventArgs& e);


	
	virtual	void	onTextAcceptedEvent(WindowEventArgs& e);

	
	virtual	void	onTabPressedEvent(WindowEventArgs& e);
	
	
	virtual	void	onMouseButtonDown(MouseEventArgs& e);
	virtual void	onMouseButtonUp(MouseEventArgs& e);
	virtual	void	onMouseDoubleClicked(MouseEventArgs& e);
	virtual	void	onMouseTripleClicked(MouseEventArgs& e);
	virtual void	onMouseMove(MouseEventArgs& e);
	virtual void	onCaptureLost(WindowEventArgs& e);
	virtual void	onCharacter(KeyEventArgs& e);
	virtual void	onKeyDown(KeyEventArgs& e);
	virtual void	onKeyUp(KeyEventArgs& e);
	virtual void	onTextChanged(WindowEventArgs& e);


	
	bool	d_readOnly;			
	bool	d_forbidInput;	
	bool	d_maskText;			
	utf32	d_maskCodePoint;	
	size_t	d_maxTextLen;		
	size_t	d_caratPos;			
	size_t	d_selectionStart;	
	size_t	d_selectionEnd;		
	String	d_validationString;	
	RegexValidator*	d_validator;		
	bool	d_dragging;			
	size_t	d_dragAnchorIdx;	
	bool	d_useRegex;
	bool	d_lostFocus;

	
	colour	d_normalTextColour;				
	colour	d_selectTextColour;				
	colour	d_selectBrushColour;			
	colour	d_inactiveSelectBrushColour;	


private:
	
	static EditboxProperties::ReadOnly					d_readOnlyProperty;
	static EditboxProperties::MaskText					d_maskTextProperty;
	static EditboxProperties::MaskCodepoint				d_maskCodepointProperty;
	static EditboxProperties::ValidationString			d_validationStringProperty;
	static EditboxProperties::CaratIndex				d_caratIndexProperty;
	static EditboxProperties::SelectionStart			d_selectionStartProperty;
	static EditboxProperties::SelectionLength			d_selectionLengthProperty;
	static EditboxProperties::MaxTextLength				d_maxTextLengthProperty;
	static EditboxProperties::NormalTextColour			d_normalTextColourProperty;
	static EditboxProperties::SelectedTextColour		d_selectedTextColourProperty;
	static EditboxProperties::ActiveSelectionColour		d_activeSelectionColourProperty;
	static EditboxProperties::InactiveSelectionColour	d_inactiveSelectionColourProperty;
	static EditboxProperties::ForbidInput				d_forbidInputProperty;
	static EditboxProperties::UseRegex					d_useRegexProperty;
	static EditboxProperties::LostFocus					d_lostFocusProperty;


	
	void	addEditboxProperties(void);
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
