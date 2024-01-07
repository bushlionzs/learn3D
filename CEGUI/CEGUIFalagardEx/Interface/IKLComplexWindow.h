
namespace CEGUI
{
	class IKLComplexWindow
	{
	public:
		enum ChildType
		{
			CT_Text,
			CT_Option,
			CT_Item,
			CT_Action,
			CT_Money,
			CT_HyperLink,
		};

		
		virtual int				AddChildElement_Text(String strText, Font* font, TextFormatting typeset=WordWrapLeftAligned, bool showImage=false, bool showButton=false) = 0;
		
		
		virtual void			AddChildElement_Option(String strText,String strText2,String strText3, String strText4, Font* font=NULL) = 0;
		
		
		virtual void			AddChildElement_HyperLink( String strText, int nLinkID, bool bReArrange, Font* font=NULL) = 0;

		
		virtual Window*			AddChildElement_Item(String strIconImage, String strText, bool bRadio,bool bReArrange, Font* font=NULL, int ActionID = -1, int nCount = 0, bool isMask = false) = 0;

		
		virtual Window*			AddChildElement_Action(String strIconImage, int ActionID, bool bRadio, bool bReArrange, Font* font=NULL) = 0;

		
		virtual void			AddChildElement_Money(int money, Font* font=NULL) = 0;
		
		virtual void			ClearAllElement(void) = 0;

		virtual void			PageEnd() = 0;

		virtual int				GetCurActionId() = 0;

		virtual Window*			GetInlineButtion(int nChildWindowIndex) = 0;
	};
}