
x300749_g_ScriptId = 300749

--�����ı�����
x300749_g_MissionName="��³��֮ս"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300749_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId);
		local localexp = (GetLevel( sceneId, selfId )) *1000*0.8*5	

		local Readme_1 = "#Y��³��֮ս#r#W"
		
		local Readme_2 = "\t�����У������ڴ�#r"
		
		local Readme = Readme_1..Readme_2
		
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 );
	
end

--**********************************
--�о��¼�
--**********************************
function x300749_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--AddQuestNumText(sceneId,x300749_g_ScriptId,x300749_g_MissionName);
end


--********************
--����������
--**********************************
function x300749_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300749_ProcAccept( sceneId, selfId )

	
end

--**********************************
--����
--**********************************
function x300749_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300749_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300749_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300749_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300749_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300749_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300749_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
