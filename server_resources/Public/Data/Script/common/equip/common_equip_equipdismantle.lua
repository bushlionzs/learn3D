--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800005_g_ScriptId = 800005 

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800005_g_MissionName="װ�����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800005_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800005_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800005_g_ScriptId,x800005_g_MissionName);
end


--********************
--����������
--**********************************
function x800005_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800005_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800005_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800005_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800005_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800005_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800005_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800005_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800005_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
