--帮会战守护兽积分采集点

x300644_g_ItemIndex = -1
x300644_g_GrowPointType = 114

--生成函数开始************************************************************************
function x300644_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300644_g_GrowPointType, sceneId, 0, x300644_g_ItemIndex)
    SetGrowPointObjID(sceneId,x300644_g_GrowPointType,x,y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function x300644_OnOpen(sceneId,selfId,targetId)
    return x300644_OnOpenItemBox(sceneId, selfId, targetId, x300644_g_GrowPointType, x300644_g_ItemIndex)
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function x300644_OnRecycle(sceneId,selfId,targetId)
	return x300644_OnGuildRecycle( sceneId, selfId, targetId, x300644_g_GrowPointType, x300644_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function x300644_OnProcOver(sceneId,selfId,targetId)	
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


function x300644_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
end


--**********************************************************************
--采集任务
--打开ItemBox
function x300644_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction(300643,"OnRecyleConvoyGrowPoint_Check",sceneId,selfId)
end

--回收
function x300644_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

	return CallScriptFunction(300643,"OnRecyleConvoyGrowPoint",sceneId,selfId)
end

--**********************************************************************

