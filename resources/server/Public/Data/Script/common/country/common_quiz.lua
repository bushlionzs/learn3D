x300101_g_ScriptId 		= 300101
x300101_g_MissionKind 	= 	1                       --��������
x300101_g_MissionId		= 9251			--����ID
x300101_g_MissionName	= "�����ˡ��˹ٽ���"

--�������
x300101_g_MaxCount		= 15			--���ܳ���31

x300101_g_GameId		= 1038			--�淨ID
x300101_g_LimitLevel	= 50			--��ͼ���

function x300101_GetTurnCount( sceneId, selfId, daycount )
	local t = 1
	local d = daycount
	while d > 3 do
		t = t + 1
		d = d - 3
	end
	
	return t, d
end

function x300101_GetBonusExp( sceneId, selfId, Right, daycount )
	local t, d = x300101_GetTurnCount( sceneId, selfId, daycount )
	
	local level = GetLevel(sceneId,selfId)
	local bonusExp = 0
	local bonusMoney = 0
	if t == 1 then
		if Right > 0 then

			bonusExp = level*700

		else
			bonusExp = level*350
		end
		bonusMoney = 5000
	elseif t == 2 then
		if Right > 0 then
			bonusExp = level*1400
		else
			bonusExp = level*700
		end
		bonusMoney = 10000
	elseif t == 3 then
		if Right > 0 then
			bonusExp = level*2800
		else
			bonusExp = level*1400
		end
		bonusMoney = 20000
	elseif t == 4 then
		if Right > 0 then
			bonusExp = level*5600
		else
			bonusExp = level*2800
		end
		bonusMoney = 40000
	elseif t == 5 then
		if Right > 0 then
			bonusExp = level*8400
		else
			bonusExp = level*4200
		end
		bonusMoney = 60000
	end

	if level >= 80 and level <90 then
		bonusExp = bonusExp*2
	elseif level >= 90 and level <160 then
		bonusExp = bonusExp*2.6
	end
	
	return t, d, bonusExp, bonusMoney
end

----------------------------------------------------------------------------------------------
--����������Ե�����£��Żᴥ��
----------------------------------------------------------------------------------------------
function x300101_GiveBonus( sceneId,selfId, Right, daycount )

	--�δ����
	if GetGameOpenById(x300101_g_GameId) ~= 1 then
		return
	end
	
	local t, d, bonusExp, bonusMoney = x300101_GetBonusExp( sceneId, selfId, Right, daycount )
	--������
	AddExp(sceneId,selfId,bonusExp)
	
	local msg = format("#cffcf00�������#G%d�㾭��#cffcf00�Ľ���",bonusExp)
	Msg2Player(sceneId,selfId,msg,8,3)
	Msg2Player(sceneId,selfId,msg,8,2)
end

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x300101_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--�����ҵȼ�
	local level = GetLevel(sceneId,selfId)
	if level<x300101_g_LimitLevel then
		return
	end
	
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300101_g_MissionId)
	if bHaveMission <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,targetId,x300101_g_MissionId)
		AddQuestNumText(sceneId,x300101_g_MissionId,x300101_g_MissionName,state,-1)
	end
end

----------------------------------------------------------------------------------------------
--��ӵ��մ�ѡ��
----------------------------------------------------------------------------------------------
function x300101_AddDengmiAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)

	--������ѡ��
	local arr_answer = { {strAnswer1,11001},{strAnswer2,11002},{strAnswer3,11003},{strAnswer4,11004} }
	for j = 1, 2 do
		local n = random(1, 4)
		local m =  random(1, 4)
		if n ~= m then
			local t = arr_answer[n]
			arr_answer[n] = arr_answer[m]
			arr_answer[m] = t
		end
	end
	
	for i=1,4 do
		AddQuestNumText(sceneId,x300101_g_ScriptId,arr_answer[i][1],3,arr_answer[i][2] )
	end
end

-- ��ʾ����
function x300101_ShowQuiz(sceneId, selfId, npcId)

	--��ر�
	if GetGameOpenById(x300101_g_GameId) ~= 1 then
		--��¼��־
		local strMsg = format("DML:<Info>x300101_ProcTiming GM close sceneId = %d", sceneId )
    	WriteLog( 1, strMsg )
		return		
	end
	
	local nCount = QuestQuiz_GetQuestionCount()
	local idx = GetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3])-1
	if idx < 0 or idx > nCount then
		idx = random(1,nCount)
	end
	
	--�õ�����
	local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestQuiz_GetQuestionInfo(idx-1)
	
	SetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3], idx+1)
	
	--���¶Ի�������
	BeginQuestEvent(sceneId)
		
		local daycount = x300101_GetDayCount(sceneId, selfId)
		local t, d = x300101_GetTurnCount( sceneId,selfId, daycount+1 )
		AddQuestText(sceneId,format("��%d�ֵ�%d����Ŀ\n", t, d))
		
		AddQuestText(sceneId,strDesc)
		x300101_AddDengmiAnswerOption( sceneId, 
										strAnswer1, 
										strAnswer2, 
										strAnswer3, 
										strAnswer4 )
									
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,npcId)	
end

function x300101_AnswerRight( sceneId, selfId, npcId )
	--�����ʾ
	local daycount = x300101_GetDayCount(sceneId, selfId)+1
	local t, d = x300101_GetTurnCount( sceneId, selfId, daycount )
	local msg = "��ϲ�����ˡ�"
	Msg2Player(sceneId,selfId,msg,8,3)
	Msg2Player(sceneId,selfId,msg,8,2)
	if d ~= 3 then
		x300101_ShowQuiz(sceneId, selfId, npcId)
	else
		if daycount >= x300101_g_MaxCount then
			
			
			--���¶Ի�������
			BeginQuestEvent(sceneId)
				--AddQuestText(sceneId,"\t��ϲ�����ˡ�" )
				AddQuestText(sceneId,"��ϲ������˴����˹ٽ��������������������еĿ��顣������������ս��ף�������и�����ջ�")	
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		else
			--local msg = format("\t��ϲ�����ˡ�" )
			--Msg2Player(sceneId,selfId,msg,8,3)
			--Msg2Player(sceneId,selfId,msg,8,2)
			
			BeginQuestEvent(sceneId)
				if x300101_g_MaxCount - daycount <1 then
					AddQuestText(sceneId,format("\t��ϲ������˴����˹ٽ��������������������еĿ��顣������������ս��ף�������и�����ջ�") )				
				else
					AddQuestText(sceneId,format("\t��ϲ������˴����˹ٽ���������컹���Խ���#R%d��#W���㻹��μ���һ�ֵĿ�����",(x300101_g_MaxCount - daycount)/3 ) )
				end	
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		end
	end
	
	--������
	x300101_GiveBonus( sceneId,selfId, 1 , daycount)
	
	--����淨��־
	GamePlayScriptLog( sceneId, selfId, 1501)
end

function x300101_AnswerError( sceneId, selfId, npcId )
	local daycount = x300101_GetDayCount(sceneId, selfId)+1
	local t, d = x300101_GetTurnCount( sceneId, selfId, daycount )
	local msg = "���ź��������ˡ�"
		Msg2Player(sceneId,selfId,msg,8,3)
		Msg2Player(sceneId,selfId,msg,8,2)
			
	if d ~= 3 then
		x300101_ShowQuiz(sceneId, selfId, npcId)		
	else
		if daycount >= x300101_g_MaxCount then

			
			--���¶Ի�������
			BeginQuestEvent(sceneId)
				--AddQuestText(sceneId,"\t���ź��������ˡ�")	
				AddQuestText(sceneId,"\t��ϲ������˴����˹ٽ��������������������еĿ��顣������������ս��ף�������и�����ջ�")	
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		else
			--local msg = format("\t���ź��������ˡ�",x300101_g_MaxCount - daycount )
			--Msg2Player(sceneId,selfId,msg,8,3)
			--Msg2Player(sceneId,selfId,msg,8,2)
			
			BeginQuestEvent(sceneId)
				if x300101_g_MaxCount - daycount <1 then
					AddQuestText(sceneId,format("\t��ϲ������˴����˹ٽ��������������������еĿ��顣������������ս��ף�������и�����ջ�") )				
				else
					AddQuestText(sceneId,format("\t��ϲ������˴����˹ٽ���������컹���Խ���#R%d��#W���㻹��μ���һ�ִε��˹ٽ�����",(x300101_g_MaxCount - daycount)/3 ) )
				end				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		end
	end
	
	--������
	x300101_GiveBonus( sceneId,selfId, 0, daycount )
	
	--����淨��־
	GamePlayScriptLog( sceneId, selfId, 1502)
end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x300101_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

	--�δ����
	if GetGameOpenById(x300101_g_GameId) ~= 1 then
		
		--֪ͨ�ͻ����������
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
		
		--���������ʾ
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�˹ٽ��������Ѿ��رգ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	-- ������
	local daycount = x300101_GetDayCount(sceneId, selfId)
	if daycount >= x300101_g_MaxCount then
		--���¶Ի�������
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t�������Ѿ���������е��˹ٽ��������ˣ������������ɡ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	local t, d, bonusExp, bonusMoney = x300101_GetBonusExp( sceneId, selfId, 1, daycount+1 )
	
	if idExt == 12000 then
		if d == 1 and GetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3]) == 0 then
			-- ���������������
			local ret, type = SpendMoney( sceneId , selfId ,bonusMoney,301)
			if ret ~= 1 then
				local sillerMode
				if GetSillerMode(sceneId,selfId) == 1 then
					sillerMode = "����"
				else
					sillerMode = "����"
				end
				local Readme = "�ܱ�Ǹ�������˹ٽ�����Ҫ"..(bonusMoney/1000).."��"..sillerMode
				Msg2Player(sceneId,selfId,Readme,8,3)
				Msg2Player(sceneId,selfId,Readme,8,2)
				return
			else
				local sillerMode
				if type == 0 then
					sillerMode = "����"
				else
					sillerMode = "����"
				end
				local Readme = format("�����˹ٽ����ɹ����۳�#R%s#{_MONEY%d}��", sillerMode, bonusMoney)
				Msg2Player(sceneId,selfId,Readme,8,3)
				Msg2Player(sceneId,selfId,Readme,8,2)
			end
		end
		x300101_ShowQuiz(sceneId, selfId, npcId)
	elseif idExt >= 11001 and idExt <= 11004 then
		--ȡ����Ŀ��Ϣ
		local nCount = QuestQuiz_GetQuestionCount()
		local idx = GetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3])-1
		if idx < 0 or idx > nCount then
			return
		end
	
		--�õ�����
		local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestQuiz_GetQuestionInfo(idx-1)
		
		SetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3], 0)
	
		--��Ŀ��ż��ͨ���ˣ������ټ����Ƿ���ȷ
		if 11000+nAnswer == idExt then
			--�����
			x300101_AnswerRight( sceneId, selfId, npcId )
		else
			--�����
			x300101_AnswerError( sceneId, selfId, npcId )
		end	
		
		x300101_SetDayCount(sceneId, selfId)
	else
	
		local daycount = x300101_GetDayCount(sceneId, selfId)
		local t, d = x300101_GetTurnCount( sceneId,selfId, daycount+1 )
		
		--���¶Ի�������
		BeginQuestEvent(sceneId)
		
			AddQuestText(sceneId,"�����ˡ��˹ٽ���")
			if GetQuestData(sceneId, selfId, MD_QUIZ_ANSWER[1], MD_QUIZ_ANSWER[2], MD_QUIZ_ANSWER[3]) == 0 then
				AddQuestText(sceneId,format("\t������ÿ��Ϊÿ��׼����#G����#W������Ϊ�˹ٽ����Ŀ��飬ÿ������#G����#W��Ŀ��\n\t����ҳ�������ø߶�ľ���,����ش������ľ��齱��������롣\n\t�����㻹���Բμ�#R%d��#W���飬ֻҪ������#R%d��#W���ң��Ϳ��Բμӱ��ֵ��˹ٽ����������⣬ÿ���һ�����õ�#R%d����#W��", 6-t, bonusMoney/1000, bonusExp))
				AddQuestNumText(sceneId,x300101_g_ScriptId,"��ʼ����",0,12000)
			else
				AddQuestText(sceneId,format("\t������ÿ��Ϊÿ��׼����#G����#W������Ϊ�˹ٽ����Ŀ��飬ÿ������#G����#W��Ŀ������ҳ�������ø߶�飻����ش������ľ��齱��������롣\n\t��������ֵĿ��飬ÿ���һ�����õ�%d���顣", bonusExp))
				AddQuestNumText(sceneId,x300101_g_ScriptId,"�������ֿ���",0,12000)
		  end						
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)	
	end
		    
end

function x300101_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300101_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300101_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x300101_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x300101_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x300101_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x300101_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x300101_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x300101_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

---------------------------------------------------------------------------------------------------
--ȡ�ô������쵱ǰ����ɴ���
---------------------------------------------------------------------------------------------------
function x300101_GetDayCount(sceneId, selfId)
	if x300101_g_MaxCount > 0 then
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_QUIZ_DATE[1], MD_QUIZ_DATE[2], MD_QUIZ_DATE[3])
		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_QUIZ_COUNT[1], MD_QUIZ_COUNT[2], MD_QUIZ_COUNT[3])
		return daycount

	end
	return 0
end

---------------------------------------------------------------------------------------------------
--���µ�����������
---------------------------------------------------------------------------------------------------
function x300101_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_QUIZ_DATE[1], MD_QUIZ_DATE[2], MD_QUIZ_DATE[3])
	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_QUIZ_DATE[1], MD_QUIZ_DATE[2], MD_QUIZ_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_QUIZ_COUNT[1], MD_QUIZ_COUNT[2], MD_QUIZ_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_QUIZ_COUNT[1], MD_QUIZ_COUNT[2], MD_QUIZ_COUNT[3])
		SetQuestData(sceneId, selfId, MD_QUIZ_COUNT[1], MD_QUIZ_COUNT[2], MD_QUIZ_COUNT[3], daycount+1)
	end
end
