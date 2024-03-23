
x310370_g_ScriptId	= 310370
--x310370_g_BuffId					=	7708		
--x310370_g_Buff_Time					=	10*60	--��λ����
--x310370_g_Time_Interval				=	10		--��λ����


function x310370_FixedBuf(sceneId,selfId,bufId)

	--ȡ������BUF������
	local nImpactCount = GetImpactListCount(sceneId,selfId)
	if nImpactCount <=0 then
		return
	end
	
	--�����ҹ��ĵ�BUF����
	local nCollectCount = 0
	for i=0,nImpactCount-1 do
		
		if GetImpactDataIndex(sceneId,selfId,i) == bufId then
			nCollectCount = nCollectCount + 1
		end
	end
	
	--���BUF�����쳣 ִ���޸�����
	if nCollectCount > 1 then
		
		nCollectCount = nCollectCount -1
		
		for i = 1,nCollectCount do
			CancelSpecificImpact(sceneId,selfId,bufId)
		end
		
		WriteLog(1,format("BUFERROR:sceneId=%d,GUID=%X,level=%d,BufTotalCount=%d,BufCount=%d,BufId=%d",GetPlayerGUID(sceneId,selfId),sceneId,GetLevel(sceneId,selfId),nImpactCount,nCollectCount,bufId))
	end
end


--�������ʱ����
function x310370_OnIntervalOverEvent( sceneId, selfId )
	
	--��������
	x310370_FixedBuf(sceneId,selfId,7718)
	
	local day, week = GetWeek()
	if day == 0 or day == 6 then
		if sceneId==40 then
			x310370_AddBonus(sceneId, selfId)
		end
	end
	
	local msg = GetBattleSceneName(sceneId)
	if msg == "zhanchang_mshuangrenzhanchang/zhanchang_mshuangrenzhanchang.scn"  
		or msg == "zhanchang_kuafu2v2/zhanchang_kuafu2v2.scn" 
		or msg == "zhanchang_kuafu2v2_02/zhanchang_kuafu2v2_02.scn" 
		or msg == "zhanchang_kuafu2v2_03/zhanchang_kuafu2v2_03.scn"
		or msg == "zhanchang_kuafu2v2_04/zhanchang_kuafu2v2_04.scn" then
		if day == 1 or day == 4 then
			if GetMinOfDay() >= 1195 and GetMinOfDay() <= 1260 then	
				x310370_AddBonus1(sceneId, selfId)
			end
		elseif day == 0 then
			if GetMinOfDay() >= 775 and GetMinOfDay() <= 900 then	
				x310370_AddBonus1(sceneId, selfId)		
			end
		else 
			return
		end
	end
end

--��Чʱ����
function x310370_OnActiveEvent( sceneId, selfId )

end

--Ч����ɢʱ����
function x310370_OnFadeOutEvent( sceneId, selfId )

end

function x310370_ProcEventEntry()
end

--------------------------------------------------
-- ����Ƿ���������
--------------------------------------------------
function x310370_CheckPlayerInArea(sceneId, selfId)
	if sceneId ==40 then
		return 1;
	end

	return 0;
end


--------------------------------------------------
-- ð����
--------------------------------------------------
function x310370_AddBonus(sceneId, selfId)
		if GetWeek() ~= 0 and GetWeek() ~= 6 then
			return
		end
		if GetMinOfDay() < 540 or GetMinOfDay() >=1380 then	
			return
		end
				
		local exp = GetLevel( sceneId, selfId) * 135
		if IsHaveSpecificImpact( sceneId, selfId, 7510) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7511) == 1 then
			exp = GetLevel( sceneId, selfId) * 270;
		end	
		AddExp ( sceneId , selfId , exp )		
		Msg2Player(sceneId,selfId,"��������˼���԰����#R����"..exp.."��#cffcf00",8,2)
end

function x310370_AddBonus1(sceneId, selfId)
		if GetWeek() ~= 1 and GetWeek() ~= 4 and GetWeek() ~= 0 then
			return
		end
		if GetMinOfDay() < 540 or GetMinOfDay() >=1380 then	
			return
		end
				
		local exp = GetLevel( sceneId, selfId) * 135
		if IsHaveSpecificImpact( sceneId, selfId, 7510) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7511) == 1 then
			exp = GetLevel( sceneId, selfId) * 270;
		end	
		AddExp ( sceneId , selfId , exp )		
		Msg2Player(sceneId,selfId,"��ÿ��˫��ս������#R����"..exp.."��#cffcf00",8,2)
end
--// system
function x310370_ProcessQuestFail(sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x310370_GetDayCount(sceneId, selfId)

end
--// system end