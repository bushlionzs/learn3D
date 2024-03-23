
x310183_g_scriptId = 310183
x310183_g_GameId = 1019
x310183_g_LimitLevel = 40
x310183_g_MaxCount = 20

x310183_g_GameID_Right	= 971
x310183_g_GameID_Error	= 972

x310183_g_NpcList = {141512, 141513, 141514,141515,141516,
						141517,141518,141519,141520,141521,
						141522,141523,141524,141525,141526,
						141527,141528,141529,141530,141531}

function x310183_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	

	if GetGameOpenById(x310183_g_GameId) ~= 1 then
		return
	end
	
    AddQuestNumText(sceneId,x310183_g_scriptId,"��Ҫ�μ������ʵ���̭����",3,x310183_g_scriptId);
        
end

function x310183_CheckValid( sceneId,selfId,npcId)


	if GetGameOpenById(x310183_g_GameId) ~= 1 then
		--���������ʾ
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t�����ʵ��Ѿ��رգ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -1
	end

	local level = GetLevel(sceneId,selfId)
	if level<x310183_g_LimitLevel then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t��ĵȼ����㣬��40��֮��������")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return -2
	end
	local minute =  GetMinOfDay()

	--if GetWeek() ~= 0 or minute>16*60 then
	--	BeginQuestEvent(sceneId)
	--		AddQuestText(sceneId,"\t���ź��������ǵ����̭��������16��00�Ѿ������ˡ�")				
	--	EndQuestEvent(sceneId)
	--	DispatchQuestEventList(sceneId,selfId,npcId)
	--	return -3
	--end
	--if  GetWeek() ~= 0 or minute <14*60 then
	--	BeginQuestEvent(sceneId)
	--		AddQuestText(sceneId,"\t�����ǵ����̭��������2��00����ʽ��ʼ�����ļ���")				
	--	EndQuestEvent(sceneId)
	--	DispatchQuestEventList(sceneId,selfId,npcId)
	--	return -3
	--end

		if GetWeek() ~= 0 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t�����ǵ����̭������������2��00����ʽ��ʼ�����ļ���")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -3
		elseif 	minute>16*60 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t���ź��������ǵ����̭��������16��00�Ѿ������ˡ�")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -3
		elseif 	minute <14*60 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t�����ǵ����̭��������2��00����ʽ��ʼ�����ļ���")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -3
		end
		
	local curDay = GetDayOfYear() 
	local nDate   = GetQuestData(sceneId,selfId,MD_WULONG_DATE[1], MD_WULONG_DATE[2], MD_WULONG_DATE[3] )
	if curDay ~= nDate then
		BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t���ź�����û��ͨ�������ǵ�������ѡ��")		
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		return -6
	end

	if IsHaveQuest(sceneId,selfId, 9335) <= 0 then
  	if AddQuestNM( sceneId, selfId, 9335 ) <= 0 then
  			--Msg2Player(sceneId, selfId, "�������������������������μ������ʵ���̭��", 0, 2)
				Msg2Player(sceneId, selfId, "�������������������������μ������ʵ���̭��", 0, 3)
  	end
  end  
	
	local step = GetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3])
	if step == 1 or step == 0 then
	 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		 if curCount < 20 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t���ź�����û��ͨ�������ǵ�������ѡ��")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -4
		elseif curCount > 20 then
			SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3], 20 )
		 end
		 local curRightCount = GetQuestData(sceneId,selfId,MD_WULONG_RIGHT_COUNT[1], MD_WULONG_RIGHT_COUNT[2], MD_WULONG_RIGHT_COUNT[3] )
		 if curRightCount <10 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t���ź�����û��ͨ�������ǵ�������ѡ��")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -5
		 end
	end
	
	local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
	if step == 1 and curCount == 20 then
		if GetMonsterGUID(sceneId, npcId) ~= x310183_g_NpcList[1] then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t��Ӧ��ȥ��@npc_"..x310183_g_NpcList[1].."���ܿ��顣")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return -7
		end
	end

	if step == 2 or step == 3 then
		if curCount>=1 and curCount<=20 then
			if GetMonsterGUID(sceneId, npcId) ~= x310183_g_NpcList[curCount] then

				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t��Ӧ��ȥ��@npc_"..x310183_g_NpcList[curCount].."���ܿ��顣")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return -7
			end
		end
	end

	return 1

end

function x310183_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)
	--������ѡ��
	local answer = { {strAnswer1,12001},{strAnswer2,12002},{strAnswer3,12003},{strAnswer4,12004} }
	local index = {1,2,3,4}
	for i=1, 4 do
		local r = random(1, getn(index))
		AddQuestNumText(sceneId,x310183_g_scriptId,answer[index[r]][1],3,answer[index[r]][2] )

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
	AddQuestNumText(sceneId,x310183_g_scriptId, format("�����һ����ȷ��ʣ��%d�Σ�",guoguan),13,12005 )
	AddQuestNumText(sceneId,x310183_g_scriptId, format("�ڰ��������ȷ��ʣ��%d�Σ�",heibai),13,12006 )

end

function x310183_AddAward(sceneId ,selfId)
	local nExpBonus = GetLevel(sceneId ,selfId)*2400
	AddExp(sceneId, selfId, nExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o���#R����"..nExpBonus.."��#o�Ľ���",4,2)
	
end

function x310183_GetValidTime()

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

function x310183_ModifyCount(sceneId ,selfId, value)
	
	--if value > 20 then
		--value = 20
	--end
	SetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3], value )
	SetQuestData(sceneId,selfId,MD_WULONG_ERROR_COUNT[1], MD_WULONG_ERROR_COUNT[2], MD_WULONG_ERROR_COUNT[3], 0)
	x310183_ProcQuestLogRefresh( sceneId, selfId, 9335)

end

----------------------------------------------------------
--������ݵ��������
----------------------------------------------------------
function x310183_PushToPool(sceneId ,selfId, costTime)

	local name = GetName(sceneId ,selfId)
	local tblSort = function(a,b) return a[2] < b[2] end
	
	SendToplistKeyValue2GL(sceneId,selfId,WULONG_TOPLIST,costTime)

	----------------------------------------------------------
	--�б�Ϊ�գ�ֱ��׷��
	----------------------------------------------------------
	if WULONGCIDIAN_STEPIN_COUNT == 0 then
		WULONGCIDIAN_STEPIN_COUNT = 1
		
		--׷�ӵ�������
		WULONGCIDIAN_STEPIN_NAME[WULONGCIDIAN_STEPIN_COUNT] = name
		WULONGCIDIAN_STEPIN_TIME[WULONGCIDIAN_STEPIN_COUNT] = costTime
		
		--����
		return
	end
	
	----------------------------------------------------------
	--�������б��в����Ƿ����
	----------------------------------------------------------
	local tblTmp = {}
	local bFind = 0
	for i=1, WULONGCIDIAN_STEPIN_COUNT do
		
		tblTmp[i] = { WULONGCIDIAN_STEPIN_NAME[i], WULONGCIDIAN_STEPIN_TIME[i] }
		
		if WULONGCIDIAN_STEPIN_NAME[i] == name then
			if WULONGCIDIAN_STEPIN_TIME[i] > costTime then
				tblTmp[i][2] = costTime
			end

			bFind = 1
		end
	end
	
	----------------------------------------------------------
	--����ʱ��֮����������
	----------------------------------------------------------
	if bFind == 1 then
	
		--����ҵ���������Ȼ���������������
		sort(tblTmp,tblSort)
		
		WULONGCIDIAN_STEPIN_NAME = {}
		WULONGCIDIAN_STEPIN_TIME = {}

		for i=1, WULONGCIDIAN_STEPIN_COUNT do
			WULONGCIDIAN_STEPIN_NAME[i] = tblTmp[i][1]
			WULONGCIDIAN_STEPIN_TIME[i] = tblTmp[i][2]
		end

		--����
		return
	end
	
	----------------------------------------------------------
	--�滻����
	----------------------------------------------------------
	if WULONGCIDIAN_STEPIN_COUNT < 30 then
		
		WULONGCIDIAN_STEPIN_COUNT = WULONGCIDIAN_STEPIN_COUNT + 1
		
		WULONGCIDIAN_STEPIN_NAME[WULONGCIDIAN_STEPIN_COUNT] = name
		WULONGCIDIAN_STEPIN_TIME[WULONGCIDIAN_STEPIN_COUNT] = costTime
		
	else
		
		WULONGCIDIAN_STEPIN_NAME[WULONGCIDIAN_STEPIN_COUNT] = name
		WULONGCIDIAN_STEPIN_TIME[WULONGCIDIAN_STEPIN_COUNT] = costTime
	end
	
	----------------------------------------------------------
	--������֯����
	----------------------------------------------------------
	tblTmp = {}
	for i=1, WULONGCIDIAN_STEPIN_COUNT do
		tblTmp[i] = {WULONGCIDIAN_STEPIN_NAME[i],WULONGCIDIAN_STEPIN_TIME[i]}
	end
	
	sort(tblTmp,tblSort)
	
	WULONGCIDIAN_STEPIN_NAME = {}
	WULONGCIDIAN_STEPIN_TIME = {}
		
	for i=1, WULONGCIDIAN_STEPIN_COUNT do
		WULONGCIDIAN_STEPIN_NAME[i] = tblTmp[i][1]
		WULONGCIDIAN_STEPIN_TIME[i] = tblTmp[i][2]
	end
	
	--����
	return
end


function x310183_AfterAnswer(sceneId ,selfId)
	local step = GetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3])
	if step == 2 then
		if GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )> x310183_g_MaxCount then
			local costTime = x310183_GetValidTime() - GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
			x310183_PushToPool(sceneId ,selfId, costTime)
			SetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3], 3)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000 )
			x310183_ModifyCount(sceneId ,selfId, 1)
			SetQuestData( sceneId, selfId, MD_WULONG_LAST_ANSWER[1], MD_WULONG_LAST_ANSWER[2], MD_WULONG_LAST_ANSWER[3], 0 )
			return 1
		end
	elseif step == 3 then
		if GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )> x310183_g_MaxCount then
			local costTime = x310183_GetValidTime() - GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])
			x310183_PushToPool(sceneId ,selfId, costTime)
			return 2
		end
	end
	return 0
end

function x310183_NextNpcName(sceneId ,selfId)
	local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
	local name = ""
	if curCount > 20 then
		curCount = 1
	end

	if curCount>=1 and curCount<=20 then
			--local objId = FindMonsterByGUID(sceneId, x310183_g_NpcList[curCount])
			--name  = GetName(sceneId, objId)
			name = "@npc_"..x310183_g_NpcList[curCount]	
	end
	return name
end

function x310183_DisplayTimeCost(sceneId ,selfId)
local costTime = x310183_GetValidTime() - GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3])

AddQuestText(sceneId,format("\t���ֱ������Ѿ���ʱ#G%d#W��", costTime)	)
end

function x310183_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )
	if x310183_CheckValid( sceneId,selfId,npcId) < 0 then
		return
	end
	local step = GetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3])
	if idExt == 12005 then
		if step ~= 2 and step ~= 3 then
				return 
		end

		if GetQuestData(sceneId,selfId,MD_WULONG_GUOGUANLING[1], MD_WULONG_GUOGUANLING[2], MD_WULONG_GUOGUANLING[3]) == 1 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "���Ѿ��ù��������ˣ�");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���Ѿ��ù��������ˣ�",8,2)
			return 
		end

		SetQuestData(sceneId,selfId,MD_WULONG_GUOGUANLING[1], MD_WULONG_GUOGUANLING[2], MD_WULONG_GUOGUANLING[3], 1)

		local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "��ϲ��,�ش���ȷ��");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"��ϲ��,�ش���ȷ��",8,2)

		--������
		x310183_AddAward(sceneId ,selfId)
		local resultStr ="";
		local toggle = 0
		--����淨��־
			GamePlayScriptLog( sceneId, selfId, x310183_g_GameID_Right)
			x310183_ModifyCount(sceneId ,selfId, curCount+1)
			SetQuestData( sceneId, selfId, MD_WULONG_LAST_ANSWER[1], MD_WULONG_LAST_ANSWER[2], MD_WULONG_LAST_ANSWER[3], curCount )
			if x310183_AfterAnswer(sceneId ,selfId) ==1 then
				resultStr = format( "\t��ɹ��������һ�������ǵ���̭����������ٲμ�һ����̭��,ȥ��%s��ʼ��һ�ְɡ�", x310183_NextNpcName(sceneId ,selfId) )
				toggle = 1
			elseif x310183_AfterAnswer(sceneId ,selfId) == 2 then
				resultStr = "\t��ɹ�������������ǵ���̭����ȫ�������������ĵȴ���������һ�־�������ʤ������������16:00������"
				toggle = 1
				DelQuestNM( sceneId, selfId, 9335 )
			end
			-------------------------------------
			if toggle == 0 then
				resultStr = format( "\t��ϲ��ͨ����������Ŀ���,�����ȥ��%s�ˡ�", x310183_NextNpcName(sceneId ,selfId) )
			end

			BeginQuestEvent(sceneId);
			AddQuestText(sceneId,resultStr)							
			--if toggle == 1 then
				x310183_DisplayTimeCost(sceneId ,selfId)
			--end
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)

		return
	end

	if idExt == 12006 then
		if step ~= 2 and step ~= 3 then
				return 
		end

		local useHeiBai = GetQuestData(sceneId,selfId,MD_WULONG_HEIBAILING[1], MD_WULONG_HEIBAILING[2], MD_WULONG_HEIBAILING[3]) 
		if useHeiBai>= 3 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "���Ѿ��ù�3�κڰ����ˣ�");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���Ѿ��ù�3�κڰ����ˣ�",8,2)
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
		
		local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		if bRight == 1 then
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "��ϲ��,�ش���ȷ��");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"��ϲ��,�ش���ȷ��",8,2)

			--������
			x310183_AddAward(sceneId ,selfId)
			local resultStr ="";
			local toggle = 0
			--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310183_g_GameID_Right)
				x310183_ModifyCount(sceneId ,selfId, curCount+1)
				SetQuestData( sceneId, selfId, MD_WULONG_LAST_ANSWER[1], MD_WULONG_LAST_ANSWER[2], MD_WULONG_LAST_ANSWER[3], curCount )
				if x310183_AfterAnswer(sceneId ,selfId) ==1 then
					resultStr = format( "\t��ɹ��������һ�������ǵ���̭����������ٲμ�һ����̭��,ȥ��%s��ʼ��һ�ְɡ�", x310183_NextNpcName(sceneId ,selfId) )
					toggle = 1
				elseif x310183_AfterAnswer(sceneId ,selfId) == 2 then
					resultStr = "\t��ɹ�������������ǵ���̭����ȫ��������"
					toggle = 1
					DelQuestNM( sceneId, selfId, 9335 )
				end
				-------------------------------------
				if toggle == 0 then
					resultStr = format( "\t��ϲ��ͨ����������Ŀ���,�����ȥ��%s�ˡ�", x310183_NextNpcName(sceneId ,selfId) )
				end

				BeginQuestEvent(sceneId);
				AddQuestText(sceneId,resultStr)							
				--if toggle == 1 then
					x310183_DisplayTimeCost(sceneId ,selfId)
				--end
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
			return
		end

		if bRight == 0 then
			local lastTime = GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3] )
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t���ź��������ˣ�����ܴ���ʱ��������15�롣");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���ź��������ˣ�����ܴ���ʱ��������15�롣",8,2)
			SetQuestData(sceneId,selfId,MD_WULONG_ERROR_COUNT[1], MD_WULONG_ERROR_COUNT[2], MD_WULONG_ERROR_COUNT[3], GetQuestData(sceneId,selfId,MD_WULONG_ERROR_COUNT[1], MD_WULONG_ERROR_COUNT[2], MD_WULONG_ERROR_COUNT[3])+1)
			--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310183_g_GameID_Error)

				local errorCount = GetQuestData(sceneId,selfId,MD_WULONG_ERROR_COUNT[1], MD_WULONG_ERROR_COUNT[2], MD_WULONG_ERROR_COUNT[3])
				
			if errorCount == 1 then
				SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], lastTime-15 )
				Msg2Player(sceneId,selfId,"���ź���������һ�Ρ�",8,2)
				local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, lastIndex = QuestWulong_GetQuestionInfo(1)
				SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], lastIndex)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

					AddQuestText(sceneId,strDesc)
					x310183_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				
				return
			elseif errorCount >= 2 then
				SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000)
				SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], lastTime-15 )
				Msg2Player(sceneId,selfId,"���ź��������㶼�����,�㻹��ȥ��һλ������������ܿ���ɡ�",8,2)
				
				x310183_ModifyCount(sceneId ,selfId, curCount+1)
				SetQuestData( sceneId, selfId, MD_WULONG_LAST_ANSWER[1], MD_WULONG_LAST_ANSWER[2], MD_WULONG_LAST_ANSWER[3], curCount )
				local toggle = 0
				if x310183_AfterAnswer(sceneId ,selfId) ==1 then
					Msg2Player(sceneId,selfId,"��ɹ�������˱��ִ��⣬�����ǰ��һ�����������￪ʼ���ٲμ�һ�������ǵ����̭����",8,2)
					toggle = 1
				elseif x310183_AfterAnswer(sceneId ,selfId) == 2 then
					Msg2Player(sceneId,selfId,"��ɹ�������������ǵ���̭����ȫ��������",8,2)
					DelQuestNM( sceneId, selfId, 9335 )
					toggle = 2
				end

				if toggle == 0 then
					AddQuestText(sceneId,"���ź��������㶼�����,�㻹��ȥ��һλ������������ܿ���ѡ�")
					x310183_DisplayTimeCost(sceneId ,selfId)
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				elseif toggle == 1 then
					AddQuestText(sceneId,"\t��ɹ�������˱��ִ��⣬�����ǰ��һ�����������￪ʼ���ٲμ�һ�������ǵ����̭����")							
					x310183_DisplayTimeCost(sceneId ,selfId)
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				elseif toggle == 2 then
					AddQuestText(sceneId,"\t��ɹ�������������ǵ���̭����ȫ��������")
					x310183_DisplayTimeCost(sceneId ,selfId)
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				end
				
				return
			end

			return
		end

		return
	end

	if idExt == x310183_g_scriptId then 
		BeginQuestEvent(sceneId)	
			if step ~= 1 and step ~= 2 and step ~= 3 then
				return 
			end
		
			if step == 1 then
				SetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3], 2)
				SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000 )
				SetQuestData( sceneId, selfId, MD_WULONG_GUOGUANLING[1], MD_WULONG_GUOGUANLING[2], MD_WULONG_GUOGUANLING[3], 0 )
				SetQuestData( sceneId, selfId, MD_WULONG_HEIBAILING[1], MD_WULONG_HEIBAILING[2], MD_WULONG_HEIBAILING[3], 0 )
				x310183_ModifyCount(sceneId ,selfId, 1)
				SetQuestData( sceneId, selfId, MD_WULONG_LAST_ANSWER[1], MD_WULONG_LAST_ANSWER[2], MD_WULONG_LAST_ANSWER[3], 0 )
				SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], x310183_GetValidTime() )
			end

			 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
			
			if step == 3 and curCount > x310183_g_MaxCount then
				AddQuestText(sceneId,"\t���ź��������ǵ����̭���ѽ�����")							
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end

			 if step == 3 and curCount == 1 then
				SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], x310183_GetValidTime() )
			 end
			 
		if GetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3] ) ~= 60000 then
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestWulong_GetQuestionInfo(1, 1, GetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3] ))
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

				AddQuestText(sceneId,strDesc)
				x310183_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		else
			local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, lastIndex = QuestWulong_GetQuestionInfo(1)
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], lastIndex)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

				AddQuestText(sceneId,strDesc)
				x310183_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
		end
		
		return
	elseif idExt >= 12001 and idExt <= 12004 then
		if step ~= 2 and step ~= 3 then
				return 
		end

		 local curCount = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		 local lastAnswer = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER)

		if lastAnswer == idExt then --���
			SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000)
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t��ϲ��,�ش���ȷ��");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"��ϲ��,�ش���ȷ��",8,2)

			--������
			x310183_AddAward(sceneId ,selfId)
			local resultStr ="";
			local toggle = 0
			--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310183_g_GameID_Right)
				x310183_ModifyCount(sceneId ,selfId, curCount+1)
				SetQuestData( sceneId, selfId, MD_WULONG_LAST_ANSWER[1], MD_WULONG_LAST_ANSWER[2], MD_WULONG_LAST_ANSWER[3], curCount )
				if x310183_AfterAnswer(sceneId ,selfId) ==1 then
					resultStr = format( "\t��ɹ��������һ�������ǵ���̭����������ٲμ�һ����̭��,ȥ��%s��ʼ��һ�ְɡ�", x310183_NextNpcName(sceneId ,selfId) )
					toggle = 1
				elseif x310183_AfterAnswer(sceneId ,selfId) == 2 then
					resultStr = "\t��ɹ�������������ǵ���̭����ȫ��������"
					toggle = 1
					DelQuestNM( sceneId, selfId, 9335 )
				end
				-------------------------------------
				if toggle == 0 then
					resultStr = format( "\t��ϲ��ͨ����������Ŀ���,�����ȥ��%s�ˡ�", x310183_NextNpcName(sceneId ,selfId) )
				end

				BeginQuestEvent(sceneId);
				AddQuestText(sceneId,resultStr)							
				--if toggle == 1 then
					x310183_DisplayTimeCost(sceneId ,selfId)
				--end
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)

		else
			local lastTime = GetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3] )
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "\t���ź��������ˣ�����ܴ���ʱ��������15�롣");
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���ź��������ˣ�����ܴ���ʱ��������15�롣",8,2)
			SetQuestData(sceneId,selfId,MD_WULONG_ERROR_COUNT[1], MD_WULONG_ERROR_COUNT[2], MD_WULONG_ERROR_COUNT[3], GetQuestData(sceneId,selfId,MD_WULONG_ERROR_COUNT[1], MD_WULONG_ERROR_COUNT[2], MD_WULONG_ERROR_COUNT[3])+1)
			--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310183_g_GameID_Error)

				local errorCount = GetQuestData(sceneId,selfId,MD_WULONG_ERROR_COUNT[1], MD_WULONG_ERROR_COUNT[2], MD_WULONG_ERROR_COUNT[3])
				
			if errorCount == 1 then
				SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], lastTime-15 )
				Msg2Player(sceneId,selfId,"���ź���������һ�Ρ�",8,2)
				local strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer, lastIndex = QuestWulong_GetQuestionInfo(1)
				SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], lastIndex)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_WULONG_CUR_ANSWER,nAnswer+12000)

					AddQuestText(sceneId,strDesc)
					x310183_AddAnswerOption( sceneId,selfId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)							
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				
				return
			elseif errorCount >= 2 then
				SetQuestData(sceneId,selfId,MD_WULONG_LAST_QUESTION[1], MD_WULONG_LAST_QUESTION[2], MD_WULONG_LAST_QUESTION[3], 60000)
				SetQuestData(sceneId,selfId,MD_WULONG_TIME_BEGIN[1], MD_WULONG_TIME_BEGIN[2], MD_WULONG_TIME_BEGIN[3], lastTime-15 )
				Msg2Player(sceneId,selfId,"���ź��������㶼�����,�㻹��ȥ��һλ������������ܿ���ѡ�",8,2)
				x310183_ModifyCount(sceneId ,selfId, curCount+1)
				SetQuestData( sceneId, selfId, MD_WULONG_LAST_ANSWER[1], MD_WULONG_LAST_ANSWER[2], MD_WULONG_LAST_ANSWER[3], curCount )
				local toggle = 0
				if x310183_AfterAnswer(sceneId ,selfId) ==1 then
					toggle = 1
					Msg2Player(sceneId,selfId,"��ɹ�������˱��ִ��⣬�����ǰ��һ�����������￪ʼ���ٲμ�һ�������ǵ����̭����",8,2)
				elseif x310183_AfterAnswer(sceneId ,selfId) == 2 then
					toggle = 2
					Msg2Player(sceneId,selfId,"��ɹ�������������ǵ���̭����ȫ��������",8,2)
					DelQuestNM( sceneId, selfId, 9335 )
				end

				if toggle == 0 then
					AddQuestText(sceneId,"���ź��������㶼�����,�㻹��ȥ��һλ������������ܿ���ѡ�")
					x310183_DisplayTimeCost(sceneId ,selfId)
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				elseif toggle == 1 then
					AddQuestText(sceneId,"\t��ɹ�������˱��ִ��⣬�����ǰ��һ�����������￪ʼ���ٲμ�һ�������ǵ����̭����")							
					x310183_DisplayTimeCost(sceneId ,selfId)
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				elseif toggle == 2 then
					AddQuestText(sceneId,"\t��ɹ�������������ǵ���̭����ȫ��������")
					x310183_DisplayTimeCost(sceneId ,selfId)
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				end
				
				return
			end
		end
		
		return
	end

end

function x310183_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	return
end

function x310183_ProcQuestAbandon( sceneId, selfId,MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end
	DelQuestNM( sceneId, selfId, MissionId )
end


function x310183_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	local step = GetQuestData(sceneId,selfId,MD_WULONG_STEP[1], MD_WULONG_STEP[2], MD_WULONG_STEP[3]) 
	local npcIndex = 0
	if step == 1 then
		npcIndex = 1
	elseif step == 2 or step ==3 then
		local count = GetQuestData(sceneId,selfId,MD_WULONG_COUNT[1], MD_WULONG_COUNT[2], MD_WULONG_COUNT[3] )
		if count >20 then
			count = 20 
		end
		
		npcIndex = count
	end

	if npcIndex == 0 then
		return
	end
	--local npcId = FindMonsterByGUID(sceneId, x310183_g_NpcList[npcIndex])
	--local name = GetName(sceneId, npcId)	

	local str = "ͨ��@npc_"..x310183_g_NpcList[npcIndex].."�Ŀ���";	
	BeginQuestEvent(sceneId)		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							"�����ˡ������ǵ����",        -- ��������
							str,		--����Ŀ��
							"@npc_"..x310183_g_NpcList[npcIndex],			--����NPC
							"ͨ��@npc_"..x310183_g_NpcList[npcIndex].."�Ŀ���",               --������
							"\t����14��00������ǰ���󶼣�157��215����96��222����66��196������һ���ҵ�һ�������ˣ��μ������ǵ����̭����",	--��������
							""					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		
end