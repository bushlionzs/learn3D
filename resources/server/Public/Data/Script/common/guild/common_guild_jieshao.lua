--�����NPC��
function x300720_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

			AddQuestNumText(sceneId,300720,"����᡿������",0,1)--���Ӱ�ťB

  --AddQuestNumText(sceneId,ScriptId,MissionName,state,index)
								--MissionName����ť����
								--state:ͷ����ʾ����
								--index:�����������ж��ã�

end

--�������ť������������ִ�д˽ű�
function x300720_ProcEventEntry( sceneId, selfId, targetId,state,index)	

	if index == 1 then
	
			BeginQuestEvent(sceneId)

			local Readme_1 = "#Y������#r#W #r"			
			
			local Readme_2 = "һ�����#G�������#W������������������#r #r"
			
			local Readme_3 = "\t���������Ҫ#G30��#W���ϡ�#r #r"
			
			local Readme_4 = "\t����Ҫ����#G5����#W��#r #r"
			
			local Readme_5 = "\t����Ҫӵ��#G������#W��#r #r"
			
			local Readme_6 = "�������#G������#W����������һ������#r #r"
			
			local Readme_7 = "\t��������Ҫ#G20��#W���ϡ�#r #r"

			local Readme_8 = "����#G�������#W�ɹ�#G10���#W�������#Gδ�ﵽ10��#Wϵͳ��#G�Զ���ɢ���#W��#r #r"	
			
			local Readme_9=  "�ģ�#G����#W����Ҫ��ܱ߾���#G�����#W��������420��190��������#W����#Gһ�����ʻ�á�"
			
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7..Readme_8..Readme_9
			
			AddQuestText( sceneId,Readme)
			
			EndQuestEvent(sceneId)

			DispatchQuestEventList(sceneId,selfId,targetId)	
			
	end
	
end


--�����ȷ����
function x300720_ProcAcceptCheck( sceneId, selfId, NPCId )

		--BeginQuestEvent(sceneId);AddQuestText(sceneId,bb);EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);Msg2Player(sceneId,selfId,"������",8,2)

end






















--**********************************
--����
--**********************************
function x300720_ProcAccept( sceneId, sceneId )

end

--**********************************
--����
--**********************************
function x300720_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x300720_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x300720_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x300720_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x300720_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x300720_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x300720_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


