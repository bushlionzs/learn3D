--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800047_g_ScriptId = 800047

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800047_g_MissionName="װ������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800047_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800047_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800047_g_ScriptId,x800047_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800047_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800047_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800047_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800047_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800047_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800047_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800047_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800047_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800047_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
