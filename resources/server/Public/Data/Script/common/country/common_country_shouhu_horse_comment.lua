
x300653_g_ScriptId 					= 	300653  
 
function x300653_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300653,"���ػ�����˵����",1)	
end



--�������ť������������ִ�д˽ű�
function x300653_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y���ػ�����˵����#r#W #r"			
			
			local Readme_2 = "\t�������#G����֮������ȸ֮��#W������������������ȡ#R�ػ�����#W��#r"
			
			local Readme_3 = "\t��ȡ�ػ�����ʱ������#R��������#W�������ػ�������ŵȼ������������#G������ȡ#W���߼�����ػ�����뽫���е��ػ�����#G����#W��#r"
			
			local Readme_4 ="\t���ǹ��ҵ��ػ������У�#G30�����40�����50�����60�����70�����80�����90�����100������#W��#r"
			
			local Readme_5="\t��ȡʱ�������#R����ǰ�ĵȼ�#W�������������������Ӧ�ȼ������#r"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
			
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--�����ȷ����
function x300653_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300653_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300653_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300653_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300653_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300653_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300653_OnKillObject( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300653_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300653_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end