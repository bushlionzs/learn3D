--**********************************
--������ں���
--**********************************
function x300775_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
	BeginQuestEvent(sceneId);
	
	local Readme_1 = "#Y�������ر�֮��������������#W#r"
	
	local Readme_2 = "\t�����ﵽ40��ʱ�����������������ն�̨��ȡ�����ر���������������ȡ�ͻظ������رߵڶ���������������ġ�#r"
	
	local Readme_3 = "\t#W�����ڼ����������߻�ʱ�������Զ��ó�ʧ��״̬������������ȡ��" 
	
	local Readme = Readme_1..Readme_2..Readme_3
	
	AddQuestText(sceneId,Readme)
	
	EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
	
end

--**********************************
--�о��¼�
--**********************************
function x300775_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local Level = GetLevel(sceneId, selfId)--�ж��Ƿ����40��
	if Level >= 40 then
		AddQuestNumText(sceneId,300775,"�������ر�֮��������������",5);
	end
end


--********************
--����������
--**********************************
function x300775_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300775_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x300775_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300775_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300775_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300775_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300775_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300775_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300775_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
