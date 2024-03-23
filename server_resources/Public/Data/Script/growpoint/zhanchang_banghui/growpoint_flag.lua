--旗子

x300666_g_ItemIndex = 12010001

--生成函数开始************************************************************************
function 	x300666_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, LD_GUILD_BATTLE_FLAG_GROW_POINT, sceneId, 0, x300666_g_ItemIndex)
    SetGrowPointObjID(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,x,y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300666_OnOpen(sceneId,selfId,targetId)
    return x300666_OnOpenItemBox(sceneId, selfId, targetId, LD_GUILD_BATTLE_FLAG_GROW_POINT, x300666_g_ItemIndex)
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x300666_OnRecycle(sceneId,selfId,targetId)
	return   x300666_OnGuildRecycle( sceneId, selfId, targetId, LD_GUILD_BATTLE_FLAG_GROW_POINT, x300666_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300666_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300666_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x300666_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return 0
end

--回收
function x300666_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

    if CallScriptFunction(GUILDBATTLE_SCRIPTID,"CheckBattleState", sceneId) == 0 then
        return 0
    end

    ReCallHorse( sceneId, selfId )--强制下马

 	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,LD_GUILD_BATTLE_DEC_SPEED_BUF,200)  --200毫秒
 	SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,LD_GUILD_BATTLE_INC_DEFENCE_BUF,200)--200毫秒
 	--SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId,LD_GUILD_BATTLE_FLAG_BUF,0)

 	if GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_TIME) == -1 then
 	 	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_TIME,60*10 )     --旗子有效时间5分钟
 	end

 	SetGuildBattleSceneData_Param( sceneId,LD_GUILD_BATTLE_FLAG_OWNER,selfId )  --记录旗子主人
	--重设旗子重生时间
	SetGrowPointIntervalContainer(sceneId,LD_GUILD_BATTLE_FLAG_GROW_POINT,-1)

    CallScriptFunction( GUILDBATTLE_SCRIPTID,"UpdateSceneDataFlag",sceneId,7 )
    CallScriptFunction( 300669,"CancelBuffer",sceneId,selfId )

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
        
        LuaThisScenceM2Wrold(sceneId,"蓝方夺取了战旗",2,1)
        LuaThisScenceM2Wrold(sceneId,"蓝方夺取了战旗",3,1)

    elseif nFlag == 1 then
        
        LuaThisScenceM2Wrold(sceneId,"红方夺取了战旗",2,1)
        LuaThisScenceM2Wrold(sceneId,"红方夺取了战旗",3,1)
    end

	return 1

end

--**********************************************************************

