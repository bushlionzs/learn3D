--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800032_g_ScriptId = 800032

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800032_g_MissionName="���ϴ��"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800032_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������˼���ѧϰ����Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800032_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800032_g_ScriptId,x800032_g_MissionName);
end


--********************
--����������
--**********************************
function x800032_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800032_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800032_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800032_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800032_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800032_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800032_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800032_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800032_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
