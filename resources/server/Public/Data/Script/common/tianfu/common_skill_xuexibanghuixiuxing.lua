--ɱ������
--���ʿ��
--MisDescBegin
--�ű���
x570052_g_ScriptId = 570052

--��һ�������ID
--g_MissionIdPre =



--�����ı�����
x570052_g_MissionName="�����츳�о�"
x570052_g_MissionStr="�㻹δ�����κΰ�ᡣ"
x570052_g_Leader_Index=5
--MisDescEnd
--**********************************
--������ں���
--**********************************
function x570052_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	if GetGameOpenById(1052 ) == 0 then
		return
	end

	local nGuildID= GetGuildID( sceneId, selfId)
	if nGuildID == -1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x570052_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	else
		local pos = GetGuildOfficial(sceneId, selfId)
		if pos ~= x570052_g_Leader_Index then			--���ǰ���
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "��Ǹ�������ǰ�����û��Ȩ��������������츳��");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else
			OpenGuildSkillStudyUI_Guild( sceneId, selfId)
		end

	
 	end

	return 0
end

--**********************************
--�о��¼�
--**********************************
function x570052_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(1052 ) == 0 then
		return
	end

	AddQuestNumText(sceneId,x570052_g_ScriptId,x570052_g_MissionName,3);
end


--********************
--����������
--**********************************
function x570052_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x570052_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x570052_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x570052_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x570052_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x570052_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x570052_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x570052_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x570052_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
