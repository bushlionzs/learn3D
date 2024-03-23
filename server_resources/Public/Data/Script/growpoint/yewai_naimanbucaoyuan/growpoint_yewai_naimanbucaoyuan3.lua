--生长点

x301362_g_GrowpointId = 312 --对应生长点ID
x301362_g_ItemIndex = 13010120 --对应收集物品的ID


--生成函数开始************************************************************************
function 	x301362_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301362_g_GrowpointId, sceneId, 0, x301362_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301362_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( 202002, "OnOpenItemBox", sceneId, selfId, targetId, x301362_g_GrowpointId, x301362_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301362_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( 202002, "OnRecycle", sceneId, selfId, targetId, x301362_g_GrowpointId, x301362_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301362_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

