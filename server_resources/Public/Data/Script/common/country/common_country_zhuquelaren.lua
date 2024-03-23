x310115_g_ScriptId = 310115
x310115_g_MissionName="朱雀战场传送"

x310115_g_ZhuQue_Signup                  	= 100     --报名
x310115_g_ZhuQue_WaitBattle              	= 101     --报名结束，等待朱雀战场
x310115_g_ZhuQue_BeginBattle             	= 102     --开始朱雀战场
x310115_g_ZhuQue_EndBattle               	= 103     --结束朱雀战场

function x310115_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_ZHUQUEBATTLELITE ) == 0 then
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
	local nBattleStatus = CallScriptFunction(310113,"GetBattleState",sceneId)
    if nBattleStatus ~= x310115_g_ZhuQue_BeginBattle then
    	return 1
    end

    if CallScriptFunction(310113,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
       return 1
    end

	AddQuestNumText(sceneId,x310115_g_ScriptId,x310115_g_MissionName,3);
end


function x310115_ProcEventEntry( sceneId, selfId, targetId )
    
    --朱雀战场状态
    local nBattleStatus = CallScriptFunction(310113,"GetBattleState",sceneId)
    if nBattleStatus ~= x310115_g_ZhuQue_BeginBattle then
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


    if CallScriptFunction(310113,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        
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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_ZHUQUEBATTLELITE ) == 0 then
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
    AddQuestText( sceneId, "确认要进入朱雀战场吗？" )
    EndQuestEvent( sceneId )
    DispatchQuestInfo( sceneId, selfId, targetId, x310115_g_ScriptId,-1 )

    return 1
end

--********************
--检测接受条件
--**********************************
function x310115_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--接受
--**********************************
function x310115_ProcAccept( sceneId, selfId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_ZHUQUEBATTLELITE ) == 0 then
        return
    end
    
    --检查是否有国王
    local nHumanGUID = GetPlayerGUID( sceneId,selfId )
    local nCountryId,nKingGUID,szKingName,nCountryGold = GetCountrySimpleData( sceneId,selfId )
    if nKingGUID <= 0 or nHumanGUID == nKingGUID then
    	return    	
    end
	
	local nBattleStatus = CallScriptFunction(310113,"GetBattleState",sceneId)
    if nBattleStatus ~= x310115_g_ZhuQue_BeginBattle then
    	return
    end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return
	end

    if CallScriptFunction(310113,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        return
    end

    --玩家状态
    local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
    if state == 1 then
        return
    end

    --进入朱雀战场
    GameBattleRequestEnterScene(sceneId, selfId,0) 
end

function x310115_OnZhuQueBattleChangeScene(sceneId,selfId,nRetCode,newSceneID,nBattleCamp)
	
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

			NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,310115 )
		end
		
	else
		x310115_OnZhuQueBattleTransError(sceneId,selfId,nRetCode )
	end
end

function x310115_OnZhuQueBattleTransError(sceneId,selfId,nRetCode )

	if nRetCode == 100 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "没有开始")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 101 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "没有帮会")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )

	elseif nRetCode == 102 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "帮会没有报名")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 103 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "战场已经结束")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 104 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "轮空")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 105 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "进场景时间已过")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 106 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "玩家已经进入过场景了")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 107 then
		
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
function x310115_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x310115_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x310115_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x310115_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

