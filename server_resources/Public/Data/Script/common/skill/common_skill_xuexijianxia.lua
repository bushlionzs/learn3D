--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800042_g_ScriptId = 800042

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800042_g_MissionName="��������ѧϰ"
x800042_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ̽����ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800042_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 1 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800042_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800042_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800042_g_ScriptId,x800042_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800042_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800042_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800042_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800042_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800042_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800042_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800042_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800042_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800042_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
