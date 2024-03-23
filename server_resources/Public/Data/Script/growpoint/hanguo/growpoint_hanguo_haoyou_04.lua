--生长点

x302004_g_GrowpointId = 424 --对应生长点ID
x302004_g_ItemIndex = 13013704 --对应收集物品的ID


--生成函数开始************************************************************************
function 	x302004_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x302004_g_GrowpointId, sceneId, 0, x302004_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x302004_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnOpenItemBox", sceneId, selfId, targetId, x302004_g_GrowpointId, x302004_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x302004_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( 300782, "OnRecycle", sceneId, selfId, targetId, x302004_g_GrowpointId, x302004_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x302004_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( 300782, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


