--生长点

x301057_g_GrowpointId = 57 --对应生长点ID
x301057_g_ItemIndex = 13011507 --对应收集物品的ID
x301057_g_FarScriptId = 300501


--生成函数开始************************************************************************
function 	x301057_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301057_g_GrowpointId, sceneId, 0, x301057_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301057_OnOpen(sceneId,selfId,targetId)

	return CallScriptFunction( x301057_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x301057_g_GrowpointId, x301057_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301057_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x301057_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x301057_g_GrowpointId, x301057_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301057_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301057_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301057_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301057_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end
