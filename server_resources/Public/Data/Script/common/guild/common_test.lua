--�����NPC��
function x300635_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--AddQuestNumText(sceneId,300635,"���԰�ťA",0,1)
	
end



--�������ť������������ִ�д˽ű�
function x300635_ProcEventEntry( sceneId, selfId, targetId,state,index)	

		if index == 1 then
		
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"��ťA��Ӧ����������");EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 300635, -1)
			
		end
	
end



--�����ȷ����
function x300635_ProcAcceptCheck( sceneId, selfId, NPCId )
	
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"��ťA��Ӧ����������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId)
			
			Msg2Player(sceneId,selfId,"��ťA��Ӧ����������",8,2)

end



--**********************************
--����
--**********************************
function x300635_ProcAccept( sceneId, selfId )
end
--**********************************
--����
--**********************************
function x300635_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300635_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300635_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300635_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300635_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300635_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300635_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end