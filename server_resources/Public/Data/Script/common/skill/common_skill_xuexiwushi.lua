--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800041_g_ScriptId = 800041

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800041_g_MissionName="��ʿ����ѧϰ"
x800041_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ���ʿ�ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800041_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 0 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800041_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800041_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800041_g_ScriptId,x800041_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800041_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800041_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800041_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800041_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800041_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800041_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800041_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800041_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800041_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
