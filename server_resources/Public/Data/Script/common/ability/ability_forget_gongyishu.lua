
x540015_g_ScriptId = 540015

x540015_g_AbilityName = "波斯工艺术"
x540015_g_MissionName = "遗忘"..x540015_g_AbilityName
x540015_g_ContinueInfo="\t制造系生活技能分为六种：中原草药术、印度珠宝术、蒙古驯马术、突厥锻造术、罗马铸甲术、波斯工艺术。\n\t你最多学习其中三种制造系生活技能。如果你已经学满三种制造技能，又希望学习新的制造技能，可以到我这里遗忘"..x540015_g_AbilityName.."。\n\t遗忘技能后本生活技能相应称号也会消失，你希望遗忘"..x540015_g_AbilityName.."吗？"
x540015_g_TitleId = 86

-- 相关称号任务信息
x540015_g_Title_Quest_ScriptId = 3615

function x540015_ProcEnumEvent( sceneId, selfId, targetId, index )
	
	AddQuestNumText(sceneId, x540015_g_ScriptId, x540015_g_MissionName, 3)
		
end

function x540015_ProcEventEntry( sceneId , selfId , targetId , state , index )
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x540015_g_MissionName)
		AddQuestText(sceneId,x540015_g_ContinueInfo)
	EndQuestEvent()
	--DispatchQuestEventList(sceneId, selfId, targetId)
	DispatchQuestInfo(sceneId,selfId,-1,x540015_g_ScriptId,-1)
	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,0)
	return
end

--********************
--检测接受条件
--**********************************
function x540015_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

function x540015_ProcAccept( sceneId, selfId )

	local nStep = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)

 if 0 == nStep then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"遗忘后技能等级无法恢复,您确定要遗忘波斯工艺术吗?")
		EndQuestEvent()
		DispatchQuestInfo(sceneId,selfId,-1,x540015_g_ScriptId,-1)
		SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID,1)
 elseif 1 == nStep then
	 	local abilityLevel = QueryPlayerAbility( sceneId, selfId, 7 )
		if abilityLevel >0 then
			-- 删除生活技能
			local nRet = DelAbility( sceneId,selfId, 7 )
			if nRet == 1 then
				DeleteTitle(sceneId, selfId, x540015_g_TitleId)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "您遗忘了"..x540015_g_AbilityName)
				DispatchQuestTips(sceneId, selfId)
				EndQuestEvent(sceneId)
				Msg2Player(sceneId,selfId,"您遗忘了"..x540015_g_AbilityName,8,2)
				--TipsToPlayer (sceneId,selfId,"您遗忘了"..x540015_g_AbilityName)
	
				-- 放弃相关称号任务
				if IsHaveQuestNM( sceneId, selfId, x540015_g_Title_Quest_ScriptId) > 0 then
					DelQuest( sceneId, selfId, x540015_g_Title_Quest_ScriptId)
				end
			end
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "您还未学习"..x540015_g_AbilityName)
			DispatchQuestTips(sceneId, selfId)
			EndQuestEvent(sceneId)
			--TipsToPlayer (sceneId,selfId,"您还未学习"..x540015_g_AbilityName)
		end
 end
end