--��˷�ֳ
--��˷�ֳ
--MisDescBegin
--�ű���
x800050_g_ScriptId = 800050

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800050_g_MissionName="��˷�ֳ"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800050_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
--		(����д������˼���ѧϰ����Ľű��ӿ�)
end

--**********************************
--�о��¼�
--**********************************
function x800050_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800050_g_ScriptId,x800050_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800050_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800050_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800050_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800050_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800050_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800050_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800050_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800050_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800050_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
