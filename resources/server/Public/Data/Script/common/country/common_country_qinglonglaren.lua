x310112_g_ScriptId = 310112
x310112_g_MissionName="青龙战场传送"

x310112_g_QingLong_Signup                  	= 200     --报名
x310112_g_QingLong_WaitBattle              	= 201     --报名结束，等待青龙战场
x310112_g_QingLong_BeginBattle             	= 202     --开始青龙战场
x310112_g_QingLong_EndBattle               	= 203     --结束青龙战场

function x310112_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_QINGLONGBATTLELITE ) == 0 then
        return
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end
	
	--检查是否有国王
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
	
	--检查状态
	local nBattleStatus = CallScriptFunction(310110,"GetBattleState",sceneId)
    if nBattleStatus ~= x310112_g_QingLong_BeginBattle then
    	return 1
    end

    if CallScriptFunction(310110,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
       return 1
    end

	AddQuestNumText(sceneId,x310112_g_ScriptId,x310112_g_MissionName,3);
end


function x310112_ProcEventEntry( sceneId, selfId, targetId )
    
    --青龙战状态
    local nBattleStatus = CallScriptFunction(310110,"GetBattleState",sceneId)
    if nBattleStatus ~= x310112_g_QingLong_BeginBattle then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "战场未开放！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "没有帮会,不能申请进入战场！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end


    if CallScriptFunction(310110,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "现在不能进入战场！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
        return 1
    end

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_QINGLONGBATTLELITE ) == 0 then
       return
    end
    
    --检查是否有国王
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
    

    --玩家状态
    local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
    if state == 1 then
        
        BeginQuestEvent(sceneId)
        AddQuestText( sceneId, msg );
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 1
    end

    BeginQuestEvent( sceneId )
    AddQuestText( sceneId, "确认要进入青龙战场吗？" )
    EndQuestEvent( sceneId )
    DispatchQuestInfo( sceneId, selfId, targetId, x310112_g_ScriptId,-1 )

    return 1
end

--********************
--检测接受条件
--**********************************
function x310112_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--接受
--**********************************
function x310112_ProcAccept( sceneId, selfId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_QINGLONGBATTLELITE ) == 0 then
        return
    end
    
    --检查是否有国王
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
	
	local nBattleStatus = CallScriptFunction(310110,"GetBattleState",sceneId)
    if nBattleStatus ~= x310112_g_QingLong_BeginBattle then
    	return
    end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return
	end

    if CallScriptFunction(310110,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        return
    end

    --玩家状态
    local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
    if state == 1 then
        return
    end

    --进入青龙战场
    GameBattleRequestEnterScene(sceneId, selfId,1) 
end

function x310112_OnQingLongBattleChangeScene(sceneId,selfId,nRetCode,newSceneID,nBattleCamp)
	
	if nRetCode == 0 then
		
		--如果在监狱不可以被传送
		if sceneId == PK_PUNISH_PRISON_SCENE_ID then
			BeginQuestEvent(sceneId)
			local strText = "监狱里还不老实,想走,没门。"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			return
		end
	
	    local PosX = 100
	    local PosZ = 100
	
	
	    if sceneId == newSceneID then
	        
	        if Flag == 0 then
			    SetPos( sceneId , selfId , 47 , 218 )
	        else
	            SetPos( sceneId , selfId , 209,35 )
	        end
		else
	        
	        --检查状态
	        local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
	        if state == 1 then
	            
	            BeginQuestEvent(sceneId)
	            AddQuestText( sceneId, msg );
	            EndQuestEvent(sceneId)
	            DispatchQuestTips(sceneId,selfId)
	            return
	        end
	        
	        --检查是否可以传送
			if CallScriptFunction(COUNTRY_BATTLE_LITE_SCRIPT,"CheckCountryBattleLiteSceneTrans",sceneId,selfId,newSceneID) == 0 then
				return
			end
	
	        --记录一个RuntimeData
	        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
	        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
	        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
	        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
	        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,1)

			NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,310112 )
		end
		
	else
		x310112_OnQingLongBattleTransError(sceneId,selfId,nRetCode )
	end
end

function x310112_OnQingLongBattleTransError(sceneId,selfId,nRetCode )

	if nRetCode == 200 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "没有开始")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 201 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "没有帮会")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )

	elseif nRetCode == 202 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "帮会没有报名")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 203 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "战场已经结束")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 204 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "轮空")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 205 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "进场景时间已过")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 206 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "玩家已经进入过场景了")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 207 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "战场玩家已达上限")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	else
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "未知错误")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	end

end

--**********************************
--放弃
--**********************************
function x310112_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x310112_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x310112_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x310112_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

