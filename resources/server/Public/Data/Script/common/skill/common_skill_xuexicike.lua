--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800105_g_ScriptId = 800105

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800105_g_MissionName="�̿ͼ���ѧϰ"
x800105_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�̴ܽ̿͵ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800105_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 8 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800105_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800105_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800105_g_ScriptId,x800105_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800105_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800105_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800105_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800105_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800105_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800105_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800105_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800105_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800105_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
