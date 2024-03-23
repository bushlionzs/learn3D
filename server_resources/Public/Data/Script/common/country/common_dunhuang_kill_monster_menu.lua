
x300891_g_ScriptId = 300891
x300891_g_MissionName = "【国家】敌国刺杀"

x300891_g_DayCountLimited = 1


x300891_g_SceneIdList = {51,151,251,351}

function x300891_ProcEnumEvent( sceneId, selfId, targetId, index )
	
	local country = GetCurCountry( sceneId, selfId )
	local Level = GetLevel(sceneId, selfId)
	if Level >= 40 then
		if country<=3 and country>=0 then
			if sceneId == x300891_g_SceneIdList[country+1] then
		
				AddQuestNumText(sceneId,x300891_g_ScriptId, x300891_g_MissionName, 8)
			end
		end
	end	
end

function x300891_ProcEventEntry( sceneId , selfId , targetId , state , index )
	local country = GetCurCountry( sceneId, selfId )

		BeginQuestEvent(sceneId)
			local Readme ="#Y【国家】敌国刺杀"
			local mission1 = "楼兰刺杀"
			local mission2 = "天山刺杀"
			local mission3 = "昆仑刺杀"
			local mission4 = "敦煌刺杀"

			local script = 300879

			local missionId1 = 7650
			local missionId2 = 7653
			local missionId3 = 7656
			local missionId4 = 7659
			local state1 = GetQuestStateNM(sceneId, selfId, targetId, missionId1);
			local state2 = GetQuestStateNM(sceneId, selfId, targetId, missionId2);
			local state3 = GetQuestStateNM(sceneId, selfId, targetId, missionId3);
			local state4 = GetQuestStateNM(sceneId, selfId, targetId, missionId4);
			

			local nDayCount1 = x300891_GetDayCount(sceneId, selfId, DQ_SHAGUAI_LOULAN_DATE,DQ_SHAGUAI_LOULAN_DAYCOUNT)
			local nDayCount2 = x300891_GetDayCount(sceneId, selfId, DQ_SHAGUAI_LAIYIN_DATE,DQ_SHAGUAI_LAIYIN_DAYCOUNT)
			local nDayCount3 = x300891_GetDayCount(sceneId, selfId, DQ_SHAGUAI_KUNLUN_DATE,DQ_SHAGUAI_KUNLUN_DAYCOUNT)
			local nDayCount4 = x300891_GetDayCount(sceneId, selfId, DQ_SHAGUAI_DUNHUANG_DATE,DQ_SHAGUAI_DUNHUANG_DAYCOUNT)
			
			if country == 0 then
				if nDayCount2>=x300891_g_DayCountLimited and nDayCount3>=x300891_g_DayCountLimited and nDayCount4>=x300891_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			elseif country == 1 then
				if nDayCount1>=x300891_g_DayCountLimited and nDayCount3>=x300891_g_DayCountLimited and nDayCount4>=x300891_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			elseif country == 2 then
				if nDayCount1>=x300891_g_DayCountLimited and nDayCount2>=x300891_g_DayCountLimited and nDayCount4>=x300891_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			elseif country == 3 then
				if nDayCount1>=x300891_g_DayCountLimited and nDayCount2>=x300891_g_DayCountLimited and nDayCount3>=x300891_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			end
	

			AddQuestText(sceneId,Readme)
			AddQuestText(sceneId,"")
			AddQuestText(sceneId,"\t近日，敌国的边塞主将突然增派了大量人手巡查他们整个边塞地区，我国暗探损失惨重。\n\t绝不能让这种情况继续下去！你立刻潜入敌国，刺杀他们的主将，如果得手，定能让他们整个边塞军务陷入混乱！")
			if country == 0 then
				if nDayCount2<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount3<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
				if nDayCount4<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
			elseif country == 1 then
				if nDayCount1<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount3<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
				if nDayCount4<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
			elseif country == 2 then
				if nDayCount1<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount2<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount4<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
			elseif country == 3 then
				if nDayCount1<x300891_g_DayCountLimited then	
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount2<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount3<x300891_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
			end

		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
end



---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300891_GetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, nDayIndex[1], nDayIndex[2],nDayIndex[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2],nDayCountIndex[3] );
	return daycount;

	

end
