--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800013_g_ScriptId = 800013

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800013_g_MissionName="��˼���ѧϰ"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800013_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������˼���ѧϰ����Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800013_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800013_g_ScriptId,x800013_g_MissionName);
end


--********************
--����������
--**********************************
function x800013_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800013_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800013_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800013_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800013_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800013_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800013_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800013_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800013_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
