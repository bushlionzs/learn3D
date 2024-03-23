
--MisDescBegin
x300608_g_ScriptId 					= 	300608                  --脚本ID

x300608_g_MissionKind 				= 	1                       --任务类型
x300608_g_LevelLess					= 	20                      --任务最小等级  <=0 表示不限制
x300608_g_MissionName				= 	"【帮会】帮会神兽"           --任务名称(512)

x300608_g_MissionTarget				= 	"  护送神兽经过@npc_124534中转后到达@npc_125514处"          --任务目标
x300608_g_MissionInfo				= 	"\t帮主带领帮会成员，每天可在王城参加一次【帮会】帮会神兽任务。\n\t帮主需要在帮会任务发布人处缴纳#G10两现银#W才能接受此任务。帮会成员只需此时在帮主周围，便可自动接到任务，进入护送神兽状态。\n\t在护送神兽过程中，神兽只跟随帮主移动，如帮主离神兽过远，神兽会#G停止前进#W。如果神兽受到袭击并死亡，帮主的#G押金#W将被对方抢走，全体成员#G任务失败#W。\n\t帮主离开神兽一段时间或掉线，神兽消失，所有人#G任务失败#W。\n\t由于路途遥远，神兽中途需要休息，帮主在@npc_124534处点击#R神兽驿站#W按扭，当前在驿站周围的帮众都会获得经验奖励。并且在最后完成护兽任务时都会获得经验加成的奖励。\n\t顺利护送神兽到达指定地点，帮主可得到返还的押金和#G巨额经验#W，参与护送的帮会成员得到#G巨额经验#W。\n\t帮主到达指定地点提交任务，此时只有帮主周围并且已经参与护送的帮会成员才能完成任务并获得#G巨额奖励#W，同时帮会增加100点帮会经验#W。当帮主发布#G护兽令#W时2小时内回复任务可获得翻倍奖励（经验，帮贡）和2点使命点！"            --任务信息
x300608_g_ContinueInfo				= 	"神兽乃祥瑞之兽，我在等待它的降临"  --任务继续信息
x300608_g_MissionCompleted			= 	"恭喜您顺利完成任务！这是您应得的奖励，请收下！"  --任务完成信息
x300608_g_MissionHelp				=	"\t接受任务后，会在帮主屏幕正下方出现辅助图标：#R上\下车#W和护送#G成员列表。帮主通过列表踢除表内成员，解除其护送神兽状态。当帮主提交任务时，周围参与护送的帮众越多，您所获得的奖励也会更多。随着您所在帮会等级的提高，你获得的奖励也会相应增加。"          --任务提示信息
x300608_g_ExtTarget		=	{ {type=20,n=1,target="护送神兽"}} --目标
 
--MisDescEnd


--奖励
x300608_g_BonusMoney8               =   150  --任务奖励帮贡
x300608_g_GuildExpBonus				=	1
--x300608_g_BangExp 					=	2
x300608_SubmitNPCGUID				= 125514 --交任务NPC GUID
x300608_g_BusScriptId = 300609
x300608_g_Leader_Index = 5		--帮主在帮会职务中的索引
x300608_g_MissionId  = 7002
x300608_g_CostMoney = 10000
x300608_g_Exp = 100*3*25*1*1*0.4

x300608_g_RingMissionIndex = 1	--环任务在主任务中的位置

x300608_g_CountryList = {
							{ countryId = 0 , scriptId = 300608, misId = 7002 },
							{ countryId = 1 , scriptId = 300871, misId = 7023 },
							{ countryId = 2 , scriptId = 300869, misId = 7022 },
							{ countryId = 3 , scriptId = 300867, misId = 7021 },							
						}

function x300608_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--初始化全局变量
	--RD_GUILDCONTEND_KILL_LEADER = 1
	SetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_LEADER,1)

	if GetGuildID(sceneId, selfId) == -1 then
		--未加入帮会
		return 0
	end
	
	if GetCurCountry(sceneId,selfId) ~=0 then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x300608_g_MissionId ) == 0 then	-- 如果没有这个任务
		local state = GetQuestStateNM(sceneId,selfId,targetId,x300608_g_MissionId)
		AddQuestNumText(sceneId,x300608_g_MissionId,x300608_g_MissionName,8);
		return 1
	end
	return 0
end


--选中任务
function x300608_ProcEventEntry( sceneId, selfId, NPCId, MissionId,nExtIdx )

	if GetGuildID(sceneId, selfId) == -1 then
		--未加入帮会
		return 0
	end

	if GetCurCountry(sceneId,selfId) ~=0 then
		return
	end

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, MissionId);
	if(bHaveMission > 0) then
		local npcGuid = GetMonsterGUID(sceneId,NPCId)
		if x300608_SubmitNPCGUID == npcGuid then
			x300608_DispatchCompletedInfo( sceneId, selfId, NPCId) --完成任务显示			
		end

	else
		if nExtIdx ~= x300608_g_ScriptId then
			x300608_DispatchMissionInfo( sceneId, selfId, NPCId )	--任务信息显示	
			--RD_GUILDCONTEND_KILL_LEADER = 2
			SetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_LEADER,2)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"你没有此任务！")
			EndQuestEvent()
			DispatchQuestEventList(sceneId,selfId,NPCId);			
		end

	end

end


--**********************************
--接受
--**********************************
function x300608_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	if GetGuildID(sceneId, selfId) == -1 then
		--未加入帮会
		return 0
	end
	
	if GetCurCountry(sceneId,selfId) ~=0 then
		return
	end
	if IsHideName(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"抱歉，蒙面状态不能接此任务。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end
			
	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"可接任务数量已满")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end

	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos ~= x300608_g_Leader_Index then			--不是帮主
  		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "抱歉，您不是帮主，没有权利发起护送神兽！");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o抱歉，您不是帮主，没有权利发起护送神兽！"
		Msg2Player(sceneId,selfId,Readme,8,2)
  		return 0
 	end

	if IsTeamFollow(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "组队跟随状态下不可以接帮会护送任务!");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o组队跟随状态下不可以接帮会护送任务！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
	local BusID = IsBusMember(sceneId, selfId);
	if(BusID == 1) then
		local strText = "您已处于护送状态，无法领取新的护送任务！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o您已处于护送状态，无法领取新的护送任务！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
			
 	local level = GetLevel(sceneId,selfId)
	if level < x300608_g_LevelLess then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，30级以后才能接受【帮会】帮会神兽任务！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o很抱歉，30级以后才能接受【帮会】帮会神兽任务！"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	--if RD_GUILDCONTEND_KILL_LEADER == 3 then
		if GetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_LEADER) == 3 then
	 		GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, x300608_g_ScriptId,MissionId,"OnReturn")
	 	end
 	
	--if RD_GUILDCONTEND_KILL_LEADER == 2 then	
		if GetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_LEADER) == 2 then
			BeginQuestEvent(sceneId)
					--RD_GUILDCONTEND_KILL_LEADER = 3
					SetPlayerRuntimeData(sceneId,selfId,RD_GUILDCONTEND_KILL_LEADER,3)
					AddQuestText(sceneId,"#Y【帮会】帮会神兽#W\n  \n\t当您领取神兽时，帮会成员需在您的身边才可接收到接受任务的提示；在您完成任务时，只有在您身边的帮会成员才能完成任务获得奖励。\n \n#G您确定要领取帮会神兽吗?")
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, targetId, x300608_g_ScriptId, x300608_g_MissionId)
		end
	
	
	
 	--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, x300608_g_ScriptId,MissionId,"OnReturn")

end
function x300608_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)

	if GetGuildID(sceneId, selfId) == -1 then
		--未加入帮会
		return 0
	end

 local curTime = GetCurrentTime()
	local isMultiple = 0
	if curTime - MissionData < 2*60*60 then
		isMultiple = 1
	end
	local membercount = MissionId
	local raingMisFinishing = targetId
	x300608_GetBonus( sceneId,selfId, isMultiple, membercount,raingMisFinishing )
end

---------------------------------------------------------------------------------------------------
function x300608_GetBonus( sceneId, selfId, isMultiple, membercount, raingMisFinishing )	
--奖励经验
	
	local exExp = 1
	if raingMisFinishing == 1 then
		exExp = 1.6
	else 
		exExp = 1
	end
	
	local level = GetLevel(sceneId, selfId)
	--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
	local ExpBonus = x300608_g_Exp * level * exExp
	ExpBonus =floor(ExpBonus+0.5)
	local GuildLevel = GetGuildSimpleData( GetGuildID( sceneId, selfId ) )--得到帮会简单数据(等级) 
    if ExpBonus > 0 then
		if GetHp(sceneId, selfId) > 0 then
			AddExp(sceneId, selfId, ExpBonus);
			--AddGuildMerit(sceneId, selfId,1)
	  		local Readme = "您完成了任务：【帮会】帮会神兽#r获得#R经验"..ExpBonus.."点#o的奖励" 
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "您完成了任务：【帮会】帮会神兽" );
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "获得#R经验"..ExpBonus.."点#o的奖励" );
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			DispatchQuestTips(sceneId,selfId)
			-- BeginQuestEvent(sceneId)
			-- AddQuestText(sceneId, "获得#R帮会功德1点#o的奖励" );
			-- EndQuestEvent(sceneId)
			-- DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
			if GetLevel(sceneId,selfId) >= 80 then
				local refixInhExp = AddInherenceExp(sceneId,selfId,400)
				local str = format("获得#R天赋值%d点#o的奖励", refixInhExp)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, str);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,str,8,2)
			end
		end
		if isMultiple == 1 then
			local ExpBonus1 = ceil (x300608_g_Exp * level*3) * exExp
			local Exp3 = ceil (x300608_g_Exp * level*3 ) * exExp
			local ExpBonus2 = ceil (x300608_g_Exp * level*2) * exExp
			local pos = GetGuildOfficial(sceneId, selfId)
			local text3 = "获得#R使命点2点#o的奖励"
				AddGuildShiMing(sceneId, selfId,2)
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, text3);
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,text3,8,2)
			if pos == 5 then
				AddExp(sceneId, selfId, ExpBonus1);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..Exp3.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..Exp3.."点#o的奖励",8,2)
			elseif pos == 4 then
				AddExp(sceneId, selfId, ExpBonus2);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus2.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..ExpBonus2.."点#o的奖励",8,2)
			else
				AddExp(sceneId, selfId, ExpBonus);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R经验"..ExpBonus.."点#o的奖励",8,2)
			end
		end
		if GuildLevel == 1 then
				if membercount >= 1  then
					if membercount>=30 then
						membercount=30
					end
				ExpBonus3 = format(ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus3.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("护送人数增加额外获得#R经验"..ExpBonus3.."点#o的奖励"),8,2)
			end
		end
		if 	GuildLevel == 2 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300608_g_Exp* level * 0.25 )
			if membercount >= 1  then
					if membercount>=40 then
						membercount=40
					end
				ExpBonus3 = format(ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus3.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("护送人数增加额外获得#R经验"..ExpBonus3.."点#o的奖励"),8,2)
			end
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("帮会等级2级额外获得#R经验"..exp.."点#o的奖励"),8,2)
		end
		if 	GuildLevel == 3 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300608_g_Exp * level *0.5 )
			if membercount >= 1  then
					if membercount>=50 then
						membercount=50
					end
				ExpBonus3 =format( ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus3.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("护送人数增加额外获得#R经验"..ExpBonus3.."点#o的奖励"),8,2)
			end
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("帮会等级3级额外获得#R经验"..exp.."点#o的奖励"),8,2)
		end
		if 	GuildLevel == 4 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300608_g_Exp * level * 0.75 )
			if membercount >= 1  then
					if membercount>=60 then
						membercount=60
					end
				ExpBonus3 =format( ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus3.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)	
				Msg2Player(sceneId,selfId,format("护送人数增加额外获得#R经验"..ExpBonus3.."点#o的奖励"),8,2)
			end
			AddExp(sceneId, selfId, exp);	
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)	
			Msg2Player(sceneId,selfId,format("帮会等级4级额外获得#R经验"..exp.."点#o的奖励"),8,2)
		end
		if 	GuildLevel == 5 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300608_g_Exp* level *1 )
			if membercount >= 1  then
					if membercount>=70 then
						membercount=70
					end
				ExpBonus3 =format( ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus3.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,format("护送人数增加额外获得#R经验"..ExpBonus3.."点#o的奖励"),8,2)
			end
			AddExp(sceneId, selfId, exp);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,format("帮会等级5级额外获得#R经验"..exp.."点#o的奖励"),8,2)
		end
		if 	GuildLevel == 6 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300608_g_Exp* level *1.25 )
			if membercount >= 1  then
					if membercount>=70 then
						membercount=70
					end
				ExpBonus3 =format( ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus3.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,format("护送人数增加额外获得#R经验"..ExpBonus3.."点#o的奖励"),8,2)
			end
			AddExp(sceneId, selfId, exp);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,format("帮会等级6级额外获得#R经验"..exp.."点#o的奖励"),8,2)
		end
		if 	GuildLevel == 7 then
			local level = GetLevel(sceneId, selfId)
			local exp = ceil (x300608_g_Exp* level *1.5 )
			if membercount >= 1  then
					if membercount>=70 then
						membercount=70
					end
				ExpBonus3 =format( ExpBonus*(membercount/100))
				AddExp(sceneId, selfId, ExpBonus3);	
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "额外获得#R经验"..ExpBonus3.."点#o的奖励");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,format("护送人数增加额外获得#R经验"..ExpBonus3.."点#o的奖励"),8,2)
			end
			AddExp(sceneId, selfId, exp);
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "额外获得#R经验"..exp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,format("帮会等级7级额外获得#R经验"..exp.."点#o的奖励"),8,2)
		end
	end


	--奖励帮贡
    if x300608_g_BonusMoney8 > 0 then
		AddGuildUserPoint(sceneId,selfId,x300608_g_BonusMoney8)	--增加帮贡
		local BonusMoney8 = x300608_g_BonusMoney8
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "获得#R帮贡"..BonusMoney8.."点#o的奖励" );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,format("获得#R帮贡"..BonusMoney8.."点#o的奖励", x300608_g_BonusMoney8),8,2)
		if isMultiple == 1 then
			local pos = GetGuildOfficial(sceneId, selfId)
				if pos == 5 then
					AddGuildUserPoint(sceneId,selfId,450)	--增加帮贡
					local BonusMoney8 = x300621_g_BonusMoney8
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R帮贡450点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R帮贡450点#o的奖励",8,2)
				elseif pos == 4 then
					AddGuildUserPoint(sceneId,selfId,300)	--增加帮贡
					local BonusMoney8 = x300621_g_BonusMoney8
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R帮贡300点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,"帮会多倍任务额外获得#R帮贡300点#o的奖励",8,2)
				else
					AddGuildUserPoint(sceneId,selfId,150)	--增加帮贡
					local BonusMoney8 = x300621_g_BonusMoney8
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "额外获得#R帮贡150点#o的奖励");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("帮会多倍任务额外获得#R帮贡150点#o的奖励", x300621_g_BonusMoney8),8,2)
				end
		end
	end
	-- 奖励帮会经验
	local bangExp = x300608_g_GuildExpBonus
	if bangExp > 0 then
		local pos = GetGuildOfficial(sceneId, selfId)
		if pos == x300608_g_Leader_Index then
			AddGuildExp(sceneId, selfId,100)
			Msg2Player(sceneId,selfId,format("护兽成功，帮会获得#R帮会经验100点#G的奖励"),6,2)
		end
		--local gongde = GetGuildMerit(sceneId, selfId)
		--if 	gongde >= 5 then
			AddGuildExp(sceneId,selfId,bangExp)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "获得#R帮会经验"..bangExp.."点#o的奖励");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)			
			Msg2Player(sceneId,selfId,format("获得#R帮会经验"..bangExp.."点#o的奖励"),8,2)
		--else
			-- BeginQuestEvent(sceneId)
			-- AddQuestText( sceneId, "很抱歉，帮会功德低于5点，不能获得帮会经验。" )
			-- EndQuestEvent( sceneId )
			-- DispatchQuestTips( sceneId, selfId )
			-- Msg2Player(sceneId,selfId,"很抱歉，帮会功德低于5点，不能获得帮会经验。",8,2)
		-- end
	end
--返回押金
	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos == x300608_g_Leader_Index then			--是帮主
		if x300608_g_CostMoney > 0 then
			AddMoney( sceneId , selfId ,0, x300608_g_CostMoney )
			local readme="获得#R返还押金10两#o"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "获得#R返还押金10两#o" );
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player( sceneId,selfId,readme,8,2 )
		end 
 	end
	--交任务写日志
	GamePlayScriptLog(sceneId,selfId,12)
	
	CallScriptFunction( 300638, "SaveGuildYunBiaoMD", sceneId,selfId )	
end


--完成任务
--返回1代表成功，0代表交任务失败
function x300608_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if GetGuildID(sceneId, selfId) == -1 then
		--未加入帮会
		return 0
	end

	-- local pos = GetGuildOfficial(sceneId, selfId)
  	-- if pos ~= x300608_g_Leader_Index then			--不是帮主
  		-- return 0
 	-- end
 	
 	if GetCurCountry(sceneId,selfId) ~=0 then
		return
	end
 	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- 如果没这个任务直接退出
		return 0
	end

    local pos = GetGuildOfficial(sceneId, selfId)
  	if pos ~= x300608_g_Leader_Index then			--不是帮主
	  	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您不是帮主无法回复【帮会】帮会神兽任务！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o您不是帮主无法回复【帮会】帮会神兽任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
 	end

    --镖车是否存在
	local valid = IsValidGuildBus(sceneId, selfId)
	if valid == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您距离镖车过远，无法提交【帮会】帮会神兽任务！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o您距离镖车过远，无法提交【帮会】帮会神兽任务！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
	SubmitGuildConvoyQuest(sceneId, selfId)
 	local GuildID = GetGuildID(sceneId,selfId)
	local CurDaytime = GetDayTime()						--当前时间(天)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)

	return 0
end


function x300608_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, x300608_g_MissionId ) == 0 then	-- 如果没有这个任务
		return
	end

	if npcGuid == x300608_SubmitNPCGUID then	--点击的NPC的名字和任务中NPC的名字相同，场景也判断过了
		local state = GetQuestStateNM(sceneId,selfId,npcId,x300608_g_MissionId)
		AddQuestNumText( sceneId, x300608_g_MissionId,x300608_g_MissionName, 7,x300608_g_ScriptId ) -- 显示任务信息
	end
end


--********************************************************************
--清除帮会护送任务数据
--********************************************************************
function x300608_OnGuildConvoyClearMemberQuest( sceneId, selfId,state )

	local misId = 0
	local scriptId = 0

	for i,itm in x300608_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misId = itm.misId
			scriptId = itm.scriptId
			break
		end
	end
	
	if IsHaveQuestNM( sceneId, selfId, misId ) == 0 then	-- 如果没有这个任务
		return
	end
	local str = "你放弃了【帮会】帮会神兽任务，任务失败!"
	if state == 0 then				--帮会成员主动放弃
		str = "你放弃了【帮会】帮会神兽任务，任务失败!"
	elseif state == 1 then			--帮主踢人
		str = "由于帮主将你踢出了护送神兽队伍，【帮会】帮会神兽任务失败!"
	elseif state == 2 then			--帮主放弃
		str = "由于帮主放弃了【帮会】帮会神兽任务，任务失败!"
		local pos = GetGuildOfficial(sceneId, selfId)
		if pos == x300608_g_Leader_Index then			--是帮主
			local GuildID = GetGuildID(sceneId,selfId)
			local CurDaytime = GetDayTime()						--当前时间(天)
			SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
		end
	elseif state == 3 then			--禅让
		str = "由于帮主禅让了职位，【帮会】帮会神兽任务失败!"
		local GuildID = GetGuildID(sceneId,selfId)
		local CurDaytime = GetDayTime()						--当前时间(天)
		SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	elseif state == 4 then			--帮会解散
		str = "由于帮会被解散，【帮会】帮会神兽任务失败!"
	elseif state == 5 then			--BUS死亡
		str = "由于神兽死亡，【帮会】帮会神兽任务失败!"
	elseif state == 6 then			--BUS等待超时
		str = "由于帮主离开护送目标时间过久，护送目标消失，任务失败！"
	elseif state == 7 then			--BUS生命超时
		str = "由于神兽生命超时，【帮会】帮会神兽任务失败!"
	elseif state == 11 then			--交任务时离镖车太远
		str = "由于你离开神兽太远，你无法获得奖励!"
	elseif state == 17 then			--帮主被弹劾
		str = "由于弹劾帮主成功，帮主位置发生变化，【帮会】帮会神兽任务失败!"
		local GuildID = GetGuildID(sceneId,selfId)
		local CurDaytime = GetDayTime()						--当前时间(天)
		SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	elseif state == 18 then			--上线删除镖车
		str = "由于神兽死亡，【帮会】帮会神兽任务失败!"
		local GuildID = GetGuildID(sceneId,selfId)
		local CurDaytime = GetDayTime()						--当前时间(天)
		SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	end

	if state>=0 and state<=7 or state == 11 or state ==17 or state ==18 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, str)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,str,8,2)
	end

	local ret = DelQuest( sceneId, selfId, misId  )
	if ret == 1 then
		--Msg2Player( sceneId, selfId, "#R你已经放弃["..MissionName.."]任务", MSG2PLAYER_PARA )
	else
		--扣除任务物品失败处理
	end
	
end     


--********************************************************************
--提交玩家帮会护送任务：给奖励
--********************************************************************
function x300608_OnGuildConvoySubmitQuest( sceneId, selfId )

	local misId = 0
	local scriptId = 0

	for i,itm in x300608_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misId = itm.misId
			break
		end
	end
	
	local misIndex = GetQuestIndexByID(sceneId, selfId, misId); 
	
	--得到环任务状态
	local raingMisFinishing = GetQuestParam( sceneId, selfId,misIndex,x300608_g_RingMissionIndex )

	--清除任务数据  
	--GetQuestNameNM( sceneId, selfId, MissionId )
	if DelQuest( sceneId, selfId, misId  ) < 1 then
		return 
	end

    -- 增加活跃度
    local id = GetGuildID( sceneId, selfId)
    if id ~= -1 then
        AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM5) )
    end

	CallScriptFunction( 256264, "Finishhss", sceneId, selfId)
	CallScriptFunction( 256265, "Finishhss", sceneId, selfId)
	CallScriptFunction( 256266, "Finishhss", sceneId, selfId)
	CallScriptFunction( 256267, "Finishhss", sceneId, selfId)
	local membercount = GetBusEscortMemberNum(sceneId,selfId)
	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_HUSHOU, x300608_g_ScriptId,membercount,"OnReturn1",raingMisFinishing)
end


--********************************************************************
--放弃
--********************************************************************
function x300608_ProcQuestAbandon( sceneId, selfId, MissionId )

	AbandonGuildConvoyQuest(sceneId, selfId,0)
	
--	local pos = GetGuildOfficial(sceneId, selfId)
--  	if pos == x300608_g_Leader_Index then			--是帮主
--  		local GuildID = GetGuildID(sceneId,selfId)
--		SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_STATE, -1)
-- 	end
 	
end

function x300608_ClearBusMission( sceneId, selfId )
	AbandonGuildConvoyQuest(sceneId, selfId, 18)
end

function x300608_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)


	local CurDaytime = GetDayTime()						--当前时间(天)
		
	if MissionData == CurDaytime then					--上次发布的时间是今天
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，今天您的帮会已护送过神兽了，请改天再来吧！")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "#o很抱歉，今天您的帮会已护送过神兽了，请改天再来吧！" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		--DispatchQuestEventList(sceneId, selfId, -1)
	else
		local CurrMoney = GetMoney(sceneId , selfId ,0)
		if CurrMoney < x300608_g_CostMoney then
		    BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "您身上的现银不足！");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "#o很抱歉，您包裹中的现银不够支付押金，无法接取任务！" 
			Msg2Player(sceneId,selfId,Readme,8,2)
			return
		end

	
	    local BusID = CallScriptFunction( x300608_g_BusScriptId, "OnCreateBus", sceneId, selfId,MissionId )
		--if BusID ~= -1 then
		--	AcceptGuildConvoy( sceneId, selfId,BusID )
		--end
		
	end
	
	--DispatchQuestEventList(sceneId, selfId, -1)

end


--********************************************************************
--接受
--********************************************************************
function x300608_ProcAccept( sceneId, selfId )	
	
	if GetGuildID(sceneId, selfId) == -1 then
		--未加入帮会
		return 0
	end
	
	local pos = GetGuildOfficial(sceneId, selfId)
  	if pos == x300608_g_Leader_Index then			--是帮主
		
		local num = CostMoney( sceneId , selfId ,0, x300608_g_CostMoney,301 )--成功返回1 失败返回-1
		if num == -1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "接取任务失败！");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "#o很抱歉，您包裹中的现银不够支付押金，无法接取任务！" 
			Msg2Player(sceneId,selfId,Readme,8,2)
			return
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "您接受了任务：【帮会】帮会神兽")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			local Readme = "您接受了任务：【帮会】帮会神兽#r扣除您#R10#W#o两现银做为押金！" 
			Msg2Player(sceneId,selfId,Readme,8,2)
		end

 	end



	local CurDaytime = GetDayTime()						--当前时间(天)
	
	local misId = 0
	local scriptId = 0

	for i,itm in x300608_g_CountryList do
		if itm.countryId == GetCurCountry(sceneId, selfId) then
			misId = itm.misId
			scriptId = itm.scriptId
			break
		end
	end
	
	local ret = AddQuest( sceneId, selfId,misId , scriptId,0,0,0,1 ) -- 给玩家添加任务
	local ret = 0
	if ret == 1 then

		--接任务写日志
		GamePlayScriptLog(sceneId,selfId,11)

		x300608_QuestLogRefresh( sceneId, selfId, x300608_g_MissionId)
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		-- local Readme = "你已接受护送神兽！"
		-- Msg2Player(sceneId,selfId,Readme,8,2)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300608_g_MissionId);
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);
		
		--环任务初始化
		SetQuestByIndex(sceneId, selfId, misIndex, x300608_g_RingMissionIndex, 0);		

  		--AddDispatchQuestInfoNM( sceneId, selfId, -1, x300608_g_MissionId )
  		local pos = GetGuildOfficial(sceneId, selfId)
  		if pos == x300608_g_Leader_Index then			--是帮主
  			local GuildID = GetGuildID(sceneId,selfId)
  			SetGuildQuestData(sceneId, GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME , CurDaytime)	
  			SetGuildQuestData(sceneId, GuildID, GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME , 0)	  				
  		end
	end

end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300608_DispatchMissionInfo( sceneId, selfId, NPCId,index )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x300608_g_MissionName)
		AddQuestText(sceneId,format("%s", x300608_g_MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y任务目标：")
		AddQuestText( sceneId,format("%s", x300608_g_MissionTarget))
		AddQuestText( sceneId," ")

		--提示信息
		if x300608_g_MissionHelp ~= "" then

			AddQuestText(sceneId,"#Y任务提示：")
			AddQuestText(sceneId,format("%s", x300608_g_MissionHelp))
			AddQuestText(sceneId," ")
		end
		-- if level >= 80 then
			-- AddQuestText(sceneId,"天赋值：400点")
		-- end
		--任务奖励信息
			AddQuestText(sceneId,"\n#Y奖励内容：")	
		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300608_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestText(sceneId,"经验值："..ExpBonus.."点")	
		end

		--2、帮贡
		if x300608_g_BonusMoney8 > 0 then
			--AddQuestMoneyBonus8(sceneId, x300608_g_BonusMoney8 )
			AddQuestText(sceneId,"帮贡：150点")	
			
		end	
		--帮会经验
		if x300608_g_GuildExpBonus>0 then
			--AddQuestGuildExpBonus(sceneId,x300608_g_GuildExpBonus)
			AddQuestText(sceneId,"帮会经验：1点")		
		end
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 400)
			local str = format("天赋值：%d点", refixInhExp)
			AddQuestText(sceneId, str)
		end
		

	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300608_g_ScriptId, x300608_g_MissionId);
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300608_DispatchContinueInfo( sceneId, selfId, NPCId )
	
	BeginQuestEvent(sceneId)

		--任务继续信息
		AddQuestText(sceneId,"#Y"..x300608_g_MissionName)
		AddQuestText(sceneId,format("%s", x300608_g_MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
		AddQuestText( sceneId,"#Y完成情况：")
		AddQuestText(sceneId, "未完成\n");
		AddQuestText(sceneId, "#Y奖励内容：");
  		--任务奖励信息

   		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300608_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestText(sceneId,"经验值："..ExpBonus.."点")	
		end

		--2、帮贡
		if x300608_g_BonusMoney8 > 0 then
			--AddQuestMoneyBonus8(sceneId, x300608_g_BonusMoney8 )
			AddQuestText(sceneId,"帮贡：150点")	
			
		end	
		--帮会经验
		if x300608_g_GuildExpBonus>0 then
			--AddQuestGuildExpBonus(sceneId,x300608_g_GuildExpBonus)
			AddQuestText(sceneId,"帮会经验：1点")		
		end
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 400)
			local str = format("天赋值：%d点", refixInhExp)
			AddQuestText(sceneId, str)
		end
	    --任务提示信息
	EndQuestEvent()
	--DispatchQuestEventList(sceneId,selfId,NPCId);
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300608_g_ScriptId, x300608_g_MissionId,0);

end

---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300608_DispatchCompletedInfo( sceneId, selfId, NPCId )
	
	BeginQuestEvent(sceneId)

		--任务完成信息
		AddQuestText(sceneId,"#Y"..x300608_g_MissionName)
		AddQuestText(sceneId,x300608_g_MissionCompleted)
		AddQuestText(sceneId," ")

  		--任务奖励信息
		AddQuestText(sceneId,"\n#Y奖励内容：")	
		--1、经验
		--1、经验
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300608_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestText(sceneId,"经验值："..ExpBonus.."点")	
		end

		--2、帮贡
		if x300608_g_BonusMoney8 > 0 then
			--AddQuestMoneyBonus8(sceneId, x300608_g_BonusMoney8 )
			AddQuestText(sceneId,"帮贡：150点")	
			
		end	
		--帮会经验
		if x300608_g_GuildExpBonus>0 then
			--AddQuestGuildExpBonus(sceneId,x300608_g_GuildExpBonus)
			AddQuestText(sceneId,"帮会经验：1点")		
		end
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 400)
			local str = format("天赋值：%d点", refixInhExp)
			AddQuestText(sceneId, str)
		end
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300608_g_ScriptId, x300608_g_MissionId);
  CallScriptFunction( 256238, "Finishhss", sceneId, selfId)
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300608_QuestLogRefresh( sceneId, selfId, MissionId)
 BeginQuestEvent(sceneId)

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
	if bHaveMission > 0 then
		BeginQuestEvent(sceneId)	
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = x300608_g_Exp * level
		ExpBonus =floor(ExpBonus+0.5)
	    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,  ExpBonus);
		end
		if x300608_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x300608_g_BonusMoney8 )
		end	
		--帮会经验
		if x300608_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300608_g_GuildExpBonus)
		end
		if level >= 80 then
			local refixInhExp = RefixInherenceExp(sceneId, selfId, 400)
			AddQuestInherenceExpBonus(sceneId,refixInhExp)
		end
		AddQuestLogCustomText( sceneId,
								"",						-- 标题
								x300608_g_MissionName,        -- 任务名字
								x300608_g_MissionTarget,		--任务目标
								"",					--任务NPC
								"将神兽安全护送到边境交给@npc_125514",                 --任务攻略
								x300608_g_MissionInfo,	--任务描述
								""					--任务小提示
								)
	end

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end

function x300608_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300608_QuestLogRefresh( sceneId, selfId, x300608_g_MissionId)
end


function x300608_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end


--成员超出护送范围的处理
function x300608_OnMeberOffline(sceneId,selfId)

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "您已经距离神兽过远，神兽感到了一丝危险，请尽快返回！")
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,"#cEFC800您已经距离神兽过远，神兽感到了一丝危险，请尽快返回！", 8,2)
	
end