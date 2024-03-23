--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300578_g_MissionId 				= 	9334                     --任务ID
x300578_g_ScriptId 					= 	300578                  --脚本ID
x300578_g_MissionKind 				= 	1                       --任务类型
x300578_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制


x300578_g_MissionName				= 	"【个人】黄道吉日"
x300578_g_MissionName1				= 	"你什么时候可以出海"
x300578_g_MissionTarget				= 	"前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期"
x300578_g_MissionTarget1				= 	"询问水手们，确定出航日期"
x300578_g_MissionInfo				= 	""
x300578_g_ContinueInfo				= 	""
x300578_g_MissionCompleted			= 	""
x300578_g_MissionHelp				=	""          --任务提示信息

--目标
x300578_g_ExtTarget					=	{ {type=20,n=1,target="黄道吉日"}}

--奖励

x300578_g_ExpBonus					= 	0;--x300578_AddExpAward               	--奖励：经验
x300578_g_BonusItem					=	{{item=11050003, n=8}}	--奖励：物品

x300578_g_BonusMoney1               = 	0
x300578_g_BonusMoney2               =   0
x300578_g_BonusMoney3               =   0
x300578_g_BonusMoney5				=	0

x300578_g_BonusChoiceItem           =   {}


--MisDescEnd


x300578_g_NpcList = {143099,143100,143101,143102,143103,143104,143105,143106}
x300578_g_ReplyNpcId = 143145


-- Mission Text list

x300578_g_GameId			= 1015

x300578_g_QuestionCount		= 9	
x300578_g_QuestionTextList	= {
								{	title="【个人】黄道吉日",  --任务名称
								  title1="你什么时候可以出海", 
									info="\t在一周的七天里，这些水手们各自都有几天不愿上船，#Y@myname#W，你可否帮我问问他们，找出究竟何日他们都可以登船出海？", --描述
									task="前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期",
									text1="\t船主又派人来问我？我周一，周三不登船。",
									text2="\t我的习惯是，除了周五，周六，我都可以登船。",
									text3="\t别问了，每周我只有周一，周四，周日登船。",
									text4="\t我是个喜欢有规律的水手，每周日和周六我不登船。",
									text5="\t恩？我在周三，周六，周日从不登船",
									text6="\t周一，周二我不登船。",
									text7="\t除了周三，周四，周六以外，我都不登船。",
									text8="\t听说周一和周五容易起风暴，我在这两天不登船。",
									answer="\t你打听明白了？他们在周几都可以登船？\n\t#Y(您可以在任务攻略中查看水手们说过的话，以便分析。)",
									answer1="周一",
									answer2="周二",
									answer3="周三",
									answer4="周四",
									answer5="周五",
									answer6="周六",
									answer7="周日",
									
									gonglue1="#G周一，三不登船#W。",
									gonglue2="#G周五，六不登船#W。",
									gonglue3="#G周一，四，日登船#W。",
									gonglue4="#G周六，日不登船#W。",
									gonglue5="#G周三，六，日不登船#W。",
									gonglue6="#G周一，二不登船#W。",
									gonglue7="#G周三，四，六登船#W。",
									gonglue8="#G周一，周五不登船#W。",

									
									result = 4  -- 答案

								},
								{title="【个人】黄道吉日",  --任务名称
								 title1="你什么时候可以出海", 
									info="\t在一周的七天里，这些水手们各自都有几天不愿上船，#Y@myname#W，你可否帮我问问他们，找出究竟何日他们都可以登船出海？", --描述
									task="前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期",
									text1="\t船主又派人来问我？我周一，周三不登船。",
									text2="\t我的习惯是，除了周五，周六，我都可以登船。",
									text3="\t别问了，每周我只有周二，周四，周日登船。",
									text4="\t我是个喜欢有规律的水手，每周日和周六我不登船。",
									text5="\t恩？我在周三，周六，周日从不登船",
									text6="\t周一，周四我不登船。",
									text7="\t除了周二，周四，周六以外，我都不登船。",
									text8="\t听说周一和周五容易起风暴，我在这两天不登船。",
									answer="\t你打听明白了？他们在周几都可以登船？\n\t#Y(您可以在任务攻略中查看水手们说过的话，以便分析。)",
									answer1="周一",
									answer2="周二",
									answer3="周三",
									answer4="周四",
									answer5="周五",
									answer6="周六",
									answer7="周日",
									
									gonglue1="#G周一，三不登船#W。",
									gonglue2="#G周五，六不登船#W。",
									gonglue3="#G周二，四，日登船#W。",
									gonglue4="#G周六，日不登船#W。",
									gonglue5="#G周三，六，日不登船#W。",
									gonglue6="#G周一，四不登船#W。",
									gonglue7="#G周二，四，六登船#W。",
									gonglue8="#G周一，周五不登船#W。",

                 	result = 2  -- 答案
								},
								{
									title="【个人】黄道吉日",  --任务名称
									 title1="你什么时候可以出海", 
									info="\t在一周的七天里，这些水手们各自都有几天不愿上船，#Y@myname#W，你可否帮我问问他们，找出究竟何日他们都可以登船出海？", --描述
									task="前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期",
									text1="\t船主又派人来问我？我周二，周三不登船。",
									text2="\t我的习惯是，除了周五，周六，我都可以登船。",
									text3="\t别问了，每周我只有周一，周三，周四，周日登船。",
									text4="\t我是个喜欢有规律的水手，每周日和周六我不登船。",
									text5="\t恩？我在周三，周六，周日从不登船",
									text6="\t周二，周五我不登船。",
									text7="\t除了周一，周四，周六以外，我都不登船。",
									text8="\t听说周四和周五容易起风暴，我在这两天不登船。",
									answer="\t你打听明白了？他们在周几都可以登船？\n\t#Y(您可以在任务攻略中查看水手们说过的话，以便分析。)",
									answer1="周一",
									answer2="周二",
									answer3="周三",
									answer4="周四",
									answer5="周五",
									answer6="周六",
									answer7="周日",
									
									gonglue1="#G周二，三不登船#W。",
									gonglue2="#G周五，六不登船#W。",
									gonglue3="#G周一，三，四，日登船#W。",
									gonglue4="#G周六，日不登船#W。",
									gonglue5="#G周三，六，日不登船#W。",
									gonglue6="#G周二，五不登船#W。",
									gonglue7="#G周一，四，六登船#W。",
									gonglue8="#G周四，周五不登船#W。",

									
									result = 1  -- 答案
								},
								{title="【个人】黄道吉日",  --任务名称
								 title1="你什么时候可以出海", 
									info="\t在一周的七天里，这些水手们各自都有几天不愿上船，#Y@myname#W，你可否帮我问问他们，找出究竟何日他们都可以登船出海？", --描述
									task="前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期",
									text1="\t船主又派人来问我？我周一，周二不登船。",
									text2="\t我的习惯是，除了周五，周六，我都可以登船。",
									text3="\t别问了，每周我只有周三，周四，周日登船。",
									text4="\t我是个喜欢有规律的水手，每周日和周六我不登船。",
									text5="\t恩？我在周一，周六，周日从不登船",
									text6="\t周二，周五我不登船。",
									text7="\t除了周三，周四，周六以外，我都不登船。",
									text8="\t听说周四和周五容易起风暴，我在这两天不登船。",
									answer="\t你打听明白了？他们在周几都可以登船？\n\t#Y(您可以在任务攻略中查看水手们说过的话，以便分析。)",
									answer1="周一",
									answer2="周二",
									answer3="周三",
									answer4="周四",
									answer5="周五",
									answer6="周六",
									answer7="周日",
									
									gonglue1="#G周一，二不登船#W。",
									gonglue2="#G周五，六不登船#W。",
									gonglue3="#G周三，四，日登船#W。",
									gonglue4="#G周六，日不登船#W。",
									gonglue5="#G周一，六，日不登船#W。",
									gonglue6="#G周二，五不登船#W。",
									gonglue7="#G周三，四，六登船#W。",
									gonglue8="#G周四，周五不登船#W。",

									
									result = 3 -- 答案
								},
								
								{
								title="【个人】黄道吉日",  --任务名称
								 title1="你什么时候可以出海", 
									info="\t在一周的七天里，这些水手们各自都有几天不愿上船，#Y@myname#W，你可否帮我问问他们，找出究竟何日他们都可以登船出海？", --描述
									task="前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期",
									text1="\t船主又派人来问我？我周二，周三不登船。",
									text2="\t我的习惯是，除了周四，周六，我都可以登船。",
									text3="\t别问了，每周我只有周三，周五，周日登船。",
									text4="\t我是个喜欢有规律的水手，每周日和周六我不登船。",
									text5="\t恩？我在周一，周六，周日从不登船",
									text6="\t周二，周三我不登船。",
									text7="\t除了周三，周五，周六以外，我都不登船。",
									text8="\t听说周四和周六容易起风暴，我在这两天不登船。",
									answer="\t你打听明白了？他们在周几都可以登船？\n\t#Y(您可以在任务攻略中查看水手们说过的话，以便分析。)",
									answer1="周一",
									answer2="周二",
									answer3="周三",
									answer4="周四",
									answer5="周五",
									answer6="周六",
									answer7="周日",
									
									gonglue1="#G周二，三不登船#W。",
									gonglue2="#G周四，六不登船#W。",
									gonglue3="#G周三，五，日登船#W。",
									gonglue4="#G周六，日不登船#W。",
									gonglue5="#G周一，六，日不登船#W。",
									gonglue6="#G周二，三不登船#W。",
									gonglue7="#G周三，五，六登船#W。",
									gonglue8="#G周四，周六不登船#W。",

									
									result = 5 -- 答案
								},
								
								{title="【个人】黄道吉日",  --任务名称
								 title1="你什么时候可以出海", 
									info="\t在一周的七天里，这些水手们各自都有几天不愿上船，#Y@myname#W，你可否帮我问问他们，找出究竟何日他们都可以登船出海？", --描述
									task="前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期",
									text1="\t船主又派人来问我？我周二，周三不登船。",
									text2="\t我的习惯是，除了周四，我都可以登船。",
									text3="\t别问了，每周我只有周三，周五，周六登船。",
									text4="\t我是个喜欢有规律的水手，每周五和周日我不登船。",
									text5="\t恩？我在周一，周五，周日从不登船",
									text6="\t周二，周三我不登船。",
									text7="\t除了周三，周五，周六以外，我都不登船。",
									text8="\t听说周四和周五容易起风暴，我在这两天不登船。",
									answer="\t你打听明白了？他们在周几都可以登船？\n\t#Y(您可以在任务攻略中查看水手们说过的话，以便分析。)",
									answer1="周一",
									answer2="周二",
									answer3="周三",
									answer4="周四",
									answer5="周五",
									answer6="周六",
									answer7="周日",
									
									gonglue1="#G周二，三不登船#W。",
									gonglue2="#G周四不登船#W。",
									gonglue3="#G周三，五，六登船#W。",
									gonglue4="#G周五，日不登船#W。",
									gonglue5="#G周一，五，日不登船#W。",
									gonglue6="#G周二，三不登船#W。",
									gonglue7="#G周三，五，六登船#W。",
									gonglue8="#G周四，周五不登船#W。",

									
									result = 6 -- 答案
								
								},
								{title="【个人】黄道吉日",  --任务名称
								 title1="你什么时候可以出海", 
									info="\t在一周的七天里，这些水手们各自都有几天不愿上船，#Y@myname#W，你可否帮我问问他们，找出究竟何日他们都可以登船出海？", --描述
									task="前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期",
									text1="\t船主又派人来问我？我周二，周三不登船。",
									text2="\t我的习惯是，除了周四，我都可以登船。",
									text3="\t别问了，每周我只有周三，周五，周日登船。",
									text4="\t我是个喜欢有规律的水手，每周五和周六我不登船。",
									text5="\t恩？我在周一，周五，周六从不登船",
									text6="\t周二，周三我不登船。",
									text7="\t除了周三，周五，周日以外，我都不登船。",
									text8="\t听说周四和周五容易起风暴，我在这两天不登船。",
									answer="\t你打听明白了？他们在周几都可以登船？\n\t#Y(您可以在任务攻略中查看水手们说过的话，以便分析。)",
									answer1="周一",
									answer2="周二",
									answer3="周三",
									answer4="周四",
									answer5="周五",
									answer6="周六",
									answer7="周日",
									
									gonglue1="#G周二，三不登船#W。",
									gonglue2="#G周四不登船#W。",
									gonglue3="#G周三，五，日登船#W。",
									gonglue4="#G周五，六不登船#W。",
									gonglue5="#G周一，五，六不登船#W。",
									gonglue6="#G周二，三不登船#W。",
									gonglue7="#G周三，五，日登船#W。",
									gonglue8="#G周四，周五不登船#W。",

									
									result = 7 -- 答案
								
								},
								{title="【个人】黄道吉日",  --任务名称
								 title1="你什么时候可以出海", 
									info="\t在一周的七天里，这些水手们各自都有几天不愿上船，#Y@myname#W，你可否帮我问问他们，找出究竟何日他们都可以登船出海？", --描述
									task="前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期",
									text1="\t船主又派人来问我？我周一，周二不登船。",
									text2="\t我的习惯是，除了周二，周五我都可以登船。",
									text3="\t别问了，每周我只有周三，周五登船。",
									text4="\t我是个喜欢有规律的水手，每周五和周六我不登船。",
									text5="\t恩？我在周一，周五，周六从不登船",
									text6="\t周二，周四我不登船。",
									text7="\t除了周三，周五，周日以外，我都不登船。",
									text8="\t听说周四和周五容易起风暴，我在这两天不登船。",
									answer="\t你打听明白了？他们在周几都可以登船？\n\t#Y(您可以在任务攻略中查看水手们说过的话，以便分析。)",
									answer1="周一",
									answer2="周二",
									answer3="周三",
									answer4="周四",
									answer5="周五",
									answer6="周六",
									answer7="周日",
									
									gonglue1="#G周一，二不登船#W。",
									gonglue2="#G周二，五不登船#W。",
									gonglue3="#G周三，五登船#W。",
									gonglue4="#G周五，六不登船#W。",
									gonglue5="#G周一，五，六不登船#W。",
									gonglue6="#G周二，四不登船#W。",
									gonglue7="#G周三，五，日登船#W。",
									gonglue8="#G周四，周五不登船#W。",

									
									result = 3 -- 答案
								
								},
								{title="【个人】黄道吉日",  --任务名称
								 title1="你什么时候可以出海", 
									info="\t在一周的七天里，这些水手们各自都有几天不愿上船，#Y@myname#W，你可否帮我问问他们，找出究竟何日他们都可以登船出海？", --描述
									task="前往@npc_85055和@npc_85056，询问扬武号的水手们，确定出航日期",
									text1="\t船主又派人来问我？我周二，周三不登船。",
									text2="\t我的习惯是，除了周二，周五我都可以登船。",
									text3="\t别问了，每周我只有周一，周五，周日登船。",
									text4="\t我是个喜欢有规律的水手，每周五和周六我不登船。",
									text5="\t恩？我在周二，周五，周六从不登船",
									text6="\t周三，周四我不登船。",
									text7="\t除了周一，周五以外，我都不登船。",
									text8="\t听说周四和周五容易起风暴，我在这两天不登船。",
									answer="\t你打听明白了？他们在周几都可以登船？\n\t#Y(您可以在任务攻略中查看水手们说过的话，以便分析。)",
									answer1="周一",
									answer2="周二",
									answer3="周三",
									answer4="周四",
									answer5="周五",
									answer6="周六",
									answer7="周日",
									
									gonglue1="#G周二，三不登船#W。",
									gonglue2="#G周二，五不登船#W。",
									gonglue3="#G周一，五，日登船#W。",
									gonglue4="#G周五，六不登船#W。",
									gonglue5="#G周二，五，六不登船#W。",
									gonglue6="#G周三，四不登船#W。",
									gonglue7="#G周一，五登船#W。",
									gonglue8="#G周四，周五不登船#W。",

									
									result = 1 -- 答案
								
								},
							   }	
				

-- 任务奖励物品列表
x300578_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}


function x300578_GetMissionId( sceneId, selfId )
	return x300578_g_MissionId
end

function x300578_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel( sceneId,selfId )
    if level < x300578_g_LevelLess then
       return
    end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300578_g_MissionName,8,1);
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x300578_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300578_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
		return
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )	
	
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

		

		local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )
		local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

		if bCompleted>0 then
			local bAnswerQuestion = GetQuestParam( sceneId, selfId, misIndex, 5 )

			if bAnswerQuestion>1 then
				x300578_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			else
				if nExt==7 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
						AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].info)
						AddQuestNumText(sceneId, myMissionId, "我知道哪天能出海了",2,20);
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300578_g_ScriptId, myMissionId);
				elseif nExt==20 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
						--AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].info)
						--AddQuestText(sceneId," ")
						AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].answer)
						
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer1,2,21);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer2,2,22);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer3,2,23);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer4,2,24);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer5,2,25);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer6,2,26);
						AddQuestNumText(sceneId, myMissionId, x300578_g_QuestionTextList[nQuestionId].answer7,2,27);
						
						
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300578_g_ScriptId, myMissionId);
				elseif nExt>=21 then
					local nAnswer = nExt-20
					local nResult = x300578_g_QuestionTextList[nQuestionId].result;

					if nResult == nAnswer then
						x300578_ShowTips(sceneId, selfId, "太好了！我这就吩咐下去让他们开始准备。")
						SetQuestByIndex( sceneId, selfId, misIndex, 5, 2 )
						x300578_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
					else
						x300578_ShowTips(sceneId, selfId, "真的吗？我看未必吧，你还是再去问问，耽误了开船可是大事。")
						x300578_GiveQuestion(sceneId, selfId, targetId, MissionId,2)
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

		x300578_DispatchNpcTalkInfo( sceneId, selfId, targetId,myMissionId,iIndex )

	
	else
		
		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			x300578_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			if nExt==7 then -- 任务完成
				--x300578_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
				
				
			else
				
				x300578_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
			end
		end
	end
end


function x300578_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )

	return 1;

end

function x300578_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300578_g_LevelLess then
		x300578_ShowTips(sceneId, selfId, "你等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300578_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end

    local day = GetDayOfYear()
    if day == GetQuestData( sceneId, selfId, MD_HDJR_DATE[1], MD_HDJR_DATE[2],MD_HDJR_DATE[3] ) then
        Msg2Player( sceneId, selfId, "很抱歉，您今天已经做过此任务，不能再次领取", 8, 3)
        return 0
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

function x300578_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0
	end
	
	if x300578_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300578_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
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

	local ret = AddQuest( sceneId, selfId, myMissionId, x300578_g_ScriptId, 0, 0, 0,1)-- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务："..x300578_g_MissionName;
		x300578_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300578_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )
		
		x300578_GiveQuestion(sceneId, selfId, targetId, MissionId,1)

		GamePlayScriptLog(sceneId, selfId, 851)
		return 1
	else
		
		x300578_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end

function x300578_GiveQuestion(sceneId, selfId, targetId, MissionId, nExt)
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "此活动今天不开放")
		return
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )

	local nQuestionId = random(1,x300578_g_QuestionCount)
		
	

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 6, nQuestionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --还没有答题
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x300578_ShowQuestion( sceneId, selfId, targetId,MissionId,nQuestionId, nExt )

	x300578_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300578_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300578_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务："..x300578_g_MissionName;
	    x300578_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData( sceneId, selfId, MD_HDJR_DATE[1], MD_HDJR_DATE[2], MD_HDJR_DATE[3], today)
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
		x300578_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300578_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	
	if x300578_CheckSubmit(sceneId, selfId )>0 then
		
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
            return 0
        end

		if x300578_GiveReward(sceneId,selfId,selectId)<=0 then
			return
		end
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300578_g_MissionId)

			local str = "您完成了任务:"..x300578_g_MissionName;
			x300578_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

            SetQuestData( sceneId, selfId, MD_HDJR_DATE[1], MD_HDJR_DATE[2], MD_HDJR_DATE[3], GetDayOfYear() )

			GamePlayScriptLog(sceneId, selfId, 852)
			
		else
			x300578_ShowTips(sceneId, selfId, "交任务失败")
		end
		
	end
end

function x300578_GiveReward(sceneId,selfId,selectRadioId)
	
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300578_g_RewardTable do
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
        for i, item in x300578_g_RewardTable do
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
		
		
        Msg2Player( sceneId, selfId, format("您获得了物品：@itemid_%d",id), 8, 3)

		return 1;
	else
        Msg2Player( sceneId, selfId, "背包空间不足，无法获得任务奖励物品，交任务失败", 8, 3)
		return 0;	
	end
end



function x300578_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		x300578_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
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
function x300578_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300578_g_MissionName)
	AddQuestText(sceneId,"\t扬武号上的这群水手们，要说起本事，个个都有一手绝活，但要说起他们那些怪脾气，可真是一言难尽啊。\n\t这几天扬武号就要出海，可是这些家伙，个个都有十足的理由不愿意上船！")
	AddQuestText( sceneId,"#Y任务目标：")
			
	AddQuestText( sceneId,x300578_g_MissionTarget)
			
	AddQuestText(sceneId," ")

	local level = GetLevel(sceneId, selfId)
    for i, item in x300578_g_RewardTable do
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

	-- if x300578_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300578_g_BonusMoney5)
	-- end

	-- for i, item2 in x300578_g_BonusItem do
		
		-- AddQuestItemBonus(sceneId, item2.item, item2.n)
		
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300578_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300578_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\t你问那些水手们了吗？")
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300578_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300578_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\t太好了！我这就吩咐下去让他们开始准备。这是我的一点小小的心意，你可千万不要推辞。")
	
	
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300578_g_RewardTable do
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

	-- if x300578_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300578_g_BonusMoney5)
	-- end

	-- for i, item2 in x300578_g_BonusItem do
		
		-- AddQuestItemBonus(sceneId, item2.item, item2.n)
		
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300578_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--向客户端发送题目
---------------------------------------------------------------------------------------------------
function x300578_ShowQuestion( sceneId, selfId, NPCId,MissionId,nQuestionId, nExt )


	if nExt==1 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
	
			AddQuestText( sceneId,x300578_g_QuestionTextList[nQuestionId].info)
		
			
		EndQuestEvent()
	elseif nExt==2 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
			
			AddQuestText( sceneId,"\t真的吗？我看未必吧，你还是再去问问，耽误了开船可是大事。")
		
			
		EndQuestEvent()
	
	else
		return	
	end
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300578_g_ScriptId, MissionId,1);
	


end


function x300578_DispatchNpcTalkInfo( sceneId, selfId, NPCId,MissionId,iIndex )
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	
	--验证这个NPC是否对过话
	local npcGuid = GetMonsterGUID(sceneId,NPCId)
	
	local bFind =0;
	local iIndex=0
	for i,item in x300578_g_NpcList do
		iIndex = iIndex+1;
		if npcGuid==item then
			bFind=1;
			break;
		end
	end	

	if bFind==0 then
		return
	else
		
		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
		if nStep~=1 then
			return
		end
	
		local data1 = GetQuestParam( sceneId, selfId, misIndex, 1 )
		local data2 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	
		local value4 = floor(data1/1000)
		local value3 = floor(mod(data1,1000)/100)
		local value2 = floor(mod(data1,100)/10)
		local value1 = floor(mod(data1,10)/1)
	
		local value8 = floor(data2/1000)
		local value7 = floor(mod(data2,1000)/100)
		local value6 = floor(mod(data2,100)/10)
		local value5 = floor(mod(data2,10)/1)
	
		local temp_list = {value1,value2,value3,value4,value5,value6,value7,value8}
		local value = temp_list[iIndex]
	
		if value~=0 then
			--当NPC对过话，那么直接返回，不进行处理
			return
		end
	end

	
	
	--以下设置这个NPC的对话属性
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 2 )

	if iIndex<=4 then
		
		local nValue = GetQuestParam( sceneId, selfId, misIndex, 1 )

		local nAdd = 1
		for i=1, iIndex-1 do
			nAdd = 10*nAdd
		end

		SetQuestByIndex( sceneId, selfId, misIndex, 1, nValue+nAdd )
		value1 = nValue+nAdd
	else
		local nValue = GetQuestParam( sceneId, selfId, misIndex, 2 )

		local nAdd = 1
		for i=1, iIndex-5 do
			nAdd = 10*nAdd
		end

		SetQuestByIndex( sceneId, selfId, misIndex, 2, nValue+nAdd )

		value2 = nValue+nAdd
	end

	

	
	if value1==1111 and value2==1111 then
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )

		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
		
	end
	
	x300578_QuestLogRefresh( sceneId, selfId, myMissionId );

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300578_g_QuestionTextList[nQuestionId].title)
		
		if iIndex==1 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text1)
		elseif iIndex==2 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text2)
		elseif iIndex==3 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text3)
		elseif iIndex==4 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text4)
		elseif iIndex==5 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text5)
		elseif iIndex==6 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text6)
		elseif iIndex==7 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text7)
		elseif iIndex==8 then
			AddQuestText(sceneId,x300578_g_QuestionTextList[nQuestionId].text8)
		end
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300578_g_ScriptId, myMissionId,0);

	

end





---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300578_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300578_GetMissionName(sceneId,selfId),        -- 任务名字
							x300578_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x300578_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300578_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300578_GetMissionText(sceneId,selfId),	--任务描述
							x300578_GetMissionHelp(sceneId,selfId)					--任务小提示
							)
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300578_g_RewardTable do
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

	-- if x300578_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300578_g_BonusMoney5)
	-- end

	-- for i, item2 in x300578_g_BonusItem do
		
		-- AddQuestItemBonus(sceneId, item2.item, item2.n)
		
	-- end
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300578_GetMissionName(sceneId,selfId)
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local str = x300578_g_QuestionTextList[nQuestionId].title

	return str
end

function x300578_GetMissionTask(sceneId,selfId)
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	
	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )

	local strTable = "  ";
	local str1 = strTable..(x300578_g_QuestionTextList[nQuestionId].task)..format("(%d/1)",value1)

	if value1>=1 then
		str1 = "#G"..str1
	else
		str1 = "#W"..str1
	end

	return str1
end

function x300578_GetReplyNpcId(sceneId,selfId)
	return x300578_g_ReplyNpcId;
end

function x300578_GetMissionMethod(sceneId,selfId)
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	



	local data1 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local data2 = GetQuestParam( sceneId, selfId, misIndex, 2 )

	
	local value4 = floor(data1/1000)
	local value3 = floor(mod(data1,1000)/100)
	local value2 = floor(mod(data1,100)/10)
	local value1 = floor(mod(data1,10)/1)

	local value8 = floor(data2/1000)
	local value7 = floor(mod(data2,1000)/100)
	local value6 = floor(mod(data2,100)/10)
	local value5 = floor(mod(data2,10)/1)

	local str=""

	if nMissionStep>0 then
		
		str = x300578_g_MissionTarget1
		
		if value1>=1 then
			str=str.."\n  大副："..x300578_g_QuestionTextList[nQuestionId].gonglue1;
		end
		if value2>=1 then
			str=str.."\n  二副："..x300578_g_QuestionTextList[nQuestionId].gonglue2;
		end
		if value3>=1 then
			str=str.."\n  船匠："..x300578_g_QuestionTextList[nQuestionId].gonglue3;
		end
		if value4>=1 then
			str=str.."\n  船工："..x300578_g_QuestionTextList[nQuestionId].gonglue4;
		end

		if value5>=1 then
			str=str.."\n  帆手："..x300578_g_QuestionTextList[nQuestionId].gonglue5;
		end
		if value6>=1 then
			str=str.."\n  炮手："..x300578_g_QuestionTextList[nQuestionId].gonglue6;
		end
		if value7>=1 then
			str=str.."\n  舵手："..x300578_g_QuestionTextList[nQuestionId].gonglue7;
		end
		if value8>=1 then
			str=str.."\n  领航："..x300578_g_QuestionTextList[nQuestionId].gonglue8;
		end
		
		
	else
		str = x300578_g_MissionTarget
	end

	return str
end

function x300578_GetMissionText(sceneId,selfId)
	return "\t扬武号的水手们都有些怪脾气，每周，他们各自都有不愿意出海的几天，你能帮我去询问他们一番，找出哪天他们可以共同登船出海。"
end

function x300578_GetMissionHelp(sceneId,selfId)
	return "\t每个水手都会告诉你一些他们何时可以登船的信息，根据这些信息，就能找出哪天他们都可以登船。"
end



function x300578_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300578_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300578_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if GetGameOpenById(x300578_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300578_g_MissionId) == 0 then
		
		return
	end
	local myMissionId = x300578_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	
	local bFind =0;
	local iIndex=0
	for i,item in x300578_g_NpcList do
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



	local data1 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local data2 = GetQuestParam( sceneId, selfId, misIndex, 2 )

	
	local value4 = floor(data1/1000)
	local value3 = floor(mod(data1,1000)/100)
	local value2 = floor(mod(data1,100)/10)
	local value1 = floor(mod(data1,10)/1)

	local value8 = floor(data2/1000)
	local value7 = floor(mod(data2,1000)/100)
	local value6 = floor(mod(data2,100)/10)
	local value5 = floor(mod(data2,10)/1)

	local temp_list = {value1,value2,value3,value4,value5,value6,value7,value8}

	local value = temp_list[iIndex]

	if value==0 then


		AddQuestNumText(sceneId, x300578_g_MissionId, x300578_g_QuestionTextList[nQuestionId].title1,2,iIndex+10);
	end
	
	

	
end

function x300578_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end



--// system end




