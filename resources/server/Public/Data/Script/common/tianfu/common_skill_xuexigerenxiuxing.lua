--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x570053_g_ScriptId = 570053

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x570053_g_MissionName="�����츳ѧϰ"
x570053_g_MissionStr="�㻹δ�����κΰ�ᡣ"
x570053_g_Leader_Index=5
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570053_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	
	if GetGameOpenById(1053 ) == 0 then
		return
	end

	local nGuildID= GetGuildID( sceneId, selfId)
	if nGuildID == -1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x570053_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	else
		OpenGuildSkillStudyUI_Char( sceneId, selfId)
 	end

	return 0
end

--**********************************
--�о��¼�
--**********************************
function x570053_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(1053 ) == 0 then
		return
	end

	AddQuestNumText(sceneId,x570053_g_ScriptId,x570053_g_MissionName,3);
end


--********************
--����������
--**********************************
function x570053_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x570053_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x570053_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570053_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570053_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570053_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570053_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570053_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570053_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
