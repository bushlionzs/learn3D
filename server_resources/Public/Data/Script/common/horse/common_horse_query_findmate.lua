--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800030_g_ScriptId = 800030

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800030_g_MissionName="��ѯ�������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800030_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	OpenFindHorseMating(sceneId, selfId, 1) --1: ��ѯ
end

--**********************************
--�о��¼�
--**********************************
function x800030_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800030_g_ScriptId,x800030_g_MissionName);
end


--********************
--����������
--**********************************
function x800030_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800030_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800030_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800030_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800030_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800030_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800030_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800030_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800030_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
