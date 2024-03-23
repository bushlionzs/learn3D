
x310182_g_scriptId = 310182
x310182_g_GameId = 1019
x310182_g_LimitLevel = 20
x310182_g_MaxCount = 20
x310182_g_NextLimitLevel = 40

x310182_g_GameID_Right	= 971
x310182_g_GameID_Error	= 972

function x310182_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x310182_g_GameId) ~= 1 then
		return
	end
	
    AddQuestNumText(sceneId,x310182_g_scriptId,"��Ҫ�μ������ʵ亣ѡ��",3,x310182_g_scriptId);
        
end

function x310182_CheckValid( sceneId,selfId,npcId)
	if GetGameOpenById(x310182_g_GameId) ~= 1 then
		--���������ʾ
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�����ʵ��Ѿ��رգ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -1
	end

	local level = GetLevel(sceneId,selfId)
	if level<x310182_g_LimitLevel then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\tֻ��20�����ϵ���Ҳ��ܲμ������ǵ亣ѡ����")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -2
	end
	local minute =  GetMinOfDay()
		
	if GetWeek() ~= 0 or minute> 840 then
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t���ź��������ǵ�������ѡ��������14��00�Ѿ������ˣ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -3
	end
	if GetWeek() ~= 0 or minute <780 then
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t���ļ��������ǵ亣ѡ��������13��00����ʽ��ʼ��")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -3
	end
		
	return 1

end

function x310182_AddAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)
	--������ѡ��
	local answer = { {strAnswer1,12001},{strAnswer2,12002},{strAnswer3,12003},{strAnswer4,12004} }
	local index = {1,2,3,4}
	for i=1, 4 do
		local r = random(1, getn(index))
		AddQuestNumText(sceneId,x310182_g_scriptId,answer[index[r]][1],3,answer[index[r]][2] )

		local tmp = index;
		index = {}
		local curIndex =1;
		for n=1, getn(tmp) do
			if n ~= r then
				index[curIndex] = tmp[n]
				curIndex = curIndex + 1
			end
		end
	end
end

function x310182_AddAward(sceneId ,selfId)
	local nExpBonus = GetLevel(sceneId ,selfId)*800
	AddExp(sceneId, selfId, nExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o���#R����"..nExpBonus.."��#o�Ľ���",4,2)
end


function x310182_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )
	if x310182_CheckValid( sceneId,selfId,npcId) < 0 then
		return
	end

	local step = GetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3])

	if idExt == x310182_g_scriptId then 

		local curDay = GetDayOfYear() 
		local nDate   = GetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3] )
	
		if curDay ~= nDate then
			SetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3],curDay )
			SetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3],1 )
			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],1 )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3],0 )
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3],0 )
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3],60000 )
		else
			if step ~= 1 then
				return 
			end

			 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
			 if curCount > x310182_g_MaxCount then --����
				local resultStr ="\t��ϲ��ɹ�ͨ�������ǵ亣ѡ����\n\t��������#G2��#W׼ʱǰ��#G��#W�μӿ������ҵ�#G�����ǵ���̭����\n\t#W������ǰ���󶼵�#G��157��215����96��222����66��196��#W������һ�����ҵ�#G��һ��������#W��ʼ������"
				if GetLevel(sceneId,selfId) < x310182_g_NextLimitLevel then
					resultStr = format("�ܿ�ϧ����Ȼ��μ��������ǵ亣ѡ����������ĵȼ�����%d��,�޷�������һ�֡�", x310182_g_NextLimitLevel)
				elseif GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3]) < 10 then
					resultStr = format("���ź�,��û��ͨ�������ǵ亣ѡ��\n\t#G��������Ҫ�ش���ȷ%d������ܽ�����һ�֣�", 10)
				end

				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId, resultStr)						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return 
			 end

			 --SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )
		end
		
		local lastQuest = GetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3] ) 
		if lastQuest ~= 60000 then
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestWulong_GetQuestionInfo(0, 1, lastQuest)
			if nAnswer == 0 then
				return
			end

			 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
			 local rightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )

			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)
			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310182_AddAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)						
					--local msg = format("\t����ǰ��%d�⣬�Ѵ��%d�⣩",curCount, rightCount)
					AddQuestText(sceneId,format("\t����ǰ��#G%d#W�⣬�Ѵ��#G%d#W�⣩",curCount, rightCount) )						
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)	
		else
		local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		local rightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, lastIndex = QuestWulong_GetQuestionInfo(0)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3],lastIndex )
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)
			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310182_AddAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
					--AddQuestText(sceneId,format("��ǰ��#G%d#W��",curCount))
					--AddQuestText(sceneId,format("�Ѵ��#G%d#W��",rightCount))
					--AddQuestNumText(sceneId,x310182_g_scriptId,format("����ǰ��#G%d#W��, �Ѵ��#G%d#W�⣩",curCount, rightCount),3 )
						AddQuestText(sceneId,format("\t����ǰ��#G%d#W�⣬�Ѵ��#G%d#W�⣩",curCount, rightCount) )		
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
		end
		
		
		
		return
	elseif idExt >= 12001 and idExt <= 12004 then
		if step ~= 1 then
				return 
		end

		 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		 local lastAnswer = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER)
		 SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3],60000 )

		if lastAnswer == idExt then --���
			local curRightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3], curRightCount+1 )

			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�ش���ȷ��������һ�⣡");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"�ش���ȷ��",8,2)

			--������
			x310182_AddAward(sceneId ,selfId)

			--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310182_g_GameID_Right)
		else
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "���ź���������");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���ź���������",8,2)
			--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310182_g_GameID_Error)
		end

		local curDay = GetDayOfYear() 
		local nDate   = GetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3] )

		if curDay ~= nDate then
			SetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3],curDay )
			SetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3],1 )
			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],1 )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3],0 )
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3],0 )
			return 
		else	
			if curCount >= x310182_g_MaxCount then  --����
				local resultStr ="\t��ϲ��ɹ�ͨ�������ǵ亣ѡ����\n\t��������#G2��#W׼ʱǰ��#G��#W�μӿ������ҵ�#G�����ǵ���̭����"
				if GetLevel(sceneId,selfId) < x310182_g_NextLimitLevel then
					resultStr = format("\t���ֵĲ���,��������ϧ��ĵȼ�����%d��,�޷��μ������ǵ�ڶ�����̭����", x310182_g_NextLimitLevel)
				elseif GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3]) < 10 then
					resultStr = format("\t���ź�,��û��ͨ�������ǵ����ֺ�ѡ��������Ҫ���%d����ܲμ������ǵ�ڶ�����̭����", 10)
				end

				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId, resultStr)						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				if AddQuestNM( sceneId, selfId, 9335 ) <= 0 then
					--BeginQuestEvent(sceneId);
					--AddQuestText(sceneId, "");
					--EndQuestEvent(sceneId);
					--DispatchQuestTips(sceneId,selfId);
					--Msg2Player(sceneId,selfId,"",8,2)
				else
					SetQuestParam(sceneId, selfId, 9335, 7, 1)
				end
				SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )   
				return 
			end
			 SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )
		end

		local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer,lastIndex = QuestWulong_GetQuestionInfo(0)
		SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3],lastIndex )
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)
		local lastCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		local rightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
		BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,strDesc)
				x310182_AddAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
				--AddQuestText(sceneId,format("��ǰ��#G%d#W��",lastCount))
				--AddQuestText(sceneId,format("�Ѵ��#G%d#W��",rightCount))
				--AddQuestNumText(sceneId,x310182_g_scriptId,format("����ǰ��#G%d#W��, �Ѵ��#G%d#W�⣩",curCount, rightCount),3 )
					AddQuestText(sceneId,format("\t����ǰ��#G%d#W�⣬�Ѵ��#G%d#W�⣩",lastCount, rightCount) )		
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)

		return
	end

end