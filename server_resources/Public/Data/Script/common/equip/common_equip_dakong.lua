--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800000_g_ScriptId = 800000

--��һ�������ID
--g_MissionIdPre =


--�����ı�����
x800000_g_MissionName="װ�����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800000_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800000_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800000_g_ScriptId,x800000_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800000_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800000_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800000_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800000_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800000_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800000_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800000_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800000_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800000_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
