
x300765_g_ScriptId 					= 	300765  
x300765_g_MissionName0= "����ؽ��ܡ�"
x300765_g_MissionName1= "������������"
x300765_g_MissionName2= "���������ս����"

function x300765_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300765,"���������ս˵����",1)	
end



--�������ť������������ִ�д˽ű�
function x300765_ProcEventEntry( sceneId, selfId, targetId)		
			BeginQuestEvent(sceneId)
			local Readme_1 = "#Y���������ս˵����#r#W #r"						
			local Readme_2 = "\t��������ڳɼ�˼�������������鹥���ӵصĿ�У���Ҫ����ؾ���һ�����˽���ܵ���Ӧ�֡� #r"			
			local Readme_3 = "\t�������ж�Ӧ��ť�������Բ�ѯ��������Ϣ:"			
			local Readme = Readme_1..Readme_2..Readme_3
			
			AddQuestNumText(sceneId,300935 ,x300765_g_MissionName0,1);
			AddQuestNumText(sceneId,300936 ,x300765_g_MissionName1,1);		
			AddQuestNumText(sceneId,300937 ,x300765_g_MissionName2,1);			
			AddQuestText( sceneId,Readme)
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,targetId);
end



function x300765_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300765_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300765_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300765_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300765_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300765_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300765_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300765_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300765_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end