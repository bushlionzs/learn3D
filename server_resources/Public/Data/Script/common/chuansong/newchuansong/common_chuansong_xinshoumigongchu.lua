--�뿪���ִ�

--MisDescBegin
x550201_g_ScriptId = 550201
x550201_g_MissionName = "���ش���"
x550201_g_MissionInfo=" �ҿ��԰����ͻش��ӡ�"  --��������
x550201_g_MissionInfo2=""
--x550201_g_MissionQuestID	=	2553
x550201_g_MissionComplete="  "					--�������npc˵���Ļ�
x550201_g_ContinueInfo="    "
x550201_g_TransPos1 = "xinshoumigong1loulan"
x550201_g_TransPos2 = "xinshoumigong1laiyin"
x550201_g_TransPos3 = "xinshoumigong1kunlun"
x550201_g_TransPos4 = "xinshoumigong1dunhuang"
--������
x550201_g_MoneyBonus = 10000
--�̶���Ʒ���������8��
x550201_g_ItemBonus={}

--��ѡ��Ʒ���������8��
x550201_g_RadioItemBonus={}

--MisDescEnd
x550201_g_ExpBonus = 1000
--**********************************

--������ں���

--**********************************

function x550201_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	local country = GetCurCountry(sceneId,selfId)
		if country == 0 then		
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550201_g_TransPos1)
    elseif country ==1 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550201_g_TransPos2)
		elseif country ==2 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550201_g_TransPos3)
		elseif country ==3 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550201_g_TransPos4)
	end



--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId, x550201_g_MissionInfo)
--		EndQuestEvent()
--		DispatchQuestInfo(sceneId, selfId, targetId, x550201_g_ScriptId, x550201_g_MissionName)

	
end



--**********************************

--�о��¼�

--**********************************

function x550201_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x550201_g_ScriptId, x550201_g_MissionName,15)

			
end



--**********************************

--����������

--**********************************

function x550201_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end


--**********************************

--���鿴����

--**********************************

function x550201_CheckPushList(sceneId, selfId, targetId)
	
end

--**********************************

--����

--**********************************

function x550201_ProcAccept(sceneId, selfId)
		--PrintNum(111)

	
end



--**********************************

--����

--**********************************

function x550201_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--����Ƿ�����ύ

--**********************************

function x550201_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--�ύ

--**********************************

function x550201_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

	
end


--���������¼�

--**********************************

function x550201_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x550201_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

