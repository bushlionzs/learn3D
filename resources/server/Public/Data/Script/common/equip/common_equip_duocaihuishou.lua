
--MisDescBegin
--�ű���
x800109_g_ScriptId = 800109

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800109_g_MissionName="��ʱ�ʯ����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800109_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800109_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800109_g_ScriptId,x800109_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800109_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800109_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800109_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800109_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800109_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800109_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800109_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800109_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800109_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
