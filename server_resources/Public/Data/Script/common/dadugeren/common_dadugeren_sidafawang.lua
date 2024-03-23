--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300564_g_MissionId 				= 	9300                     --任务ID
x300564_g_ScriptId 					= 	300564                  --脚本ID
x300564_g_MissionKind 				= 	1                       --任务类型
x300564_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制


x300564_g_MissionName				= 	"【个人】四大法王"
x300564_g_MissionTarget				= 	"找到@npc_141500"
x300564_g_MissionTarget1				= 	"询问明教四大法王"
x300564_g_MissionInfo				= 	""
x300564_g_ContinueInfo				= 	""
x300564_g_MissionCompleted			= 	""
x300564_g_MissionHelp				=	""          --任务提示信息

--目标
x300564_g_ExtTarget					=	{ {type=20,n=1,target="明教风云"}}

--奖励

x300564_g_ExpBonus					= 	0;--x300564_AddExpAward               	--奖励：经验
x300564_g_BonusItem					=	{}	--奖励：物品

x300564_g_BonusMoney1               = 	0
x300564_g_BonusMoney2               =   0
x300564_g_BonusMoney3               =   0
x300564_g_BonusMoney5				=	1000

x300564_g_BonusChoiceItem           =   {}


--MisDescEnd

x300564_g_NpcList = {139829,139828,139827,139834}
x300564_g_ReplyNpcId = 141500


-- Mission Text list

x300564_g_GameId			= 1001

x300564_g_QuestionCount		= 7	
x300564_g_QuestionTextList	= {
								{	title="【个人】四大法王",  --任务名称
									info="\t我们明教四大法王中出了一个叛徒，你去询问一下四大法王，他们中有#G三个人#W会告诉你#G真话#W，#G一个人会撒谎#W。\n\t记住，#G撒谎的人不一定是叛徒，叛徒不一定撒谎#W。", --描述
									task1="询问青翼蝠王@npc_"..x300564_g_NpcList[1].."",
									task2="询问白眉鹰王@npc_"..x300564_g_NpcList[2].."",
									task3="询问紫衫龙王@npc_"..x300564_g_NpcList[3].."",
									task4="询问金毛狮王@npc_"..x300564_g_NpcList[4].."",
									text1="\t怎么？！我青翼蝠王竟会被怀疑？哼，我只能告诉你：#G鹰王说真话#W。",
									text2="\t我白眉鹰王殷天正，岂是那等背叛明教的宵小之徒！不过，我倒是知道：#G狮王说假话#W。",
									text3="\t想不到有人居然会怀疑到我紫衫龙王这里？根据我的推测：#G蝠王是叛徒#W。",
									text4="\t谢逊一世豪杰，岂能受这等污蔑！别人我不清楚，但我能肯定：#G蝠王是好人#W。",
									answer="\t我已经知道谁是叛徒了，你知道吗？\n\t是金毛狮王#W？#G紫衫龙王#W？#G白眉鹰王#W？还是#G青翼蝠王#W？\n\t#Y(您可以在任务攻略中查看四大法王说过的话，以便分析。)",
									answer1="是金毛狮王",
									answer2="是紫衫龙王",
									answer3="是青翼蝠王",
									answer4="是白眉鹰王",
									
								  gonglue1="#G鹰王说真话#W。",
									gonglue2="#G狮王说假话#W。",
									gonglue3="#G蝠王是叛徒#W。",
									gonglue4="#G蝠王是好人#W。",
									
									result = 3  -- 答案

								},
								{	title="【个人】四大法王",  --任务名称
									info="\t我们明教四大法王中出了一个叛徒，你去询问一下四大法王，他们中有#G三个人#W会告诉你#G真话#W，#G一个人会撒谎#W。\n\t记住，#G撒谎的人不一定是叛徒，叛徒不一定撒谎#W。", --描述
									task1="询问青翼蝠王@npc_"..x300564_g_NpcList[1].."",
									task2="询问白眉鹰王@npc_"..x300564_g_NpcList[2].."",
									task3="询问紫衫龙王@npc_"..x300564_g_NpcList[3].."",
									task4="询问金毛狮王@npc_"..x300564_g_NpcList[4].."",
									text1="\t怎么？！我青翼蝠王竟会被怀疑？哼，我只能告诉你：#G我不是叛徒#W。",
									text2="\t我白眉鹰王殷天正，岂是那等背叛明教的宵小之徒！不过，我倒是知道：#G我不是叛徒#W。",
									text3="\t想不到有人居然会怀疑到我紫衫龙王这里？根据我的推测：#G蝠王说真话#W。",
									text4="\t谢逊一世豪杰，岂能受这等污蔑！别人我不清楚，但我能肯定：#G蝠王说真话#W。",
									answer="\t我已经知道谁是叛徒了，你知道吗？\n\t是金毛狮王#W？紫衫龙王#W？白眉鹰王#W？还是青翼蝠王#W？\n\t#Y(您可以在任务攻略中查看四大法王说过的话，以便分析。)",
									answer1="是金毛狮王",
									answer2="是紫衫龙王",
									answer3="是青翼蝠王",
									answer4="是白眉鹰王",
									
									gonglue1="#G我不是叛徒#W。",
									gonglue2="#G我不是叛徒#W。",
									gonglue3="#G蝠王说真话#W。",
									gonglue4="#G蝠王说真话#W。",
									
									result = 4  -- 答案

								},
								{	title="【个人】四大法王",  --任务名称
									info="\t我们明教四大法王中出了一个叛徒，你去询问一下四大法王，他们中有#G三个人#W会告诉你#G真话#W，#G一个人会撒谎#W。\n\t记住，#G撒谎的人不一定是叛徒，叛徒不一定撒谎#W。", --描述
									task1="询问青翼蝠王@npc_"..x300564_g_NpcList[1].."",
									task2="询问白眉鹰王@npc_"..x300564_g_NpcList[2].."",
									task3="询问紫衫龙王@npc_"..x300564_g_NpcList[3].."",
									task4="询问金毛狮王@npc_"..x300564_g_NpcList[4].."",
									text1="\t怎么？！我青翼蝠王竟会被怀疑？哼，我只能告诉你：#G鹰王是叛徒#W。",
									text2="\t我白眉鹰王殷天正，岂是那等背叛明教的宵小之徒！不过，我倒是知道：#G我不是叛徒#W。",
									text3="\t想不到有人居然会怀疑到我紫衫龙王这里？根据我的推测：#G狮王说真话#W。",
									text4="\t谢逊一世豪杰，岂能受这等污蔑！别人我不清楚，但我能肯定：#G龙王是叛徒#W。",
									answer="\t我已经知道谁是叛徒了，你知道吗？\n\t是金毛狮王？紫衫龙王？白眉鹰王？还是青翼蝠王？\n\t#Y(您可以在任务攻略中查看四大法王说过的话，以便分析。)",
									answer1="是金毛狮王",
									answer2="是紫衫龙王",
									answer3="是青翼蝠王",
									answer4="是白眉鹰王",
									
									gonglue1="#G鹰王是叛徒#W。",
									gonglue2="#G我不是叛徒#W。",
									gonglue3="#G狮王说真话#W。",
									gonglue4="#G龙王是叛徒#W。",
									
									result = 2  -- 答案

								},
								{	title="【个人】四大法王",  --任务名称
									info="\t我们明教四大法王中出了一个叛徒，你去询问一下四大法王，他们中有#G三个人#W会告诉你#G真话#W，#G一个人会撒谎#W。\n\t记住，#G撒谎的人不一定是叛徒，叛徒不一定撒谎#W。", --描述
									task1="询问青翼蝠王@npc_"..x300564_g_NpcList[1].."",
									task2="询问白眉鹰王@npc_"..x300564_g_NpcList[2].."",
									task3="询问紫衫龙王@npc_"..x300564_g_NpcList[3].."",
									task4="询问金毛狮王@npc_"..x300564_g_NpcList[4].."",
									text1="\t怎么？！我青翼蝠王竟会被怀疑？哼，我只能告诉你：#G我说真话#W。",
									text2="\t我白眉鹰王殷天正，岂是那等背叛明教的宵小之徒！不过，我倒是知道：#G龙王是叛徒#W。",
									text3="\t想不到有人居然会怀疑到我紫衫龙王这里？根据我的推测：#G我说真话#W。",
									text4="\t谢逊一世豪杰，岂能受这等污蔑！别人我不清楚，但我能肯定：#G蝠王说假话#W。",
									answer="\t我已经知道谁是叛徒了，你知道吗？\n\t是金毛狮王？紫衫龙王？白眉鹰王？还是青翼蝠王？\n\t#Y(您可以在任务攻略中查看四大法王说过的话，以便分析。)",
									answer1="是金毛狮王",
									answer2="是紫衫龙王",
									answer3="是青翼蝠王",
									answer4="是白眉鹰王",
									
									gonglue1="#G我说真话#W。",
									gonglue2="#G龙王是叛徒#W。",
									gonglue3="#G我说真话#W。",
									gonglue4="#G蝠王说假话#W。",
									
									result = 2  -- 答案

								},
									{	title="【个人】四大法王",  --任务名称
									info="\t我们明教四大法王中出了一个叛徒，你去询问一下四大法王，他们中有#G三个人#W会告诉你#G真话#W，#G一个人会撒谎#W。\n\t记住，#G撒谎的人不一定是叛徒，叛徒不一定撒谎#W。", --描述
									task1="询问青翼蝠王@npc_"..x300564_g_NpcList[1].."",
									task2="询问白眉鹰王@npc_"..x300564_g_NpcList[2].."",
									task3="询问紫衫龙王@npc_"..x300564_g_NpcList[3].."",
									task4="询问金毛狮王@npc_"..x300564_g_NpcList[4].."",
									text1="\t怎么？！我青翼蝠王竟会被怀疑？哼，我只能告诉你：#G龙王是好人#W。",
									text2="\t我白眉鹰王殷天正，岂是那等背叛明教的宵小之徒！不过，我倒是知道：#G龙王是好人#W。",
									text3="\t想不到有人居然会怀疑到我紫衫龙王这里？根据我的推测：#G说假话的是叛徒#W。",
									text4="\t谢逊一世豪杰，岂能受这等污蔑！别人我不清楚，但我能肯定：#G龙王是叛徒#W。",
									answer="\t我已经知道谁是叛徒了，你知道吗？\n\t是金毛狮王？紫衫龙王？白眉鹰王？还是青翼蝠王？\n\t#Y(您可以在任务攻略中查看四大法王说过的话，以便分析。)",
									answer1="是金毛狮王",
									answer2="是紫衫龙王",
									answer3="是青翼蝠王",
									answer4="是白眉鹰王",
									
									gonglue1="#G龙王是好人#W。",
									gonglue2="#G龙王是好人#W。",
									gonglue3="#G说假话的是叛徒#W。",
									gonglue4="#G龙王是叛徒#W。",
									
									result = 1  -- 答案

								},
								{	title="【个人】四大法王",  --任务名称
									info="\t我们明教四大法王中出了一个叛徒，你去询问一下四大法王，他们中有#G三个人#W会告诉你#G真话#W，#G一个人会撒谎#W。\n\t记住，#G撒谎的人不一定是叛徒，叛徒不一定撒谎#W。", --描述
									task1="询问青翼蝠王@npc_"..x300564_g_NpcList[1].."",
									task2="询问白眉鹰王@npc_"..x300564_g_NpcList[2].."",
									task3="询问紫衫龙王@npc_"..x300564_g_NpcList[3].."",
									task4="询问金毛狮王@npc_"..x300564_g_NpcList[4].."",
									text1="\t怎么？！我青翼蝠王竟会被怀疑？哼，我只能告诉你：#G龙王说假话#W。",
									text2="\t我白眉鹰王殷天正，岂是那等背叛明教的宵小之徒！不过，我倒是知道：#G狮王是叛徒#W。",
									text3="\t想不到有人居然会怀疑到我紫衫龙王这里？根据我的推测：#G叛徒说了假话#W。",
									text4="\t谢逊一世豪杰，岂能受这等污蔑！别人我不清楚，但我能肯定：#G龙王说假话#W。",
									answer="\t我已经知道谁是叛徒了，你知道吗？\n\t是金毛狮王？紫衫龙王？白眉鹰王？还是青翼蝠王？\n\t#Y(您可以在任务攻略中查看四大法王说过的话，以便分析。)",
									answer1="是金毛狮王",
									answer2="是紫衫龙王",
									answer3="是青翼蝠王",
									answer4="是白眉鹰王",
									
									gonglue1="#G龙王说假话#W。",
									gonglue2="#G狮王是叛徒#W。",
									gonglue3="#G叛徒说了假话#W。",
									gonglue4="#G龙王说假话#W。",
									
									result = 1  -- 答案

								},
								{	title="【个人】四大法王",  --任务名称
									info="\t我们明教四大法王中出了一个叛徒，你去询问一下四大法王，他们中有#G三个人#W会告诉你#G真话#W，#G一个人会撒谎#W。\n\t记住，#G撒谎的人不一定是叛徒，叛徒不一定撒谎#W。", --描述
									task1="询问青翼蝠王@npc_"..x300564_g_NpcList[1].."",
									task2="询问白眉鹰王@npc_"..x300564_g_NpcList[2].."",
									task3="询问紫衫龙王@npc_"..x300564_g_NpcList[3].."",
									task4="询问金毛狮王@npc_"..x300564_g_NpcList[4].."",
									text1="\t怎么？！我青翼蝠王竟会被怀疑？哼，我只能告诉你：#G我是好人#W。",
									text2="\t我白眉鹰王殷天正，岂是那等背叛明教的宵小之徒！不过，我倒是知道：#G龙王是叛徒#W。",
									text3="\t想不到有人居然会怀疑到我紫衫龙王这里？根据我的推测：#G我说真话#W。",
									text4="\t谢逊一世豪杰，岂能受这等污蔑！别人我不清楚，但我能肯定：#G蝠王是叛徒#W。",
									answer="\t我已经知道谁是叛徒了，你知道吗？\n\t是金毛狮王？紫衫龙王？白眉鹰王？还是青翼蝠王？\n\t#Y(您可以在任务攻略中查看四大法王说过的话，以便分析。)",
									answer1="是金毛狮王",
									answer2="是紫衫龙王",
									answer3="是青翼蝠王",
									answer4="是白眉鹰王",
									
									gonglue1="#G我是好人#W。",
									gonglue2="#G龙王是叛徒#W。",
									gonglue3="#G我说真话#W。",
									gonglue4="#G蝠王是叛徒#W。",
									
									result = 2  -- 答案

								}
							   }	
				

-- 任务奖励物品列表
x300564_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}


function x300564_GetMissionId( sceneId, selfId )
	return x300564_g_MissionId
end

function x300564_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300564_g_LevelLess then
       return
    end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300564_g_MissionName,8,1);
	else
		--local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		--AddQuestNumText(sceneId, myMissionId, x300564_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300564_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
		return
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		if nExt==30 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x300564_g_MissionName)
				AddQuestText(sceneId,"\t诸多证据表明，我明教四大法王中的一位和波斯明教偷袭一事有着莫大关系，我这里有一计，你可愿意一试？")
				AddQuestNumText(sceneId, myMissionId, "好的，交给我吧",2,31);
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId, x300564_g_ScriptId, myMissionId);
			return
		elseif nExt ==31 then
			x300564_GiveQuestion(sceneId, selfId, targetId, MissionId,1)
			return
		end
	end
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

		

		local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
		local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

		if bCompleted>0 then
			local bAnswerQuestion = GetQuestParam( sceneId, selfId, misIndex, 5 )

			if bAnswerQuestion>1 then
				x300564_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			else
				if nExt==7 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
						AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].info)
						AddQuestNumText(sceneId, myMissionId, "我知道谁是叛徒了！",2,20);
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300564_g_ScriptId, myMissionId);
				elseif nExt==20 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
						--AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].info)
						--AddQuestText(sceneId," ")
						AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].answer)
						
						AddQuestNumText(sceneId, myMissionId, x300564_g_QuestionTextList[nQuestionId].answer1,2,21);
						AddQuestNumText(sceneId, myMissionId, x300564_g_QuestionTextList[nQuestionId].answer2,2,22);
						AddQuestNumText(sceneId, myMissionId, x300564_g_QuestionTextList[nQuestionId].answer3,2,23);
						AddQuestNumText(sceneId, myMissionId, x300564_g_QuestionTextList[nQuestionId].answer4,2,24);
						
						
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300564_g_ScriptId, myMissionId);
				elseif nExt>=21 then
					local nAnswer = nExt-20
					local nResult = x300564_g_QuestionTextList[nQuestionId].result;

					if nResult == nAnswer then
						x300564_ShowTips(sceneId, selfId, "不错不错，你说对了！")
						SetQuestByIndex( sceneId, selfId, misIndex, 5, 2 )
						x300564_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
					else
						x300564_ShowTips(sceneId, selfId, "你说错了！真是没用，再去仔细问问！")
						x300564_GiveQuestion(sceneId, selfId, targetId, MissionId,2)
					end
				end
			end
			return
		end
	end
	
	
	if nExt>10 then --跟npc对话时
		if nExt>=20 then
			return
		end

		local iIndex = nExt-10

		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			return
		end

		x300564_DispatchNpcTalkInfo( sceneId, selfId, targetId,myMissionId,iIndex )

	
	else
		
		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			x300564_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			if nExt==7 then -- 任务完成
				--x300564_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
				
				
			else
				
				x300564_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
			end
		end
	end
end


function x300564_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )

	return 1;

end

function x300564_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300564_g_LevelLess then
		x300564_ShowTips(sceneId, selfId, "你等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300564_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end

    local day = GetDayOfYear()
    if GetQuestData( sceneId, selfId, MD_MJFY_DATE[1], MD_MJFY_DATE[2],MD_MJFY_DATE[3] ) == day then
        x300564_ShowTips(sceneId, selfId, "很抱歉，您今天已经做过此任务，不能再次领取" )
        return 0;
    end

    if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == day then
        if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
            Msg2Player( sceneId, selfId, "你不能再领取今天的日常任务了", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
    end

	return 1;

end

function x300564_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end
	
	if x300564_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300564_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
		return 0
	end
	---------------------------- add end -------------------------------
	
	--检查前置任务
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,myMissionId  )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 0
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return 0
		end
	end

	local ret = AddQuest( sceneId, selfId, myMissionId, x300564_g_ScriptId, 0, 0, 0,1)-- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务："..x300564_g_MissionName;
		x300564_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300564_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )
		GamePlayScriptLog(sceneId, selfId, 901)
		return 1
	else
		
		x300564_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end

function x300564_GiveQuestion(sceneId, selfId, targetId, MissionId, nExt)
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "此活动今天不开放")
		return
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )

	local nQuestionId = random(1,x300564_g_QuestionCount)
		
	

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 6, nQuestionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --还没有答题
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x300564_ShowQuestion( sceneId, selfId, targetId,MissionId,nQuestionId, nExt )

	x300564_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300564_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300564_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务："..x300564_g_MissionName;
	    x300564_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_MJFY_DATE[1], MD_MJFY_DATE[2], MD_MJFY_DATE[3], today)
		if today == GetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3] ) then
            local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
            if count < 3 then
                SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1 + count)
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3], today)
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1)
        end
	else
		x300564_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300564_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	
	if x300564_CheckSubmit(sceneId, selfId )>0 then
		
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
            return 0
        end

        if x300564_GiveReward(sceneId,selfId,selectId) == 0 then
            return
        end

		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300564_g_MissionId)

			local str = "您完成了任务："..x300564_g_MissionName;
			x300564_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

            SetQuestData(sceneId, selfId, MD_MJFY_DATE[1], MD_MJFY_DATE[2], MD_MJFY_DATE[3], GetDayOfYear() )

			GamePlayScriptLog(sceneId, selfId, 902)
			
		else
			x300564_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end

function x300564_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

    -- 检查玩家选择的奖励是不是可判定非绑定的
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300564_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
            break
        end
    end

    -- 特殊情况处理，玩家在选择物品后升级跨越到下个奖励区时的处理
    if count == 0 then
        for i, item in x300564_g_RewardTable do
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
        end
    end

    if id == 0 or count == 0 then
        return 0
    end

	BeginAddItem(sceneId)
    if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
        if canBind == 1 then
            AddItem( sceneId, id, count)
        else
            AddBindItem( sceneId, id, count)
        end
    else
		AddBindItem( sceneId, id, count)
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		
		AddItemListToPlayer(sceneId,selfId)
		
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("您获得了物品：@itemid_%d",id))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)

		return 1;
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"背包空间不足，无法获得任务奖励物品，交任务失败")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0;	
	end
end



function x300564_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		x300564_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
	local bAnswered = GetQuestParam( sceneId, selfId, misIndex, 6 )

	if (bCompleted*bAnswered)<=0 then
		return 0
	end

	return 1;
end



---------------------------------------------------------------------------------------------------
--向客户端发送任务信息
---------------------------------------------------------------------------------------------------
function x300564_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300564_g_MissionName)
	AddQuestText(sceneId,"\n\t近日，我中土明教总坛竟然被波斯明教偷袭，丢失了一些至关重要的物事。我明教总坛历来守备森严，如没有内应，波斯人绝不可能如此轻松得手。\n\t现今，我明教广招中原武林同道，誓要将这内奸查出，你不妨前去和我明教执法使冷谦一叙。")
	AddQuestText( sceneId,"#Y任务目标：")
			
	AddQuestText( sceneId,x300564_g_MissionTarget)
			
	AddQuestText(sceneId," ")

	local level = GetLevel(sceneId, selfId)
    for i, item in x300564_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
		
	-- end

	-- if x300564_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300564_g_BonusMoney5)
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300564_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300564_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\t你问过四大法王了吗？")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300564_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300564_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\n\t很好！和我的判断一模一样，辛苦你了，这是你的奖励。")
	
	
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300564_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
		
	-- end

	-- if x300564_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300564_g_BonusMoney5)
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300564_g_ScriptId, MissionId);
	CallScriptFunction( 256225, "Finishfawang", sceneId, selfId)	

end


---------------------------------------------------------------------------------------------------
--向客户端发送题目
---------------------------------------------------------------------------------------------------
function x300564_ShowQuestion( sceneId, selfId, NPCId,MissionId,nQuestionId, nExt )


	if nExt==1 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
	
			AddQuestText( sceneId,x300564_g_QuestionTextList[nQuestionId].info)
		
			
		EndQuestEvent()
	elseif nExt==2 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
			
			AddQuestText( sceneId,"\t根据他们说的话，真相已经很明显了！你居然还没判断出谁是叛徒？\n\t真是没用，再回去仔细问问！\n\t#G（您回答错了，看来只好回去重新询问。）")
		
			
		EndQuestEvent()
	
	else
		return	
	end
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300564_g_ScriptId, MissionId,1);
	


end


function x300564_DispatchNpcTalkInfo( sceneId, selfId, NPCId,MissionId,iIndex )
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	SetQuestByIndex( sceneId, selfId, misIndex, iIndex-1, 1 )

	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	if value1*value2*value3*value4>0 then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		
	end
	
	x300564_QuestLogRefresh( sceneId, selfId, myMissionId );

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300564_g_QuestionTextList[nQuestionId].title)
		
		if iIndex==1 then
			AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].text1)
		elseif iIndex==2 then
			AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].text2)
		elseif iIndex==3 then
			AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].text3)
		elseif iIndex==4 then
			AddQuestText(sceneId,x300564_g_QuestionTextList[nQuestionId].text4)
		end
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300564_g_ScriptId, myMissionId,0);

	

end





---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300564_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300564_GetMissionName(sceneId,selfId),        -- 任务名字
							x300564_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x300564_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300564_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300564_GetMissionText(sceneId,selfId),	--任务描述
							x300564_GetMissionHelp(sceneId,selfId)					--任务小提示
							)
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300564_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	-- local nExpBonus = level*0;
	-- if nExpBonus > 0 then
		-- AddQuestExpBonus( sceneId, nExpBonus)
		
	-- end

	-- if x300564_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300564_g_BonusMoney5)
	-- end
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300564_GetMissionName(sceneId,selfId)
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		return ""..x300564_g_MissionName;
	end

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local str = x300564_g_QuestionTextList[nQuestionId].title

	return str
end

function x300564_GetMissionTask(sceneId,selfId)
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "  #Y任务回复:#G@npc_"..x300564_g_ReplyNpcId;
	end
	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	local strTable = "  ";
	local str1 = strTable..(x300564_g_QuestionTextList[nQuestionId].task1)..format("(%d/1)",value1)
	local str2 = "\n"..strTable..(x300564_g_QuestionTextList[nQuestionId].task2)..format("(%d/1)",value2)
	local str3 = "\n"..strTable..(x300564_g_QuestionTextList[nQuestionId].task3)..format("(%d/1)",value3)
	local str4 = "\n"..strTable..(x300564_g_QuestionTextList[nQuestionId].task4)..format("(%d/1)",value4)

	if value1>=1 then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end
	if value2>=1 then
		str2 = "#G"..str2
	else
		str2 = "#W"..str2
	end
	if value3>=1 then
		str3 = "#G"..str3
	else
		str3 = "#W"..str3
	end
	if value4>=1 then
		str4 = "#G"..str4
	else
		str4 = "#W"..str4
	end

	return str1..str2..str3..str4
end

function x300564_GetReplyNpcId(sceneId,selfId)
	return x300564_g_ReplyNpcId;
end

function x300564_GetMissionMethod(sceneId,selfId)
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	local str=""

	if nMissionStep>0 then
		
		str = x300564_g_MissionTarget1
		
		if value1>=1 then
			str=str.."\n  青翼蝠王说："..x300564_g_QuestionTextList[nQuestionId].gonglue1;
		end
		if value2>=1 then
			str=str.."\n  白眉鹰王说："..x300564_g_QuestionTextList[nQuestionId].gonglue2;
		end
		if value3>=1 then
			str=str.."\n  紫衫龙王说："..x300564_g_QuestionTextList[nQuestionId].gonglue3;
		end
		if value4>=1 then
			str=str.."\n  金毛狮王说："..x300564_g_QuestionTextList[nQuestionId].gonglue4;
		end
		
		
	else
		str = x300564_g_MissionTarget
	end

	return str
end

function x300564_GetMissionText(sceneId,selfId)
	return "\t我们明教四大法王中出了一个叛徒，你去询问一下四大法王，他们中有#G三个人#W会告诉你#G真话#W，#G一个人#W会#G撒谎#W。\n\t记住，#G撒谎的人不一定是叛徒，叛徒不一定撒谎#W。"
end

function x300564_GetMissionHelp(sceneId,selfId)
	return "\t如何识别叛徒？四个法王中有#R三个人#G会告诉你#R真话#G，#R一个人会撒谎#G。先找出有#R两句是正好矛盾#G的，那么其中#R必有一句是假话#G；那么另外两个法王说的一定是真话，根据他们的真话，往往能推论出谁是叛徒。\n\t记住，#R撒谎的人不一定是叛徒，叛徒不一定撒谎#G。"
end



function x300564_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300564_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300564_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if GetGameOpenById(x300564_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300564_g_MissionId) == 0 then
		
		return
	end
	local myMissionId = x300564_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	if npcGuid == x300564_g_ReplyNpcId then
		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
		
		if nStep==0 then
			AddQuestNumText(sceneId, x300564_g_MissionId, x300564_g_MissionName,2,30);
		elseif nStep>0 then
			local state = GetQuestStateNM(sceneId, selfId, npcGuid, myMissionId);

		
			AddQuestNumText(sceneId, myMissionId, x300564_g_MissionName,state,state);
		end
	
	else
		local bFind =0;
		local iIndex=0
		for i,item in x300564_g_NpcList do
			iIndex = iIndex+1;
			if npcGuid==item then
				bFind=1;
				break;
			end
		end

		

		if bFind==0 then
			return
		end

		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

		if nStep~=1 then
			return
		end



		
		local value = GetQuestParam( sceneId, selfId, misIndex, iIndex-1)

		if value==0 then


			AddQuestNumText(sceneId, x300564_g_MissionId, x300564_g_QuestionTextList[nQuestionId].title,2,iIndex+10);
		end
	end
	

	
end

function x300564_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end



--// system end




