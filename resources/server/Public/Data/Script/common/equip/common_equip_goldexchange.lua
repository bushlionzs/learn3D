--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800035_g_ScriptId = 800035

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800035_g_MissionName="��Ҷһ�����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800035_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800035_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800035_g_ScriptId,x800035_g_MissionName);
end


--********************
--����������
--**********************************
function x800035_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800035_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800035_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800035_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800035_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800035_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800035_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800035_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800035_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
