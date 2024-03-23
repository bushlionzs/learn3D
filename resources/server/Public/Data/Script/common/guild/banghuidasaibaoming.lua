
--��ս����

--MisDescBegin
x300642_g_ScriptId          = 300642
x300642_g_Leader_Index      = 5
x300642_g_MissionName       ="������ս��"
--MisDescEnd

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x300642_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

    local pos = GetGuildOfficial(sceneId, selfId)
	if pos == x300642_g_Leader_Index and GetGuildBattleStatus(sceneId) == STATE_GUILD_BATTLE_SIGNUP then
        
        AddQuestNumText(sceneId,x300642_g_ScriptId,x300642_g_MissionName,3);

    end
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x300642_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
    
    --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
    
    --���Է�����
    --if GetTestServerToggle() == 0 then
    --    return
    --end

    --ս���Լ��Ŀ���
    if GetBattleSceneToggle( BATTLESCENE_TYPE_GUILDBATTLE ) == 0 then
        return
    end

    if idExt == 0 then
        
        --��ѯ���
        local nGuildId = GetGuildID( sceneId,selfId )
        QueryGuildBattleSignupState( sceneId,selfId,nGuildId,targetId )


    elseif idExt == 1 then

        
        local nGuildId = GetGuildID( sceneId,selfId )
        if nGuildId < 0 then
            return
        end
        
        --�Ƿ��ǰ���
        local pos = GetGuildOfficial(sceneId, selfId)
        if pos ~= x300642_g_Leader_Index then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "����ʧ�ܣ��ܱ�Ǹ���������ǰ����޷�������ս��");
            EndQuestEvent(sceneId)
            DispatchQuestEventList(sceneId,selfId,targetId)
            return
        end



        if GetGuildBattleStatus(sceneId) ~= STATE_GUILD_BATTLE_SIGNUP then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId, "���ս������ʱ��Ϊÿ�ܶ��������17��00~~18��30");
            EndQuestEvent(sceneId)
            DispatchQuestTips(sceneId,selfId)
            return
        end

        --���϶�ͨ������������
        SignupGuildBattle( sceneId,selfId,nGuildId,targetId )

    end
    return 1

end

function x300642_OnQueryBattleSignup( sceneId,selfId,result,targetId )


    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����û�п�ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��û�а�ᣡ");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�����ڵİ�ỹû�б�����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���ս��û�п�ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ڵİ���ڴ˴ΰ��ս���ֿգ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����İ����Ϣ���䲻��ȷ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ǰ�����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 8 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����İ���Ա����10�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 9 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���Ѿ���������İ�ս��������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 10 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����ս�����Ѵ����ޣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0
    end


    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "���Ƿ�Ҫ��������İ��ս��");
    AddQuestNumText(sceneId,x300642_g_ScriptId,"ȷ��..",3,1);
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,targetId)

    return 1

end

function x300642_OnBattleSignup( sceneId,selfId,result,targetId )
    
    if result == 1 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����û�п�ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 2 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ����û�а�ᣡ");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

    elseif result == 3 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ڵİ�ỹû�б�����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 4 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����ս��û�п�ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 5 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ڵİ���ڴ˴ΰ��ս���ֿգ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 6 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����İ����Ϣ���䲻��ȷ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 7 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�������ǰ�����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 8 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����İ���Ա����10�ˣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 9 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ���Ѿ���������İ�ս��������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0

    elseif result == 10 then
        
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�ܱ�Ǹ�����ս�����Ѵ����ޣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

        return 0
    end

    BeginQuestEvent(sceneId)
    AddQuestText(sceneId, "#G���������Ѿ���¼��#R20��#G��ʽ��ʼ��");
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)

    local str = "#G���������˰��ս��������׼����#R20��#G��ʽ��ʼ��"
    local nGuildID = GetGuildID(sceneId,selfId)
    LuaAllScenceM2Guild(sceneId, str, nGuildID, 2, 1)
    LuaAllScenceM2Guild(sceneId, str, nGuildID, 3, 1)

    return 1

end


----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x300642_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300642_ProcAccept( sceneId, selfId )

    

	--GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_BATTLE_SINGUP, x300642_g_ScriptId,-1,"OnReturn")
end

----------------------------------------------------------------------------------------------
--����Ƿ��Ѿ�����
----------------------------------------------------------------------------------------------
function x300642_OnReturn(sceneId, selfId,MissionData,MissionId,targetId)

--	if MissionData >= 0 then
-- 		BeginQuestEvent(sceneId)
--		AddQuestText(sceneId, "#G���������Ѿ���¼��#R20��#G��ʽ��ʼ��");
--		EndQuestEvent(sceneId)
--		DispatchQuestEventList(sceneId,selfId,targetId)
--	else
--
--		local guild = GetGuildID(sceneId, selfId)
--		SignupGuildBattle(sceneId,selfId,guild)       	--����
--
--		--���������
--		GetGuildQuestData(sceneId, selfId, GD_GUILD_INDEX_BATTL_SINGUP_RESULT, x300642_g_ScriptId,-1,"OnReturn2")
--
--  	end

end

----------------------------------------------------------------------------------------------
--������
----------------------------------------------------------------------------------------------
function x300642_OnReturn2(sceneId, selfId,MissionData,MissionId,targetId)

	if MissionData == 1 then    	--�����ɹ�
		local str = "#G���������˰��ս��������׼����#R20��#G��ʽ��ʼ��"
        local nGuildID = GetGuildID(sceneId,selfId)
        LuaAllScenceM2Guild(sceneId, str, nGuildID, 2, 1)
        LuaAllScenceM2Guild(sceneId, str, nGuildID, 3, 1)

        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�������˰��ս��������׼����20����ʽ��ʼ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)

	elseif MissionData == 0 then
  	 	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���İ�᲻����");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	elseif MissionData == -2 then
   	 	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���ս�������Ѵ����ޣ�");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	elseif MissionData == -3 then
   	 	BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���İ������̫�٣�����ʧ�ܡ�");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	elseif MissionData == -4 then
 		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���Ѿ���������");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	end

end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300642_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300642_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x300642_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x300642_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x300642_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x300642_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x300642_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
