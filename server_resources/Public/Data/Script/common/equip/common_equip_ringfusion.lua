x800065_g_ScriptId = 800065


--�����ı�����
x800065_g_MissionName="�ʼ���������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800065_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
end

--**********************************
--�о��¼�
--**********************************
function x800065_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800065_g_ScriptId,x800065_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800065_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800065_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800065_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800065_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800065_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800065_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800065_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800065_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800065_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
