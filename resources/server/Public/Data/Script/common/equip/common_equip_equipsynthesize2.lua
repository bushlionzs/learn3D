--װ������ű�

--MisDescBegin
--�ű���
x800052_g_ScriptId = 800052

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800052_g_MissionName="��ָ�������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800052_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800052_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800052_g_ScriptId,x800052_g_MissionName);
end


--********************
--����������
--**********************************
function x800052_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800052_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800052_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800052_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800052_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800052_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800052_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800052_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800052_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
