
--MisDescBegin
--�ű���
x800037_g_ScriptId = 800037

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800037_g_MissionName="װ������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800037_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800037_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800037_g_ScriptId,x800037_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800037_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800037_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800037_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800037_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800037_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800037_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800037_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800037_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800037_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
