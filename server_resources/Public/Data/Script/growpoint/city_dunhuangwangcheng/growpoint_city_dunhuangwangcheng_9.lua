--生长点

x301010_g_GrowpointId = 11 --对应生长点ID
x301010_g_ItemIndex = 13011003 --对应收集物品的ID
x301010_g_MissionId = 2895
x301010_g_Bossid =-1
x301010_g_DemandItem ={{id=13020007,num=1},{id=13020008,num=1},{id=13020009,num=1}}

--生成函数开始************************************************************************
function 	x301010_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301010_g_GrowpointId, sceneId, 0, x301010_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301010_OnOpen(sceneId,selfId,targetId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x301010_g_MissionId)
		if IsHaveQuest(sceneId,selfId, x301010_g_MissionId) > 0 then
			if GetItemCount(sceneId,selfId,x301010_g_DemandItem[3].id) >= x301010_g_DemandItem[3].num then
					return 0
			else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"乌黑的石像，散发出邪恶的光辉，似乎需要一颗钻石才能开启它。")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId);
					return 1
			end
		end
		return 1
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301010_OnRecycle(sceneId,selfId,targetId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x301010_g_MissionId)
		if IsHaveQuest(sceneId,selfId, x301010_g_MissionId) > 0 then
						DelItem( sceneId,selfId,x301010_g_DemandItem[3].id, x301010_g_DemandItem[3].num )
						BeginAddItem(sceneId)
						AddItem( sceneId, x301010_g_DemandItem[1].id, x301010_g_DemandItem[1].num )
    				EndAddItem(sceneId,selfId)
    				AddItemListToPlayer(sceneId,selfId)
    				BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"乌黑的石像张开了嘴吐出一颗乌黑的珠子。")
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId);
						return 0
		end
		return 0

end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301010_OnProcOver(sceneId,selfId,targetId)
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

