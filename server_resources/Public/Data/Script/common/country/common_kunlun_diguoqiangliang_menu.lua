x300897_g_ScriptId = 300897
x300897_g_MissionName = "【国家】敌国情报"

x300897_g_DayCountLimited	=	1


x300897_g_SceneIdList = {51,151,251,351}
function x300897_ProcEnumEvent( sceneId, selfId, targetId, index )
	local country = GetCurCountry( sceneId, selfId )
	local Level = GetLevel(sceneId, selfId)
	if Level >= 40 then
		if country<=3 and country>=0 then
			if sceneId == x300897_g_SceneIdList[country+1] then
		
				AddQuestNumText(sceneId,x300897_g_ScriptId, x300897_g_MissionName, 8)
			end
		end
	end
end

function x300897_ProcEventEntry( sceneId , selfId , targetId , state , index )
--PrintStr("qiangliang")
	local country = GetCurCountry( sceneId, selfId )
		BeginQuestEvent(sceneId)
			local Readme ="#Y【国家】敌国情报"
			local mission1 = "楼兰情报"
			local mission2 = "天山情报"
			local mission3 = "昆仑情报"
			local mission4 = "敦煌情报"

			local script = 300885

			local missionId1 = 7664
			local missionId2 = 7667
			local missionId3 = 7670
			local missionId4 = 7673

			local state1 = GetQuestStateNM(sceneId, selfId, targetId, missionId1);
			local state2 = GetQuestStateNM(sceneId, selfId, targetId, missionId2);
			local state3 = GetQuestStateNM(sceneId, selfId, targetId, missionId3);
			local state4 = GetQuestStateNM(sceneId, selfId, targetId, missionId4);

			local nDayCount1 = x300897_GetDayCount(sceneId, selfId, DQ_MIBAO_LOULAN_DATE,DQ_MIBAO_LOULAN_DAYCOUNT)
			local nDayCount2 = x300897_GetDayCount(sceneId, selfId, DQ_MIBAO_LAIYIN_DATE,DQ_MIBAO_LAIYIN_DAYCOUNT)
			local nDayCount3 = x300897_GetDayCount(sceneId, selfId, DQ_MIBAO_KUNLUN_DATE,DQ_MIBAO_KUNLUN_DAYCOUNT)
			local nDayCount4 = x300897_GetDayCount(sceneId, selfId, DQ_MIBAO_DUNHUANG_DATE,DQ_MIBAO_DUNHUANG_DAYCOUNT)


			if country == 0 then
				if nDayCount2>=x300897_g_DayCountLimited and nDayCount3>=x300897_g_DayCountLimited and nDayCount4>=x300897_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			elseif country == 1 then
				if nDayCount1>=x300897_g_DayCountLimited and nDayCount3>=x300897_g_DayCountLimited and nDayCount4>=x300897_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			elseif country == 2 then
				if nDayCount1>=x300897_g_DayCountLimited and nDayCount2>=x300897_g_DayCountLimited and nDayCount4>=x300897_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			elseif country == 3 then
				if nDayCount1>=x300897_g_DayCountLimited and nDayCount2>=x300897_g_DayCountLimited and nDayCount3>=x300897_g_DayCountLimited then
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
			AddQuestText(sceneId,"\t知己知彼，百战不殆。我们的密探常常会送回一些重要的情报。")
			if country == 0 then
				if nDayCount2<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount3<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
				if nDayCount4<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end

			elseif country == 1 then
				if nDayCount1<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount3<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
				if nDayCount4<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
			elseif country == 2 then
				if nDayCount1<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount2<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount4<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
			elseif country == 3 then
				if nDayCount1<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount2<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount3<x300897_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
			end
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
end


---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300897_GetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, nDayIndex[1], nDayIndex[2],nDayIndex[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2],nDayCountIndex[3] );
	return daycount;

	

end
