--�����NPC��
x310158_g_ScriptId 					= 	310158   
-- ����ս�淨����ID
x310158_g_GameOpenId                = 1026
								  							   
function x310158_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    if GetGameOpenById(x310158_g_GameOpenId) <= 0 then
		return
	end
	AddQuestNumText(sceneId,310158,"�����ҡ���ѯ����ս����",3)	
end



--�������ť������������ִ�д˽ű�
function x310158_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y�����ҡ���ѯ����ս����#r#W #r"			
			
			local Readme_2 = "\t����սÿ#G����#W����һ�Σ���������Ϊ#G���ܵ��������ϣ�20��00-21��00��#W�����������������ѯ#G����#W����ս�Ƿ����� #r#r"
			
			local Readme_3 = "#r #r����ս����ʱ��Ϊ:#R#r"
			
			
			local Readme = Readme_1..Readme_2..Readme_3	
			
			
			local y,m,d = CountryBattleLite_GetNextStartDate()
			local str   ="(20:00-21:00)"
			local msg = format("%s%d-%02d-%02d%s",Readme,y,m,d,str)
			
		AddQuestText( sceneId,msg)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
end



--�����ȷ����
function x310158_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x310158_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x310158_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x310158_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x310158_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x310158_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x310158_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x310158_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x310158_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end