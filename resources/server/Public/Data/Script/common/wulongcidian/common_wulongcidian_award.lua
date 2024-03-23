
x310181_g_scriptId = 310181
x310181_g_GameId = 1019

function x310181_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	if GetGameOpenById(x310181_g_GameId) ~= 1 then
		return
	end
	if GetWeek() ~= 0 then
	   return
	end
    AddQuestNumText(sceneId,x310181_g_scriptId,"我要领取乌龙辞典奖励",3,x310181_g_scriptId);
        
end

function x310181_AddAward(sceneId ,selfId, arg)
	local nExpBonus = GetLevel(sceneId ,selfId)*arg
	AddExp(sceneId, selfId, nExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o获得#R经验"..nExpBonus.."点#o的奖励");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o获得#R经验"..nExpBonus.."点#o的奖励",4,2)
end


function x310181_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )
	local minute =  GetMinOfDay()
	if minute < 17*60+5 then
		BeginQuestEvent(sceneId)	
		AddQuestText(sceneId, "\t请在下午17:05后来领取")						
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end

	local name = GetName(sceneId, selfId)
	local index = 0
	for i=1, WULONGCIDIAN_AWARD_COUNT do
		if WULONGCIDIAN_AWARD_NAME[i] == name then
			index = i
		end
	end

	if index >0 and index <=WULONGCIDIAN_AWARD_COUNT then
		if WULONGCIDIAN_AWARD_Draw[index] == 1 then
			BeginQuestEvent(sceneId)	
			AddQuestText(sceneId, "\t你已经领取过奖励了！")						
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return
		end
	else
		BeginQuestEvent(sceneId)	
		AddQuestText(sceneId, "\t你似乎并没有取得名次！")						
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end

	local r = random(1, 100)
	local item =0
	if idExt == x310181_g_scriptId then 
		if index == 1 then
			WULONGCIDIAN_AWARD_Draw[index] = 1
			BeginQuestEvent(sceneId)	
			AddQuestText(sceneId, "\t你在乌龙辞典中赢得了第一名，获得了乌龙宗师的称号！")						
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			AwardTitle(sceneId,selfId,6)
			x310181_AddAward(sceneId ,selfId, 100000)
		elseif index == 2 then
			WULONGCIDIAN_AWARD_Draw[index] = 1
			BeginQuestEvent(sceneId)	
			AddQuestText(sceneId, "\t你在乌龙辞典中赢得了第二名，获得了乌龙高手的称号！")						
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			AwardTitle(sceneId,selfId,7)
			x310181_AddAward(sceneId ,selfId, 80000)
		elseif index == 3 then
			WULONGCIDIAN_AWARD_Draw[index] = 1
			BeginQuestEvent(sceneId)	
			AddQuestText(sceneId, "\t你在乌龙辞典中赢得了第三名，获得了乌龙强人的称号！")						
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			AwardTitle(sceneId,selfId,8)
			x310181_AddAward(sceneId ,selfId, 50000)
			else
			WULONGCIDIAN_AWARD_Draw[index] = 1
			BeginQuestEvent(sceneId)
			if GetSex(sceneId,selfId) == 0 then
				AddQuestText(sceneId, "\t你在乌龙辞典中获得了乌龙才女的称号！")
			else
				AddQuestText(sceneId, "\t你在乌龙辞典中获得了乌龙才子的称号！")
			end
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			AwardTitle(sceneId,selfId,14)

			x310181_AddAward(sceneId ,selfId, 30000)
		end
	
	end
	
end