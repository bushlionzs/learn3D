
x300902_g_ScriptId = 300902
x300902_g_MissionName = "【国家】敌国夺旗"

x300902_g_DayCountLimited = 1

x300902_g_SceneIdList = {51,151,251,351}
function x300902_ProcEnumEvent( sceneId, selfId, targetId, index )
	local country = GetCurCountry( sceneId, selfId )
	local Level = GetLevel(sceneId, selfId)
	if Level >= 40 then
		if country<=3 and country>=0 then
			if sceneId == x300902_g_SceneIdList[country+1] then
		
				AddQuestNumText(sceneId,x300902_g_ScriptId, x300902_g_MissionName, 8)
			end
		end
	end
end

function x300902_ProcEventEntry( sceneId , selfId , targetId , state , index )
	local country = GetCurCountry( sceneId, selfId )

		BeginQuestEvent(sceneId)
			local Readme ="#Y【国家】敌国夺旗"
			local mission1 = "楼兰夺旗"
			local mission2 = "天山夺旗"
			local mission3 = "昆仑夺旗"
			local mission4 = "敦煌夺旗"

			local script = 300890

			local missionId1 = 7694
			local missionId2 = 7695
			local missionId3 = 7696
			local missionId4 = 7697

			local state1 = GetQuestStateNM(sceneId, selfId, targetId, missionId1);
			local state2 = GetQuestStateNM(sceneId, selfId, targetId, missionId2);
			local state3 = GetQuestStateNM(sceneId, selfId, targetId, missionId3);
			local state4 = GetQuestStateNM(sceneId, selfId, targetId, missionId4);

			local nDayCount1 = x300902_GetDayCount(sceneId, selfId, DQ_DUOQI_LOULAN_DATE,DQ_DUOQI_LOULAN_DAYCOUNT)
			local nDayCount2 = x300902_GetDayCount(sceneId, selfId, DQ_DUOQI_LAIYIN_DATE,DQ_DUOQI_LAIYIN_DAYCOUNT)
			local nDayCount3 = x300902_GetDayCount(sceneId, selfId, DQ_DUOQI_KUNLUN_DATE,DQ_DUOQI_KUNLUN_DAYCOUNT)
			local nDayCount4 = x300902_GetDayCount(sceneId, selfId, DQ_DUOQI_DUNHUANG_DATE,DQ_DUOQI_DUNHUANG_DAYCOUNT)

		


			if country == 0 then
				if nDayCount2>=x300902_g_DayCountLimited and nDayCount3>=x300902_g_DayCountLimited and nDayCount4>=x300902_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来",8,2);
					return 0;

				end
			elseif country == 1 then
				if nDayCount1>=x300902_g_DayCountLimited and nDayCount3>=x300902_g_DayCountLimited and nDayCount4>=x300902_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来",8,2);
					return 0;

				end
			elseif country == 2 then
				if nDayCount1>=x300902_g_DayCountLimited and nDayCount2>=x300902_g_DayCountLimited and nDayCount4>=x300902_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来",8,2);
					return 0;

				end
			elseif country == 3 then
				if nDayCount1>=x300902_g_DayCountLimited and nDayCount2>=x300902_g_DayCountLimited and nDayCount3>=x300902_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来",8,2);
					return 0;

				end
			end

			AddQuestText(sceneId,Readme)
			AddQuestText(sceneId,"")
			AddQuestText(sceneId,"\t兵者，攻心为上。若想要打击敌人的士气，最好的办法莫过于夺取他们的军旗！")
			if country == 0 then

				if nDayCount2<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount3<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
				if nDayCount4<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
				
			elseif country == 1 then
				if nDayCount1<x300902_g_DayCountLimited then	
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount3<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
				if nDayCount4<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
			elseif country == 2 then
				if nDayCount1<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount2<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount4<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
			elseif country == 3 then
				if nDayCount1<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount2<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount3<x300902_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
			end
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
end

---------------------------------------------------------------------------------------------------
--最后一次做这个任务是哪天
---------------------------------------------------------------------------------------------------
function x300902_GetLastDay(sceneId, selfId, nMDIndex, nOffset, nSize)
	local lastday = GetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize)
	return lastday
end

---------------------------------------------------------------------------------------------------
--最后一天做这个任务做了几次
---------------------------------------------------------------------------------------------------
function x300902_GetLastDayCount(sceneId, selfId, nMDIndex, nOffset, nSize)
	local daycount =  GetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize)
	return daycount
end

---------------------------------------------------------------------------------------------------
--今天这个任务做了几次
---------------------------------------------------------------------------------------------------
function x300902_GetDayCount(sceneId, selfId, nMDDayIndex, nMDCountIndex)
	local today = GetDayOfYear()
	local lastday = x300902_GetLastDay(sceneId, selfId, nMDDayIndex[1], nMDDayIndex[2], nMDDayIndex[3])

	--不是同一天
	if today ~= lastday then
		return 0
	end

	local daycount = x300902_GetLastDayCount(sceneId, selfId, nMDCountIndex[1], nMDCountIndex[2], nMDCountIndex[3])
	return daycount
end
