
--MisDescBegin
--�ű���
x800061_g_ScriptId = 800061

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800061_g_MissionName="װ����ֵ(ͬ��װ��)"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800061_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800061_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800061_g_ScriptId,x800061_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800061_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800061_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800061_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800061_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800061_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800061_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800061_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800061_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800061_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
