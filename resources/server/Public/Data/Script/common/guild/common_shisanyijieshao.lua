
x300748_g_ScriptId = 300748

--�����ı�����
x300748_g_MissionName="ʮ����֮ս"

--MisDescEnd
--**********************************
--������ں���
--**********************************
function x300748_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
		BeginQuestEvent(sceneId);
		local localexp = (GetLevel( sceneId, selfId )) *1000*0.8*10	

		local Readme_1 = "#Yʮ����֮ս#r#W"
		
		local Readme_2 = "\t�����У������ڴ�#r"
		
		local Readme = Readme_1..Readme_2		
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 );
	
end

--**********************************
--�о��¼�
--**********************************
function x300748_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--AddQuestNumText(sceneId,x300748_g_ScriptId,x300748_g_MissionName);
end


--********************
--����������
--**********************************
function x300748_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--����
--**********************************
function x300748_ProcAccept( sceneId, selfId )

	
end

--**********************************
--����
--**********************************
function x300748_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300748_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300748_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300748_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300748_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300748_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300748_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
