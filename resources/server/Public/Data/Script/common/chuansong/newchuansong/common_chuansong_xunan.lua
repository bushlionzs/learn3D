
x550528_g_MissionId 				= 	7550                    --����ID

function x550528_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,550528,"����������",0,1)--���Ӱ�ťC
end

--�������ť������������ִ�д˽ű�
function x550528_ProcEventEntry( sceneId, selfId, targetId,state,index)	

	if index == 1 then

		local Readme_1 = "#Y������#r"
	
		local Readme_2 = "\t#W���ǰ���������ġ�׷��Ѳ������������ͨ���Ҵ��ͽ���������#r #r"
	
		local Readme_3 = "#r���Ƿ�Ҫ����������"
	
		local Readme = Readme_1..Readme_2..Readme_3	

		BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme);EndQuestEvent(sceneId);DispatchQuestInfo(sceneId, selfId, targetId, 550528, -1)
	
	end
	
end


--�����ȷ����
function x550528_ProcAcceptCheck( sceneId, selfId, NPCId )

	local posX = 0

	local posY = 0

	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x550528_g_MissionId);

	if bHaveMission > 0 then		

			local pos = random(1,2)

			local Num = random(1,7)

			if 	Num == 1 then

					posX= 198 + pos

					posY= 27 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)
					
			elseif Num == 2 then

					posX= 235 + pos

					posY= 63 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 3 then

					posX= 225 + pos

					posY= 165 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 4 then

					posX= 153 + pos

					posY= 224 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 5 then

					posX= 37 + pos

					posY= 220 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 6 then

					posX= 37 + pos

					posY= 133 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			elseif Num == 7 then

					posX= 31 + pos

					posY= 45 +  pos

					NewWorld(sceneId,selfId,95,posX,posY,550528)

			end

	else
    	BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "�ܱ�Ǹ����δ��ȡ��Ѳ�����񡱲��ܽ���������" )
    	EndQuestEvent()
        DispatchQuestTips( sceneId, selfId)

		Msg2Player( sceneId, selfId, "�ܱ�Ǹ����δ��ȡ��Ѳ�����񡱲��ܽ���������", 8, 2)
        

	end	

end


