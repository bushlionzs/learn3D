--װ������ű�

--MisDescBegin
--�ű���
x800102_g_ScriptId = 800102

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800102_g_MissionName="װ������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800102_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800102_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800102_g_ScriptId,x800102_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800102_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800102_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800102_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800102_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800102_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800102_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800102_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800102_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800102_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
