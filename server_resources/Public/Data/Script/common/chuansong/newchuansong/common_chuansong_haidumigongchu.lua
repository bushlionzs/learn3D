--�뿪���ִ�

--MisDescBegin
x550203_g_ScriptId = 550203
x550203_g_MissionName = "�뿪����"
x550203_g_MissionInfo=" �ҿ��Խ����ͻش��"  --��������
x550203_g_MissionInfo2=""
--x550203_g_MissionQuestID	=	2723
x550203_g_MissionComplete="  "					--�������npc˵���Ļ�
x550203_g_ContinueInfo="    "
x550203_g_TransPos1 = "xinshoumigong2loulan"
x550203_g_TransPos2 = "xinshoumigong2laiyin"
x550203_g_TransPos3 = "xinshoumigong2kunlun"
x550203_g_TransPos4 = "xinshoumigong2dunhuang"
--������
x550203_g_MoneyBonus = 10000
--�̶���Ʒ���������8��
x550203_g_ItemBonus={}

--��ѡ��Ʒ���������8��
x550203_g_RadioItemBonus={}

--MisDescEnd
x550203_g_ExpBonus = 1000
--**********************************

--������ں���

--**********************************

function x550203_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local country = GetCurCountry(sceneId,selfId)
	if country == 0 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550203_g_TransPos1)
    elseif country ==1 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550203_g_TransPos2)
		elseif country ==2 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550203_g_TransPos3)
		elseif country ==3 then
			CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550203_g_TransPos4)
 	end
 	 	   
--		BeginQuestEvent(sceneId)
--			AddQuestText(sceneId, x550203_g_MissionInfo)
--		EndQuestEvent()
--		DispatchQuestInfo(sceneId, selfId, targetId, x550203_g_ScriptId, x550203_g_MissionName)

	
end



--**********************************

--�о��¼�

--**********************************

function x550203_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

		AddQuestNumText(sceneId, x550203_g_ScriptId, x550203_g_MissionName,15)

			
end



--**********************************

--����������

--**********************************

function x550203_ProcAcceptCheck(sceneId, selfId, targetId)
	return 1
end


--**********************************

--���鿴����

--**********************************

function x550203_CheckPushList(sceneId, selfId, targetId)
	
end

--**********************************

--����

--**********************************

function x550203_ProcAccept(sceneId, selfId)
		--PrintNum(111)
		
	  BeginQuestEvent(sceneId)
					NewWorld(sceneId,selfId,24,120,465,550202)
		EndQuestEvent()
    
end



--**********************************

--����

--**********************************

function x550203_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--����Ƿ�����ύ

--**********************************

function x550203_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--�ύ

--**********************************

function x550203_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)

	
end


--���������¼�

--**********************************

function x550203_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x550203_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

