--�������
--�������
--MisDescBegin
--�ű���
x800031_g_ScriptId = 800031

--��һ�������ID
--g_MissionIdPre =
x800031_g_GameId = 1055


--�����ı�����
x800031_g_MissionName="�������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800031_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������˼���ѧϰ����Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800031_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x800031_g_GameId) ~= 1 then
		return
	end
	

	if CallScriptFunction(888888,"IsCanHorseCompose",sceneId,selfId) == 0 then --�����Ѿ���������
		AddQuestNumText(sceneId,x800031_g_ScriptId,x800031_g_MissionName,3,3);
	else
		AddQuestNumText(sceneId,x800031_g_ScriptId,x800031_g_MissionName,3,2);
	end
end


--********************
--����������
--**********************************
function x800031_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800031_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800031_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800031_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800031_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800031_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800031_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800031_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800031_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
