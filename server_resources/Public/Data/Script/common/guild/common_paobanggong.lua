
x300640_g_ScriptId	= 300640
x300640_g_MissionId	=	{ --for each country
							7020,
							7742,
							7741,
							7740,
						}

x300640_MP_KILLCOUNT	= 0
x300640_g_MissionName = "����᡿��ᰵս"
x300640_g_LevelUp				=	1
x300640_g_NeedKillMonsterNum			= 200

x300640_g_DayCountUntil = 1	--ÿ����Խ���Ĵ���
x300640_g_GuildExpBonus       = 3
x300640_g_BonusMoney8		=50
x300640_g_SceneList	=	{2,3,5,6,7,8,9,10,11,13,16,17,18,19,20,21,22,23,24,25,26,27,29,30,31,32,33,34,35,104,105,106,107,108,109,110,111,204,205,206,207,208,209,210,211,304,305,306,307,308,309,310,311,404,405,406,407,408,409,410,411}


function x300640_OnLeaveGuild(sceneId, selfId, missionId)
	DelQuestNM( sceneId, selfId, missionId)

	x300640_MarkThisMission(sceneId, selfId, 1)

	local message = format("���Ѿ����ڰ�����ˣ�ɾ��������%s", x300640_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);
end
---------------------------------------------------------------------------------------------------
--���һ�����������������
---------------------------------------------------------------------------------------------------
function x300640_GetLastDay(sceneId, selfId)
	local lastday = GetQuestData(sceneId, selfId, MD_GUILD_ANZHAN_DATE[1], MD_GUILD_ANZHAN_DATE[2], MD_GUILD_ANZHAN_DATE[3])
	return lastday
end

---------------------------------------------------------------------------------------------------
--���һ��������������˼���
---------------------------------------------------------------------------------------------------
function x300640_GetLastDayCount(sceneId, selfId)
	local daycount =  GetQuestData(sceneId, selfId, MD_GUILD_ANZHAN_COUNT[1], MD_GUILD_ANZHAN_COUNT[2], MD_GUILD_ANZHAN_COUNT[3])
	return daycount
end

---------------------------------------------------------------------------------------------------
--�����Ƿ�����������
---------------------------------------------------------------------------------------------------
function x300640_CanDoThisMission(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = x300640_GetLastDay(sceneId, selfId)
	--����ͬһ�죬����
	if today ~= lastday then
		return 1
	end
	
	local daycount = x300640_GetLastDayCount(sceneId, selfId)
	if daycount < x300640_g_DayCountUntil then
		--����<���ɽӴ���������
		return 1
	end
	
	return 0
end

function x300640_SetLastDay(sceneId, selfId, day)
	SetQuestData(sceneId, selfId, MD_GUILD_ANZHAN_DATE[1], MD_GUILD_ANZHAN_DATE[2], MD_GUILD_ANZHAN_DATE[3], day)
end

function x300640_SetLastDayCount(sceneId, selfId, count)
	SetQuestData(sceneId, selfId, MD_GUILD_ANZHAN_COUNT[1], MD_GUILD_ANZHAN_COUNT[2], MD_GUILD_ANZHAN_COUNT[3], count)
end

---------------------------------------------------------------------------------------------------
--��MD�б���������������񡢷�������flag�ò���0���������ò���1
---------------------------------------------------------------------------------------------------
function x300640_MarkThisMission(sceneId, selfId, flag)
	local today = GetDayOfYear()
	local lastday = x300640_GetLastDay(sceneId, selfId)

	--�ϴ���ɵ����ڲ��ǽ���
	if today ~= lastday then
		x300640_SetLastDay(sceneId, selfId, today)
		x300640_SetLastDayCount(sceneId, selfId, 1)
		return
	end
	
	--�ϴ���ɵ������ǽ���
	if flag == 1 then
		local daycount = x300640_GetLastDayCount(sceneId, selfId) + 1
		x300640_SetLastDayCount(sceneId, selfId, daycount)
	end
end

function x300640_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local level =GetLevel(sceneId,selfId)
	if GetGuildID(sceneId, selfId) ~= -1 and level >= 30then
		local state = GetQuestStateNM(sceneId, selfId, targetId, MissionId);
		AddQuestNumText(sceneId, MissionId, x300640_g_MissionName, state, -1)
	end
end

--ѡ������
function x300640_ProcEventEntry( sceneId, selfId, targetId, MissionId )
 	
  if IsHaveQuestNM( sceneId, selfId, MissionId ) == 1 then	-- ������������
		
	 	if GetGuildID(sceneId, selfId) == -1 then
	 		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���Ѿ����ڰ���У����������ټ���������")
			EndQuestEvent()
			DispatchQuestDemandInfo(sceneId, selfId, targetId, x300640_g_ScriptId, MissionId,0);
			return
		end
		
		local country = GetCurCountry(sceneId, selfId)
		local ret
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- �������������
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y����᡿��ᰵս")
			AddQuestText(sceneId,"\t��ϲ��������ˡ���᡿��ᰵս�����Ǹ����Ľ����������¡�#r#r#r#r")
			--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
			local level = GetLevel(sceneId, selfId)
			local exp = floor(level * 26000)
			AddQuestText( sceneId, "#Y�������ݣ�#W#r�ﹱ��50��#r��ᾭ�飺3��#r����ֵ��"..exp.."��#rʹ���㣺1��")
			EndQuestEvent()
			DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300640_g_ScriptId, MissionId);
		else
			BeginQuestEvent(sceneId)
			local Readme_1 = "\t������ͨ��������񷢲��˽���ÿ��һ�εİ�ᰵս���������µص�������Ӧ�ȼ��Ĺ���200ֻ��������ĵȼ�����Ŀ�����ȼ�5�����Ͻ������������\n\t����������#G��ս��#Wʱ2Сʱ�ڻظ�����ɻ�÷����������飬�ﹱ��2��ʹ���㣡�½��������ʱ�����24Сʱ�ߣ����ܻ�ð�ᾭ�飡#r"			
			
			local Readme_2 = "#R ���     ��45-140����#R�����᳡����#O#r#G �����Թ� ��30-110����#G����ƽ������#W#r"
			
			local Readme_3 = "��ѡ���Ӧ��ͼ�������#r"
			
			local Readme_4 = "#GС��ʾ�����������ڰ��ȼ�������������õĽ���Ҳ����Ӧ���ӡ���Ҳ���ԺͷǱ����Ա����������"
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4
			AddQuestText(sceneId,Readme)
			--����Ŀ��
			AddQuestText( sceneId,"#Y��������")
			AddQuestText(sceneId, "δ���#r");
			--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
			local level = GetLevel(sceneId, selfId)
			local exp = floor(level * 26000)
			AddQuestText( sceneId, "#Y�������ݣ�#W#r�ﹱ��50��#r��ᾭ�飺3��#r����ֵ��"..exp.."��#rʹ���㣺1��")
			EndQuestEvent()
			DispatchQuestDemandInfo(sceneId, selfId, targetId, x300640_g_ScriptId, MissionId,0);
		end
		
		country = GetCurCountry(sceneId, selfId)
		if country == 0 then 
			ret = CallScriptFunction( 256264, "Finishanzhan", sceneId, selfId)
		elseif country == 1 then
			ret = CallScriptFunction( 256265, "Finishanzhan", sceneId, selfId)
		elseif country == 2 then
			ret = CallScriptFunction( 256266, "Finishanzhan", sceneId, selfId)
		elseif country == 3 then
			ret = CallScriptFunction( 256267, "Finishanzhan", sceneId, selfId)
		end
			
		return ret
	end
	
	-- if x300640_CanDoThisMission( sceneId, selfId) ~= 1 then
		-- BeginQuestEvent( sceneId)
		-- AddQuestText( sceneId, "�ܱ�Ǹ���������Ѿ���������������������ɡ�")
		-- EndQuestEvent()
		-- DispatchQuestDemandInfo(sceneId, selfId, targetId, x300640_g_ScriptId, MissionId,0);
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "�ܱ�Ǹ���������Ѿ���������������������ɡ�");
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)	
		-- Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������Ѿ���������������������ɡ�",8,2)
		
		-- return
	-- end
	BeginQuestEvent(sceneId)
			local Readme_1 = "\t������ͨ��������񷢲��˽���ÿ��һ�εİ�ᰵս���������µص�������Ӧ�ȼ��Ĺ���200ֻ��������ĵȼ�����Ŀ�����ȼ�5�����Ͻ������������\n\t����������#G��ս��#Wʱ2Сʱ�ڻظ�����ɻ�÷����������飬�ﹱ��2��ʹ���㣡�½��������ʱ�����24Сʱ�ߣ����ܻ�ð�ᾭ�飡#r"			
			local Readme_2 = "#R ���     ��45-140����#R�����᳡����#O#r#G �����Թ� ��30-110����#G����ƽ������#W#r"
			local Readme_3 = "��ѡ���Ӧ��ͼ�������#r"
			local Readme_4 ="#GС��ʾ�����������ڰ��ȼ�������������õĽ���Ҳ����Ӧ���ӣ���ɫ��ͼΪPK��ͼ��"
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4
			AddQuestText(sceneId,"#Y����᡿��ᰵս")
			AddQuestText(sceneId,Readme)
			--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
			local level = GetLevel(sceneId, selfId)
			local exp = floor(level * 26000)
			local 	Readme = "#Y�������ݣ�#W#r�ﹱ��50��#r��ᾭ�飺3��#r����ֵ��"..exp.."��#rʹ���㣺1��"							
			AddQuestText( sceneId,Readme )
			EndQuestEvent()

			local nCountry = GetCurCountry( sceneId, selfId )

			DispatchQuestInfo(sceneId, selfId, targetId, x300640_g_MissionId[nCountry+1], -1)
			return

end

function x300640_DoAccept( sceneId, selfId )
	if GetGuildID(sceneId, selfId) == -1 then
		return "�ܱ�Ǹ����û�м����ᣬ������ȡ������"
	end
	if GetLevel(sceneId, selfId) < x300640_g_LevelUp then
		return format("�ܱ�Ǹ�����ĵȼ�����%d����������ȡ������", x300640_g_LevelUp)
	end
	
	if 1 == IsQuestFullNM(sceneId, selfId) then
			return "�ܱ�Ǹ�����������Ѿ����ˣ�������ȡ������"
	end
	
	--���ǰ������
	local nCountry = GetCurCountry( sceneId, selfId )
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x300640_g_MissionId[nCountry+1] )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return 
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return 
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return
		end
	end
	
	AddQuestNM(sceneId, selfId, x300640_g_MissionId[nCountry+1]);

	x300640_MarkThisMission(sceneId, selfId, 1)
	
	-- write log file
	x300640_WriteLog( sceneId, selfId, MissionId, 121);
	local misIndex = GetQuestIndexByID(sceneId, selfId, x300640_g_MissionId[nCountry+1]);
	SetQuestByIndex(sceneId, selfId, misIndex, x300640_MP_KILLCOUNT, 0);
	
	local str = format("����ȡ������%s", x300640_g_MissionName)
	Msg2Player(sceneId,selfId,str,8,2)
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	
	return nil
end
--**********************************
--����
--**********************************
function x300640_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
if x300640_CanDoThisMission( sceneId, selfId) ~= 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���������Ѿ���ȡ����ᰵս���������������ɡ�");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������Ѿ���ȡ����ᰵս���������������ɡ�",8,2)	
		return
	end
	local str = x300640_DoAccept( sceneId, selfId )
	if str ~= nil then
		Msg2Player(sceneId,selfId,str,8,2)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	end
end
function x300640_OnReturn1(sceneId, selfId,MissionData,MissionId,targetId)
 local curTime = GetCurrentTime()
	local isMultiple = 0
	if curTime - MissionData < 2*60*60 then
		isMultiple = 1
	end
	local joinguildtime = MissionId
	x300640_GetBonus( sceneId,selfId, isMultiple, joinguildtime )
end

function x300640_GetBonus( sceneId, selfId, isMultiple,joinguildtime )

			local guildId = GetGuildID(sceneId, selfId);
			local GuildLevel = GetGuildSimpleData( GetGuildID( sceneId, selfId ) )--�õ���������(�ȼ�) 	
			if guildId ~= -1 then
				--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
				local level = GetLevel(sceneId, selfId)
				local exp = floor(level * 26000)
				AddGuildUserPoint(sceneId,selfId,50)				--���Ӱﹱ
				AddGuildShiMing(sceneId, selfId,1)
				AddExp (sceneId,selfId,(GetLevel(sceneId, selfId)) * 26000)				--���Ӿ���
				local Readme_1 = "����������񣺡���᡿��ᰵս "
				local Readme_2 = "���#R�ﹱ50��#o�Ľ�����"
				local Readme_4 = "���#R����ֵ"..exp.."��#o�Ľ�����"
				--local Readme_5 = "���#R��Ṧ��1��#o�Ľ�����"
				local Readme_6 = "���#Rʹ����1��#o�Ľ�����"
				Msg2Player(sceneId,selfId,Readme_1,8,3)
				Msg2Player(sceneId,selfId,Readme_2,8,3)
				--Msg2Player(sceneId,selfId,Readme_3,8,3)
				Msg2Player(sceneId,selfId,Readme_4,8,3)
				--Msg2Player(sceneId,selfId,Readme_5,8,3)
				Msg2Player(sceneId,selfId,Readme_6,8,3)
				Msg2Player(sceneId,selfId,Readme_1,8,2)
				Msg2Player(sceneId,selfId,Readme_2,8,2)
				--Msg2Player(sceneId,selfId,Readme_3,8,2)
				Msg2Player(sceneId,selfId,Readme_4,8,2)
				--Msg2Player(sceneId,selfId,Readme_5,8,2)
				Msg2Player(sceneId,selfId,Readme_6,8,2)
				if isMultiple == 1 then
					local ExpBonus1 = (GetLevel(sceneId, selfId)) * 26000*3
					local Exp3 = (GetLevel(sceneId, selfId)) *26000*2
					local ExpBonus2 = (GetLevel(sceneId, selfId)) *26000*3
					local pos = GetGuildOfficial(sceneId, selfId)
					local text3 = "������#Rʹ����2��#o�Ľ���"
					AddGuildShiMing(sceneId, selfId,2)
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, text3);
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,text3,8,2)
					if  pos == 5 then
						local guildid =GetGuildID(sceneId, selfId)
						if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "����ְλֻ����ȡһ�ΰ�ս���");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
							Msg2Player(sceneId,selfId,"����ְλֻ����ȡһ�ΰ�ս���",8,2)
						else
							AddExp(sceneId, selfId, ExpBonus1);	
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "������#R����"..ExpBonus1.."��#o�Ľ���");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"���౶���������#R����"..ExpBonus1.."��#o�Ľ���",8,2)
							SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
						end
					elseif pos == 4 then
						local guildid =GetGuildID(sceneId, selfId)
						if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "������ְλֻ����ȡһ�ΰ�ս���");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
							Msg2Player(sceneId,selfId,"������ְλֻ����ȡһ�ΰ�ս���",8,2)
						else
							AddExp(sceneId, selfId, Exp3);	
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "������#R����"..Exp3.."��#o�Ľ���");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"���౶���������#R����"..Exp3.."��#o�Ľ���",8,2)
							SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
						end
					else
						AddExp(sceneId, selfId, exp);	
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)	
						Msg2Player(sceneId,selfId,"���౶���������#R����"..exp.."��#o�Ľ���",8,2)
					end
				end
				if 	GuildLevel == 2 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*0.25 )
					AddExp(sceneId, selfId, exp);
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("���ȼ�2��������#R����"..exp.."��#o�Ľ���"),8,2)
				end
				if 	GuildLevel == 3 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*0.5 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("���ȼ�3��������#R����"..exp.."��#o�Ľ���"),8,2)
				end
				if 	GuildLevel == 4 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*0.75 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("���ȼ�4��������#R����"..exp.."��#o�Ľ���"),8,2)
				end
				if 	GuildLevel == 5 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*1 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("���ȼ�5��������#R����"..exp.."��#o�Ľ���"),8,2)
				end
				if 	GuildLevel == 6 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*1.25 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("���ȼ�6��������#R����"..exp.."��#o�Ľ���"),8,2)
				end
				if 	GuildLevel == 7 then
					local level = GetLevel(sceneId, selfId)
					local exp = ceil (level *26000*1.5 )
					AddExp(sceneId, selfId, exp);	
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId, "������#R����"..exp.."��#o�Ľ���");
					EndQuestEvent(sceneId)
					DispatchQuestTips(sceneId,selfId)	
					Msg2Player(sceneId,selfId,format("���ȼ�7��������#R����"..exp.."��#o�Ľ���"),8,2)
				end
				if isMultiple == 1 then
					local pos = GetGuildOfficial(sceneId, selfId)
					if pos == 5 then
					local guildid =GetGuildID(sceneId, selfId)
						if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "����ְλֻ����ȡһ�ΰ�ս���");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
							Msg2Player(sceneId,selfId,"����ְλֻ����ȡһ�ΰ�ս���",8,2)
						else
							AddGuildUserPoint(sceneId,selfId,150)	--���Ӱﹱ
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "������#R�ﹱ150��#o�Ľ���");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"���౶���������#R�ﹱ150��#o�Ľ���",8,2)
							SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_CHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
						end
					elseif pos == 4 then
					local guildid =GetGuildID(sceneId, selfId)
						local guildid =GetGuildID(sceneId, selfId)
						if  GetGuildCacheFreeParam(guildid,GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY) == GetDayOfYear() then
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "������ְλֻ����ȡһ�ΰ�ս���");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
							Msg2Player(sceneId,selfId,"������ְλֻ����ȡһ�ΰ�ս���",8,2)
						else
							AddGuildUserPoint(sceneId,selfId,100)	--���Ӱﹱ
							local BonusMoney8 = x300621_g_BonusMoney8
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId, "������#R�ﹱ100��#o�Ľ���");
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)	
							Msg2Player(sceneId,selfId,"���౶���������#R�ﹱ100��#o�Ľ���",8,2)
							SetGuildQuestData(sceneId,GetGuildID(sceneId,selfId),GD_GUILD_INDEX_ASSCHIEF_MULTIMISSION_DAY,GetDayOfYear(),0)
						end
					else
						AddGuildUserPoint(sceneId,selfId,50)	--���Ӱﹱ
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId, "������#R�ﹱ50��#o�Ľ���");
						EndQuestEvent(sceneId)
						DispatchQuestTips(sceneId,selfId)	
						Msg2Player(sceneId,selfId,format("���౶���������#R�ﹱ50��#o�Ľ���", x300621_g_BonusMoney8),8,2)
					end
				end
				if joinguildtime == -1 or GetCurrentTime()-joinguildtime<24*3600 then
					BeginQuestEvent(sceneId)
					AddQuestText( sceneId, "�ܱ�Ǹ����������ʱ�����24Сʱ�����ܻ�ð�ᾭ�顣" )
					EndQuestEvent( sceneId )
					DispatchQuestTips( sceneId, selfId )
					Msg2Player(sceneId,selfId,"�ܱ�Ǹ����������ʱ�����24Сʱ�����ܻ�ð�ᾭ�顣",8,2)
					return
				end
				local name = GetName(sceneId, selfId)
				--if 	gongde >= 5 then
					AddGuildExp(sceneId, selfId, 3);				--���Ӱ�ᾭ��
				-- else
				BeginQuestEvent(sceneId)
				AddQuestText( sceneId, "���#R��ᾭ��3��#o�Ľ�����" )
				EndQuestEvent( sceneId )
				DispatchQuestTips( sceneId, selfId )
				Msg2Player(sceneId,selfId,"���#R��ᾭ��3��#o�Ľ�����",8,2)
				Msg2Player(sceneId,selfId,"��᣺"..name.."����ˡ���᡿��ᰵս����Ϊ��ṱ����3���ᾭ�顣",6,2)
				-- end
				--AddGuildMerit(sceneId, selfId,1)
			end		
end

--�������
--����1����ɹ���0��������ʧ��
function x300640_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

    if MissionId == nil or MissionId < 0 then
        return 0
    end

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then	-- ���û�������ֱ���˳�
		return 0
	end
	--������ 
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local ret = QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
	if ret > 0 then -- ����������
		local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- ��ȡ���������Ϣ
		if ret == 1 then -- ����ɹ����

			DelQuestNM( sceneId, selfId, MissionId)

            -- ���ӻ�Ծ��
            local id = GetGuildID( sceneId, selfId)
            if id ~= -1 then
                AddGuildActivity( sceneId, selfId, GetGuildCacheFreeParam( id, GD_GUILD_ACTIVITY_PARAM3) )
            end

			x300640_MarkThisMission(sceneId, selfId, 1)
	
			-- write log file
			x300640_WriteLog( sceneId, selfId, MissionId, 122);
			--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_ANZHAN, x300640_g_ScriptId,MissionId,"OnReturn1",targetId)
			GetJoinGuildTime(sceneId,selfId,x300640_g_ScriptId)
		end
	end
    
	return 0
end

function x300640_OnMemberJoinTimeReturn( sceneId, selfId, param )

	GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_MULTI_MISSION_ANZHAN, x300640_g_ScriptId,param,"OnReturn1",-1)

end

function x300640_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
	
end


--********************************************************************
--����
--********************************************************************
function x300640_ProcQuestAbandon( sceneId, selfId, MissionId )
	
	DelQuestNM( sceneId, selfId, MissionId)

	x300640_MarkThisMission(sceneId, selfId, 1)
	
	local message = format("������������%s", x300640_g_MissionName);
	BeginQuestEvent(sceneId);
	AddQuestText(sceneId, message);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId, selfId, message, 8, 2);
	
end


--д��־
function x300640_WriteLog( sceneId, selfId, MissionId, gameId)
	GamePlayScriptLog(sceneId, selfId, gameId)
end
--ɱ������
function x300640_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
						   --����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID

end

--ɱ������
function x300640_OnDie( sceneId, objId, killerId )

							   --����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID
	--�ж�ɱ�ֵص��Ƿ�������ָ���ĳ���
	if IsObjValid( sceneId,killerId ) ~=1 then
		return
	end
	
	local killerType = GetObjType(sceneId, killerId)

	--����ɱ�ģ�����������
	if killerType == 3 then
		killerId = GetOwnerID(sceneId, killerId)
	end	
	
	if IsPlayerStateNormal( sceneId, killerId) ~= 1 then
        return
    end
	
	local bInScene = 0;
	for i, item in x300640_g_SceneList do
		if sceneId == item then
			bInScene = 1;
			break;
		end
	end
	if bInScene <= 0 then
		return 0;
	end
	
	local NeedKilledNum = x300640_g_NeedKillMonsterNum;
	local str = "";
	
	local num = 1;
	local bHasTeam = HasTeam(sceneId, killerId);
	if bHasTeam > 0 then
		num = GetNearTeamCount(sceneId, killerId)
	end
  
	local memberId = killerId;
	local nCountry = GetCurCountry( sceneId, killerId )
	local MissionName = GetQuestNameNM(sceneId, killerId, x300640_g_MissionId[nCountry+1]);
  
	for i=0, num-1 do
		if bHasTeam > 0 then
			memberId = GetNearTeamMember(sceneId, killerId, i);
		end

		local misIndex = GetQuestIndexByID(sceneId, memberId, x300640_g_MissionId[nCountry+1]);
		local curKillNum = GetQuestParam(sceneId, memberId, misIndex, x300640_MP_KILLCOUNT)
		local level = GetLevel(sceneId,killerId)
		if curKillNum < NeedKilledNum and IsPlayerStateNormal( sceneId, memberId) == 1 and GetHp(sceneId, memberId) > 0 and IsHaveQuestNM(sceneId, memberId, x300640_g_MissionId[nCountry+1]) > 0  and GetGuildID(sceneId, memberId) ~= -1 then
			if GetLevel(sceneId, objId) >= GetLevel(sceneId, memberId)-5 then--�����ɱ���Ĺֵȼ����ڻ������ҵȼ�
				local KilledNum = GetQuestParam(sceneId, memberId, misIndex, x300640_MP_KILLCOUNT);
				if KilledNum < NeedKilledNum then
					SetQuestByIndex(sceneId, memberId, misIndex, x300640_MP_KILLCOUNT, KilledNum+1);
				
					if KilledNum == x300640_g_NeedKillMonsterNum - 1 then
						--����ˡ���
						str = format( "#G%s#Y���Ѿ�����: %d/%d������", MissionName, KilledNum+1, x300640_g_NeedKillMonsterNum )
						SetQuestByIndex( sceneId, memberId, misIndex, 7, 1 )
					else
						str = format( "#G%s#Y���Ѿ�����: %d/%d������", MissionName, KilledNum+1, x300640_g_NeedKillMonsterNum )
					end
					BeginQuestEvent(sceneId)
					AddQuestText( sceneId, str )
					EndQuestEvent( sceneId )
					DispatchQuestTips( sceneId, memberId )
				end
		
			elseif GetLevel(sceneId, objId) < GetLevel(sceneId, killerId)-5 then--�����ɱ���Ĺֵȼ�С����ҵȼ�����ʾ��ʾ��Ϣ
					nlevel = ceil(level/5)
					mlevel =nlevel*5-5
					BeginQuestEvent(sceneId)
					AddQuestText( sceneId, "���ĵȼ����ߣ�����ս������"..mlevel.."���ĵ��ˡ�" )
					local message = format("���ĵȼ����ߣ�����ս������"..mlevel.."���ĵ��ˡ�")
					EndQuestEvent( sceneId )
					DispatchQuestTips( sceneId, killerId )
					Msg2Player(sceneId, killerId, message, 8, 2);
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300640_QuestLogRefresh( sceneId, selfId, MissionId)

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,MissionId );
	if bHaveMission > 0 then
	BeginQuestEvent(sceneId)	
		if x300640_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x300640_g_BonusMoney8 )	--���Ӱﹱ
		end
		if x300640_g_GuildExpBonus>0 then
			AddQuestGuildExpBonus(sceneId,x300640_g_GuildExpBonus)--��ᾭ��
		end 
		local level = GetLevel(sceneId, selfId)
		--local gongdezhi =GetMeritInfo_Multiple(sceneId, selfId)
		local ExpBonus = ceil (level * 26000)
		AddQuestExpBonus(sceneId, ExpBonus);

		-- local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
		-- local num = GetQuestParam(sceneId, selfId,misIndex,0)
		-- local text = format("(kkkkkkkkkkq%d/%d)",num,5)

		AddQuestLogCustomText( sceneId,
								"",								-- ����
								"",								-- ��������
								"",								--����Ŀ��
								"",								--����NPC
								"",								--������
								"",								--��������
								"���������ڰ��ȼ�������������õĽ���Ҳ����Ӧ���ӡ�"								--����С��ʾ
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	end

end

function x300640_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	local nCountry = GetCurCountry( sceneId, selfId )
	x300640_QuestLogRefresh( sceneId, selfId, x300640_g_MissionId[nCountry+1] );
end 