#include "KLinfolist.h"
#include "ceguipropertyhelper.h"

namespace CEGUI
{
	const utf8 KLInfoList::WidgetTypeName[] = "Falagard/InfoList";
	
	KLInfoListProperties::AddInfo		KLInfoList::d_AddInfoProperty;
	KLInfoListProperties::FadeSpeed	KLInfoList::d_FadeSpeedProperty;
	KLInfoListProperties::Life		KLInfoList::d_LifeProperty;
	KLInfoListProperties::MaxInfo		KLInfoList::d_MaxInfoProperty;

	
	FalagardInfoItem::FalagardInfoItem(const String& text, uint item_id , void* item_data , bool disabled , bool auto_delete ):
		ListboxTextItem( text, item_id, item_data, disabled, auto_delete )
	{
		m_fCurAlpha = 1;
	}
	bool FalagardInfoItem::update( float elapsed )
	{
		m_nTimer -= int( elapsed * 1000 ); 
		if( m_nTimer < 0 )
		{
			m_fCurAlpha -= float( m_nFadeSpeed * elapsed ) / 255.f;
			if( m_fCurAlpha < 0 )
				return false;
		}
		return true;
	}

	void FalagardInfoItem::draw(RenderCache& cache,const Rect& targetRect, float zBase,  float alpha, const Rect* clipper) const
	{
		if (d_selected && d_selectBrush != 0)
		{
			cache.cacheImage(*d_selectBrush, targetRect, zBase, getModulateAlphaColourRect(d_selectCols, alpha), clipper);
		}

		const Font* font = getFont();

		if (font)
		{
			Rect finalPos(targetRect);

			cache.cacheText(getOwnerWindow(), d_itemText, font, Centred, finalPos, zBase, getModulateAlphaColourRect(d_textCols, alpha), clipper);
		}
	}
	
	
	KLInfoList::KLInfoList(const String& type, const String& name) :
		FalagardListbox(type, name)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLInfoList )
		   CEGUI_ADD_STATICPROPERTY( &d_AddInfoProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_FadeSpeedProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_LifeProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_MaxInfoProperty  );
		CEGUI_END_ADD_STATICPROPERTY

		m_nMaxInfoNumber = 3;
	}

	KLInfoList::~KLInfoList(void)
	{
	}
	void KLInfoList::NormalizeItemNumber()
	{
		if( (int)getItemCount() < m_nMaxInfoNumber )
			return;
		for (size_t i = 0; i < getItemCount() - m_nMaxInfoNumber; i ++ ) 
			removeItem( d_listItems[ 0 ] );

	}
	void KLInfoList::updateSelf( float elapsed )
	{
		FalagardListbox::updateSelf( elapsed );

		for (size_t i = 0; i < getItemCount(); ++i ) 
		{
			
			if ( ((FalagardInfoItem*)d_listItems[i])->update( elapsed ) == false )
			{
				
				removeItem( d_listItems[ i ] );
			}

		}
		int x=(int)getItemCount();
		if( x == 0)
			setVisible(false);
		else
			setVisible(true);
		requestRedraw();
	}


    Window* KLInfoListFactory::createWindow(const String& name)
    {
        return new KLInfoList(d_type, name);
    }

    void KLInfoListFactory::destroyWindow(Window* window)
    {
       delete window;
    }

	
	namespace KLInfoListProperties
	{
		
		String Life::get(const PropertyReceiver* receiver) const
		{
			return  PropertyHelper::intToString( static_cast< const KLInfoList*>(receiver)->getLife() );
		}

		void Life::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLInfoList*>(receiver)->setLife( PropertyHelper::stringToInt( value ) );
		};

		
		String FadeSpeed::get(const PropertyReceiver* receiver) const
		{
			return  PropertyHelper::intToString( static_cast< const KLInfoList*>(receiver)->getFadeSpeed() );
		}

		void FadeSpeed::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLInfoList*>(receiver)->setFadeSpeed( PropertyHelper::stringToInt( value ) );
		};

		
		String AddInfo::get(const PropertyReceiver* receiver) const
		{
			return  "";
		}

		void AddInfo::set(PropertyReceiver* receiver, const String& value)
		{
			FalagardInfoItem* pItem = new FalagardInfoItem(value);
			KLInfoList *pParent = static_cast<KLInfoList*>(receiver);
			if( pItem && pParent )
			{
				pItem->setFadeSpeed( pParent->getFadeSpeed());
				pItem->setTimer( pParent->getLife() );
				pParent->addItem( pItem );
				pParent->NormalizeItemNumber();
				
			}
		};

		
		String MaxInfo::get(const PropertyReceiver* receiver) const
		{
			return "";
		}

		void MaxInfo::set(PropertyReceiver* receiver, const String& value)
		{
			static_cast<KLInfoList*>(receiver)->setMaxInfo( PropertyHelper::stringToInt( value ) );
		};

	};
};