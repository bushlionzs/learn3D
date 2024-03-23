--脚本号 300801

--动态变量初始化方法
x300801_g_MissionId 	= 7554
x300801_g_ItemId 		= 13011603
x300801_g_ScriptId 		= 300755
x300801_g_GrowPointType	= 116
x300801_g_ItemCount		= 1


---------------------------------------------------------------------------------------------------
--生成函数
---------------------------------------------------------------------------------------------------
function 		x300801_OnCreate(sceneId,growPointType,x,y)
	--创建
	local ItemBoxId = ItemBoxEnterScene(x,y,x300801_g_GrowPointType,sceneId,0,x300801_g_ItemId)
end


---------------------------------------------------------------------------------------------------
--打开前函数
---------------------------------------------------------------------------------------------------
function	 x300801_OnOpen(sceneId,selfId,targetId)
	if IsHaveQuest(sceneId,selfId, x300801_g_MissionId) > 0 then
		--if GetItemCount(sceneId,selfId,x300801_g_ItemId) < x300801_g_ItemCount then
			return 0
		--else
		--	BeginQuestEvent(sceneId)
		--	AddQuestText(sceneId,"您无法这样做")
		--	EndQuestEvent(sceneId)
		--	DispatchQuestTips(sceneId,selfId)
		--	return 1
		--end
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
function	 x300801_OnRecycle(sceneId,selfId,targetId)
	local x = GetItemBoxWorldPosX(sceneId,targetId)
	local z = GetItemBoxWorldPosZ(sceneId,targetId)
   	
   	local posx = x - 5;
   	local posz = z;
   --	CreateMonster(sceneId,9560, posx, posz, 16,50, -1,-1,21,1000 * 60 *3 )
   	
   	local posx = x;
   	local posz = z - 5;
   --	CreateMonster(sceneId,9560, posx, posz, 16,50, -1,-1,21,1000 * 60 *3 )
   	
   	local posx = x + 5;
   	local posz = z;
   	CreateMonster(sceneId,9560, posx, posz, 16,50, -1,-1,21,1000 * 60 *3 )
	return CallScriptFunction( x300801_g_ScriptId, "OnGetGrowPoint", sceneId, selfId, x300801_g_MissionId, x300801_g_ItemId )
end

---------------------------------------------------------------------------------------------------
--打开后函数
---------------------------------------------------------------------------------------------------
function	x300801_OnProcOver(sceneId,selfId,targetId)

end

function	x300801_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

end
