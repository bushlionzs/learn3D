--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800020_g_ScriptId = 800020

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800020_g_MissionName="������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800020_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800020_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800020_g_ScriptId,x800020_g_MissionName);
end


--********************
--����������
--**********************************
function x800020_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800020_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800020_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800020_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800020_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800020_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800020_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800020_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800020_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
