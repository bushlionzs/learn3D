
--MisDescBegin
--�ű���
x800062_g_ScriptId = 800062

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800062_g_MissionName="��ʯ����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800062_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800062_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800062_g_ScriptId,x800062_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800062_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800062_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800062_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800062_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800062_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800062_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800062_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800062_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800062_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
