--�����NPC��
x300792_g_ScriptId 					= 	300792   
x300792_g_MissionName0= "�����ܡ��������"
x300792_g_MissionName1= "�����ܡ�������"
x300792_g_MissionName2= "�����ܡ���������"
x300792_g_MissionName3= "�����ܡ����˽���" 
x300792_g_MissionName4= "�����ܡ��ػ�����" 							   
function x300792_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300792,"�����ܡ���������",1)	
end



--�������ť������������ִ�д˽ű�
function x300792_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300792_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y�����ܡ���������#r#W"			
			
			local Readme_2 = "\t�����Ǹ���Ϊ�����������׵Ĺ����һ�ֽ����� #r"
			
			local Readme_3 = "\t�������ж�Ӧ��ť�������Բ�ѯ���������Ϣ:"
			
			
			local Readme = Readme_1..Readme_2..Readme_3
		AddQuestNumText(sceneId,300793 ,x300792_g_MissionName0,1);
		AddQuestNumText(sceneId,300794 ,x300792_g_MissionName1,1);
		AddQuestNumText(sceneId,300795 ,x300792_g_MissionName2,1);
		AddQuestNumText(sceneId,300796 ,x300792_g_MissionName3,1);
		AddQuestNumText(sceneId,300799 ,x300792_g_MissionName4,1);
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
end



--�����ȷ����
function x300792_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300792_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300792_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300792_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300792_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300792_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300792_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300792_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300792_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end