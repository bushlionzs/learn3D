--生长点

x301047_g_GrowpointId = 192 --对应生长点ID
x301047_g_ItemIndex = 13810059 --对应收集物品的ID
x301047_g_MissionId = 300566


--生成函数开始************************************************************************
function 	x301047_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301047_g_GrowpointId, sceneId, 0, x301047_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301047_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x301047_g_MissionId, "OnOpenItemBox", sceneId, selfId, targetId, x301047_g_GrowpointId, x301047_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301047_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301047_g_MissionId, "OnRecycle", sceneId, selfId, targetId, x301047_g_GrowpointId, x301047_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301047_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


