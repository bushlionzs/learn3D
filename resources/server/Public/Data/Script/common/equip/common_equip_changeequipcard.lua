--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800017_g_ScriptId = 800017

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800017_g_MissionName="�齫����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800017_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800017_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800017_g_ScriptId,x800017_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800017_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800017_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800017_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800017_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800017_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800017_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800017_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800017_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800017_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
