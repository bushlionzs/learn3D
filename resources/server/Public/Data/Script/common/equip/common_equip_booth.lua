--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800003_g_ScriptId = 800003 

--��һ�������ID
--g_MissionIdPre =


--�����ı�����
x800003_g_MissionName="�̵�����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800003_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800003_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800003_g_ScriptId,x800003_g_MissionName);
end


--********************
--����������
--**********************************
function x800003_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800003_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800003_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800003_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800003_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800003_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800003_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800003_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800003_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
