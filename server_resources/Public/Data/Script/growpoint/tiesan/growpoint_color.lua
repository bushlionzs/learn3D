--生长点

x301431_g_GrowpointId = 710 		--对应生长点ID

x301431_g_MissionId = 7538
x301431_g_BuffList={7709,7710,7711,0}
x301431_g_SubmitNpc = 139102

--生成函数开始************************************************************************
function 	x301431_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301431_g_GrowpointId, sceneId, 0, -1)
	SetGrowPointObjID(sceneId,x301431_g_GrowpointId,x, y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301431_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x301431_OnOpen")
    return x301431_OnOpenItemBox(sceneId, selfId, targetId, x301431_g_GrowpointId, -1)	
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301431_OnRecycle(sceneId,selfId,targetId)
	return   x301431_OnGuildRecycle( sceneId, selfId, targetId, x301431_g_GrowpointId, -1 )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301431_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301431_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x301431_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	
	if IsHaveQuestNM( sceneId, selfId, x301431_g_MissionId ) <= 0 then
		Msg2Player(sceneId,selfId,"您没有任务【体】铁人三项，请您关注系统公告。",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		return -31
	end
	    
	return 0
end

--回收
function x301431_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
	local x, z = GetWorldPos( sceneId, FindMonsterByGUID(sceneId, x301431_g_SubmitNpc))
	Msg2Player(sceneId,selfId,format("简申现在正在:%d,%d附近。", x, z),CHAT_TYPE_SELF,CHAT_LEFTDOWN)
	return 1

end