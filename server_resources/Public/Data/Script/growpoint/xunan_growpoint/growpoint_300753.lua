--脚本号 300800

--动态变量初始化方法
x300800_g_MissionId 	= 7551
x300800_g_ItemId 		= 13011602
x300800_g_ScriptId 		= 300752
x300800_g_GrowPointType	= 115
x300800_g_ItemCount		= 1


---------------------------------------------------------------------------------------------------
--生成函数
---------------------------------------------------------------------------------------------------
function 		x300800_OnCreate(sceneId,growPointType,x,y)
	--创建
	local ItemBoxId = ItemBoxEnterScene(x,y,x300800_g_GrowPointType,sceneId,0,x300800_g_ItemId)
end


---------------------------------------------------------------------------------------------------
--打开前函数
---------------------------------------------------------------------------------------------------
function	 x300800_OnOpen(sceneId,selfId,targetId)
	if IsHaveQuest(sceneId,selfId, x300800_g_MissionId) > 0 then
		if GetItemCount(sceneId,selfId,x300800_g_ItemId) < x300800_g_ItemCount then
			return 0
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"您无法这样做")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			return 1
		end
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您没有这个任务")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 1
	end
end

---------------------------------------------------------------------------------------------------
--回收函数
---------------------------------------------------------------------------------------------------
function	 x300800_OnRecycle(sceneId,selfId,targetId)
     return CallScriptFunction( x300800_g_ScriptId, "OnGetGrowPoint", sceneId, selfId, x300800_g_MissionId, x300800_g_ItemId )
end

---------------------------------------------------------------------------------------------------
--打开后函数
---------------------------------------------------------------------------------------------------
function	x300800_OnProcOver(sceneId,selfId,targetId)

end

function	x300800_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
