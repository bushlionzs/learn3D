--װ������ű�

--MisDescBegin
--�ű���
x800115_g_ScriptId = 800115

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800115_g_MissionName="��ɫװ������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800115_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800115_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800115_g_ScriptId,x800115_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800115_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800115_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800115_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800115_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800115_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800115_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800115_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800115_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800115_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
