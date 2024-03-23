
x561103_g_ScriptId = 561103
x561103_g_MissionName = "��ȡ��Ʒ"

--һ�������ʾ�Ľ�Ʒ��
x561103_g_MaxOnceAwardNum = 5

--�����NPC��
function x561103_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	return 0
	
end




--�������ť������������ִ�д˽ű�
function x561103_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	if  x561103_HaveBagSpace(sceneId, selfId,index,targetId) == 1 then
		x561103_DispatchMissionInfo( sceneId, selfId, targetId,index)
	end

end

function x561103_DispatchMissionInfo( sceneId, selfId, targetId,index)

	local dbIndex = GetPlayerRuntimeData( sceneId, selfId, index+x561103_g_MaxOnceAwardNum )
	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, dbIndex )

	local id = GetPlayerRuntimeData( sceneId, selfId, index )

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,id )--���������ӱ��еõ�����
	local str = format("%s \n  %s",title,text)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)

	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x561103_g_ScriptId, -1);

end


function x561103_HaveBagSpace(sceneId, selfId,index,targetId)

	local id = GetPlayerRuntimeData( sceneId, selfId, index )
	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,id )

	local BagNum = BagNeedSpace

	if BagNeedSpace > 0 then
		local itemNum = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_NUM1+index-RD_HUMAN_AWARE_INDEX1 ) 
		if MinSpliceNum == 0 then
			MinSpliceNum = 1
		end

		itemNum = itemNum * BagNeedSpace	
		BagNum = ceil(itemNum / MinSpliceNum )
		if BagNum < BagNeedSpace then
			BagNum = BagNeedSpace
		end		
	else 
		BagNum = BagNeedSpace
	end

	--�жϱ����Ƿ����㹻�ռ�
	if GetBagSpace( sceneId, selfId ) <	BagNum then

		BeginQuestEvent(sceneId)
		local str = format("�˴��콱������������ҪԤ��%d���ո��㵱ǰ�����ռ䲻����",BagNum)
		AddQuestText(sceneId,str)
		EndQuestEvent(sceneId)

		if targetId == -1 then
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,str,8,2)
		else
			DispatchQuestEventList(sceneId,selfId,targetId)
		end

		return 0
	end

	return 1

end


--�콱������
function x561103_OnAddAwardManager( sceneId, selfId, result,itemNum,index,dbIndex )
	
	if result == 0 then
		--�콱ʧ��
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�콱ʧ�ܣ�û�в�ѯ�������¼������ڣ����Ժ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	if result == 2 then
		--���˻��콱������ʱ����
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�˻��콱������ʱ���ᣬ�Ժ�����")
		EndQuestEvent(sceneId)
		return 
	end

	--trophy.tab��������ת��Ϊȫ�ֱ���(RuntimeData)������
	local runData = -1
	for tmpIndex=0, x561103_g_MaxOnceAwardNum-1 do

		local logicIndex = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+tmpIndex )
		local tmpDbIndex = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_DB_INDEX1+tmpIndex ) 
		
		if index == logicIndex and tmpDbIndex == dbIndex then
			runData = RD_HUMAN_AWARE_INDEX1 + tmpIndex  	
		end
	end

	if  runData ~=-1 and x561103_HaveBagSpace(sceneId, selfId,runData,-1) ~= 1 then
		return
	end

	local title,text,scriptId,BagNeedSpace,MinSpliceNum = GetAwardInfo( sceneId, selfId,index )--���������ӱ��еõ�������Ϣ
	CallScriptFunction( scriptId, "AddAward", sceneId, selfId ,itemNum,index,dbIndex ) 

	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX, -1 )

	for i=0, x561103_g_MaxOnceAwardNum-1 do
		SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_INDEX1+i, -1 )
		SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_DB_INDEX1+i, -1 )
		SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_NUM1+i, -1 )
	end

end

--**********************************
--����
--**********************************
function x561103_ProcAccept( sceneId, selfId )

	local tabIndex = -1	--trophy.tab���е�����
	local dbIndex = GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_INDEX )
		
	--dbIndexת��Ϊtrophy.tab���е�����
	for i=0, x561103_g_MaxOnceAwardNum-1 do

		if dbIndex ==  GetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_AWARE_DB_INDEX1+i ) then
			tabIndex = RD_HUMAN_AWARE_DB_INDEX1+i - x561103_g_MaxOnceAwardNum  
		end
	end

	if tabIndex ~= -1 and x561103_HaveBagSpace(sceneId, selfId,tabIndex,-1) ~= 1 then
		return		
	end

	local awardType = 0
	
	--1000�Ժ����CDKEY�콱
	if GetPlayerRuntimeData( sceneId, selfId, tabIndex )>=1000 then
	
		awardType = 1
		
	else 
	
		awardType = 0
		
	end

	--֪ͨBalling�콱
	GetAward( sceneId, selfId, dbIndex, awardType )

end


function x561103_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end
--�����ȷ����
function x561103_ProcQuestAccept( sceneId, selfId, NPCId )
end

--**********************************
--����
--**********************************
function x561103_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x561103_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x561103_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x561103_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x561103_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
