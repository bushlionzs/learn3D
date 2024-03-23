--���������

x580022_g_ScriptId = 580022
x580022_g_MissionName = "��ȡ��ٻع����"

--һ�������ʾ�Ľ�Ʒ��
x580022_g_MaxOnceAwardNum = 1

x580022_g_ItemBonus =	{	}

--�����NPC��
function x580022_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x580022_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--δ�жϱ����Ƿ����㹻�ռ�

	x580022_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580022_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580022_g_ScriptId, -1);

end

--�콱
function x580022_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	BeginAddItem( sceneId )

	local	nLevel = GetLevel(sceneId, selfId)
	local nExp = nLevel * 180000 * itemNum
	local nMoney = nLevel * 1000 * itemNum
	
	AddExpAutoLevelup(sceneId,selfId,nExp) --�Զ���������
	AddMoney(sceneId,selfId,1,nMoney,101)	--��������

--	AddMoney( sceneId, selfId, 0, 1000*itemNum,101 ) 
--
--	--�콱�ɹ�
--	BeginQuestEvent(sceneId)
--	local DoneMSG = format("��ϲ���������������%d�ģ�",1000*itemNum)
--	AddQuestText(sceneId,DoneMSG)
--	EndQuestEvent(sceneId)
--	DispatchQuestTips(sceneId,selfId)

	--д�ɹ�LOG
	local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID������ID���������ȼ�����ǰ������DBIndex,ItemIndex,�ɹ�(1) / ʧ��(0)
	local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,1)
	WriteLog(16,logMsg)

end



--**********************************
--����
--**********************************
function x580022_ProcAccept( sceneId, selfId )
end

function x580022_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x580022_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x580022_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x580022_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x580022_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x580022_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x580022_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�