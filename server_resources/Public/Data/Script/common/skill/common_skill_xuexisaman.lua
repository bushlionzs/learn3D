--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800046_g_ScriptId = 800046

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800046_g_MissionName="��������ѧϰ"
x800046_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ������ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800046_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 5 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800046_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800046_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800046_g_ScriptId,x800046_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800046_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800046_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800046_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800046_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800046_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800046_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800046_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800046_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800046_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
