--װ������ű�

--MisDescBegin
--�ű���
x570045_g_ScriptId = 570045

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x570045_g_MissionName="װ��ת��"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570045_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x570045_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x570045_g_ScriptId,x570045_g_MissionName,3);
end


--********************
--����������
--**********************************
function x570045_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x570045_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x570045_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570045_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570045_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570045_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570045_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570045_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570045_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
