
x580071_g_ScriptId = 580071
x580071_g_MissionName = "��ȡ�����"

--һ�������ʾ�Ľ�Ʒ��
x580071_g_MaxOnceAwardNum = 5
x580071_g_5070Exp = 352800
x580071_g_7090Exp = 554400

--�����NPC��
function x580071_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x580071_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--δ�жϱ����Ƿ����㹻�ռ�

	x580071_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580071_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580071_g_ScriptId, -1);

end

--�콱
function x580071_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����
	local nLevel = GetLevel(sceneId,selfId)
	local nExp = 0

	if nLevel >= 60 and nLevel < 70 then
		nExp = nLevel*x580071_g_5070Exp*itemNum
		AddExpAutoLevelup(sceneId,selfId,nExp)
			--�콱�ɹ�
		BeginQuestEvent(sceneId)
		local DoneMSG = format("��ϲ�����������%d�㾭��ֵ",nExp)
		AddQuestText(sceneId,DoneMSG)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
		--д�ɹ�LOG
		local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID������ID���������ȼ�����ǰ������DBIndex,ItemIndex,�ɹ�(1) / ʧ��(0)
		local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,1)
		WriteLog(16,logMsg)

	elseif nLevel >= 70 and nLevel < 85 then
		nExp = nLevel*x580071_g_7090Exp*itemNum
		AddExpAutoLevelup(sceneId,selfId,nExp)
		
		BeginQuestEvent(sceneId)
		local DoneMSG = format("��ϲ�����������%d�㾭��ֵ",nExp)
		AddQuestText(sceneId,DoneMSG)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
		local DoneMSG = "�Բ������ĵȼ��Ѿ������˽�����Χ���޷���ý�����"
		AddQuestText(sceneId,DoneMSG)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

end



--**********************************
--����
--**********************************
function x580071_ProcAccept( sceneId, selfId )
end

function x580071_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x580071_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x580071_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x580071_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x580071_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x580071_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x580071_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�