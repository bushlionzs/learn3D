--���ܽű�
--������ȡļ���ʽ�
--MisDescBegin
--�ű���
x300308_g_ScriptId = 300308

--��һ�������ID
--g_MissionIdPre =



--�����ı�����

x300308_g_MissionName= "ļ���ʽ� -��������ȡ��"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300308_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

end

--**********************************
--�о��¼�
--**********************************
function x300308_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x300308_g_ScriptId,x300308_g_MissionName);
end


--********************
--����������
--**********************************
function x300308_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300308_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x300308_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300308_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300308_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300308_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300308_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300308_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300308_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
