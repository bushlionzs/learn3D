
--MisDescBegin
--�ű���
x800066_g_ScriptId = 800066

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800066_g_MissionName="װ����ֵ(�缶װ��)"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800066_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800066_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800066_g_ScriptId,x800066_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800066_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800066_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800066_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800066_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800066_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800066_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800066_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800066_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800066_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
