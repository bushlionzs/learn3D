--�����NPC��
x300317_g_ScriptId 					= 	300317   
--x300317_g_MissionName6= "" 
--x300317_g_MissionName7= ""
								  

							   
function x300317_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,300317,"�����ҡ�ı������",0,1)	
end



--�������ť������������ִ�д˽ű�
function x300317_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y�����ҡ�ı������#r#G"
		local Readme_2 = "#Yһ��#G��������ڹ��ҵ�ս��֮������һ������19��30-23��00֮�䱻�й��ݻ٣����ᵼ�±���������̨�����ҽ����޹���״̬��ͬʱ������̨�Ĺ����ｫ�������������#r#r"
		local Readme_3 = "#Y����#G����̨�Ĺ������������������������������ͬʱ��һ����ս��֮���ٴα��й��ݻ�ʱ���¹��������������λ�� #r#r"
		local Readme_4 = "#Y����#G��һ������19��30-23��00֮�䣬��ɱ�й�ս��֮�죬�ᵼ�¸ù������Զ���̨��#r#r"
		local Readme_5 = "#Y�ģ�#G����ù�û�й�������ݻ�ս��֮����Ч�� #r#r"
		local Readme_6 = "#Y�壬#G���¸ù�������̨��һ��֮�����ս��֮���ٴα��ݻ��򲻻ᴥ��������̨�¼���#r#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6
		--AddQuestNumText(sceneId,300772 ,x300317_g_MissionName6,1);
		--AddQuestNumText(sceneId,300773 ,x300317_g_MissionName7,1);
		AddQuestText( sceneId,Readme)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
		
end



--�����ȷ����
function x300317_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--����
--**********************************
function x300317_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300317_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300317_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300317_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300317_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300317_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300317_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300317_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end