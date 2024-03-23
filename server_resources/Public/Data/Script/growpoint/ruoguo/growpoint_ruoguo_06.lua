--生长点

x301437_g_GrowpointId = 716 --对应生长点ID
x301437_g_ItemIndex = -1 --对应收集物品的ID
x301437_g_TargetScriptId = 310210


--生成函数开始************************************************************************
function 	x301437_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301437_g_GrowpointId, sceneId, 0, x301437_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301437_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301437_g_TargetScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301437_g_GrowpointId, x301437_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301437_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301437_g_TargetScriptId, "OnRecycle", sceneId, selfId, targetId, x301437_g_GrowpointId, x301437_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301437_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( x301437_g_TargetScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

