--���ܣ����ѱ��

--MisDescBegin
--�ű���
x800051_g_ScriptId = 800051

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800051_g_MissionName="���ѱ��"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800051_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������˼���ѧϰ����Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800051_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800051_g_ScriptId,x800051_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800051_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800051_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800051_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800051_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800051_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800051_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800051_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800051_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800051_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
