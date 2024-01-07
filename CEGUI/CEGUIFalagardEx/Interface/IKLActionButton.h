

#ifndef IFALAGARDACTIONBUTTON_H
#define IFALAGARDACTIONBUTTON_H

namespace CEGUI
{
	class KLActionButton;
	class KLExtendTooltip;
	class IKLActionButton
	{
	public:		
		virtual void		subscribeDragDropStartedEvent(Event::Subscriber subscriber) = 0;
		virtual void		subscribeMouseEnterEvent(Event::Subscriber subscriber) = 0;
		virtual void		subscribeMouseLeaveEvent(Event::Subscriber subscriber) = 0;
		virtual void		setAnimate(const String& name, int totalTime, float percent) = 0;
		virtual void		cleanAnimate(void) = 0;
		virtual void		notifyDragingEnd(void) = 0;
		virtual void		notifyDragDrop_Droped(KLActionButton* pBtn) = 0;
		virtual void		setLogicItemData(void* pData) = 0;
		virtual void*		getLogicItemData(void) const = 0;
		virtual const char*	getDragAcceptName(void) const = 0;
		virtual void		setCornerChar(int nPos, const String& strChar, bool isColor = false ) = 0;
		virtual void		setCoverImage(const String& imageset, const String& image, float alpha = 0.5f)	= 0;
		virtual void		setCoverImageShow(bool bshow)	= 0;
	};
}

#endif 