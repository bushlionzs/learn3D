--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800022_g_ScriptId = 800022

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800022_g_MissionName="�鿴���ҹ�����Ա"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800022_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800022_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800022_g_ScriptId,x800022_g_MissionName);
end


--********************
--����������
--**********************************
function x800022_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800022_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800022_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800022_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800022_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800022_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800022_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800022_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800022_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
