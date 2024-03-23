--生长点

x700080_g_GrowpointId = 500 --对应生长点ID
x700080_g_ItemIndex = -1 --对应收集物品的ID

x700080_g_ScriptId = 700080
x700080_Fuben_ScriptId = 700021
x700080_CSP_B_GROWPOINT_OVER = 239--x700021_CSP_B_GROWPOINT_OVER



--生成函数开始************************************************************************
function 	x700080_OnCreate(sceneId,growPointType,x,y)
	

	local bOver = GetFubenData_Param(sceneId, x700080_CSP_B_GROWPOINT_OVER);

	if bOver>0 then
		return
	end

	local ItemBoxId = ItemBoxEnterScene(x, y, x700080_g_GrowpointId, sceneId, 0, x700080_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x700080_OnOpen(sceneId,selfId,targetId)
	
	
	return 0
	
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x700080_OnRecycle(sceneId,selfId,targetId)
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x700080_g_GrowpointId, x700080_g_ItemIndex )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x700080_OnProcOver(sceneId,selfId,targetId)

	--//add in 2009-9-8
	local nScriptId = GetFubenData_Param(sceneId, 1);

	CallScriptFunction( nScriptId, "OnGrowPoint", sceneId, selfId ) ;
	
	--//add end

	

	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x700080_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
