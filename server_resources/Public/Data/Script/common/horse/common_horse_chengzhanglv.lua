--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800018_g_ScriptId = 800018

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800018_g_MissionName="�ɳ��ʼ���"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800018_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д�����ɳ��ʼ�������Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800018_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800018_g_ScriptId,x800018_g_MissionName);
end


--********************
--����������
--**********************************
function x800018_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800018_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800018_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800018_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800018_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800018_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800018_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800018_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800018_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
