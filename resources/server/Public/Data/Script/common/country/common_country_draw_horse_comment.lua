
x300651_g_ScriptId 					= 	300651  
 
function x300651_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300651,"�����ܡ���������",1)	
end



--�������ť������������ִ�д˽ű�
function x300651_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y�����ܡ���������#r#W #r"			
			
			local Readme_2 = "\t�������#G����������#W������������������ȡ#R��������#W��#r"
			
			local Readme_3 = "\t��ȡ��������ʱ������#R��������#W�����й�����ˡ�����У�������#Rѡ�����#W��������������#G�ٴ���ȡ��������#W��#r"
			
			local Readme_4 ="\t���ǹ��ҵĹ��������У�#G30�����40�����50�����60�����70�����80�����90�����100������#W��#r"
			
			local Readme_5="\t��ȡʱ�������#R����ǰ�ĵȼ�#W�������������������Ӧ�ȼ������#r"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
			
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--�����ȷ����
function x300651_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300651_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300651_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300651_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300651_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300651_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300651_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300651_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300651_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end