
x303009_g_ScriptId          		= 303009
x303009_g_Leader_Index      		= 5
x303009_g_MissionName       		="�뿪ս��"
x303009_g_LeaveMessageFix      		="\t�����Ҫ�����뿪ս����?"

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x303009_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
  
  --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
  
	--����Գ���У��
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleSceneType",sceneId) < 0 then
		return
	end
	
	--������Ч�ĳ���
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"IsBattleSceneValid",sceneId) ~= 1 then
		return
	end
	
	--ˢ��BUF�б�
	AddQuestNumText(sceneId,x303009_g_ScriptId,x303009_g_MissionName,3,-1);
	
end

----------------------------------------------------------------------------------------------
--Ĭ���¼�
----------------------------------------------------------------------------------------------
function x303009_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	--�Ϸ�����
    if GetMergeDBToggle() == 1 then
        return
    end
  
  --�������ݿ⿪��
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end

	--����Գ���У��
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleSceneType",sceneId) < 0 then
		return
	end
	
	--������Ч�ĳ���
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"IsBattleSceneValid",sceneId) ~= 1 then
		return
	end
	
	
	if idExt == -1 then
		--�Ƿ����Ҫ�뿪ս��
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x303009_g_LeaveMessageFix);		
			AddQuestNumText(sceneId,x303009_g_ScriptId,"ȷ��...",3,x303009_g_ScriptId);		
	    EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	elseif idExt == x303009_g_ScriptId then
		
		CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"KickPlayer",sceneId,selfId) 
	end
end

----------------------------------------------------------------------------------------------
--����������
----------------------------------------------------------------------------------------------
function x303009_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303009_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303009_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x303009_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x303009_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x303009_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x303009_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x303009_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x303009_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
