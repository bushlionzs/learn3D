--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800002_g_ScriptId = 800002

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800002_g_MissionName="װ������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800002_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800002_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800002_g_ScriptId,x800002_g_MissionName);
end


--********************
--����������
--**********************************
function x800002_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800002_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800002_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800002_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800002_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800002_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800002_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800002_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800002_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
