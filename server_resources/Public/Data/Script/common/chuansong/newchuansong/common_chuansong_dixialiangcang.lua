function x550502_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,550502,"�뿪����",0,1)--���Ӱ�ťC
  --AddQuestNumText(sceneId,ScriptId,MissionName,state,index)
								--MissionName����ť����
								--state:ͷ����ʾ����
								--index:�����������ж��ã�
end

--�������ť������������ִ�д˽ű�
function x550502_ProcEventEntry( sceneId, selfId, targetId,state,index)	

if index == 1 then

	local Readme_1 = "#Y���ͻر�������#r"
	
	local Readme_2 = "\t#W���ã�������ͨ���Ҵ��ͻر���������������Ҫ��������#G50������#W��Ϊ·�ѡ�#r"
	
	local Readme_3 = "#r���Ƿ�Ҫ�ص�������"
	
	local Readme = Readme_1..Readme_2..Readme_3	

	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 550502, -1)
	
	end
	
end


--�����ȷ����
function x550502_ProcAcceptCheck( sceneId, selfId, NPCId )


	local x550502posX = 0
	local x550502posY = 0
	local x550502pos = random(1,2)

	if GetMoney(sceneId, selfId, 1) >= 50 then
	
				if GetCurCountry(sceneId,selfId) == 0 then--¥��

						x550502posX= 273 + x550502pos
						
						x550502posY= 233 + x550502pos
						
						CostMoney( sceneId , selfId , 1 , 50,302 )

						NewWorld(sceneId,selfId,51,x550502posX,x550502posY, 550502)	
						
				elseif GetCurCountry(sceneId,selfId) == 1 then--��ɽ
				
						x550502posX= 273 + x550502pos
						
						x550502posY= 233 + x550502pos

						CostMoney( sceneId , selfId, 1 , 50,302 )
						
						NewWorld(sceneId,selfId,151,x550502posX,x550502posY, 550502)
						
				elseif GetCurCountry(sceneId,selfId) == 2 then--����
				
						x550502posX= 273 + x550502pos
						
						x550502posY= 233 + x550502pos
						
						CostMoney( sceneId , selfId, 1 , 50,302 )
						
						NewWorld(sceneId,selfId,251,x550502posX,x550502posY, 550502)
						
				elseif GetCurCountry(sceneId,selfId) == 3 then--�ػ�

						x550502posX= 273 + x550502pos
						
						x550502posY= 233 + x550502pos
						
						CostMoney( sceneId , selfId, 1 , 50,302 )
						
						NewWorld(sceneId,selfId,351,x550502posX,x550502posY, 550502)
						
				end
		
	else
	
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������е���������֧��·�ѣ��޷�ʹ�ûع����ͣ�",8,2)	
	
	end
	
end





















--**********************************
--����
--**********************************
function x550502_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x550502_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x550502_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x550502_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x550502_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x550502_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x550502_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x550502_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end







