--生长点

x301310_g_GrowpointId = 176 --对应生长点ID
x301310_g_ItemIndex = 13030081 --对应收集物品的ID


--生成函数开始************************************************************************
function 	x301310_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301310_g_GrowpointId, sceneId, 0, x301310_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301310_OnOpen(sceneId,selfId,targetId)
--if IsHaveQuest(sceneId,selfId, 2715) > 0 then
local isHaveMission = IsHaveQuestNM(sceneId,selfId,3039)
		if isHaveMission == 1 then
		if GetItemCount(sceneId,selfId,13030081) == 0 then

		  return 0
		else
    	  	BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"你已经抓到了小螃蟹！")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
			return 1
		end
		else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"河里的石头还是别乱翻的好！")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
    	return 1
    end

end
--end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301310_OnRecycle(sceneId,selfId,targetId)
		local x,y = GetWorldPos ( sceneId, selfId )
		x,y = floor ( x + random ( 1,2 ) ) , floor ( y + random ( 1,2 ) )
		CreateMonster(sceneId,1838, x, y, 1, 0, -1,-1,21,30000)
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301310_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

