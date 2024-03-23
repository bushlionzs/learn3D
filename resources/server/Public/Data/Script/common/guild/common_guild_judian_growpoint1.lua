--DOORA

x300921_g_ItemIndex = -1

--生成函数开始************************************************************************
function x300921_OnCreate(sceneId,growPointType,x,y)
	
	local typeGrowPoint = CallScriptFunction(300918,"GetDoorA",sceneId)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, typeGrowPoint, sceneId, 0, x300921_g_ItemIndex)
    SetGrowPointObjID(sceneId,typeGrowPoint,x,y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function x300921_OnOpen(sceneId,selfId,targetId)
	
	local typeGrowPoint = CallScriptFunction(300918,"GetDoorA",sceneId)
    return x300921_OnOpenItemBox(sceneId, selfId, targetId, typeGrowPoint, x300921_g_ItemIndex)
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function x300921_OnRecycle(sceneId,selfId,targetId)
	local typeGrowPoint = CallScriptFunction(300918,"GetDoorA",sceneId)
	return x300921_OnGuildRecycle( sceneId, selfId, targetId, typeGrowPoint, x300921_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function x300921_OnProcOver(sceneId,selfId,targetId)	
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


function x300921_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
end


--**********************************************************************
--采集任务
--打开ItemBox
function x300921_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction(300918,"OnOpenDoorA_Check",sceneId,selfId)
end

--回收
function x300921_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )

	return CallScriptFunction(300918,"OnOpenDoorA",sceneId,selfId)
end

--**********************************************************************

