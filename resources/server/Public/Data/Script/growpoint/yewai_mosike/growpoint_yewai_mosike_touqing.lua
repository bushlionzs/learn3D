--生长点

x301450_g_GrowpointId = 125 --对应生长点ID
x301450_g_ItemIndex = 13010029 --对应收集物品的ID


--生成函数开始************************************************************************
function 	x301450_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301450_g_GrowpointId, sceneId, 0, x301450_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301450_OnOpen(sceneId,selfId,targetId)
	return CallScriptFunction( 203328, "Growpoint", sceneId, selfId, 0 )
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301450_OnRecycle(sceneId,selfId,targetId)
	 CallScriptFunction( 203328, "Growpoint", sceneId, selfId, 1 )
	  return 0
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301450_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

