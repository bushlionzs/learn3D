
--MisDescBegin
--�ű���
x800064_g_ScriptId = 800064

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800064_g_MissionName="��ʯ��ж"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800064_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800064_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800064_g_ScriptId,x800064_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800064_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800064_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800064_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800064_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800064_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800064_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800064_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800064_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800064_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
