--����ؽ�

--MisDescBegin
x550200_g_ScriptId = 550200
x550200_g_MissionName = "��������ı�����"
x550200_g_MissionInfo=" ���������ƽѰɡ�"  --��������
x550200_g_MissionInfo2=""
x550200_g_MissionQuestID	=	2722
x550200_g_MissionComplete="  "					--�������npc˵���Ļ�
x550200_g_ContinueInfo="    "
x550200_g_TransPos1 = "xinshoumigong1loulanin"
x550200_g_TransPos2 = "xinshoumigong1laiyinin"
x550200_g_TransPos3 = "xinshoumigong1kunlunin"
x550200_g_TransPos4 = "xinshoumigong1dunhuangin"
--������
x550200_g_MoneyBonus = 10000
--�̶���Ʒ���������8��
x550200_g_ItemBonus={}

--��ѡ��Ʒ���������8��
x550200_g_RadioItemBonus={}

--MisDescEnd
x550200_g_ExpBonus = 1000
--**********************************

--������ں���

--**********************************

function x550200_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local country = GetCurCountry(sceneId,selfId)
	if country == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550200_g_TransPos1)
	elseif country ==1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550200_g_TransPos2)
	elseif country ==2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550200_g_TransPos3)
	elseif country ==3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550200_g_TransPos4)
	end
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId, x550200_g_MissionInfo)
--		EndQuestEvent()
--		DispatchQuestInfo(sceneId, selfId, targetId, x550200_g_ScriptId, x550200_g_MissionName)

	
end



--**********************************

--�о��¼�

--**********************************

function x550200_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

--	if IsHaveQuest(sceneId, selfId,x550200_g_MissionQuestID) > 0 then

		AddQuestNumText(sceneId, x550200_g_ScriptId, x550200_g_MissionName,16)

--	else 
--		return
--	end
			
end



--**********************************

--����������

--**********************************

function x550200_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end


--**********************************

--���鿴����

--**********************************

function x550200_CheckPushList(sceneId, selfId, targetId)
	
end

--**********************************

--����

--**********************************

function x550200_ProcAccept(sceneId, selfId)
		
		
--	  BeginQuestEvent(sceneId)
--					NewWorld(sceneId,selfId,96,65,64,550200)
--		EndQuestEvent()
    
end



--**********************************

--����

--**********************************

function x550200_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--����Ƿ�����ύ

--**********************************

function x550200_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--�ύ

--**********************************

function x550200_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

	
end


--���������¼�

--**********************************

function x550200_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x550200_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

