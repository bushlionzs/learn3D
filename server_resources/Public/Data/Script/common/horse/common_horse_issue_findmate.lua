--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800029_g_ScriptId = 800029

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800029_g_MissionName="�����������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800029_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	OpenFindHorseMating(sceneId, selfId, 0) --0: ����
end

--**********************************
--�о��¼�
--**********************************
function x800029_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800029_g_ScriptId,x800029_g_MissionName);
end


--********************
--����������
--**********************************
function x800029_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800029_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800029_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800029_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800029_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800029_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800029_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800029_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800029_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
