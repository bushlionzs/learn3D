--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800014_g_ScriptId = 800014

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800014_g_MissionName="��˽���"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800014_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800014_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800014_g_ScriptId,x800014_g_MissionName);
end


--********************
--����������
--**********************************
function x800014_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800014_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800014_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800014_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800014_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800014_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800014_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800014_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800014_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
