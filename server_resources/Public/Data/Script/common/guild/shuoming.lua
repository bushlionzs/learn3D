--�����NPC��
x300766_g_ScriptId 					= 	300766   
x300766_g_MissionName0= "���������˵����"
x300766_g_MissionName1= "����ᰵս˵����"
--x300766_g_MissionName2= "�����ܡ����ֳ���"
-- x300766_g_MissionName3= "�����ܡ��ռ���ľ" 
x300766_g_MissionName4= "������ħ˵����"
x300766_g_MissionName5= "�����ͼ��˵����"
x300766_g_MissionName6= "���������˵����" 
--x300766_g_MissionName7= "�����ܡ�����ܻ�"
x300766_g_MissionName8= "����������˵����"
x300766_g_MissionName9= "����ṱƷ˵����"	
x300766_g_MissionName10= "������ٳ�˵����"									  

							   
function x300766_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300766,"���������˵����",1)	
end



--�������ť������������ִ�д˽ű�
function x300766_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y���������˵����#r#W #r"			
			
			local Readme_2 = "\t��������ڳɼ�˼���������ｨ����ͼ��ҵ�����������һ��ǿ��İ�������������Ļ����� #r"
			
			local Readme_3 = "\t�������ж�Ӧ��ť�������Բ�ѯ��������Ϣ:"
			
			
			local Readme = Readme_1..Readme_2..Readme_3
		AddQuestNumText(sceneId,300774 ,x300766_g_MissionName0,1);
		AddQuestNumText(sceneId,300767 ,x300766_g_MissionName1,1);
		-- AddQuestNumText(sceneId,300768 ,x300766_g_MissionName2,1);
		-- AddQuestNumText(sceneId,300769 ,x300766_g_MissionName3,1);
		AddQuestNumText(sceneId,300770 ,x300766_g_MissionName4,1);
		AddQuestNumText(sceneId,300771 ,x300766_g_MissionName5,1);
		AddQuestNumText(sceneId,300704 ,x300766_g_MissionName6,1);
		--AddQuestNumText(sceneId,300804 ,x300766_g_MissionName7,1);
		AddQuestNumText(sceneId,300773 ,x300766_g_MissionName8,1);
		AddQuestNumText(sceneId,300784 ,x300766_g_MissionName9,1);
		AddQuestNumText(sceneId,300830 ,x300766_g_MissionName10,1);
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--�����ȷ����
function x300766_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300766_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300766_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300766_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300766_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300766_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300766_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300766_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300766_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end