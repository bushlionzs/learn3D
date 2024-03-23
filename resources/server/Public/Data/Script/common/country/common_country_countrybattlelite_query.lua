x310152_g_scriptId                      = 310152


----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x310152_ProcEnumEvent( sceneId, selfId, targetId, MissionId )


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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    if CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId) < 0 then
        return
    end
    
    AddQuestNumText(sceneId,x310152_g_scriptId,"������ս����ѯ",3);
        
end

----------------------------------------------------------------------------------------------
--ȡ�ù�������
----------------------------------------------------------------------------------------------
function x310152_GetCountryName( countryId )
    
    if countryId == 0 then
        return "¥������"
    elseif countryId == 1 then
        return "��ɽ����"
    elseif countryId == 2 then
        return "��������"
    elseif countryId == 3 then
        return "�ػ�����"
    end
    
end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x310152_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

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
    if GetBattleSceneToggle( BATTLESCENE_TYPE_COUNTRYBATTLELITE ) == 0 then
        return
    end
    
    local camp = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT, "GetCountryBattleLite_CountryCamp", sceneId, selfId)
    if camp < 0 then
        return
    end
    
    local match = CallScriptFunction( COUNTRY_BATTLE_LITE_SCRIPT,"GetCountryBattleLite_MatchCountry",sceneId ,selfId)
    if match < 0 then
        return
    end
    
    
    local strCountryName = x310152_GetCountryName( match )
    if strCountryName == nil then
        return
    end
    
    
    
    BeginQuestEvent(sceneId) 
    
    if camp == 0 then 
        local strMsg = format("#Y������ս����ѯ#r\t#G���������ڷ��ط�������Ҫ������������ǣ�#R%s",strCountryName )
        AddQuestText(sceneId, strMsg )
    else
        local strMsg = format("#Y������ս����ѯ#r\t#G���������ڽ����������ĵ����ǣ�#R%s",strCountryName )
        AddQuestText(sceneId, strMsg )
    end
    
    EndQuestEvent(sceneId)
    DispatchQuestEventList(sceneId,selfId,npcId)
    
end


function x310152_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310152_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310152_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310152_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x310152_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x310152_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x310152_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x310152_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x310152_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end