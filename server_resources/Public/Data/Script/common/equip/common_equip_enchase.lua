--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800028_g_ScriptId = 800028 

--��һ�������ID
--g_MissionIdPre =


--�����ı�����
x800028_g_MissionName="��ʯ��Ƕ"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800028_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800028_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800028_g_ScriptId,x800028_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800028_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800028_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800028_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800028_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800028_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800028_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800028_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800028_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800028_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
