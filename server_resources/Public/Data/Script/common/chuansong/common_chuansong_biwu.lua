--�뿪���䳡

--MisDescBegin
x300314_g_ScriptId = 300314
--x300314_g_Name	="���䴫��"

x300314_g_MissionName = "�뿪���䳡"
x300314_g_MissionInfo=" ��ȷ��Ҫ�뿪���䳡��"  --��������
x300314_g_MissionInfo2=""
x300314_g_MissionTarget="    "
x300314_g_MissionComplete="  "					--�������npc˵���Ļ�
x300314_g_ContinueInfo="    "
x300314_g_TransPos1 = "biwu2loulan"
x300314_g_TransPos2 = "biwu2laiyin"
x300314_g_TransPos3 = "biwu2kunlun"
x300314_g_TransPos4 = "biwu2dunhuang"
--������
x300314_g_MoneyBonus = 10000
--�̶���Ʒ���������8��
x300314_g_ItemBonus={}

--��ѡ��Ʒ���������8��
x300314_g_RadioItemBonus={}

--MisDescEnd
x300314_g_ExpBonus = 1000
--**********************************

--������ں���

--**********************************

function x300314_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, x300314_g_MissionInfo)
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x300314_g_ScriptId, x300314_g_MissionName)

end



--**********************************

--�о��¼�

--**********************************

function x300314_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

--	BeginQuestEvent(sceneId)
		AddQuestNumText(sceneId, x300314_g_ScriptId, x300314_g_MissionName)
--	EndQuestEvent()
--	DispatchQuestEventList(sceneId, selfId, targetId)

end



--**********************************

--����������

--**********************************

function x300314_ProcAcceptCheck(sceneId, selfId, targetId)
return 1
end


--**********************************

--���鿴����

--**********************************

function x300314_CheckPushList(sceneId, selfId, targetId)

end

--**********************************

--����

--**********************************

function x300314_ProcAccept(sceneId, selfId)
	local country = GetCurCountry(sceneId, selfId)

    CallScriptFunction(700005,"RestorePlayerCamp", sceneId,selfId)
    SetPlayerMutexState( sceneId,selfId,PLAYER_STATE_DIE,0) --####

	if country == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300314_g_TransPos1)
	elseif country == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300314_g_TransPos2)
	elseif country == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300314_g_TransPos3)
	elseif country == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x300314_g_TransPos4)
	end

end



--**********************************

--����

--**********************************

function x300314_ProcQuestAbandon(sceneId, selfId, MissionId)


end



--**********************************

--����Ƿ�����ύ

--**********************************

function x300314_CheckSubmit( sceneId, selfId, targetId)


end



--**********************************

--�ύ

--**********************************

function x300314_ProcQuestSubmit(sceneId, selfId, targetId, selectRadioId, MissionId)


end


--���������¼�

--**********************************

function x300314_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)

end



--**********************************

--���߸ı�

--**********************************

function x300314_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

end

