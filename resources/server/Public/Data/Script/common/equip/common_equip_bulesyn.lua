
--MisDescBegin
--�ű���
x800110_g_ScriptId = 800110

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800110_g_MissionName="�������ɫ"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800110_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800110_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800110_g_ScriptId,x800110_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800110_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800110_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800110_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800110_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800110_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800110_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800110_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800110_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800110_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
