
x300941_g_ScriptId 					= 300941
x300941_g_MissionName				= "�����ҡ���ѯ����ս��Ԯ" 
x300941_g_Leader_Index              = 5

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x300941_ProcEnumEvent( sceneId, selfId, targetId )

	--����Ƿ��а��
	local nGuildID = GetGuildID(sceneId,selfId)
	if nGuildID < 0 then
		return
	end
	
	--�ǰ��� 
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300941_g_Leader_Index then
        return
    end
    
    --����Ƿ��й���
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
	
	 --����Ƿ�������
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_QINGLONG_LEADER) == 1 then
    	return
    end
    
    --����Ƿ�����ȸ
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_ZHUQUE_LEADER) == 1 then
    	return
    end
    
    --����Ƿ��ǹ���
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_KING) == 1 then
    	return
    end
    
    --��ʾ��ť
    AddQuestNumText(sceneId,x300941_g_ScriptId,x300941_g_MissionName,3,x300941_g_ScriptId);
    
end

----------------------------------------------------------------------------------------------
--�¼����
----------------------------------------------------------------------------------------------
function x300941_ProcEventEntry(sceneId, selfId,targetId,scriptId,idExt )
	
	if idExt ~=  x300941_g_ScriptId then
		return
	end

	--����Ƿ��а��
	local nGuildID = GetGuildID(sceneId,selfId)
	if nGuildID < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ��ѯ#W#r\t����ʧ��,��û�а�ᡣ");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		return
	end
	
	--�ǰ��� 
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos ~= x300941_g_Leader_Index then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ��ѯ#W#r\t����ʧ��,�����ǰ�����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
        return
    end
    
    --����Ƿ��й���
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ��ѯ#W#r\t����ʧ��,û�й�����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	return    	
    end
	
	 --����Ƿ�������
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_QINGLONG_LEADER) == 1 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ��ѯ#W#r\t����ʧ��,������᲻��ִ�С�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	return
    end
    
    --����Ƿ�����ȸ
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_ZHUQUE_LEADER) == 1 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ��ѯ#W#r\t����ʧ��,��ȸ��᲻��ִ�С�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	return
    end
    
    --����Ƿ��ǹ���
    if IsSpecialCountryOffical(sceneId,selfId,COUNTRY_POSITION_KING) == 1 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ��ѯ#W#r\t����ʧ��,������᲻��ִ�С�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
    	return
    end
	
	--���ͨ��,����GL������Ԯ�б�
	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,targetId)
	GameBattleLairdRequestPlayerAidList(sceneId,selfId,x300941_g_ScriptId);
	
	return 0

end 

----------------------------------------------------------------------------------------------
--���ܼ��
----------------------------------------------------------------------------------------------
function x300941_ProcAcceptCheck( sceneId, selfId, NPCId )

end

----------------------------------------------------------------------------------------------
--������Ԯ��ʼ�¼�
----------------------------------------------------------------------------------------------
function x300941_ProcPlayerAidBegin(sceneId,nPlayerAidCount )
	--�¼���ʼ
	BeginQuestEvent(sceneId)
	if nPlayerAidCount <= 0 then
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ�б�:#W#r\��ǰû����Ԯ��");
	else
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ�б�:#W#r");
	end
end

----------------------------------------------------------------------------------------------
--�����Ԯ��Ϣ
----------------------------------------------------------------------------------------------
function x300941_ProcAddPlayerAid(sceneId,nPlayerAidGUID,strPlayerAidName,nouse1 )
	--�������
	AddQuestNumText(sceneId,x300941_g_ScriptId,strPlayerAidName,3,nPlayerAidGUID);	
end

----------------------------------------------------------------------------------------------
--������Ԯ�����¼�
----------------------------------------------------------------------------------------------
function x300941_ProcPlayerAidEnd(sceneId,selfId )

	--�¼�����
	local targetId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
end

--**********************************
--����
--**********************************
function x300941_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x300941_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x300941_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300941_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x300941_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

--**********************************
--ɱ����������
--**********************************
function x300941_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--���������¼�
--**********************************
function x300941_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300941_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end