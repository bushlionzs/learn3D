
--MisDescBegin
--�ű���
x800060_g_ScriptId = 800060

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800060_g_MissionName="װ����¯��ϴ�ϣ�"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800060_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800060_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800060_g_ScriptId,x800060_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800060_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800060_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800060_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800060_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800060_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800060_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800060_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800060_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800060_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
