x800119_g_ScriptId = 800119


--�����ı�����
x800119_g_MissionName="�ǳ�����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800119_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
end

--**********************************
--�о��¼�
--**********************************
function x800119_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800119_g_ScriptId,x800119_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800119_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800119_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800119_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800119_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800119_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800119_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800119_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800119_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800119_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
