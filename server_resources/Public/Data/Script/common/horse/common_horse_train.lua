--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800033_g_ScriptId = 800033

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800033_g_MissionName="���ѵ��"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800033_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������˼���ѧϰ����Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800033_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800033_g_ScriptId,x800033_g_MissionName);
end


--********************
--����������
--**********************************
function x800033_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800033_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800033_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800033_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800033_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800033_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800033_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800033_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800033_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
