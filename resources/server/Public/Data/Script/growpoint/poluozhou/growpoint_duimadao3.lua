-- 采集点

x301440_g_GrowpointId = 719 --对应生长点ID
x301440_g_ItemIndex = 13070012 --对应收集物品的ID
x301440_g_ScriptId = 305015


--生成函数开始************************************************************************
function 	x301440_OnCreate( sceneId, growPointType, x, y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301440_g_GrowpointId, sceneId, 0, x301440_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301440_g_GrowpointId, x, y, ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301440_OnOpen( sceneId, selfId, targetId)
	return CallScriptFunction( x301440_g_ScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301440_g_GrowpointId, x301440_g_ItemIndex)
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301440_OnRecycle( sceneId, selfId, targetId)
	return CallScriptFunction( x301440_g_ScriptId, "OnRecycle", sceneId, selfId, targetId, x301440_g_GrowpointId, x301440_g_ItemIndex)
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301440_OnProcOver( sceneId, selfId, targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId)
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


