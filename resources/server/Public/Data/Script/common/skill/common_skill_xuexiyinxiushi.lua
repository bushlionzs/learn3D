--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800107_g_ScriptId = 800107

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800107_g_MissionName="����ʿ����ѧϰ"
x800107_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ�����ʿ�ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800107_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 10 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800107_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800107_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800107_g_ScriptId,x800107_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800107_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800107_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800107_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800107_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800107_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800107_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800107_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800107_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800107_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
