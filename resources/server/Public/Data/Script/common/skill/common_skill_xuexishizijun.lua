--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x800103_g_ScriptId = 800103

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x800103_g_MissionName="ʮ�־�����ѧϰ"
x800103_g_MissionStr="��Ӧ���������ʦѧϰ���ܲ��ǣ���ֻ�ܽ�ʮ�־��ļ��ܡ�"
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x800103_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 6 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800103_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--�о��¼�
--**********************************
function x800103_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800103_g_ScriptId,x800103_g_MissionName,3);
end


--********************
--����������
--**********************************
function x800103_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x800103_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x800103_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x800103_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x800103_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x800103_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x800103_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x800103_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x800103_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
