
--MisDescBegin
--�ű���
x800063_g_ScriptId = 800063

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800063_g_MissionName="ϴʯ������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800063_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800063_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800063_g_ScriptId,x800063_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800063_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800063_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800063_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800063_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800063_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800063_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800063_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800063_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800063_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
