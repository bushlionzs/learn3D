--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800113_g_ScriptId = 800113

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800113_g_MissionName="ʱװ����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800113_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800113_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800113_g_ScriptId,x800113_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800113_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800113_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800113_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800113_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800113_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800113_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800113_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800113_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800113_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
