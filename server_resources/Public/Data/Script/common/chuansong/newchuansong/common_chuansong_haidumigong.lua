--����ؽ�

--MisDescBegin
x550202_g_ScriptId = 550202
x550202_g_MissionName = "������ϵļ�̳"
x550202_g_MissionInfo=" �ҿ���������ɽ�ȣ����ȷ��"  --��������
x550202_g_MissionInfo2=""
x550202_g_MissionQuestID	=	2723
x550202_g_MissionComplete="  "					--�������npc˵���Ļ�
x550202_g_ContinueInfo="    "
x550202_g_TransPos1 = "xinshoumigong2loulanin"
x550202_g_TransPos2 = "xinshoumigong2laiyinin"
x550202_g_TransPos3 = "xinshoumigong2kunlunin"
x550202_g_TransPos4 = "xinshoumigong2dunhuangin"
--������
x550202_g_MoneyBonus = 10000
--�̶���Ʒ���������8��
x550202_g_ItemBonus={}

--��ѡ��Ʒ���������8��
x550202_g_RadioItemBonus={}

--MisDescEnd
x550202_g_ExpBonus = 1000
--**********************************

--������ں���

--**********************************

function x550202_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local country = GetCurCountry(sceneId,selfId)
	if country == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550202_g_TransPos1)
	elseif country ==1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550202_g_TransPos2)
	elseif country ==2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550202_g_TransPos3)
	elseif country ==3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550202_g_TransPos4)
	end	
		
		
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId, x550202_g_MissionInfo)
--		EndQuestEvent()
--		DispatchQuestInfo(sceneId, selfId, targetId, x550202_g_ScriptId, x550202_g_MissionName)

	
end



--**********************************

--�о��¼�

--**********************************

function x550202_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	--if IsHaveQuest(sceneId, selfId,x550202_g_MissionQuestID) > 0 then

		AddQuestNumText(sceneId, x550202_g_ScriptId, x550202_g_MissionName,16)

	--else 
		--return
	--end
			
end



--**********************************

--����������

--**********************************

function x550202_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end


--**********************************

--���鿴����

--**********************************

function x550202_CheckPushList(sceneId, selfId, targetId)
	
end

--**********************************

--����

--**********************************

function x550202_ProcAccept(sceneId, selfId)
		
		
--	  BeginQuestEvent(sceneId)
--					NewWorld(sceneId,selfId,163,65,64, 550202)
--		EndQuestEvent()
    
end



--**********************************

--����

--**********************************

function x550202_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--����Ƿ�����ύ

--**********************************

function x550202_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--�ύ

--**********************************

function x550202_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

	
end


--���������¼�

--**********************************

function x550202_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x550202_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

