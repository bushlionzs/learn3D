

#include "FalModule.h"
#include "CEGUIExceptions.h"
#include "CEGUIWindowFactoryManager.h"

#include "FalButton.h"
#include "FalCheckbox.h"
#include "FalComboDropList.h"
#include "FalCombobox.h"
#include "FalEditbox.h"
#include "FalFrameWindow.h"
#include "FalListHeader.h"
#include "FalListHeaderSegment.h"
#include "FalListbox.h"
#include "FalMenuBar.h"
#include "FalMenuItem.h"
#include "FalMultiColumnList.h"
#include "FalMultiLineEditbox.h"
#include "FalPopupMenu.h"
#include "FalProgressBar.h"
#include "FalRadioButton.h"
#include "FalScrollablePane.h"
#include "FalScrollbar.h"
#include "FalSlider.h"
#include "FalSpinner.h"
#include "FalStaticImage.h"
#include "FalStaticText.h"
#include "FalSystemButton.h"
#include "FalTabButton.h"
#include "FalTabControl.h"
#include "FalTabPane.h"
#include "FalThumb.h"
#include "FalTitlebar.h"
#include "FalTooltip.h"

#include "KLActionButton.h"
#include "KLPrizeButton.h"
#include "KLComplexWindow.h"
#include "KLcheckbutton.h"
#include "KLInjuryInfoBoard.h"
#include "KLExtendTooltip.h"
#include "KLWealth.h"
#include "KLSimpleText.h"
#include "KLDragTitle.h"
#include "KLActorWindow.h"
#include "KLBoundWindow.h"
#include "KLIMEEditBox.h"
#include "KLMultiIMEEditBox.h"
#include "KLTextChatBoard.h"
#include "KLTextChatHistory.h"
#include "KLTextChatChannel.h"
#include "KLExtendProgress.h"
#include "KLInfolist.h"
#include "KLRoleInformationBoard.h"
#include "KLCountDownTimer.h"
#include "KLKeyImageAnimation.h"
#include "KLSelfAdaptationWindow.h"
#include "KLBalloon.h"
#include "KLSoftKeyBoard.h"
#include "KLRadar.h"
#include "KLTextScrollBar.h"
#include "KLEventTimer.h"
#include "KLRingProgress.h"


static CEGUI::FalagardButtonFactory             s_ButtonFactory;
static CEGUI::FalagardCheckboxFactory           s_CheckboxFactory;
static CEGUI::FalagardComboDropListFactory      s_ComboDropListFactory;
static CEGUI::FalagardComboboxFactory           s_ComboboxFactory;
static CEGUI::FalagardEditboxFactory            s_EditboxFactory;
static CEGUI::FalagardFrameWindowFactory        s_FrameWindowFactory;
static CEGUI::FalagardListHeaderFactory         s_ListHeaderFactory;
static CEGUI::FalagardListHeaderSegmentFactory  s_ListHeaderSegmentFactory;
static CEGUI::FalagardListboxFactory            s_ListboxFactory;
static CEGUI::FalagardMenubarFactory            s_MenubarFactory;
static CEGUI::FalagardMenuItemFactory           s_MenuItemFactory;
static CEGUI::FalagardMultiColumnListFactory    s_MultiColumnListFactory;
static CEGUI::FalagardMultiLineEditboxFactory   s_MultiLineEditboxFactory;
static CEGUI::FalagardPopupMenuFactory          s_PopupMenuFactory;
static CEGUI::FalagardProgressBarFactory        s_ProgressBarFactory;
static CEGUI::FalagardRadioButtonFactory        s_RadioButtonFactory;
static CEGUI::FalagardScrollablePaneFactory     s_ScrollablePaneFactory;
static CEGUI::FalagardScrollbarFactory          s_ScrollbarFactory;
static CEGUI::FalagardSliderFactory             s_SliderFactory;
static CEGUI::FalagardSpinnerFactory            s_SpinnerFactory;
static CEGUI::FalagardStaticImageFactory        s_StaticImageFactory;
static CEGUI::FalagardStaticTextFactory         s_StaticTextFactory;
static CEGUI::FalagardSystemButtonFactory       s_SystemButtonFactory;
static CEGUI::FalagardTabButtonFactory          s_TabButtonFactory;
static CEGUI::FalagardTabControlFactory         s_TabControlFactory;
static CEGUI::FalagardTabPaneFactory            s_TabPaneFactory;
static CEGUI::FalagardThumbFactory              s_ThumbFactory;
static CEGUI::FalagardTitlebarFactory           s_TitlebarFactory;
static CEGUI::FalagardTooltipFactory            s_TooltipFactory;


static CEGUI::KLActionButtonFactory       s_ActionButtonFactory;
static CEGUI::KLPrizeButtonWindowFactory	s_prizeButtonWindowFactory;
static CEGUI::KLComplexWindow::ParentWindowFactory		s_ComplexParentWindowFactory;
static CEGUI::KLComplexWindowFactory		s_ComplexWindowFactory;
static CEGUI::KLCheckButtonFactory		s_CheckbuttonFactory;
static CEGUI::KLInjuryInfoBoardFactory	s_injuryInfoBoardFactory;
static CEGUI::KLExtendTooltipFactory		s_ExtendTooltipFactory;
static CEGUI::KLExtendTooltip::ResizeTextFactory 		s_resizeTextFactory;
static CEGUI::KLWealthFactory				s_WealthFactory;
static CEGUI::KLSimpleTextFactory			s_SimpleTextFactory;
static CEGUI::KLDragTitleFactory			s_dragTitleFactory;
static CEGUI::KLActorWindowFactory			s_actorWindowFactory;
static CEGUI::KLBoundWindowFactory		s_boundWindowFactory;
static CEGUI::KLIMEEditBoxFactory			s_imeEditBoxWindowFactory;
static CEGUI::KLMultiIMEEditBoxFactory	s_multiImeEditBoxWindowFactory;
static CEGUI::KLTextChatBoardFactory			s_textChatBoardWindowFactory;
static CEGUI::KLTextChatHistoryFactory		s_textChatHistoryWindowFactory;
static CEGUI::KLTextChatHistory::ParentWindowFactory			s_chatHistoryParentWindowFactory;
static CEGUI::KLTextChatChannelFactory		s_textChatChannelWindowFactory;
static CEGUI::KLExtendProgressFactory		s_extendProgressFactory;
static CEGUI::KLScenemapFactory			s_ScenemapFactory;
static CEGUI::KLInfoListFactory			s_InfoListFactory;
static CEGUI::KLRoleInformationBoardFactory		s_roleInformationBoardFactory;
static CEGUI::KLCountDownTimerFactory			s_countDownTimerFactory;
static CEGUI::KLAnimateFactory			s_AnimateFactory;
static CEGUI::KLSelfAdaptationWindowFactory			s_selfAdaptationFactory;
static CEGUI::KLBalloonFactory				s_BalloonFactory;
static CEGUI::KLSoftKeyFactory			s_SoftKeyFactory;
static CEGUI::KLRadarFactory				s_RadarFactory;
static CEGUI::KLTextScrollBarFactory				s_TextScrollBarFactory;
static CEGUI::KLEventTimerFactory			s_TextEventTimerFactory;

static CEGUI::KLRingProgressFactory		s_ringProgressFactory;

using namespace CEGUI;

struct mapEntry
{
    const CEGUI::utf8* d_name;
    CEGUI::WindowFactory* d_factory;
};

mapEntry factoriesMap[] =
{
    {FalagardButton::WidgetTypeName, &s_ButtonFactory},
    {FalagardCheckbox::WidgetTypeName, &s_CheckboxFactory},
    {FalagardComboDropList::WidgetTypeName, &s_ComboDropListFactory},
    {FalagardCombobox::WidgetTypeName, &s_ComboboxFactory},
    {FalagardEditbox::WidgetTypeName, &s_EditboxFactory},
    {FalagardFrameWindow::WidgetTypeName, &s_FrameWindowFactory},
    {FalagardListHeader::WidgetTypeName, &s_ListHeaderFactory},
    {FalagardListHeaderSegment::WidgetTypeName, &s_ListHeaderSegmentFactory},
    {FalagardListbox::WidgetTypeName, &s_ListboxFactory},
    {FalagardMenubar::WidgetTypeName, &s_MenubarFactory},
    {FalagardMenuItem::WidgetTypeName, &s_MenuItemFactory},
    {FalagardMultiColumnList::WidgetTypeName, &s_MultiColumnListFactory},
    {FalagardMultiLineEditbox::WidgetTypeName, &s_MultiLineEditboxFactory},
    {FalagardPopupMenu::WidgetTypeName, &s_PopupMenuFactory},
    {FalagardProgressBar::WidgetTypeName, &s_ProgressBarFactory},
    {FalagardRadioButton::WidgetTypeName, &s_RadioButtonFactory},
    {FalagardScrollablePane::WidgetTypeName, &s_ScrollablePaneFactory},
    {FalagardScrollbar::WidgetTypeName, &s_ScrollbarFactory},
    {FalagardSlider::WidgetTypeName, &s_SliderFactory},
    {FalagardSpinner::WidgetTypeName, &s_SpinnerFactory},
    {FalagardStaticImage::WidgetTypeName, &s_StaticImageFactory},
    {FalagardStaticText::WidgetTypeName, &s_StaticTextFactory},
    {FalagardSystemButton::WidgetTypeName, &s_SystemButtonFactory},
    {FalagardTabButton::WidgetTypeName, &s_TabButtonFactory},
    {FalagardTabControl::WidgetTypeName, &s_TabControlFactory},
    {FalagardTabPane::WidgetTypeName, &s_TabPaneFactory},
    {FalagardThumb::WidgetTypeName, &s_ThumbFactory},
    {FalagardTitlebar::WidgetTypeName, &s_TitlebarFactory},
    {FalagardTooltip::WidgetTypeName, &s_TooltipFactory},
	

	
    {KLActionButton::WidgetTypeName, &s_ActionButtonFactory},
	{KLPrizeButton::WidgetTypeName, &s_prizeButtonWindowFactory},
	{KLComplexWindow::ParentWindow::WidgetTypeName, &s_ComplexParentWindowFactory},
	{KLComplexWindow::WidgetTypeName, &s_ComplexWindowFactory},
	{KLCheckButton::WidgetTypeName, &s_CheckbuttonFactory},
	{KLInjuryInfoBoard::WidgetTypeName, &s_injuryInfoBoardFactory},
	{KLExtendTooltip::WidgetTypeName, &s_ExtendTooltipFactory},
	{KLExtendTooltip::ResizeText::WidgetTypeName, &s_resizeTextFactory},
	{KLWealth::WidgetTypeName, &s_WealthFactory},
	{KLSimpleText::WidgetTypeName, &s_SimpleTextFactory},
	{KLDragTitle::WidgetTypeName, &s_dragTitleFactory},
	{KLActorWindow::WidgetTypeName, &s_actorWindowFactory},
	{KLBoundWindow::WidgetTypeName, &s_boundWindowFactory},
	{KLIMEEditBox::WidgetTypeName, &s_imeEditBoxWindowFactory},
	{KLMultiIMEEditBox::WidgetTypeName, &s_multiImeEditBoxWindowFactory},
	{KLTextChatBoard::WidgetTypeName, &s_textChatBoardWindowFactory},
	{KLTextChatHistory::WidgetTypeName, &s_textChatHistoryWindowFactory},
	{KLTextChatHistory::ParentWindow::WidgetTypeName, &s_chatHistoryParentWindowFactory},
	{KLTextChatChannel::WidgetTypeName, &s_textChatChannelWindowFactory},
	{KLExtendProgress::WidgetTypeName, &s_extendProgressFactory},
	{KLRingProgress::WidgetTypeName, &s_ringProgressFactory},
	{KLSceneMap::WidgetTypeName, &s_ScenemapFactory},
	{KLInfoList::WidgetTypeName, &s_InfoListFactory},
	{KLRoleInformationBoard::WidgetTypeName, &s_roleInformationBoardFactory},
	{KLCountDownTimer::WidgetTypeName, &s_countDownTimerFactory},
	{KLKeyImageAnimation::WidgetTypeName, &s_AnimateFactory},
	{KLSelfAdaptationWindow::WidgetTypeName, &s_selfAdaptationFactory},
	{KLBalloon::WidgetTypeName, &s_BalloonFactory},
	{KLSoftKeyBoard::WidgetTypeName, &s_SoftKeyFactory},
	{KLRadar::WidgetTypeName, &s_RadarFactory},
	{KLTextScrollBar::WidgetTypeName, &s_TextScrollBarFactory},
	{KLEventTimer::WidgetTypeName, &s_TextEventTimerFactory},
    {0,0}
};


extern "C" void registerFactory(const CEGUI::String& type_name)
{
    mapEntry* entry = factoriesMap;

    while (entry->d_name)
    {
        if (entry->d_name == type_name)
        {
            doSafeFactoryRegistration(entry->d_factory);
            return;
        }

        ++entry;
    }

    throw UnknownObjectException((utf8*)"::registerFactory - The window factory for type '" + type_name + "' is not known in this module.");
}

extern "C" void registerFalagardFactory(const CEGUI::String& type_name)
{
	registerFactory(type_name);
}

extern "C" CEGUI::uint registerAllFactories(void)
{
    CEGUI::uint count = 0;
    mapEntry* entry = factoriesMap;

    while (entry->d_name)
    {
		doSafeFactoryRegistration(entry->d_factory);

        ++entry;
        ++count;
    }
	System::getSingleton().getRenderer()->Register3DWindowFactory();
    return count;
}

extern "C" CEGUI::uint registerAllFalagardFactories(void)
{
	return registerAllFactories();
}

void doSafeFactoryRegistration(WindowFactory* factory)
{
	assert(factory != 0);

	WindowFactoryManager& wfm = WindowFactoryManager::getSingleton();

	if (wfm.isFactoryPresent(factory->getTypeName()))
	{
		
		Logger::getSingleton().logEvent(
			"Falagard widget factory '" + factory->getTypeName() + "' appears to be already registered, skipping.",
			Informative);
	}
	else
	{
		wfm.addFactory(factory);
	}
}
