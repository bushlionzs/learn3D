
--MisDescBegin
--�ű���
x800059_g_ScriptId = 800059

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800059_g_MissionName="װ���̽�ϴ�ϣ�"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800059_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800059_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800059_g_ScriptId,x800059_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800059_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800059_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800059_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800059_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800059_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800059_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800059_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800059_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800059_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
