--帮会银票脚本

--脚本号
x300673_g_scriptId 		= 300673 
--物品号
x300673_g_ItemID		= 13030128
--帮会跑钱任务id
x300673_g_MissionId		= 7026
x300673_g_MissionId1	= 7027
x300673_g_MissionId2	= 7028
x300673_g_MissionId3	= 7029

--**********************************
--事件交互入口
--**********************************
function x300673_ProcEventEntry( sceneId, selfId, bagIndex )

	if IsHaveQuestNM( sceneId, selfId, x300673_g_MissionId ) == 1 then	-- 如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300673_g_MissionId)
		local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
		local msg = "帮会银票内的金钱数额：#G"..nMoney
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,msg,8,2)	
		return	
	elseif IsHaveQuestNM( sceneId, selfId, x300673_g_MissionId1 ) == 1 then	-- 如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300673_g_MissionId1)
		local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
		local msg = "帮会银票内的金钱数额：#G"..nMoney
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,msg,8,2)	
		return	
	elseif IsHaveQuestNM( sceneId, selfId, x300673_g_MissionId2 ) == 1 then	-- 如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300673_g_MissionId2)
		local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
		local msg = "帮会银票内的金钱数额：#G"..nMoney
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,msg,8,2)	
		return	
	elseif IsHaveQuestNM( sceneId, selfId, x300673_g_MissionId3 ) == 1 then	-- 如果有这个任务
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300673_g_MissionId3)
		local nMoney = GetQuestParam( sceneId, selfId, misIndex, 0)
		local msg = "帮会银票内的金钱数额：#G"..nMoney
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, msg);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,msg,8,2)	
		return	
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t你还没有接受帮会跑商任务");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"你还没有接受帮会跑商任务",8,2)	
		return
	end

end

function x300673_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持
end
