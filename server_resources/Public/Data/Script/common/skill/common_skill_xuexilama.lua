--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800108_g_ScriptId = 800108

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800108_g_MissionName="ɮ�¼���ѧϰ"
x800108_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ�ɮ�µļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800108_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 11 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800108_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800108_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800108_g_ScriptId,x800108_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800108_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800108_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800108_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800108_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800108_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800108_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800108_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800108_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800108_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
