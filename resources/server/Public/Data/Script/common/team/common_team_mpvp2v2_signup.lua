--##########################################
--##��� 2v2 ս�������ű� by rj 2010-9-24 ##
--##########################################

x303100_g_ScriptId          		= 303100
x303100_g_MissionName       		="�����ս����˫��ս������"
x303100_g_BackSceneIdAry		    = {0, 0, 0, 0}								--�Ĺ��ӱ������������ѹ�����ǩ֤ʱ���˻س��� id
x303100_g_BackPosAry		     	= {{168, 68}, {168, 68}, {168, 68}, {168, 68}}		--�Ĺ��ӱ������������ѹ�����ǩ֤ʱ���˻س�������
x303100_g_curSignupTypeTbl 			= {}												--��ǰ��ұ���˫��ս�����ͱ�

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x303100_ProcEnumEvent(sceneId, selfId, targetId, missionId)

	--�����Ǳ�������
	if GetSceneType(sceneId) ~= 8 then
		return
	end
		
	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
  	--�������ݿ⿪��
	if GetUpdateDBBeforeToggle() == 1 then
		return
	end
    
    --ֻ���ڱ���ʱ����ڲſ���
    if CallScriptFunction(MPVP2V2_BATTLE_SCRIPT, "IsBattleSignup", sceneId) == 1 then
    	AddQuestNumText(sceneId, x303100_g_ScriptId, x303100_g_MissionName, 3)
    else
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���ڲ��ڿ��ս������ʱ����ڣ��޷�������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
    end
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303100_ProcEventEntry(sceneId, selfId, targetId, scriptId, idExt)

	--�����Ǳ�������
	if GetSceneType(sceneId) ~= 8 then
		return
	end

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
  	--�������ݿ⿪��
	if GetUpdateDBBeforeToggle() == 1 then
		return
	end
    
    --��û�п�ʼ
    if CallScriptFunction(MPVP2V2_BATTLE_SCRIPT, "IsBattleSignup", sceneId) ~= 1 then
    	BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "\t���˫��ս��������û�п�ʼ��");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId, selfId, targetId)
    	return
    end
    
  	--�Ƕӳ�
	if IsTeamLeader(sceneId, selfId) ~= 1 then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "\tֻ�жӳ���������μӿ��˫��ս����");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId, selfId, targetId)
        return
	end
    	    
    if idExt == 0 then
       
        --��ѯ���
        MPVP2v2SignupState(sceneId, selfId ,targetId)
    elseif idExt == 1 then
    
        --���϶�ͨ������������
       	MPVP2v2Signup(sceneId, selfId, targetId)
	end
	
    return 1
end

----------------------------------------------------------------------------------------------
--��ѯ�������
----------------------------------------------------------------------------------------------
function x303100_OnMQuerySignupResult(sceneId, selfId, result, targetId)

    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ��˫��ս����û�п�ʼ��")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t��û�ж��飡")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�����ڶ�����������Ϊ2�˲��ܱ���˫��ս����")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 4 then --�������Ѿ���Ч��Ŀǰ����ʱ��ɨ�����Χ���߶���
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�����ڶ������ұ��붼���ߡ�")
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���Ѿ��������ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���Ķ����Ѿ��������ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t��ε�˫��ս�������Ѿ����ˣ���Ⱥ��³�ս����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 8 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ�����ĵȼ�����40����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
    elseif result == 9 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ�����Ķ��ѵĵȼ�������40�����ϣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0		
    elseif result == 10 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t����Χ�����߶���������2�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
    end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "\t���Ƿ�Ҫ�����μӡ�ս����˫��ս����");
    AddQuestNumText(sceneId, x303100_g_ScriptId, "ȷ��", 3, 1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId, selfId, targetId)
    return 1
end

----------------------------------------------------------------------------------------------
--�������
----------------------------------------------------------------------------------------------
function x303100_OnMSignupResult(sceneId, selfId, result, targetId)
    
    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ��˫��ս����û�п�ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t��û�ж��飡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�����ڶ�����������Ϊ2�˲��ܱ���˫��ս����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 4 then --�������Ѿ���Ч��Ŀǰ����ʱ��ɨ�����Χ���߶���
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�����ڶ������ұ��붼���ߡ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���Ѿ��������ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���Ķ����Ѿ��������ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t��ε�˫��ս�������Ѿ����ˣ���Ⱥ��³�ս����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
        return 0
    elseif result == 8 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ�����ĵȼ�����40����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
    elseif result == 9 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ�����Ķ��ѵĵȼ�������40�����ϣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
		
 	elseif result == 10 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t����Χ�����߶���������2�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId, selfId, targetId)
		return 0
    end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "\t#G���ɹ��������ˡ�ս����˫��ս������ȴ������Ŀ�ʼ,#R�����뿪������#G�������޷����յ�����ս�������룡");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId, selfId, targetId)
	
	--�����������ϵĶ���ȫ��ȡ������ǩ֤�������ȡ���������ǲ����Լ���
	local sceneMemberNum = GetTeamSceneMemberCount(sceneId, selfId)
	for i = 0, sceneMemberNum - 1 do
		local memberId = GetTeamSceneMember(sceneId, selfId, i)
		SetQuestData(sceneId, memberId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 0)
		x303100_g_curSignupTypeTbl[GetPlayerGUID(sceneId, memberId)] = 1
        
        --ʹ�� Msg2Player ���ƣ�ԭ���� LuaAllScenceM2Team ��ʹ�� SendPacket_SingleMode �޷�֧�ֿ���� GL ģʽ
        Msg2Player(sceneId, memberId, "���Ķ���˳��������ˡ����ս����˫��ս���ı���,#R�����뿪������#G�������޷����յ�����ս�������룡", 8, 2)
        Msg2Player(sceneId, memberId, "���Ķ���˳��������ˡ����ս����˫��ս���ı���,#R�����뿪������#G�������޷����յ�����ս�������룡", 8, 3)
		WriteLog(1, format("MP2BL:x303100_OnMSignupResult 1 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, memberId)))
	end
	
	--��Ҫ�����Լ�
	SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 0)
	x303100_g_curSignupTypeTbl[GetPlayerGUID(sceneId, selfId)] = 1
    Msg2Player(sceneId, selfId, "���Ķ���˳��������ˡ����ս����˫��ս���ı���,#R�����뿪������#G�������޷����յ�����ս�������룡", 8, 2)
    Msg2Player(sceneId, selfId, "���Ķ���˳��������ˡ����ս����˫��ս���ı���,#R�����뿪������#G�������޷����յ�����ս�������룡", 8, 3)
	WriteLog(1, format("MP2BL:x303100_OnMSignupResult 2 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, selfId)))
		
    return 1
end

---------------------------------------------------------------------------------------------------
--�������м�¼��2v2�����߱���ǩ֤��������μ�¼��
---------------------------------------------------------------------------------------------------
function x303100_Set2V2SignAndClean(sceneId)

	--�����ս����ʼ�������������ϵ�����������ǩ֤��ʹ�䲻�����Ҫ������
	local humanCount = GetScenePlayerCount(sceneId)	
	for	i = 0, humanCount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i)

		--�����б���˫��ս������ң�������û��ȥ�ģ��������ǩ֤�������ж���˫��ս���Ϳ��Ա����ͬ�����ı���6��ս���ķֿ���
		if x303100_g_curSignupTypeTbl[GetPlayerGUID(sceneId, humanId)] == 1 then
			if GetQuestData(sceneId, humanId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3]) == 0 then
				SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
				SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], MBATTLE_SIGNUP_SIGNTIME)
				WriteLog(1, format("MP2BL:x303100_Set2V2SignAndClean 1 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, humanId)))	
			end
		end  
	end

	--����Ҫ��ÿ�θ����м�¼���е�������ǩ֤��Ҫ����ñ�����ÿ�ο�����������һЩ�����Ĳ������õ��û�ǩ֤
	x303100_g_curSignupTypeTbl = {}
end

---------------------------------------------------------------------------------------------------
--��ҽ��뱨������ʱ�Ĵ���
---------------------------------------------------------------------------------------------------
function x303100_ProcMapPlayerNewConnectEnter(sceneId, selfId)

	--�����������
	if GetSceneType(sceneId) ~= 8 then
		return
	end
	
	local signState = GetQuestData(sceneId, selfId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3])
	local selfCountry = GetCurCountry(sceneId, selfId)
	
	--����������������
	if signState == 0 then
	
		--�Ѿ�������ϴα����ĳ��Σ�����ʱ���ߡ�Ҫ����������
	 	if MPVP2v2IsSignup(sceneId, selfId) == 0 then
			SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3], 1)
			SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], 10)
			WriteLog(1, format("MP2BL:x303100_ProcMapPlayerNewConnectEnter 1 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, selfId)))	
	 	end
	 	return
	end

	--û��������������
	
	local lastLogoutTime = GetLastLogoutTime(sceneId, selfId)
	local thisInterval = GetCurrentTime() - lastLogoutTime
	local signTime = GetQuestData(sceneId, selfId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3])

	--ʱ���ݴ��ж�����ֹ����ʱ��ǰ�޸����ڵ��µ� thisInterval Ϊ�������
	if thisInterval > 0 then
		
		--������ߵ�ʱ����ڱ���ǩ֤ʱ�����û����͵���Ӧ���Ǭ�������������ת���ͻ��˻�ҳ UI ���޷�������ʹ�ö�ʱ��������ʱ 10 ��
		if thisInterval > signTime then
			SetQuestData(sceneId, selfId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], 10)
			WriteLog(1, format("MP2BL:x303100_ProcMapPlayerNewConnectEnter 2 SceneId=%d PlayerGUID=%u Param1=%u Param2=%u", 
				sceneId, GetGUID(sceneId, selfId), thisInterval, signTime))
		end
	else
		WriteLog(2, format("MP2BL:x303100_ProcMapPlayerNewConnectEnter: get this thisInterval error for modify system time"))    		
	end
end

---------------------------------------------------------------------------------------------------
--����������ʱ��
---------------------------------------------------------------------------------------------------
function x303100_ProcTiming(sceneId, nowTime)

	local humanCount = GetScenePlayerCount(sceneId)	
	for	i = 0, humanCount - 1 do
		
		local humanId = GetScenePlayerObjId(sceneId, i)
		local signState = GetQuestData(sceneId, humanId, MD_MBATTLE_SIGNSTATE[1], MD_MBATTLE_SIGNSTATE[2], MD_MBATTLE_SIGNSTATE[3])
		local isBack = 0		
	 	
	 	--����ǩ֤״̬��û�н��й���������ҽ���ǩ֤��ʱ���ų��������뿪�����ֻ�������ң�
		if signState == 1 and MPVP2v2IsSignup(sceneId, humanId) == 0 then

			--����б���ǩ֤�����ʱ���ݼ��������ж��Ƿ�Ϊ 0�������ڵ���ʱʱ�û����ߣ��ٴ����߾���ѭ���� 1024 ����
			local signTime = GetQuestData(sceneId, humanId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3])
			if signTime ~= 0 then
				SetQuestData(sceneId, humanId, MD_MBATTLE_SIGNTIME[1], MD_MBATTLE_SIGNTIME[2], MD_MBATTLE_SIGNTIME[3], signTime - 1)
				
				--��ʱ����
				if signTime > 0 and signTime <= 10 then
					Msg2Player(sceneId, humanId, format("��������ʱ��û�б�������%d����뿪����������", signTime), 8, 3)
				end
				
				--�ݼ�ʱ�䵽Ҫ����
				if signTime - 1 == 0 then
					isBack = 1
				end		
			end	
		end

		if isBack == 1 then
			local humanCountry = GetCurCountry(sceneId, humanId)
			NewWorld
				(
				sceneId, 
				humanId, 
				x303100_g_BackSceneIdAry[humanCountry + 1], 
				x303100_g_BackPosAry[humanCountry + 1][1],
				x303100_g_BackPosAry[humanCountry + 1][2], 
		 		x303100_g_ScriptId
		 		)
			WriteLog(1, format("MP2BL:x303100_ProcTiming 1 SceneId=%d PlayerGUID=%u", sceneId, GetGUID(sceneId, humanId)))
		 end
	end
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303100_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end
----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303100_ProcAccept( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303100_ProcQuestAbandon( sceneId, selfId, missionId )
end
----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303100_OnContinue( sceneId, selfId, targetId )
end
----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x303100_CheckSubmit( sceneId, selfId )
end
----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x303100_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, missionId )
end
----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x303100_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, missionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x303100_ProcAreaEntered( sceneId, selfId, zoneId, missionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x303100_ProcQuestItemChanged( sceneId, selfId, itemdataId, missionId )
end
