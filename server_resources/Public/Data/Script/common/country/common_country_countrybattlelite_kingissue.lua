x310154_g_scriptId                      = 310154

x310154_g_Time					= { min = 2000,max = 2059 }	--ʱ������
----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x310154_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    --�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
		
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
	local hour,minute,sec =GetHourMinSec(); --���ʱ���Ƿ���ȷ
	local now = hour *100 + minute
	if now < x310154_g_Time.min or now > x310154_g_Time.max then
		return
	end
	
	
    --����ս�Ƿ���
    local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
    if  camp < 0 then
        return
    end
    
    
    --ȡ�ù���ID
    local nCountry = -1
    if camp == 0 then --���ط���ȡ�ñ�������ID
    	nCountry = GetCurCountry(sceneId, selfId)
    elseif camp == 1 then
    	nCountry = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_MatchCountry", sceneId, selfId)
    end
    --�жϹ���ID�Ƿ���Ч
    if nCountry < 0 or nCountry > 3 then
    	return
    end
    
    --ֻ������Է����ط������ͽ��������ܵ������ʹ�ù����ټ�
    if camp == 0 then
    	local nTargetSceneId = nCountry*100 + 86
		local nTargetSceneId1 = nCountry*100 + 58
    	if nTargetSceneId == sceneId then
    	 	
    	end
		if nTargetSceneId1 == sceneId then
    		  	
    	end
    else
    	return
    end
    
    --���������ټ���ť
    AddQuestNumText(sceneId,x310154_g_scriptId,"������ս���ط������ټ���",3);
    
    --����־
    local CountryID = GetCurCountry(sceneId,selfId)
		
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "ErrorName"
	end
	
    local strMsg = format("CBL:<Info>x310154_ProcEnumEvent [kingissue] sceneId = %d, name=%s, nCountryId=%d", sceneId, name, CountryID  )
    WriteLog( 1, strMsg )
end

function x310154_OnReturn(sceneId, selfId,MissionData,MissionId)

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    --����ս�Ƿ���
    if CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId) < 0 then
        return
    end
    
     --ֻ�й�����������
    if IsKing(sceneId, selfId) <= 0  then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y������ս�������ټ���#W#r\tֻ�й�������ʹ�á�����ս�������ټ���!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,selfId)
		
		return
    end
    
    
    if MissionData == nil or MissionData > 3 or MissionData <= 0 then
    	--�����κ����������Ϊ��ʹ�ô��������ޣ�����ԭ��
		
		local CountryID = GetCurCountry(sceneId,selfId)
		
		local strName = GetName( sceneId,selfId )
		if strName == nil then
			strName = " "
		end
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y������ս�������ټ���#W#r\t�ܱ�Ǹ��������ս�������ټ���ֻ��ʹ��3��!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,selfId)
		
		LuaScenceM2Player( sceneId,selfId,"�ܱ�Ǹ��������ս�������ټ���ֻ��ʹ��3��!",strName,3,1 )
		LuaScenceM2Player( sceneId,selfId,"�ܱ�Ǹ��������ս�������ټ���ֻ��ʹ��3��!",strName,2,1 )
		
		local name = GetName(sceneId,selfId)
		if name == nil then
			name = "ErrorName"
		end
		
		local strMsg = format("CBL:<Error>x310154_OnReturn [kingissue] sceneId = %d, name=%s, count=%d, nCountryId=%d", sceneId, name, MissionData, CountryID  )
        WriteLog( 1, strMsg )
        
    	return
    end
    
    local CountryID = GetCurCountry(sceneId,selfId)
	CountryBattleLiteKingIssue(sceneId, selfId)
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, format("#Y������ս�������ټ���#W#r\t��ʹ���ˡ�����ս�������ټ����ʣ%d�Σ�",MissionData-1));
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,selfId)
	
	local npcGUID = GetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_KINGISSUE_NPC)
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCountryQuestData(sceneId, nCountryId, CD_INDEX_COUNTRYBATTLELITE_KINGISUE_NPC,npcGUID)
	
	--�򱾹��㲥
	local msg = "���������ˡ�����ս���ټ���";
	local countryid = GetCurCountry(sceneId,selfId)
	LuaAllScenceM2Country(sceneId,msg,CountryID,5,1)
	
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "ErrorName"
	end
	
	local strMsg = format("CBL:<Info>x310154_OnReturn [kingissue] sceneId = %d, name=%s, leftcount=%d, nCountryId=%d", sceneId, name, 2, CountryID  )
    WriteLog( 1, strMsg )	
	
end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x310154_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

    --�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    if CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId) < 0 then
        return
    end
    
    --ֻ�й�����������
    if IsKing(sceneId, selfId) <= 0  then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y������ս�������ټ���#W#r\tֻ�й�������ʹ�á�����ս�������ټ���!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,selfId)
		
		return
    end
    
    --����NPCID
    local npcGUID = GetMonsterGUID( sceneId, npcId)
    SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_KINGISSUE_NPC,npcGUID)
    
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCountryQuestData(sceneId, nCountryId, CD_INDEX_COUNTRYBATTLELITE_KINGISUE_NPC,npcGUID)
    
    --�ص����������¼�
    GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_KINGISUSE, x310154_g_scriptId,-1,"OnReturn")
    
end


function x310154_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310154_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310154_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310154_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x310154_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x310154_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x310154_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x310154_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x310154_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end