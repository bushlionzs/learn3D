--װ������ű�

--MisDescBegin
--�ű���
x800121_g_ScriptId = 800121

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800121_g_MissionName="ս������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800121_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800121_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800121_g_ScriptId,x800121_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800121_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800121_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800121_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800121_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800121_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800121_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800121_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800121_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800121_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
