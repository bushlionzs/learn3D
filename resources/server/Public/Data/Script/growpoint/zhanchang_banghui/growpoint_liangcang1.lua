--粮仓1

x300662_g_GrowpointId = 106 		--对应生长点ID
x300662_g_ItemIndex = 12010001
x300662_g_BufIndex = 1210

--生成函数开始************************************************************************
function 	x300662_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300662_g_GrowpointId, sceneId, 0, x300662_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300662_OnOpen(sceneId,selfId,targetId)
    return x300662_OnOpenItemBox(sceneId, selfId, targetId, x300662_g_GrowpointId, x300662_g_ItemIndex)
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x300662_OnRecycle(sceneId,selfId,targetId)
	return   x300662_OnGuildRecycle( sceneId, selfId, targetId, x300662_g_GrowpointId, x300662_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300662_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300662_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x300662_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )

    
    local nResult = CallScriptFunction(GUILDBATTLE_SCRIPTID,"CheckBattleState", sceneId)
    if  nResult == 0 then
        return 1
    end

	local guild = GetGuildID(sceneId, selfId)
	if guild == -1 then
		return 1
	end

	--得到粮仓当前帮会
	local guild = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN1_GUILD)
	if guild == GetGuildID(sceneId, selfId) then	--是本方粮仓
		--得到玩家所属方，A或B方
        local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
        local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

        local flag = -1

        --设置在战场中的阵营属性
        if guild == nGuildA then
            flag = 0
        elseif guild == nGuildB then
            flag = 1
        end

	  	--判断身上是否有旗
    	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
    	if IsHaveFlag == 0 then
    		--身上无旗不可交
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "身上无旗不可交！");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		end

		if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN2_GUILD) ~= guild and GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_BARN3_GUILD) ~= guild then
  			--占领相邻粮仓才能交
 			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "占领相邻粮仓才能交！");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		end

		local FlagNum = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_FLAG_NUM+flag) + 1
        --if FlagNum < LD_GUILD_BATTLE_FLAG_COUNT then						--夺旗次数
        SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_FLAG_NUM+flag,FlagNum )
        --else
        --	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_A_FLAG_NUM+flag,LD_GUILD_BATTLE_FLAG_COUNT )
        --end

        --积分增加10
        if flag == 0 then
            local Score = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_SOCRE) + 10
            SetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_SOCRE ,Score )
        end

        if flag == 1 then
            local Score = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_SOCRE) + 10
            SetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_SOCRE ,Score )
        end

        --旗子计数加1
        local nGetFlag = GetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG) + 1
        SetPlayerRuntimeData(sceneId,selfId,RD_GUILDBATTLE_GETFLAG,nGetFlag) 

		--删除夺旗BUF
	    CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
	    CancelSpecificImpact(sceneId,selfId,LD_GUILD_BATTLE_INC_DEFENCE_BUF )
	    --CancelSpecificImpact(sceneId,owner,LD_GUILD_BATTLE_FLAG_BUF )
	    SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,-1 )

		--if FlagNum < LD_GUILD_BATTLE_FLAG_COUNT then
			--重设旗子位置后立即重生
			SetGrowPointPos(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,LD_GUILD_BATTLE_FLAG_X,LD_GUILD_BATTLE_FLAG_Y)
			SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,1000)
			SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,-1 )
            CallScriptFunction( GUILDBATTLE_SCRIPTID,"UpdateSceneDataFlag",sceneId,7 )
		--end

        --给出相应提示
        if flag == 0 then
            
            LuaThisScenceM2Wrold(sceneId,"蓝方成功交付了战旗",2,1)
            LuaThisScenceM2Wrold(sceneId,"蓝方成功交付了战旗",3,1)

        elseif flag == 1 then
            
            LuaThisScenceM2Wrold(sceneId,"红方成功交付了战旗",2,1)
            LuaThisScenceM2Wrold(sceneId,"红方成功交付了战旗",3,1)
        end

		return 1
	else
        --判断身上是否有旗
    	local IsHaveFlag = IsHaveSpecificImpact(sceneId, selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF )
    	if IsHaveFlag == 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "身上有旗不可采集！");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		end
    end

	return 0
end

--回收
function x300662_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
    
    local nResult = CallScriptFunction(GUILDBATTLE_SCRIPTID,"CheckBattleState", sceneId)
    if  nResult == 0 then
        return 0
    end

	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_GUILD,GetGuildID(sceneId, selfId) )

	--重设被占领时间
	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_BARN1_TIME,-1 )

    CallScriptFunction( GUILDBATTLE_SCRIPTID,"UpdateSceneDataFlag",sceneId,1 )

    local nGuildA = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_A_GUILD )
    local nGuildB = GetGuildBattleSceneData_Param( sceneId, LD_GUILD_BATTLE_B_GUILD )

    local nGuildId = GetGuildID( sceneId,selfId )

    --设置在战场中的阵营属性
    local nFlag = -1
    if nGuildId == nGuildA then
        nFlag = 0
    elseif nGuildId == nGuildB then
        nFlag = 1
    end

    --给出相应提示
    if nFlag == 0 then
        
        LuaThisScenceM2Wrold(sceneId,"蓝方夺取了粮仓",2,1)
        LuaThisScenceM2Wrold(sceneId,"蓝方夺取了粮仓",3,1)

    elseif nFlag == 1 then
        
        LuaThisScenceM2Wrold(sceneId,"红方夺取了粮仓",2,1)
        LuaThisScenceM2Wrold(sceneId,"红方夺取了粮仓",3,1)
    end

	return 1

end

--**********************************************************************

