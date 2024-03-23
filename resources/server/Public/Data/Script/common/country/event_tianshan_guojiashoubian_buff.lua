
x300857_g_ScriptId	= 300857

x300857_g_x1		= 112
x300857_g_z1		= 164
x300857_g_x2		= 141
x300857_g_z2		= 193

x300857_g_TimerIndex				=	6
x300857_g_Shoubian_ScriptId			=	300860
x300857_g_Mission_Id				=	7569

--x300857_g_BuffId					=	7708		
--x300857_g_Buff_Time					=	10*60	--��λ����
--x300857_g_Time_Interval				=	10		--��λ����

function x300857_GetMissionId( sceneId, selfId )
	
	return x300857_g_Mission_Id
end

--�������ʱ����
function x300857_OnIntervalOverEvent( sceneId, selfId )
	local country = GetCurCountry( sceneId, selfId )

	local nMyMissionId = x300857_GetMissionId( sceneId, selfId )

	if IsHaveQuestNM(sceneId,selfId,nMyMissionId) <= 0 then
        return 
    end

--	--// ����TickCount
--	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
--	local nTickCount = GetQuestParam( sceneId, selfId, misIndex, x300857_g_TimerIndex )+1
--	
--	SetQuestByIndex( sceneId, selfId, misIndex, x300857_g_TimerIndex, nTickCount )
--	--//����end
--
--	--// ͬ���ͻ��˺ͷ������� 
--	TimerCommand( sceneId, selfId, 1, 7569, -1,-1,-1,-1 );
--
--	local nTime = x300857_g_Buff_Time - nTickCount* x300857_g_Time_Interval
--	TimerCommand( sceneId, selfId, 2, 7569, 1, x300857_g_ScriptId, nTime+1, nTime+60 );
--	--// ͬ��end

	local misIndex = GetQuestIndexByID( sceneId, selfId, nMyMissionId )
    local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

	if bCompleted>=1 then
		return
	end

	if country==0 then
		if sceneId==51 then
			if x300857_CheckPlayerInArea(sceneId, selfId)>0 then
				x300857_AddShoubianBonus(sceneId, selfId)
			end
		end
	end

	if country==1 then
		if sceneId==151 then
			if x300857_CheckPlayerInArea(sceneId, selfId)>0 then
				x300857_AddShoubianBonus(sceneId, selfId)
			end
		end
	end

	if country==2 then
		if sceneId==251 then
			if x300857_CheckPlayerInArea(sceneId, selfId)>0 then
				x300857_AddShoubianBonus(sceneId, selfId)
			end
		end
	end

	if country==3 then
		if sceneId==351 then
			if x300857_CheckPlayerInArea(sceneId, selfId)>0 then
				x300857_AddShoubianBonus(sceneId, selfId)
			end
		end
	end
end

--��Чʱ����
function x300857_OnActiveEvent( sceneId, selfId )
	local nMyMissionId = x300857_GetMissionId( sceneId, selfId )
--	TimerCommand( sceneId, selfId, 2, 7569, 1, x300857_g_ScriptId, x300857_g_Buff_Time+1, x300857_g_Buff_Time+60 );
--
--	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
--	SetQuestByIndex( sceneId, selfId, misIndex, x300857_g_TimerIndex, 0 )
end

--Ч����ɢʱ����
function x300857_OnFadeOutEvent( sceneId, selfId )

	local myMissionId = x300857_GetMissionId( sceneId, selfId )
	
	if IsHaveQuestNM(sceneId,selfId,myMissionId) <= 0 then
        return 
    end

--	TimerCommand( sceneId, selfId, 1, myMissionId, -1,-1,-1,-1 );
	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	CallScriptFunction(x300857_g_Shoubian_ScriptId,"QuestLogRefresh",sceneId, selfId, myMissionId)
end

function x300857_ProcEventEntry()
end

--------------------------------------------------
-- ����Ƿ���������
--------------------------------------------------
function x300857_CheckPlayerInArea(sceneId, selfId)
	local x,z =GetWorldPos(sceneId,selfId)

	if x>x300857_g_x1 and x<x300857_g_x2 and z>x300857_g_z1 and z<x300857_g_z2 then
		return 1;
	end

	return 0;
end


--------------------------------------------------
-- ð����
--------------------------------------------------
function x300857_AddShoubianBonus(sceneId, selfId)
	local level = GetLevel(sceneId, selfId)
	local nDayCount = CallScriptFunction(x300857_g_Shoubian_ScriptId,"GetDayCount",sceneId, selfId)
	if nDayCount == 0 then
		local exp1 = floor((level * 15000*0.15*0.3)/60)
		local exp2 = floor((level * 15000*0.15*0.3)/60)
		local exp = 0
		if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			exp = exp1;
		elseif GetLevel(sceneId, selfId) >=70 then
			exp = exp2;
		end 
		AddExp ( sceneId , selfId , exp )
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1 then
			AddExp ( sceneId , selfId , exp )
		end
	elseif nDayCount == 1 then
		local exp1 =floor((level * 15000*0.3*0.5)/60)
		local exp2 =floor((level * 15000*0.3*0.5)/60)
		local exp = 0
		if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			exp = exp1;
		elseif GetLevel(sceneId, selfId) >=70 then
			exp = exp2;
		end 
		AddExp ( sceneId , selfId , exp )
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1 then
			AddExp ( sceneId , selfId , exp )
		end
	elseif nDayCount == 2 then
		local exp1 = floor((level * 15000*0.5*0.7)/60)
		local exp2 = floor((level * 15000*0.5*0.7)/60)
		local exp = 0
		if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			exp = exp1;
		elseif GetLevel(sceneId, selfId) >=70 then
			exp = exp2;
		end 
		AddExp ( sceneId , selfId , exp )
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1 then
			AddExp ( sceneId , selfId , exp )
		end
	end
end

--// system
function x300857_ProcessQuestFail(sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300857_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2],DQ_SHOUBIAN_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2],DQ_SHOUBIAN_DAYCOUNT[3] );
	return daycount;



	

end
--// system end