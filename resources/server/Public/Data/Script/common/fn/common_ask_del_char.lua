
x561102_g_ScriptId = 561102
x561102_g_MissionName = "ɾ����ɫ"

--�����NPC��
function x561102_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,561102,x561102_g_MissionName,0,-1)
	
end



--�������ť������������ִ�д˽ű�
function x561102_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t��ȷ��Ҫɾ����")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, 561102, -1);

end


--�����ȷ����
function x561102_ProcAcceptCheck( sceneId, selfId, NPCId )
	
	return 1

end


--**********************************
--����
--**********************************
function x561102_ProcAccept( sceneId, selfId )

	if x561102_IsCanDeleteChar( sceneId, selfId ) == 1 then
		AskDeleteChar( sceneId, selfId )
	end

end

--����������֤ͨ����Ĵ���
function x561102_OnDeleteChar( sceneId, selfId )

	if x561102_IsCanDeleteChar( sceneId, selfId ) == 1 then
		DeleteChar( sceneId, selfId )
	end

end

function x561102_IsCanDeleteChar( sceneId, selfId )

	if CountryGetOfficial( sceneId, selfId ) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"ɾ����ɫǰ���Ƚ�������ڵ�һ��ְ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0		
	end

	--�ж��Ƿ��ڰ����
	if GetGuildID( sceneId, selfId ) ~= -1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"ɾ����ɫǰ�����˳���ᡣ")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--�Ƿ���
	if IsMarried( sceneId, selfId ) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"ɾ����ɫǰ������顣")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--�Ƿ���ʦͽ��ϵ
	if IsHaveMaster( sceneId, selfId ) > 0 or IsHavePrentice( sceneId, selfId ) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"ɾ����ɫǰ���Ƚ��ʦͽ��ϵ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	--�Ƿ��к���
	if IsHaveFriend( sceneId, selfId ) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"ɾ����ɫǰ����ɾ�����к��ѡ�")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end	
	
	return 1

end


--**********************************
--����
--**********************************
function x561102_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x561102_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x561102_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x561102_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x561102_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x561102_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x561102_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end