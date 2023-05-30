#include "stdafx.h"
#include "SCChat.h"
#include "CEGUIKeyImageAnimationManager.h"

SCChat::SCChat()
    :NetPacket(SC_CHAT)
{

}

SCChat::~SCChat()
{

}

bool SCChat::process()
{
	
	/* �߼�õ�廨��Ч */
	if (CHAT_TYPE_ROSE == mChatType)
	{
		COMMAND_SYS_PTR->AddCommand(GCD_ADVANCED_ROSE);
	}	/* if */

	/* ��Ϣ���� */
	std::string& strContex = mChatMessage;
	if (strContex.empty())
		return 0;

	int32 nPos = mChatShowPosition;

	/* ����ͨ��GMTools���͵�ϵͳ���� */
	int32 nContex = -1;

	KYLIN_TRY if (strContex.at(0) == '$' && CHAT_TYPE_SYSTEM == mChatType)
	{
		STRING strTmp;
		strTmp = strContex.substr(1);

		/* �ڶ���$ */
		STRING::size_type	tFind = strTmp.find_first_of("$");
		if (STRING::npos != tFind)
		{
			/*
			 * ȡ������ֵ ;
			 * int32 nContexLen = strContex.length();
			 */
			strContex = strTmp.substr(tFind + 1);

			strTmp = strTmp.substr(0, tFind);
			nContex = atoi(strTmp.c_str());
		}
	}

	KYLIN_CATCH("HandleShowTipPacket 1") switch (nContex)
	{
		/* 1 = ��Ļ����ˮƽ���� */
	case 1:
		nPos = CHAT_PLANE_SCROLL;
		break;

		/*
		 * 2 = �������� ;
		 * case 2: nPos = CHAT_MAIN_WINDOW;
		 * * break;
		 */
	};
	switch (nPos)
	{
		/* �м�������� */
	case CHAT_MAIN_RIGHTDOWN:
	{
		KYLIN_TRY

			/*
			 * COMMAND_SYS_PTR->AddCommand( GCD_SCENE_NAME_TIP, strContex.c_str() );
			 */
			GAME_DATA_PTR->AddInfoToBuffer(strContex);

		/*
		 * �յ���������Ϣ����������¹�����Ϣ(09/04/25 by QL) ;
		 * (09/06/24 by QL)ȡ�����ʹ���Ϣ��������ȫ�������ܶ�ʱ������������ ;
		 * CGCountry msg;
		 * *msg.SetType(OP_ASKINFO);
		 * *NET_MANAGER_PTR->SendMessage( &msg);
		 */
		KYLIN_CATCH("HandleShowTipPacket 2")
	}
	break;

	/* ˮƽ������ʾ�� */
	case CHAT_PLANE_SCROLL:
	{
		KYLIN_TRY char szCycleCount[32] = { 0 };
		_snprintf(szCycleCount, 32, "%d", mCycleCount);

		COMMAND_SYS_PTR->AddCommand(GCD_PARALLEL_MESSAGE, strContex.c_str(), szCycleCount);

		KYLIN_CATCH("HandleShowTipPacket 3")
	}
	break;

	/* �м��²��Ĺ����� */
	case CHAT_MIDDLE_BOTTOM_SCROLL:
	{
		KYLIN_TRY char szTemp[32] = { 0 };
		_snprintf(szTemp, 32, "%d", mCycleCount);
		COMMAND_SYS_PTR->AddCommand(GCD_MIDDLE_BOTTOM_SCROLL_MESSAGE, strContex.c_str(), szTemp, FALSE);

		KYLIN_CATCH("HandleShowTipPacket 4")
	}
	break;

	/* �м��²����ı��� */
	case CHAT_MIDDLE_BOTTOM_TEXT:
	{
		KYLIN_TRY COMMAND_SYS_PTR->AddCommand(GCD_MIDDLE_BOTTOM_TEXT_MESSAGE, strContex.c_str());

		KYLIN_CATCH("HandleShowTipPacket 5")
	}
	break;

	/* �м�Ķ����� */
	case CHAT_MIDDLE_ANIM:
	{
		KYLIN_TRY

			/* ��ȡ���� */
			const CEGUI::KeyImageAnimation* pAnimate = CEGUI::KeyImageAnimationManager::getSingletonPtr()->getAnimate(mAnimateImage);
		if (pAnimate)
		{
			COMMAND_SYS_PTR->AddCommand(GCD_MIDDLE_ANIM_MESSAGE, pAnimate->getName().c_str());
		}

		KYLIN_CATCH("HandleShowTipPacket 6")
	}
	break;

	default:
	{
		/*KYLIN_TRY	HandleRecvTalkPacket(pPacket);

		KYLIN_CATCH("HandleShowTipPacket 7")*/
	}
	break;
	}

    return true;
}

void SCChat::setChatType(int32_t type)
{
    mChatType = type;
}

void SCChat::setChatMsg(const char* msg)
{
    mChatMessage = msg;
}

void SCChat::setChatShowPos(ENUM_SYSTEM_CHAR_SHOW_POS pos)
{
    mChatShowPosition = pos;
}
