x303011_g_GrowPointType	= 542

-------------------------------------------------------------------------
--采集点创建
-------------------------------------------------------------------------
function 	x303011_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x303011_g_GrowPointType, sceneId, 0, -1)
	SetGrowPointObjID(sceneId,x303011_g_GrowPointType,x,y,ItemBoxId)
end

-------------------------------------------------------------------------
--采集点打开
-------------------------------------------------------------------------
function x303011_OnOpen(sceneId,selfId,targetId)
    return 0
end

-------------------------------------------------------------------------
--采集点回收
-------------------------------------------------------------------------
function x303011_OnRecycle(sceneId,selfId,targetId)
	CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"OnGrowpointEvent_CB",sceneId,selfId,x303011_g_GrowPointType)
	return 1
end

-------------------------------------------------------------------------
--采集点结束
-------------------------------------------------------------------------
function x303011_OnProcOver(sceneId,selfId,targetId)
end

-------------------------------------------------------------------------
--采集点检查
-------------------------------------------------------------------------
function x303011_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
end

-------------------------------------------------------------------------
--采集任务
-------------------------------------------------------------------------
function x303011_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return 0
end
