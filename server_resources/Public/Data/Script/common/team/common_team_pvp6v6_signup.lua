
x303005_g_ScriptId          		= 303005
x303005_g_Leader_Index      		= 5
x303005_g_MissionName       		="��ս��������ս������"

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x303005_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

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
    if CallScriptFunction(303006,"IsBattleSignup",sceneId) == 1 then
    	AddQuestNumText(sceneId,x303005_g_ScriptId,x303005_g_MissionName,3);
    end
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303005_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

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
    
    if CallScriptFunction(303006,"IsBattleSignup",sceneId) ~= 1 then
    	BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "\t��ս��������ս��������û�п�ʼ��");
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
    	if HasTeam(sceneId,selfId) == 1 and IsTeamLeader(sceneId, selfId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t����ģʽ��,ֻ�жӳ���������μӡ�ս��������ս����");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
    	--��û�п�ʼ
    	if CallScriptFunction(303006,"IsBattleSignup",sceneId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t��ս��������ս��������û�п�ʼ��");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
        
        --��ѯ���
        PVP6v6SignupState( sceneId,selfId ,targetId)


    elseif idExt == 1 then

        
        --�Ƕӳ�
    	if HasTeam(sceneId,selfId) == 1 and IsTeamLeader(sceneId, selfId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t����ģʽ��,ֻ�жӳ���������μӡ�ս��������ս����");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end
    	
    	--��û�п�ʼ
    	if CallScriptFunction(303006,"IsBattleSignup",sceneId) ~= 1 then
    		BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "\t��ս��������ս��������û�п�ʼ��");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
    	end

        --���϶�ͨ������������
        PVP6v6Signup( sceneId,selfId,targetId)
			
	end
    return 1

end

----------------------------------------------------------------------------------------------
--��ѯ�������
----------------------------------------------------------------------------------------------
function x303005_OnQuerySignupResult( sceneId,selfId,result,targetId )


    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ����ս��������ս����û�п�ʼ��");
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
		AddQuestText(sceneId, "\t����ģʽ��,�����ڶ�����������Ϊ3�����ϲ��ܱ�����ս��������ս����");
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
		AddQuestText(sceneId, "\t��εġ�ս��������ս�������Ѿ����ˣ���Ⱥ��³�ս����");
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
    AddQuestText(sceneId, "\t���Ƿ�Ҫ�����μӡ�ս��������ս����");
    AddQuestNumText(sceneId,x303005_g_ScriptId,"ȷ��",3,1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1

end

----------------------------------------------------------------------------------------------
--�������
----------------------------------------------------------------------------------------------
function x303005_OnSignupResult( sceneId,selfId,result,targetId )
    
    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "\t�ܱ�Ǹ����ս��������ս����û�п�ʼ��");
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
		AddQuestText(sceneId, "\t����ģʽ��,�����ڶ�����������Ϊ3�����ϲ��ܱ�����ս��������ս����");
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
		AddQuestText(sceneId, "\t��εġ�ս��������ս�������Ѿ����ˣ���Ⱥ��³�ս����");
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
    AddQuestText(sceneId, "\t#G���ɹ��������ˡ�ս��������ս������ȴ������Ŀ�ʼ��");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	
	local nTeamId = GetTeamId( sceneId,selfId)
	if nTeamId >= 0 then
		LuaAllScenceM2Team(sceneId,"���Ķ���˳��������ˡ�ս��������ս���ı�����",nTeamId,2,1)
		LuaAllScenceM2Team(sceneId,"���Ķ���˳��������ˡ�ս��������ս���ı�����",nTeamId,3,1)		
	else
	
		local name = GetName(sceneId,selfId)
		LuaScenceM2Player(sceneId,selfId,"��˳��������ˡ�ս��������ս���ı�����",name,2,1)
		LuaScenceM2Player(sceneId,selfId,"��˳��������ˡ�ս��������ս���ı�����",name,3,1)		
	end

    return 1

end


----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303005_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303005_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303005_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303005_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x303005_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x303005_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x303005_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x303005_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x303005_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
