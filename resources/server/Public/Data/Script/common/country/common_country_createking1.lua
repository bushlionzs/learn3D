--���ܽű�
--����ļ��
--MisDescBegin
--�ű���
x300307_g_ScriptId = 300307

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x300307_g_MissionName="����ļ��"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300307_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

end

--**********************************
--�о��¼�
--**********************************
function x300307_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x300307_g_ScriptId,x300307_g_MissionName);
end


--********************
--����������
--**********************************
function x300307_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300307_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x300307_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300307_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300307_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300307_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300307_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300307_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300307_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
