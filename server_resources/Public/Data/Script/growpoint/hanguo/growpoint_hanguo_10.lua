--生长点

x301059_g_GrowpointId = 59 --对应生长点ID
x301059_g_ItemIndex = 13011509 --对应收集物品的ID
x301059_g_FarScriptId = 300501


--生成函数开始************************************************************************
function 	x301059_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301059_g_GrowpointId, sceneId, 0, x301059_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301059_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301059_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301059_g_GrowpointId, x301059_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301059_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301059_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x301059_g_GrowpointId, x301059_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301059_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301059_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301059_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301059_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end
