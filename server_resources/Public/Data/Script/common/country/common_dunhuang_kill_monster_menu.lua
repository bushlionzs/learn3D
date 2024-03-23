
x300891_g_ScriptId = 300891
x300891_g_MissionName = "�����ҡ��й���ɱ"

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
			local Readme ="#Y�����ҡ��й���ɱ"
			local mission1 = "¥����ɱ"
			local mission2 = "��ɽ��ɱ"
			local mission3 = "���ش�ɱ"
			local mission4 = "�ػʹ�ɱ"

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
						AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ���ȡ���������ҵ�����������������");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ���������ҵ�����������������",8,2);
					return 0;

				end
			elseif country == 1 then
				if nDayCount1>=x300891_g_DayCountLimited and nDayCount3>=x300891_g_DayCountLimited and nDayCount4>=x300891_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ���ȡ���������ҵ�����������������");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ���������ҵ�����������������",8,2);
					return 0;

				end
			elseif country == 2 then
				if nDayCount1>=x300891_g_DayCountLimited and nDayCount2>=x300891_g_DayCountLimited and nDayCount4>=x300891_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ���ȡ���������ҵ�����������������");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ���������ҵ�����������������",8,2);
					return 0;

				end
			elseif country == 3 then
				if nDayCount1>=x300891_g_DayCountLimited and nDayCount2>=x300891_g_DayCountLimited and nDayCount3>=x300891_g_DayCountLimited then
					BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ���ȡ���������ҵ�����������������");
					EndQuestEvent();
					DispatchQuestTips(sceneId, selfId);
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ���������ҵ�����������������",8,2);
					return 0;

				end
			end
	

			AddQuestText(sceneId,Readme)
			AddQuestText(sceneId,"")
			AddQuestText(sceneId,"\t���գ��й��ı�������ͻȻ�����˴�������Ѳ���������������������ҹ���̽��ʧ���ء�\n\t���������������������ȥ��������Ǳ��й�����ɱ���ǵ�������������֣�����������������������������ң�")
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
--ȡ�õ�ǰ����
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
