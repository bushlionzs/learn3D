#pragma once
#include "fallistbox.h"
#include "KLimagelistproperties.h"
#include "elements/ceguilistboxtextitem.h"
namespace CEGUI
{
	
	namespace KLInfoListProperties
	{
		
		
		class Life: public Property
		{
		public:
			Life() : Property(
				"Life",
				"Property to get/set Minimap name status.",
				"type: set: image:")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		
		class FadeSpeed: public Property
		{
		public:
			FadeSpeed() : Property(
				"FadeSpeed",
				"Property to get/set Minimap name status.",
				"type: set: image:")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		
		class AddInfo: public Property
		{
		public:
			AddInfo() : Property(
				"AddInfo",
				"Property to get/set Minimap name status.",
				"type: set: image:")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};
		
		
		class MaxInfo: public Property
		{
		public:
			MaxInfo() : Property(
				"MaxInfo",
				"Property to get/set Minimap name status.",
				"type: set: image:")
			{}

			String   get(const PropertyReceiver* receiver) const;
			void   set(PropertyReceiver* receiver, const String& value);
		};

	};
	
	class FALAGARDBASE_API FalagardInfoItem : public ListboxTextItem
	{
		float   m_fCurAlpha;
		int		m_nTimer;		
		int		m_nFadeSpeed;
	public:
		virtual void draw(RenderCache& cache,const Rect& targetRect, float zBase,  float alpha, const Rect* clipper) const;

		FalagardInfoItem(const String& text, uint item_id = 0, void* item_data = NULL, bool disabled = false, bool auto_delete = true);
		~FalagardInfoItem() {};
	
		void setTimer( int nLife ){ m_nTimer = nLife; };
		void setFadeSpeed( int nSpeed ) { m_nFadeSpeed = nSpeed; };
		
		bool update( float elapsed );
	};
	
	class FALAGARDBASE_API KLInfoList :public FalagardListbox
	{
		int  m_nLife; 
		int  m_nFadeSpeed;
		int	 m_nMaxInfoNumber;
	public:
		KLInfoList(const String& type, const String& name);
		~KLInfoList(void);

		static const utf8   WidgetTypeName[];       

		virtual void updateSelf( float elapsed );

		void	setLife( int nLife ) { m_nLife = nLife; };
		void	setFadeSpeed( int nSpeed ) { m_nFadeSpeed = nSpeed; };

		const int  	getLife() const { return m_nLife; };
		const int	getFadeSpeed() const { return m_nFadeSpeed; };

		void	setMaxInfo( int nNumber ) { m_nMaxInfoNumber = nNumber; };

		void	NormalizeItemNumber();

		static KLInfoListProperties::AddInfo		d_AddInfoProperty;
		static KLInfoListProperties::FadeSpeed	d_FadeSpeedProperty;
		static KLInfoListProperties::Life			d_LifeProperty;
		static KLInfoListProperties::MaxInfo		d_MaxInfoProperty;
	};

	
	class FALAGARDBASE_API KLInfoListFactory : public WindowFactory
    {
    public:
        KLInfoListFactory(void) : WindowFactory(KLInfoList::WidgetTypeName) { }
        ~KLInfoListFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
	
}