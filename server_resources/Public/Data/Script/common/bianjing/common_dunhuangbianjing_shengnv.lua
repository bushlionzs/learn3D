--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300581_g_MissionId 				= 	9501                     --任务ID
x300581_g_ScriptId 					= 	300581                  --脚本ID
x300581_g_MissionKind 				= 	1                       --任务类型
x300581_g_LevelLess					= 	40                      --场景开放等级  <=0 表示不限制


x300581_g_MissionName				= 	"【个人】赵王府选美"
x300581_g_MissionTarget				= 	"找到@npc_139406"
x300581_g_MissionTarget1				= 	"询问四位赵王客卿"
x300581_g_MissionInfo				= 	""
x300581_g_ContinueInfo				= 	""
x300581_g_MissionCompleted			= 	""
x300581_g_MissionHelp				=	""          --任务提示信息

--目标
x300581_g_ExtTarget					=	{ {type=20,n=1,target="赵王府选美"}}

--奖励

x300581_g_ExpBonus					= 	0;--x300581_AddExpAward               	--奖励：经验


x300581_g_BonusMoney1               = 	0
x300581_g_BonusMoney2               =   0
x300581_g_BonusMoney3               =   0
x300581_g_BonusMoney5				=	0

x300581_g_BonusChoiceItem           =   {}
x300581_g_BonusItem					=   {{item=11050004,n=8}}	--奖励：物品


--MisDescEnd

x300581_g_NpcList = {139405,141533,141534,141535}
x300581_g_ReplyNpcId = 139406


-- Mission Text list

x300581_g_GameId			= 1024

x300581_g_QuestionCount		= 8
x300581_g_QuestionTextList	= {
								{	title="【个人】赵王府选美",  --任务名称
									info="\t赵王府之中的四位客卿见多识广，前去请教一番便能知晓谁是最出色的回鹘美人。", --描述
									task1="询问@npc_"..x300581_g_NpcList[1].."",
								  task2="询问@npc_"..x300581_g_NpcList[2].."",
									task3="询问@npc_"..x300581_g_NpcList[3].."",
									task4="询问@npc_"..x300581_g_NpcList[4].."",
									text1="\t你是来打听回鹘美人之事？我可以告诉你：回鹘第一美人所穿衣服会有#G黄色#W。",
									text2="\t今早四位回鹘美人我见到了：回鹘第一美人所穿衣服有#G红色#W和#G蓝色#W。",
									text3="\t回鹘第一美人？我可以很肯定的说：回鹘第一美人今日所穿衣服有#G白色#W。",
									text4="\t我敢断定：衣服上有#G黑色#W的人，必不是回鹘第一美人。",
									answer="\t你现在知道谁是回鹘第一美人吗？\n\t是#G药罗葛丽#W？#G古力裴娜#W？#G黠多丽罗#W？还是#G顿英贺宁#W？\n\t#Y(您可以在任务攻略中查看四位赵王客卿说过的话，以便分析。)",
									answer1="是药罗葛丽",
									answer2="是古力裴娜",
									answer3="是黠多丽罗",
									answer4="是顿英贺宁",
									
								  gonglue1="#G衣服上有黄色#W",
									gonglue2="#G衣服上有红色和蓝色#W",
									gonglue3="#G衣服上有白色#W",
									gonglue4="#G衣服上没有黑色#W",
									
									result = 1  -- 答案

								},
							  {	title="【个人】赵王府选美",  --任务名称
									info="\t赵王府之中的四位先生见多识广，前去请教一番便能知晓谁是最出色的回鹘美人。", --描述
									task1="询问@npc_"..x300581_g_NpcList[1].."",
								  task2="询问@npc_"..x300581_g_NpcList[2].."",
									task3="询问@npc_"..x300581_g_NpcList[3].."",
									task4="询问@npc_"..x300581_g_NpcList[4].."",
									text1="\t你是来打听回鹘美人之事？我可以告诉你：回鹘第一美人所穿衣服会有#G蓝色#W。",
									text2="\t今早四位回鹘美人我见到了：回鹘第一美人所穿衣服有#G黄色#W没有#G粉色#W。",
									text3="\t回鹘第一美人？我可以很肯定的说：回鹘第一美人所穿衣服有#G红色#W和#G蓝色#W。",
									text4="\t我敢断定：回鹘第一美人的衣服上有#G白色#W。",
									answer="\t你现在知道谁是回鹘第一美人了吗？\n\t是#G药罗葛丽#W？#G古力裴娜#W？#G黠多丽罗#W？还是#G顿英贺宁#W？\n\t#Y(您可以在任务攻略中查看知情人说过的话，以便分析。)",
									answer1="是药罗葛丽",
									answer2="是古力裴娜",
									answer3="是黠多丽罗",
									answer4="是顿英贺宁",
									
									gonglue1="#G衣服上有蓝色#W",
									gonglue2="#G衣服上有黄色没有粉色#W",
									gonglue3="#G衣服上有红色和蓝色#W",
									gonglue4="#G衣服上有白色#W",
									
									result = 1  -- 答案

								},
								{	title="【个人】赵王府选美",  --任务名称
									info="\t赵王府之中的四位先生见多识广，前去请教一番便能知晓谁是最出色的回鹘美人。", --描述
									task1="询问@npc_"..x300581_g_NpcList[1].."",
								  task2="询问@npc_"..x300581_g_NpcList[2].."",
									task3="询问@npc_"..x300581_g_NpcList[3].."",
									task4="询问@npc_"..x300581_g_NpcList[4].."",
									text1="\t你是来打听回鹘美人之事？我可以告诉你：回鹘第一美人所穿衣服不会出现#G粉色#W。",
									text2="\t今早四位回鹘美人我见到了：回鹘第一美人所穿衣有#G红色#W和#G黄色#W。",
									text3="\t回鹘第一美人？我可以很肯定的说：回鹘第一美人所穿衣有#G紫色#W和#G绿色#W。",
									text4="\t我敢断定：回鹘第一美人的衣服上有#G蓝色#W。",
								  answer="\t你现在知道谁是回鹘第一美人了吗？\n\t是#G药罗葛丽#W？#G古力裴娜#W？#G黠多丽罗#W？还是#G顿英贺宁#W？\n\t#Y(您可以在任务攻略中查看知情人说过的话，以便分析。)",
									answer1="是药罗葛丽",
									answer2="是古力裴娜",
									answer3="是黠多丽罗",
									answer4="是顿英贺宁",
									
								  gonglue1="#G衣服上没有粉色#W",
									gonglue2="#G衣服上有红色和黄色#W",
									gonglue3="#G衣服上有紫色和绿色#W",
									gonglue4="#G衣服上有蓝色#W",
									
									result = 2  -- 答案

								},
								{	title="【个人】赵王府选美",  --任务名称
									info="\t赵王府之中的四位先生见多识广，前去请教一番便能知晓谁是最出色的回鹘美人。", --描述
									task1="询问@npc_"..x300581_g_NpcList[1].."",
								  task2="询问@npc_"..x300581_g_NpcList[2].."",
									task3="询问@npc_"..x300581_g_NpcList[3].."",
									task4="询问@npc_"..x300581_g_NpcList[4].."",
									text1="\t你是来打听回鹘美人之事？我可以告诉你：回鹘第一美人所穿衣服会有#G紫色#W。",
									text2="\t今早四位回鹘美人我见到了：回鹘第一美人所穿衣服有#G红色#W和#G黄色#W。",
									text3="\t回鹘第一美人？我可以很肯定的说：回鹘第一美人今日所穿衣服有#G蓝色#W。",
									text4="\t我敢断定：衣服上有#G白色#W的人，必不是回鹘第一美人。",
									 answer="\t你现在知道谁是回鹘第一美人了吗？\n\t是#G药罗葛丽#W？#G古力裴娜#W？#G黠多丽罗#W？还是#G顿英贺宁#W？\n\t#Y(您可以在任务攻略中查看知情人说过的话，以便分析。)",
									answer1="是药罗葛丽",
									answer2="是古力裴娜",
									answer3="是黠多丽罗",
									answer4="是顿英贺宁",
									
									gonglue1="#G衣服上有紫色#W",
									gonglue2="#G衣服上有红色和黄色#W",
									gonglue3="#G衣服上有蓝色#W",
									gonglue4="#G衣服上没有白色#W",
									
									result = 2  -- 答案

								},
								{	title="【个人】赵王府选美",  --任务名称
									info="\t赵王府之中的四位先生见多识广，前去请教一番便能知晓谁是最出色的回鹘美人。", --描述
									task1="询问@npc_"..x300581_g_NpcList[1].."",
								  task2="询问@npc_"..x300581_g_NpcList[2].."",
									task3="询问@npc_"..x300581_g_NpcList[3].."",
									task4="询问@npc_"..x300581_g_NpcList[4].."",
									text1="\t你是来打听回鹘美人之事？我可以告诉你：回鹘第一美人所穿衣服会有#G紫色#W。",
									text2="\t今早四位回鹘美人我见到了：回鹘第一美人所穿衣服有#G红色#W和#G黄色#W。",
									text3="\t回鹘第一美人？我可以很肯定的说：回鹘第一美人今日所穿衣服有#G白色#W。",
									text4="\t我敢断定：衣服上有#G绿色#W的人，必不是回鹘第一美人。",
									 answer="\t你现在知道谁是回鹘第一美人了吗？\n\t是#G药罗葛丽#W？#G古力裴娜#W？#G黠多丽罗#W？还是#G顿英贺宁#W？\n\t#Y(您可以在任务攻略中查看知情人说过的话，以便分析。)",
									answer1="是药罗葛丽",
									answer2="是古力裴娜",
									answer3="是黠多丽罗",
									answer4="是顿英贺宁",
									
									gonglue1="#G衣服上有紫色#W",
									gonglue2="#G衣服上有红色和黄色#W",
									gonglue3="#G衣服上有白色#W",
									gonglue4="#G衣服上没有绿色#W",
									
									result = 3  -- 答案

								},
								{	title="【个人】赵王府选美",  --任务名称
									info="\t赵王府之中的四位先生见多识广，前去请教一番便能知晓谁是最出色的回鹘美人。", --描述
									task1="询问@npc_"..x300581_g_NpcList[1].."",
								  task2="询问@npc_"..x300581_g_NpcList[2].."",
									task3="询问@npc_"..x300581_g_NpcList[3].."",
									task4="询问@npc_"..x300581_g_NpcList[4].."",
									text1="\t你是来打听回鹘美人之事？我可以告诉你：回鹘第一美人所穿衣服会有#G白色#W和#G黄色#W。",
									text2="\t今早四位回鹘美人我见到了：回鹘第一美人所穿衣服有#G红色#W和#G紫色#W。",
									text3="\t回鹘第一美人？我可以很肯定的说：回鹘第一美人今日所穿衣服有#G红色#W。",
									text4="\t我敢断定：回鹘第一美人衣服上没有#G绿色#W。",
									 answer="\t你现在知道谁是回鹘第一美人了吗？\n\t是#G药罗葛丽#W？#G古力裴娜#W？#G黠多丽罗#W？还是#G顿英贺宁#W？\n\t#Y(您可以在任务攻略中查看知情人说过的话，以便分析。)",
									answer1="是药罗葛丽",
									answer2="是古力裴娜",
									answer3="是黠多丽罗",
									answer4="是顿英贺宁",
									
								  gonglue1="#G衣服上有白色和黄色#W",
									gonglue2="#G衣服上有红色和紫色#W",
									gonglue3="#G衣服上有红色#W",
									gonglue4="#G衣服上没有绿色#W",
									
									result = 3  -- 答案

								},
								{	title="【个人】赵王府选美",  --任务名称
									info="\t赵王府之中的四位先生见多识广，前去请教一番便能知晓谁是最出色的回鹘美人。", --描述
									task1="询问@npc_"..x300581_g_NpcList[1].."",
								  task2="询问@npc_"..x300581_g_NpcList[2].."",
									task3="询问@npc_"..x300581_g_NpcList[3].."",
									task4="询问@npc_"..x300581_g_NpcList[4].."",
									text1="\t你是来打听回鹘美人之事？我可以告诉你：回鹘第一美人所穿衣服没有#G橙色#W。",
									text2="\t今早四位回鹘美人我见到了：回鹘第一美人所穿衣服有#G红色#W。",
									text3="\t回鹘第一美人？我可以很肯定的说：回鹘第一美人今日所穿衣服有#G蓝色#W和#G白色#W。",
									text4="\t我敢断定：回鹘第一美人的衣服上有#G紫色#W。",
								 answer="\t你现在知道谁是回鹘第一美人吗？\n\t是#G药罗葛丽#W？#G古力裴娜#W？#G黠多丽罗#W？还是#G顿英贺宁#W？\n\t#Y(您可以在任务攻略中查看知情人说过的话，以便分析。)",
									answer1="是药罗葛丽",
									answer2="是古力裴娜",
									answer3="是黠多丽罗",
									answer4="是顿英贺宁",
									
									gonglue1="#G衣服上没有橙色#W",
									gonglue2="#G衣服上有红色#W",
									gonglue3="#G衣服上有蓝色和白色#W",
									gonglue4="#G衣服上有紫色#W",
									
									result = 4  -- 答案

								},
						    {	title="【个人】赵王府选美",  --任务名称
								  info="\t赵王府之中的四位先生见多识广，前去请教一番便能知晓谁是最出色的回鹘美人。", --描述
							    task1="询问@npc_"..x300581_g_NpcList[1].."",
						      task2="询问@npc_"..x300581_g_NpcList[2].."",
								  task3="询问@npc_"..x300581_g_NpcList[3].."",
								  task4="询问@npc_"..x300581_g_NpcList[4].."",
							    text1="\t你是来打听回鹘美人之事？我可以告诉你：回鹘第一美人所穿衣服有#G紫色#W没有#G绿色#W。",
							    text2="\t今早四位回鹘美人我见到了：回鹘第一美人所穿衣服有#G红色#W和#G蓝色#W。",
								  text3="\t回鹘第一美人？我可以很肯定的说：回鹘第一美人今日所穿衣服有#G白色#W。",
								  text4="\t我敢断定：衣服上有#G黄色#W的人，必不是回鹘第一美人。",
								 answer="\t你现在知道谁是回鹘第一美人了吗？\n\t是#G药罗葛丽#W？#G古力裴娜#W？#G黠多丽罗#W？还是#G顿英贺宁#W？\n\t#Y(您可以在任务攻略中查看知情人说过的话，以便分析。)",
									answer1="是药罗葛丽",
									answer2="是古力裴娜",
									answer3="是黠多丽罗",
									answer4="是顿英贺宁",
								
								  gonglue1="#G衣服上有紫色没有绿色#W",
								  gonglue2="#G衣服上有红色和蓝色#W",
								  gonglue3="#G衣服上有白色#W",
								  gonglue4="#G衣服上没有黄色#W",
							
							  	result = 4  -- 答案
          
							  }
							   }	
				
-- 任务奖励物品列表
x300581_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}



function x300581_GetMissionId( sceneId, selfId )
	return x300581_g_MissionId
end

function x300581_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	local level = GetLevel( sceneId,selfId )
    if level < x300581_g_LevelLess then
       return
    end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300581_g_MissionName,8,1);
	else
		--local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		--AddQuestNumText(sceneId, myMissionId, x300581_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300581_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "此活动今天不开放，详情请到大都包打处听查询每日新鲜事")
		return
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId )>0 then
		if nExt==30 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x300581_g_MissionName)
				AddQuestText(sceneId,"\t连你也慕名而来了？可是究竟谁是回鹘第一美人呢？")
				AddQuestNumText(sceneId, myMissionId, "交给我吧",2,31);
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, targetId, x300581_g_ScriptId, myMissionId);
			return
		elseif nExt ==31 then
			x300581_GiveQuestion(sceneId, selfId, targetId, MissionId,1)
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
				x300581_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
			
			else
				if nExt==7 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
						AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].info)
						AddQuestNumText(sceneId, myMissionId, "我知道谁是回鹘第一美人！",2,20);
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300581_g_ScriptId, myMissionId);
				elseif nExt==20 then
					
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
						--AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].info)
						--AddQuestText(sceneId," ")
						AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].answer)
						
						AddQuestNumText(sceneId, myMissionId, x300581_g_QuestionTextList[nQuestionId].answer1,2,21);
						AddQuestNumText(sceneId, myMissionId, x300581_g_QuestionTextList[nQuestionId].answer2,2,22);
						AddQuestNumText(sceneId, myMissionId, x300581_g_QuestionTextList[nQuestionId].answer3,2,23);
						AddQuestNumText(sceneId, myMissionId, x300581_g_QuestionTextList[nQuestionId].answer4,2,24);
						
						
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, targetId, x300581_g_ScriptId, myMissionId);
				elseif nExt>=21 then
					local nAnswer = nExt-20
					local nResult = x300581_g_QuestionTextList[nQuestionId].result;

					if nResult == nAnswer then
						x300581_ShowTips(sceneId, selfId, "你果然聪慧，所料不错！")
						SetQuestByIndex( sceneId, selfId, misIndex, 5, 2 )
						x300581_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
						
					
					else
						x300581_ShowTips(sceneId, selfId, "你果然猜错了，再去找先生们问问吧！")
						x300581_GiveQuestion(sceneId, selfId, targetId, MissionId,2)
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

		x300581_DispatchNpcTalkInfo( sceneId, selfId, targetId,myMissionId,iIndex )

	
	else
		
		if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
			x300581_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
		else
			if nExt==7 then -- 任务完成
				--x300581_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
				
				
			else
				
				x300581_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
			end
		end
	end
end


function x300581_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )

	return 1;

end

function x300581_CheckRequest(sceneId, selfId)
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300581_g_LevelLess then
		x300581_ShowTips(sceneId, selfId, "你等级不足")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300581_ShowTips(sceneId, selfId, "你已经有这个任务，请先完成这个任务")
		return 0;
	end

    local day = GetDayOfYear()
    if GetQuestData(sceneId, selfId, MD_SNZX_DATE[1], MD_SNZX_DATE[2],MD_SNZX_DATE[3] ) == day then
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

function x300581_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end
	
	if x300581_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300581_ShowTips(sceneId, selfId, "任务已满，无法接受任务")
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

	local ret = AddQuest( sceneId, selfId, myMissionId, x300581_g_ScriptId, 0, 0, 0,1)-- 给玩家添加任务		
		
	if ret > 0 then
		local str = "您接受了任务："..x300581_g_MissionName;
		x300581_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)
		
		local myMissionId = x300581_GetMissionId( sceneId, selfId )
		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 )
		GamePlayScriptLog(sceneId, selfId, 1541)
		return 1
	else
		
		x300581_ShowTips(sceneId, selfId, "接受任务错误")
	
	end


end

function x300581_GiveQuestion(sceneId, selfId, targetId, MissionId, nExt)
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )

	local nQuestionId = random(1,x300581_g_QuestionCount)
		
	

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 6, nQuestionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 5, 1 )  --还没有答题
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 2, 0 )
	SetQuestByIndex( sceneId, selfId, misIndex, 3, 0 )

	x300581_ShowQuestion( sceneId, selfId, targetId,MissionId,nQuestionId, nExt )

	x300581_QuestLogRefresh( sceneId, selfId, myMissionId );
end

function x300581_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300581_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "您放弃了任务："..x300581_g_MissionName;
	    x300581_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

        local today = GetDayOfYear()
		SetQuestData(sceneId, selfId, MD_SNZX_DATE[1], MD_SNZX_DATE[2], MD_SNZX_DATE[3], today)
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
		x300581_ShowTips(sceneId, selfId, "放弃任务失败")
	end

	
end



function x300581_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end
	


	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	
	if x300581_CheckSubmit(sceneId, selfId )>0 then
		local today = GetDayOfYear()
        local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
        if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
            Msg2Player( sceneId, selfId, "今天的日常任务已经不能再交了，请明天再来", 8, 3)
            return 0
        end

		if x300581_GiveReward(sceneId,selfId,selectId)>0 then
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then
            CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300581_g_MissionId)

			local str = "您完成了任务："..x300581_g_MissionName;
			x300581_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

            SetQuestData(sceneId, selfId, MD_SNZX_DATE[1], MD_SNZX_DATE[2], MD_SNZX_DATE[3], GetDayOfYear() )

			GamePlayScriptLog(sceneId, selfId, 1542)
			
		else
			x300581_ShowTips(sceneId, selfId, "交任务失败")
		end
		end
		
	end
end

function x300581_GiveReward( sceneId, selfId, selectRadioId)
	
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

    -- 检查玩家选择的奖励是不是可判定非绑定的
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300581_g_RewardTable do
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
        for i, item in x300581_g_RewardTable do
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



function x300581_CheckSubmit(sceneId, selfId )
	
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end

	local myMissionId = x300581_GetMissionId( sceneId, selfId )
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
function x300581_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	
	AddQuestText(sceneId,"#Y"..x300581_g_MissionName)
	AddQuestText(sceneId,"\t前些日子，回鹘王子来我们王府做客，献上了四位绝色的回鹘美人。不过这四位美人，却给我这个管家带来不少麻烦……")
	AddQuestText( sceneId,"#Y任务目标：")
			
	AddQuestText( sceneId,x300581_g_MissionTarget)
			
	AddQuestText(sceneId," ")

	local level = GetLevel(sceneId, selfId)
    for i, item in x300581_g_RewardTable do
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

	-- if x300581_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300581_g_BonusMoney5)
	-- end
	-- for i, item in x300581_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300581_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--向客户端发送任务未完成
---------------------------------------------------------------------------------------------------
function x300581_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\t你还没找出谁是回鹘第一美人？")
		AddQuestText(sceneId,"\n#G小提示#W：")
		AddQuestText(sceneId,"\t可以询问一下赵王客卿，兴许能有线索。")

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300581_g_ScriptId, MissionId,0);
	


end







---------------------------------------------------------------------------------------------------
--向客户端发送任务完成信息
---------------------------------------------------------------------------------------------------
function x300581_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )

	
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- 如果有这个任务直接退出
		return 0
	end

	
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
		AddQuestText(sceneId,"\n\t年轻人果然不凡啊，这点心意还请你收下。")
	
	
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300581_g_RewardTable do
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

	-- if x300581_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300581_g_BonusMoney5)
	-- end
	
	-- for i, item in x300581_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300581_g_ScriptId, myMissionId);

end


---------------------------------------------------------------------------------------------------
--向客户端发送题目
---------------------------------------------------------------------------------------------------
function x300581_ShowQuestion( sceneId, selfId, NPCId,MissionId,nQuestionId, nExt )


	if nExt==1 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
	
			AddQuestText( sceneId,x300581_g_QuestionTextList[nQuestionId].info)
		
			
		EndQuestEvent()
	elseif nExt==2 then
		BeginQuestEvent(sceneId)
			
			AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
			
			AddQuestText( sceneId,"\t不对不对，和本王的判断完全不一样。\n\t你再去仔细问问吧。\n\t#G（您回答错了，看来只好回去重新询问。）")
		
			
		EndQuestEvent()
	
	else
		return	
	end
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300581_g_ScriptId, MissionId,1);
	


end


function x300581_DispatchNpcTalkInfo( sceneId, selfId, NPCId,MissionId,iIndex )
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
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
	
	x300581_QuestLogRefresh( sceneId, selfId, myMissionId );

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x300581_g_QuestionTextList[nQuestionId].title)
		
		if iIndex==1 then
			AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].text1)
		elseif iIndex==2 then
			AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].text2)
		elseif iIndex==3 then
			AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].text3)
		elseif iIndex==4 then
			AddQuestText(sceneId,x300581_g_QuestionTextList[nQuestionId].text4)
		end
	
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300581_g_ScriptId, myMissionId,0);

	

end





---------------------------------------------------------------------------------------------------
--任务日志刷新
---------------------------------------------------------------------------------------------------
function x300581_QuestLogRefresh( sceneId, selfId, MissionId)
	
	
		
	BeginQuestEvent(sceneId)	
			
		
	AddQuestLogCustomText( sceneId,
							"",						-- 标题
							x300581_GetMissionName(sceneId,selfId),        -- 任务名字
							x300581_GetMissionTask(sceneId,selfId),		--任务目标
							"@npc_"..x300581_GetReplyNpcId(sceneId,selfId),			--任务NPC
							x300581_GetMissionMethod(sceneId,selfId),               --任务攻略
							x300581_GetMissionText(sceneId,selfId),	--任务描述
							x300581_GetMissionHelp(sceneId,selfId)					--任务小提示
							)
	
	local level = GetLevel(sceneId, selfId)
    for i, item in x300581_g_RewardTable do
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

	-- if x300581_g_BonusMoney5 > 0 then
		-- AddQuestMoneyBonus5( sceneId, x300581_g_BonusMoney5)
	-- end
	-- for i, item in x300581_g_BonusItem do
		-- AddQuestItemBonus(sceneId, item.item, item.n)
	-- end
	
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300581_GetMissionName(sceneId,selfId)
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		return ""..x300581_g_MissionName;
	end

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )

	local str = x300581_g_QuestionTextList[nQuestionId].title

	return str
end

function x300581_GetMissionTask(sceneId,selfId)
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )

	if nStep==0 then
		
		return "  #Y任务回复:#G@npc_"..x300581_g_ReplyNpcId;
	end
	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	local strTable = "  ";
	local str1 = strTable..(x300581_g_QuestionTextList[nQuestionId].task1)..format("(%d/1)",value1)
	local str2 = "\n"..strTable..(x300581_g_QuestionTextList[nQuestionId].task2)..format("(%d/1)",value2)
	local str3 = "\n"..strTable..(x300581_g_QuestionTextList[nQuestionId].task3)..format("(%d/1)",value3)
	local str4 = "\n"..strTable..(x300581_g_QuestionTextList[nQuestionId].task4)..format("(%d/1)",value4)

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

function x300581_GetReplyNpcId(sceneId,selfId)
	return x300581_g_ReplyNpcId;
end

function x300581_GetMissionMethod(sceneId,selfId)
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	local nMissionStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
	local value1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	local value2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local value3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local value4 = GetQuestParam( sceneId, selfId, misIndex, 3 )

	local str=""

	if nMissionStep>0 then
		
		str = x300581_g_MissionTarget1
		
		if value1>=1 then
			str=str.."\n  张申算说："..x300581_g_QuestionTextList[nQuestionId].gonglue1;
		end
		if value2>=1 then
			str=str.."\n  阎必忠说："..x300581_g_QuestionTextList[nQuestionId].gonglue2;
		end
		if value3>=1 then
			str=str.."\n  霍身先说："..x300581_g_QuestionTextList[nQuestionId].gonglue3;
		end
		if value4>=1 then
			str=str.."\n  只天明说："..x300581_g_QuestionTextList[nQuestionId].gonglue4;
		end
		
		
	else
		str = x300581_g_MissionTarget
	end

	return str
end

function x300581_GetMissionText(sceneId,selfId)
	return "\t这四位美人，真是各有千秋啊，不日就是皇上大寿，我准备选其中最好的一名献给陛下，可是我这府内众说纷纭，始终无法在这四人中选出最出色的女子，甚是愁人啊。\n\t莫不如，你去问问我府内的四位先生们，看看他们是何看法？"
end

function x300581_GetMissionHelp(sceneId,selfId)
	return "\t如何寻找回鹘第一美人。先要记住赵王客卿们#R话中的提示#G，进行总结，然后依照提示#R观察回鹘美人的衣着#G；那么你就会找到答案。"
end



function x300581_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300581_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300581_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if GetGameOpenById(x300581_g_GameId)<=0 and IsHaveQuestNM( sceneId, selfId, x300581_g_MissionId) == 0 then
		x300581_ShowTips(sceneId, selfId, "此活动今天不开放")
		return 0;
	end
	local myMissionId = x300581_GetMissionId( sceneId, selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )

	

	local nQuestionId = GetQuestParam( sceneId, selfId, misIndex, 6 )
	
	if npcGuid == x300581_g_ReplyNpcId then
		local nStep = GetQuestParam( sceneId, selfId, misIndex, 5 )
		
		if nStep==0 then
			AddQuestNumText(sceneId, x300581_g_MissionId, x300581_g_MissionName,2,30);
		elseif nStep>0 then
			local state = GetQuestStateNM(sceneId, selfId, npcGuid, myMissionId);

		
			AddQuestNumText(sceneId, myMissionId, x300581_g_MissionName,state,state);
		end
	
	else
		local bFind =0;
		local iIndex=0
		for i,item in x300581_g_NpcList do
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


			AddQuestNumText(sceneId, x300581_g_MissionId, x300581_g_QuestionTextList[nQuestionId].title,2,iIndex+10);
		end
	end
	

	
end

function x300581_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end



--// system end




