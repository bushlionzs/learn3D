x300929_g_ScriptId = 300929
x300929_g_MissionName = "�����ҡ���ؽ���"
x300929_g_GameId =1047

function x300929_ProcEnumEvent( sceneId, selfId, targetId, index )
		if GetGuildID( sceneId, selfId ) == -1 then
			--���ڰ����
			return
		end
	if GetGameOpenById(x300929_g_GameId) > 0 then
		AddQuestNumText(sceneId,x300929_g_ScriptId, x300929_g_MissionName, 3)
		
	end
	
end

function x300929_ProcEventEntry( sceneId , selfId , targetId , state , index )
	GetGuildQuestData(sceneId,selfId,GD_GUILD_LAIRDBATTLE_SCENEID, x300929_g_ScriptId,-1,"ProcEventEntry1")		
end

function x300929_ProcEventEntry1(sceneId, selfId,MissionData,MissionId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����",8,2)
		
		return
	end
	
	local money = 0
	local nLaridMoney = 0

	BeginQuestEvent(sceneId)
	local nGuildID = GetGuildID(sceneId,selfId)
	local pos = GetGuildOfficial(sceneId, selfId)
	local ding = 0
	local liang =0
	local wen = 0
	if pos == 5 then
		if MissionData ==6 then
			 money = format(4*9*0.5*1000)
		end
		
		if MissionData ==9 then
			 money = format(4*10*0.5*1000)
		end
		
		if MissionData ==13 then
			 money = format(4*11*0.5*1000)
		end
		
		if MissionData ==18 then
			 money = format(4*12*0.5*1000)
		end
		
		
		if MissionData ==21 then
			 money = format(4*13*0.5*1000)
		end
		
		
		if MissionData ==24 then
			 money = format(4*14*0.5*1000)
		end
		
		
		if MissionData ==27 then
			 money = format(4*15*0.5*1000)
		end
		
		
		if MissionData ==31 then
			 money = format(4*16*0.5*1000)
		end
		
		if MissionData ==34 then
			 money = format(4*17*0.5*1000)
		end
	else
		if MissionData ==6 then
			 money = format(9*0.5*1000)
		end
		
		if MissionData ==9 then
			 money = format(10*0.5*1000)
		end
		
		if MissionData ==13 then
			 money = format(11*0.5*1000)
		end
		
		if MissionData ==18 then
			 money = format(12*0.5*1000)
		end
		
		
		if MissionData ==21 then
			 money = format(13*0.5*1000)
		end
		
		
		if MissionData ==24 then
			 money = format(14*0.5*1000)
		end
		
		
		if MissionData ==27 then
			 money = format(15*0.5*1000)
		end
		
		
		if MissionData ==31 then
			 money = format(16*0.5*1000)
		end
		
		if MissionData ==34 then
			 money = format(17*0.5*1000)
		end
	end
	
	
	nLaridMoney = money * nLairdLevel/10
	
	local Readme_1 = "#Y�����ҡ���ؽ���#r#W"
	local Readme_2 = "\t���ã��𾴵����ռ���ߣ������ĵȼ��ﵽ#R60��#Wʱ����������ÿ#R����#W��#R0��-16��#W��ȡ���ܵġ����ҡ���ؽ��������ǻ������ռ�е���صȼ�����������Ӧ�Ľ𿨽�����ռ�����صȼ�Խ�ߣ���õĽ���Խ�ࡣ #r"
	local Readme_3 = "\t��Ϊ��ص�����������������ȡ��ͨ����Ա�ı��Ľ𿨽�����#r #r"
	local Readme_4 = "�����ܿ�����ȡ�Ľ𿨽������£�#r #r"
	local Readme_5 = format("�𿨣�#Y#{_MONEY%d}#W",money)
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	AddQuestText(sceneId, Readme);
	EndQuestEvent(sceneId);
	DispatchQuestInfo( sceneId, selfId,-1, x300929_g_ScriptId, -1 );

end

function x300929_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

function x300929_ProcAccept( sceneId, selfId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����",8,2)
		
		return
	end

	local hour,minute,second = GetHourMinSec()
    local curTime = GetMinOfDay()
	if GetWeek() ~= 6 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������ȡ��",8,2)
		return
	end
	if curTime >= 960 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������0��-16�����ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������0��-16�����ȡ��",8,2)
		return
	end	
	if	GetLevel(sceneId, selfId) < 60 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������",8,2)
		return
	end
	
	-- local lastDay = GetQuestData(sceneId, selfId, MD_JUDIANMONEY_DATE[1], MD_JUDIANMONEY_DATE[2], MD_JUDIANMONEY_DATE[3])
	-- local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)
	
	-- if lastDay ~= 0 and GetDayOfYear() == lastDay then
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ������ؽ�Ǯ������")
		-- DispatchQuestTips(sceneId, selfId)
		-- EndQuestEvent(sceneId)
		-- Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ������ؽ�Ǯ������",8,2)
		-- return
	-- end
	
	GetGuildQuestData(sceneId,selfId,GD_GUILD_LAIRDBATTLE_SCENEID, x300929_g_ScriptId,-1,"GetGuildLairdSceneId")
end

function x300929_GetGuildLairdSceneId(sceneId, selfId,MissionData,MissionId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����",8,2)
		
		return
	end

	local hour,minute,second = GetHourMinSec()
    local curTime = GetMinOfDay()
	if GetWeek() ~= 6 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������ȡ��",8,2)
		return
	end
	if curTime >= 960 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������0��-16�����ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������0��-16�����ȡ��",8,2)
		return
	end	
	if	GetLevel(sceneId, selfId) < 60 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������",8,2)
		return
	end

	if MissionData > 0 then
		if MissionData ~= 6 and MissionData ~= 9 and MissionData ~= 13 and 
		   MissionData ~= 18 and MissionData ~= 21 and MissionData ~= 24 and 
		   MissionData ~= 27  and MissionData ~= 31 and MissionData ~= 34then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�ܱ�Ǹ�������Ǹ����ռ����");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�������Ǹ����ռ����",4,2)		
			return
		end
	else
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�ܱ�Ǹ����û��ռ���κ����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ����û��ռ���κ����",4,2)	
		return
	end
	local lastDay = GetQuestData(sceneId, selfId, MD_JUDIANMONEY_DATE[1], MD_JUDIANMONEY_DATE[2], MD_JUDIANMONEY_DATE[3])
	local lastFortune = GetFortuneLastTime(sceneId, selfId, 1)
	
	if lastDay ~= 0 and GetDayOfYear() == lastDay then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ������ؽ�Ǯ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ������ؽ�Ǯ������",8,2)
		return
	end
	GetJoinGuildTime(sceneId,selfId,x300929_g_ScriptId)
end

function x300929_OnMemberJoinTimeReturn( sceneId, selfId, param )

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����",8,2)
		
		return
	end

	local hour,minute,second = GetHourMinSec()
    local curTime = GetMinOfDay()
	if GetWeek() ~= 6 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������ȡ��",8,2)
		return
	end
	if curTime >= 960 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������0��-16�����ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������0��-16�����ȡ��",8,2)
		return
	end	
	if	GetLevel(sceneId, selfId) < 60 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������",8,2)
		return
	end
	
	if param == -1 or GetCurrentTime()-param<24*3600 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ������������ռ����ʱ�����24Сʱ��������ȡ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ������������ռ����ʱ�����24Сʱ��������ȡ������",8,2)
		return		
	end
	
	GetGuildQuestData(sceneId,selfId,GD_GUILD_LAIRDBATTLE_DATE, x300929_g_ScriptId,-1,"Newqinglong")
end

function x300929_Newqinglong(sceneId, selfId,MissionData,MissionId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����",8,2)
		
		return
	end

	
	local hour,minute,second = GetHourMinSec()
    local curTime = GetMinOfDay()
	if GetWeek() ~= 6 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������ȡ��",8,2)
		return
	end
	if curTime >= 960 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������0��-16�����ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������0��-16�����ȡ��",8,2)
		return
	end	
	if	GetLevel(sceneId, selfId) < 60 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������",8,2)
		return
	end
	
	local curDay = GetDayTime()
	if curDay == MissionData then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�ܱ�Ǹ��������̨�����ռ���߲�����ȡ����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��������̨�����ռ���߲�����ȡ����",4,2)
		return
	end
	GetGuildQuestData(sceneId,selfId,GD_GUILD_LAIRDBATTLE_REDEEM_DATE, x300929_g_ScriptId,-1,"CheckHasRedeem")
end

function x300929_CheckHasRedeem( sceneId, selfId, param )

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����",8,2)
		
		return
	end

	local hour,minute,second = GetHourMinSec()
    local curTime = GetMinOfDay()
	if GetWeek() ~= 6 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������ȡ��",8,2)
		return
	end
	if curTime >= 960 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������0��-16�����ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������0��-16�����ȡ��",8,2)
		return
	end	
	if	GetLevel(sceneId, selfId) < 60 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������",8,2)
		return
	end

	local nGuildID = GetGuildID(sceneId,selfId)
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos == 5 then
		if param == GetDayOfYear() then
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ����Ǯ������",8,3)
			Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ����Ǯ������",8,2)
			return		
		end
	else
		GetQuestData(sceneId, selfId, MD_JUDIANMONEY_DATE[1], MD_JUDIANMONEY_DATE[2], MD_JUDIANMONEY_DATE[3])
	end
	GetGuildQuestData(sceneId,selfId,GD_GUILD_LAIRDBATTLE_SCENEID, x300929_g_ScriptId,-1,"GetGuildLairdSceneId2")
end


function x300929_GetGuildLairdSceneId2(sceneId, selfId,MissionData,MissionId)

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����ذ���Ա������ȡ��ؽ�����",8,2)
		
		return
	end

	local hour,minute,second = GetHourMinSec()
    local curTime = GetMinOfDay()
	if GetWeek() ~= 6 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������ȡ��",8,2)
		return
	end
	if curTime >= 960 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ��ֻ����������0��-16�����ȡ��")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ��ֻ����������0��-16�����ȡ��",8,2)
		return
	end	
	if	GetLevel(sceneId, selfId) < 60 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���ﵽ60���ſ�����ȡ��ؽ�Ǯ������",8,2)
		return
	end

	local nGuildID = GetGuildID(sceneId,selfId)
	local nLairdMapId,_,_,_,nLairdLevel = GetGuildLairdSceneId(nGuildID)
	if nLairdMapId <= 0 then
		return
	end
	
	local money = 0
	local money1 = 0
	local nLaridMoney = 0
	
	local pos = GetGuildOfficial(sceneId, selfId)
	if pos == 5 then
		if MissionData ==6 then
			 money1 = format(4*9*0.5*1000)
		end
		
		if MissionData ==9 then
			 money1 = format(4*10*0.5*1000)
		end
		
		if MissionData ==13 then
			 money1 = format(4*11*0.5*1000)
		end
		
		if MissionData ==18 then
			 money1 = format(4*12*0.5*1000)
		end
		
		
		if MissionData ==21 then
			 money1= format(4*13*0.5*1000)
		end
		
		
		if MissionData ==24 then
			 money1 = format(4*14*0.5*1000)
		end
		
		
		if MissionData ==27 then
			 money1 = format(4*15*0.5*1000)
		end
		
		
		if MissionData ==31 then
			 money1 = format(4*16*0.5*1000)
		end
		
		if MissionData ==34 then
			 money1 = format(4*17*0.5*1000)
		end
		
		AddMoney( sceneId, selfId, 3, money1 )
		SetGuildQuestData( sceneId,GetGuildID( sceneId, selfId ),GD_GUILD_LAIRDBATTLE_REDEEM_DATE,GetDayOfYear() )
		
		nLaridMoney = money1 * nLairdLevel/10
		AddMoney( sceneId, selfId, 3, nLaridMoney )
		
		
		local award = format("����ȡ��#R#{_MONEY%d}#o��", money1)
		local awardLaird = format("��صȼ��ӳɶ�����#R#{_MONEY%d}#o��", nLaridMoney)
		
		Msg2Player(sceneId,selfId,award,4,3)
		Msg2Player(sceneId,selfId,awardLaird,4,3)
		--Msg2Player(sceneId,selfId,award,4,2)
		GamePlayScriptLog(sceneId,selfId,1481)
	end
	
	if  pos ~= 5 then
		if MissionData ==6 then
			 money = format(9*0.5*1000)
		end
		
		if MissionData ==9 then
			 money = format(10*0.5*1000)
		end
		
		if MissionData ==13 then
			 money = format(11*0.5*1000)
		end
		
		if MissionData ==18 then
			 money = format(12*0.5*1000)
		end
		
		
		if MissionData ==21 then
			 money = format(13*0.5*1000)
		end
		
		
		if MissionData ==24 then
			 money = format(14*0.5*1000)
		end
		
		
		if MissionData ==27 then
			 money = format(15*0.5*1000)
		end
		
		
		if MissionData ==31 then
			 money = format(16*0.5*1000)
		end
		
		if MissionData ==34 then
			 money = format(17*0.5*1000)
		end
		
		AddMoney( sceneId, selfId, 3, money )
		SetQuestData(sceneId, selfId, MD_JUDIANMONEY_DATE[1], MD_JUDIANMONEY_DATE[2], MD_JUDIANMONEY_DATE[3], GetDayOfYear())	
		
		nLaridMoney = money * nLairdLevel/10
		AddMoney( sceneId, selfId, 3, nLaridMoney )
		
		
		local award = format("����ȡ��#R#{_MONEY%d}#o��", money)
		local awardLaird = format("��صȼ��ӳɶ�����#R#{_MONEY%d}#o��", nLaridMoney)
		
		Msg2Player(sceneId,selfId,award,4,3)
		Msg2Player(sceneId,selfId,awardLaird,4,3)
		--Msg2Player(sceneId,selfId,award,4,2)
		GamePlayScriptLog(sceneId,selfId,1481)
	end
end