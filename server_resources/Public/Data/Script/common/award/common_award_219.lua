--��ȡ�弶ƽ��֮��	11010115

x580219_g_ScriptId = 580219
x580219_g_MissionName = "��ȡ�弶ƽ��֮��"

--һ�������ʾ�Ľ�Ʒ��
x580219_g_MaxOnceAwardNum = 1
x580219_g_ItemBonus =	{	{zhiye=-1,id=11010115,num=1}	--�弶ƽ��֮��
						}


--�����NPC��
function x580219_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x580219_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--δ�жϱ����Ƿ����㹻�ռ�

	x580219_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580219_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580219_g_ScriptId, -1);

end

--�콱
function x580219_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	BeginAddItem( sceneId )

	local	zhiye = GetZhiye(sceneId, selfId)

	local IsHaveItem = 0
	for i,itm in x580219_g_ItemBonus do
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

--	AddMoney( sceneId, selfId, 3, 12000000*itemNum,101 ) 

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����

	--�콱�ɹ�
	BeginQuestEvent(sceneId)
	local DoneMSG =  format("��ϲ�����������"..title..itemNum.."��")
	AddQuestText(sceneId,DoneMSG)
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
function x580219_ProcAccept( sceneId, selfId )
end

function x580219_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x580219_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x580219_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x580219_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x580219_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x580219_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x580219_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�