
x300813_g_scriptId                      = 300813
x300813_g_TotalBattleTime               = 60 * 20     	--战争持续时间1200秒        19:00-19:20

--玩法类型
x300813_g_SceneName                     = { {Name="zhanchang_guowangzhanchang/zhanchang_guowangzhanchang.scn",Script=300813} }

x300813_g_King_Signup                  = 2     --报名
x300813_g_King_WaitBattle              = 3     --报名结束，等待国王战场
x300813_g_King_BeginBattle             = 4     --开始国王战场
x300813_g_King_EndBattle               = 5     --结束国王战场

--奖励相关
x300813_g_MaxScore                     = 49	            --从0开始计数
x300813_g_BonusTips                    = "#G您获得了#R%d#G点经验,#R%d#G点帮会贡献,#R%d#G帮会经验!" --奖励提示
x300813_g_BonusTips1                   = "您获得了奖励" --奖励提示


--经验奖励
x300813_g_WinPrise                     = 1000*0.5*20              --获胜方经验奖励系数，只与等级有关
x300813_g_LosePrise                    = 1000*0.1*20              --失败方经验奖励系数，只与等级有关
x300813_g_DeucePrise                   = 1000*0.3*20              --战平时经验奖励系数，只与等级有关

--帮贡奖励
x300813_g_WinBangGong                  = 25

x300813_g_DeuceBangGong                = 20

--帮会经验
x300813_g_WinBangExp                   = 2
x300813_g_LoseBangExp                  = 2
x300813_g_DeuceBangExp                 = 2

x300813_g_Guild_Camp_A                 = 5
x300813_g_Guild_Camp_B                 = 6

x300813_g_Leader_Index                 = 5

x300813_g_Kick_Down                    = 8



----------------------------------------------------------------------------------------------
--检查是否是国王战场场景，如果不是返回0，是返回1
----------------------------------------------------------------------------------------------
function x300813_GetKingBattleSceneScript( sceneId )

    local name = GetBattleSceneName(sceneId)
    for i,item in x300813_g_SceneName do
        if name == item.Name then
            return item.Script
        end
    end

    return 0
end


----------------------------------------------------------------------------------------------
--活动触发
----------------------------------------------------------------------------------------------
function x300813_OnBattleStateEvent( sceneId, state  )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_KINGBATTLE ) == 0 then
        return
    end


	local sceneType = GetSceneType(sceneId);
	if sceneType == 0 then --场景类型是普通场景

        if state == x300813_g_King_Signup then

            --检查状态是否已经置过
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_SIGNUP then
                
                --记录日志
                local msg = format("KBL:STATE_KING_BATTLE_SIGNUP,SceneId=%d ",sceneId  )
                WriteLog(1,msg)

            end
            
            --开始报名
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_SIGNUP)
            
        elseif state == x300813_g_King_WaitBattle then

            --检查状态是否已经置过
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_SIGNUP_FINISH then
                
                --记录日志
                local msg = format("KBL:STATE_KING_BATTLE_SIGNUP_FINISH,SceneId=%d ",sceneId )
                WriteLog(1,msg)

            end
            
            --报名结束
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_SIGNUP_FINISH)
            
        elseif state == x300813_g_King_BeginBattle then

            --检查状态是否已经置过
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus == STATE_KING_BATTLE_BATTLE then
                
                --记录日志
                local msg = format("KBL:STATE_KING_BATTLE_BATTLE,SceneId=%d ",sceneId )
                WriteLog(1,msg)

            end
            
            --开始国王战场
		    SetKingBattleStatus(sceneId,STATE_KING_BATTLE_BATTLE)
            SetKingBattleEnterSceneFlag( sceneId,1)

        elseif state == x300813_g_King_EndBattle then
            
            --国王战场结束
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_BATTLE_FINISH)

            --记录日志
            local msg = format("KBL:STATE_KING_BATTLE_BATTLE_FINISH, SceneId=%d",sceneId )
            WriteLog(1,msg)

        end

	elseif sceneType == 2 then --场景类型是国王战场场景
        
        --检查是否是国王战场场景列表中所处理的情况，如果不是，则不处理
        local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
        if  nScriptId == 0 then
            return
        end

        if state == x300813_g_King_Signup then

            --检查状态是否已经置过
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_READY then
                
                --记录日志
                local msg = format("KBL:STATE_KING_BATTLE_SIGNUP,SceneId=%d,2 ",sceneId  )
                WriteLog(1,msg)

            end

            KingBattleAskInit( sceneId )                                               --向GLServer注册一下
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_READY)                      --设置状态


            --设置基本数据
            SetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_SCRIPT,KINGBATTLE_FLOW_SCRIPT)

        elseif state == x300813_g_King_WaitBattle then

            --检查状态是否已经置过
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_SIGNUP_FINISH then
                
                --记录日志
                local msg = format("KBL:STATE_KING_BATTLE_SIGNUP_FINISH,SceneId=%d,2",sceneId )
                WriteLog(1,msg)

            end

            --设置基本数据
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_SIGNUP_FINISH)
            SetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_SCRIPT,KINGBATTLE_FLOW_SCRIPT)

        elseif state == x300813_g_King_BeginBattle then

            --检查状态是否已经置过
            local selfStatus = GetKingBattleStatus(sceneId)
            if selfStatus ~= STATE_KING_BATTLE_BATTLE then
                
                --记录日志
                local msg = format("KBL:STATE_KING_BATTLE_BATTLE,SceneId=%d,2",sceneId )
                WriteLog(1,msg)

            end

            --设置基本数据            
            SetKingBattleStatus(sceneId,STATE_KING_BATTLE_BATTLE)                     --设置开始国王战场
            SetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_SCRIPT,KINGBATTLE_FLOW_SCRIPT)
            SetKingBattleEnterSceneFlag( sceneId,1)

            x300813_OnBattleSceneReady( sceneId,( x300813_g_TotalBattleTime) )

        elseif state == x300813_g_King_EndBattle then

            local nState = GetKingBattleStatus( sceneId )
            if nState > STATE_KING_BATTLE_BATTLE or nState < STATE_KING_BATTLE_READY then
                
                --记录日志
                local msg = format("KBL:STATE_KING_BATTLE_BATTLE_FINISH,Result:nState > STATE_KING_BATTLE_BATTLE or nState < STATE_KING_BATTLE_READY  SceneId=%d,state=%d,2",sceneId, nState )
                WriteLog(1,msg)

                --根据玩法的脚本的不同，进行相关初始化回调
                x300813_OnBattleSceneClose( sceneId )

                --记录日志
                local msg = format("KBL:STATE_KING_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
                WriteLog(1,msg)
                return
            end

            --设置状态，活动结束
    		SetKingBattleStatus(sceneId,STATE_KING_BATTLE_BATTLE_FINISH)
            x300813_OnBattleSceneClose( sceneId )

            --记录日志
            local msg = format("KBL:STATE_KING_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
            WriteLog(1,msg)
        end
	end
end

----------------------------------------------------------------------------------------------
--国王战场场心跳
----------------------------------------------------------------------------------------------
function x300813_ProcTiming( sceneId,uTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --检查是否是国王战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
       
    x300813_OnBattleSceneTimer( sceneId, uTime)
end


----------------------------------------------------------------------------------------------
--玩家进入事件
----------------------------------------------------------------------------------------------
function x300813_OnPlayerEnter( sceneId, playerId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --检查是否是国王战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local status = GetKingBattleStatus( sceneId )
    if status ~= STATE_KING_BATTLE_BATTLE then
    
        --x300813_RestoreAllPlayerCamp( sceneId )
        --x300813_KingBattleKickAllPlayer(sceneId) --顺例踢下所有人
        x300813_SetAllPlayerNeedKick( sceneId )
        --记录日志
        local msg = format("KBL:x300813_OnBattlePlayerEnter Kick,Player,SceneId=%d,playerId=%d status=%d",sceneId,playerId,status )
        WriteLog(1,msg)
        return
    end


    --取得帮会A和帮会B
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,playerId )

    --设置在战场中的阵营属性
    local nSendCCamp = -1
    if nGuildId == nGuildA then
        nSendCCamp = 0
    elseif nGuildId == nGuildB then
        nSendCCamp = 1
    else
        SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN ,x300813_g_Kick_Down) 
        --记录日志
        local msg = format("KBL:x300813_OnBattlePlayerEnter Kick 2,Player,SceneId=%d,playerId=%d",sceneId,playerId )
        WriteLog(1,msg)
        return

    end

    --积分栏设定
    SetKingBattleDisable(sceneId, playerId, 0, nSendCCamp )

    local strGuildA = GetGuildName( nGuildA )
    local strGuildB = GetGuildName( nGuildB )

    SendKingBattleInfo( sceneId, playerId, strGuildA, strGuildB )

    --玩家进入战场，则清空之前的数据
    SetPlayerRuntimeData(sceneId,playerId,RD_KING_BATTLE_BEKILLED,0)

    --设置阵营
    
    if nGuildId == nGuildA then
        SetCurCamp(sceneId,playerId,x300813_g_Guild_Camp_A)
        SetPos(sceneId,playerId,50,204)

    elseif nGuildId == nGuildB then
        SetCurCamp(sceneId,playerId,x300813_g_Guild_Camp_B)
        SetPos(sceneId,playerId,206,48)
    end

    SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN,-1)

    --对玩家原先的场景进行备份
    local scenePre = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_SCENE_PRE ) - 1
    if scenePre >= 0 then
        
        local CurX = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSZ_PRE)

        SetPlayerBakSceneInfo(sceneId,playerId,scenePre,CurX,CurZ)

        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_SCENE_PRE,0)
        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSX_PRE,0)
        SetPlayerRuntimeData(sceneId,playerId,RD_HUMAN_POSZ_PRE,0)

    end

end

----------------------------------------------------------------------------------------------
--玩家离开事件
----------------------------------------------------------------------------------------------
function x300813_OnPlayerLeave( sceneId, playerId )
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --检查是否是国王战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local nCountryId = GetCurCountry(sceneId,playerId )
    SetCurCamp( sceneId,playerId,nCountryId )

    SetKingBattleDisable(sceneId, playerId,1,-1)
end

----------------------------------------------------------------------------------------------
--玩家退会
----------------------------------------------------------------------------------------------
function x300813_OnPlayerLeaveGuild( sceneId,selfId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --检查是否是国王战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end
    
    x300813_KingBattleKickPlayer( sceneId,selfId )
    SetKingBattleDisable(sceneId, selfId,1,-1)

end

----------------------------------------------------------------------------------------------
--设置国王战场相关配对信息
----------------------------------------------------------------------------------------------
function x300813_OnSetKingBattleMatchInfo( sceneId,nGuildA,nGuildB,nCountryId )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --检查是否是国王战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD, nGuildA )
    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD, nGuildB )
    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_COUNTRYID, nCountryId )

    --debug
    local a = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local b = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )
    local c = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_COUNTRYID )

    local msg = format( "KBL:KING_BATTLE_MATCHINFO:sceneId=%d,A=%d,B=%d,CountryId=%d", sceneId, a, b,c )
    WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--玩家重新上线
----------------------------------------------------------------------------------------------
function x300813_OnPlayerNewConnectEnter( sceneId, selfId )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --检查是否是国王战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    local BattleSceneFlag = GetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG)
    if BattleSceneFlag == 0 then

        --新上线的玩家,设置Kick倒计时，准备踢掉
        SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN,x300813_g_Kick_Down)

        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "KBL:x300813_OnPlayerNewConnectEnter 0,need kick,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

    else

        --从别一个服务器转过来的玩家
        --同组服务器的玩家,这时的RD_BATTLESCENE_ENTER_FLAG值目前无法清0，
        --只有在玩家离开战场或下线时清除，但是不同服务器组的可以马上清除
        local name = GetName(sceneId,selfId)
        if name == nil then
            name = "ErrorName"
        end
        local msg = format( "KBL:x300813_OnPlayerNewConnectEnter 1,sceneId=%d,selfId=%d,name=%s", sceneId, selfId, name )
        WriteLog(1,msg)

        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    end

    --x300813_KingBattleKickPlayer( sceneId,selfId )
end

----------------------------------------------------------------------------------------------
--玩家死亡处理
----------------------------------------------------------------------------------------------
function x300813_OnPlayerDie( sceneId, selfId, killerId  )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --检查是否是国王战场场景列表中所处理的情况，如果不是，则不处理
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if  nScriptId == 0 then
        return
    end

    --记录被杀次数
    local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED ) + 1
    SetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED,nBeKilled)

    --是玩家杀死的
    local ObjType = GetObjType(sceneId, killerId)

    --杀人者在线并且是玩家，被杀的人死亡6次以内（包含6次）
    if IsPlayerStateNormal( sceneId,killerId ) == 1 and ObjType == 1 and nBeKilled <= 6 then

        AddGuildUserPoint(sceneId,killerId,10)

        local msg = "您获得了10点帮贡"
        local name = GetName(sceneId,killerId )

        LuaScenceM2Player(sceneId, killerId, msg, name , 2,1)
    
    end

    --超过六次，不再提示
    if nBeKilled <= 6 then 

        local str = format("#G%s在国王战场中被杀死%d次。",GetName(sceneId,selfId ),nBeKilled )
        LuaThisScenceM2Wrold(sceneId,str,3,1)
        LuaThisScenceM2Wrold(sceneId,str,2,1)
    end

    --第六次，给提示
    if nBeKilled == 6 then

        local nCountryId = GetCurCountry( sceneId,selfId)

        local str = format("#G%s在国王战场中，死亡次数已满，被迫离开战场。",GetName(sceneId,selfId ) )
        LuaAllScenceM2Country(sceneId,str,nCountryId,3,1)
        LuaAllScenceM2Country(sceneId,str,nCountryId,2,1)

        --RestoreHp(sceneId, selfId,100)
	    --RestoreRage(sceneId, selfId,100)
	    --ClearMutexState(sceneId, selfId, 6)
	    --SendReliveResult(sceneId, selfId,1)	

        --x300813_KingBattleKickPlayer( sceneId,selfId )

        --加入倒计时保护，防止一直被杀，而不退出战场
        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
        if KickDown <= 0 or KickDown > 4 then
            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,4) 
        end
    end

end

-------------------------------------------------------------------------------
--检查状态是否正常
-------------------------------------------------------------------------------
function x300813_CheckPlayerState( sceneId,selfId )
    

    local state
    local ErrorMsg

    state = IsPlayerStateNormal(sceneId,selfId )
    if state == 0 then
        ErrorMsg = "状态异常"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_MENTALGAME )
    if state == 1 then
        ErrorMsg = "处于答题状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_STALL )
    if state == 1 then
        ErrorMsg = "处于摆摊状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE )
    if state == 1 then
        ErrorMsg = "处于死亡状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_CRASHBOX )
    if state == 1 then
        ErrorMsg = "处于运镖状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY )
    if state == 1 then
        ErrorMsg = "处于挂机状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_SUBTRAIN )
    if state == 1 then
        ErrorMsg = "处于代练状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_BUS )
    if state == 1 then
        ErrorMsg = "处于BUS状态，不能进入战场"
        return 1,ErrorMsg
    end

    state = IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_PKMODE )
    if state == 1 then
        ErrorMsg = "PK值过高或处于狂暴模式，不能进入战场"
        return 1,ErrorMsg
    end

    return 0

end

-------------------------------------------------------------------------------
--国王战场相关传送脚本
-------------------------------------------------------------------------------
function x300813_OnKingBattleChangeScene( sceneId,selfId,newSceneID,Flag )
    

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
		    SetPos( sceneId , selfId , 50 , 204 )
        else
            SetPos( sceneId , selfId , 206,48 )
        end
	else
        
        --检查状态
        local state,msg = x300813_CheckPlayerState( sceneId,selfId )
        if state == 1 then
            
            BeginQuestEvent(sceneId)
            AddQuestText( sceneId, msg );
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end

        --记录一个RuntimeData
        local nCurX,nCurZ = GetWorldPos( sceneId,selfId )
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,sceneId + 1)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,nCurX)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,nCurZ)
        SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,1)

		NewWorld( sceneId , selfId , newSceneID , PosX , PosZ,300813 )
	end
end

function x300813_DoPlayerRelive( sceneId, selfId )
	
	if GetHp(sceneId,selfId) > 0 then
		return
	end
	
    RestoreHp(sceneId, selfId,0)
	RestoreRage(sceneId, selfId,100)
	ClearMutexState(sceneId, selfId, 6)
	SendReliveResult(sceneId, selfId,1)	

    --清除死亡状态
    RelivePlayerNM(sceneId,selfId,2)	
    SetPlayerMutexState(sceneId,selfId,PLAYER_STATE_DIE,0)
end

--国王战场复活
function x300813_OnPlayerRelive( sceneId, selfId )

    --检查是否是国王战场
    local nScriptId = x300813_GetKingBattleSceneScript( sceneId )
    if nScriptId == 0 then
        return
    end
    
    --检查死亡次数是否超过6次
    local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_KING_BATTLE_BEKILLED )
    if nBeKilled >= 6 then
        
        --再做一次保护
        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
        if KickDown <= 0 or KickDown > 4 then
            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,4) 
        end
        
        return
    end
    
    --执行复活操作
    ClearRageRecoverTick(sceneId, selfId)
	RestoreHp(sceneId, selfId,100)
	RestoreRage(sceneId, selfId,100)
	ClearMutexState(sceneId, selfId, 6)
	SendReliveResult(sceneId, selfId,1)

	--得到玩家所属方，A或B方
    local nGuildId = GetGuildID( sceneId,selfId )
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    if nGuildId == nGuildA then

        x300813_OnKingBattleChangeScene(sceneId,selfId,sceneId,0)
    else
        x300813_OnKingBattleChangeScene(sceneId,selfId,sceneId,1)
    end

end


----------------------------------------------------------------------------------------------
--夺旗场景初始化
----------------------------------------------------------------------------------------------
function x300813_OnBattleSceneReady( sceneId,totalTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --生长点相关初始化
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE,-1 )
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_TIME,10 )

    --设置心跳时间
    --SetKingBattleSceneData_Timer( sceneId,1000 )
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_ITME,totalTime )

end

function x300813_OnBattleSceneClose( sceneId )

    if GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE) == 1 then
        return
    end

    local status = GetKingBattleStatus( sceneId )
	if status == STATE_KING_BATTLE_BATTLE_FINISH then
		x300813_BattleGenResult( sceneId,0 )
	end


end

----------------------------------------------------------------------------------------------
--国王战场场心跳
----------------------------------------------------------------------------------------------
function x300813_OnBattleSceneTimer( sceneId,uTime )

    --相关检测
    ----------------------------------------------------------------------------------------------
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --更新玩家Kick状态
    x300813_UpdatePlayerKickState( sceneId )

    local BattleStatus = GetKingBattleStatus(sceneId)
    if BattleStatus ~= STATE_KING_BATTLE_BATTLE then
        return
    end

    --计时
    ----------------------------------------------------------------------------------------------
    local nTime = GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_ITME ) - 1
    SetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_ITME,nTime )

    --倒计时处理
    ----------------------------------------------------------------------------------------------
    if GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE) == 1 then

	    --倒计时状态
	    local time = GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_DOWN_TIME)
	    if time > 0 then

		    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_TIME,time-1 )

		    local str = format("#G国王战场结束,#R%d秒#G后战场自动关闭",time)

		    LuaThisScenceM2Guild(sceneId,str,GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_A_GUILD),3,1)
		    LuaThisScenceM2Guild(sceneId,str,GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_B_GUILD),3,1)

		else

		    --倒计时结束
	    	SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE,-1 )
            
            --踢掉所有玩家
            x300813_RestoreAllPlayerCamp( sceneId )
	    	x300813_KingBattleKickAllPlayer(sceneId)

		 	--停止心跳
			--SetKingBattleSceneData_Timer(sceneId,0)
			ClearKingBattleSceneData(sceneId)
            
            --记录日志
            local msg = format("KBL:x300813_OnBattleSceneTimer KingBattleFinished,SceneId=%d,LeaveTime h= %d,m=%d",sceneId, floor(nTime/60),mod(nTime,60) )
            WriteLog(1,msg)

	    end

	    return

	end

    --检查是否结束
    ----------------------------------------------------------------------------------------------
    if nTime < 18*60 then
        local bIsFinished = x300813_CheckIsFinished( sceneId)
        if bIsFinished == 1 then
            
            local status = GetKingBattleStatus( sceneId )
            if status == STATE_KING_BATTLE_BATTLE then

                x300813_BattleGenResult( sceneId,1 )
                return
            end

        end
    end
	

    --定时器时间同步
    ----------------------------------------------------------------------------------------------
    --x300813_SyncBattleTimeToAllPlayer( sceneId, nTime )
    x300813_SyncGuildPower( sceneId )

    --小地图上显示帮主
    x300813_UpdateSceneDataFlag( sceneId )

end


----------------------------------------------------------------------------------------------
--检查是否可以结束
----------------------------------------------------------------------------------------------
function x300813_CheckIsFinished( sceneId )

    
    --收集信息
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nGuildA_MemberCount = 0
    local nGuildB_MemberCount = 0


    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA then
                nGuildA_MemberCount = nGuildA_MemberCount + 1
            elseif nGuildId == nGuildB then
                nGuildB_MemberCount = nGuildB_MemberCount + 1
            end
        end
    end

    if nGuildA_MemberCount == 0 and nGuildB_MemberCount == 0 then
        return 1
    end

    --一方无人，则可以结束
    if nGuildA_MemberCount == 0 and nGuildB_MemberCount > 0 then
        return 1
    end

    if nGuildB_MemberCount == 0 and nGuildA_MemberCount > 0 then
        return 1
    end

    return 0

end


----------------------------------------------------------------------------------------------
--得到获胜方：0为A方获胜，1为B方获胜，-1为平手
----------------------------------------------------------------------------------------------
function x300813_GetWinner(sceneId)

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return -1
    end

    --收集信息
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nGuildA_MemberCount = 0
    local nGuildB_MemberCount = 0

    local nGuildA_GuildIn = 0
    local nGuildB_GuildIn = 0

    local nGuildA_GuilderDie = 0
    local nGuildB_GuilderDie = 0

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA then
                nGuildA_MemberCount = nGuildA_MemberCount + 1
            elseif nGuildId == nGuildB then
                nGuildB_MemberCount = nGuildB_MemberCount + 1
            end

            local pos = GetGuildOfficial(sceneId, objId)
	        if pos == x300813_g_Leader_Index then
                if nGuildId == nGuildA then
                    nGuildA_GuildIn = 1
                    nGuildA_GuilderDie = GetPlayerRuntimeData(sceneId,objId,RD_KING_BATTLE_BEKILLED )
                else
                    nGuildB_GuildIn = 1
                    nGuildB_GuilderDie = GetPlayerRuntimeData(sceneId,objId,RD_KING_BATTLE_BEKILLED )
                end
            end
        end
    end


    --胜负判定

    --优先判断只有一个帮主在的赢
    if nGuildA_GuildIn == 1 and nGuildB_GuildIn == 0 then
        return 0
    end

    if nGuildA_GuildIn == 0 and nGuildB_GuildIn == 1 then
        return 1
    end

    --帮主都在或是都不在，再判断人数多的赢
    if nGuildA_MemberCount == 0 and nGuildB_MemberCount > 0 then
        return 1
    end

    if nGuildB_MemberCount == 0 and nGuildA_MemberCount > 0 then
        return 0
    end

    --如果都大于0，则认为人多的一方赢
    if nGuildA_MemberCount > 0 and nGuildB_MemberCount > 0 then
        if nGuildA_MemberCount > nGuildB_MemberCount then
            return 0
        elseif nGuildA_MemberCount < nGuildB_MemberCount then
            return 1
        else
            
            
            if nGuildA_GuildIn == 0 and nGuildB_GuildIn == 0 then
                --人数相同，帮主都不在，国王赢
                return 1            
            elseif nGuildA_GuildIn == 1 and nGuildB_GuildIn == 0 then
                --人数相同，帮主死的次少为赢
                return 0
            elseif nGuildA_GuildIn == 0 and nGuildB_GuildIn == 1 then
                --人数相同，帮主死的次少为赢
                return 1
            else
                --人数相同，帮主死的次少为赢
                if nGuildA_GuilderDie > nGuildB_GuilderDie then
                    return 1

                elseif nGuildA_GuilderDie < nGuildB_GuilderDie then
                    return 0

                --人数相同，帮主死的次数相同，国王方赢
                else
                    return 1
                end
            end
        end
    end

    return 1
end

----------------------------------------------------------------------------------------------
--奖励
----------------------------------------------------------------------------------------------
function x300813_BattleBonus( sceneId,selfId,battleResult )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

end

----------------------------------------------------------------------------------------------
--玩家骑马控制
----------------------------------------------------------------------------------------------
function x300813_KingBattleBonus( sceneId ,battleResult )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            x300813_BattleBonus( sceneId,objId,battleResult)
        end
    end
end


----------------------------------------------------------------------------------------------
--恢复阵营
----------------------------------------------------------------------------------------------
function x300813_RestorePlayerCamp( sceneId,selfId )
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
end

----------------------------------------------------------------------------------------------
--恢复阵营
----------------------------------------------------------------------------------------------
function x300813_RestoreAllPlayerCamp( sceneId )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nCountryId = GetCurCountry( sceneId,objId )
            SetCurCamp(sceneId,objId,nCountryId )
        end
    end
end

----------------------------------------------------------------------------------------------
--生成帮战结果
----------------------------------------------------------------------------------------------
function x300813_BattleGenResult( sceneId, callerId  )
    
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nCountryId = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_COUNTRYID )

    if nGuildA == nGuildB then
        return
    end

    local nWinner = x300813_GetWinner( sceneId )
    if nWinner == 0 then
        --挑战方获取

        local strGuildName = GetGuildName(nGuildA)
        local strGuildLeaderName = GetGuildLeaderName(nGuildA)
        
        local str = format("#G%s帮会获得%s国王战场的胜利，%s坐上了国王的宝座。 ",strGuildName,GetCountryName(nCountryId),strGuildLeaderName)
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)

        SendKingBattleResultToGL( nCountryId,1,nGuildA,nGuildB)

    else
        --国王方获取
        local strGuildName = GetGuildName(nGuildB)
        
        local str = format("#G%s帮会团结一致的顶住了挑战，卫冕了%s国王的宝座。  ",strGuildName,GetCountryName(nCountryId) )
        local nKingGuildID = GetCountryKingGuildIdNM( nCountryId )
        if nKingGuildID < 0 then
        	--没有国王的处理
        	local strGuildLeaderName = GetGuildLeaderName(nGuildB)
        	str = format("#G%s帮会获得%s国王战场的胜利，%s坐上了国王的宝座。 ",strGuildName,GetCountryName(nCountryId),strGuildLeaderName)
        end
        LuaAllScenceM2Wrold(sceneId, str, 2, 1)
        LuaAllScenceM2Wrold(sceneId, str, 3, 1)

        SendKingBattleResultToGL( nCountryId,0,nGuildA,nGuildB)
    end

    --进入倒计时状态,并设置倒计时间
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_STATE,1 )
    SetKingBattleSceneData_Param( sceneId,LD_KING_BATTLE_COUNT_DOWN_TIME,10 )

    local nTime = GetKingBattleSceneData_Param(sceneId,LD_KING_BATTLE_COUNT_ITME )
        
    --记录日志
    local msg = format("KBL:x300813_BattleGenResult SceneId=%d,LeaveTime h= %d,m=%d,CallerId=%d nWinner=%d,GuildA=%d,name=%s,GuildB=%d,name=%s",sceneId, floor(nTime/60),mod(nTime,60), callerId,nWinner,nGuildA,GetGuildName(nGuildA),nGuildB,GetGuildName(nGuildB) )
    WriteLog(1,msg)

    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD,-1 )
    SetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD,-1 )

    x300813_SetAllPlayerNeedKick(sceneId)
    ClearKingBattleSceneData(sceneId)
    
end

----------------------------------------------------------------------------------------------
--踢人
----------------------------------------------------------------------------------------------
function x300813_KingBattleKickPlayer( sceneId,selfId )

    x300813_DoPlayerRelive( sceneId,selfId )

    x300813_RestorePlayerCamp( sceneId,selfId)

    --只要玩家离开战场，将进场景标记置否
    SetPlayerRuntimeData(sceneId,selfId,RD_BATTLESCENE_ENTER_FLAG,0)

    --如果存在BakScene信息，则以BakScene信息为准
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,300813)
        return
    end

    --选择一个合适的场景传送出去
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        
        --楼兰
        local nDestSceneId = 50
        local nPosX = 188
        local nPosZ = 39

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300813)

    elseif nCountry == 1 then
        
        --天山
        local nDestSceneId = 150
        local nPosX = 187
        local nPosZ = 49

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300813)

    elseif nCountry == 2 then

        --昆仑
        local nDestSceneId = 250
        local nPosX = 78
        local nPosZ = 217

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300813)

    elseif nCountry == 3 then
        
        --敦煌
        local nDestSceneId = 350
        local nPosX = 65
        local nPosZ = 209

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300813)

    end
end

----------------------------------------------------------------------------------------------
--踢掉场景里所有的人
----------------------------------------------------------------------------------------------
function x300813_KingBattleKickAllPlayer( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            x300813_KingBattleKickPlayer( sceneId,objId)

        end
    end
end


----------------------------------------------------------------------------------------------
--同步帮战倒计时给全部玩家（当前场景）
----------------------------------------------------------------------------------------------
function x300813_SyncBattleTimeToAllPlayer( sceneId ,nTime )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);                 --先强制关闭

            if nTime > 0 then
                TimerCommand( sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID, nTime, nTime );
            end
        end
    end    
end

----------------------------------------------------------------------------------------------
--同步帮战倒计时关闭信息给全部玩家（当前场景）
----------------------------------------------------------------------------------------------
function x300813_SyncBattleTimeCloseToAllPlayer(sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, GUILDBATTLE_SCRIPTID,-1,-1);                 --先强制关闭
        end
    end    

end

----------------------------------------------------------------------------------------------
--同步帮会势力
----------------------------------------------------------------------------------------------
function x300813_SyncGuildPower( sceneId )
    
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nGuildA_Count = 0
    local nGuildB_Count = 0

    --统计玩家数量，由于不能处理玩家掉线的情况，所以在这里必须主动同步玩家数据
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nGuildId = GetGuildID( sceneId,objId )
            if nGuildId == nGuildA then
                nGuildA_Count = nGuildA_Count + 1
            elseif nGuildId == nGuildB then
                nGuildB_Count = nGuildB_Count + 1
            end
        end
    end

    --同步给玩家
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            SyncKingBattlePowerInfo(sceneId,objId,nGuildA_Count,nGuildB_Count)
        end
    end

end

----------------------------------------------------------------------------------------------
--更新小地图
----------------------------------------------------------------------------------------------
function x300813_UpdateSceneDataFlag( sceneId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    ClearSceneMapDataFlag( sceneId )

	SetSceneMapDataFlag( sceneId,10,8,"斯拉夫联军传送者",47.8,220,-1)
	SetSceneMapDataFlag( sceneId,11,8,"亚洲联军传送者",210.5,30,-1)

    --更新帮主的位置
    local GuildLeaderA = -1
    local GuildLeaderB = -1
    
    local nGuildA = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_A_GUILD )
    local nGuildB = GetKingBattleSceneData_Param( sceneId, LD_KING_BATTLE_B_GUILD )

    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            local pos = GetGuildOfficial(sceneId, objId)
	        if pos == x300813_g_Leader_Index then
                local nGuild = GetGuildID( sceneId,objId )
                if nGuild == nGuildA then
                    GuildLeaderA = objId
                elseif nGuild == nGuildB then
                    GuildLeaderB = objId
                end
            end
        end
    end


    local a_leader_name = ""
    local a_leader_x = 0
    local a_leader_z = 0
    
    if GuildLeaderA > 0 then
        
        a_leader_name = GetName(sceneId,GuildLeaderA)
        a_leader_x,a_leader_z = GetWorldPos(sceneId,GuildLeaderA)
    end

    local b_leader_name = ""
    local b_leader_x = 0
    local b_leader_z = 0
    
    if GuildLeaderB > 0 then

        b_leader_name = GetName(sceneId,GuildLeaderB)
        b_leader_x,b_leader_z = GetWorldPos(sceneId,GuildLeaderB)
    end

    --发送帮主状态
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            if GuildLeaderA > 0 and GuildLeaderA ~= objId then
                SetSceneMapDataFlagToPlayer( sceneId,objId,12,8,a_leader_name,a_leader_x,a_leader_z,-1)
            end

            if GuildLeaderB > 0 and GuildLeaderB ~= objId then
                SetSceneMapDataFlagToPlayer( sceneId,objId,13,8,b_leader_name,b_leader_x,b_leader_z,-1)
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--进入战场错误的报告
----------------------------------------------------------------------------------------------
--function x300813_OnKingEnterError( sceneId,selfId,nErrorId )
--    
--    if nErrorId == 0 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"只有参加帮会之后才能进入！",name,3,1)
--
--    elseif nErrorId == 1 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"您的帮会没有报名！",name,3,1)
--
--    elseif nErrorId == 2 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"国王战场还没到开放时间！",name,3,1)
--
--    elseif nErrorId == 3 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"国王战场已经关闭入口（超过两分钟）",name,3,1)
--
--    elseif nErrorId == 4 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"目前没有国王战场开始",name,3,1)
--
--    elseif nErrorId == 5 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"战场人数已满",name,3,1)
--
--    elseif nErrorId == 6 then
--        
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"你已经进入过战场，不能重复进入！",name,3,1)
--
--    else
--        local name = GetName(sceneId,selfId )
--        LuaScenceM2Player( sceneId,selfId,"未知错误，不能进入！",name,3,1)
--    end
--
--end


----------------------------------------------------------------------------------------------
--从GLServer过来的同步国王战场时间的东东
----------------------------------------------------------------------------------------------
function x300813_OnSyncKingBattleTime( sceneId,nTime )
    
    if x300813_GetKingBattleSceneScript( sceneId ) == 0 then
        return
    end

    local nTime_new = x300813_g_TotalBattleTime - NumberCastIntToUInt( nTime )
    SetKingBattleSceneData_Param(sceneId, LD_KING_BATTLE_COUNT_ITME, nTime_new )

    --定时器时间同步
    ----------------------------------------------------------------------------------------------
    x300813_SyncBattleTimeToAllPlayer( sceneId, nTime_new )
end

----------------------------------------------------------------------------------------------
--设置所有玩家需要踢掉
----------------------------------------------------------------------------------------------
function x300813_SetAllPlayerNeedKick( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > x300813_g_Kick_Down then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,x300813_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--更新玩家踢掉状态
----------------------------------------------------------------------------------------------
function x300813_UpdatePlayerKickState( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown > 0 then                
                KickDown = KickDown - 1 
                if KickDown == 0 then
                    --倒计时为零，踢掉
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,-1) 
                    x300813_KingBattleKickPlayer( sceneId,objId )                    
                else
                    --否则，继续倒计时
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end