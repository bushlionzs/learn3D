--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800001_g_ScriptId = 800001

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800001_g_MissionName="�������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800001_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800001_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800001_g_ScriptId,x800001_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800001_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800001_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800001_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800001_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800001_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800001_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800001_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800001_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800001_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
