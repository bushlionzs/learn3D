
--MisDescBegin
--�ű���
x800071_g_ScriptId = 800071

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800071_g_MissionName="�������ɫ"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800071_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800071_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800071_g_ScriptId,x800071_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800071_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800071_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800071_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800071_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800071_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800071_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800071_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800071_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800071_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
