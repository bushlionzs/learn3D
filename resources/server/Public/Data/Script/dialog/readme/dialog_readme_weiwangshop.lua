--�����NPC��
function x103000_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,103000,"������˵����",0,0)	
end



--�������ť������������ִ�д˽ű�
function x103000_ProcEventEntry( sceneId, selfId, targetId,state,index)	
		local Readme_1 = "#Y������˵����#r"
		local Readme_2 = "#W\t��#Gͽ�������������ʦͽ����ʱ#W��ʦ�����������㡣#r"
		local Readme_3 = "#W#r\t��õ����������ͨ���������̵�����ȡ������Ʒ�������������������£�#r"
		local Readme_4 = "#W#r1��ʦ����ͽ�ܻ�ʦ��ͽ�ܵ�ͽ������ʱ��ʦ������һ���������㡣#r"
		local Readme_5 = "#W#r2��ʦ����ͽ��һ�����ʦͽ����ʦ�����ô����������㡣#W#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		--BeginQuestEvent(sceneId);AddQuestText(sceneId,"��ťA��Ӧ����������");EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 103000, -1)--˫��ť
		BeginQuestEvent(sceneId);AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 )--����ť
end



--�����ȷ����
function x103000_ProcAcceptCheck( sceneId, selfId, NPCId )
	
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"��ťA��Ӧ����������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
			
			Msg2Player(sceneId,selfId,"��ťA��Ӧ����������",8,2)

end



--**********************************
--����
--**********************************
function x103000_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x103000_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x103000_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x103000_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x103000_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x103000_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x103000_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x103000_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end