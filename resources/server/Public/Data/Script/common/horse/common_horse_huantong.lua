--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800015_g_ScriptId = 800015

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800015_g_MissionName="��˻�ͯ"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800015_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������˻�ͯ����Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800015_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800015_g_ScriptId,x800015_g_MissionName);
end


--********************
--����������
--**********************************
function x800015_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800015_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800015_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800015_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800015_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800015_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800015_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800015_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800015_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
