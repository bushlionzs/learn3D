--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800045_g_ScriptId = 800045

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800045_g_MissionName="��ǹ����ѧϰ"
x800045_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�̻ܽ�ǹ�ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800045_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 3 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800045_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800045_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800045_g_ScriptId,x800045_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800045_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800045_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800045_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800045_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800045_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800045_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800045_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800045_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800045_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
