--Ѱ����ӽű�

--MisDescBegin
--�ű���
x302600_g_ScriptId = 302600

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x302600_g_MissionName="Ѱ�����"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x302600_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д����Ѱ����ӽ���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x302600_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x302600_g_ScriptId,x302600_g_MissionName,3);
end


--********************
--����������
--**********************************
function x302600_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x302600_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x302600_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x302600_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x302600_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x302600_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x302600_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x302600_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x302600_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
