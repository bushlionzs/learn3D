x300803_g_scriptId  = 300803
x300803_g_Impact1   = -1 --效果ID
x300803_g_Impact2   = -1 --不用

x300803_g_MissionId 	= 7558			--任务ID
x300803_g_ItemId 		= 13011605		--物品ID
x300803_g_ScriptId 		= 300759		--脚本ID

x300803_g_UseSceneID	= 350			--使用物品场景
x300803_g_UsePosX		= 122			--使用物品位置
x300803_g_UsePosZ		= 58


--**********************************
--事件交互入口
--**********************************
function x300803_ProcEventEntry( sceneId, selfId, bagIndex )
--SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300803_g_Impact1, 0); --特效
	local x,z = GetWorldPos (sceneId,selfId)
	if(x300803_g_UseSceneID == sceneId and abs(x300803_g_UsePosX - x) < 30 and abs(x300803_g_UsePosZ - z) < 30) then
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"此处不能使用该物品！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;
	end
	
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300803_g_MissionId);
	if(bHaveMission > 0) then
	    local misIndex = GetQuestIndexByID(sceneId, selfId, x300803_g_MissionId);
		local bDone = GetQuestParam(sceneId, selfId, misIndex, 7);
		if(bDone == 0) then
			return CallScriptFunction( x300803_g_ScriptId, "OnPositionUseItem", sceneId, selfId, x300803_g_MissionId, x300803_g_ItemId );
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"您已经完成这个任务")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您没有这个任务")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
	return 0;
end


function x300803_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x300803_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x300803_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300803_OnDeplete( sceneId, selfId )

	return 1
end

function x300803_OnActivateOnce( sceneId, selfId )
end

function x300803_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
