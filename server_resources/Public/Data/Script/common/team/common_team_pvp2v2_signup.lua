
x303000_g_ScriptId          		= 303000
x303000_g_Leader_Index      		= 5
x303000_g_MissionName       		="��ս����˫��ս������"

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x303000_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--����Գ���У��
	if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 then
		return
	end

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end

    --ս���Լ��Ŀ���
    
    
    --ֻ���ڱ���ʱ����ڲſ���
    if CallScriptFunction(303001,"IsBattleSignup",sceneId) == 1 then
    	AddQuestNumText(sceneId,x303000_g_ScriptId,x303000_g_MissionName,3);
    end
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303000_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	--����Գ���У��
	if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350  then
		return
	end

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    if CallScriptFunction(303001,"IsBattleSignup",sceneId) ~= 1 then
    	BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "\t˫��ս��������û�п�ʼ��");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,targetId)
    	return
    end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���

    if idExt == 0 then
    	
    	--�Ƕӳ�
    	if IsTeamLeader(sceneId, selfId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\tֻ�жӳ���������μ�˫��ս����");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
    	--��û�п�ʼ
    	if CallScriptFunction(303001,"IsBattleSignup",sceneId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t˫��ս��������û�п�ʼ��");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
        
        --��ѯ���
        PVP2v2SignupState( sceneId,selfId ,targetId)


    elseif idExt == 1 then

        
        --�Ƕӳ�
    	if IsTeamLeader(sceneId, selfId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\tֻ�жӳ���������μ�˫��ս����");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
    	--��û�п�ʼ
    	if CallScriptFunction(303001,"IsBattleSignup",sceneId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t˫��ս��������û�п�ʼ��");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end

        --���϶�ͨ������������
        PVP2v2Signup( sceneId,selfId,targetId)
			
	end
    return 1

end

----------------------------------------------------------------------------------------------
--��ѯ�������
----------------------------------------------------------------------------------------------
function x303000_OnQuerySignupResult( sceneId,selfId,result,targetId )


    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ��˫��ս����û�п�ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t��û�ж��飡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�����ڶ�����������Ϊ2�˲��ܱ���˫��ս����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�����ڶ������ұ��붼���ߡ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���Ѿ��������ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���Ķ����Ѿ��������ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t��ε�˫��ս�������Ѿ����ˣ���Ⱥ��³�ս����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0
    elseif result == 8 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ�����ĵȼ�����60����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
    elseif result == 9 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ�����Ķ��ѵĵȼ�������60�����ϣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
    end


    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "\t���Ƿ�Ҫ�����μӡ�ս����˫��ս����");
    AddQuestNumText(sceneId,x303000_g_ScriptId,"ȷ��",3,1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1

end

----------------------------------------------------------------------------------------------
--�������
----------------------------------------------------------------------------------------------
function x303000_OnSignupResult( sceneId,selfId,result,targetId )
    
    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ��˫��ս����û�п�ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t��û�ж��飡");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�����ڶ�����������Ϊ2�˲��ܱ���˫��ս����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�����ڶ������ұ��붼���ߡ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���Ѿ��������ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t���Ķ����Ѿ��������ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t��ε�˫��ս�������Ѿ����ˣ���Ⱥ��³�ս����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0
    elseif result == 8 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ�����ĵȼ�����60����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
    elseif result == 9 then
    	
    	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ�����Ķ��ѵĵȼ�������60�����ϣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
		
    end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "\t#G���ɹ��������ˡ�ս����˫��ս������ȴ������Ŀ�ʼ��");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	
	local nTeamId = GetTeamId( sceneId,selfId)
	if nTeamId >= 0 then
		LuaAllScenceM2Team(sceneId,"���Ķ���˳��������ˡ�ս����˫��ս���ı�����",nTeamId,2,1)
		LuaAllScenceM2Team(sceneId,"���Ķ���˳��������ˡ�ս����˫��ս���ı�����",nTeamId,3,1)		
	end

    return 1

end


----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303000_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303000_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303000_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303000_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x303000_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x303000_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x303000_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x303000_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x303000_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
