-- 采集点

x301446_g_GrowpointId = 725 --对应生长点ID
x301446_g_ItemIndex = 13070011 --对应收集物品的ID
x301446_g_ScriptId = 305015


--生成函数开始************************************************************************
function 	x301446_OnCreate( sceneId, growPointType, x, y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301446_g_GrowpointId, sceneId, 0, x301446_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301446_g_GrowpointId, x, y, ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301446_OnOpen( sceneId, selfId, targetId)
	return CallScriptFunction( x301446_g_ScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301446_g_GrowpointId, x301446_g_ItemIndex)
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301446_OnRecycle( sceneId, selfId, targetId)
	return CallScriptFunction( x301446_g_ScriptId, "OnRecycle", sceneId, selfId, targetId, x301446_g_GrowpointId, x301446_g_ItemIndex)
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301446_OnProcOver( sceneId, selfId, targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId)
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


