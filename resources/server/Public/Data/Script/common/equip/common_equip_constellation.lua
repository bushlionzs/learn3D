--װ������ű�

--MisDescBegin
--�ű���
x800117_g_ScriptId = 800117

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800117_g_MissionName="��������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800117_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800117_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800117_g_ScriptId,x800117_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800117_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800117_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800117_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800117_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800117_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800117_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800117_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800117_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800117_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
