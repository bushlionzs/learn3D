--װ������ű�

--MisDescBegin
--�ű���
x800004_g_ScriptId = 800004

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800004_g_MissionName="���ƻʼ�װ��"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800004_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800004_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800004_g_ScriptId,x800004_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800004_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800004_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800004_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800004_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800004_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800004_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800004_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800004_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800004_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
