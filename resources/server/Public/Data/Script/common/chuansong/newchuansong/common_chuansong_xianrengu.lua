function x550523_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,550523,"���ͻع�",0,1)--���Ӱ�ťC
  --AddQuestNumText(sceneId,ScriptId,MissionName,state,index)
								--MissionName����ť����
								--state:ͷ����ʾ����
								--index:�����������ж��ã�
end

--�������ť������������ִ�д˽ű�
function x550523_ProcEventEntry( sceneId, selfId, targetId,state,index)

if index == 1 then

	local Readme_1 = "#Y���ͻر�������#r"

	local Readme_2 = "\t#W���ã�������ͨ���Ҵ��ͻر���������������Ҫ��������#G100������#W��Ϊ·�ѡ�#r"

	local Readme_3 = "#r���Ƿ�Ҫ�ص�������"

	local Readme = Readme_1..Readme_2..Readme_3

	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 550523, -1)

	end

end


--�����ȷ����
function x550523_ProcAcceptCheck( sceneId, selfId, NPCId )

	local x550523pos = random(1,3)
	
	local x550523posX = 0
	
	local x550523posY = 0
	

	if GetMoney(sceneId, selfId, 1) >= 100 then

				if GetCurCountry(sceneId,selfId) == 0 then--¥��

						x550523posX= 349 + x550523pos

						x550523posY= 489 + x550523pos

						CostMoney( sceneId , selfId , 1 , 100,302 )

						NewWorld(sceneId,selfId,51,x550523posX,x550523posY,550523)

				elseif GetCurCountry(sceneId,selfId) == 1 then--��ɽ

						x550523posX= 349 + x550523pos

						x550523posY= 489 + x550523pos

						CostMoney( sceneId , selfId, 1 , 100,302 )

						NewWorld(sceneId,selfId,151,x550523posX,x550523posY,550523)

				elseif GetCurCountry(sceneId,selfId) == 2 then--����

						x550523posX= 349 + x550523pos

						x550523posY= 489 + x550523pos

						CostMoney( sceneId , selfId, 1 , 100,302 )

						NewWorld(sceneId,selfId,251,x550523posX,x550523posY,550523)

				elseif GetCurCountry(sceneId,selfId) == 3 then--�ػ�

						x550523posX= 349 + x550523pos

						x550523posY= 489 + x550523pos

						CostMoney( sceneId , selfId, 1 , 100,302 )

						NewWorld(sceneId,selfId,351,x550523posX,x550523posY,550523)

				end

	else

		Msg2Player(sceneId,selfId,"�ܱ�Ǹ���������е���������֧��·�ѣ��޷�ʹ�ûع����ͣ�",8,2)

	end

end





















--**********************************
--����
--**********************************
function x550523_ProcAccept( sceneId, selfId )
end

--**********************************
--����
--**********************************
function x550523_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--����
--**********************************
function x550523_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--����Ƿ�����ύ
--**********************************
function x550523_CheckSubmit( sceneId, selfId )

end

--**********************************
--�ύ
--**********************************
function x550523_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--ɱ����������
--**********************************
function x550523_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--���������¼�
--**********************************
function x550523_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--���߸ı�
--**********************************
function x550523_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end







