
x310001_g_ScriptId = 310001
x310001_g_MissionName = "【领取战神加护】" 
x310001_g_ContinueInfo="\t当今四处怪物横行，要去迷宫的话更要小心为上。\n\t我可以为你祈求#G战神加护#W，虽说不能帮你强攻御敌，但好歹能让你精神抖擞，让你在战斗中获得更多的收益吧。\n\t#R注意：#G战神加护#W仅在#G外高加索、乌孙古道、葱岭西麓、大同路、济宁路、保定路、地下粮仓、仙人谷#W有效。\n\t每次领取将获得#G1小时#W的在该当场景中的#R经验加成#W。战神加护的时间#G可以叠加#W，也可以#G和别的经验加成奖励共同作用#W。\n\t但#R每天你只可以领取1次#W，请合理安排。"

x310001_g_SuccessInfo="你领取了一小时的战神加护"
--x310001_g_MD_AcceptTime = 210
--x310001_g_MD_Rounds = 211
x310001_g_LevelLimit = 20
x310001_g_ImpactId = 7041

x310001_g_RoundLimit= 1


x310001_SceneList = {2,3,4,5,6,7,8,9,10,11,86,87,89,186,187,189,286,287,289,386,387,389,73,173,273,373,74,174,274,374,68,168,268,368}

--列举事件
--**********************************

function x310001_NextDayReset(sceneId, selfId)
	local lastDay = GetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_DATE[1], MD_MIGONG_SHUANGBEI_DATE[2], MD_MIGONG_SHUANGBEI_DATE[3])

	if lastDay ~= GetDayOfYear() then
		SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_DATE[1], MD_MIGONG_SHUANGBEI_DATE[2], MD_MIGONG_SHUANGBEI_DATE[3], 0)
		SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3], 0)
	end
end

function x310001_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	local country = GetCurCountry(sceneId, selfId)
	local nDefaultCamp = GetSceneCamp( sceneId )-16

	if GetLevel( sceneId, selfId ) < x310001_g_LevelLimit then 
		return
	end
	if country == nDefaultCamp then 
		x310001_NextDayReset(sceneId, selfId)
		AddQuestNumText(sceneId, x310001_g_ScriptId, x310001_g_MissionName, 3, 1)
	else 
			return
	end
	
end

function x310001_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310001_g_MissionName)
		AddQuestText(sceneId,x310001_g_ContinueInfo)
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x310001_g_ScriptId, -1)

end

--检测接受条件

--**********************************

function x310001_ProcAcceptCheck(sceneId, selfId, NPCId)
	local curRounds = GetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3])

	if curRounds >= x310001_g_RoundLimit then
		local str = "你已经领取过战神加护了，请明天再来";
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,str,8,2)
		return 0
	end

	if GetLevel( sceneId, selfId ) < x310001_g_LevelLimit then 
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "等级不够。");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"等级不够。",8,2)
		return 0
	end


	return 1
end

function x310001_ProcAccept( sceneId, selfId )
	local rounds = GetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3])

	local today = GetDayOfYear() 

	if IsHaveSpecificImpact(sceneId, selfId,x310001_g_ImpactId) > 0 then
		local lastContinuance = GetImpactContinuanceByDataIndex(sceneId, selfId, x310001_g_ImpactId) - GetImpactContinuanceElapsed(sceneId, selfId, x310001_g_ImpactId) 
		if lastContinuance >= 0 then
			SetImpactContinuanceByDataIndex( sceneId, selfId, x310001_g_ImpactId, lastContinuance+60*60*1000 )
			ResetImpactContinuanceElapsed(sceneId, selfId, x310001_g_ImpactId)

			SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_DATE[1], MD_MIGONG_SHUANGBEI_DATE[2], MD_MIGONG_SHUANGBEI_DATE[3], today)
			SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3], rounds+1)

			RefreshImpactByDataIndex(sceneId, selfId,x310001_g_ImpactId)
		end
	else
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x310001_g_ImpactId, 0)

		SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_DATE[1], MD_MIGONG_SHUANGBEI_DATE[2], MD_MIGONG_SHUANGBEI_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_MIGONG_SHUANGBEI_ROUNDS[1], MD_MIGONG_SHUANGBEI_ROUNDS[2], MD_MIGONG_SHUANGBEI_ROUNDS[3], rounds+1)
	end
	
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, x310001_g_SuccessInfo);
	EndQuestEvent(sceneId);
	DispatchQuestTips(sceneId,selfId);
	Msg2Player(sceneId,selfId,x310001_g_SuccessInfo,8,2)
	
	x310001_EnterScene(sceneId,selfId)
	
end

function x310001_EnterScene(sceneId, selfId)
	local sign=0;
	for i, item in x310001_SceneList do
		if sceneId == item then sign = 1 break end
	end

	if sign == 1 then
		if IsHaveSpecificImpact( sceneId, selfId, x310001_g_ImpactId ) > 0 then
			--local curMult = GetWanFaExpMult(sceneId, selfId)
			SetWanFaExpMult( sceneId, selfId, 0.5 )
			
		end
	else
        SetWanFaExpMult( sceneId, selfId, 0 )
    end
end