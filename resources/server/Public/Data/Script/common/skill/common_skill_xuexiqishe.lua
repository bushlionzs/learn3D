--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800043_g_ScriptId = 800043

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800043_g_MissionName="���似��ѧϰ"
x800043_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ�����ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800043_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 2 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800043_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800043_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800043_g_ScriptId,x800043_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800043_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800043_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800043_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800043_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800043_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800043_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800043_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800043_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800043_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
