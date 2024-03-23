
x310184_g_scriptId = 310184
x310184_g_GameId = 1019
x310184_g_LimitLevel = 40
x310184_g_MaxCount = 20

x310184_g_GameID_Right	= 971
x310184_g_GameID_Error	= 972

function x310184_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(x310184_g_GameId) ~= 1 then
		return
	end
	
    AddQuestNumText(sceneId,x310184_g_scriptId,"��Ҫ�μ������ʵ��ռ���ս��",3,x310184_g_scriptId);
        
end

function x310184_IsInPool(sceneId,selfId)
	local name = GetName(sceneId,selfId)

	for i=1, WULONGCIDIAN_STEPIN_COUNT do
		if WULONGCIDIAN_STEPIN_NAME[i] == name then
			return 1
		end
	end
	return -1
end

function x310184_CheckValid( sceneId,selfId,npcId)
	if GetGameOpenById(x310184_g_GameId) ~= 1 then
		--���������ʾ
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t�����ʵ��Ѿ��رգ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -1
	end

	local level = GetLevel(sceneId,selfId)
	if level<x310184_g_LimitLevel then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t���ƺ�û��ȡ�òμ������ǵ��ռ���ս���ʸ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -2
	end
	local minute =  GetMinOfDay()
		if GetWeek() ~= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t�����ǵ��ռ���ս������������16��30����ʽ��ʼ�����ļ���")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -3
		elseif 	minute>17*60 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t���ź��������ǵ��ռ���ս��������17��00�Ѿ������ˡ�")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -3
		elseif 	minute <16*60+30 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t�����ǵ��ռ���ս��������16��30����ʽ��ʼ�����ļ���")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -3
		end

	local curDay = GetDayOfYear() 
	local nDate   = GetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3] )
	if curDay ~= nDate then
		BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t���ƺ�û��ȡ�òμ������ǵ��ռ���ս���ʸ�")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		return -5
	end

	if x310184_IsInPool(sceneId,selfId) < 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t���ƺ�û��ȡ�òμ������ǵ��ռ���ս���ʸ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -4
	end

	return 1

end

function x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)
	--������ѡ��
	local answer = { {strAnswer1,12001},{strAnswer2,12002},{strAnswer3,12003},{strAnswer4,12004} }
	local index = {1,2,3,4}
	for i=1, 4 do
		local r = random(1, getn(index))
		AddQuestNumText(sceneId,x310184_g_scriptId,answer[index[r]][1],3,answer[index[r]][2] )

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
	local guoguan = 1 - GetQuestData(sceneId,selfId,MD_WULONG_GUOGUANLING[1], MD_WULONG_GUOGUANLING[2], MD_WULONG_GUOGUANLING[3])
	local heibai = 3 - GetQuestData(sceneId,selfId,MD_WULONG_HEIBAILING[1], MD_WULONG_HEIBAILING[2], MD_WULONG_HEIBAILING[3])
	if guoguan < 0 then
		guoguan = 0
	end
	if heibai < 0 then
		heibai = 0
	end
	AddQuestNumText(sceneId,x310184_g_scriptId, format("�����һ����ȷ��ʣ��%d�Σ�",guoguan),13,12005 )
	AddQuestNumText(sceneId,x310184_g_scriptId, format("�ڰ��������ȷ��ʣ��%d�Σ�",heibai),13,12006 )
end

function x310184_AddAward(sceneId ,selfId)
	local nExpBonus = GetLevel(sceneId ,selfId)*2400
	AddExp(sceneId, selfId, nExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o���#R����"..nExpBonus.."��#o�Ľ���",4,2)
end

function x310184_PushToPool(sceneId ,selfId, costTime)
	--------------------
	local name = GetName(sceneId ,selfId)
	if WULONGCIDIAN_AWARD_COUNT == 0 then
		WULONGCIDIAN_AWARD_COUNT = 1
		WULONGCIDIAN_AWARD_NAME[WULONGCIDIAN_AWARD_COUNT] = name
		WULONGCIDIAN_AWARD_TIME[WULONGCIDIAN_AWARD_COUNT] = costTime
		return
	end

	for i=1, WULONGCIDIAN_AWARD_COUNT do
		if WULONGCIDIAN_AWARD_NAME[i] == name then
			if WULONGCIDIAN_AWARD_TIME[i] > costTime then
				WULONGCIDIAN_AWARD_TIME[i] = costTime	
			end
			return
		end
	end
	
	if WULONGCIDIAN_AWARD_COUNT == 30 then
		for i=1, WULONGCIDIAN_AWARD_COUNT do
			if WULONGCIDIAN_AWARD_TIME[i] > costTime then
				
				for j=WULONGCIDIAN_AWARD_COUNT, i, -1 do
					if (j-1>0) then
						WULONGCIDIAN_AWARD_NAME[j] = WULONGCIDIAN_AWARD_NAME[j-1]
						WULONGCIDIAN_AWARD_TIME[j] = WULONGCIDIAN_AWARD_TIME[j-1]
					end
				end

				WULONGCIDIAN_AWARD_NAME[i] = name
				WULONGCIDIAN_AWARD_TIME[i] = costTime
				return
			end
		end
	elseif WULONGCIDIAN_AWARD_COUNT < 30 then
		for i=1, WULONGCIDIAN_AWARD_COUNT do
			if WULONGCIDIAN_AWARD_TIME[i] > costTime then
				
				for j=(WULONGCIDIAN_AWARD_COUNT+1), i, -1 do
					if (j-1>0) then
						WULONGCIDIAN_AWARD_NAME[j] = WULONGCIDIAN_AWARD_NAME[j-1]
						WULONGCIDIAN_AWARD_TIME[j] = WULONGCIDIAN_AWARD_TIME[j-1]
					end
				end

				WULONGCIDIAN_AWARD_NAME[i] = name
				WULONGCIDIAN_AWARD_TIME[i] = costTime
				WULONGCIDIAN_AWARD_COUNT = WULONGCIDIAN_AWARD_COUNT + 1
				return
			end
		end
	end
	
	if WULONGCIDIAN_AWARD_COUNT < 30 then
		WULONGCIDIAN_AWARD_COUNT = WULONGCIDIAN_AWARD_COUNT + 1
		WULONGCIDIAN_AWARD_NAME[WULONGCIDIAN_AWARD_COUNT] = name
		WULONGCIDIAN_AWARD_TIME[WULONGCIDIAN_AWARD_COUNT] = costTime
		return
	end

end

function x310184_GetValidTime()

	local n1 = GetCurrentTime()
	local n2 = GetCurrentTime()
	
	local nResult = n2 - n1 
	while nResult > 5 or nResult < 0 do
		n1 = GetCurrentTime()
		n2 = GetCurrentTime()
		nResult = n2 - n1 
	end
	
	return n2
end

function x310184_AfterAnswer(sceneId ,selfId)
	
	if GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )>= x310184_g_MaxCount then
		local costTime = x310184_GetValidTime() - GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
		x310184_PushToPool(sceneId ,selfId, costTime)
		return 1
	end
	return -1
end


function x310184_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )
	if x310184_CheckValid( sceneId,selfId,npcId) < 0 then
		return
	end

	local step = GetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3])
	
	if idExt ==  12005 then
		if step ~= 4 then
				return 
		end

		if GetQuestData(sceneId,selfId,MD_WULONG_GUOGUANLING[1], MD_WULONG_GUOGUANLING[2], MD_WULONG_GUOGUANLING[3]) == 1 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t�Ѿ��ù������");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"�Ѿ��ù������",8,2)
			return 
		end

		SetQuestData(sceneId,selfId,MD_WULONG_GUOGUANLING[1], MD_WULONG_GUOGUANLING[2], MD_WULONG_GUOGUANLING[3], 1)
		
		 local lastAnswer = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER)
		 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )

		local curRightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3], curRightCount+1 )

			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "��ϲ��,�ش���ȷ��");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"��ϲ��,�ش���ȷ��",8,2)

			--������
			x310184_AddAward(sceneId ,selfId)

			--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Right)
			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"��ɹ������������ǵ��ռ���ս��",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t��ɹ������������ǵ��ռ���ս��")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end

			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)

		return
	end

	if idExt == 12006 then
		if step ~= 4 then
				return 
		end

		local useHeiBai = GetQuestData(sceneId,selfId,MD_WULONG_HEIBAILING[1], MD_WULONG_HEIBAILING[2], MD_WULONG_HEIBAILING[3]) 
		if useHeiBai>= 3 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t�Ѿ��ù�3�κڰ��");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"�Ѿ��ù�3�κڰ��",8,2)
			return 
		end

		SetQuestData(sceneId,selfId,MD_WULONG_HEIBAILING[1], MD_WULONG_HEIBAILING[2], MD_WULONG_HEIBAILING[3], useHeiBai+1)
		local bRight;
		local r = random(1, 100)
		if r>=1 and r<=50 then
			bRight = 1
		else
			bRight = 0
		end

		local lastAnswer = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER)
		 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )

		if bRight == 1 then

			local curRightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3], curRightCount+1 )

			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "��ϲ��,�ش���ȷ��");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"��ϲ��,�ش���ȷ��",8,2)

			--������
			x310184_AddAward(sceneId ,selfId)

			--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Right)
			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"��ɹ������������ǵ��ռ���ս��",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t��ɹ������������ǵ��ռ���ս��")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end

			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return 
		else
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t�ش������Ĵ�����ʱ��������15�롣");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"�ش������Ĵ�����ʱ��������15�롣",8,2)
			--����淨��־
			GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Error)
			local curTime = GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], curTime-15 )

			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"��ɹ������������ǵ��ռ���ս��",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t��ɹ������������ǵ��ռ���ս��")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return
		end

		return
	end

	if idExt == x310184_g_scriptId then 

		if step ~= 4 then
			SetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3], 4)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000 )
			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3], 1 )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3],0 )
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], x310184_GetValidTime())
		else
			local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
			 if curCount >= x310184_g_MaxCount then --����
				x310184_AfterAnswer(sceneId ,selfId)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t��ɹ��Ĵ������ռ���ս����ȴ����εĹ�����")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return 
			 end

			--SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

			--local lastTime = GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
			--SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], lastTime-15 )
		end
		 
		local lastquest = GetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3])
		if lastquest ~= 60000 then
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestWulong_GetQuestionInfo(1, 1, lastquest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,strDesc)
				x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		else
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

			BeginQuestEvent(sceneId)	
					AddQuestText(sceneId,strDesc)
					x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		end

		return
	elseif idExt >= 12001 and idExt <= 12004 then
		if step ~= 4 then
				return 
		end

		 local lastAnswer = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER)
		 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		 SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000)

		if lastAnswer == idExt then --���
			local curRightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
			SetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3], curRightCount+1 )

			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t��ϲ��,�ش���ȷ��");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"��ϲ��,�ش���ȷ��",8,2)

			--������
			x310184_AddAward(sceneId ,selfId)

			--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Right)
			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"��ɹ������������ǵ��ռ���ս��",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t��ɹ������������ǵ��ռ���ս��")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
		else
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t�ش������Ĵ�����ʱ��������15�롣");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"�ش������Ĵ�����ʱ��������15�롣",8,2)
			--����淨��־
			GamePlayScriptLog( sceneId, selfId, x310184_g_GameID_Error)
			local curTime = GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
			SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], curTime-15 )

			if x310184_AfterAnswer(sceneId ,selfId) > 0 then
				Msg2Player(sceneId,selfId,"��ɹ������������ǵ��ռ���ս��",8,2)
				BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,"\t��ɹ������������ǵ��ռ���ս��")						
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
		end

		SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3],curCount+1 )

		local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, nQuest = QuestWulong_GetQuestionInfo(1)
		SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], nQuest)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

		BeginQuestEvent(sceneId)	
				AddQuestText(sceneId,strDesc)
				x310184_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)

		return
	end

end

