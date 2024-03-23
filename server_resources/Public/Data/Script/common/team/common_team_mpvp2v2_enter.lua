--##############################################
--##��� 2v2 ���뱨�������ű� by rj 2010-9-24 ##
--##############################################

x303102_g_ScriptId          		= 303102
x303102_g_MissionName       		= "��˫��ս�������뱨������"
x303102_g_MMapServerId       		= 7															--��� MapServer id
x303102_g_MinLevelLimit       		= 40															--��С��������
x303102_g_MaxEnterLimit       		= 2000															--��� MapServer ����������
x303102_g_SignupSceneIdAry		    = {519, 530, 531, 532}												--�Ĺ�˫��ս���������� id
x303102_g_EnterPosAry		     	= {																--�Ĺ�˫��ս����������
[1] = {{54, 52}, {204, 53}, {205, 203}, {55, 203}, {130, 128}},
[2] = {{54, 52}, {204, 53}, {205, 203}, {55, 203}, {130, 128}},
[3] = {{54, 52}, {204, 53}, {205, 203}, {55, 203}, {130, 128}},
[4] = {{54, 52}, {204, 53}, {205, 203}, {55, 203}, {130, 128}},
}	
x303102_g_GameId = 1061
----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x303102_ProcEnumEvent(sceneId, selfId, targetId, missionId)

    AddQuestNumText(sceneId, x303102_g_ScriptId, x303102_g_MissionName, 3)
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303102_ProcEventEntry(sceneId, selfId, targetId, scriptId, idExt)

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
  	--�������ݿ⿪��
	if GetUpdateDBBeforeToggle() == 1 then
		return
	end
        
   	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, "#Y��˫��ս����#W\n\t�������ȺӢ���͡�Ӣ���Ƽ��ĵط�����ȷ��Ҫ������")
 	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x303102_g_ScriptId, -1)
    return
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303102_ProcAcceptCheck(sceneId, selfId, npcId)
	--�ж��淨����
	if GetGameOpenById(x303102_g_GameId) ~= 1 then
		Msg2Player(sceneId,selfId,"�û�п����������ڴ���",8, 3)	
		return
	end
	--�Ƿ���ʱ��
	if GetWeek() == 1 or GetWeek() == 4 then
		if GetMinOfDay() < 1195 or GetMinOfDay() >= 1260 then	
			Msg2Player(sceneId, selfId, "���˫��ս��������û�п�ʼ��", 8, 3)		
			return
		end	
	elseif GetWeek() == 0 then
		if GetMinOfDay() < 775 or GetMinOfDay() >= 900 then	
			Msg2Player(sceneId, selfId, "���˫��ս��������û�п�ʼ��", 8, 3)		
			return
		end
	else 
		Msg2Player(sceneId, selfId, "���˫��ս��������û�п�ʼ��", 8, 3)		
		return
	end
	
  	--�����ж���
	if HasTeam(sceneId, selfId) ~= 1 then
		Msg2Player(sceneId, selfId, "�����ж����������μӿ��˫��ս����", 8, 3)
        return
	end
	
  	--�Ƕӳ�
	if IsTeamLeader(sceneId, selfId) ~= 1 then
		Msg2Player(sceneId, selfId, "ֻ�жӳ���������μӿ��˫��ս����", 8, 3)
        return
	end
	
	--������������Ϊ 2
	if GetTeamSize(sceneId, selfId) ~= 2 then
		Msg2Player(sceneId, selfId, "ֻ�����˵Ķ���������룡", 8, 3)
      return
	end
	
	local nearCount = GetNearTeamCount(sceneId, selfId)
	
	--������Ա������Ϊ 2
	if nearCount ~= 2 then
		Msg2Player(sceneId, selfId, "�����������������ˣ�", 8, 3)
        return
	end
	
	for i = 0, nearCount - 1 do

		local memberId = GetNearTeamMember(sceneId, selfId, i)
		
		local ret, msg = x303102_EnterSignupSceneCheck(sceneId, memberId)
       	if ret == 0 then
       		Msg2Player(sceneId, selfId, msg, 8, 3)
		 	WriteLog(1, format("MP2BL:x303102_ProcAcceptCheck 1 SceneId=%d PlayerGUID=%u Param1=%u Param2=%u Param3=%s", 
		 		sceneId, GetGUID(sceneId, selfId), GetGUID(sceneId, memberId), npcId, msg))
       		return
       	end
    end
	
	--�����ս�������������Ƿ񳬹�����
	local userNum = GetMapServerCurUserNum(x303102_g_MMapServerId)
	if userNum + 2 > x303102_g_MaxEnterLimit then
    	Msg2Player(sceneId, selfId, "���ս���������������������Ժ���룡", 8, 3)
	 	WriteLog(1, format("MP2BL:x303102_ProcAcceptCheck 2 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, selfId)))
   	 	return       
   	end 
	
	local rand = random(1, 5)
		
	for i = 0, nearCount - 1 do
		
		local memberId = GetNearTeamMember(sceneId, selfId, i)
		
		--��������ǩ֤����¼ǩ֤ʱ��
		SetQuestData(sceneId, memberId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
		SetQuestData(sceneId, memberId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], MBATTLE_SIGNUP_SIGNTIME)
		
		local nPlayerLevel = GetLevel(sceneId, memberId)
		
		if nPlayerLevel >= 65 and nPlayerLevel < 85 then
			SendSpecificImpactToUnit(sceneId, memberId, memberId, memberId, 7717, 0)
		elseif nPlayerLevel >= 85 then
			SendSpecificImpactToUnit(sceneId, memberId, memberId, memberId, 7718, 0)
			DispelSpecificImpact(sceneId, memberId, 7717, 1)
		end
		
		--���ݲ�ͬ���ҵ��򵽲�ͬ�ı�����ͼ
		local memberCountry = GetCurCountry(sceneId, memberId)
		NewWorld
			(
			sceneId, 
			memberId, 
			x303102_g_SignupSceneIdAry[memberCountry + 1], 
			x303102_g_EnterPosAry[memberCountry + 1][rand][1],
			x303102_g_EnterPosAry[memberCountry + 1][rand][2], 
	 		x303102_g_ScriptId
	 		)

	 	WriteLog(1, format("MP2BL:x303102_ProcAcceptCheck 3 SceneId=%d PlayerGUID=%u Param1=%d", 
	 		sceneId, GetGUID(sceneId, memberId), x303102_g_SignupSceneIdAry[memberCountry + 1]))	
	end
end

function x303102_EnterSignupSceneCheck(sceneId, selfId)

	if GetLevel(sceneId, selfId) < x303102_g_MinLevelLimit then
		return 0, format("�������г�Աû�дﵽ%d�������ܽ��뱨������", x303102_g_MinLevelLimit)
	end

	if GetPKMode(sceneId, selfId) ~= 0 then
    	return 0, "�������г�Ա����PKģʽ�£����ܽ��뱨������" 
   	end 

	if GetBusId(sceneId, selfId) ~= -1 then
		return 0, "�������г�Ա���ڻ���״̬�����ܽ��뱨������"
	end
    
    if IsHideName(sceneId, selfId) > 0 then
    	return 0, "�������г�Ա��������״̬��,���ܽ��뱨������"
    end
    
    if sceneId == PK_PUNISH_PRISON_SCENE_ID then
    	return 0,"�������г�Ա�ڼ�������ܽ��뱨������"
    end

    if IsHaveSpecificImpact(sceneId, selfId, 7536) ~= 0 then
        return 0, "�������г�Ա���ڱ�������ս�ڼ䣬���ܽ��뱨������"
    end

    if IsHaveSpecificImpact(sceneId, selfId, 7537) ~= 0 then
        return 0, "�������г�Ա���ڱ�������ս�ڼ䣬���ܽ��뱨������"
    end
    
    if IsHaveSpecificImpact(sceneId, selfId, 7702) ~= 0 then
        return 0, "�������г�Ա���ڶ���״̬�£����ܽ��뱨������"
    end

    if IsPlayerStateNormal(sceneId, selfId) == 0 then
        return 0, "�������г�Ա״̬�쳣�����ܽ��뱨������"
    end
    
    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_TONGQUBUFF) == 1 then
        return 0, "�������г�Ա����ͯȤ����״̬�����ܽ��뱨������"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_TIESAN) == 1 then
        return 0, "�������г�Ա���������������״̬�����ܽ��뱨������"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_MENTALGAME) == 1 then
        return 0, "�������г�Ա���ڴ���״̬�����ܽ��뱨������"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_STALL) == 1 then
        return 0, "�������г�Ա���ڰ�̯״̬�����ܽ��뱨������"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_DIE) == 1 then
        return 0, "�������г�Ա��������״̬�����ܽ��뱨������"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_CRASHBOX) == 1 then
        return 0, "�������г�Ա��������״̬�����ܽ��뱨������"
    end

    if IsPlayerMutexState(sceneId,selfId,PLAYER_STATE_AUTOPLAY) == 1 then
        return 0, "�������г�Ա���ڹһ�״̬�����ܽ��뱨������"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_SUBTRAIN) == 1 then
        return 0, "�������г�Ա���ڴ���״̬�����ܽ��뱨������"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_BUS) == 1 then
        return 0, "�������г�Ա����BUS״̬�����ܽ��뱨������"
    end

    if IsPlayerMutexState(sceneId, selfId, PLAYER_STATE_PKMODE) == 1 then
        return 0, "�������г�ԱPKֵ���߻��ڿ�ģʽ�����ܽ��뱨������"
    end

    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303102_ProcAccept( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303102_ProcQuestAbandon( sceneId, selfId, missionId )
end
----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303102_OnContinue( sceneId, selfId, targetId )
end
----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x303102_CheckSubmit( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x303102_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, missionId )
end
----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x303102_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, missionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x303102_ProcAreaEntered( sceneId, selfId, zoneId, missionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x303102_ProcQuestItemChanged( sceneId, selfId, itemdataId, missionId )
end
