--楼兰师徒任务
x310307_g_ScriptId = 310307
x310307_g_GameId	= 1037

x310307_g_MissionName	= "【师徒】能人异士"
x310307_g_MissionId	= 9342
x310307_g_MasterDistance = 15
x310307_g_LimitTimes = 1

x310307_g_GoodBadValue = 2500
x310307_g_ExpRate = 30000
x310307_g_ExpRate_Low = 5000

x310307_g_LevelLessPrentice = 20
x310307_g_LevelLessMaster = 50
x310307_g_MissionReplyGuid = 129023
x310307_g_MissionReply          = "@npc_129023"

x310307_g_ItemID = 12030211

-- NPC Id乘这个系数表示已经进行过任务对话
x310307_g_HasTalkedCoff            = 100
-- 完成任务保存的MP大于此值表示已经进行过任务对话
x310307_g_HasTalkedValue           = 10000000

-- NPC Id乘这个系数表示已经进行过答题
x310307_g_HasAnsweredCoff            = 10
-- 完成任务保存的MP大于此值表示已经进行过答题
x310307_g_HasAnsweredValue           = 100000000

x310307_g_strNPCTalk             = {
					{ID = 129017 , content = "\t我是免费治疗医师，如果你受伤了，我可以帮你恢复健康。"},	
					{ID = 129018 , content = "\t我是帮战发布人，受到别的帮会欺负，就请帮主通过我来向对方帮会宣战吧。"}, 
					{ID = 129019 , content = "\t我是国战发布人，如今国家战事不断，当你拥有一定实力后，要多来找我为国出力。"}, 
					{ID = 129020 , content = "\t我是帮会任务发布人，想要为自己的帮会尽一份力？找我就对了。"}, 
					{ID = 129021 , content = "\t我是国家管理员，通过我可以参加屠城战、查询自己的功勋值"}, 

					{ID = 129024 , content = "\t我是声望商人，在我这里可以用声望值换取很多实用的东西，不要错过啊。"},
					{ID = 129025 , content = "\t我是药店商人，在我这里可以买到很多常用药品，随身携带一些药品是基本常识。"}, 
					{ID = 129026 , content = "\t我是防具商人，在我这里能买到各式防具，有需要的时候随时来找我。"}, 
					{ID = 129027 , content = "\t我是武器商人，在我这里能买到各式武器，有需要的时候随时来找我。"}, 
					{ID = 129029 , content = "\t我是领双管理员，大于20级后，每周都能找我领取5小时的双倍经验时间。"}, 
				  }

x310307_g_NPCLevel_Tab             = {
					{minlevel = 20 ,maxlevel = 30, 
						npcGUID = {
							129017,
							129018, 
							129019, 
							129020, 
							129021,
							},
					},
					{minlevel = 30 ,maxlevel = 160, 
						npcGUID = {
							129024,
							129025, 
							129026, 
							129027, 
							129029,
							129017,
							129018, 
							129019, 
							129020, 
							129021							},
					},

				  }


x310307_g_FinishOne             = "你已完成拜访@npc_%s的任务（%d/5）"
-- 拜访人数
x310307_g_TargetCount           = 5

-- 任务目标
x310307_g_MissionTarget			=	"  拜访@npc_%d(%d/1)"

-- 任务描述
x310307_g_MissionInfo           = "\t找到@npc_%d，@npc_%d，@npc_%d，@npc_%d和@npc_%d，你会得到意外的收获！"

-- 任务提示
x310307_g_MissionHelp           = "#G找到指定NPC后，可以回答他们的问题，答对会得到额外的经验！"

-- 任务需要金钱
x310307_g_MissionMoney = 5000

function x310307_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById(x310307_g_GameId)<=0 then
		return
	end
	--local level = GetLevel(sceneId, selfId)
	--if level < x310307_g_LevelLessMaster then
		--return
	--end

	local level = GetLevel(sceneId, selfId)
	if level < x310307_g_LevelLessPrentice then
		return
	end

	local npcGuid = GetMonsterGUID( sceneId, targetId)
	if npcGuid == x310307_g_MissionReplyGuid then
		if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) == 1 then
			local state = GetQuestStateNM( sceneId, selfId, targetId, x310307_g_MissionId)
			AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, state)
		else
			AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 8)
		end
	end
end

function x310307_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	if GetGameOpenById(x310307_g_GameId)<=0 then
		return
	end

	if MissionId ~= x310307_g_MissionId then
		return
	end

	local npcGuid = GetMonsterGUID( sceneId, targetId)
	if npcGuid == x310307_g_MissionReplyGuid then
		-- 交任务NPC
		local nMOPFlag = x310307_CheckIsMasterOrPrentice(sceneId, selfId)
		if nMOPFlag == 1 then -- 徒弟点击
			if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) == 1 then
				local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
				local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
				BeginQuestEvent(sceneId)
				AddQuestText( sceneId, "#Y"..x310307_g_MissionName)
				if isFinish == 0 then
					-- 任务未完成
					AddQuestText( sceneId, "\t交给你的事情都办完了？")
					EndQuestEvent( sceneId)
					DispatchQuestEventList( sceneId, selfId, targetId)
				else
					x310307_DispatchCompletedInfo(sceneId, selfId, targetId, index)
					--AddQuestText(sceneId,"\t恭喜您，完成了师徒任务！")
					----AddQuestText(sceneId,"\t请与你的师傅组队来我这里，由你的师傅帮你提交任务！")
					--local exp = x310307_CalculateExp(sceneId, selfId)
					--local szAwardForPrentice = "\n \n \n#Y徒弟奖励内容：\n#W经验值:"..exp.."点"
					--AddQuestText(sceneId, szAwardForPrentice)
					--local szAwardForMaster = "\n#Y师傅奖励内容：\n#W威望值:"..x310307_g_GoodBadValue.."点"
					--AddQuestText(sceneId, szAwardForMaster)
					--EndQuestEvent()
					----DispatchQuestEventList( sceneId, selfId, targetId)
					--DispatchQuestInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId)
				end
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y【师徒】能人异士")
				local str = "\t大隐隐于市，天下间能人异士无数，有不少就出没在各个城市、交通要道。时常去拜访他们，对徒弟的成长有很大的帮助。\n\t你是否愿意花费#G5两银币#W让你徒弟前去拜访几位能人，增加他的历练？"
				AddQuestText(sceneId,str)
				AddQuestText(sceneId,"\n#Y任务目标：")
				local target = "#W拜访5位当世能人。"
				AddQuestText(sceneId,target)
				AddQuestText(sceneId,"\n#G小提示：\n1.本任务需在师傅组队陪伴下提交。\n2.当徒弟等级低于等级排行榜最后一名10级以上，徒弟获得高额经验奖励，否则，徒弟获得普通经验奖励。师傅奖励不变。#W")
				AddQuestText(sceneId,"\n#Y任务奖励：")
				local exp, expRate = x310307_CalculateExp(sceneId, selfId)
				AddQuestText(sceneId,format("#W徒弟获得经验：徒弟等级*%s点", expRate))
				AddQuestText(sceneId,format("#W师傅获得威望：%s点", x310307_g_GoodBadValue))
				EndQuestEvent()

				DispatchQuestInfo(sceneId, selfId, targetId, x310307_g_MissionId, -1)
			end
			return

		elseif nMOPFlag == 2 then -- 师傅点击 
			local nPrenticeId = x310307_GetPrenticeObjId(sceneId, selfId)
			if IsHaveQuestNM( sceneId, nPrenticeId, x310307_g_MissionId) == 0 then
				-- 没有任务
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y【师徒】能人异士")
				local str = "\t大隐隐于市，天下间能人异士无数，有不少就出没在各个城市、交通要道。时常去拜访他们，对徒弟的成长有很大的帮助。\n\t你是否愿意花费#G5两银币#W让你徒弟前去拜访几位能人，增加他的历练？"
				AddQuestText(sceneId,str)
				AddQuestText(sceneId,"\n#Y任务目标：")
				local target = "#W拜访5位当世能人。"
				AddQuestText(sceneId,target)
				AddQuestText(sceneId,"\n#G小提示：\n1.本任务需在师傅组队陪伴下提交。\n2.当徒弟等级低于等级排行榜最后一名10级以上，徒弟获得高额经验奖励，否则，徒弟获得普通经验奖励。师傅奖励不变。#W")
				AddQuestText(sceneId,"\n#Y任务奖励：")
				local exp,expRate = x310307_CalculateExp(sceneId, nPrenticeId)
				AddQuestText(sceneId,format("#W徒弟获得经验：徒弟等级*%s点", expRate))
				AddQuestText(sceneId,format("#W师傅获得威望：%s点", x310307_g_GoodBadValue))
				EndQuestEvent()

				DispatchQuestInfo(sceneId, selfId, targetId, x310307_g_MissionId, -1)

			else
				-- 已经接受过任务
				local misIndex = GetQuestIndexByID( sceneId, nPrenticeId, x310307_g_MissionId)
				local isFinish = GetQuestParam( sceneId, nPrenticeId, misIndex, 7)
				BeginQuestEvent(sceneId)
				AddQuestText( sceneId, "#Y"..x310307_g_MissionName)
				if isFinish == 0 then
					-- 任务未完成
					AddQuestText( sceneId, "\t交给你的事情都办完了？")
					EndQuestEvent( sceneId)
					DispatchQuestEventList( sceneId, selfId, targetId)
				else
					AddQuestText(sceneId,"\t您这位徒弟今天已经领取过师徒任务了，请让他提交本任务。")
					local exp = x310307_CalculateExp(sceneId, nPrenticeId)
					local szAwardForPrentice = "\n \n \n#Y徒弟奖励内容：\n#W经验值:"..exp.."点"
					AddQuestText(sceneId, szAwardForPrentice)
					local szAwardForMaster = "\n#Y师傅奖励内容：\n#W威望值:"..x310307_g_GoodBadValue.."点"
					AddQuestText(sceneId, szAwardForMaster)
					EndQuestEvent()
					--DispatchQuestEventList( sceneId, selfId, targetId)
					DispatchQuestInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId)
				end
			end
			return
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y【师徒】能人异士")
			local str = "\t大隐隐于市，天下间能人异士无数，有不少就出没在各个城市、交通要道。时常去拜访他们，对徒弟的成长有很大的帮助。\n\t你是否愿意花费#G5两银币#W让你徒弟前去拜访几位能人，增加他的历练？"
			AddQuestText(sceneId,str)
			AddQuestText(sceneId,"\n#Y任务目标：")
			local target = "#W拜访5位当世能人。"
			AddQuestText(sceneId,target)
			AddQuestText(sceneId,"\n#G小提示：\n1.本任务需在师傅组队陪伴下提交。\n2.当徒弟等级低于等级排行榜最后一名10级以上，徒弟获得高额经验奖励，否则，徒弟获得普通经验奖励。师傅奖励不变。#W")
				AddQuestText(sceneId,"\n#Y任务奖励：")
			local exp,expRate = x310307_CalculateExp(sceneId, selfId)
			AddQuestText(sceneId,format("#W徒弟获得经验：徒弟等级*%s点", expRate))
			AddQuestText(sceneId,format("#W师傅获得威望：%s点", x310307_g_GoodBadValue))
			EndQuestEvent()

			DispatchQuestInfo(sceneId, selfId, targetId, x310307_g_MissionId, -1)
			return
		end
	else
	-- 子任务NPC
		if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) == 1 then	--只有徒弟有该任务，所以此处selfId为徒弟的ID
			if  index >= 11001 and index <= 11004 then
				-- 回答NPC的问题
				if x310307_CanAnswerQuestion(sceneId, selfId, targetId)  == 1  then
					x310307_NPCQuestion(sceneId, selfId, targetId, index)
				end
			else
				-- 完成拜访该NPC的任务
				x310307_FindNPC(sceneId, selfId, targetId)
			end
		end
	end
end

function x310307_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x310307_g_GameId)<=0 then
		return
	end
	
	if MissionId ~= x310307_g_MissionId then
		return
	end

	local npcGuid = GetMonsterGUID( sceneId, targetId)
	if npcGuid == x310307_g_MissionReplyGuid then
		-- 交任务NPC
		local nMOPFlag = x310307_CheckIsMasterOrPrentice(sceneId, selfId)
		local strMOP = nil
		if nMOPFlag == -1 then
			strMOP = "请师徒两人组队来领取任务！"
		elseif nMOPFlag == 0 then
			strMOP = "组队两人没有师徒关系或距离太远，无法领取任务！"
		end

		if strMOP ~= nil then
			Msg2Player(sceneId,selfId,strMOP,8,2)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, strMOP);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId)
			return
		end


		if nMOPFlag == 1 then	--徒弟点击确定
			local nMasterId = x310307_GetMasterObjId(sceneId, selfId)
			if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) > 0 then -- 交任务
				x310307_DoSubmit( sceneId, nMasterId, selfId, 2)
			else
				Msg2Player(sceneId,selfId,"请让你的师傅来领取任务！",8,2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "请让你的师傅来领取任务！");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId)
			end
		elseif nMOPFlag == 2 then	--师傅点击确定
			local nPrenticeId = x310307_GetPrenticeObjId(sceneId, selfId)
			if IsHaveQuestNM( sceneId, nPrenticeId, x310307_g_MissionId) > 0 then -- 交任务
				Msg2Player(sceneId,selfId,"您这位徒弟今天已经领取过师徒任务了，请让他提交本任务。",8,2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "您这位徒弟今天已经领取过师徒任务了，请让他提交本任务。");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId)
			else
				local str = x310307_DoAccept( sceneId, selfId ,nPrenticeId)
				if str ~= nil then
					Msg2Player(sceneId,selfId,str,8,2)
					BeginQuestEvent(sceneId);
					AddQuestText(sceneId, str);
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
				return
				end

				local szMasterName = GetName(sceneId, selfId)
				local szMsg = format("你的师傅%s已经为你领取了师徒任务，请努力完成，不要辜负了师傅的期望。", szMasterName)
		
				Msg2Player(sceneId, nPrenticeId, szMsg, 8, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, szMsg);
				EndQuestEvent();
				DispatchQuestTips(sceneId, nPrenticeId);
			end

		end
	else
		--子任务NPC,回答NPC的问题
		if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) == 1 then	--只有徒弟有该任务，所以此处selfId为徒弟的ID
			x310307_ShowQuestion(sceneId, selfId, targetId)

		end
	end	
end

function x310307_DoAccept( sceneId, MasterId, PrenticeId )

	if IsQuestFullNM(sceneId, PrenticeId) == 1 then
		return "很抱歉，你徒弟的任务已经满了，无法领取本任务。"
	end
	
	if x310307_GetMissionTimes(sceneId, PrenticeId) >= x310307_g_LimitTimes then
		return format("很抱歉，你这个徒弟本日的已经领取过%s次本任务，请明天再带他来。", x310307_g_LimitTimes)
	end

	if IsEnoughMoney(sceneId, MasterId,x310307_g_MissionMoney) == 0 then
		return "很抱歉，你没有足够的银币，无法为徒弟法领取本任务"
	end

	if SpendMoney(sceneId, MasterId, x310307_g_MissionMoney) ~= 1 then
		return "扣费失败，无法为徒弟法领取本任务"
	end

	local errorCode = AddQuest( sceneId, PrenticeId, x310307_g_MissionId, x310307_g_ScriptId, 0, 0, 0, 1)
	if errorCode ~= 1 then
		return "添加任务失败！"
	end
	
	BeginQuestEvent( sceneId)
        -- 任务名称
        AddQuestText( sceneId, "#Y"..x310307_g_MissionName)

        -- 根据级别选中5个NPC
	local nindex = 0
	local indexs = {}
	local Prenticelevel = GetLevel(sceneId, PrenticeId)
        for i, item in x310307_g_NPCLevel_Tab do
		if Prenticelevel >= item.minlevel and Prenticelevel < item.maxlevel then
			nindex = i
			indexs[1] = random( 1, getn( item.npcGUID) )
			local rndm = random( 1, getn( item.npcGUID) )
			while rndm == indexs[1] do
				rndm = random( 1, getn( item.npcGUID) )
			end
			indexs[2] = rndm
			rndm = random( 1, getn( item.npcGUID) )
			while rndm == indexs[1] or rndm == indexs[2] do
				rndm = random( 1, getn( item.npcGUID) )
			end
			indexs[3] = rndm
			rndm = random( 1, getn( item.npcGUID) )
			while rndm == indexs[1] or rndm == indexs[2] or rndm == indexs[3] do
				rndm = random( 1, getn( item.npcGUID) )
			end
			indexs[4] = rndm
			rndm = random( 1, getn( item.npcGUID) )
			while rndm == indexs[1] or rndm == indexs[2] or rndm == indexs[3] or rndm == indexs[4] do
				rndm = random( 1, getn( item.npcGUID) )
			end
			indexs[5] = rndm
		end
	end
				local str = "\t大隐隐于市，天下间能人异士无数，有不少就出没在各个城市、交通要道。时常去拜访他们，对你的成长有很大的帮助。"
				AddQuestText(sceneId,str)
        AddQuestText( sceneId, "\n#Y任务目标：" )
        -- 格式化任务描述信息
	local npcGUIDs =  x310307_g_NPCLevel_Tab[nindex].npcGUID
        AddQuestText( sceneId, format( "拜访@npc_%s,@npc_%s,@npc_%s,@npc_%s,@npc_%s", x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[1]], x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[2]], x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[3]],x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[4]],x310307_g_NPCLevel_Tab[nindex].npcGUID[indexs[5]] ) )
        AddQuestText( sceneId, " " )

        -- 任务回复
        AddQuestText( sceneId, "#Y任务回复：" )
        AddQuestText( sceneId, x310307_g_MissionReply)
        AddQuestText( sceneId, " " )

        AddQuestText( sceneId, "#Y小提示：" )
        AddQuestText( sceneId, x310307_g_MissionHelp)
        AddQuestText( sceneId, " " )

        --AddQuestText( sceneId, "#Y奖励内容：" )
	local exp = x310307_CalculateExp(sceneId, PrenticeId)
	local szAward = "\n#Y奖励内容：\n#W经验值:"..exp.."点"
	AddQuestText( sceneId, szAward )
        AddQuestText( sceneId, " " )

	EndQuestEvent( sceneId)
	DispatchQuestEventList( sceneId, PrenticeId, MasterId)


	-- 保存拜访的目标
	local misIndex = GetQuestIndexByID( sceneId, PrenticeId, x310307_g_MissionId)

	SetQuestByIndex( sceneId, PrenticeId, misIndex, 0, 0)
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 1, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[1]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 2, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[2]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 3, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[3]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 4, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[4]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 5, x310307_g_NPCLevel_Tab[ nindex].npcGUID[indexs[5]] )
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 6, 0)
	SetQuestByIndex( sceneId, PrenticeId, misIndex, 7, 0)
	-- 显示任务接受信息
	Msg2Player( sceneId, MasterId, format("你已经成功的帮助徒弟领取了任务：%s,扣去银币：%d两", x310307_g_MissionName, x310307_g_MissionMoney / 1000), 8, 2)
	Msg2Player( sceneId, MasterId, format("你已经成功的帮助徒弟领取了任务：%s,扣去银币：%d两", x310307_g_MissionName, x310307_g_MissionMoney / 1000), 8, 3)

	if GetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	else
		local times = GetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3])
		times = times + 1
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], times)
	end

	GamePlayScriptLog(sceneId, PrenticeId, 1471)
	return nil
end

function x310307_CalculateExp(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	local minlevel = GetTopListInfo_MinLevel(GetWorldID(sceneId, selfId))
	local exp = 0
	local ExpRate = 0
	if (minlevel - level) <= 10 then
		exp = level * x310307_g_ExpRate_Low
		ExpRate = x310307_g_ExpRate_Low
	else
		exp = level * x310307_g_ExpRate
		ExpRate = x310307_g_ExpRate
	end

	return exp,ExpRate
end

function x310307_DoSubmit( sceneId, MasterId , PrenticeId , Param)
	if Param == 2 then
	        -- 删除道具
                if DelItem( sceneId, PrenticeId, x310307_g_ItemID, 1) == 0 then
                    Msg2Player( sceneId, PrenticeId, format( "没有道具@item_%d#cffcc00，提交任务失败", x310307_g_ItemID), 8, 3)
                    return
                end

	end

	if GetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, PrenticeId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	end
	
	
	
	local bret = DelQuest( sceneId, PrenticeId, x310307_g_MissionId )
	if bret == 0 then
		return
	end
	
	--师傅奖励
	local value = GetPlayerGoodBadValue(sceneId, MasterId)
	value = value + x310307_g_GoodBadValue* Param
	SetPlayerGoodBadValue(sceneId, MasterId, value)
	local str = format("你的徒弟已完成师徒任务你获得%d点威望。", x310307_g_GoodBadValue * Param)
	Msg2Player(sceneId,MasterId,str,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, MasterId);
	--徒弟奖励
	local exp = x310307_CalculateExp(sceneId, PrenticeId)
	AddExp(sceneId, PrenticeId, exp* Param);
	str = format("你已完成师徒任务，获得%d点经验的奖励。", exp * Param)
	Msg2Player(sceneId,PrenticeId,str,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, PrenticeId);
	GamePlayScriptLog(sceneId, PrenticeId, 1472)
end

function x310307_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId )
    if GetGameOpenById(x310307_g_GameId)<=0 then
	return
    end
    local level = GetLevel(sceneId, selfId)
	
    if level < x310307_g_LevelLessPrentice then
	return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
    local npc1 = GetQuestParam( sceneId, selfId, misIndex, 1)
    if npc1 > x310307_g_HasTalkedValue then
		if npc1 > x310307_g_HasAnsweredValue then
			npc1 = npc1 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc1 = npc1 / x310307_g_HasTalkedCoff
		end
    end
    local npc2 = GetQuestParam( sceneId, selfId, misIndex, 2)
    if npc2 > x310307_g_HasTalkedValue then
		if npc2 > x310307_g_HasAnsweredValue then
			npc2 = npc2 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc2 = npc2 / x310307_g_HasTalkedCoff
		end
    end
    local npc3 = GetQuestParam( sceneId, selfId, misIndex, 3)
    if npc3 > x310307_g_HasTalkedValue then
		if npc3 > x310307_g_HasAnsweredValue then
			npc3 = npc3 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc3 = npc3 / x310307_g_HasTalkedCoff
		end
    end
    local npc4 = GetQuestParam( sceneId, selfId, misIndex, 4)
    if npc4 > x310307_g_HasTalkedValue then
		if npc4 > x310307_g_HasAnsweredValue then
			npc4 = npc4 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc4 = npc4 / x310307_g_HasTalkedCoff
		end
    end
    local npc5 = GetQuestParam( sceneId, selfId, misIndex, 5)
    if npc5 > x310307_g_HasTalkedValue then
		if npc5 > x310307_g_HasAnsweredValue then
			npc5 = npc5 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc5 = npc5 / x310307_g_HasTalkedCoff
		end
    end
    if npcGuid == npc1 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 1)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
    if npcGuid == npc2 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 2)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
    if npcGuid == npc3 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 3)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
    if npcGuid == npc4 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 4)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
    if npcGuid == npc5 then
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 5)
        if isFinish < x310307_g_HasTalkedValue then
            AddQuestNumText( sceneId, x310307_g_MissionId, x310307_g_MissionName, 6)
        end
        return
    end
end

function x310307_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    if GetGameOpenById(x310307_g_GameId)<=0 then
	return
    end
    local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
    local mFinished = GetQuestParam( sceneId, selfId, misIndex, 7)
    local F1 = GetQuestParam( sceneId, selfId, misIndex, 1)
    if F1 > x310307_g_HasTalkedValue then
        F1 = 1
    else
        F1 = 0
    end
    local F2 = GetQuestParam( sceneId, selfId, misIndex, 2)
    if F2 > x310307_g_HasTalkedValue then
        F2 = 1
    else
        F2 = 0
    end
    local F3 = GetQuestParam( sceneId, selfId, misIndex, 3)
    if F3 > x310307_g_HasTalkedValue then
        F3 = 1
    else
        F3 = 0
    end
    local F4 = GetQuestParam( sceneId, selfId, misIndex, 4)
    if F4 > x310307_g_HasTalkedValue then
        F4 = 1
    else
        F4 = 0
    end
    local F5 = GetQuestParam( sceneId, selfId, misIndex, 5)
    if F5 > x310307_g_HasTalkedValue then
        F5 = 1
    else
        F5 = 0
    end
    --local PrenticeObjId = x310307_GetPrenticeObjId(sceneId, selfId)

	
    local npc1, npc2, npc3, npc4, npc5 = x310307_GetNPCID( sceneId, selfId)
    local strMissionInfo = ""

    if mFinished == 0 then
    		if F1 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc1, F1);
    		strMissionInfo = strMissionInfo.."\n"
    		
    		if F2 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc2, F2);
    		strMissionInfo = strMissionInfo.."\n"
    		
    		if F3 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc3, F3);
		strMissionInfo = strMissionInfo.."\n"

		if F4 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc4, F4);
		strMissionInfo = strMissionInfo.."\n"

		if F5 > 0 then
    			strMissionInfo = strMissionInfo.."#G";
    		else
    			strMissionInfo = strMissionInfo.."#W";
    		end
    		strMissionInfo = strMissionInfo..format(x310307_g_MissionTarget, npc5, F5);
		strMissionInfo = strMissionInfo.."\n"
    else
        strMissionInfo = "任务已经完成，请回去向"..x310307_g_MissionReply.."汇报！"
    end

    BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                               "师徒任务",                             -- 标题
                               x310307_g_MissionName,          -- 任务名字
                               strMissionInfo,     -- 任务目标
                               x310307_g_MissionReply,         -- 任务NPC
                               "找到隐秘的高人",	--任务攻略
                               format( x310307_g_MissionInfo, npc1, npc2, npc3, npc4, npc5),   -- 任务描述
                               x310307_g_MissionHelp)          -- 任务提示


    local exp = x310307_CalculateExp(sceneId, selfId)
            
    AddQuestExpBonus( sceneId, exp)
    EndQuestEvent()
    DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x310307_ProcQuestAbandon(sceneId, selfId, MissionId)
	DelQuest( sceneId, selfId, x310307_g_MissionId )
	
	local message = "您放弃了师徒任务"
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 4, 2);
	
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3], GetDayOfYear())
		SetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3], 1)
	end
end

-- 获得子任务NPC的Id
function x310307_GetNPCID(sceneId, selfId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
    local F1 = GetQuestParam( sceneId, selfId, misIndex, 1)
    local F2 = GetQuestParam( sceneId, selfId, misIndex, 2)
    local F3 = GetQuestParam( sceneId, selfId, misIndex, 3)
    local F4 = GetQuestParam( sceneId, selfId, misIndex, 4)
    local F5 = GetQuestParam( sceneId, selfId, misIndex, 5)

    local npc1 = F1
    local npc2 = F2
    local npc3 = F3
    local npc4 = F4
    local npc5 = F5

    if npc1 > x310307_g_HasTalkedValue then
		if npc1 > x310307_g_HasAnsweredValue then
			npc1 = npc1 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc1 = npc1 / x310307_g_HasTalkedCoff
		end
    end
    if npc2 > x310307_g_HasTalkedValue then
		if npc2 > x310307_g_HasAnsweredValue then
			npc2 = npc2 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc2 = npc2 / x310307_g_HasTalkedCoff
		end
    end
    if npc3 > x310307_g_HasTalkedValue then
		if npc3 > x310307_g_HasAnsweredValue then
			npc3 = npc3 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc3 = npc3 / x310307_g_HasTalkedCoff
		end
    end
    if npc4 > x310307_g_HasTalkedValue then
		if npc4 > x310307_g_HasAnsweredValue then
			npc4 = npc4 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc4 = npc4 / x310307_g_HasTalkedCoff
		end
    end
    if npc5 > x310307_g_HasTalkedValue then
		if npc5 > x310307_g_HasAnsweredValue then
			npc5 = npc5 / x310307_g_HasAnsweredCoff / x310307_g_HasTalkedCoff
		else
			npc5 = npc5 / x310307_g_HasTalkedCoff
		end
    end
    return npc1, npc2, npc3, npc4, npc5
end

function x310307_GetNPCTalk(targetId)
	for i, item in x310307_g_strNPCTalk do
		if item.ID == targetId then
			return item.content
		end
	end
end

function x310307_GetMissionTimes(sceneId, selfId)
	if GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_DAY[1], MD_MASTER_PRENTICE_COM_DAY[2], MD_MASTER_PRENTICE_COM_DAY[3]) ~= GetDayOfYear() then
		return 0
	else
		return GetQuestData(sceneId, selfId, MD_MASTER_PRENTICE_COM_TIMES[1], MD_MASTER_PRENTICE_COM_TIMES[2], MD_MASTER_PRENTICE_COM_TIMES[3])
	end
end

function x310307_CheckIsMasterOrPrentice( sceneId, selfId)	--返回徒弟还是师傅的标志  -1 不是两人组队 0 没有关系 1 是徒弟 2 是师傅	
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize ~= 2) then
		return -1
	end
	
	local MasterOrPrenticeFlag = 0 
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if targetId ~= selfId then
			if IsInDist(sceneId, selfId, targetId, x310307_g_MasterDistance) == 1then
				if GetObjType(sceneId, targetId) == 1 then
					if IsPrentice(sceneId, selfId, targetId) == 1 then
						MasterOrPrenticeFlag = 2
					elseif IsMaster(sceneId, selfId, targetId) == 1 then
						MasterOrPrenticeFlag = 1
					end
				end
			end
		end
	end

	return MasterOrPrenticeFlag
end

function x310307_ShowQuestion(sceneId, selfId, targetId)
	local npcGuid = GetMonsterGUID( sceneId, targetId)
	--得到谜语
	local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestShitu_GetQuestionInfo(npcGuid)

	if id ~= npcGuid then
		return
	end

	--更新对话框内容
	BeginQuestEvent(sceneId)
		
		AddQuestText(sceneId,"#Y【师徒】能人异士#W\n")
		
		AddQuestText(sceneId,strDesc)
		x310307_AddDengmiAnswerOption( sceneId, 
							strAnswer1, 
							strAnswer2, 
							strAnswer3, 
							strAnswer4 )
									
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)	
end

----------------------------------------------------------------------------------------------
--添加师徒任务NPC问题答案选项
----------------------------------------------------------------------------------------------
function x310307_AddDengmiAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)

	--随机添加选项
	local arr_answer = { {strAnswer1,11001},{strAnswer2,11002},{strAnswer3,11003},{strAnswer4,11004} }
	for j = 1, 2 do
		local n = random(1, 4)
		local m =  random(1, 4)
		if n ~= m then
			local t = arr_answer[n]
			arr_answer[n] = arr_answer[m]
			arr_answer[m] = t
		end
	end
	
	for i=1,4 do
		AddQuestNumText(sceneId,x310307_g_MissionId,arr_answer[i][1],3,arr_answer[i][2] )
	end
end


function x310307_AnswerRight( sceneId, selfId, targetId )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"恭喜你，回答正确。")	
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
		
	local exp = x310307_CalculateExp(sceneId, selfId)/10
	AddExp(sceneId, selfId, exp);
	str = format("你回答对了问题，获得%d点经验的奖励。", exp)
	Msg2Player(sceneId,selfId,str,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x310307_AnswerError( sceneId, selfId, targetId )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"很遗憾，你回答错了，不能获得额外奖励。")	
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)

	Msg2Player(sceneId,selfId,"很遗憾，你的问题回答错了，不能获得额外奖励。",8,2)
end

function x310307_GetPrenticeObjId(sceneId, selfId)
	local teamSize = GetTeamSize(sceneId, selfId)
	local nPrenticeObjId = -1
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310307_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsPrentice(sceneId, selfId, targetId) then
				nPrenticeObjId = targetId
			end
		end
	end
	
	return nPrenticeObjId
end

function x310307_GetMasterObjId(sceneId, selfId)
	local teamSize = GetTeamSize(sceneId, selfId)
	local nMasterObjId = -1
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x310307_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				nMasterObjId = targetId
			end
		end
	end
	
	return nMasterObjId
end

function x310307_AnswerQuestion(sceneId, selfId, targetId, index)
	if  index >= 11001 and index <= 11004	then
		local npcGuid = GetMonsterGUID( sceneId, targetId)
		--取得题目信息
		local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestShitu_GetQuestionInfo(npcGuid)
		if id ~= npcGuid then
			return
		end

		--检查答案是否正确
		if 11000+nAnswer == index then
			--正确
			x310307_AnswerRight( sceneId, selfId, targetId )
		else
			--错误
			x310307_AnswerError( sceneId, selfId, targetId )
		end
		
	end

end

function x310307_NPCQuestion(sceneId, selfId, targetId, index)
	local logFmtMsg         = "x310307_NPCQuestion : sceneId = %d,selfId = %d,targetId = %d,index = %d" 	
	local logMsg = format(logFmtMsg,sceneId,selfId,targetId,index)
	WriteLog(1,logMsg)
	x310307_AnswerQuestion(sceneId, selfId, targetId, index)
end

function x310307_FindNPC(sceneId, selfId, targetId)
	local npcGuid = GetMonsterGUID( sceneId, targetId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
	local npc1, npc2, npc3, npc4, npc5 = x310307_GetNPCID(sceneId, selfId)
	local count = GetQuestParam( sceneId, selfId, misIndex, 6)
	BeginQuestEvent(sceneId)

	local npcTalkContent = ""
	AddQuestText( sceneId, "#Y"..x310307_g_MissionName)

	if npcGuid == npc1 and GetQuestParam( sceneId, selfId, misIndex, 1) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 1, GetQuestParam( sceneId, selfId, misIndex, 1) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc1)
	end
	if npcGuid == npc2 and GetQuestParam( sceneId, selfId, misIndex, 2) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 2, GetQuestParam( sceneId, selfId, misIndex, 2) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc2)
	end
	if npcGuid == npc3 and GetQuestParam( sceneId, selfId, misIndex, 3) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 3, GetQuestParam( sceneId, selfId, misIndex, 3) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc3)
	end
	if npcGuid == npc4 and GetQuestParam( sceneId, selfId, misIndex, 4) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 4, GetQuestParam( sceneId, selfId, misIndex, 4) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc4)
	end
	if npcGuid == npc5 and GetQuestParam( sceneId, selfId, misIndex, 5) < x310307_g_HasTalkedValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 5, GetQuestParam( sceneId, selfId, misIndex, 5) * x310307_g_HasTalkedCoff)
		count = count + 1
		npcTalkContent = x310307_GetNPCTalk(npc5)
	end
	
	AddQuestText( sceneId, npcTalkContent)
	AddQuestText( sceneId, "\n \n#G小提示#W：\n\t请点击确定回答我提出的问题。答对会有额外经验奖励。" )
	EndQuestEvent( sceneId)
	--DispatchQuestEventList( sceneId, selfId, targetId)
	DispatchQuestInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId, 0)

	local strTip = format( x310307_g_FinishOne, npcGuid, count)
	BeginQuestEvent( sceneId)
	AddQuestText( sceneId, strTip)
	EndQuestEvent( sceneId)
	DispatchQuestTips( sceneId, selfId)
	if count >= x310307_g_TargetCount then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
		Msg2Player( sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 2)
		Msg2Player( sceneId, selfId, "任务已经完成，快点回去汇报吧！", 8, 3)
	end
	-- 更新已拜访人数
	SetQuestByIndex( sceneId, selfId, misIndex, 6, count)
	-- 更新任务面板
	x310307_ProcQuestLogRefresh( sceneId, selfId, x310307_g_MissionId)

end

function x310307_DispatchCompletedInfo( sceneId, selfId, targetId, index)
	if index == 31 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310307_g_MissionName)
		AddQuestText(sceneId, "\t天下间能人无数，时常走访这些高人会对你的成长很有帮助。\n\t如果你提交给我一个#G师恩难谢#W。完成任务后，你和师傅均会获得双倍的奖励。\n\t你确定要提交一个师恩难谢么？" )
		local exp = x310307_CalculateExp(sceneId, selfId)
		exp = exp * 2
		local szAwardForPrentice = "\n \n \n#Y徒弟奖励内容：\n#W经验值（双倍）:"..exp.."点"
		AddQuestText(sceneId, szAwardForPrentice)
		local GoodBadValue = x310307_g_GoodBadValue * 2
		local szAwardForMaster = "\n#Y师傅奖励内容：\n#W威望值（双倍）:"..GoodBadValue.."点"
		AddQuestText(sceneId, szAwardForMaster)
		EndQuestEvent()
		DispatchQuestInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId)

	elseif index == 32 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310307_g_MissionName)
		AddQuestText(sceneId, "\t天下间能人无数，时常走访这些高人会对你的成长很有帮助。\n\t你如果能交给我一个#G师恩难谢#W，完成任务后你和你的师傅均会获得双倍的奖励。\n \n#G小提示:\n\t如果你希望提交师恩难谢使自己和师傅的奖励翻倍，请关闭此界面重新提交本任务。" )
		local exp = x310307_CalculateExp(sceneId, selfId)
		local szAwardForPrentice = "\n \n \n#Y徒弟奖励内容：\n#W经验值:"..exp.."点"
		AddQuestText(sceneId, szAwardForPrentice)
		local szAwardForMaster = "\n#Y师傅奖励内容：\n#W威望值:"..x310307_g_GoodBadValue.."点"
		AddQuestText(sceneId, szAwardForMaster)
		EndQuestEvent()
		DispatchQuestContinueInfoNM( sceneId, selfId, targetId, x310307_g_ScriptId, x310307_g_MissionId)

	else
		BeginQuestEvent(sceneId)
		    AddQuestText(sceneId,"#Y"..x310307_g_MissionName)
		    AddQuestText(sceneId, "\t恭喜您，完成了师徒任务！" )
		    AddQuestText(sceneId," ")

		    AddQuestNumText( sceneId, x310307_g_MissionId, "使用师恩难谢提交任务", 3, 31)
		    AddQuestNumText( sceneId, x310307_g_MissionId, "直接提交任务", 3, 32)
		EndQuestEvent()
		DispatchQuestEventList( sceneId, selfId, targetId)
	end

end

function x310307_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId)

	if GetGameOpenById(x310307_g_GameId)<=0 then
		return
	end
	
	if MissionId ~= x310307_g_MissionId then
		return
	end

	local npcGuid = GetMonsterGUID( sceneId, targetId)
	if npcGuid == x310307_g_MissionReplyGuid then
		-- 交任务NPC
		local nMOPFlag = x310307_CheckIsMasterOrPrentice(sceneId, selfId)

		if nMOPFlag == 1 then	--徒弟点击确定
			local nMasterId = x310307_GetMasterObjId(sceneId, selfId)
			if IsHaveQuestNM( sceneId, selfId, x310307_g_MissionId) > 0 then -- 交任务
				x310307_DoSubmit( sceneId, nMasterId, selfId, 1)
			end
		end
	end
end

function x310307_CanAnswerQuestion(sceneId, selfId, targetId)
	local npcGuid = GetMonsterGUID( sceneId, targetId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310307_g_MissionId)
	local npc1, npc2, npc3, npc4, npc5 = x310307_GetNPCID(sceneId, selfId)
	local ret = 0

	if npcGuid == npc1 and GetQuestParam( sceneId, selfId, misIndex, 1) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 1) < x310307_g_HasAnsweredValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 1, GetQuestParam( sceneId, selfId, misIndex, 1) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	if npcGuid == npc2 and GetQuestParam( sceneId, selfId, misIndex, 2) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 2) < x310307_g_HasAnsweredValue  then
		SetQuestByIndex( sceneId, selfId, misIndex, 2, GetQuestParam( sceneId, selfId, misIndex, 2) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	if npcGuid == npc3 and GetQuestParam( sceneId, selfId, misIndex, 3) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 3) < x310307_g_HasAnsweredValue then
		SetQuestByIndex( sceneId, selfId, misIndex, 3, GetQuestParam( sceneId, selfId, misIndex, 3) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	if npcGuid == npc4 and GetQuestParam( sceneId, selfId, misIndex, 4) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 4) < x310307_g_HasAnsweredValue  then
		SetQuestByIndex( sceneId, selfId, misIndex, 4, GetQuestParam( sceneId, selfId, misIndex, 4) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	if npcGuid == npc5 and GetQuestParam( sceneId, selfId, misIndex, 5) > x310307_g_HasTalkedValue and GetQuestParam( sceneId, selfId, misIndex, 5) < x310307_g_HasAnsweredValue   then
		SetQuestByIndex( sceneId, selfId, misIndex, 5, GetQuestParam( sceneId, selfId, misIndex, 5) * x310307_g_HasAnsweredCoff)
		ret = 1
	end
	
	return ret

end
