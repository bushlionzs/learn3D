--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800038_g_ScriptId = 800038 

--��һ�������ID
--g_MissionIdPre =


--�����ı�����
x800038_g_MissionName="������ñ���"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800038_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800038_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800038_g_ScriptId,x800038_g_MissionName);
end


--********************
--����������
--**********************************
function x800038_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800038_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800038_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800038_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800038_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800038_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800038_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800038_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800038_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
