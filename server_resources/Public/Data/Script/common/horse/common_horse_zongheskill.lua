--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800034_g_ScriptId = 800034

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800034_g_MissionName="��˼���"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800034_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������˼���ѧϰ����Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800034_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800034_g_ScriptId,x800034_g_MissionName);
end


--********************
--����������
--**********************************
function x800034_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800034_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800034_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800034_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800034_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800034_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800034_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800034_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800034_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
