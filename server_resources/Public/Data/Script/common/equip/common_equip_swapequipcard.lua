--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800016_g_ScriptId = 800016

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800016_g_MissionName="װ�����ĶԵ�"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800016_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������׽���Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800016_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800016_g_ScriptId,x800016_g_MissionName);
end


--********************
--����������
--**********************************
function x800016_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800016_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800016_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800016_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800016_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800016_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800016_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800016_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800016_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
