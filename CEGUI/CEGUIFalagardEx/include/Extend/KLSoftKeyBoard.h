#pragma once
#include "falstaticimage.h"
#include "IKLsoftkeyboard.h"
#include <vector>
namespace CEGUI
{
	
	enum SoftKey_Type
	{
		SoftKey_Number = 0, 
		SoftKey_Word,		
		SoftKey_Punctuation,
		SoftKey_Type_Number,
		SoftKey_Back,		
		SoftKey_Shift,		
		SoftKey_Return,		
		SoftKey_Space,		
		SoftKey_TypeNumber,
	};

	enum SoftKey_Define
	{
		SoftKeyDef_Number = 0,			
		SoftKeyDef_Lower_Word,			
		SoftKeyDef_Capital_Word,		
		SoftKeyDef_Punctuation,			
		SoftKeyDef_MaxNumber,
	};

	namespace KLSoftKeyProperties
	{
		class KeySize: public Property
		{
		public:
			KeySize() : Property(
				"KeySize",
				"Property to get/set the horizontal formatting mode.  Value is one of the HorzFormatting strings.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};

		class HoverImage: public Property
		{
		public:
			HoverImage() : Property(
				"HoverImage",
				"Property to get/set the horizontal formatting mode.  Value is one of the HorzFormatting strings.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
		
		class PushedImage: public Property
		{
		public:
			PushedImage() : Property(
				"PushedImage",
				"Property to get/set the horizontal formatting mode.  Value is one of the HorzFormatting strings.",
				"")
			{}

			String	get(const PropertyReceiver* receiver) const;
			void	set(PropertyReceiver* receiver, const String& value);
		};
	};
	struct SKey_Define
	{
		utf32    uChar; 
		int     nType;
	};
	struct SKey_Position
	{
		Point	m_Pos;
		bool	m_bHover; 
		SKey_Define* m_pKeyDefine; 
		void setHover( bool bHover ){ m_bHover = bHover; };
		SKey_Position()
		{
			m_bHover = false;
		};
	};
	enum BUTTON_TYPE
	{
		BUTTON_TYPE_NORMAL = 0,
		BUTTON_TYPE_BACK,
		BUTTON_TYPE_SHIFT,
		BUTTON_TYPE_RETURN,
		BUTTON_TYPE_NUMBER,

	};
	class FALAGARDBASE_API KLSoftKeyBoard : public FalagardStaticImage, public IKLSoftKeyBoard
	{
	public:
		static const utf8   WidgetTypeName[];       
		static const String		EventNamespace;
	private:
		std::vector<SKey_Position> m_aKeyPosList[SoftKey_TypeNumber ]; 
		std::vector<SKey_Define> m_aKeyDefineList[ SoftKeyDef_MaxNumber ];
		SKey_Define   m_KeyDefReturn;
		SKey_Define   m_KeyDefBack;
		SKey_Define   m_KeyDefShift;
		Window*  m_pAimEditBox;
		bool			m_bShiftDown;
		bool			m_bKeyDown;

		SKey_Position* m_pLastKey;
		SKey_Position* m_pCurrentKey;

		float GridWidth;
		float GridHeight;
		float d_gridWidth;
		float d_gridHeight;

		const Image*  m_pHoverImage[ BUTTON_TYPE_NUMBER ]; 
		const Image*  m_pPushedImage[ BUTTON_TYPE_NUMBER ]; 

	protected:

		void setKeyPosition( int x, int y, int nType );
		void setKeyDefine( utf32 nchar, int nType );
		void ResetAllKey();
		void setKeyHover( SKey_Position* pKey, bool bHover );
		
		void updateKeyPosition( const Point& screenPos );
		
		SKey_Position* getKeyByPosition( const Point& screenPos );

		void resetAllPosition();

		virtual void	onSized(WindowEventArgs& e);

	public:
		KLSoftKeyBoard(const String& type, const String& name);
		~KLSoftKeyBoard(void);
		virtual void initialise();
		virtual void SetActiveEditBox( String& windowName );
		virtual void onMouseMove( MouseEventArgs& e );
		virtual void onMouseButtonDown( MouseEventArgs& e );
		virtual void onMouseButtonUp( MouseEventArgs& e );
		virtual void onMouseLeaves( MouseEventArgs& e );
		virtual void populateRenderCache();
		virtual void onShown(WindowEventArgs& e);

		void setKeySize( const Size& size );

		void setHoverImage( int nType, const Image* pImage );
		void setPushedImage( int nType,const Image* pImage );


		static KLSoftKeyProperties::HoverImage   d_hoverImage;
		static KLSoftKeyProperties::PushedImage  d_pushedImage;
		static KLSoftKeyProperties::KeySize      d_keySize;

		static const String EventReturn;	

		typedef bool SoftkeyCallback( int nType, uint32 nChar );
		void setGameSoftkeyPointer( SoftkeyCallback* pSoftkey ) { d_SoftkeyCallback = pSoftkey; }

	private:

		SoftkeyCallback*	d_SoftkeyCallback; 
	};

	class FALAGARDBASE_API KLSoftKeyFactory : public WindowFactory
    {
    public:
        KLSoftKeyFactory(void) : WindowFactory(KLSoftKeyBoard::WidgetTypeName) { }
        ~KLSoftKeyFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
};