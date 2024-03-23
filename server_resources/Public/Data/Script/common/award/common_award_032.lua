
x580031_g_ScriptId = 580031
x580031_g_MissionName = "������չ�ֿ�"

--һ�������ʾ�Ľ�Ʒ��
x580031_g_MaxOnceAwardNum = 5

x580031_g_ItemBonus =	{
							{zhiye=-1,id=12030302,num=1}
						}

--�����NPC��
function x580031_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end



--�������ť������������ִ�д˽ű�
function x580031_ProcEventEntry( sceneId, selfId, targetId,state,index )	
	
	--δ�жϱ����Ƿ����㹻�ռ�

	x580031_DispatchMissionInfo( sceneId, selfId, targetId,index)

end

function x580031_DispatchMissionInfo( sceneId, selfId, targetId,index)

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x580031_g_ScriptId, -1);

end

--�콱
function x580031_AddAward( sceneId, selfId,itemNum,index, dbIndex )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�����
	local storesize = GetBankSize(sceneId,selfId)
	if storesize == 36 then
		ExpandBankSize(sceneId,selfId,36)
		if storesize == 72 then
			--�콱�ɹ�
			BeginQuestEvent(sceneId)
			local DoneMSG = "��ϲ�������ɹ���������չ�ֿ⣡"
			AddQuestText(sceneId,DoneMSG)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		
			--д�ɹ�LOG
			local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID������ID���������ȼ�����ǰ������DBIndex,ItemIndex,�ɹ�(1) / ʧ��(0)
			local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,1)
			WriteLog(16,logMsg)
		else
			--ʧ��дLOG
			local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID������ID���������ȼ�����ǰ������DBIndex,ItemIndex,�ɹ�(1) / ʧ��(0)
			local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,0)
			WriteLog(16,logMsg)
			return
		end
	elseif storesize > 36 then
--		AddMoney(sceneId,selfId,1,200000,101)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"���Ѿ���������չ�ֿ⣬�޷���ñ��ο�����չ�ֿ�Ľ�����")
--		AddQuestText(sceneId,"�������200�������Ľ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		
		--ʧ��дLOG
			local logFmtMsg         = "%u,%d,\"%s\",%d,%d,%d,%d,%d" --GUID������ID���������ȼ�����ǰ������DBIndex,ItemIndex,�ɹ�(1) / ʧ��(0)
			local logMsg = format(logFmtMsg,GetPlayerGUID( sceneId,selfId ),GetWorldId(sceneId,selfId),GetName( sceneId,selfId ),GetLevel(sceneId,selfId),sceneId,dbIndex,index,0)
			WriteLog(16,logMsg)
			
		return
		
	end

end



--**********************************
--����
--**********************************
function x580031_ProcAccept( sceneId, selfId )
end

function x580031_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x580031_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x580031_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x580031_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x580031_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x580031_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x580031_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�