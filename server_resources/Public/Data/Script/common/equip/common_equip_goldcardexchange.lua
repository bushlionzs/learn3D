--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800036_g_ScriptId = 800036

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800036_g_MissionName="�𿨶һ�����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800036_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800036_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800036_g_ScriptId,x800036_g_MissionName);
end


--********************
--����������
--**********************************
function x800036_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800036_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800036_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800036_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800036_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800036_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800036_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800036_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800036_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
