--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800027_g_ScriptId = 800027

--��һ�������ID
--g_MissionIdPre =


--�����ı�����
x800027_g_MissionName="װ������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800027_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800027_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800027_g_ScriptId,x800027_g_MissionName);
end


--********************
--����������
--**********************************
function x800027_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800027_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800027_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800027_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800027_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800027_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800027_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800027_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800027_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
