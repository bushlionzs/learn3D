--生长点

x301061_g_GrowpointId = 61 --对应生长点ID
x301061_g_ItemIndex = 13011511 --对应收集物品的ID
x301061_g_FarScriptId = 300501


--生成函数开始************************************************************************
function 	x301061_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301061_g_GrowpointId, sceneId, 0, x301061_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301061_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301061_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301061_g_GrowpointId, x301061_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301061_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301061_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x301061_g_GrowpointId, x301061_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301061_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301061_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301061_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301061_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end
