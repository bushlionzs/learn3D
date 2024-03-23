x310150_g_scriptId                      = 310150

x310150_g_CountryBattleLite_Begin       = 1     --��ʼС��ս
x310150_g_CountryBattleLite_End         = 2     --����С��ս

x310150_g_MissionScriptId 				= 310155
x310150_g_MissionId 					= 7559

x310150_g_TickBuf						= 8727
x310150_g_BufID							= {8719,8720,8721,8722,8723,8724,8725,8726,8727}	--���BUFID,����ҽ�������սʱ,���Ӵ˱��ȡBUFID,�˱�˳��Ϊ:¥��,��ɽ,����,�ػ�

x310150_g_Monster_x51                   ={}
x310150_g_Monster_x50                   ={}
x310150_g_Monster_x58					={}
x310150_g_Monster_x86					={}
x310150_g_Monster_x104 					={}
x310150_g_Monster_x105		 			={}
x310150_g_Monster_x106 					={}
x310150_g_Monster_x107 					={}
x310150_g_Monster_x108 					={}
x310150_g_Monster_x109 					={}
x310150_g_Monster_x110 					={}
x310150_g_Monster_x111 					={}

x310150_g_Match0                        ={} --�����������ط�
x310150_g_Match1                        ={} --�����������ط�

x310150_g_MatchScore0                   ={}
x310150_g_MatchScore1                   ={}

x310150_g_BonusFlag0					={}--������־
x310150_g_BonusFlag1					={}--������־


----------------------------------------------------------------------------------------------
--��ʼ����ͼ����
----------------------------------------------------------------------------------------------
function x310150_OnMapInit(sceneId)

	x310150_g_Monster_x51[sceneId]   ={}
	x310150_g_Monster_x50[sceneId]   ={}
	x310150_g_Monster_x58[sceneId]	 ={}
	x310150_g_Monster_x86[sceneId]	 ={}
	x310150_g_Monster_x104[sceneId]	 ={}
	x310150_g_Monster_x105[sceneId]	 ={}
	x310150_g_Monster_x106[sceneId]	 ={}
	x310150_g_Monster_x107[sceneId]	 ={}
	x310150_g_Monster_x108[sceneId]	 ={}
	x310150_g_Monster_x109[sceneId]	 ={}
	x310150_g_Monster_x110[sceneId]	 ={}
	x310150_g_Monster_x111[sceneId]	 ={}
	
	x310150_g_Match0[sceneId]       = { -1,-1 } --�����������ط�
	x310150_g_Match1[sceneId]       = { -1,-1 } --�����������ط�
	
	x310150_g_MatchScore0[sceneId]  = { 0,0 }
	x310150_g_MatchScore1[sceneId]  = { 0,0 }
	
	x310150_g_BonusFlag0[sceneId]	= {-1,-1}--������־
	x310150_g_BonusFlag1[sceneId]	= {-1,-1}--������־

end

----------------------------------------------------------------------------------------------
--�������Ƿ��ǽ�����
----------------------------------------------------------------------------------------------
function x310150_IsCountryAttact(sceneId, nCountry )
	
	if nCountry == x310150_g_Match0[sceneId][1] then
        return 1
    end
    
    if nCountry == x310150_g_Match1[sceneId][1] then
        return 1
    end
    
    
    return 0
	
end

----------------------------------------------------------------------------------------------
--�Ƿ���ǰ����
----------------------------------------------------------------------------------------------
function x310150_IsBattleFinished( sceneId,selfId )

	local nCountryId = GetCurCountry(sceneId,selfId)
	if x310150_IsCountryAttact( sceneId, nCountryId ) == 1 then
	
		--�Ѿ�����
		if x310150_g_Match0[sceneId][1] == -1 then
			return 1
		end
		
		
		--��ǰ����
		if x310150_g_Match0[sceneId][1] == nCountryId then
			
			if x310150_g_MatchScore0[sceneId][1] == 10 then
				return 1
			end			
		end
		
		if x310150_g_Match1[sceneId][1] == nCountryId then
			
			if x310150_g_MatchScore1[sceneId][1] == 10 then
				return 1
			end			
		end
		
		--û�н���
		return 0
	else
		
		--�Ѿ�����
		if x310150_g_Match0[sceneId][2] == -1 then
			return 1
		end
		
		--��ǰ����
		if x310150_g_Match0[sceneId][2] == nCountryId then
			
			if x310150_g_MatchScore0[sceneId][2] == 0 then
				return 1
			end			
		end
		
		if x310150_g_Match1[sceneId][2] == nCountryId then
			
			if x310150_g_MatchScore1[sceneId][2] == 0 then
				return 1
			end			
		end
		
		--û�н���
		return 0
		
	end

end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x310150_ProcEventEntry( sceneId ,selfId, npcId )
end

----------------------------------------------------------------------------------------------
--���ݳ���ID��ȡ�ù���ID
----------------------------------------------------------------------------------------------
function x310150_GetCountryIdBySceneId( sceneId )
    
    if sceneId == 50 or sceneId == 51 or sceneId == 58 or sceneId == 86  then
        return 0
    elseif sceneId == 150 or sceneId == 151 or sceneId == 158 or sceneId == 186  then
        return 1
    elseif sceneId == 250 or sceneId == 251 or sceneId == 258 or sceneId == 286  then
        return 2
    elseif sceneId == 350 or sceneId == 351 or sceneId == 358 or  sceneId == 386  then
        return 3   
    end 
end

----------------------------------------------------------------------------------------------
--ȡ�ý���������Թ���
----------------------------------------------------------------------------------------------
function x310150_GetMatchCountry( sceneId )
    
    local nCountry = x310150_GetCountryIdBySceneId( sceneId )
    
    if nCountry == x310150_g_Match0[sceneId][2] then
        return x310150_g_Match0[sceneId][1]
    end
    
    if nCountry == x310150_g_Match1[sceneId][2] then
        return x310150_g_Match1[sceneId][1]
    end
    
    return -1        
end


----------------------------------------------------------------------------------------------
--ȡ�ý���������Թ���
----------------------------------------------------------------------------------------------
function x310150_GetMatchCountryByCountryID( nCountry )
    
    if nCountry == x310150_g_Match0[sceneId][2] then
        return x310150_g_Match0[sceneId][1]
    end
    
    if nCountry == x310150_g_Match1[sceneId][2] then
        return x310150_g_Match1[sceneId][1]
    end
    
    return -1        
end

----------------------------------------------------------------------------------------------
--��������¼�
----------------------------------------------------------------------------------------------
function x310150_OnDie( sceneId,selfId,killerId )

    --��ָ��ɱ��NPC����ô������
    local dataid = GetMonsterDataID( sceneId,selfId)
    if dataid ~= 9700 and dataid ~= 9701 and dataid ~= 9702 and dataid ~= 9703 and dataid ~= 9704 and dataid ~= 9714 and dataid ~= 9715 and  dataid ~= 9776 and dataid ~= 9777 then
        return
    end

    local nMatchCountryId = x310150_GetMatchCountry(sceneId)
    x310150_OnMonsterKillObject( sceneId,selfId,killerId,nMatchCountryId )
    
    --����Ҫͬ������Ϣ
    local nCountryId = x310150_GetCountryIdBySceneId( sceneId )
    CountryBattleLiteSyncKillCount( sceneId,nCountryId )
    
    
    --������ɱNPC��ͬ����������������
    local nMissionData = 0
    if dataid == 9700 or dataid == 9714 or dataid == 9701 or dataid == 9702 or dataid == 9776 then
    	nMissionData = 10000
    elseif dataid == 9715 or dataid == 9703 or dataid == 9777 then
    	nMissionData = 1000
    elseif dataid == 9704 then
    	nMissionData = 100
    end
    
    SetCountryQuestData(sceneId,nMatchCountryId,CD_INDEX_COUNTRYBATTLELITE_KILLCOUNT,nMissionData,1)
    SetCountryQuestData(sceneId,nCountryId,CD_INDEX_COUNTRYBATTLELITE_KILLCOUNT,nMissionData,1)
    
    --����־
    if IsPlayerStateNormal( sceneId, killerId ) == 1 then
        local killername = GetName( sceneId, killerId )
        if killername == nil then
            killername = "ErrorName"
        end
        
        local nKillerCountryId = GetCurCountry( sceneId, killerId )
        local strMsg = format("CBL:<Info>x310150_OnDie [killerInfo] sceneId = %d, killer = %s, killercountryId=%d, nCountryId=%d", sceneId, killername, nKillerCountryId, nCountryId  )
        WriteLog( 1, strMsg )
    end
    
    --�ټ���־
    local strMsg = format("CBL:<Info>x310150_OnDie sceneId = %d countryId=%d,nMatchCountryId=%d", sceneId, nCountryId, nMatchCountryId  )
    WriteLog( 1, strMsg )    
    
end

----------------------------------------------------------------------------------------------
--�����Ϣ
----------------------------------------------------------------------------------------------
function x310150_OnSetCountryBattleLiteMatchInfo( sceneId,countryId0,countryId1,countryId2,countryId3 )
    
    x310150_g_Match0[sceneId][1] = countryId0
    x310150_g_Match0[sceneId][2] = countryId1
    
    x310150_g_Match1[sceneId][1] = countryId2
    x310150_g_Match1[sceneId][2] = countryId3
    
    x310150_g_MatchScore0[sceneId][1] = 0
    x310150_g_MatchScore0[sceneId][2] = 10
    
    x310150_g_MatchScore1[sceneId][1] = 0
    x310150_g_MatchScore1[sceneId][2] = 10
    
    local strMsg = format("CBL:<Info>SetCountryBattleLiteMatchInfo sceneId = %d countryId0=%d, countryId1=%d, countryId2=%d, countryId3=%d", sceneId, countryId0, countryId1, countryId2, countryId3  )
    WriteLog( 1, strMsg )
end

----------------------------------------------------------------------------------------------
--ͬ��������Ϣ
----------------------------------------------------------------------------------------------
function x310150_OnCountryBattleLiteSyncKillCout( sceneId,countryId,killcount,targetSceneId )

	while killcount >=10000 do
		killcount = killcount - 10000
	end
	
	while killcount >= 1000 do
		killcount = killcount - 1000
	end
	
	while killcount >= 100 do
		killcount = killcount - 100
	end

    if countryId == x310150_g_Match0[sceneId][1] then
        x310150_g_MatchScore0[sceneId][1] = killcount
        
        if killcount == 10 then
        	if x310150_IsCountryAttact( sceneId,countryId) == 1 then
        		x310150_g_BonusFlag0[sceneId][1] = GetMinOfYear()
        	end
        end
    elseif countryId == x310150_g_Match0[sceneId][2] then
        x310150_g_MatchScore0[sceneId][2] = killcount
        
        if killcount == 0 then
        	if x310150_IsCountryAttact( sceneId,countryId) == 0 then
        		x310150_g_BonusFlag0[sceneId][2] = GetMinOfYear()
        	end
        end 
    elseif countryId == x310150_g_Match1[sceneId][1] then
        x310150_g_MatchScore1[sceneId][1] = killcount
        
        if killcount == 10 then
        	if x310150_IsCountryAttact( sceneId,countryId) == 1 then
        		x310150_g_BonusFlag1[sceneId][1] = GetMinOfYear()
        	end
        end 
    elseif countryId == x310150_g_Match1[sceneId][2] then
        x310150_g_MatchScore1[sceneId][2] = killcount
        
        if killcount == 0 then
        	if x310150_IsCountryAttact( sceneId,countryId) == 0 then
        		x310150_g_BonusFlag1[sceneId][2] = GetMinOfYear()
        	end
        end
    end
    
    --��Ӧ���Ҿ����ı��¼�
	x310150_OnCountryKillCountChanged( sceneId,countryId,killcount )

    --����֪ͨ
    if targetSceneId == sceneId then
        local msg = format("���Ҿ�����%d/10",killcount)
        LuaAllScenceM2Country( sceneId,msg,countryId, 5,1)
        LuaAllScenceM2Country( sceneId,msg,countryId, 5,1) 
		LuaAllScenceM2Country( sceneId,msg,countryId, 2,0)
        LuaAllScenceM2Country( sceneId,msg,countryId, 2,0) 
    end
    
    local strMsg = format("CBL:<Info>CountryBattleLiteSyncKillCout sceneId = %d countryId=%d,killcount=%d,targetSceneId=%d", sceneId,countryId, killcount,targetSceneId  )
    WriteLog( 1, strMsg )
        
end

----------------------------------------------------------------------------------------------
--�״̬����
----------------------------------------------------------------------------------------------
function x310150_OnCountryBattleLiteState( sceneId, state )

    --��¼��־
    local strMsg = format("CBL:<Info>OnCountryBattleLiteState sceneId = %d, state = %d", sceneId, state)
    WriteLog( 1, strMsg )

    --������ش���
    if state == x310150_g_CountryBattleLite_Begin then
        
        --��ʼС��ս    
        if sceneId == 51 or sceneId == 151 or sceneId == 251 or sceneId == 351 then
            x310150_OnStartCountryBattleLite_x51( sceneId  )
        elseif sceneId == 50 or sceneId == 150 or sceneId == 250 or sceneId == 350 then
            x310150_OnStartCountryBattleLite_x50( sceneId  )
		elseif sceneId == 58 or sceneId == 158 or sceneId == 258 or sceneId == 358 then
            x310150_OnStartCountryBattleLite_x58( sceneId  )
		elseif sceneId == 104 or sceneId == 204 or sceneId == 304 or sceneId == 404 then
        	x310150_OnStopCountryBattleLite_x104( sceneId )
		elseif sceneId == 105 or sceneId == 205 or sceneId == 305 or sceneId == 405 then
        	x310150_OnStopCountryBattleLite_x105( sceneId )
		elseif sceneId == 106 or sceneId == 206 or sceneId == 306 or sceneId == 406 then
        	x310150_OnStopCountryBattleLite_x106( sceneId )
		elseif sceneId == 107 or sceneId == 207 or sceneId == 307 or sceneId == 407 then
        	x310150_OnStopCountryBattleLite_x107( sceneId )
		elseif sceneId == 108 or sceneId == 208 or sceneId == 308 or sceneId == 408 then
        	x310150_OnStopCountryBattleLite_x108( sceneId )
		elseif sceneId == 109 or sceneId == 209 or sceneId == 309 or sceneId == 409 then
        	x310150_OnStopCountryBattleLite_x109( sceneId )
		elseif sceneId == 110 or sceneId == 210 or sceneId == 310 or sceneId == 410 then
        	x310150_OnStopCountryBattleLite_x110( sceneId )
		elseif sceneId == 111 or sceneId == 211 or sceneId == 311 or sceneId == 411 then
        	x310150_OnStopCountryBattleLite_x111 ( sceneId )
        elseif sceneId == 86 or sceneId == 186 or sceneId == 286 or sceneId == 386  or sceneId == 3 then
        	x310150_OnStartCountryBattleLite_x86( sceneId )
        end


        --��ʼ���콱���
        x310150_g_BonusFlag0[sceneId] = {-1,-1}
        x310150_g_BonusFlag1[sceneId] = {-1,-1}
        
    elseif state == x310150_g_CountryBattleLite_End then
        
        --����С��ս
        if sceneId == 51 or sceneId == 151 or sceneId == 251 or sceneId == 351 then
            x310150_OnStopCountryBattleLite_x51( sceneId )
        elseif sceneId == 50 or sceneId == 150 or sceneId == 250 or sceneId == 350 then
            x310150_OnStopCountryBattleLite_x50( sceneId )
		elseif sceneId == 58 or sceneId == 158 or sceneId == 258 or sceneId == 358 then
            x310150_OnStopCountryBattleLite_x58( sceneId )
        elseif sceneId == 86 or sceneId == 186 or sceneId == 286 or sceneId == 386 then
        	x310150_OnStopCountryBattleLite_x86( sceneId )
		elseif sceneId == 104 or sceneId == 204 or sceneId == 304 or sceneId == 404 then
        	x310150_OnStopCountryBattleLite_x104( sceneId )
		elseif sceneId == 105 or sceneId == 205 or sceneId == 305 or sceneId == 405 then
        	x310150_OnStopCountryBattleLite_x105( sceneId )
		elseif sceneId == 106 or sceneId == 206 or sceneId == 306 or sceneId == 406 then
        	x310150_OnStopCountryBattleLite_x106( sceneId )
		elseif sceneId == 107 or sceneId == 207 or sceneId == 307 or sceneId == 407 then
        	x310150_OnStopCountryBattleLite_x107( sceneId )
		elseif sceneId == 108 or sceneId == 208 or sceneId == 308 or sceneId == 408 then
        	x310150_OnStopCountryBattleLite_x108( sceneId )
		elseif sceneId == 109 or sceneId == 209 or sceneId == 309 or sceneId == 409 then
        	x310150_OnStopCountryBattleLite_x109( sceneId )
		elseif sceneId == 110 or sceneId == 210 or sceneId == 310 or sceneId == 410 then
        	x310150_OnStopCountryBattleLite_x110( sceneId )
		elseif sceneId == 111 or sceneId == 211 or sceneId == 311 or sceneId == 411 then
        	x310150_OnStopCountryBattleLite_x111 ( sceneId )
        elseif sceneId == 68 or sceneId == 168 or sceneId == 268 or sceneId == 368  or sceneId == 3 then
        	x310150_OnStopCountryBattleLite_x68( sceneId )
        end
        
        --��ʼ���콱���
        x310150_g_BonusFlag0[sceneId] = {-1,-1}
        x310150_g_BonusFlag1[sceneId] = {-1,-1}
    end
end

-- �������ϵĻ���״̬�ж��Ƿ���Բμӡ�����ս��
function x310150_IsCanJoinCountryBattleLite( sceneId, selfId)

	-- ����״̬�б������ɫ��������Щ״̬���ܲμӡ�����ս��
	local MutexStateList = { 
                            PLAYER_STATE_STALL,                     --��̯
                            PLAYER_STATE_FUBEN,                 --����
                            PLAYER_STATE_GUILDBATTLEFIELDSCENE,     --ս��
                            PLAYER_STATE_PRISONSCENE,               --����
                            PLAYER_STATE_BUS,                       --BUS
                            PLAYER_STATE_CRASHBOX,                  --����
                            PLAYER_STATE_MENTALGAME,                --����
                            PLAYER_STATE_PRISON,                    --����
                            PLAYER_STATE_TIESAN,                    --��������
                            PLAYER_STATE_READYFUBEN,            --���븱��״̬
                            PLAYER_STATE_WEDDING,				    --����״̬
                            PLAYER_STATE_ENJAIL,				    --����״̬
						   }

    for i, mutex in MutexStateList do
        if IsPlayerMutexState( sceneId, selfId, MutexStateList[ i ] ) > 0 then
            return 0
        end
    end

    return 1
end

----------------------------------------------------------------------------------------------
--����ս��
----------------------------------------------------------------------------------------------
function x310150_AskEnterCountryBattleLite( sceneId, selfId )
    -- �ж��Ƿ���������
    if IsPlayerStateNormal( sceneId, selfId) == 0 or x310150_IsCanJoinCountryBattleLite( sceneId, selfId) == 0 then
        Msg2Player( sceneId, selfId, "�����ڲ��ܲμӡ�����ս��", 8, 3)
        return
    end

    --��GLServer������볡��
    AskEnterCountryBattleLite( sceneId,selfId )
    
    local name = GetName(sceneId,selfId)
    if name == nil then
        name = "<ErrorName>"
    end

    local strMsg = format("CBL:<Info>AskEnterCountryBattleLite sceneId = %d, name = %s", sceneId, name )
    WriteLog( 1, strMsg )
    
end

----------------------------------------------------------------------------------------------
--֪ͨ��ҽ���ս��
----------------------------------------------------------------------------------------------
function x310150_OnCountryBattleLiteAskPlayerEnterScene(sceneId,selfId,campFlag,matchCountry )
    
    local level = GetLevel(sceneId,selfId)
	if level < 40 then
		return
	end
	
    --ѯ������Ƿ�Ҫ����С��ս
    SpeerPlayerToEnterCountryBattleLite( sceneId, selfId, campFlag ,matchCountry)
    
    local name = GetName(sceneId,selfId)
    if name == nil then
        name = "<ErrorName>"
    end

    local strMsg = format("CBL:<Info>CountryBattleLiteAskPlayerEnterScene sceneId = %d,name = %s,campFlag=%d ,matchCountry=%d", sceneId, name, campFlag,matchCountry )
    WriteLog( 1, strMsg )
    
end

----------------------------------------------------------------------------------------------
--����ս,ˢ��������Ϣ
----------------------------------------------------------------------------------------------
function x310150_CountryBattleLite_RefreshQuest( sceneId,selfId )

	--����Ч����
	if sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and
	   sceneId ~= 51 and sceneId ~= 151 and sceneId ~= 251 and sceneId ~= 351 and
	   sceneId ~= 58 and sceneId ~= 158 and sceneId ~= 258 and sceneId ~= 358 and
	   sceneId ~= 104 and sceneId ~=204 and sceneId ~= 304 and sceneId ~= 404 and
	   sceneId ~= 76 and sceneId ~= 176 and sceneId ~= 276 and sceneId ~= 376 and
	   sceneId ~= 86 and sceneId ~= 186 and sceneId ~= 286 and sceneId ~= 386 and
	   sceneId ~= 105 and sceneId ~=205 and sceneId ~= 305 and sceneId ~= 405 and
	   sceneId ~= 106 and sceneId ~=206 and sceneId ~= 306 and sceneId ~= 406 and
	   sceneId ~= 107 and sceneId ~=207 and sceneId ~= 307 and sceneId ~= 407 and
	   sceneId ~= 108 and sceneId ~=208 and sceneId ~= 308 and sceneId ~= 408 and
	   sceneId ~= 109 and sceneId ~=209 and sceneId ~= 309 and sceneId ~= 409 and
	   sceneId ~= 110 and sceneId ~=210 and sceneId ~= 310 and sceneId ~= 410 and
	   sceneId ~= 111 and sceneId ~=211 and sceneId ~= 311 and sceneId ~= 411 and
	   sceneId ~= 91 and sceneId ~= 191 and sceneId ~= 291 and sceneId ~= 391 and sceneId ~= 3 then
	   return
	end
	
	--�Ƿ����
	if getn(x310150_g_Monster_x51[sceneId]) == 0 then
		--return
	end
	
	--����ˢ��
	if GetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG) == 1 then
		SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,0)
		local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
		local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
		x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
	end
	
end

----------------------------------------------------------------------------------------------
--����ҽ���ս��
----------------------------------------------------------------------------------------------
function x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,flag )

	if x310150_IsMissionCanAccept( sceneId,selfId) == 0 then
		if flag == nil or flag == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�������Ѿ��μӹ������ҡ�����ս�ˣ�")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
		return
	end
	
	--�ڲ���ʱ�����
    local nFrom = 20*60 + 0
    local nTo   = 20*60 + 20
    local minTime = GetMinOfDay()

    if minTime < nFrom or minTime > nTo then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�μӡ����ҡ�����սʱ���ѹ���")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
        return
    end
    
    --����״̬���ܲμ�����ս
    if IsHideName(sceneId,selfId) ~= 0 then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"����״̬���ܲμӡ����ҡ�����ս��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
    	return
    end
	
	if IsHaveQuest(sceneId,selfId, x310150_g_MissionId) == 0 then
		
		--��������
		if IsQuestFullNM(sceneId,selfId)==1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���������Ѿ����ˣ��޷��μ�����ս��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 
		end
		if sceneId == 89 or sceneId == 189 or sceneId == 289 or sceneId == 389 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�˳������ܽӡ����ҡ�����ս����")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
		end
		--����������
		if AddQuest(sceneId,selfId,x310150_g_MissionId,x310150_g_MissionScriptId,0,0,0,1) ~= 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�μ�����սʧ�ܣ��޷�������������ȥ���ҹ���Ա�����Ա����μӣ�")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return
		end
	end	
	
	GamePlayScriptLog( sceneId, selfId, 1511)

	local nCurDayTime = GetDayOfYear()+100
	
	--������������
	local misIndex = GetQuestIndexByID( sceneId,selfId,x310150_g_MissionId)
	SetQuestParam( sceneId,selfId,x310150_g_MissionId,3,0)					--�趨�������
	SetQuestParam( sceneId,selfId,x310150_g_MissionId,4,nCurDayTime)
	SetQuestParam( sceneId,selfId,x310150_g_MissionId,5,campFlag)
	SetQuestParam( sceneId,selfId,x310150_g_MissionId,6,nMatchCountry)
	
	--���ý���������
	x310150_SetMissionAcceptDate(sceneId,selfId)
	
	--��������BUFID
	local nCountry = GetCurCountry(sceneId,selfId)
	local nBufID = x310150_g_BufID[nCountry*2+1]
	if nBufID ~= -1 then
		if GetSex(sceneId,selfId) == 0 then
			nBufID = nBufID + 1
		end
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,nBufID,0)
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,x310150_g_TickBuf,0)
	end
	
	--ˢ������
	if flag == nil then
		CallScriptFunction(310155,"ProcQuestLogRefresh",sceneId, selfId, x310150_g_MissionId)
	end
    
    BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"���μ�������ս��")
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	
	local nCountry = GetCurCountry( sceneId,selfId)
	local name = GetName(sceneId,selfId)
    if name == nil then
        name = "<ErrorName>"
    end

    local strMsg = format("CBL:<Info>CountryBattleLiteChangeScene sceneId = %d,name = %s Country = %d,nMatchCountry = %d campFlag = %d",sceneId, name,nCountry,nMatchCountry,campFlag )
    WriteLog( 1, strMsg ) 
end

----------------------------------------------------------------------------------------------
--���Ǿ���
----------------------------------------------------------------------------------------------
function x310150_IsMonsterValid_x58( sceneId,index )
	
	local nCount = getn(x310150_g_Monster_x58[sceneId])
	if index < 1 or index > nCount then
		return 0
	end
	
	if IsObjValid(sceneId,x310150_g_Monster_x58[sceneId][index]) ~= 1 or GetHp(sceneId,x310150_g_Monster_x58[sceneId][index]) <= 0 then
		return 0
	end
	
	
	return 1
	
end

----------------------------------------------------------------------------------------------
--�߾�����
----------------------------------------------------------------------------------------------
function x310150_IsMonsterValid_x51( sceneId,index )
	
	local nCount = getn(x310150_g_Monster_x51[sceneId])
	if index < 1 or index > nCount then
		return 0
	end
	
	if IsObjValid(sceneId,x310150_g_Monster_x51[sceneId][index]) ~= 1 or GetHp(sceneId,x310150_g_Monster_x51[sceneId][index]) <= 0 then
		return 0
	end
	
	
	return 1
	
end

----------------------------------------------------------------------------------------------
--�߾�����
----------------------------------------------------------------------------------------------
function x310150_IsMonsterValid_x86( sceneId,index )
	
	local nCount = getn(x310150_g_Monster_x86[sceneId])
	if index < 1 or index > nCount then
		return 0
	end
	
	if IsObjValid(sceneId,x310150_g_Monster_x86[sceneId][index]) ~= 1 or GetHp(sceneId,x310150_g_Monster_x86[sceneId][index]) <= 0 then
		return 0
	end
	
	
	return 1
	
end

----------------------------------------------------------------------------------------------
--����С��ս���߾�
----------------------------------------------------------------------------------------------
function x310150_OnStartCountryBattleLite_x51( sceneId )
    local strMsg = format("CBL:<Info>begin,StartCountryBattleLite_Bianjin sceneId = %d ",sceneId )
    WriteLog( 1, strMsg )
    
    
    --���֮ǰ���й������ݣ���ô����־���������
    local n = getn(x310150_g_Monster_x51[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x51[sceneId][i] )
        end
        
        local strMsg = format("CBL:<Error>StartCountryBattleLite_Bianjin sceneId = %d, n = %d",sceneId, n)
        WriteLog( 1, strMsg )
        
        x310150_g_Monster_x51[sceneId] = {}
    end
    
    --�����µ�Monster
    local campId = x310150_SelectNpcCamp( sceneId )
	local nCountry = x310150_GetCountryIdBySceneId( sceneId )
	if x310150_IsCountryAttact( sceneId, nCountry ) == 0 then
		if nCountry == 0 then
			x310150_g_Monster_x51[sceneId][1] = CreateMonster(sceneId, 9700, 126, 152, 24, -1, x310150_g_scriptId, 129740, campId, -1, 0, "", "" )
			x310150_g_Monster_x51[sceneId][2] = CreateMonster(sceneId, 9714, 126, 81, 24, -1, x310150_g_scriptId, 129741, campId, -1, 0, "", "" )
		elseif  nCountry == 1 then
			x310150_g_Monster_x51[sceneId][1] = CreateMonster(sceneId, 9700, 126, 152, 24, -1, x310150_g_scriptId, 129740, campId, -1, 0, "", "" )
			x310150_g_Monster_x51[sceneId][2] = CreateMonster(sceneId, 9714, 127, 82, 24, -1, x310150_g_scriptId, 129741, campId, -1, 0, "", "" )
		elseif  nCountry == 2 then
			x310150_g_Monster_x51[sceneId][1] = CreateMonster(sceneId, 9700, 127, 95, 24, -1, x310150_g_scriptId, 129740, campId, -1, 0, "", "" )
			x310150_g_Monster_x51[sceneId][2] = CreateMonster(sceneId, 9714, 126, 166, 24, -1, x310150_g_scriptId, 129741, campId, -1, 0, "", "" )
		elseif  nCountry == 3 then
			x310150_g_Monster_x51[sceneId][1] = CreateMonster(sceneId, 9700, 127, 95,  24, -1, x310150_g_scriptId, 129740, campId, -1, 0, "", "" )
			x310150_g_Monster_x51[sceneId][2] = CreateMonster(sceneId, 9714, 126, 166,24, -1, x310150_g_scriptId, 129741, campId, -1, 0, "", "" )
		end                                                            
		
		for i,item in x310150_g_Monster_x51[sceneId] do
			SendSpecificImpactToUnit(sceneId,item,item,item,8354,0)
		end
		
	    
		local strMsg = format("CBL:<Info>end,StartCountryBattleLite_Bianjin sceneId = %d ,m1:%d,m2:%d ",sceneId,x310150_g_Monster_x51[sceneId][1],x310150_g_Monster_x51[sceneId][2] )
		WriteLog( 1, strMsg )
	end

end

----------------------------------------------------------------------------------------------
--ֹͣС��ս���߾�
----------------------------------------------------------------------------------------------
function x310150_OnStopCountryBattleLite_x51( sceneId )
    
    local n = getn(x310150_g_Monster_x51[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x51[sceneId][i] )
        end
        
        x310150_g_Monster_x51[sceneId] = {}
    end
    
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_Bianjin sceneId = %d",sceneId )
    WriteLog( 1, strMsg )
end


----------------------------------------------------------------------------------------------
--����С��ս������
----------------------------------------------------------------------------------------------

function x310150_OnStartCountryBattleLite_x50( sceneId )
	local strMsg = format("CBL:<Info>begin,StartCountryBattleLite_50 sceneId = %d ",sceneId )
    WriteLog( 1, strMsg )
   
    
    --���֮ǰ���й������ݣ���ô����־���������
    local n = getn(x310150_g_Monster_x50[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x50[sceneId][i] )
        end
        
        local strMsg = format("CBL:<Error>StartCountryBattleLite_50 sceneId = %d, n = %d",sceneId, n)
        WriteLog( 1, strMsg )
        
        x310150_g_Monster_x50[sceneId] = {}
    end
end

function x310150_OnStartCountryBattleLite_x58( sceneId )
    
    local strMsg = format("CBL:<Info>begin,StartCountryBattleLite_58 sceneId = %d ",sceneId )
    WriteLog( 1, strMsg )
   
    
    --���֮ǰ���й������ݣ���ô����־���������
    local n = getn(x310150_g_Monster_x58[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x58[sceneId][i] )
        end
        
        local strMsg = format("CBL:<Error>StartCountryBattleLite_58 sceneId = %d, n = %d",sceneId, n)
        WriteLog( 1, strMsg )
        
        x310150_g_Monster_x58[sceneId] = {}
    end
    
    --�����µ�Monster
	local campId = x310150_SelectNpcCamp( sceneId )
	local nCountry = x310150_GetCountryIdBySceneId( sceneId )
	if x310150_IsCountryAttact( sceneId, nCountry ) == 0 then
		if nCountry == 0 then
			x310150_g_Monster_x58[sceneId][1] = CreateMonster( sceneId, 9776, 128, 134, 24, -1, x310150_g_scriptId, 129745, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][2] = CreateMonster( sceneId, 9715, 128, 112, 24, -1, x310150_g_scriptId, 129746, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][3] = CreateMonster( sceneId, 9703, 92, 76, 24, 209, x310150_g_scriptId, 129747, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][4] = CreateMonster( sceneId, 9777, 164, 76, 24, -1, x310150_g_scriptId, 129748, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][5] = CreateMonster( sceneId, 9704, 128, 43, 24, -1, x310150_g_scriptId, 129749, campId, -1, 0, "", "" )

			
			x310150_g_Monster_x58[sceneId][6]  = CreateMonster( sceneId, 9713, 124, 131, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][7]  = CreateMonster( sceneId, 9713, 131, 131, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][8]  = CreateMonster( sceneId, 9713, 130, 124, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][9]  = CreateMonster( sceneId, 9713, 124, 124, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][10] = CreateMonster( sceneId, 9713, 156, 71, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][11] = CreateMonster( sceneId, 9713, 166, 81, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][12] = CreateMonster( sceneId, 9713, 101, 81, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][13] = CreateMonster( sceneId, 9713, 101, 71, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][14] = CreateMonster( sceneId, 9713, 121, 45, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][15] = CreateMonster( sceneId, 9713, 131, 46, 21, -1, -1, -1, campId, -1, 0, "", "" )
		elseif  nCountry == 1 then
			x310150_g_Monster_x58[sceneId][1] = CreateMonster( sceneId, 9776, 128, 134, 24, -1, x310150_g_scriptId, 129745, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][2] = CreateMonster( sceneId, 9715, 128, 112, 24, -1, x310150_g_scriptId, 129746, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][3] = CreateMonster( sceneId, 9703, 92, 76, 24, 209, x310150_g_scriptId, 129747, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][4] = CreateMonster( sceneId, 9777, 164, 76, 24, -1, x310150_g_scriptId, 129748, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][5] = CreateMonster( sceneId, 9704, 128, 43, 24, -1, x310150_g_scriptId, 129749, campId, -1, 0, "", "" )

			
			x310150_g_Monster_x58[sceneId][6]  = CreateMonster( sceneId, 9713, 124, 131, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][7]  = CreateMonster( sceneId, 9713, 131, 131, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][8]  = CreateMonster( sceneId, 9713, 130, 124, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][9]  = CreateMonster( sceneId, 9713, 124, 124, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][10] = CreateMonster( sceneId, 9713, 156, 71, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][11] = CreateMonster( sceneId, 9713, 166, 81, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][12] = CreateMonster( sceneId, 9713, 101, 81, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][13] = CreateMonster( sceneId, 9713, 101, 71, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][14] = CreateMonster( sceneId, 9713, 121, 45, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][15] = CreateMonster( sceneId, 9713, 131, 46, 21, -1, -1, -1, campId, -1, 0, "", "" )
		elseif  nCountry == 2 then
			x310150_g_Monster_x58[sceneId][1] = CreateMonster( sceneId, 9776, 128, 123, 24, -1, x310150_g_scriptId, 129745, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][2] = CreateMonster( sceneId, 9715, 128, 144, 24, -1, x310150_g_scriptId, 129746, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][3] = CreateMonster( sceneId, 9703, 164, 180, 24, 209, x310150_g_scriptId, 129747, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][4] = CreateMonster( sceneId, 9777, 92, 180, 24, -1, x310150_g_scriptId, 129748, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][5] = CreateMonster( sceneId, 9704, 128, 213, 24, -1, x310150_g_scriptId, 129749, campId, -1, 0, "", "" )
                             
			
			x310150_g_Monster_x58[sceneId][6]  = CreateMonster( sceneId, 9713, 124, 125, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][7]  = CreateMonster( sceneId, 9713, 130, 125, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][8]  = CreateMonster( sceneId, 9713, 126, 132, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][9]  = CreateMonster( sceneId, 9713, 132, 132, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][10] = CreateMonster( sceneId, 9713, 100, 185, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][11] = CreateMonster( sceneId, 9713, 90, 175, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][12] = CreateMonster( sceneId, 9713, 155, 175, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][13] = CreateMonster( sceneId, 9713, 155, 185, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][14] = CreateMonster( sceneId, 9713, 135, 211, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][15] = CreateMonster( sceneId, 9713, 125, 210, 21, -1, -1, -1, campId, -1, 0, "", "" )
		elseif  nCountry == 3 then
			x310150_g_Monster_x58[sceneId][1] = CreateMonster( sceneId, 9776, 128, 123, 24, -1, x310150_g_scriptId, 129745, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][2] = CreateMonster( sceneId, 9715, 128, 144, 24, -1, x310150_g_scriptId, 129746, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][3] = CreateMonster( sceneId, 9703, 164, 180, 24, 209, x310150_g_scriptId, 129747, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][4] = CreateMonster( sceneId, 9777, 92, 180, 24, -1, x310150_g_scriptId, 129748, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][5] = CreateMonster( sceneId, 9704, 128, 213, 24, -1, x310150_g_scriptId, 129749, campId, -1, 0, "", "" )
                             
			
			x310150_g_Monster_x58[sceneId][6]  = CreateMonster( sceneId, 9713, 124, 125, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][7]  = CreateMonster( sceneId, 9713, 130, 125, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][8]  = CreateMonster( sceneId, 9713, 126, 132, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][9]  = CreateMonster( sceneId, 9713, 132, 132, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][10] = CreateMonster( sceneId, 9713, 100, 185, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][11] = CreateMonster( sceneId, 9713, 90, 175, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][12] = CreateMonster( sceneId, 9713, 155, 175, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][13] = CreateMonster( sceneId, 9713, 155, 185, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][14] = CreateMonster( sceneId, 9713, 135, 211, 21, -1, -1, -1, campId, -1, 0, "", "" )
			x310150_g_Monster_x58[sceneId][15] = CreateMonster( sceneId, 9713, 125, 210, 21, -1, -1, -1, campId, -1, 0, "", "" )
		end                   
		
		for i,item in x310150_g_Monster_x58[sceneId] do
			SendSpecificImpactToUnit(sceneId,item,item,item,8354,0)
		end
		
	    
		local strMsg = format("CBL:<Info>end,StartCountryBattleLite_58 sceneId = %d ,m1:%d,m2:%d ",sceneId,x310150_g_Monster_x58[sceneId][1],x310150_g_Monster_x58[sceneId][2] )
		WriteLog( 1, strMsg )
	end
    
end

----------------------------------------------------------------------------------------------
--����С��ս��86
----------------------------------------------------------------------------------------------
function x310150_OnStartCountryBattleLite_x86( sceneId )
    local strMsg = format("CBL:<Info>begin,StartCountryBattleLite_86 sceneId = %d ",sceneId )
    WriteLog( 1, strMsg )
   
    
    --���֮ǰ���й������ݣ���ô����־���������
    local n = getn(x310150_g_Monster_x86[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x86[sceneId][i] )
        end
        
        local strMsg = format("CBL:<Error>StartCountryBattleLite_86 sceneId = %d, n = %d",sceneId, n)
        WriteLog( 1, strMsg )
        
        x310150_g_Monster_x86[sceneId] = {}
    end
    
    --�����µ�Monster
    local campId = x310150_SelectNpcCamp( sceneId )
	local nCountry = x310150_GetCountryIdBySceneId( sceneId )
	if x310150_IsCountryAttact( sceneId, nCountry ) == 0 then
		if nCountry == 0 then
			x310150_g_Monster_x86[sceneId][1] = CreateMonster( sceneId, 9701, 179, 100, 24, 2, x310150_g_scriptId, 129742, campId, -1, 0, "", "" )
			x310150_g_Monster_x86[sceneId][2] = CreateMonster( sceneId, 9702, 155, 157, 24, -1, x310150_g_scriptId, 129743, campId, -1, 0, "", "" )
			x310150_g_Monster_x86[sceneId][3] = CreateMonster( sceneId, 9702, 146, 69, 24, -1, x310150_g_scriptId, 129744, campId, -1, 0, "", "" )
		elseif nCountry == 1 then
			x310150_g_Monster_x86[sceneId][1] = CreateMonster( sceneId, 9701, 140, 136, 24, 2, x310150_g_scriptId, 129742, campId, -1, 0, "", "" )
			x310150_g_Monster_x86[sceneId][2] = CreateMonster( sceneId, 9702, 150, 167, 24, -1, x310150_g_scriptId, 129743, campId, -1, 0, "", "" )
			x310150_g_Monster_x86[sceneId][3] = CreateMonster( sceneId, 9702, 154, 89, 24, -1, x310150_g_scriptId, 129744, campId, -1, 0, "", "" )
		elseif nCountry == 2 then
			x310150_g_Monster_x86[sceneId][1] = CreateMonster( sceneId, 9701, 147, 137, 24, 2, x310150_g_scriptId, 129742, campId, -1, 0, "", "" )
			x310150_g_Monster_x86[sceneId][2] = CreateMonster( sceneId, 9702, 148, 75, 24, -1, x310150_g_scriptId, 129743, campId, -1, 0, "", "" )
			x310150_g_Monster_x86[sceneId][3] = CreateMonster( sceneId, 9702, 152, 166, 24, -1, x310150_g_scriptId, 129744, campId, -1, 0, "", "" )
		elseif nCountry == 3 then
			x310150_g_Monster_x86[sceneId][1] = CreateMonster( sceneId, 9701, 110, 126, 24, 2, x310150_g_scriptId, 129742, campId, -1, 0, "", "" )
			x310150_g_Monster_x86[sceneId][2] = CreateMonster( sceneId, 9702, 149, 162, 24, -1, x310150_g_scriptId, 129743, campId, -1, 0, "", "" )
			x310150_g_Monster_x86[sceneId][3] = CreateMonster( sceneId, 9702, 136, 91, 24, -1, x310150_g_scriptId, 129744, campId, -1, 0, "", "" )
		end
	    
		for i,item in x310150_g_Monster_x86[sceneId] do
			SendSpecificImpactToUnit(sceneId,item,item,item,8354,0)
		end
		
		--��¼��־
		local strMsg = format("CBL:<Info>end,StartCountryBattleLite_86 sceneId = %d ,m1:%d,m2:%d,m3:%d  ",sceneId,x310150_g_Monster_x86[sceneId][1],x310150_g_Monster_x86[sceneId][2],x310150_g_Monster_x86[sceneId][3] )
		WriteLog( 1, strMsg )
    end
end

----------------------------------------------------------------------------------------------
--ֹͣС��ս��58
----------------------------------------------------------------------------------------------
function x310150_OnStopCountryBattleLite_x58( sceneId )
    
    local n = getn(x310150_g_Monster_x58[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x58[sceneId][i] )
        end
        
        x310150_g_Monster_x58[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_58 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end
----------------------------------------------------------------------------------------------
--ֹͣС��ս��86
----------------------------------------------------------------------------------------------
function x310150_OnStopCountryBattleLite_x86( sceneId )
    
    local n = getn(x310150_g_Monster_x86[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x86[sceneId][i] )
        end
        
        x310150_g_Monster_x86[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_86 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end

function x310150_OnStopCountryBattleLite_x104( sceneId )  -- �Թ�
    
    local n = getn(x310150_g_Monster_x104[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x104[sceneId][i] )
        end
        
        x310150_g_Monster_x104[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_104 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end

function x310150_OnStopCountryBattleLite_x105( sceneId )
    
    local n = getn(x310150_g_Monster_x105[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x105[sceneId][i] )
        end
        
        x310150_g_Monster_x105[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_105 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end

function x310150_OnStopCountryBattleLite_x106( sceneId )
    
    local n = getn(x310150_g_Monster_x106[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x106[sceneId][i] )
        end
        
        x310150_g_Monster_x106[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_106 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end

function x310150_OnStopCountryBattleLite_x107( sceneId )
    
    local n = getn(x310150_g_Monster_x107[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x107[sceneId][i] )
        end
        
        x310150_g_Monster_x107[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_107 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end

function x310150_OnStopCountryBattleLite_x108( sceneId )
    
    local n = getn(x310150_g_Monster_x108[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x108[sceneId][i] )
        end
        
        x310150_g_Monster_x108[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_108 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end

function x310150_OnStopCountryBattleLite_x109( sceneId )
    
    local n = getn(x310150_g_Monster_x109[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x109[sceneId][i] )
        end
        
        x310150_g_Monster_x109[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_109 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end
function x310150_OnStopCountryBattleLite_x110( sceneId )
    
    local n = getn(x310150_g_Monster_x110[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x110[sceneId][i] )
        end
        
        x310150_g_Monster_x110[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_110 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end

function x310150_OnStopCountryBattleLite_x111( sceneId )
    
    local n = getn(x310150_g_Monster_x111[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x111[sceneId][i] )
        end
        
        x310150_g_Monster_x111[sceneId] = {}
    end
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_111 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end




----------------------------------------------------------------------------------------------
--ֹͣС��ս������
----------------------------------------------------------------------------------------------
function x310150_OnStopCountryBattleLite_x50( sceneId )
    
    local n = getn(x310150_g_Monster_x50[sceneId])
    if n > 0 then
        for i = 1, n do
            DeleteMonster( sceneId,x310150_g_Monster_x50[sceneId][i] )
        end
        
        x310150_g_Monster_x50[sceneId] = {}
    end
    
    --������ʾ
    x310150_OnCountryBattleLiteFinish( sceneId )
    
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_Wangchen sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end


----------------------------------------------------------------------------------------------
--ֹͣС��ս���ܵ�
----------------------------------------------------------------------------------------------
function x310150_OnStopCountryBattleLite_x68( sceneId )
   
    --������0
    x310150_g_Match0[sceneId]                        = { -1,-1 }
    x310150_g_Match1[sceneId]                        = { -1,-1 }
    
    x310150_g_MatchScore0[sceneId]                   = { 0,0 }
    x310150_g_MatchScore1[sceneId]                   = { 0,0 }
    
    local strMsg = format("CBL:<Info>StopCountryBattleLite_x68 sceneId = %d ", sceneId )
    WriteLog( 1, strMsg )
    
end

----------------------------------------------------------------------------------------------
--ѡ����Ӫ
----------------------------------------------------------------------------------------------
function x310150_SelectNpcCamp( sceneId )
    if sceneId == 50 or sceneId == 51 or sceneId == 58 or sceneId == 86 then
        return 16
    elseif sceneId == 150 or sceneId == 151 or sceneId == 158 or sceneId == 186 then
        return 17
    elseif sceneId == 250 or sceneId == 251 or sceneId == 258 or sceneId == 286 then
        return 18
    elseif sceneId == 350 or sceneId == 351 or sceneId == 358  or sceneId == 386 then
        return 19
    end
    
    --�������������������˶��ж�
    return 21    
end

----------------------------------------------------------------------------------------------
--��������
----------------------------------------------------------------------------------------------
function x310150_SetDay( sceneId ,selfId )
    
    local today = GetDayOfYear()
	local lastday = x310150_GetDay( sceneId, selfId)

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_COUNTRYBATTLELITE_DATE[1], MD_COUNTRYBATTLELITE_DATE[2], MD_COUNTRYBATTLELITE_DATE[3], today + 100)
	end
end

----------------------------------------------------------------------------------------------
--ȡ������
----------------------------------------------------------------------------------------------
function x310150_GetDay( sceneId ,selfId )

	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x310150_g_MissionId );
	if bHaveMission <= 0 then
		return
	end
		
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310150_g_MissionId )
	local nDay = GetQuestParam( sceneId, selfId, misIndex, 4 ) - 100
	
	--�������
	local nCurDayTime = GetDayOfYear()
	if nCurDayTime == nDay then
		return nDay		
	end
    
    return -1
    
end

----------------------------------------------------------------------------------------------
--������Ӫ
----------------------------------------------------------------------------------------------
function x310150_SetCampFlag( sceneId, selfId, camp )
    SetQuestData(sceneId, selfId, MD_COUNTRYBATTLELITE_CAMP[1], MD_COUNTRYBATTLELITE_CAMP[2], MD_COUNTRYBATTLELITE_CAMP[3], camp)
end

----------------------------------------------------------------------------------------------
--ȡ����Ӫ
----------------------------------------------------------------------------------------------
function x310150_GetCampFlag( sceneId, selfId )
    return GetQuestData(sceneId, selfId, MD_COUNTRYBATTLELITE_CAMP[1], MD_COUNTRYBATTLELITE_CAMP[2], MD_COUNTRYBATTLELITE_CAMP[3])
end

----------------------------------------------------------------------------------------------
--��������
----------------------------------------------------------------------------------------------
function x310150_SetKillCount( sceneId, selfId, nKillCount )
    SetQuestData(sceneId, selfId, MD_COUNTRYBATTLELITE_KILLCOUNT[1], MD_COUNTRYBATTLELITE_KILLCOUNT[2], MD_COUNTRYBATTLELITE_KILLCOUNT[3], nKillCount)
end

----------------------------------------------------------------------------------------------
--ȡ������
----------------------------------------------------------------------------------------------
function x310150_GetKillCount( sceneId, selfId )
    return GetQuestData(sceneId, selfId, MD_COUNTRYBATTLELITE_KILLCOUNT[1], MD_COUNTRYBATTLELITE_KILLCOUNT[2], MD_COUNTRYBATTLELITE_KILLCOUNT[3])
end

----------------------------------------------------------------------------------------------
--�����ҺϷ���
----------------------------------------------------------------------------------------------
function x310150_CheckPlayerValid( sceneId,selfId ,nCountry)

    --���״̬�Ƿ�����
    if IsPlayerStateNormal( sceneId,selfId ) <= 0 then
        return -1
    end
    
    --���������ϴδ��ʱ��
    local today = GetDayOfYear()
    local selfToday = x310150_GetDay( sceneId,selfId )    
    if today ~= selfToday then
        return -2
    end
    
    --������
    local selfCountry = GetCurCountry( sceneId,selfId )
    if selfCountry ~= nCountry then
        return -3
    end
    
    return 1    
end

----------------------------------------------------------------------------------------------
--���Ӽ���
----------------------------------------------------------------------------------------------
function x310150_IncKillCount( sceneId,selfId,nCountry )
    
    local nCount =  x310150_GetKillCount( sceneId,selfId) + 1
    x310150_SetKillCount( sceneId,selfId,nCount)      
                 
end

----------------------------------------------------------------------------------------------
--������������
----------------------------------------------------------------------------------------------
function x310150_OnMonsterKillObject( sceneId,selfId,killerId ,nCountry)

    if x310150_CheckPlayerValid( sceneId,killerId,nCountry ) <= 0 then
        return
    end
    
    local dataid = GetMonsterDataID( sceneId,selfId)
    
    local x,z = GetWorldPos( sceneId,killerId)
    local nCount = GetNearCountryCount( sceneId,killerId,x,z,25 )
    for i =0,nCount -1 do
        
        local objId = GetNearCountryMember(sceneId,killerId,i)
        
        if x310150_CheckPlayerValid( sceneId,objId ,nCountry) == 1 then
            
            --������ɱ�м������������ܻ�ϳ�
            x310150_IncKillCount( sceneId,objId,nCountry )
            
            --��������
            if dataid == 9700 or dataid == 9714 or dataid == 9701 or dataid == 9702 or dataid == 9776 then
                AddExp(sceneId,objId,9999)
            elseif dataid == 9715 or dataid == 9703 or dataid == 9777 then
                AddExp(sceneId,objId,19999)
            elseif dataid == 9704 then
                AddExp(sceneId,objId,29999)
            end 
        end                    
    end
end


----------------------------------------------------------------------------------------------
--ȡ�ù�����Ӫ 0�����ط� 1��������
----------------------------------------------------------------------------------------------
function x310150_GetCountryBattleLite_CountryCamp( sceneId ,selfId )

    local nCountry = GetCurCountry( sceneId,selfId )
    
    if x310150_g_Match0[sceneId][1] == nCountry then
        return 1
    elseif x310150_g_Match0[sceneId][2] == nCountry then
        return 0
    elseif x310150_g_Match1[sceneId][1] == nCountry then
        return 1
    elseif x310150_g_Match1[sceneId][2] == nCountry then
        return 0
    end
    
    return -1    
    
end


----------------------------------------------------------------------------------------------
--ȡ�ù�����Ӫ
----------------------------------------------------------------------------------------------
function x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )

    local nCountry = GetCurCountry( sceneId,selfId )
    
    if x310150_g_Match0[sceneId][1] == nCountry then
        return x310150_g_Match0[sceneId][2]
    elseif x310150_g_Match0[sceneId][2] == nCountry then
        return x310150_g_Match0[sceneId][1]
    elseif x310150_g_Match1[sceneId][1] == nCountry then
        return x310150_g_Match1[sceneId][2]
    elseif x310150_g_Match1[sceneId][2] == nCountry then
        return x310150_g_Match1[sceneId][1]
    end
    
    return -1
    
end

----------------------------------------------------------------------------------------------
--С��ս�����ټ���Ӧ�����ͬ������ټ�
----------------------------------------------------------------------------------------------
function x310150_AskCountryBattleLite_KingIssue( sceneId, selfId )

	GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_DATE, x310150_g_scriptId,-1,"OnKingIssueReturn1")
end

----------------------------------------------------------------------------------------------
--��֤����
----------------------------------------------------------------------------------------------
function x310150_OnKingIssueReturn1( sceneId, selfId,MissionData,MissionId )
	local CurDaytime = GetDayTime()
	if MissionData ~= CurDaytime then
 		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "������ս���Ѿ��������޷�����" )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_FINISHED, x310150_g_scriptId,-1,"OnKingIssueReturn2")

end

----------------------------------------------------------------------------------------------
--��֤�Ƿ����
----------------------------------------------------------------------------------------------
function x310150_OnKingIssueReturn2( sceneId, selfId,MissionData,MissionId )
	
	if MissionData <= 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "������ս���Ѿ��������޷�����" )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	
	GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_CAMP, x310150_g_scriptId,-1,"OnKingIssueReturn3")
	
	
end

----------------------------------------------------------------------------------------------
--��֤��Ӫ
----------------------------------------------------------------------------------------------
function x310150_OnKingIssueReturn3( sceneId, selfId,MissionData,MissionId )
	if MissionData == 0 then
		--��������Ҫȡ�öԶԷ����ҵ������Ϣ
		GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_KINGISUE_NPC, x310150_g_scriptId,-1,"OnKingIssueReturn5")
	else
		--ȡ��NPC��ID
		GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_KINGISUE_NPC, x310150_g_scriptId,-1,"OnKingIssueReturn4")
	end	
	
end

----------------------------------------------------------------------------------------------
--���ط��Ĵ���
----------------------------------------------------------------------------------------------
function x310150_OnKingIssueReturn4( sceneId, selfId,MissionData,MissionId )
	--���ȼ�
	local level = GetLevel(sceneId,selfId)
	if level < 40 then
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "�ȼ�����40�����޷����ͣ�" )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	--������״̬
	local state,msg = x310150_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return
    end
	local nCountry = GetCurCountry( sceneId,selfId)
	if nCountry >= 0 then		
		if MissionData == 129719 then
			local nCountry = GetCurCountry( sceneId,selfId)
			if nCountry >= 0 then
				if nCountry == 0 then
					local pos = { {83,32},{ 68,34},{107,33}}
					local rnd = random(1,3)
					
					local x = pos[rnd][1] + random(-2,2)
					local z = pos[rnd][2] + random(-2,2)
					
					local nTargetSceneId = nCountry*100 + 58
					if sceneId == nTargetSceneId then
						SetPos( sceneId, selfId,x,z)
						local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
						local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
						x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
					else
						--�������ս����
						SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
						NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
					end
				end
				
				if nCountry == 1 then
					local pos = { {83,32},{ 68,34},{107,33}}
					local rnd = random(1,3)
					
					local x = pos[rnd][1] + random(-2,2)
					local z = pos[rnd][2] + random(-2,2)
					
					local nTargetSceneId = nCountry*100 + 58
					if sceneId == nTargetSceneId then
						SetPos( sceneId, selfId,x,z)
						local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
						local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
						x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
					else
						--�������ս����
						SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
						NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
					end
				end
				
				if nCountry == 2 then
					local pos = { {161,224},{ 145,224},{184,226}}
					local rnd = random(1,3)
					
					local x = pos[rnd][1] + random(-2,2)
					local z = pos[rnd][2] + random(-2,2)
					
					local nTargetSceneId = nCountry*100 + 58
					if sceneId == nTargetSceneId then
						SetPos( sceneId, selfId,x,z)
						local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
						local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
						x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
					else
						--�������ս����
						SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
						NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
					end
				end
				
				if nCountry == 3 then
					local pos = { {161,224},{ 145,224},{184,226}}
					local rnd = random(1,3)
					
					local x = pos[rnd][1] + random(-2,2)
					local z = pos[rnd][2] + random(-2,2)
					
					local nTargetSceneId = nCountry*100 + 58
					if sceneId == nTargetSceneId then
						SetPos( sceneId, selfId,x,z)
						local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
						local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
						x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
					else
						--�������ս����
						SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
						NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
					end
				end
			end
			
		elseif MissionData == 129720 then
			
			local nCountry = GetCurCountry( sceneId,selfId)
			if nCountry >= 0 then
				
				--����
				if nCountry == 0 then
					local pos = { {112,127},{ 127,124},{120,145}}
					local rnd = random(1,3)
					
					local x = pos[rnd][1] + random(-2,2)
					local z = pos[rnd][2] + random(-2,2)
					
					local nTargetSceneId = nCountry*100 + 86
					if sceneId == nTargetSceneId then
						SetPos( sceneId, selfId,x,z)
						local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
						local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
						x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
					else
						--�������ս����
						SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
						NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
					end
				end
				
				if nCountry == 1 then
					local pos = { {201,131},{ 178,118},{197,150}}
					local rnd = random(1,3)
					
					local x = pos[rnd][1] + random(-2,2)
					local z = pos[rnd][2] + random(-2,2)
					
					local nTargetSceneId = nCountry*100 + 86
					if sceneId == nTargetSceneId then
						SetPos( sceneId, selfId,x,z)
						local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
						local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
						x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
					else
						--�������ս����
						SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
						NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
					end
				end
				
				if nCountry == 2 then
					local pos = { {74,137},{ 87,138},{82,122}}
					local rnd = random(1,3)
					
					local x = pos[rnd][1] + random(-2,2)
					local z = pos[rnd][2] + random(-2,2)
					
					local nTargetSceneId = nCountry*100 + 86
					if sceneId == nTargetSceneId then
						SetPos( sceneId, selfId,x,z)
						local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
						local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
						x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
					else
						--�������ս����
						SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
						NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
					end
				end
				
				if nCountry == 3 then
					local pos = { {201,131},{ 178,118},{197,150}}
					local rnd = random(1,3)
					
					local x = pos[rnd][1] + random(-2,2)
					local z = pos[rnd][2] + random(-2,2)
					
					local nTargetSceneId = nCountry*100 + 86
					if sceneId == nTargetSceneId then
						SetPos( sceneId, selfId,x,z)
						local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
						local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
						x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
					else
						--�������ս����
						SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
						NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
					end
				end
			end
			
		elseif MissionData == 129724 then
			
			local nCountry = GetCurCountry( sceneId,selfId)
			if nCountry >= 0 then
			
				--����			
				local pos = { {71,136},{81,104},{122,142}}
				local rnd = random(1,3)
				
				local x = pos[rnd][1] + random(-2,2)
				local z = pos[rnd][2] + random(-2,2)
				
				local nTargetSceneId = nCountry*100 + 86
				if sceneId == nTargetSceneId then
					SetPos( sceneId, selfId,x,z)
					local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
					local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
					x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
				else
					--�������ս����
					SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
					NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
				end
			end
		elseif MissionData == 129746 then
			
			local nCountry = GetCurCountry( sceneId,selfId)
			if nCountry >= 0 then
				
				--����
				local pos = { {189,113},{ 153,157},{147,198}}
				local rnd = random(1,3)
				
				local x = pos[rnd][1] + random(-2,2)
				local z = pos[rnd][2] + random(-2,2)
				
				local nTargetSceneId = nCountry*100 + 86
				if sceneId == nTargetSceneId then
					SetPos( sceneId, selfId,x,z)
					local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
					local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
					x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
				else
					--�������ս����
					SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
					NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
				end
			end
		end
	end	
end


----------------------------------------------------------------------------------------------
--������ȡ��NPC��Ϣ
----------------------------------------------------------------------------------------------
function x310150_OnKingIssueReturn5( sceneId, selfId,MissionData,MissionId )
	if MissionData == -1 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "����Ŀ����Ч���޷�����" )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
						
	end
	
	SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_KINGISSUE_NPC,MissionData)
	GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_MATCH_COUNTRY, x310150_g_scriptId,-1,"OnKingIssueReturn6")	
	
	
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x310150_OnKingIssueReturn6( sceneId, selfId,MissionData,MissionId )

	if MissionData < 0 or MissionData > 3  then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "������ս���Ѿ��������޷�����" )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end

	--���ȼ�
	local level = GetLevel(sceneId,selfId)
	if level < 40 then
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "�ȼ�����40�����޷����ͣ�" )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	--������״̬
	local state,msg = x310150_CheckPlayerState( sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return
    end
	
	--��ʼ����
	local npcId = GetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_KINGISSUE_NPC)
	if npcId == 129715 then
	
		local nCountry = GetCurCountry( sceneId,selfId)
		if nCountry == 0 then
		
			local pos = { {73,66},{92,61},{82,86}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end		
		end
		
		if  nCountry == 1 then
		
			local pos = { {185,165},{158,188},{176,150}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
		end
			
		if  nCountry == 2 then
		
			local pos = { {73,149},{55,148},{64,129}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
		end
			
		if  nCountry == 3 then
		
			local pos = { {67,149},{84,199},{64,178}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
		end
		
	elseif npcId == 129716 then
	
		local nCountry = GetCurCountry( sceneId,selfId)
		if nCountry == 0 then
			
			SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
			
			local pos = { {77,175},{ 90,186},{85,155}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
			
		end
		
		if nCountry == 1 then
			
			SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
			
			local pos = { {77,151},{ 81,132},{96,146}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
			
		end
		
		if nCountry == 2 then
			
			SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
			
			local pos = { {130,59},{ 103,62},{125,81}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
			
		end
		
		if nCountry == 3 then
			
			SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
			
			local pos = { {106,65},{ 122,77},{115,102}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
			
		end
		
	elseif npcId == 129718 then
	
		local nCountry = GetCurCountry( sceneId,selfId)
		if nCountry == 0 then
					
			SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
		
			local pos = { {168,127},{137,128},{194,131}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
		end		
		
		if nCountry == 1 then
					
			SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
		
			local pos = { {186,169},{166,147},{190,190}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
		end		
		
		if nCountry == 2 then
					
			SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
		
			local pos = { {185,103},{176,125},{183,148}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
		end		
		
		if nCountry == 3 then
					
			SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
		
			local pos = { {183,89},{159,83},{156,53}}
			local rnd = random(1,3)
			
			local x = pos[rnd][1] + random(-2,2)
			local z = pos[rnd][2] + random(-2,2)
			local nSelfCountry = GetCurCountry(sceneId,selfId)
			local nTargetSceneId = nSelfCountry*100 + 104
			if sceneId == nTargetSceneId then
				SetPos( sceneId, selfId,x,z)
				local campFlag = x310150_GetCountryBattleLite_CountryCamp(sceneId,selfId)
				local nMatchCountry = x310150_GetCountryBattleLite_MatchCountry( sceneId ,selfId )
				x310150_OnCountryBattleLiteChangeScene( sceneId,selfId,campFlag,nMatchCountry,0 )
			else
				--�������ս����
				SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_ADDQUESTFLAG,1)
				NewWorld( sceneId, selfId, nTargetSceneId, x, z, x310150_g_scriptId )
			end
		end		
	end	
end



----------------------------------------------------------------------------------------------
--������״̬
----------------------------------------------------------------------------------------------
function x310150_CheckPlayerState( sceneId,selfId )
    

    local state
    local ErrorMsg

    state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        ErrorMsg = "״̬�쳣"
        return 1,ErrorMsg
    end
    
    --����ڼ��������Ա�����
	if sceneId == PK_PUNISH_PRISON_SCENE_ID then
		ErrorMsg = "�����ﻹ����ʵ,����,û�š�"
        return 1,ErrorMsg
	end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        ErrorMsg = "���ڴ���״̬�����ܴ���"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        ErrorMsg = "���ڰ�̯״̬�����ܴ���"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        ErrorMsg = "��������״̬�����ܴ���"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        ErrorMsg = "���ڻ���״̬�����ܴ���"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        ErrorMsg = "���ڹһ�״̬�����ܴ���"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        ErrorMsg = "���ڴ���״̬�����ܴ���"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        ErrorMsg = "����BUS״̬�����ܴ���"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_PKMODE )
    if state == 1 then
        ErrorMsg = "PKֵ���߻��ڿ�ģʽ�����ܴ���"
        return 1,ErrorMsg
    end

    local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,7702 )
    if IsHaveFlag ~= 0 then
        ErrorMsg = "�ڶ���״̬�£����ܴ���"
        return 1,ErrorMsg
    end
    
    --�Ƿ������ֳ������ڱ���״̬
	IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7536  )
    if IsHaveFlag ~= 0 then
    	ErrorMsg = "�ڱ�������ս�ڼ䣬���ܴ���"
        return 1,ErrorMsg
    end
    
    IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId, 7537 )
    if IsHaveFlag ~= 0 then
    	ErrorMsg = "�ڱ�������ս�ڼ䣬���ܴ���"
        return 1,ErrorMsg
    end

    return 0

end

----------------------------------------------------------
--��������Ƿ�ɽ�
----------------------------------------------------------
function x310150_IsMissionCanAccept( sceneId, selfId )
	local nDate   = GetQuestData(sceneId,selfId,MD_COUNTRYBATTLELITE_DATE[1], MD_COUNTRYBATTLELITE_DATE[2], MD_COUNTRYBATTLELITE_DATE[3] )
	local nCurDay = GetDayOfYear()
	if nCurDay == nDate then
		return 0
	end

	return 1
end

----------------------------------------------------------
--���ý���������
----------------------------------------------------------
function x310150_SetMissionAcceptDate( sceneId, selfId )
	local nCurDay = GetDayOfYear()
	SetQuestData(sceneId,selfId, MD_COUNTRYBATTLELITE_DATE[1], MD_COUNTRYBATTLELITE_DATE[2], MD_COUNTRYBATTLELITE_DATE[3], nCurDay )
	SetQuestData(sceneId,selfId, MD_COUNTRYBATTLELITE_RONGYU[1], MD_COUNTRYBATTLELITE_RONGYU[2], MD_COUNTRYBATTLELITE_RONGYU[3], 0 )
end

----------------------------------------------------------
--��������ս�����������Ƿ�ɹ�
----------------------------------------------------------
function x310150_AddBattleCountryLiteRongyu( sceneId, diedId, selfId,rongyu )
	
	local maxlimit = 2000
	
	--����ǽ���ӵ�������ô�����������ս����
	if x310150_IsMissionCanAccept(sceneId,selfId ) ~= 0 then
		return -1
	end
	
	if IsHaveQuest(sceneId,selfId, x310150_g_MissionId) <= 0 then
		return -2
	end
	
	--ȡ�õ�ǰ�Ѿ���ӵ�����ս����
	local nAdd = GetQuestData(sceneId,selfId, MD_COUNTRYBATTLELITE_RONGYU[1], MD_COUNTRYBATTLELITE_RONGYU[2], MD_COUNTRYBATTLELITE_RONGYU[3] )
	if nAdd >= maxlimit then
		return -3
	end
	
	
	--����׷�Ӷ���
	local total = nAdd + rongyu
	if total > maxlimit then
		total = maxlimit
		nAdd = maxlimit - nAdd
	else
		nAdd = rongyu
	end
	
	--��¼���Ҵ�����
	local totalNum = 10
	local timeLimit = 3600*2 --��	
	local timesLimit = 10 --��
	local IsDiedInRecord = -1;
	local diedIndex = -1;
	local diedFirstBeKillTime = -1;
	local diedTimes = 1;	
	local curTime = GetCurrentTime();
	local index
	local diedGuid = GetGUID(sceneId, diedId)
	for index=0, tonumber(totalNum - 1) do
		local guid, killTime, times = GetHonorRecord(sceneId, selfId, index)
		if tonumber(guid) == tonumber(diedGuid) then
			IsDiedInRecord = 1
			diedIndex = index
			diedFirstBeKillTime = killTime
			diedTimes = times
		end
	end
	
	
	if 1 == IsDiedInRecord and (curTime - diedFirstBeKillTime < timeLimit and diedTimes > timesLimit) then
		--2Сʱ��ɱ����10�Σ����ټ�����ս����
		return -4
	end
	
	
	SetQuestData(sceneId,selfId, MD_COUNTRYBATTLELITE_RONGYU[1], MD_COUNTRYBATTLELITE_RONGYU[2], MD_COUNTRYBATTLELITE_RONGYU[3], total )
	--���ؿ�׷�ӵ�����
	return nAdd
	
end


----------------------------------------------------------
--ɾ��BUF
----------------------------------------------------------
function x310150_CancelBufId( sceneId,selfId )

	for i,item in x310150_g_BufID do
		if IsHaveSpecificImpact(sceneId,selfId,item) == 1 then
			CancelSpecificImpact(sceneId,selfId,item)
		end
	end

end

----------------------------------------------------------
--����г�������
----------------------------------------------------------
function x310150_PlayerEnterFinished( sceneId,selfId)
	
	if IsHaveQuest(sceneId,selfId, x310150_g_MissionId) <= 0 then
		return 
	end
	
	if sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and
	   sceneId ~= 51 and sceneId ~= 151 and sceneId ~= 251 and sceneId ~= 351 and
	   sceneId ~= 58 and sceneId ~= 158 and sceneId ~= 258 and sceneId ~= 358 and
	   sceneId ~= 104 and sceneId ~=204 and sceneId ~= 304 and sceneId ~= 404 and
	   sceneId ~= 76 and sceneId ~= 176 and sceneId ~= 276 and sceneId ~= 376 and 
	   sceneId ~= 86 and sceneId ~= 186 and sceneId ~= 286 and sceneId ~= 386 and 
	   sceneId ~= 105 and sceneId ~=205 and sceneId ~= 305 and sceneId ~= 405 and
	   sceneId ~= 106 and sceneId ~=206 and sceneId ~= 306 and sceneId ~= 406 and
	   sceneId ~= 107 and sceneId ~=207 and sceneId ~= 307 and sceneId ~= 407 and
	   sceneId ~= 108 and sceneId ~=208 and sceneId ~= 308 and sceneId ~= 408 and
	   sceneId ~= 109 and sceneId ~=209 and sceneId ~= 309 and sceneId ~= 409 and
	   sceneId ~= 110 and sceneId ~=210 and sceneId ~= 310 and sceneId ~= 410 and
	   sceneId ~= 111 and sceneId ~=211 and sceneId ~= 311 and sceneId ~= 411 and
	   sceneId ~= 91 and sceneId ~= 191 and sceneId ~= 291 and sceneId ~= 391 and sceneId ~= 3 then 	
	   DelQuest(sceneId, selfId, x310150_g_MissionId)
	   x310150_CancelBufId(sceneId,selfId)
		
		GamePlayScriptLog( sceneId, selfId, 1513)
		
	  	Msg2Player(sceneId, selfId, "���˳��ˡ����ҡ�����ս��", 0, 2)
		Msg2Player(sceneId, selfId, "���˳��ˡ����ҡ�����ս��", 0, 3)
	end
	
end

----------------------------------------------------------
--���PK�Ĵ���
----------------------------------------------------------
function x310150_OnCountryBattleLitePlayerKilled( sceneId,selfId,killerId,rongyu )

	if sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and
	   sceneId ~= 51 and sceneId ~= 151 and sceneId ~= 251 and sceneId ~= 351 and
	   sceneId ~= 58 and sceneId ~= 158 and sceneId ~= 258 and sceneId ~= 358 and
	   sceneId ~= 86 and sceneId ~= 186 and sceneId ~= 286 and sceneId ~= 386  then
	   	return
	end
	
	--ȡ��������ҵĹ���ID
	local selfCountry = GetCurCountry( sceneId,selfId )
	local killerCountry = GetCurCountry( sceneId,killerId )
	
	--ȡ��˫��������Ӫ
	local nSelfCountryCamp   = x310150_GetCountryBattleLite_CountryCamp( sceneId,selfId)
	local nKillerCountryCamp = x310150_GetCountryBattleLite_CountryCamp( sceneId,killerId)
	
	--�����ͬ���򲻴���
	if nSelfCountryCamp == nKillerCountryCamp then
		return
	end
	
	--ƥ��ɱ���ߵĹ���
	local nSelfMatchCountry = x310150_GetCountryBattleLite_MatchCountry(sceneId,selfId)
	if nSelfMatchCountry ~= killerCountry then
		return
	end
	
	--�ж������ĳ�������������ط�����������Ի�������ӳ�
	local nSceneCountry = x310150_GetCountryIdBySceneId(sceneId)
	
	--�����ɱ�������ط�
	if nSelfCountryCamp == 0 then
		if nSceneCountry == selfCountry then
			
			rongyu = x310150_AddBattleCountryLiteRongyu(sceneId,selfId,killerId,rongyu )
			if rongyu > 0 then
				--��������ӳ�
				AddHonor(sceneId, killerId, rongyu)
				Msg2Player(sceneId, killerId, format("�������ս������%d��",rongyu), 0, 2)
				Msg2Player(sceneId, killerId, format("�������ս������%d��",rongyu), 0, 3)
			elseif rongyu == -3 then
				--����ս�����Ѵ�����
				Msg2Player(sceneId, killerId, "��������ս�����Ѵ����ޣ�", 0, 2)
				Msg2Player(sceneId, killerId, "��������ս�����Ѵ����ޣ�", 0, 2)
			end
			
			return
		end
	end
	
	--��������ɱ�����ǹ���
	if nSelfCountryCamp == 1 then
		if nSceneCountry == killerCountry then
			
			rongyu = x310150_AddBattleCountryLiteRongyu(sceneId,selfId,killerId,rongyu )
			if rongyu > 0 then
				--��������ӳ�
				AddHonor(sceneId, killerId, rongyu)
				Msg2Player(sceneId, killerId, format("�������ս������%d��",rongyu), 0, 2)
				Msg2Player(sceneId, killerId, format("�������ս������%d��",rongyu), 0, 3)
			elseif rongyu == -3 then
				--����ս�����Ѵ�����
				Msg2Player(sceneId, killerId, "��������ս�����Ѵ����ޣ�", 0, 2)
				Msg2Player(sceneId, killerId, "��������ս�����Ѵ����ޣ�", 0, 2)
			end
			return
		end
	end
end


----------------------------------------------------------
--����Ƿ���Դ��͵�Ŀ�곡��
----------------------------------------------------------
function x310150_CheckCountryBattleLiteSceneTrans( sceneId,selfId,targetSceneId )
	
	--����Լ��Ƿ�����Ч����
	if sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 and
	   sceneId ~= 51 and sceneId ~= 151 and sceneId ~= 251 and sceneId ~= 351 and
	   sceneId ~= 58 and sceneId ~= 158 and sceneId ~= 258 and sceneId ~= 358 and
	   sceneId ~= 104 and sceneId ~=204 and sceneId ~= 304 and sceneId ~= 404 and
	   sceneId ~= 76 and sceneId ~= 176 and sceneId ~= 276 and sceneId ~= 376 and 
	   sceneId ~= 86 and sceneId ~= 186 and sceneId ~= 286 and sceneId ~= 386 and
	   sceneId ~= 105 and sceneId ~=205 and sceneId ~= 305 and sceneId ~= 405 and
	   sceneId ~= 106 and sceneId ~=206 and sceneId ~= 306 and sceneId ~= 406 and
	   sceneId ~= 107 and sceneId ~=207 and sceneId ~= 307 and sceneId ~= 407 and
	   sceneId ~= 108 and sceneId ~=208 and sceneId ~= 308 and sceneId ~= 408 and
	   sceneId ~= 109 and sceneId ~=209 and sceneId ~= 309 and sceneId ~= 409 and
	   sceneId ~= 110 and sceneId ~=210 and sceneId ~= 310 and sceneId ~= 410 and
	   sceneId ~= 111 and sceneId ~=211 and sceneId ~= 311 and sceneId ~= 411 and
	   sceneId ~= 91 and sceneId ~= 191 and sceneId ~= 291 and sceneId ~= 391 and sceneId ~= 3 then 
	   
	   return 1;
	end
	
	--���Ŀ�곡���Ƿ�����Ч����
	if targetSceneId ~= 50 and targetSceneId ~= 150 and targetSceneId ~= 250 and targetSceneId ~= 350 and
	   targetSceneId ~= 51 and targetSceneId ~= 151 and targetSceneId ~= 251 and targetSceneId ~= 351 and
	   targetSceneId ~= 58 and targetSceneId ~= 158 and targetSceneId ~= 258 and targetSceneId ~= 358 and
	   targetSceneId ~= 104 and targetSceneId ~= 204 and targetSceneId ~= 304 and targetSceneId ~= 404 and
	   targetSceneId ~= 76 and targetSceneId ~= 176 and targetSceneId ~= 276 and targetSceneId ~= 376 and 
	   targetSceneId ~= 86 and targetSceneId ~= 186 and targetSceneId ~= 286 and targetSceneId ~= 386 and
	   targetSceneId ~= 105 and targetSceneId ~= 205 and targetSceneId ~= 305 and targetSceneId ~= 405 and
	   targetSceneId ~= 106 and targetSceneId ~= 206 and targetSceneId ~= 306 and targetSceneId ~= 406 and
	   targetSceneId ~= 107 and targetSceneId ~= 207 and targetSceneId ~= 307 and targetSceneId ~= 407 and
	   targetSceneId ~= 108 and targetSceneId ~= 208 and targetSceneId ~= 308 and targetSceneId ~= 408 and
	   targetSceneId ~= 109 and targetSceneId ~= 209 and targetSceneId ~= 309 and targetSceneId ~= 409 and
       targetSceneId ~= 110 and targetSceneId ~= 210 and targetSceneId ~= 310 and targetSceneId ~= 410 and
	   targetSceneId ~= 111 and targetSceneId ~= 211 and targetSceneId ~= 311 and targetSceneId ~= 411 and
	   targetSceneId ~= 91 and targetSceneId ~= 191 and targetSceneId ~= 291 and targetSceneId ~= 391 and targetSceneId ~= 3 then 
	   
	   
	   	--�������Ƿ���Ч
	   	if x310150_IsMissionCanAccept( sceneId,selfId) == 0 and IsHaveQuest(sceneId,selfId, x310150_g_MissionId) == 1 then
	   	
	   		--�Ѿ�����?
	   		if x310150_g_Match0[sceneId][1] == -1 then
	   			return 1
	   		end
	   		
	   		--���ܴ���,�������ʾ
	   		Msg2Player(sceneId, selfId, "�����ڽ����ˡ����ҡ�����ս,���ڼ䲻�ܴ��ͣ�", 0, 2)
			Msg2Player(sceneId, selfId, "�����ڽ����ˡ����ҡ�����ս,���ڼ䲻�ܴ��ͣ�", 0, 3)	
	   		
	   		return 0
	   	else
	   		--���Դ���
	   		return 1
	   	end
	   
	end
	
	--���Դ���
	return 1
		
end

----------------------------------------------------------
--�������͵�Ŀ�곡��
----------------------------------------------------------
function x310150_CheckCountryBattleLiteFubenTrans( sceneId,selfId )
	
	   
   	--�������Ƿ���Ч
   	if x310150_IsMissionCanAccept( sceneId,selfId) == 0 and IsHaveQuest(sceneId,selfId, x310150_g_MissionId) == 1 then
   	
   		--�Ѿ�����?
   		if x310150_g_Match0[sceneId][1] == -1 then
   			return 1
   		end
   		
   		--���ܴ���,�������ʾ
   		--Msg2Player(sceneId, selfId, "�����ڽ����ˡ����ҡ�����ս,���ڼ䲻�ܴ��ͣ�", 0, 2)
			--Msg2Player(sceneId, selfId, "�����ڽ����ˡ����ҡ�����ս,���ڼ䲻�ܴ��ͣ�", 0, 3)	
   		
   		return 0
   	else
   		--���Դ���
   		return 1
   	end
	   

		
end

----------------------------------------------------------
--����Ƿ�����������ȡ����
----------------------------------------------------------
function x310150_IsNewFlow( sceneId,selfId)
	

	--ȡ�ù���ID
	local nCountry = GetCurCountry( sceneId,selfId )
	
	local nBonusFlag = 0
	
	if x310150_g_Match0[sceneId][1] == nCountry then
        nBonusFlag = x310150_g_BonusFlag0[sceneId][1]
    elseif x310150_g_Match0[sceneId][2] == nCountry then
        nBonusFlag = x310150_g_BonusFlag0[sceneId][2]
    elseif x310150_g_Match1[sceneId][1] == nCountry then
        nBonusFlag = x310150_g_BonusFlag1[sceneId][1]
    elseif x310150_g_Match1[sceneId][2] == nCountry then
        nBonusFlag = x310150_g_BonusFlag1[sceneId][2]
    end
    
    --������ȡ
    if nBonusFlag <= 0 then
    	return 0
    end
    
    --���������콱����
    return 1
	
end

----------------------------------------------------------
--����Ƿ������ȡ����
----------------------------------------------------------
function x310150_IsCanReciveBonus( sceneId,selfId )
	
	--ȡ�ù���ID
	local nCountry = GetCurCountry( sceneId,selfId )
	
	local nBonusFlag = 0
	
	if x310150_g_Match0[sceneId][1] == nCountry then
        nBonusFlag = x310150_g_BonusFlag0[sceneId][1]
    elseif x310150_g_Match0[sceneId][2] == nCountry then
        nBonusFlag = x310150_g_BonusFlag0[sceneId][2]
    elseif x310150_g_Match1[sceneId][1] == nCountry then
        nBonusFlag = x310150_g_BonusFlag1[sceneId][1]
    elseif x310150_g_Match1[sceneId][2] == nCountry then
        nBonusFlag = x310150_g_BonusFlag1[sceneId][2]
    end
    
    --������ȡ
    if nBonusFlag <= 0 then
    	return 0
    end
    
    --����10����
    local nMin = GetMinOfYear() - nBonusFlag
    if nMin > 10 or nMin < 0 then
    	return 0
    end
    
    --������ȡ
    return 1
end


----------------------------------------------------------
--���������Ƿ��Ѿ�����
----------------------------------------------------------
function x310150_OnCountryKillCountChanged( sceneId,countryId,killcount )


	--����Ƿ��ǹ���
	if x310150_IsCountryAttact( sceneId, countryId ) ~= 1 then
		return
	end

	
	--����Ƿ���10��.
	if killcount ~= 10 then
		return
	end
	
	--��ʼ������Ч
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 and GetHp(sceneId,objId ) > 0 and GetCurCountry(sceneId,objId ) == countryId then
        	--CallScriptFunction(UTILITY_SCRIPT,"PlayClientRiseEffect",sceneId,objId)
			SendSpecificImpactToUnit(sceneId, objId, objId, objId,8321, 0);
			x310150_OnTopListYanghua(sceneId,objId)
        end
    end
	
end

function x310150_OnTopListYanghua(mapId,playerId)

	
	--ȡ���ϴμ�¼���ܺʹ���
	local lastweek = GetQuestData( mapId, playerId, MD_YANHUA_WEEK[1], MD_YANHUA_WEEK[2], MD_YANHUA_WEEK[3] )
	local curcount = GetQuestData( mapId, playerId, MD_YANHUA_COUNT[1], MD_YANHUA_COUNT[2], MD_YANHUA_COUNT[3] )
	
	--ȡ�õ�ǰ�ܣ������ǰ�����ϴμ�¼���ܲ�ƥ�䣬���������
	local curweek = CallScriptFunction( 888888, "GetWorldWeek", mapId)
	if lastweek ~= curweek then
		curcount = 0
	end

	
	--������أ�Ȼ���¼
	curcount = curcount + 1
	SetQuestData( mapId, playerId, MD_YANHUA_COUNT[1], MD_YANHUA_COUNT[2], MD_YANHUA_COUNT[3], curcount )
	SetQuestData( mapId, playerId, MD_YANHUA_WEEK[1], MD_YANHUA_WEEK[2], MD_YANHUA_WEEK[3], curweek )

	--����������ݵ�gl
	SendToplistKeyValue2GL(mapId, playerId, YANHUA_TOPLIST, curcount)
	
end

----------------------------------------------------------
--ȡ�ù��һ���
----------------------------------------------------------
function x310150_GetCountryScore( countryId )

	if countryId == x310150_g_Match0[sceneId][1] then
        return x310150_g_MatchScore0[sceneId][1]
    elseif countryId == x310150_g_Match0[sceneId][2] then
        return x310150_g_MatchScore0[sceneId][2] 
    elseif countryId == x310150_g_Match1[sceneId][1] then
        return x310150_g_MatchScore1[sceneId][1]
    elseif countryId == x310150_g_Match1[sceneId][2] then
        return x310150_g_MatchScore1[sceneId][2]
    end

end

----------------------------------------------------------
--����ս����ʱ��ʾ
----------------------------------------------------------
function x310150_OnCountryBattleLiteFinish( sceneId )
	
	--ֻ��¥�����Ǵ���
	if sceneId ~= 50 then
		return
	end

	--����Ѿ�Ϊ-1,��ʾ�Ѿ�������,�Ѿ�����Ĳ�����
	if x310150_g_Match0[sceneId][1] == -1 then
		return
	end

	--ȡ�ù�������
	local Country1 = CallScriptFunction(UTILITY_SCRIPT,"GetCountryName",sceneId,x310150_g_Match0[sceneId][2])
	local Country2 = CallScriptFunction(UTILITY_SCRIPT,"GetCountryName",sceneId,x310150_g_Match0[sceneId][1])
	local Country3 = CallScriptFunction(UTILITY_SCRIPT,"GetCountryName",sceneId,x310150_g_Match1[sceneId][2])
	local Country4 = CallScriptFunction(UTILITY_SCRIPT,"GetCountryName",sceneId,x310150_g_Match1[sceneId][1])
	
	local msg = format("%s��ɱ%d��%s���Ҿ���,%s��ɱ%d��%s���Ҿ���",Country2,x310150_g_MatchScore0[sceneId][1],Country1,Country4,x310150_g_MatchScore1[sceneId][1],Country3 )
	LuaAllScenceM2Wrold(sceneId,msg,1,4)
end
