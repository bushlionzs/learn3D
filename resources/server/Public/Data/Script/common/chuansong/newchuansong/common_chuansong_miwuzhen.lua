function x550529_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,550529,"�뿪������",0,1)--���Ӱ�ťC
  --AddQuestNumText(sceneId,ScriptId,MissionName,state,index)
								--MissionName����ť����
								--state:ͷ����ʾ����
								--index:�����������ж��ã�
end

--�������ť������������ִ�д˽ű�
function x550529_ProcEventEntry( sceneId, selfId, targetId,state,index)	

if index == 1 then

	local Readme_1 = "#Y�뿪������#r"
	
	local Readme_2 = "\t#W���ã�������ͨ�����뿪�������������Ƿ�Ҫ�뿪��"
	
	local Readme = Readme_1..Readme_2

	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 550529, -1)
	
	end
	
end


--�����ȷ����
function x550529_ProcAcceptCheck( sceneId, selfId, NPCId )

	local x550529pos = random(1,2)
	
	local x550529posX = 0
	
	local x550529posY = 0

				if GetCurCountry(sceneId,selfId) == 0 then--¥��		
						
						x550529posX= 381 + x550529pos
						
						x550529posY= 69 + x550529pos
						
						NewWorld(sceneId,selfId,50,x550529posX,x550529posY,550529)	
						
				elseif GetCurCountry(sceneId,selfId) == 1 then--��ɽ
										
						x550529posX= 381 + x550529pos
						
						x550529posY= 69 + x550529pos

						NewWorld(sceneId,selfId,150,x550529posX,x550529posY,550529)
						
				elseif GetCurCountry(sceneId,selfId) == 2 then--����
								
						x550529posX= 381 + x550529pos
						
						x550529posY= 69 + x550529pos
						
						NewWorld(sceneId,selfId,250,x550529posX,x550529posY,550529)
						
				elseif GetCurCountry(sceneId,selfId) == 3 then--�ػ�

						x550529posX= 381 + x550529pos
						
						x550529posY= 69 + x550529pos
						
						NewWorld(sceneId,selfId,350,x550529posX,x550529posY,550529)
						
				end
	
end





















--**********************************
--����
--**********************************
function x550529_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x550529_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x550529_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x550529_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x550529_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x550529_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x550529_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x550529_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end







