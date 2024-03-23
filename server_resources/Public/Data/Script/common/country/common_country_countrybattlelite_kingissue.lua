x310154_g_scriptId                      = 310154

x310154_g_Time					= { min = 2000,max = 2059 }	--时间限制
----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x310154_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    --合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
		
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
	local hour,minute,sec =GetHourMinSec(); --检查时间是否正确
	local now = hour *100 + minute
	if now < x310154_g_Time.min or now > x310154_g_Time.max then
		return
	end
	
	
    --屠城战是否开启
    local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
    if  camp < 0 then
        return
    end
    
    
    --取得国家ID
    local nCountry = -1
    if camp == 0 then --防守方，取得本国王城ID
    	nCountry = GetCurCountry(sceneId, selfId)
    elseif camp == 1 then
    	nCountry = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_MatchCountry", sceneId, selfId)
    end
    --判断国家ID是否有效
    if nCountry < 0 or nCountry > 3 then
    	return
    end
    
    --只有在配对方的守方场景和进攻方的密道里才能使用国王召集
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
    
    --开启国王召集按钮
    AddQuestNumText(sceneId,x310154_g_scriptId,"【屠城战】守方国王召集令",3);
    
    --记日志
    local CountryID = GetCurCountry(sceneId,selfId)
		
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "ErrorName"
	end
	
    local strMsg = format("CBL:<Info>x310154_ProcEnumEvent [kingissue] sceneId = %d, name=%s, nCountryId=%d", sceneId, name, CountryID  )
    WriteLog( 1, strMsg )
end

function x310154_OnReturn(sceneId, selfId,MissionData,MissionId)

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    --屠城战是否开启
    if CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId) < 0 then
        return
    end
    
     --只有国王才能拉人
    if IsKing(sceneId, selfId) <= 0  then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【屠城战】国王召集令#W#r\t只有国王才能使用【屠城战】国王召集令!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,selfId)
		
		return
    end
    
    
    if MissionData == nil or MissionData > 3 or MissionData <= 0 then
    	--其他任何情况，都认为是使用次数达上限，不问原因
		
		local CountryID = GetCurCountry(sceneId,selfId)
		
		local strName = GetName( sceneId,selfId )
		if strName == nil then
			strName = " "
		end
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【屠城战】国王召集令#W#r\t很抱歉，【屠城战】国王召集令只能使用3次!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,selfId)
		
		LuaScenceM2Player( sceneId,selfId,"很抱歉，【屠城战】国王召集令只能使用3次!",strName,3,1 )
		LuaScenceM2Player( sceneId,selfId,"很抱歉，【屠城战】国王召集令只能使用3次!",strName,2,1 )
		
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
	AddQuestText(sceneId, format("#Y【屠城战】国王召集令#W#r\t您使用了【屠城战】国王召集令，还剩%d次！",MissionData-1));
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,selfId)
	
	local npcGUID = GetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_KINGISSUE_NPC)
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCountryQuestData(sceneId, nCountryId, CD_INDEX_COUNTRYBATTLELITE_KINGISUE_NPC,npcGUID)
	
	--向本国广播
	local msg = "国王发布了【屠城战】召集令";
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
--脚本默认事件
----------------------------------------------------------------------------------------------
function x310154_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

    --合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --测试服开关
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --战场自己的开关
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    if CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId) < 0 then
        return
    end
    
    --只有国王才能拉人
    if IsKing(sceneId, selfId) <= 0  then
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y【屠城战】国王召集令#W#r\t只有国王才能使用【屠城战】国王召集令!");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,selfId)
		
		return
    end
    
    --设置NPCID
    local npcGUID = GetMonsterGUID( sceneId, npcId)
    SetPlayerRuntimeData(sceneId,selfId,RD_COUNTRYBATTLELITE_KINGISSUE_NPC,npcGUID)
    
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCountryQuestData(sceneId, nCountryId, CD_INDEX_COUNTRYBATTLELITE_KINGISUE_NPC,npcGUID)
    
    --回调国王拉人事件
    GetCountryQuestData(sceneId,selfId,CD_INDEX_COUNTRYBATTLELITE_KINGISUSE, x310154_g_scriptId,-1,"OnReturn")
    
end


function x310154_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x310154_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x310154_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x310154_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x310154_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x310154_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x310154_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x310154_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x310154_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end