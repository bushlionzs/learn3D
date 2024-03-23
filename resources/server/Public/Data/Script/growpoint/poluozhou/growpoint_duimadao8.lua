-- 采集点

x301445_g_GrowpointId = 724 --对应生长点ID
x301445_g_ItemIndex = 13070011 --对应收集物品的ID
x301445_g_ScriptId = 305015


--生成函数开始************************************************************************
function 	x301445_OnCreate( sceneId, growPointType, x, y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301445_g_GrowpointId, sceneId, 0, x301445_g_ItemIndex)
    SetGrowPointObjID( sceneId, x301445_g_GrowpointId, x, y, ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301445_OnOpen( sceneId, selfId, targetId)
	return CallScriptFunction( x301445_g_ScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301445_g_GrowpointId, x301445_g_ItemIndex)
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301445_OnRecycle( sceneId, selfId, targetId)
	return CallScriptFunction( x301445_g_ScriptId, "OnRecycle", sceneId, selfId, targetId, x301445_g_GrowpointId, x301445_g_ItemIndex)
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301445_OnProcOver( sceneId, selfId, targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId)
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


