--�滻��ʯ
--���湦��
--MisDescBegin
--�ű���
x800058_g_ScriptId = 800058

--��һ�������ID
--g_MissionIdPre =


--�����ı�����
x800058_g_MissionName="��ʯ�滻"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800058_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800058_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800058_g_ScriptId,x800058_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800058_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800058_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800058_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800058_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800058_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800058_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800058_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800058_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800058_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
