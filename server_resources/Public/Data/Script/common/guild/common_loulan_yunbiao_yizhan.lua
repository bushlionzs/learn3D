
--MisDescBegin
x300680_g_ScriptId 					= 	300680                  --脚本ID
x300680_g_MissionKind 				= 	1                       --任务类型
x300680_g_MissionName				= 	"【帮会】神兽驿站"      --任务名称(512)

x300680_g_MissionCompleted			= 	"\t神兽经过休息后，体力更足了，请收下驿站给您的奖励！"  --任务完成信息
x300680_g_MissionInfo				= 	"\t每当帮会护送神兽时，神兽最好在我这里稍做休息。同时在帮主身边的帮众会获得经验奖励，当您完成护送神兽任务时也会获得经验奖励加成。"  	

--MisDescEnd

--奖励
x300680_g_BonusMoney8               =   100  --任务奖励帮贡
x300680_g_GuildExpBonus				=	1
x300680_g_Leader_Index = 5					--帮主在帮会职务中的索引
x300680_g_Exp = 100*3*25*1*1*0.4
x300680_g_LogId = 111
x300680_g_RingMissionIndex = 1				--环任务在主任务中的位置

x300680_g_CountryList = {
							{ countryId = 0 , submitNpcGuid = 124534, misId = 7024, misEndId = 7002 },
							{ countryId = 1 , submitNpcGuid = 127540, misId = 7705, misEndId = 7023 },
							{ countryId = 2 , submitNpcGuid = 130531, misId = 7706, misEndId = 7022 },
							{ countryId = 3 , submitNpcGuid = 133501, misId = 7707, misEndId = 7021 },							
						}

--点击（NPC）
function x300680_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos ~= x300680_g_Leader_Index then			--不是帮主
  		return 0
 	end
	
	local misId = 0
	local misEndId = 0

	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misId = itm.misId
			misEndId = itm.misEndId
			break
		end
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, misEndId); 
	local isFinishing = GetQuestParam( sceneId, selfId,misIndex,x300680_g_RingMissionIndex )
	if isFinishing == 1 then
		return
	end
	
	if IsHaveQuestNM(sceneId, selfId, misId) <= 0 then
		--return
	end
		
	AddQuestNumText(sceneId,misId,x300680_g_MissionName,8)
	
end



--点击（按钮）点击该任务后执行此脚本
function x300680_ProcEventEntry( sceneId, selfId, NPCId,state,nExtIdx)	

	local misId = 0
	local submitNpcGuid = -1

	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misId = itm.misId
			submitNpcGuid = itm.submitNpcGuid
			break
		end
	end
	
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, misId);
	if(bHaveMission > 0) then
		local npcGuid = GetMonsterGUID(sceneId,NPCId)
		if submitNpcGuid == npcGuid then
			x300680_DispatchCompletedInfo( sceneId, selfId, NPCId,misId) --完成任务显示			
		end

	else
		if nExtIdx ~= x300680_g_ScriptId then
			x300680_DispatchMissionInfo( sceneId, selfId, NPCId, misId )	--任务信息显示		
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你没有神兽任务！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId,selfId,NPCId);			
		end

	end
		
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300680_DispatchCompletedInfo( sceneId, selfId, NPCId, misId )
	
	BeginQuestEvent(sceneId)

		--任务完成信息
		AddQuestText(sceneId,"#Y"..x300680_g_MissionName)
		AddQuestText(sceneId,x300680_g_MissionCompleted)
		AddQuestText(sceneId," ")

  		--任务奖励信息

		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300680_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,  ExpBonus);
		end

		--2、帮贡
		-- if x300680_g_BonusMoney8 > 0 then
			-- AddQuestMoneyBonus8(sceneId, x300680_g_BonusMoney8 )
		-- end	
		--帮会经验
		-- if x300680_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x300680_g_GuildExpBonus)
		-- end

	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300680_g_ScriptId, misId);

end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300680_DispatchMissionInfo( sceneId, selfId, NPCId, misId )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x300680_g_MissionName)
		AddQuestText(sceneId,format("%s", x300680_g_MissionInfo))
		AddQuestText(sceneId," ")

		--任务奖励信息
		AddQuestText(sceneId,"\n#Y奖励内容：")
		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300680_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestText(sceneId,"经验值："..ExpBonus.."点")
			--AddQuestExpBonus(sceneId,  ExpBonus);
		end
		
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 300)
			local str = format("天赋值：%d点", refixInhExp)
			AddQuestText(sceneId, str)
		end
		--2、帮贡
		-- if x300680_g_BonusMoney8 > 0 then
			-- AddQuestMoneyBonus8(sceneId, x300680_g_BonusMoney8 )
		-- end	
		--帮会经验
		-- if x300680_g_GuildExpBonus>0 then
			-- AddQuestGuildExpBonus(sceneId,x300680_g_GuildExpBonus)
		-- end
		
	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300680_g_ScriptId,misId);
	
end


function x300680_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	--判断是否帮主
	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos ~= x300680_g_Leader_Index then			
  	
  		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "抱歉，您不是帮主，没有权利领取奖励！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "抱歉，您不是帮主，没有权利领取奖励！"
		Msg2Player(sceneId,selfId,Readme,8,2)
  		return 0
  		
 	end
 	
 	 --判断是否有护兽任务
	local misEndId = 0
	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misEndId = itm.misEndId
			break
		end
	end
	
	if IsHaveQuestNM( sceneId, selfId, misEndId ) == 0 then	
  		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "抱歉，您没有接受护兽任务，没有权利领取奖励！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "抱歉，您没有接受护兽任务，没有权利领取奖励！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
  	--判断神兽是否在有效距离内
	local valid = IsValidGuildBus(sceneId, selfId)
	if valid == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您距离镖车过远，无法提交护送神兽任务！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o您距离镖车过远，无法提交护送神兽任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
 	--判断当日是否已经领取过
 	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME, x300680_g_ScriptId,misEndId,"OnReturn")

end

function x300680_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

	--判断是否已经领取过
	if MissionData == 0 then					--已经领取过了

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您已经领取过了，请改天再来吧！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "很抱歉，您已经领取过了，请改天再来吧！" 
		Msg2Player(sceneId,selfId,Readme,8,2)		
		return
		
	end

	local misEndId = 0
	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misEndId = itm.misEndId
			break
		end
	end
	local misIndex = GetQuestIndexByID(sceneId, selfId, misEndId) 
	local isFinishing = GetQuestParam( sceneId, selfId,misIndex,x300680_g_RingMissionIndex )
	if isFinishing == 1 then
		return
	end
	SetQuestByIndex(sceneId, selfId, misIndex, x300680_g_RingMissionIndex, 1);	
	
	--记录领取状态	
	local GuildID = GetGuildID(sceneId,selfId)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME, 1)
	
 	--帮主及有效距离内的帮众得奖励
	local x,z = GetWorldPos(sceneId,selfId)
	local playerCount =  GetNearCountryCount(sceneId, selfId,x,z,25)  

	for i = 0, playerCount-1 do

		--判断是否同帮
		local humanObjId = GetNearCountryMember(sceneId, selfId,i) 
		if GetGuildID(sceneId, humanObjId) == GuildID then

			--判断是否有护兽任务
			if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	
				--领取奖励
				x300680_GetBonus( sceneId,humanObjId, membercount )
			end

		end

	end

end

function x300680_GetBonus( sceneId, selfId, membercount )	

	--奖励经验
	local level = GetLevel(sceneId, selfId)
	local ExpBonus = x300680_g_Exp * level
	ExpBonus =floor(ExpBonus+0.5)
    if ExpBonus > 0 then
		if GetHp(sceneId, selfId) > 0 then
			AddExp(sceneId, selfId, ExpBonus);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "获得#R经验"..ExpBonus.."点#o的奖励" );
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,"获得#R经验"..ExpBonus.."点#o的奖励",8,2)	
		end
	end
	if GetLevel(sceneId,selfId) >= 80 then
		local refixInhExp = AddInherenceExp(sceneId,selfId,300)
		local str = format("获得#R天赋值%d点#o的奖励", refixInhExp)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,str,8,2)
	end
	--奖励帮贡
    -- if x300680_g_BonusMoney8 > 0 then
		-- AddGuildUserPoint(sceneId,selfId,x300680_g_BonusMoney8)	--增加帮贡
		-- local BonusMoney8 = x300680_g_BonusMoney8
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "获得#R帮贡"..BonusMoney8.."点#o的奖励" );
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- Msg2Player(sceneId,selfId,format("获得#R帮贡"..BonusMoney8.."点#o的奖励", x300680_g_BonusMoney8),8,2)
	-- end

	-- 奖励帮会经验
	-- local bangExp = x300680_g_GuildExpBonus
	-- if bangExp > 0 then
		-- local pos = GetGuildOfficial(sceneId, selfId)
		-- if pos == x300680_g_Leader_Index then
			-- AddGuildExp(sceneId, selfId,100)
			-- Msg2Player(sceneId,selfId,format("帮会获得#R帮会经验100点#G的奖励"),6,2)
		-- end
			-- AddGuildExp(sceneId,selfId,bangExp)
			-- Msg2Player(sceneId,selfId,format("获得#R帮会经验"..bangExp.."点#o的奖励"),8,2)
	-- end

	--交任务写日志
	GamePlayScriptLog(sceneId,selfId,x300680_g_LogId)	
	
	--修改环任务标志
	local misEndId = 0
	for i,itm in x300680_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misEndId = itm.misEndId
			break
		end
	end
		
end


