--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800106_g_ScriptId = 800106

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800106_g_MissionName="����������ѧϰ"
x800106_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ̽������ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800106_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 9 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800106_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800106_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800106_g_ScriptId,x800106_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800106_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800106_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800106_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800106_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800106_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800106_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800106_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800106_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800106_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
