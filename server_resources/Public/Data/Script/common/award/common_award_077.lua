--������

x580076_g_ScriptId = 580076
x580076_g_MissionName = "��ȡ�����뻢������"

--һ�������ʾ�Ľ�Ʒ��
x580076_g_MaxOnceAwardNum = 1

x580076_g_ItemBonus =	{	{zhiye=-1,id=12030427,num=1}
						}

--�����NPC��
function x580076_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x580076_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--δ�жϱ����Ƿ����㹻�ռ�

	x580076_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580076_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580076_g_ScriptId, -1);

end

--�콱
function x580076_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	BeginAddItem( sceneId )

	local	zhiye = GetZhiye(sceneId, selfId)

	local IsHaveItem = 0
	for i,itm in x580076_g_ItemBonus do
		if itm.zhiye == -1 then
			IsHaveItem = 1
			AddBindItem( sceneId, itm.id, itm.num*itemNum )	
		elseif itm.zhiye == zhiye then 
			IsHaveItem = 1
			AddBindItem( sceneId, itm.id, itm.num*itemNum )	
		end
	end

	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		if IsHaveItem == 1 then
			AddItemListToPlayer(sceneId,selfId) 
		end
	else
		--ʧ��дLOG
		local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID������ID���������ȼ�����ǰ������DBIndex,ItemIndex,�ɹ�(1) / ʧ��(0)
		local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,0)
		WriteLog(16,logMsg)
		return
	end

--	AddMoney( sceneId, selfId, 0, 1000*itemNum ,101) 
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
function x580076_ProcAccept( sceneId, selfId )
end

function x580076_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x580076_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x580076_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x580076_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x580076_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x580076_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x580076_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�