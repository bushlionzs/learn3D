function x300741_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	--	AddQuestNumText(sceneId,300741,"�����ˡ��������",1);
	
end
function x300741_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�

	local Readme_1 = "#Y�����졿����#W#r"
	
	local Readme_2 = "\t�����ﵽ40��ʱ���������Խ�ȡ����ϵ������#r"
	
	local Readme_3 = "\t�����Խ�ȡ#G�����ر�#W��#G���ɱ��#W��#G�й���̽#W��#G�й��鱨#W�ĸ����������Щ���񣬿��Ի��#G�߶��#W��"
	
	local Readme = Readme_1..Readme_2..Readme_3
	
	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme)
	
	AddQuestNumText(sceneId,300743,"�����ر�",0,1)
	
	AddQuestNumText(sceneId,300742,"���ɱ��",0,1)
	
	AddQuestNumText(sceneId,300744,"�й���̽",0,1)
	
	AddQuestNumText(sceneId,300745,"�й��鱨",0,1)
	
	EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
	
end

--**********************************
--�о��¼�
--**********************************



--********************
--����������
--**********************************
function x300741_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300741_ProcAccept( sceneId, selfId )

end

--**********************************
--����
--**********************************
function x300741_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300741_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300741_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300741_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300741_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300741_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300741_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
