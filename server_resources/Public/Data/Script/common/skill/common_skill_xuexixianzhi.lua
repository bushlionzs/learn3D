--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800044_g_ScriptId = 800044

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800044_g_MissionName="��֪����ѧϰ"
x800044_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ���֪�ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800044_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 4 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800044_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800044_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800044_g_ScriptId,x800044_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800044_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800044_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800044_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800044_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800044_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800044_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800044_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800044_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800044_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
