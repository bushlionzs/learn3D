--������

x301427_g_GrowpointId = 703 		--��Ӧ������ID

x301427_g_MissionList = {7537,7538,7539,7551,7552}
x301427_g_BuffList={7709,7710,7711,0}
x301427_g_PosX = 185
x301427_g_PosZ = 72 
function x301427_HaveAccepted(sceneId, selfId)

	for i, item in x301427_g_MissionList do
		if IsHaveQuestNM( sceneId, selfId, item ) > 0 then
			return 1
		end
	end
	return -1
end

function x301427_RandBuff(sceneId, selfId)
	local kindIndex = random(1, 100);
	if kindIndex >= 1 and kindIndex <= 40 then
		return x301427_g_BuffList[1]
	elseif kindIndex > 40 and kindIndex <= 80 then
		return x301427_g_BuffList[4]
	elseif kindIndex > 80 and kindIndex <= 90 then
		return x301427_g_BuffList[2]
	elseif kindIndex > 90 and kindIndex <= 100 then
		return x301427_g_BuffList[3]
	end
end


--���ɺ�����ʼ************************************************************************
function 	x301427_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301427_g_GrowpointId, sceneId, 0, -1)
	SetGrowPointObjID(sceneId,x301427_g_GrowpointId,x, y,ItemBoxId)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301427_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x301427_OnOpen")
    return x301427_OnOpenItemBox(sceneId, selfId, targetId, x301427_g_GrowpointId, -1)	
end
--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x301427_OnRecycle(sceneId,selfId,targetId)
	return   x301427_OnGuildRecycle( sceneId, selfId, targetId, x301427_g_GrowpointId, -1 )
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301427_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301427_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--�ɼ�����
--��ItemBox
function x301427_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	
	if x301427_HaveAccepted(sceneId, selfId) < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��û�������塿�������������עϵͳ���档")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return -31
	end
	    
	return 0
end

--����
function x301427_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
	
	local buff = x301427_RandBuff(sceneId, selfId)
	if buff == 0 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);
			if humanObjId ~= -1 then
				if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
					if x301427_HaveAccepted(sceneId, humanObjId) > 0 then
						SetPos(sceneId, humanObjId, x301427_g_PosX, x301427_g_PosZ)
					end
				end
			end
		end
		return 1
	end
	
	if buff == 7709 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);

			if humanObjId ~= -1 then
				if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
					if x301427_HaveAccepted(sceneId, humanObjId) > 0 then
						if IsHaveSpecificImpact( sceneId, humanObjId, 7710 ) > 0 then
							CancelSpecificImpact(sceneId, humanObjId,7710)
						end
						SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, buff, 0)
						BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "�����ƶ��ٶ�15��");
						EndQuestEvent();
						DispatchQuestTips(sceneId, humanObjId);
					end
				end
			end
		end
		return 1
	end

	if buff == 7710 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);

			if humanObjId ~= -1 then
				if humanObjId ~= selfId then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if x301427_HaveAccepted(sceneId, humanObjId) > 0 then
							if IsHaveSpecificImpact( sceneId, humanObjId, 7709 ) > 0 then
								CancelSpecificImpact(sceneId, humanObjId,7709)
							end
							SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, buff, 0)
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, "�����ƶ��ٶ�5��");
							EndQuestEvent();
							DispatchQuestTips(sceneId, humanObjId);
						end
					end
				else
					BeginQuestEvent(sceneId);
					AddQuestText(sceneId, "������˼��ٶ���");
					EndQuestEvent();
					DispatchQuestTips(sceneId, humanObjId);
				end
			end
		end
		return 1
	end
	
	if buff == 7711 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);

			if humanObjId ~= -1 then
				if humanObjId ~= selfId then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if x301427_HaveAccepted(sceneId, humanObjId) > 0 then
							if IsHaveSpecificImpact( sceneId, humanObjId, buff ) > 0 then
								CancelSpecificImpact(sceneId, humanObjId,buff)
							end
							SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, buff, 1000)
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, "ѣ��2��");
							EndQuestEvent();
							DispatchQuestTips(sceneId, humanObjId);
						end
					end
				else
					BeginQuestEvent(sceneId);
					AddQuestText(sceneId, "�������ѣ�ζ���");
					EndQuestEvent();
					DispatchQuestTips(sceneId, humanObjId);
				end
			end
		end
		return 1
	end
	return 0
end