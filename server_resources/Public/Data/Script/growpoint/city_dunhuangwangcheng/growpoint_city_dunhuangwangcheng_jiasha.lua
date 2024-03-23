--生长点

x301226_g_GrowpointId = 185 --对应生长点ID
x301226_g_ItemIndex = 13030106 --对应收集物品的ID


--生成函数开始************************************************************************
function 	x301226_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301226_g_GrowpointId, sceneId, 0, x301226_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301226_OnOpen(sceneId,selfId,targetId)
--if IsHaveQuest(sceneId,selfId, 2715) > 0 then
local isHaveMission = IsHaveQuestNM(sceneId,selfId,1721)
		if isHaveMission == 1 then
		if GetItemCount(sceneId,selfId,13030106) == 0 then

		  return 0
		else
    	  	BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"你已经获得了木棉袈裟")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
			return 1
		end
		else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"一股恐怖的力量阻止了你！")
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)
    	return 1
    end

end
--end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301226_OnRecycle(sceneId,selfId,targetId)
		--local x,y = GetWorldPos ( sceneId, selfId )
		--x,y = floor ( x + random ( 1,2 ) ) , floor ( y + random ( 1,2 ) )
		CreateMonster(sceneId,1151, 458, 280, 5, 0, -1,-1,21,120000)
		CreateMonster(sceneId,1147, 454, 276, 5, 0, -1,-1,21,120000)
		CreateMonster(sceneId,1147, 461, 276, 5, 0, -1,-1,21,120000)
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301226_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

