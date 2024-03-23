--生长点

x301091_g_GrowpointId = 216 --对应生长点ID
x301091_g_ItemIndex = -1 --对应收集物品的ID
x301091_g_TargetScriptId = 300576


--生成函数开始************************************************************************
function 	x301091_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301091_g_GrowpointId, sceneId, 0, x301091_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301091_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301091_g_TargetScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301091_g_GrowpointId, x301091_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301091_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301091_g_TargetScriptId, "OnRecycle", sceneId, selfId, targetId, x301091_g_GrowpointId, x301091_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301091_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( x301091_g_TargetScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

