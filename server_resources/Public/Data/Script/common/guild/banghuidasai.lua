
x300643_g_ScriptId                      = 300643
x300643_g_TotalBattleTime               = 60 * 20     	--战争持续时间1200秒        19:00-19:20

--玩法类型
x300643_g_SceneName                     = "zhanchang_banghuizhanchang/zhanchang_banghuizhanchang.scn"
x300643_g_MatchOdd                      = "#R您所在的帮会在本次帮会战中轮空！"

x300643_g_Guild_Signup                  = 3     --报名
x300643_g_Guild_WaitBattle              = 4     --报名结束，等待帮战
x300643_g_Guild_BeginBattle             = 5     --开始帮战
x300643_g_Guild_EndBattle               = 6     --结束帮战

--奖励相关
x300643_g_MaxScore                      = 99	            
x300643_g_BonusTips                     = "#G您获得了#R%d#G点经验,#R%d#G点帮会贡献,#R%d#G点帮会经验,#R%d#G点帮会使命点,#R%d#G两帮会金钱!"
x300643_g_BonusTips1                    = "您获得了奖励"

--经验奖励
x300643_g_WinPrise                      = 1000*0.5*20              --获胜方经验奖励系数，只与等级有关
x300643_g_LosePrise                     = 1000*0.1*20              --失败方经验奖励系数，只与等级有关
x300643_g_DeucePrise                    = 1000*0.3*20              --战平时经验奖励系数，只与等级有关

--帮贡奖励
x300643_g_WinBangGong                   = 150
x300643_g_LoseBangGong                  = 50
x300643_g_DeuceBangGong                 = 100

--帮会经验
x300643_g_WinBangExp                    = 5
x300643_g_LoseBangExp                   = 5
x300643_g_DeuceBangExp                  = 5

--帮会使命点
x300643_g_WinBangshiming                = 2
x300643_g_LoseBangshiming               = 2
x300643_g_DeuceBangshiming              = 2

--帮会金钱
x300643_g_WinBangjinqian                = 40000
x300643_g_LoseBangjinqian               = 20000
x300643_g_DeuceBangjinqian              = 20000

--帮会功德
x300643_g_WinBanggongde                 = 20
x300643_g_LoseBanggongde                = 15
x300643_g_DeuceBanggongde               = 10

--帮会战中双方阵营
x300643_g_Guild_Camp_A                  = 5
x300643_g_Guild_Camp_B                  = 6

x300643_g_Kick_Down                     = 8

--帮会护兽生长点信息
x300643_g_ConvoyGrowPointState			= {}
x300643_g_ConvoyGrowPointType			= {}
x300643_g_ConvoyGrowPointPosList		= {{40,125},{30,39},{33,219},{93,46},{93,214},{125,98},{125,150},{161,44},{161,219},{213,218},{216,40},{205,122}}

--内部积分相关
x300643_g_ScoreIntervalA				= {}
x300643_g_ScoreIntervalB				= {}

x300643_g_BattleFlagA    				= {type=9771, x=202, z=122.6, ai=7, guid=150031, facedir=0, title=""}		--战旗A
x300643_g_BattleFlagB    				= {type=9770, x=48,  z=127.1, ai=7, guid=150030, facedir=0, title=""}		--战旗B


function x300643_ProcEventEntry(sceneId, selfId, NPCId, scriptid, index)	--点击该任务后执行此脚本
end

----------------------------------------------------------------------------------------------
--多场景处理
----------------------------------------------------------------------------------------------
function x300643_OnMapInit(sceneId)
	
	x300643_g_ConvoyGrowPointState[sceneId]			= 0
	x300643_g_ConvoyGrowPointType[sceneId]			= 114
	

	--内部积分相关
	x300643_g_ScoreIntervalA[sceneId]				= 0
	x300643_g_ScoreIntervalB[sceneId]				= 0
	
end

----------------------------------------------------------------------------------------------
--检查是否是帮战场景，如果不是返回0，是返回1
----------------------------------------------------------------------------------------------
function x300643_IsGuildBattleScene_Gjs( sceneId )

    local name = GetBattleSceneName(sceneId)
    if name == x300643_g_SceneName then
        return 1
    end

    return 0
end


----------------------------------------------------------------------------------------------
--活动触发
----------------------------------------------------------------------------------------------
function x300643_OnBattleStateEvent( sceneId, state  )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

	local sceneType = GetSceneType(sceneId);
	if sceneType == 0 then --场景类型是普通场景

        if state == x300643_g_Guild_Signup then

            --检查状态是否已经置过
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_SIGNUP then
                
                --记录日志
                local msg = format("GBL:STATE_GUILD_BATTLE_SIGNUP,SceneId=%d ",sceneId  )
                WriteLog(1,msg)

            end
            
            --开始报名
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_SIGNUP)
            
        elseif state == x300643_g_Guild_WaitBattle then

            --检查状态是否已经置过
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_SIGNUP_FINISH then
                
                --记录日志
                local msg = format("GBL:STATE_GUILD_BATTLE_SIGNUP_FINISH,SceneId=%d ",sceneId )
                WriteLog(1,msg)

            end
            
            --报名结束
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_SIGNUP_FINISH)
            
        elseif state == x300643_g_Guild_BeginBattle then

            --检查状态是否已经置过
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus == STATE_GUILD_BATTLE_BATTLE then
                
                --记录日志
                local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE,SceneId=%d ",sceneId )
                WriteLog(1,msg)

            end
            
            --开始帮战
		    SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE)

        elseif state == x300643_g_Guild_EndBattle then
            
            --帮战结束
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE_FINISH)

            --记录日志
            local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d",sceneId )
            WriteLog(1,msg)

        end

	elseif sceneType == 2 then --场景类型是帮会战场景
        
        --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
        local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
        if  bBattleScene_Gjs == 0 then
            return
        end

        if state == x300643_g_Guild_Signup then

            --检查状态是否已经置过
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_READY then
                
                --记录日志
                local msg = format("GBL:STATE_GUILD_BATTLE_SIGNUP,SceneId=%d,2 ",sceneId  )
                WriteLog(1,msg)

            end

            GuildBattleAskInit( sceneId )                                               --向GLServer注册一下
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_READY)                      --设置状态


            --设置基本数据
            SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_SCRIPT,GUILDBATTLE_SCRIPTID)

        elseif state == x300643_g_Guild_WaitBattle then

            --检查状态是否已经置过
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_SIGNUP_FINISH then
                
                --记录日志
                local msg = format("GBL:STATE_GUILD_BATTLE_SIGNUP_FINISH,SceneId=%d,2",sceneId )
                WriteLog(1,msg)

            end

            --设置基本数据
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_SIGNUP_FINISH)
            SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_SCRIPT,GUILDBATTLE_SCRIPTID)

        elseif state == x300643_g_Guild_BeginBattle then

            --检查状态是否已经置过
            local selfStatus = GetGuildBattleStatus(sceneId)
            if selfStatus ~= STATE_GUILD_BATTLE_BATTLE then
                
                --记录日志
                local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE,SceneId=%d,2",sceneId )
                WriteLog(1,msg)

            end

            --设置基本数据            
            SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE)                     --设置开始帮战
            SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_SCRIPT,GUILDBATTLE_SCRIPTID)

            x300643_OnBattleSceneReady( sceneId,( x300643_g_TotalBattleTime ) )

        elseif state == x300643_g_Guild_EndBattle then

            local nState = GetGuildBattleStatus( sceneId )
            if nState > STATE_GUILD_BATTLE_BATTLE or nState < STATE_GUILD_BATTLE_READY then
                
                --记录日志
                local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE_FINISH,Result:nState > STATE_GUILD_BATTLE_BATTLE or nState < STATE_GUILD_BATTLE_READY  SceneId=%d,state=%d,2",sceneId, nState )
                WriteLog(1,msg)

                --根据玩法的脚本的不同，进行相关初始化回调
                x300643_OnBattleSceneClose(sceneId )

                --记录日志
                local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
                WriteLog(1,msg)
                return
            end

            --设置状态，活动结束
    		SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE_FINISH)
            x300643_OnBattleSceneClose( sceneId )

            --记录日志
            local msg = format("GBL:STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
            WriteLog(1,msg)
        end
	end
end

----------------------------------------------------------------------------------------------
--帮会战场心跳
----------------------------------------------------------------------------------------------
function x300643_ProcTiming( sceneId,uTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end
       
    x300643_OnBattleSceneTimer( sceneId, uTime )
end


----------------------------------------------------------------------------------------------
--玩家进入事件
----------------------------------------------------------------------------------------------
function x300643_OnPlayerEnter( sceneId, playerId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    local status = GetGuildBattleStatus( sceneId )
    if status ~= STATE_GUILD_BATTLE_BATTLE then

        x300643_SetAllPlayerNeedKick( sceneId,x300643_g_Kick_Down )
        --记录日志
        local msg = format("GBL:x300643_OnBattlePlayerEnter Kick,Player,SceneId=%d,playerId=%d status=%d",sceneId,playerId,status )
        WriteLog(1,msg)
        return
    end

    --取得帮会A和帮会B
    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,playerId )

    --设置在战场中的阵营属性
    local nSendCCamp = -1
    if nGuildId == nGuildA then
        nSendCCamp = 0
    elseif nGuildId == nGuildB then
        nSendCCamp = 1
    else

        SetPlayerRuntimeData( sceneId,playerId,RD_BATTLE_SCENE_KICK_DOWN ,x300643_g_Kick_Down) 
        --记录日志
        local name = GetName(sceneId,playerId)
        if name == nil then
            name = "<ErrorName>"
        end
        local msg = format("GBL:x300643_OnBattlePlayerEnter Kick 2,Player,SceneId=%d,playerId=%d,name=%s,guild=%d,guildA=%d,guildB=%d",sceneId, playerId,name, nGuildId, nGuildA, nGuildB )
        WriteLog(1,msg)
        return

    end

    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_REFRESH_MAP,1)

    --积分栏设定
    SetGuildBattleDisable(sceneId, playerId, 0,nSendCCamp )
    
    --发送帮战配对信息
    local strGuildA_name = GetGuildName(nGuildA)
    local strGuildB_name = GetGuildName(nGuildB)
    SendGuildBattleMatchInfo(sceneId,playerId,strGuildA_name,strGuildB_name)

    --玩家进入战场，则清空之前的数据
    SetPlayerRuntimeData(sceneId,playerId,RD_GUILDBATTLE_BEKILLED,0)
    SetPlayerRuntimeData(sceneId,playerId,RD_GUILDBATTLE_KILLEDOTHER,0)
    SetPlayerRuntimeData(sceneId,playerId,RD_GUILDBATTLE_GETFLAG,0)

    --设置阵营
    if nGuildId == nGuildA then
        SetCurCamp(sceneId,playerId,x300643_g_Guild_Camp_A)
        SetPos(sceneId,playerId,234,126)
    elseif nGuildId == nGuildB then
        SetCurCamp(sceneId,playerId,x300643_g_Guild_Camp_B)
        SetPos(sceneId,playerId,21,126)
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
function x300643_OnPlayerLeave( sceneId, playerId )
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    local nCountryId = GetCurCountry(sceneId,playerId )
    SetCurCamp( sceneId,playerId,nCountryId )

    SetGuildBattleDisable(sceneId, playerId,1,0)

    --如果是夺旗玩家，删除夺旗BUF,并重生旗子
    local owner = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER)
    if owner == playerId then
        CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_DEC_SPEED_BUF )
        CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_INC_DEFENCE_BUF )
        --CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_FLAG_BUF )
        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )

        local x,y = GetWorldPos(sceneId, playerId)
        --重设旗子重生坐标
        SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,x,y)
        --重设旗子重生时间
        SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1)
    end
end

----------------------------------------------------------------------------------------------
--玩家退会
----------------------------------------------------------------------------------------------
function x300643_OnPlayerLeaveGuild( sceneId,selfId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end
    
    --如果是夺旗玩家，删除夺旗BUF,并重生旗子
    local owner = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER)
    if owner == selfId then
        CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_DEC_SPEED_BUF )
        CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_INC_DEFENCE_BUF )
        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )

        local x,y = GetWorldPos(sceneId, selfId)
        --重设旗子重生坐标
        SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,x,y)
        --重设旗子重生时间
        SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1)
    end
    
    x300643_GuildBattleKickPlayer( sceneId,selfId )
    SetGuildBattleDisable(sceneId, selfId,1,0)

end

----------------------------------------------------------------------------------------------
--玩家死亡事件
----------------------------------------------------------------------------------------------
function x300643_OnPlayerDie( sceneId, selfId, killerId  )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
    if IsHaveFlag ~= 0 then

        --死亡玩家身上有旗
        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )
        CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
        CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_INC_DEFENCE_BUF )

        local ObjType = GetObjType(sceneId, killerId)

        --杀人者在线并且是玩家,并且没有死亡,并且在30码内,则认为有效,否则掉地上
        if IsPlayerStateNormal( sceneId,killerId ) == 1 and IsPlayerMutexState(sceneId,killerId,PLAYER_STATE_DIE) ~= 1 and GetDist(sceneId,selfId,killerId,30) <= 30  then
            SendSpecificImpactToUnit(sceneId, killerId,killerId,killerId,LD_GUILD_BATTLE_DEC_SPEED_BUF,0)
            SendSpecificImpactToUnit(sceneId, killerId,killerId,killerId,LD_GUILD_BATTLE_INC_DEFENCE_BUF,0)

            SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,killerId )  --记录旗子主人
            ReCallHorse( sceneId, killerId )--强制下马

            local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
            local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

            local nGuildId = GetGuildID( sceneId,killerId )

            --设置在战场中的阵营属性
            local nFlag = -1
            if nGuildId == nGuildA then
                nFlag = 0
            elseif nGuildId == nGuildB then
                nFlag = 1
            end

            --给出相应提示
            if nFlag == 0 then
                
                LuaThisScenceM2Wrold(sceneId,"蓝方夺取了战旗",2,1)
                LuaThisScenceM2Wrold(sceneId,"蓝方夺取了战旗",3,1)

            elseif nFlag == 1 then
                
                LuaThisScenceM2Wrold(sceneId,"红方夺取了战旗",2,1)
                LuaThisScenceM2Wrold(sceneId,"红方夺取了战旗",3,1)
            end
        
        --杀人者不在线或是已死亡或者非玩家
        else

            local x,y = GetWorldPos( sceneId, selfId )
            SetGrowPointPos( sceneId, LD_GUILD_BATTLE_FLAG_GROW_POINT, x+1, y+1)
            SetGrowPointIntervalContainer( sceneId, LD_GUILD_BATTLE_FLAG_GROW_POINT, 1000 )
            SetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_FLAG_OWNER, -1 )

            x300643_UpdateSceneDataFlag( sceneId, 7 )
        end
    end

   --记录杀敌次数
   local nKilledOther = GetPlayerRuntimeData( sceneId, killerId, RD_GUILDBATTLE_KILLEDOTHER ) + 1
   SetPlayerRuntimeData( sceneId, killerId, RD_GUILDBATTLE_KILLEDOTHER, nKilledOther )

   --记录被杀次数
   local nBeKilled = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED ) + 1
   SetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED,nBeKilled)

end


----------------------------------------------------------------------------------------------
--帮会战复活操作
----------------------------------------------------------------------------------------------
function x300643_OnPlayerRelive( sceneId, selfId )

    --检查是否是帮会战
    local bBattleScene = x300643_IsGuildBattleScene_Gjs( sceneId )
    if bBattleScene == 0 then
        return
    end
    
    --如果玩家在帮战未开始或是帮战结束时因为某种原因死亡，那么不让其复活，并且踢人
    local status = GetGuildBattleStatus( sceneId )
	if status ~= STATE_GUILD_BATTLE_BATTLE then
        
        local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
        if KickDown <= 0 or KickDown > 8 then                
            SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,8 ) 
        end
        
        return
    end

    --得到玩家所属方，A或B方
    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --设置在战场中的阵营属性
    local flag = -1
    if nGuildId == nGuildA then
        flag = 0
    elseif nGuildId == nGuildB then
        flag = 1
    end
    
    --调用这个脚本接口实现传送
    CallScriptFunction(800021,"OnGuildBattleChangeScene",sceneId,selfId,sceneId,flag)

end

----------------------------------------------------------------------------------------------
--配队失败的操作
----------------------------------------------------------------------------------------------
function x300643_OnGuildBattleMatchOdd( sceneId, playerId )

    local name = GetName(sceneId,playerId)
    LuaScenceM2Player(sceneId,  playerId, x300643_g_MatchOdd, name , 2,1)
    LuaScenceM2Player(sceneId,  playerId, x300643_g_MatchOdd, name , 3,1)
end

----------------------------------------------------------------------------------------------
--骑马相关的处理
----------------------------------------------------------------------------------------------
function x300643_OnRideHorse( sceneId,selfId )
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 1
    end

    --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return 1
    end

    --有旗不能骑马
    local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
    if IsHaveFlag ~= 0 then
        return 0
    end

    --无旗，可骑马
    return 1
end

----------------------------------------------------------------------------------------------
--设置帮战相关配对信息
----------------------------------------------------------------------------------------------
function x300643_OnSetGuildBattleMatchInfo( sceneId,nGuildA,nGuildB )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD, nGuildA )
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD, nGuildB )

    --debug
    local a = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD )
    local b = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD )

    local msg = format( "GBL:GUILD_BATTLE_MATCHINFO:sceneId=%d,A=%d,B=%d",sceneId,a,b )
    WriteLog(1,msg)
end

----------------------------------------------------------------------------------------------
--玩家重新上线
----------------------------------------------------------------------------------------------
function x300643_OnPlayerNewConnectEnter( sceneId,selfId )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    AskGuildBattleEnter(sceneId,selfId)

end

function x300643_OnPlayerAskLeave( sceneId,selfId )
    
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return 
    end

    --检查是否是帮战场景列表中所处理的情况，如果不是，则不处理
    local bBattleScene_Gjs = x300643_IsGuildBattleScene_Gjs( sceneId )
    if  bBattleScene_Gjs == 0 then
        return
    end

    x300643_OnPlayerAskLeaveGuildBattle( sceneId, selfId )

end

function x300643_OnDie(sceneId, selfId, killerId)
	if selfId == GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_A_ID) then
	
		SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE,200)
    	SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE_FINISH)
        x300643_OnBattleSceneClose( sceneId )
        local msg = format("GBL:FLAG A DIE, STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
        WriteLog(1,msg)
	elseif selfId == GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_B_ID) then
		SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE,200)
		SetGuildBattleStatus(sceneId,STATE_GUILD_BATTLE_BATTLE_FINISH)
        x300643_OnBattleSceneClose( sceneId )
     
        local msg = format("GBL:FLAG B DIE, STATE_GUILD_BATTLE_BATTLE_FINISH, SceneId=%d,2",sceneId )
        WriteLog(1,msg)
	end
end
--创建战旗
function x300643_CreateBattleFlags( sceneId )

	local FlagAID,FlagBID
 	if x300643_g_BattleFlagA.title~="" then
		FlagAID = CreateMonster(sceneId, x300643_g_BattleFlagA.type, x300643_g_BattleFlagA.x, x300643_g_BattleFlagA.z, x300643_g_BattleFlagA.ai, 0, x300643_g_ScriptId, x300643_g_BattleFlagA.guid, x300643_g_Guild_Camp_A,-1,x300643_g_BattleFlagA.facedir,  "", x300643_g_BattleFlagA.title)
		
	else
		FlagAID = CreateMonster(sceneId, x300643_g_BattleFlagA.type, x300643_g_BattleFlagA.x, x300643_g_BattleFlagA.z, x300643_g_BattleFlagA.ai, 0, x300643_g_ScriptId, x300643_g_BattleFlagA.guid, x300643_g_Guild_Camp_A,-1,x300643_g_BattleFlagA.facedir)
	end
	SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_A_ID, FlagAID)
	if x300643_g_BattleFlagB.title~="" then
		FlagBID = CreateMonster(sceneId, x300643_g_BattleFlagB.type, x300643_g_BattleFlagB.x, x300643_g_BattleFlagB.z, x300643_g_BattleFlagB.ai, 0, x300643_g_ScriptId, x300643_g_BattleFlagB.guid, x300643_g_Guild_Camp_B,-1,x300643_g_BattleFlagB.facedir,  "", x300643_g_BattleFlagB.title)
	else
		FlagBID = CreateMonster(sceneId, x300643_g_BattleFlagB.type, x300643_g_BattleFlagB.x, x300643_g_BattleFlagB.z, x300643_g_BattleFlagB.ai, 0, x300643_g_ScriptId, x300643_g_BattleFlagB.guid, x300643_g_Guild_Camp_B,-1,x300643_g_BattleFlagB.facedir)
	end
	SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_B_ID, FlagBID)
	
end

--删除旗子
function x300643_DestroyBattleFlags( sceneId )
	
	local FlagAID = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_A_ID)
	local FlagBID = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_B_ID)
	
	if IsObjValid(sceneId,FlagAID) == 1 and GetHp(sceneId,FlagAID) > 0 then
		DeleteMonster(sceneId,FlagAID)
	end
	
	if IsObjValid(sceneId,FlagBID) == 1 and GetHp(sceneId,FlagBID) > 0 then
		DeleteMonster(sceneId,FlagBID)
	end
	
end

function x300643_OnBattleSceneReady( sceneId,totalTime )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    --生长点相关初始化
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_GUILD,-1)
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN2_GUILD,-1)
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN3_GUILD,-1)
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN4_GUILD,-1)
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1)

    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE,-1 )
    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME,10 )

    --旗子相关设置
    SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1)

    RecycleGrowPointByType( sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,2000)
    SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y)

    --仓库的位置一定固定
    SetSceneMapDataFlag( sceneId,5,1,"仓库",219,122.6,-1)
    SetSceneMapDataFlag( sceneId,6,2,"仓库",34, 127.1,-1)

    --设置刷新地图
    SetGuildBattleSceneData_Param(sceneId, LD_GUILD_BATTLE_REFRESH_MAP,1)

    --设置心跳时间
    --SetGuildBattleSceneData_Timer( sceneId,1000 )
    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,-1 )

    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_ITME,totalTime )
    
    --重置生长点
    x300643_g_ConvoyGrowPointState[sceneId] = 0
    x300643_ResetConvoyGrowPoint(sceneId,0)
    
    --重置内部积分
    x300643_g_ScoreIntervalA[sceneId] = 0
	x300643_g_ScoreIntervalB[sceneId] = 0
	
	--创建双方战旗
	x300643_CreateBattleFlags(sceneId)
end

function x300643_OnBattleSceneClose( sceneId )

    if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE) == 1 then
        return
    end

    local status = GetGuildBattleStatus( sceneId )
	if status == STATE_GUILD_BATTLE_BATTLE_FINISH then
		x300643_BattleGenResult( sceneId,0 )
        SendGuildBattleFinishedToGL( sceneId )
	end
end

function x300643_GetBattleState( sceneId )
    
    local down_state = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE)
    local down_time  = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME)

    if down_state == -1  and down_time <= 0 then
        return 0
    end

    return 1

end

function x300643_GetBattleDownState( sceneId )
    
    local down_state = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE)

    if down_state == 1 then
        return 0
    end

    return 1

end

function x300643_CheckBattleState( sceneId )
    
    if x300643_GetBattleState(sceneId) == 0 then
        return 0
    end

    if x300643_GetBattleDownState(sceneId) == 0 then
        return 0
    end

    return 1

end

----------------------------------------------------------------------------------------------
--帮会战场心跳
----------------------------------------------------------------------------------------------
function x300643_OnBattleSceneTimer( sceneId,uTime )

    --相关检测
    ----------------------------------------------------------------------------------------------
    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    x300643_UpdatePlayerKickState( sceneId )


    local status = GetGuildBattleStatus( sceneId )
	if status ~= STATE_GUILD_BATTLE_BATTLE then
        return
    end
    
    
    if x300643_g_ConvoyGrowPointState[sceneId] == 0 then
    	
		x300643_ResetConvoyGrowPoint(sceneId,1)    	
		x300643_g_ConvoyGrowPointState[sceneId] = 1
    end


    --计时
    ----------------------------------------------------------------------------------------------
    local nTime = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_ITME ) - 1
    SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_ITME,nTime )

    --倒计时处理
    ----------------------------------------------------------------------------------------------
    if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE) == 1 then

	    --倒计时状态
	    local time = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME)
	    if time > 0 then

		    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME,time-1 )

		else

		    --倒计时结束
	    	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE,-1 )
            
            --踢掉所有玩家
            x300643_RestoreAllPlayerCamp( sceneId )
	    	x300643_GuildBattleKickAllPlayer(sceneId)

		 	--停止心跳
			--SetGuildBattleSceneData_Timer(sceneId,0)
			ClearGuildBattleSceneData(sceneId)
            
            --记录日志
            local msg = format("GBL:x300643_OnBattleSceneTimer GuildBattleFinished,SceneId=%d,LeaveTime m= %d,s=%d",sceneId, floor(nTime/60),mod(nTime,60) )
            WriteLog(1,msg)

	    end

	    return

	end

    --帮战不能继续的时候，停止
    if x300643_GetBattleState( sceneId) == 0 then
        return
    end

    --检查是否结束
    ----------------------------------------------------------------------------------------------
	local status = GetGuildBattleStatus( sceneId )
	if status == STATE_GUILD_BATTLE_BATTLE_FINISH then

		x300643_BattleGenResult( sceneId,1 )
        SendGuildBattleFinishedToGL( sceneId )
        -- 给所有战场的玩家增加活跃度
        x300643_AddActivity( sceneId)
		return
	end

    --刷新小地图
    ----------------------------------------------------------------------------------------------
    local nRefresh =  GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_REFRESH_MAP)
    if nRefresh == 1 then

        SetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_REFRESH_MAP,0)
        
        for i=1,13 do
        	x300643_UpdateSceneDataFlag( sceneId,i )
        end

    end

    --如果旗子在人身上，每秒刷新一次
    ----------------------------------------------------------------------------------------------
    local owner = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER)
    if owner ~= -1 then
        x300643_UpdateSceneDataFlag( sceneId,7 )
    end


    --粮仓计分处理
    ----------------------------------------------------------------------------------------------
    x300643_UpdateBarnScore(sceneId,0)	 --粮仓1自动加分
    x300643_UpdateBarnScore(sceneId,1)	 --粮仓2自动加分
    x300643_UpdateBarnScore(sceneId,2)	 --粮仓3自动加分
    x300643_UpdateBarnScore(sceneId,3)	 --粮仓4自动加分

    --广播最新积分
    ----------------------------------------------------------------------------------------------
    local FlagNumA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_FLAG_NUM)
    local FlagNumB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_FLAG_NUM)

    BroadcastGuildBattleScore(sceneId, 0,GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE)+1,FlagNumA+1 )
    BroadcastGuildBattleScore(sceneId, 1,GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE)+1,FlagNumB+1 )

    --旗子相关更新
    ----------------------------------------------------------------------------------------------
    local FlagTime = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_TIME)

    if FlagTime > 0 then

        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,FlagTime-1 )     --重设旗子有效时间
        FlagTime = FlagTime - 1
        if FlagTime <= 0 then       --时间到旗子自动消失

            --删除夺旗者BUF
            CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_DEC_SPEED_BUF )
            CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_INC_DEFENCE_BUF )
            --CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_FLAG_BUF )

            SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,-1 )
            SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )

            --回收生长点
            RecycleGrowPointByType( sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,2000)
            SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y)

            --重设旗子位置与重生时间
            --SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1)

            x300643_UpdateSceneDataFlag( sceneId,7 )

        end
    end

    --判断夺旗次数，决定帮战是会提前结束
    ----------------------------------------------------------------------------------------------
    local IsFinished = 0

    local ScoreA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE)
    local ScoreB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE)

    if ScoreA >= x300643_g_MaxScore  or ScoreB>=x300643_g_MaxScore  then

        --帮会战提前结束
        IsFinished = 1

    end

    if IsFinished == 1 then

        x300643_BattleGenResult( sceneId,2 )
        SendGuildBattleFinishedToGL( sceneId )
        return
    end
    
    
    --同步双方势力信息
    ----------------------------------------------------------------------------------------------
    x300643_SyncGuildPower(sceneId )

end

-- 给所有战场的玩家增加活跃度
function x300643_AddActivity( sceneId)
    local nHumanCount = GetScenePlayerCount( sceneId)
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId, i)
        if objId >= 0 then
            -- 增加活跃度
            local id = GetGuildID( sceneId, objId)
            if id ~= -1 then
                AddGuildActivity( sceneId, objId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM8) )
            end
        end
    end
end


----------------------------------------------------------------------------------------------
--得到获胜方：0为A方获胜，1为B方获胜，-1为平手
----------------------------------------------------------------------------------------------
function x300643_GetWinner(sceneId)

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return -1
    end

    --如果都没有拿到三个旗子，看看有没有人到50分
    local ScoreA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE)
    local ScoreB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE)

    if ScoreA > ScoreB then
        return 0
    elseif ScoreA < ScoreB then
        return 1
    else
        return 2
    end

    return 2

end


----------------------------------------------------------------------------------------------
--玩法1：粮仓自动加分
--粮仓编号
----------------------------------------------------------------------------------------------
function x300643_UpdateBarnScore(sceneId,BarnNum)

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

	local Guild1 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_GUILD)
	local Guild2 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN2_GUILD)
	local Guild3 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN3_GUILD)
	local Guild4 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN4_GUILD)

    local Guild = Guild1
    if BarnNum == 0 then
        Guild = Guild1
    elseif BarnNum == 1 then
        Guild = Guild2
    elseif BarnNum == 2 then
        Guild = Guild3
    elseif BarnNum == 3 then
        Guild = Guild4
    end


 	local ScoreA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE)
	local ScoreB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE)

    local GuildA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
    local GuildB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)

	local OldTime = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_TIME + BarnNum)
  	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_TIME + BarnNum,OldTime+1)

	--每10秒粮仓自动加分和战场资源点
	
	local ResPointA = x300643_g_ScoreIntervalA[sceneId]
	local ResPointB = x300643_g_ScoreIntervalB[sceneId]
	if OldTime >= 10 then
		if Guild1 == Guild2 and Guild1 == Guild3 and Guild1 == Guild4 then
			if GuildA >= 0 and GuildA == Guild1 then 		--是A方
				SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,ScoreA+4) 
				x300643_g_ScoreIntervalA[sceneId] = x300643_g_ScoreIntervalA[sceneId] + 8
				BroadcastGuildBattleResourceScore(sceneId, 0,x300643_g_ScoreIntervalA[sceneId] )
			elseif GuildB >= 0 and GuildB == Guild1 then 	--是B方
                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,ScoreB+4)
                x300643_g_ScoreIntervalB[sceneId] = x300643_g_ScoreIntervalB[sceneId] + 8
                BroadcastGuildBattleResourceScore(sceneId, 1,x300643_g_ScoreIntervalB[sceneId] )
            end
            
        else

			if GuildA >= 0 and GuildA == Guild then 		--是A方
                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,ScoreA+1)
                x300643_g_ScoreIntervalA[sceneId] = x300643_g_ScoreIntervalA[sceneId] + 1
                BroadcastGuildBattleResourceScore(sceneId, 0,x300643_g_ScoreIntervalA[sceneId] )
            elseif GuildB >= 0 and GuildB == Guild then 	--是B方
                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,ScoreB+1)
                x300643_g_ScoreIntervalB[sceneId] = x300643_g_ScoreIntervalB[sceneId] + 1
                BroadcastGuildBattleResourceScore(sceneId, 1,x300643_g_ScoreIntervalB[sceneId] )
			end
		end
		
		--print("x300643_UpdateBarnScoreA",x300643_g_ScoreIntervalA[sceneId],x300643_g_ScoreIntervalA[sceneId])
		--重设被占领时间
		SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_TIME + BarnNum,-1 )
	end
	
    --每60秒粮仓自动加分
--	if OldTime >= 60 then
--
--		if Guild1 == Guild2 and Guild1 == Guild3 and Guild1 == Guild4 then
--
--			if GuildA >= 0 and GuildA == Guild1 then 		--是A方
--
--                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,ScoreA+2)
--
--			elseif GuildB >= 0 and GuildB == Guild1 then 	--是B方
--
--                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,ScoreB+2)
--
--            end
--
--		else
--
--			if GuildA >= 0 and GuildA == Guild then 		--是A方
--
--                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,ScoreA+1)
--
--            elseif GuildB >= 0 and GuildB == Guild then 	--是B方
--
--                SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,ScoreB+1)
--			end
--
--		end
--
--		--重设被占领时间
--		SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_TIME + BarnNum,-1 )
--	end

    --设置总分不要超过上限
  	if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE) > x300643_g_MaxScore  then
  	   SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_SOCRE,x300643_g_MaxScore)
  	end

  	if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE) > x300643_g_MaxScore  then
  	   SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_B_SOCRE,x300643_g_MaxScore)
  	end
end

----------------------------------------------------------------------------------------------
--更新小地图
----------------------------------------------------------------------------------------------
function x300643_UpdateSceneDataFlag( sceneId,idx )

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end


    --取得粮仓点相关数据
    local Guild1 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_GUILD)
    local Guild2 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN2_GUILD)
    local Guild3 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN3_GUILD)
    local Guild4 = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN4_GUILD)

    local GuidA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
    local GuidB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)

    --粮仓1
    if idx == 1 then
        if Guild1 < 0 then
            SetSceneMapDataFlag( sceneId,1,0,"粮仓",19,32,-1)
        else
            if Guild1 == GuidA then
                SetSceneMapDataFlag( sceneId,1,2,"粮仓",19,32,-1)
            elseif Guild1 == GuidB then
                SetSceneMapDataFlag( sceneId,1,1,"粮仓",19,32,-1)
            else
                SetSceneMapDataFlag( sceneId,1,0,"粮仓",19,32,-1)
            end
        end
    end

    --粮仓2
    if idx == 2 then
        if Guild2 < 0 then
            SetSceneMapDataFlag( sceneId,2,0,"粮仓",231,33,-1)
        else
            if Guild2 == GuidA then
                SetSceneMapDataFlag( sceneId,2,2,"粮仓",231,33,-1)
            elseif Guild2 == GuidB then
                SetSceneMapDataFlag( sceneId,2,1,"粮仓",231,33,-1)
            else
                SetSceneMapDataFlag( sceneId,2,0,"粮仓",231,33,-1)
            end
        end
    end

    --粮仓3
    if idx == 3 then
        if Guild3 < 0 then
            SetSceneMapDataFlag( sceneId,3,0,"粮仓",20,218,-1)
        else
            if Guild3 == GuidA then
                SetSceneMapDataFlag( sceneId,3,2,"粮仓",20,218,-1)
            elseif Guild3 == GuidB then
                SetSceneMapDataFlag( sceneId,3,1,"粮仓",20,218,-1)
            else
                SetSceneMapDataFlag( sceneId,3,0,"粮仓",20,218,-1)
            end
        end
    end

    --粮仓4
    if idx == 4 then
        if Guild4 < 0 then
            SetSceneMapDataFlag( sceneId,4,0,"粮仓",233,221,-1)
        else
            if Guild4 == GuidA then
                SetSceneMapDataFlag( sceneId,4,2,"粮仓",233,221,-1)
            elseif Guild4== GuidB then
                SetSceneMapDataFlag( sceneId,4,1,"粮仓",233,221,-1)
            else
                SetSceneMapDataFlag( sceneId,4,0,"粮仓",233,221,-1)
            end
        end
    end

    --仓库A
    if idx == 5 then
       SetSceneMapDataFlag( sceneId,5,4,"仓库",219,122.6,-1)
    end

    --仓库B
    if idx == 6 then
       SetSceneMapDataFlag( sceneId,6,3,"仓库",34,127.1,-1)
    end

    --旗子
    if idx == 7 then
        local owner = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_OWNER)
        if owner ~= -1 and IsPlayerStateNormal(sceneId,owner) == 1  then

            local nGuildID = GetGuildID(sceneId,owner)
            local x,z = GetWorldPos(sceneId,owner)

            if nGuildID == GuidA then
                SetSceneMapDataFlag( sceneId,7,6,"旗子",x,z,-1)
            elseif nGuildID == GuidB then
                SetSceneMapDataFlag( sceneId,7,5,"旗子",x,z,-1)
            else
                local x,z= GetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT )
                if x ~= nil and z ~= nil then
                    SetSceneMapDataFlag( sceneId,7,7,"旗子",x,z,-1)
                else
                    SetSceneMapDataFlag( sceneId,7,7,"旗子",LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y,-1)
                end
            end

        else

            local x,z= GetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT )

            if x ~= nil and z ~= nil then
                SetSceneMapDataFlag( sceneId,7,7,"旗子",x,z,-1)
            else
                SetSceneMapDataFlag( sceneId,7,7,"旗子",LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y,-1)
            end
        end
    end

    --NPCA
    if idx == 8 then
        SetSceneMapDataFlag( sceneId,8,8,"帮会战场传送者",17.3,134,-1)
    end

    --NPCA1
    --if idx == 9 then
    --    SetSceneMapDataFlag( sceneId,9,8,"山寨回援传送者",226,232,-1)
    --end

    if idx == 10 then
        SetSceneMapDataFlag( sceneId,10,8,"帮会战场管理员",237.8,129.8,-1)
    end

    --NPCB
    if idx == 11 then
        SetSceneMapDataFlag( sceneId,11,8,"帮会战场传送者",237.8,115,-1)
    end

    --NPCB1
    --if idx == 12 then
    --    SetSceneMapDataFlag( sceneId,12,8,"山庄回援传送者",22,22,-1)
    --end

    if idx == 13 then
        SetSceneMapDataFlag( sceneId,13,8,"帮会战场管理员",17.3,120,-1)
    end
end

----------------------------------------------------------------------------------------------
--奖励
----------------------------------------------------------------------------------------------
function x300643_BattleBonus( sceneId,selfId,battleResult ,nSortID)

    local sceneType = GetSceneType(sceneId) ;
    if sceneType ~= 2 then
        return
    end

    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID(sceneId,selfId)

    local nGuildFlag = -1

    --设置在战场中的阵营属性
    if nGuildId == nGuildA then
        nGuildFlag = 0
    elseif nGuildId == nGuildB then
        nGuildFlag = 1
    end


    local nBonusType = 2

    --判断一下输赢
    if battleResult == 0 then
        
        if nGuildFlag == 0 then
            nBonusType = 1
        else
            nBonusType = 0
        end

    elseif battleResult == 1 then
        
        if nGuildFlag == 0 then
            nBonusType = 0
        else
            nBonusType = 1
        end
    end

    if nBonusType == 0 then

        local level = GetLevel(sceneId,selfId)
        local name = GetName(sceneId,selfId)
        --战败
        local expNum =level * x300643_g_LosePrise
        local bangGong =  x300643_g_LoseBangGong
        local bangExp = x300643_g_LoseBangExp
		local bangshiming = x300643_g_LoseBangshiming 
		local bangjinqian = x300643_g_LoseBangjinqian
		--local banggongde = x300643_g_LoseBanggongde

        local msg = format(x300643_g_BonusTips,expNum,bangGong,bangExp,bangshiming,20)

        LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, x300643_g_BonusTips1,name , 3,1)

        AddExp(sceneId,selfId,expNum)
        AddGuildUserPoint(sceneId,selfId,bangGong)
        AddGuildExp(sceneId,selfId,bangExp)
		AddGuildShiMing (sceneId,selfId,bangshiming)
		AddGuildMoney(sceneId,selfId,bangjinqian)
		--AddGuildMerit(sceneId,selfId,banggongde)

        --发送Player相关信息
        local nCountryId   = GetCurCountry( sceneId, selfId )
        local nBeKilled    = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED)
        local nKilledOther = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_KILLEDOTHER)
        local nGetFlag     = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG)

        local nRongYu = nKilledOther*2
        AddHonor(sceneId,selfId,nRongYu)

        GuildBattleSendPlayerInfo(sceneId,name,nCountryId,nBeKilled,nKilledOther,nGetFlag,nRongYu,expNum,nGuildFlag)

    elseif nBonusType == 1 then

        local level = GetLevel(sceneId,selfId)
        local name = GetName(sceneId,selfId)
        --战胜
        local expNum =level * x300643_g_WinPrise
        local bangGong = x300643_g_WinBangGong
        local bangExp =  x300643_g_WinBangExp
		local bangshiming = x300643_g_WinBangshiming
		local bangjinqian = x300643_g_WinBangjinqian
		--local banggongde = x300643_g_WinBanggongde

        local msg = format(x300643_g_BonusTips,expNum,bangGong,bangExp,bangshiming,40)

        LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, x300643_g_BonusTips1,name , 3,1)

        AddExp(sceneId,selfId,expNum)
        AddGuildUserPoint(sceneId,selfId,bangGong)
        AddGuildExp(sceneId,selfId,bangExp)
		AddGuildShiMing (sceneId,selfId,bangshiming)
		AddGuildMoney(sceneId,selfId,bangjinqian)
		--AddGuildMerit(sceneId,selfId,banggongde)

        --发送Player相关信息
        local nCountryId   = GetCurCountry( sceneId, selfId )
        local nBeKilled    = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED)
        local nKilledOther = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_KILLEDOTHER)
        local nGetFlag     = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG)

        local nRongYu = nKilledOther*2
        AddHonor(sceneId,selfId,nRongYu)
        
        GuildBattleSendPlayerInfo(sceneId,name,nCountryId,nBeKilled,nKilledOther,nGetFlag,nRongYu,expNum,nGuildFlag)

    elseif nBonusType == 2 then

        local level = GetLevel(sceneId,selfId)
        local name = GetName(sceneId,selfId)
        --战平
        local expNum =level * x300643_g_DeucePrise
        local bangGong = x300643_g_DeuceBangGong
        local bangExp = x300643_g_DeuceBangExp
		local bangshiming = x300643_g_DeuceBangshiming
		local bangjinqian = x300643_g_DeuceBangjinqian
		--local banggongde = x300643_g_DeuceBanggongde

        local msg = format(x300643_g_BonusTips,expNum,bangGong,bangExp,bangshiming,20)

        LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, x300643_g_BonusTips1,name , 3,1)

        AddExp(sceneId,selfId,expNum)
        AddGuildUserPoint(sceneId,selfId,bangGong)
        AddGuildExp(sceneId,selfId,bangExp)
		AddGuildShiMing (sceneId,selfId,bangshiming)
		AddGuildMoney(sceneId,selfId,bangjinqian)
		--AddGuildMerit(sceneId,selfId,banggongde)

        --发送Player相关信息
        local nCountryId   = GetCurCountry( sceneId, selfId )
        local nBeKilled    = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_BEKILLED)
        local nKilledOther = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_KILLEDOTHER)
        local nGetFlag     = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG)

        local nRongYu = nKilledOther*2
        AddHonor(sceneId,selfId,nRongYu)
        
        GuildBattleSendPlayerInfo(sceneId,name,nCountryId,nBeKilled,nKilledOther,nGetFlag,nRongYu,expNum,nGuildFlag)

    end
    
    --前三名的特殊处理
    -- if nSortID == 1 then
    	
    	-- AddGuildMerit(sceneId,selfId,45)
    	
    	-- local name = GetName(sceneId,selfId)
    	-- local msg = "恭喜你在此次帮会战中获得个人第一名,奖励45点帮功德"
    	-- LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        -- LuaScenceM2Player(sceneId, selfId, msg ,name , 3,1)
    	
    -- elseif nSortID == 2 then
    	
    	-- AddGuildMerit(sceneId,selfId,40)
    	
    	-- local name = GetName(sceneId,selfId)
    	-- local msg = "恭喜你在此次帮会战中获得个人第二名,奖励40点帮功德"
    	-- LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        -- LuaScenceM2Player(sceneId, selfId, msg ,name , 3,1)
    	
    -- elseif nSortID == 3 then
    
    	-- AddGuildMerit(sceneId,selfId,35)
    	
    	-- local name = GetName(sceneId,selfId)
    	-- local msg = "恭喜你在此次帮会战中获得个人第三名,奖励35点帮功德"
    	-- LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        -- LuaScenceM2Player(sceneId, selfId, msg ,name , 3,1)
    -- end
    
end

----------------------------------------------------------------------------------------------
--奖励
----------------------------------------------------------------------------------------------
function x300643_GuildBattleBonus( sceneId ,battleResult )

	--收集信息
	local PlayerList = {}
	local PlayerCount = 0
	
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
        	
        	local nBeKilled    	= GetPlayerRuntimeData(sceneId,objId,RD_GUILDBATTLE_BEKILLED)
	        local nKilledOther 	= GetPlayerRuntimeData(sceneId,objId,RD_GUILDBATTLE_KILLEDOTHER)
	        local nGetFlag     	= GetPlayerRuntimeData(sceneId,objId,RD_GUILDBATTLE_GETFLAG)
	        local nPower 		= nKilledOther*5000 + nGetFlag*1000 - nBeKilled 
	        
	        --添加到排序列中
            PlayerCount = PlayerCount + 1
            PlayerList[PlayerCount] = {objId,nPower}
        end
    end
    
    
    --如果数量为0
    if PlayerCount == 0 then
    	return
    end
    
    --排序
    local sortproc = function(a,b) return a[2] > b[2] end 
    sort(PlayerList,sortproc)
    
    --奖励
    for i = 1,PlayerCount do
    	x300643_BattleBonus( sceneId,PlayerList[i][1],battleResult,i)
    end
    
end


----------------------------------------------------------------------------------------------
--恢复阵营
----------------------------------------------------------------------------------------------
function x300643_RestoreAllPlayerCamp( sceneId )

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
--恢复阵营
----------------------------------------------------------------------------------------------
function x300643_RestorePlayerCamp( sceneId,selfId )
    local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
end

----------------------------------------------------------------------------------------------
--生成帮战结果
----------------------------------------------------------------------------------------------
function x300643_BattleGenResult( sceneId, callerId  )

    local nTime = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_COUNT_ITME )
    
    --活动结束通知GLserver
    local GuildIdA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
    SetGuildQuestData(sceneId,GuildIdA,GD_GUILD_INDEX_BATTL_STATE,-1)

    local GuildIdB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)
    SetGuildQuestData(sceneId,GuildIdB,GD_GUILD_INDEX_BATTL_STATE,-1)

    local textA = "帮会战结束"
    local textB = "帮会战结束"

    local SystemTipsA = ""
    local SystemTipsB = ""

    --得到获胜方
    local Winner = x300643_GetWinner(sceneId)

    --发送基本信息
    local TitleBlue = GetGuildName( GuildIdA)
    local TitleRed  = GetGuildName( GuildIdB)

    GuildBattleSendBaseInfo(sceneId,TitleBlue,TitleRed,Winner,nTime)

    x300643_GuildBattleBonus( sceneId,Winner )

    if Winner == 0 then        --A方获胜

        SetGuildQuestData( sceneId,GuildIdA,GD_GUILD_INDEX_BATTL_WIN_NUM,1,1 )
        SetGuildQuestData( sceneId,GuildIdB,GD_GUILD_INDEX_BATTL_LOSE_NUM,1,1 )
		
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdA, 2 )	
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdB, 0 )
		

        --设置相关提示
        textA = "#G您所在的帮会在本次帮会战中取得胜利"
        textB = "#G您所在的帮会在本次帮会战中惨遭失败"

        SystemTipsA = "战场胜利"
        SystemTipsB = "战场失败"

    elseif Winner == 1 then    --B方获胜

        SetGuildQuestData( sceneId,GuildIdB,GD_GUILD_INDEX_BATTL_WIN_NUM,1,1 )
        SetGuildQuestData( sceneId,GuildIdA,GD_GUILD_INDEX_BATTL_LOSE_NUM,1,1 )
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdA, 0 )	
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdB, 2 )

        --设置相关提示
        textA = "#G您所在的帮会在本次帮会战中惨遭失败"
        textB = "#G您所在的帮会在本次帮会战中取得胜利"

        SystemTipsA = "战场失败"
        SystemTipsB = "战场胜利"

    else                        --握手言和

        SetGuildQuestData( sceneId,GuildIdA,GD_GUILD_INDEX_BATTL_DEUCE_NUM,1,1 )
        SetGuildQuestData( sceneId,GuildIdB,GD_GUILD_INDEX_BATTL_DEUCE_NUM,1,1 )
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdA, 1 )	
		CallScriptFunction( 300638, "SaveGuildWeekResult", sceneId,GuildIdB, 1 )

        --设置相关提示
        textA = "#G您所在的帮会在本次帮会战中打成平手"
        textB = "#G您所在的帮会在本次帮会战中打成平手"

        SystemTipsA = "双方战平"
        SystemTipsB = "双方战平"
    end

    --广播
    LuaThisScenceM2Guild(sceneId,textA,GuildIdA,2,1)
    LuaThisScenceM2Guild(sceneId,textB,GuildIdB,2,1)

    LuaThisScenceM2Guild(sceneId,textA,GuildIdA,3,1)
    LuaThisScenceM2Guild(sceneId,textB,GuildIdB,3,1)

    LuaThisScenceM2Guild(sceneId,SystemTipsA,GuildIdA,5,1)
    LuaThisScenceM2Guild(sceneId,SystemTipsB,GuildIdB,5,1)


    --进入倒计时状态,并设置倒计时间
    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_STATE,1 )
    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_COUNT_DOWN_TIME,60 )
        
    --记录日志
    local msg = format("GBL:x300643_BattleGenResult SceneId=%d,LeaveTime h= %d,m=%d,CallerId=%d",sceneId, floor(nTime/60),mod(nTime,60), callerId )
    WriteLog(1,msg)

    x300643_SetAllPlayerNeedKick(sceneId,60)
    x300643_DestroyBattleFlags( sceneId )
    ClearGuildBattleSceneData(sceneId)

end

----------------------------------------------------------------------------------------------
--踢人
----------------------------------------------------------------------------------------------
function x300643_GuildBattleKickPlayer( sceneId,selfId )

    --清除死亡状态
    if GetHp(sceneId,selfId) <= 0 then
	
		ClearRageRecoverTick(sceneId, selfId)
		RestoreHp(sceneId, selfId,100)
		RestoreRage(sceneId, selfId,100)
		ClearMutexState(sceneId, selfId, 6)
		SendReliveResult(sceneId, selfId,1)	
	end
	
	LastMount(sceneId, selfId )
	RestoreHp(sceneId, selfId,0)
	
    x300643_RestorePlayerCamp(sceneId,selfId)

    --如果存在BakScene信息，则以BakScene信息为准
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,300643)
        return
    end

    --如果没有BakScene信息，则传送到王城新手村
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        
        --楼兰
        local nDestSceneId = 50
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300643)

    elseif nCountry == 1 then
        
        --天山
        local nDestSceneId = 150
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300643)

    elseif nCountry == 2 then

        --昆仑
        local nDestSceneId = 250
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300643)

    elseif nCountry == 3 then
        
        --敦煌
        local nDestSceneId = 350
        local nPosX = 123
        local nPosZ = 57

        NewWorld(sceneId,selfId,nDestSceneId,nPosX,nPosZ,300643)

    end
end

----------------------------------------------------------------------------------------------
--踢掉场景里所有的人
----------------------------------------------------------------------------------------------
function x300643_GuildBattleKickAllPlayer( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            
            x300643_GuildBattleKickPlayer( sceneId,objId)

        end
    end
end

----------------------------------------------------------------------------------------------
--同步帮战倒计时给全部玩家（当前场景）
----------------------------------------------------------------------------------------------
function x300643_SyncBattleTimeToAllPlayer( sceneId ,nTime )

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
--玩家请求离开帮会战场
----------------------------------------------------------------------------------------------
function x300643_OnPlayerAskLeaveGuildBattle( sceneId,selfId )
    
    x300643_GuildBattleKickPlayer( sceneId, selfId )

end

----------------------------------------------------------------------------------------------
--从GLServer过来的同步帮会时间的东东
----------------------------------------------------------------------------------------------
function x300643_OnSyncGuildBattleTime( sceneId,nTime )
    
    if x300643_IsGuildBattleScene_Gjs( sceneId ) == 0 then
        return
    end

    if x300643_CheckBattleState( sceneId ) == 0 then
        return
    end

    local nTime_new = x300643_g_TotalBattleTime - NumberCastIntToUInt( nTime )
    SetGuildBattleSceneData_Param(sceneId, LD_GUILD_BATTLE_COUNT_ITME, nTime_new )

    --定时器时间同步
    ----------------------------------------------------------------------------------------------
    x300643_SyncBattleTimeToAllPlayer( sceneId, nTime_new )
end


----------------------------------------------------------------------------------------------
--设置所有玩家需要踢掉
----------------------------------------------------------------------------------------------
function x300643_SetAllPlayerNeedKick( sceneId,nKickTime )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > nKickTime then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,nKickTime) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--更新玩家踢掉状态
----------------------------------------------------------------------------------------------
function x300643_UpdatePlayerKickState( sceneId )
    
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
                    x300643_GuildBattleKickPlayer( sceneId,objId )
                else
                    --否则，继续倒计时
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--同步帮会势力
----------------------------------------------------------------------------------------------
function x300643_SyncGuildPower( sceneId )
    
    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

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
    BroadcastGuildBattlePower(sceneId,nGuildA_Count,nGuildB_Count)

end

----------------------------------------------------------------------------------------------
--重置护兽生长点
----------------------------------------------------------------------------------------------
function x300643_ResetConvoyGrowPoint(sceneId,bShowMsg)

	local nCount = getn(x300643_g_ConvoyGrowPointPosList)
	local nIndex = random(1,nCount)
	
	if nIndex < 1 then
		nIndex = 1
	elseif nIndex > nCount then
		nIndex = nCount
	end
	
	local x = x300643_g_ConvoyGrowPointPosList[nIndex][1]
	local z = x300643_g_ConvoyGrowPointPosList[nIndex][2]
	
	RecycleGrowPointByType(sceneId,x300643_g_ConvoyGrowPointType[sceneId],1000)
    SetGrowPointPos(sceneId,x300643_g_ConvoyGrowPointType[sceneId],x,z)
    
    if bShowMsg == 1 then
	    local msg = format("战神留下的宝箱出现在(%d,%d)",x,z)
	    LuaThisScenceM2Wrold(sceneId,msg,2,1)	
	    LuaThisScenceM2Wrold(sceneId,msg,3,1)
    end
end

----------------------------------------------------------------------------------------------
--检查是否可以执行护兽生长点采集
----------------------------------------------------------------------------------------------
function x300643_OnRecyleConvoyGrowPoint_Check(sceneId,selfId)
	
	local status = GetGuildBattleStatus( sceneId )
    if status ~= STATE_GUILD_BATTLE_BATTLE then
    	return 1
    end
    
    local nCampID = GetCurCamp(sceneId,selfId)
    if nCampID ~= x300643_g_Guild_Camp_A and nCampID ~= x300643_g_Guild_Camp_B then
    	return 1
    end
	
	return 0
end

----------------------------------------------------------------------------------------------
--执行护兽生长点采集
----------------------------------------------------------------------------------------------
function x300643_OnRecyleConvoyGrowPoint(sceneId,selfId)


	--相关检查
	local status = GetGuildBattleStatus( sceneId )
    if status ~= STATE_GUILD_BATTLE_BATTLE then
    	return 0
    end
    
    local nCampID = GetCurCamp(sceneId,selfId)
    if nCampID ~= x300643_g_Guild_Camp_A and nCampID ~= x300643_g_Guild_Camp_B then
    	return 0
    end
	
	--A方计分
	if nCampID == x300643_g_Guild_Camp_A then
		x300643_g_ScoreIntervalA[sceneId] = x300643_g_ScoreIntervalA[sceneId] + 10
		BroadcastGuildBattleResourceScore(sceneId, 0,x300643_g_ScoreIntervalA[sceneId] )
	end
	
	--B方计分
	if nCampID == x300643_g_Guild_Camp_B then
		x300643_g_ScoreIntervalB[sceneId] = x300643_g_ScoreIntervalB[sceneId] + 10
		BroadcastGuildBattleResourceScore(sceneId, 1,x300643_g_ScoreIntervalB[sceneId] )
	end
	
	--设置生长点需要重置
	x300643_g_ConvoyGrowPointState[sceneId] = 0
	
	--清空种子数量
	SetGrowPointIntervalContainer(sceneId,x300643_g_ConvoyGrowPointType[sceneId],-1)
	
	--告诉系统可以回收
	return 1
end

----------------------------------------------------------------------------------------------
--取得内部集分A
----------------------------------------------------------------------------------------------
function x300643_GetScoreIntervalA(sceneId)
	return x300643_g_ScoreIntervalA[sceneId]
end

----------------------------------------------------------------------------------------------
--取得内部集分B
----------------------------------------------------------------------------------------------
function x300643_GetScoreIntervalB(sceneId)
	return x300643_g_ScoreIntervalB[sceneId]
end

----------------------------------------------------------------------------------------------
--玩法1：获得战场资源点
--阵营ID，0或1
----------------------------------------------------------------------------------------------
--帮会战中双方阵营

function x300643_GetScoreInterval(sceneId,CampId)
	if CampId == x300643_g_Guild_Camp_A then
		local ResPointA = x300643_g_ScoreIntervalA[sceneId]
		return ResPointA
	elseif CampId == x300643_g_Guild_Camp_B then
		local ResPointB = x300643_g_ScoreIntervalB[sceneId]
		return ResPointB
	end
	return -1
end


----------------------------------------------------------------------------------------------
--设置取得内部集分
----------------------------------------------------------------------------------------------
function x300643_SetScoreIntervalInc(sceneId,CampId,resPointInc)
	if CampId == x300643_g_Guild_Camp_A then
		local ResPointA = x300643_g_ScoreIntervalA[sceneId]
		x300643_g_ScoreIntervalA[sceneId] = ResPointA + resPointInc
		BroadcastGuildBattleResourceScore(sceneId, 0,x300643_g_ScoreIntervalA[sceneId] )

	elseif CampId == x300643_g_Guild_Camp_B then
		local ResPointB = x300643_g_ScoreIntervalB[sceneId]
		x300643_g_ScoreIntervalB[sceneId] = ResPointB + resPointInc
		BroadcastGuildBattleResourceScore(sceneId, 1,x300643_g_ScoreIntervalB[sceneId] )
	end

end