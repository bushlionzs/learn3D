x300940_g_ScriptId 					= 300940
x300940_g_MissionName				= "�����ҡ���������ս��Ԯ" 
x300940_g_Leader_Index              = 5

x300940_g_Laird_Signup                  	= 300     --����
x300940_g_Laird_WaitBattle              	= 301     --�����������ȴ�����ս��
x300940_g_Laird_BeginBattle             	= 302     --��ʼ����ս��
x300940_g_Laird_EndBattle               	= 303     --��������ս��
----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x300940_ProcEnumEvent( sceneId, selfId, targetId )

	local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
	if nBattleStatus ~= x300940_g_Laird_Signup then
		return
	end
	
	local bPlayerAid = CallScriptFunction(300918,"IsPlayerInPlayerAidList",sceneId,selfId)
	if bPlayerAid ~= 1 then
		return
	end
    
    --��ʾ��ť
    AddQuestNumText(sceneId,x300940_g_ScriptId,x300940_g_MissionName,3,x300940_g_ScriptId);
    
end

----------------------------------------------------------------------------------------------
--�¼����
----------------------------------------------------------------------------------------------
function x300940_ProcEventEntry(sceneId, selfId,targetId,scriptId,idExt )
	
	if idExt ==  x300940_g_ScriptId then
	
		local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
		if nBattleStatus ~= x300940_g_Laird_Signup then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ����#W#r\t�û�п�ʼ��");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
			return
		end
		
		
		local bPlayerAid = CallScriptFunction(300918,"IsPlayerInPlayerAidList",sceneId,selfId)
		if bPlayerAid ~= 1 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ����#W#r\t��������Ԯ��");
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId)
			return
		end
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ����#W#r\t����������Ԯ��ݡ���ȷ��Ҫ��ô����?");
		AddQuestNumText(sceneId,x300940_g_ScriptId,"ȷ��...",3);
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
		
	else
	
		local nBattleStatus = CallScriptFunction(300918,"GetBattleState",sceneId)
		if nBattleStatus ~= x300940_g_Laird_Signup then
			return
		end
		
		local bPlayerAid = CallScriptFunction(300918,"IsPlayerInPlayerAidList",sceneId,selfId)
		if bPlayerAid ~= 1 then
			return
		end
		
		--ִ�з�����Ԯ
		GameBattleLairdRequestCanclePlayerAidByPlayerAid(sceneId,selfId)
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "#Y�����ҡ�����ս����Ԯ����#W#r\t�����Ѿ��ɹ��ύ��");
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
		
		return 0
		
	end
	
	

end 

----------------------------------------------------------------------------------------------
--���ܼ��
----------------------------------------------------------------------------------------------
function x300940_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--����
--**********************************
function x300940_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x300940_ProcQuestAbandon( sceneId, selfId, MissionId )
end

--**********************************
--����
--**********************************
function x300940_OnContinue( sceneId, selfId, targetId )
end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300940_CheckSubmit( sceneId, selfId )
end

--**********************************
--�ύ
--**********************************
function x300940_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

--**********************************
--ɱ����������
--**********************************
function x300940_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

--**********************************
--���������¼�
--**********************************
function x300940_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300940_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end