
x300896_g_ScriptId = 300896
x300896_g_MissionName = "【国家】敌国除奸"

x300896_g_DayCountLimited = 1

x300896_g_SceneIdList = {51,151,251,351}
function x300896_ProcEnumEvent( sceneId, selfId, targetId, index )
	local country = GetCurCountry( sceneId, selfId )
	local Level = GetLevel(sceneId, selfId)
	if Level >= 40 then
		if country<=3 and country>=0 then
			if sceneId == x300896_g_SceneIdList[country+1] then
		
				AddQuestNumText(sceneId,x300896_g_ScriptId, x300896_g_MissionName, 8)
			end
		end
	end
end

function x300896_ProcEventEntry( sceneId , selfId , targetId , state , index )
	local country = GetCurCountry( sceneId, selfId )

		BeginQuestEvent(sceneId)
			local Readme ="#Y【国家】敌国除奸"
			local mission1 = "楼兰除奸"
			local mission2 = "天山除奸"
			local mission3 = "昆仑除奸"
			local mission4 = "敦煌除奸"

			local script = 300884

			local missionId1 = 7663
			local missionId2 = 7666
			local missionId3 = 7669
			local missionId4 = 7672

			local state1 = GetQuestStateNM(sceneId, selfId, targetId, missionId1);
			local state2 = GetQuestStateNM(sceneId, selfId, targetId, missionId2);
			local state3 = GetQuestStateNM(sceneId, selfId, targetId, missionId3);
			local state4 = GetQuestStateNM(sceneId, selfId, targetId, missionId4);

			local nDayCount1 = x300896_GetDayCount(sceneId, selfId, DQ_CITAN_LOULAN_DATE,DQ_CITAN_LOULAN_DAYCOUNT)
			local nDayCount2 = x300896_GetDayCount(sceneId, selfId, DQ_CITAN_LAIYIN_DATE,DQ_CITAN_LAIYIN_DAYCOUNT)
			local nDayCount3 = x300896_GetDayCount(sceneId, selfId, DQ_CITAN_KUNLUN_DATE,DQ_CITAN_KUNLUN_DAYCOUNT)
			local nDayCount4 = x300896_GetDayCount(sceneId, selfId, DQ_CITAN_DUNHUANG_DATE,DQ_CITAN_DUNHUANG_DAYCOUNT)

		


			if country == 0 then
				if nDayCount2>=x300896_g_DayCountLimited and nDayCount3>=x300896_g_DayCountLimited and nDayCount4>=x300896_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			elseif country == 1 then
				if nDayCount1>=x300896_g_DayCountLimited and nDayCount3>=x300896_g_DayCountLimited and nDayCount4>=x300896_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			elseif country == 2 then
				if nDayCount1>=x300896_g_DayCountLimited and nDayCount2>=x300896_g_DayCountLimited and nDayCount4>=x300896_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "很抱歉，您已经接取了三个国家的任务，请明日再来！");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"很抱歉，您已经接取了三个国家的任务，请明日再来！",8,2);
					return 0;

				end
			elseif country == 3 then
				if nDayCount1>=x300896_g_DayCountLimited and nDayCount2>=x300896_g_DayCountLimited and nDayCount3>=x300896_g_DayCountLimited then
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
			AddQuestText(sceneId,"\t想不到我们派往敌国的密探统领张五常，被敌人俘虏后竟然背叛了我们！\n\t他的手中掌握着我们大量密探的信息，看来只有干掉此人，才能防止我们苦心经营多年的密探网被彻底摧毁。")
			if country == 0 then

				if nDayCount2<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount3<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
				if nDayCount4<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
				
			elseif country == 1 then
				if nDayCount1<x300896_g_DayCountLimited then	
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount3<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
				if nDayCount4<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
			elseif country == 2 then
				if nDayCount1<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount2<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount4<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission4, state4, missionId4)
				end
			elseif country == 3 then
				if nDayCount1<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission1, state1, missionId1)
				end
				if nDayCount2<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission2, state2, missionId2)
				end
				if nDayCount3<x300896_g_DayCountLimited then
					AddQuestNumText(sceneId, script, mission3, state3, missionId3)
				end
			end
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
end

---------------------------------------------------------------------------------------------------
--取得当前次数
---------------------------------------------------------------------------------------------------
function x300896_GetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, nDayIndex[1], nDayIndex[2],nDayIndex[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2],nDayCountIndex[3] );
	return daycount;

	

end
