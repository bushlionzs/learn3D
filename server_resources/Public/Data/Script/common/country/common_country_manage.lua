--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800023_g_ScriptId = 800023

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800023_g_MissionName="������ҹ�����Ա"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800023_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800023_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800023_g_ScriptId,x800023_g_MissionName);
end


--********************
--����������
--**********************************
function x800023_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800023_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800023_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800023_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800023_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800023_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800023_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800023_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800023_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
