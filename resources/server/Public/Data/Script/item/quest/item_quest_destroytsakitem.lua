--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800057_g_ScriptId = 800057

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800057_g_MissionName="ɾ���������"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800057_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800057_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x800057_g_ScriptId, x800057_g_MissionName,3 ,1 );
end


--********************
--����������
--**********************************
function x800057_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800057_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800057_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800057_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800057_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800057_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800057_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800057_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800057_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
