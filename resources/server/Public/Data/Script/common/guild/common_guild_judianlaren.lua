x300920_g_ScriptId = 300920
x300920_g_MissionName="【国家】进入领主战场"

x300920_g_Laird_Signup                  	= 300     --报名
x300920_g_Laird_WaitBattle              	= 301     --报名结束，等待领主战场
x300920_g_Laird_BeginBattle             	= 302     --开始领主战场
x300920_g_Laird_EndBattle               	= 303     --结束领主战场

function x300920_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_LAIRDGBATTLELITE ) == 0 then
        return
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end
	
	local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
    if nBattleStatus ~= x300920_g_Laird_BeginBattle then
    	return 1
    end

    if CallScriptFunction(300918,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
       return 1
    end

	AddQuestNumText(sceneId,x300920_g_ScriptId,x300920_g_MissionName,3);
end


function x300920_ProcEventEntry( sceneId, selfId, targetId )
    
    --领主战场状态
    local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
    if nBattleStatus ~= x300920_g_Laird_BeginBattle then
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


    if CallScriptFunction(300918,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        
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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_LAIRDGBATTLELITE ) == 0 then
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
    AddQuestText( sceneId, "确认要进入领主战场吗？" )
    EndQuestEvent( sceneId )
    DispatchQuestInfo( sceneId, selfId, targetId, x300920_g_ScriptId,-1 )

    return 1
end

--********************
--检测接受条件
--**********************************
function x300920_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

--**********************************
--接受
--**********************************
function x300920_ProcAccept( sceneId, selfId )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_LAIRDGBATTLELITE ) == 0 then
        return
    end
	
	local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
    if nBattleStatus ~= x300920_g_Laird_BeginBattle then
    	return
    end

    local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return
	end

    if CallScriptFunction(300918,"GetBattleEnterSceneFlag",sceneId) ~= 1 then
        return
    end

    --玩家状态
    local state,msg = CallScriptFunction(800021,"BattleTransCheckPlayerState", sceneId,selfId )
    if state == 1 then
        return
    end

    --进入领主战场
    GameBattleRequestEnterScene(sceneId, selfId,2) 
end

function x300920_OnLairdBattleChangeScene(sceneId,selfId,nRetCode,newSceneID,nBattleCamp)
	
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
			    SetPos( sceneId , selfId , 43 ,90 )
	        else
	            SetPos( sceneId , selfId , 205,147 )
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

			NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,300920 )
		end
		
	else
		x300920_OnLairdBattleTransError(sceneId,selfId,nRetCode )
	end
end

function x300920_OnLairdBattleTransError(sceneId,selfId,nRetCode )

	if nRetCode == 300 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "没有开始")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 301 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "没有帮会")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )

	elseif nRetCode == 302 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "帮会没有报名")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 303 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "战场已经结束")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 304 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "轮空")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 305 then
	
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "进场景时间已过")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 306 then
		
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, "玩家已经进入过场景了")
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
	elseif nRetCode == 307 then
		
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
function x300920_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--继续
--**********************************
function x300920_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--检测是否可以提交
--**********************************
function x300920_CheckSubmit( sceneId, selfId )
end

--**********************************
--提交
--**********************************
function x300920_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

