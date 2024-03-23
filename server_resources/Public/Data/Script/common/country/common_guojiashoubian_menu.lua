----------------------------------------------
--Author: ZP Wang
--Date: 2008-12-19
--version: 2.1
----------------------------------------------

x300730_g_DayCountLimited = 1

x300730_g_ScriptId = 300730
x300730_g_MissionName = "�����ҡ������ر�"


x300730_g_SceneIdList = {51,151,251,351}
function x300730_ProcEnumEvent( sceneId, selfId, targetId, index )
	local country = GetCurCountry( sceneId, selfId )
	local Level = GetLevel(sceneId, selfId)
	if Level >= 40 then
		if country<=3 and country>=0 then
			if sceneId == x300730_g_SceneIdList[country+1] then
		
				AddQuestNumText(sceneId,x300730_g_ScriptId, x300730_g_MissionName, 8)
			end
		end
	end
end

function x300730_ProcEventEntry( sceneId , selfId , targetId , state , index )
	--PrintStr("On")
	local country = GetCurCountry( sceneId, selfId )
	
		BeginQuestEvent(sceneId)

			local Readme ="#Y�����ҡ������ر�#r"
			local Readme2 = "#Y�����ҡ������ر�#r";
			local Readme3 = "�㻹û����ɹ����ر�����"

			local strHaveMissionText = "  ���Ѿ������˹����ر����񣬸Ͽ�ȥ��ɰɣ�#r";
			local mission1 = "�����ҡ������ر�"
			local mission2 = "�����ҡ������ر�"
			local mission3 = "�����ҡ������ر�"
			local mission4 = "�����ҡ������ر�"

			local mission2submit1 = "�����ҡ������ر�"
			local mission2submit2 = "�����ҡ������ر�"
			local mission2submit3 = "�����ҡ������ر�"
			local mission2submit4 = "�����ҡ������ر�"

			local script = 300738

			--// ������
			local missionId1 = 7564  -- ��������1
			local missionId2 = 7570	 	
			local missionId3 = 7576
			local missionId4 = 7585

			--// ������
			local shoubian_missionId1 = 7563  -- �ر�����1
			local shoubian_missionId2 = 7569	 	
			local shoubian_missionId3 = 7575
			local shoubian_missionId4 = 7584

			--// ����������2
			local mission2submitId1 = 7565  -- ��������2
			local mission2submitId2 = 7571	 	
			local mission2submitId3 = 7577
			local mission2submitId4 = 7586
			

			
			--local state2 = GetQuestStateNM(sceneId, selfId, targetId, missionId2)
			--local state3 = GetQuestStateNM(sceneId, selfId, targetId, missionId3)
			--local state4 = GetQuestStateNM(sceneId, selfId, targetId, missionId4)

			local nCurrentDayCount = x300730_GetDayCount(sceneId, selfId)

			if nCurrentDayCount>=x300730_g_DayCountLimited then
				--BeginQuestEvent(sceneId);
				--	AddQuestText(sceneId, "���Ѿ�����˹����ر���������������");
				--EndQuestEvent();
				--DispatchQuestTips(sceneId, selfId);
				--Msg2Player(sceneId,selfId,"���Ѿ�����˹����ر���������������",8,2);
				--return 0;
			end

			

			
			if country == 0 then
				
				if IsHaveQuestNM( sceneId, selfId, mission2submitId1) >0 then
					AddQuestText(sceneId,Readme2)
					AddQuestText(sceneId,"  �������岻�������ҹ�������ʹ�ñ��������Ƽ����ȶ������ҹ���־֮ʿ����������ǰ�������������������֣�")
					local state1 = GetQuestStateNM(sceneId, selfId, targetId, mission2submitId1)
					AddQuestNumText(sceneId, script, mission2submit1, state1, mission2submitId1,2)
				elseif IsHaveQuestNM( sceneId, selfId, shoubian_missionId1) >0 then
					AddQuestText(sceneId,Readme3)
				
				else
					
					if IsHaveQuestNM( sceneId, selfId, missionId1 )==0 then
						AddQuestText(sceneId,Readme)
						AddQuestText(sceneId,"  �������岻�������ҹ�������ʹ�ñ��������Ƽ����ȶ������ҹ���־֮ʿ����������ǰ�������������������֣�")
						local state1 = GetQuestStateNM(sceneId, selfId, targetId, missionId1)
						AddQuestNumText(sceneId, script, mission1, state1, missionId1,2)
					else
						local localexp = (GetLevel( sceneId, selfId )) * 100*3.6*15
						AddQuestText(sceneId,"#Y�����ҡ������ر�")
						AddQuestText(sceneId,strHaveMissionText)
						AddQuestText(sceneId,"#Y��������")
						AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
					end
				end
				
				
				

			elseif country == 1 then

				if IsHaveQuestNM( sceneId, selfId, mission2submitId2) >0 then
					AddQuestText(sceneId,Readme2)
					AddQuestText(sceneId,"  �������岻�������ҹ�������ʹ�ñ��������Ƽ����ȶ������ҹ���־֮ʿ����������ǰ�������������������֣�")
					local state1 = GetQuestStateNM(sceneId, selfId, targetId, mission2submitId2)
					AddQuestNumText(sceneId, script, mission2submit2, state1, mission2submitId2)
				elseif IsHaveQuestNM( sceneId, selfId, shoubian_missionId2) >0 then
					AddQuestText(sceneId,Readme3)
				
				else

					if IsHaveQuestNM( sceneId, selfId, missionId2 )==0 then
						AddQuestText(sceneId,Readme)
						AddQuestText(sceneId,"  �������岻�������ҹ�������ʹ�ñ��������Ƽ����ȶ������ҹ���־֮ʿ����������ǰ�������������������֣�")
						local state2 = GetQuestStateNM(sceneId, selfId, targetId, missionId2)
						AddQuestNumText(sceneId, script, mission2, state2, missionId2)
					else
						local localexp = (GetLevel( sceneId, selfId )) * 100*3.6*15
						AddQuestText(sceneId,"#Y�����ҡ������ر�")
						AddQuestText(sceneId,strHaveMissionText)
						AddQuestText(sceneId,"#Y��������")
						AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
					end
				end

			elseif country == 2 then

				if IsHaveQuestNM( sceneId, selfId, mission2submitId3) >0 then
					AddQuestText(sceneId,Readme2)
					AddQuestText(sceneId,"  �������岻�������ҹ�������ʹ�ñ��������Ƽ����ȶ������ҹ���־֮ʿ����������ǰ�������������������֣�")
					local state1 = GetQuestStateNM(sceneId, selfId, targetId, mission2submitId3)
					AddQuestNumText(sceneId, script, mission2submit3, state1, mission2submitId3)
				elseif IsHaveQuestNM( sceneId, selfId, shoubian_missionId3) >0 then
					AddQuestText(sceneId,Readme3)
				
				else	

					if IsHaveQuestNM( sceneId, selfId, missionId3 )==0 then
						AddQuestText(sceneId,Readme)
						AddQuestText(sceneId,"  �������岻�������ҹ�������ʹ�ñ��������Ƽ����ȶ������ҹ���־֮ʿ����������ǰ�������������������֣�")
						local state3= GetQuestStateNM(sceneId, selfId, targetId, missionId3)
						AddQuestNumText(sceneId, script, mission3, state3, missionId3)
					else
						local localexp = (GetLevel( sceneId, selfId )) * 100*3.6*15
						AddQuestText(sceneId,"#Y�����ҡ������ر�")
						AddQuestText(sceneId,strHaveMissionText)
						AddQuestText(sceneId,"#Y��������")
						AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
					end
				end

			elseif country == 3 then

				if IsHaveQuestNM( sceneId, selfId, mission2submitId4) >0 then
					AddQuestText(sceneId,Readme2)
					AddQuestText(sceneId,"  �������岻�������ҹ�������ʹ�ñ��������Ƽ����ȶ������ҹ���־֮ʿ����������ǰ�������������������֣�")
					local state1 = GetQuestStateNM(sceneId, selfId, targetId, mission2submitId4)
					AddQuestNumText(sceneId, script, mission2submit4, state1, mission2submitId4)
				elseif IsHaveQuestNM( sceneId, selfId, shoubian_missionId4) >0 then
					AddQuestText(sceneId,Readme3)
				
				else

					if IsHaveQuestNM( sceneId, selfId, missionId4 )==0 then
						AddQuestText(sceneId,Readme)
						AddQuestText(sceneId,"  �������岻�������ҹ�������ʹ�ñ��������Ƽ����ȶ������ҹ���־֮ʿ����������ǰ�������������������֣�")
						local state4 = GetQuestStateNM(sceneId, selfId, targetId, missionId4)
						AddQuestNumText(sceneId, script, mission4, state4, missionId4)
					else
						local localexp = (GetLevel( sceneId, selfId )) * 100*3.6*15
						AddQuestText(sceneId,"#Y�����ҡ������ر�")
						AddQuestText(sceneId,strHaveMissionText)
						AddQuestText(sceneId,"#Y��������")
						AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
					end
				end
			end

		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
end


---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300730_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2],DQ_SHOUBIAN_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2],DQ_SHOUBIAN_DAYCOUNT[3] );
	return daycount;

	

end
