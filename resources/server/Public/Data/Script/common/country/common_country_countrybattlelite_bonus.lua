x310151_g_scriptId                      = 310151
x310151_g_MissionId						= 7559
x310151_g_TickBuf						= 8727
x310151_g_BufID 						= {8719,8720,8721,8722,8723,8724,8725,8726,8727}--���BUFID,����ҽ�������սʱ,���Ӵ˱��ȡBUFID,�˱�˳��Ϊ:¥��,����,����,�ػ�
----------------------------------------------------------------------------------------------
--�����Ч��
----------------------------------------------------------------------------------------------
function x310151_CheckValid( sceneId, selfId  )
    
    --����Ƿ�������
    local nWeek = GetWeek()
    if nWeek ~= 6 then
       return 0
    end
    if IsPlayerStateNormal(sceneId,selfId ) ~= 1 then
		return 0
	end
    
    --����Ƿ���������
    if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsNewFlow",sceneId,selfId) == 1 then
    	
    	--����Ƿ�����콱
    	if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"IsCanReciveBonus",sceneId,selfId) ~= 1 then
    		return 0
    	end
    	
    	--�����ڽ�
    	return 1
    end
    
    --����Ƿ���С��ս����ʱ��
    local today = GetDayOfYear()
    local mdtoday = x310151_GetMissionDay( sceneId,selfId)
    if today ~= mdtoday then
        return -1
    end
    
    local minTime = GetMinOfDay()
    
    --�ڲ���ʱ�����
    local nFrom = 21*60 + 1
    local nTo   = 21*60 + 20

    if minTime < nFrom then
        return -2
    end
    
    if minTime > nTo then
        return -3
    end
    
    return 1
end


----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x310151_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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

    if x310151_CheckValid( sceneId, selfId  ) <= 0 then
        return
    end
    
    AddQuestNumText(sceneId,x310151_g_scriptId,"����ս��������ȡ",3);
end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x310151_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

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

    if x310151_CheckValid( sceneId, selfId  ) <= 0 then
        return
    end
    
    --���õ�ǰNPC
    SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,npcId)
    
    --�ط��Ļ�����Ҫ����GLServer��������
    GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_KILLCOUNT,x310151_g_scriptId,-1,"OnGiveBonus")
    
end


----------------------------------------------------------
--ɾ��BUF
----------------------------------------------------------
function x310151_CancelBufId( sceneId,selfId )

		for i,item in x310151_g_BufID do
		if IsHaveSpecificImpact(sceneId,selfId,item) == 1 then
			CancelSpecificImpact(sceneId,selfId,item)
		end
	end

end

----------------------------------------------------------------------------------------------
--������
----------------------------------------------------------------------------------------------
function x310151_OnGiveBonus( sceneId,selfId ,nKillCout,missionId )

    if x310151_CheckValid( sceneId, selfId  ) <= 0 then
        return
    end
    
    if nKillCout < 0 then
        return
    end
    
    local npcId = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
    
    local nCampFlag = -1
    if IsHaveQuest(sceneId,selfId, x310151_g_MissionId) > 0 then
    	
    	local misIndex = GetQuestIndexByID( sceneId, selfId, x310151_g_MissionId )
    	nCampFlag = GetQuestParam( sceneId,selfId,misIndex,5) 

    	if DelQuest( sceneId,selfId,x310151_g_MissionId) <=0 then
    		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "����ɾ��ʧ�ܣ������ԣ�");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return    		
    	else
    		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "������ˡ����ҡ�����ս��");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)	
			x310151_CancelBufId( sceneId,selfId )
    	end
    else
    	--���û������,������ȡ����
    	return
    end

    
    GamePlayScriptLog( sceneId, selfId, 1512)
    
    local level = GetLevel( sceneId,selfId)
    
    --������ֵ�ӳ�    
    local nExpExt = 0
    local n1 = -1
    local n2 = -1
    local n3 = -1
    local nKillCountBak = nKillCout
    
    if nCampFlag == 0  then

    	
    	--���ط��ļ���
    	n1=5
    	n2=4
    	n3=1

    	while nKillCout >= 10000 do
    		nKillCout = nKillCout - 10000
    		n1 = n1 - 1
    	end

    	while nKillCout >= 1000 do
    		nKillCout = nKillCout - 1000
    		n2 = n2 - 1
    	end

    	while nKillCout >= 100 do
    		nKillCout = nKillCout - 100
    		n3 = n3 - 1
    	end

	elseif nCampFlag == 1 then

		
		--�������ļ���
		n1 = 0
    	n2 = 0
    	n3 = 0
    	
    	while nKillCout >= 10000 do
    		nKillCout = nKillCout - 10000
    		n1 = n1 + 1
    	end
    	
    	while nKillCout >= 1000 do
    		nKillCout = nKillCout - 1000
    		n2 = n2 + 1
    	end
    	
    	while nKillCout >= 100 do
    		nKillCout = nKillCout - 100
    		n3 = n3 + 1
    	end
	end
	
	
	if n1 > 0 then
    	nExpExt = nExpExt + level * 12178 * n1
    end
    
    if n2 > 0 then
    	nExpExt = nExpExt + level * 12178 * n2
    end
    
    if n3 > 0 then
    	nExpExt = nExpExt + level * 12178 * n3
    end
        
    --���㽱��    
    local exp  = level * 28800
    local rong = nKillCout * 60
	
    if nKillCout == 0 then
        
        --��������������������Ϊ0�����ػ�����Ϊ0�������������
        exp = level * 28800
        rong = 30
        		
    end
    
    exp = exp + (nExpExt*2)
    
    --�����齱��
    if exp > 0 then
        AddExp( sceneId,selfId,exp )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��ϲ�����#R����"..exp.."��#o�Ľ���");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,format("��ϲ�����#R����"..exp.."��#o�Ľ���"),8,2)
    end
    
    
    --������
    if rong > 0 then
        AddHonor( sceneId,selfId,rong )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��ϲ�����#R����"..rong.."��#o�Ľ���");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,format("��ϲ�����#R����"..rong.."��#o�Ľ���"),8,2)
    end 

    

    --�ټ���־    
    local name = GetName(sceneId,selfId)
    if name == nil then
        name = "ErrorName"
    end
    
    local nCountry  = GetCurCountry( sceneId,selfId)
    local strMsg = format("CBL:<Info>x310151_OnGiveBonus sceneId=%d, name=%s,level=%d,country=%d,killcount=%d exp=%d, rong=%d n1=%d,n2=%d,n3=%d,nKillCout=%d nCampFlag=%d ", 
    					  sceneId, name,level,nCountry,nKillCout, exp, rong,n1,n2,n3,nKillCountBak,nCampFlag )
    WriteLog( 1, strMsg )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310151_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310151_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310151_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310151_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x310151_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x310151_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x310151_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x310151_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x310151_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

----------------------------------------------------------------------------------------------
--ȡ����������
----------------------------------------------------------------------------------------------
function x310151_GetMissionDay( sceneId,selfId)
	
	--�Ƿ��д�����
	if IsHaveQuest(sceneId,selfId, x310151_g_MissionId) <= 0 then
		return -100 
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, 7559)
	if misIndex < 0 then
		return -100
	end
	
	return GetQuestParam( sceneId,selfId,misIndex,4) -100		
end