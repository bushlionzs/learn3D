
--MisDescBegin
--�ű���
x800070_g_ScriptId = 800070

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800070_g_MissionName="�������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800070_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800070_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800070_g_ScriptId,x800070_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800070_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800070_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800070_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800070_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800070_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800070_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800070_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800070_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800070_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
