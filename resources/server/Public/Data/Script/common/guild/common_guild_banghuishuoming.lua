--�����NPC��
x300785_g_ScriptId 					= 	300785   
x300785_g_MissionName0= "�����ܡ��ﹱ"
x300785_g_MissionName1= "�����ܡ����ȼ�" 
x300785_g_MissionName2= "�����ܡ���ᾭ��"
x300785_g_MissionName3= "�����ܡ�����Ǯ"
--x300785_g_MissionName4= "�����ܡ���Ṧ��"	
x300785_g_MissionName5= "�����ܡ����ʹ����"
x300785_g_MissionName6= "�����ܡ���������츳"					  
					   
function x300785_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300785,"�����ܡ����˵��",1)	
end



--�������ť������������ִ�д˽ű�
function x300785_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300785_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y�����ܡ����˵��#r#W #r"			
			
			local Readme_2 = "\t��������ڳɼ�˼���������ｨ����ͼ��ҵ�����������һ��ǿ��İ�������������Ļ����� #r"
			
			local Readme_3 = "\t�������ж�Ӧ��ť�������Բ�ѯ��������Ϣ:"
			
			
			local Readme = Readme_1..Readme_2..Readme_3
		AddQuestNumText(sceneId,300790 ,x300785_g_MissionName0,1);
		AddQuestNumText(sceneId,300786 ,x300785_g_MissionName1,1);
		AddQuestNumText(sceneId,300787 ,x300785_g_MissionName2,1);
		AddQuestNumText(sceneId,300788 ,x300785_g_MissionName3,1);
		--AddQuestNumText(sceneId,300791 ,x300785_g_MissionName4,1);		
		AddQuestNumText(sceneId,300789 ,x300785_g_MissionName5,1);
		AddQuestNumText(sceneId,300719 ,x300785_g_MissionName6,1);
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--�����ȷ����
function x300785_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300785_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300785_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300785_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300785_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300785_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300785_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300785_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300785_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end