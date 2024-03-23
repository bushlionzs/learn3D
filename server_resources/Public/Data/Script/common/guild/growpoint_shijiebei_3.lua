--生长点

x300838_g_GrowpointId = 729 --对应生长点ID
x300838_g_ItemIndex = 13080024 --对应收集物品的ID
x300838_g_FarScriptId = 300615


--生成函数开始************************************************************************
function 	x300838_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300838_g_GrowpointId, sceneId, 0, x300838_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x300838_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( x300838_g_FarScriptId, "OnOpenItemBox", sceneId, selfId, targetId, x300838_g_GrowpointId, x300838_g_ItemIndex)
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x300838_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( x300838_g_FarScriptId, "OnRecycle", sceneId, selfId, targetId, x300838_g_GrowpointId, x300838_g_ItemIndex)
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x300838_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x300838_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId)
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x300838_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( x300838_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId)
end
