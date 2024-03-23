--MisDescBegin

x310171_g_ScriptId 					= 	310171                   --脚本ID

x310171_g_MissionKind 				= 	1                       --任务类型
x310171_g_LevelLess					= 	20                      --任务最小等级  <=0 表示不限制

x310171_g_MissionHelp				=	"\t请到《成吉思汗》官网进行网站资料补充,可以填写一个身份证为18岁以上的ID,如果已经注册过18岁以下身份证的玩家可能会受到游戏中防沉迷系统的影响,请在登记后重新登陆游戏。\n你将获得奖励:\n#Y50000点经验#W\n#Y1两银卡#W"          --任务提示信息
x310171_g_MissionName				=   "不能说的秘密"

--目标
x310171_g_ExtTarget					=	{ {type=20,n=1,target="@npc_72005"} }

--奖励
x310171_g_BonusExp					=	50000	--奖励：经验
x310171_g_BonusMoney				=	1000	--奖励：银卡

--MisDescEnd

--任务目标顺序
x310171_MP_ISCOMPLETE				= 7	--代表完成 0未完成， 1完成

						
--**********************************
--列举事件
--**********************************
function x310171_ProcEnumEvent( sceneId, selfId, NPCId, MissionId )

	AddQuestNumText(sceneId, x310171_g_ScriptId, x310171_g_MissionName,3,1);
	return 0;
end

--**********************************
--任务入口函数
--**********************************
function x310171_ProcEventEntry(sceneId, selfId, NPCId, MissionId,nExtIdx)	--点击该任务后执行此脚本
	
	if GetNonageFlag(sceneId, selfId) ~= 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x310171_g_MissionHelp)
		EndQuestEvent(sceneId)
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"感谢你的支持，你会得:\n")
		AddQuestText(sceneId,"经验奖励:"..x310171_g_BonusExp)
		AddQuestText(sceneId,"银卡奖励:"..x310171_g_BonusMoney)
		EndQuestEvent(sceneId)
	end

	DispatchQuestInfo(sceneId, selfId, NPCId, x310171_g_ScriptId, -1);
end

---------------------------------------------------------------------------------------------------
--检测接受条件
---------------------------------------------------------------------------------------------------
function x310171_ProcAcceptCheck( sceneId, selfId,MissionID )

	if GetLevel( sceneId, selfId ) < x310171_g_LevelLess then
		local Readme = "等级不足，请升级到"..x310171_g_LevelLess.."级以后再来接受此任务！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)		
		return
	end

	if GetNonageFlag(sceneId, selfId) ~= 0 then
		return
	end

	if GetQuestData(sceneId,selfId,MD_ZHUCE_DATE[1],MD_ZHUCE_DATE[2],MD_ZHUCE_DATE[3]) == 1 then
		local Readme = "你已经领取过这个任务了！"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)		
		return		
	end

	--给奖励
	AddExp(sceneId, selfId, x310171_g_BonusExp);
	local Readme = "你获得了"..x310171_g_BonusExp.."经验的奖励！"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
	Msg2Player(sceneId,selfId,Readme,8,2)

	AddMoney( sceneId, selfId, 1, x310171_g_BonusMoney )
	SetQuestData(sceneId, selfId, MD_ZHUCE_DATE[1], MD_ZHUCE_DATE[2], MD_ZHUCE_DATE[3], 1)

end

---------------------------------------------------------------------------------------------------
--检查任务是否可提交
---------------------------------------------------------------------------------------------------
function x310171_CheckSubmit(sceneId, selfId, NPCId, index)
end

---------------------------------------------------------------------------------------------------
--放弃任务
---------------------------------------------------------------------------------------------------
function x310171_ProcQuestAbandon(sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------------------------
--获得奖励
---------------------------------------------------------------------------------------------------
function x310171_GetBonus( sceneId, selfId,NpcID, SelectId,MissionId )
end

---------------------------------------------------------------------------------------------------
--提交任务，不管任务是否完成或是任务，显示任务继续信息或是任务完成信息
---------------------------------------------------------------------------------------------------
function x310171_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId,MissionId)
end

---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x310171_DispatchMissionInfo( sceneId, selfId, NPCId )
	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x310171_g_MissionName)
		AddQuestText(sceneId,format("%s", x310171_g_MissionInfo))
		AddQuestText(sceneId," ")

		--任务目标
--		AddQuestText( sceneId,"#Y任务目标：")
--		AddQuestText( sceneId,format("%s", x300757_g_SubMissionID[index].MissionTarget))
--		AddQuestText( sceneId," ")

		--提示信息
--		if x300757_g_MissionHelp ~= "" then
--
--			AddQuestText(sceneId,"#Y任务提示：")
--			AddQuestText(sceneId,format("%s", x310171_g_MissionHelp))
--			AddQuestText(sceneId," ")
--		end

		--任务奖励信息

		--1、经验
		if x310171_g_BonusExp > 0 then
			AddQuestExpBonus(sceneId, x310171_g_BonusExp )
		end

		--2、金钱1
		if x310171_g_BonusMoney > 0 then
			AddQuestMoneyBonus2(sceneId, x310171_g_BonusMoney )
		end

	EndQuestEvent(sceneId)
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x310171_g_ScriptId, -1);	
end

---------------------------------------------------------------------------------------------------
--单击NPC事件
---------------------------------------------------------------------------------------------------
function x310171_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
end

---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x310171_QuestLogRefresh( sceneId, selfId, MissionId)
end

function x310171_ProcQuestLogRefresh( sceneId, selfId, MissionId)
end


