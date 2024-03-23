--���˰ﹱ����

x580058_g_ScriptId = 580058
x580058_g_MissionName = "��ȡ��Ʒ"

--һ�������ʾ�Ľ�Ʒ��
x580058_g_MaxOnceAwardNum = 5

x580058_g_ItemBonus =	{
						}

--�����NPC��
function x580058_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x580058_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--δ�жϱ����Ƿ����㹻�ռ�

	x580058_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580058_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580058_g_ScriptId, -1);

end

--�콱
function x580058_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	if GetGuildID(sceneId, selfId) < 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�Բ�����Ŀǰû�а��, ��ȡʧ�ܣ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		--ʧ��дLOG
		local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID������ID���������ȼ�����ǰ������DBIndex,ItemIndex,�ɹ�(1) / ʧ��(0)
		local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,0)
		WriteLog(16,logMsg)
		return
	end
	
	local nValue = 1*itemNum
	AddGuildUserPoint(sceneId, selfId, nValue)	--���Ӱﹱ
	
	--�콱�ɹ�
	BeginQuestEvent(sceneId)
	--local title,text,scriptId = GetAwardInfo( sceneId, selfId,index )
	AddQuestText(sceneId,format("��ϲ�㣬������%d��ﹱ", nValue))
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)

	--д�ɹ�LOG
	local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID������ID���������ȼ�����ǰ������DBIndex,ItemIndex,�ɹ�(1) / ʧ��(0)
	local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,1)
	WriteLog(16,logMsg)

end



--**********************************
--����
--**********************************
function x580058_ProcAccept( sceneId, selfId )
end

function x580058_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x580058_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x580058_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x580058_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x580058_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x580058_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x580058_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�