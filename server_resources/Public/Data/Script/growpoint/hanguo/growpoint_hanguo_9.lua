--生长点

x301058_g_GrowpointId = 58 --对应生长点ID
x301058_g_ItemIndex = 13011508 --对应收集物品的ID
x301058_g_ScriptTable = {
    300520, 
    300511, 
    300512, 
    300513, 
}


--生成函数开始************************************************************************
function 	x301058_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301058_g_GrowpointId, sceneId, 0, x301058_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301058_OnOpen(sceneId,selfId,targetId)
    return CallScriptFunction( x301058_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnOpenItemBox", sceneId, selfId, targetId, x301058_g_GrowpointId, x301058_g_ItemIndex )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301058_OnRecycle(sceneId,selfId,targetId)
    return CallScriptFunction( x301058_g_ScriptTable[ GetCurCountry( sceneId, selfId) + 1], "OnRecycle", sceneId, selfId, targetId, x301058_g_GrowpointId, x301058_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301058_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( x301058_g_FarScriptId, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301058_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( x301058_g_FarScriptId, "OpenCheck", sceneId, selfId, targetId )
end
