--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800104_g_ScriptId = 800104

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800104_g_MissionName="ʥ��ʹ����ѧϰ"
x800104_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ�ʥ��ʹ�ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800104_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 7 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800104_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800104_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800104_g_ScriptId,x800104_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800104_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800104_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800104_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800104_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800104_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800104_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800104_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800104_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800104_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
