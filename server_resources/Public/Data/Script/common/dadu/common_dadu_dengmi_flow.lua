x310160_g_scriptId 		= 310160

--������Ϣ
x310160_g_DengmiInfo	= {
							{npcID=-1,GUID = 141506,nDengmi=-1},
							{npcID=-1,GUID = 141507,nDengmi=-1},
							{npcID=-1,GUID = 141508,nDengmi=-1},
							{npcID=-1,GUID = 141509,nDengmi=-1},
							{npcID=-1,GUID = 141510,nDengmi=-1},
						  }
--����ʱ����Ϣ
x310160_g_DengmiTimer	= { nStart = -1,nIndex = -1 }
x310160_g_DengmiArray 	= {}

--�������
x310160_g_TimerInterval	= 59*1000 		--����
x310160_g_MaxCount		= 10			--���ܳ���31

x310160_g_GameId		= 1007			--�淨ID
x310160_g_LimitLevel	= 40			--��ͼ���
x310160_g_LimitSceneId	= 0				--�淨���ڳ��������������淨����������һ����Ӧ��Ϊ�Ƿ�

x310160_g_StartDay		= -1			--�������ڣ����ⴥ�����������ڱ���һ�²ſɼ���

x310160_g_GameID_Right	= 961
x310160_g_GameID_Error	= 962

----------------------------------------------------------------------------------------------
--���½��������Ϣ
----------------------------------------------------------------------------------------------
--���飬����������
x310160_g_ExpBonus		= 500	--�������� ��ʽ=level*exp
x310160_g_ExpBonus1		= 650 --�������� ��ʽ=level*exp
x310160_g_ShengWang		= 0			--�����������̶�ֵ
x310160_g_MoneyBonus	= 15	--������������ʽ=level*money

--�����Ʒ
x310160_g_ItemGL		= 20			--�������
x310160_g_ItemList		= { 			--��Ʒ�б�
							{12030107,1}			
						  }

--����ĳ������ʱ�Ľ�����Ϣ
x310160_g_MissionGL		= 50			--�������
x310160_g_MissionId		= 1482			--����ID
x310160_g_MissionBonus	= 13015012		--���佱��

----------------------------------------------------------------------------------------------
--�����Ч��
----------------------------------------------------------------------------------------------
function x310160_CheckValid( sceneId,selfId)

	local level = GetLevel(sceneId,selfId)
	if level<x310160_g_LimitLevel then
		return -1
	end
	
	if sceneId ~= x310160_g_LimitSceneId then
		return -2
	end
	
	return 1

end

----------------------------------------------------------------------------------------------
--�������ʱ���Ƿ���Ч
----------------------------------------------------------------------------------------------
function x310160_IsStartTimeValid()

	local h,m = x310160_GetValidTimeHourMin()
	
	local cur  = h*60  + m
	local from = 19*60 + 00
	local to   = 20*60 + 00
	
	if cur < from or cur > to then
		
		--����־
		local strMsg = format("DML:<Info>x310160_IsStartTimeValid starttime invalid started  h=%d,m=%d", h, m )
    	WriteLog( 1, strMsg )
		return 0
	end
	
	return 1

end

----------------------------------------------------------------------------------------------
--���ÿ�ʼ����
----------------------------------------------------------------------------------------------
function x310160_SetStartDay( nDay )

	if x310160_g_StartDay ~= -1 then
		return
	end
	
	x310160_g_StartDay = nDay

end

----------------------------------------------------------------------------------------------
--�����ʼ������
----------------------------------------------------------------------------------------------
function x310160_ClearStartDay()
	x310160_g_StartDay = -1
end

----------------------------------------------------------------------------------------------
--�Ƿ������
----------------------------------------------------------------------------------------------
function x310160_IsNextDay()
	
	local curDay = GetDayOfYear()
	
	if x310160_g_StartDay ~= curDay then
		return 1
	end
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--�ж�����Ƿ��ڲµ���
----------------------------------------------------------------------------------------------
function x310160_IsPlayerGaming( sceneId,selfId )
	
	local nNpcID = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG)
	if nNpcID <= 0 then
		return -1
	end
	
	--�����Ч����
	if GetDist( sceneId, selfId, nNpcID,3 ) > 3 then
		
		--�����־�����Ч��ʱ������������
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
		
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
		
		return -1
	end 
	
	return 1
end

----------------------------------------------------------------------------------------------
--�ж���Ҳµ����Ƿ��������
----------------------------------------------------------------------------------------------
function x310160_IsPlayerGamingFull( sceneId,selfId )

	local nDate   = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1], MD_QUEST_DENGMI_DATE[2], MD_QUEST_DENGMI_DATE[3] )
	local nCount  = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3])

	local nCurDay = GetDayOfYear()
	if nCurDay == nDate then
		if nCount >= x310160_g_MaxCount then
			return 1
		end
	end

	return 0
end

----------------------------------------------------------------------------------------------
--����NPC
----------------------------------------------------------------------------------------------
function x310160_FindNpc(sceneId,npcId)
	
	for n,item in x310160_g_DengmiInfo do
		if npcId == item.npcID then
			return n
		end
	end
	
	return -1
							
end

----------------------------------------------------------------------------------------------
--��鲢����������
----------------------------------------------------------------------------------------------
function x310160_CheckAndResetPlayerGameInfo( sceneId,selfId )

	local nDay = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1],MD_QUEST_DENGMI_DATE[2],MD_QUEST_DENGMI_DATE[3])	
	local nCurDay = GetDayOfYear()
	if nCurDay ~= nDay then
		--���ý���µ�����Ϣ
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1],MD_QUEST_DENGMI_DATE[2],MD_QUEST_DENGMI_DATE[3],nCurDay)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3],0)	
		
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[1][1],MD_QUEST_DENGMI_NPC[1][2],MD_QUEST_DENGMI_NPC[1][3],-1)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[2][1],MD_QUEST_DENGMI_NPC[2][2],MD_QUEST_DENGMI_NPC[2][3],-1)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[3][1],MD_QUEST_DENGMI_NPC[3][2],MD_QUEST_DENGMI_NPC[3][3],-1)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[4][1],MD_QUEST_DENGMI_NPC[4][2],MD_QUEST_DENGMI_NPC[4][3],-1)
		SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[5][1],MD_QUEST_DENGMI_NPC[5][2],MD_QUEST_DENGMI_NPC[5][3],-1)
	end
end

----------------------------------------------------------------------------------------------
--����������Ե�����£��Żᴥ��
----------------------------------------------------------------------------------------------
function x310160_GiveBonus( sceneId,selfId )

	--�δ����
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		return
	end
	
	--��������Ч��
	if x310160_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	local level = GetLevel(sceneId,selfId)
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "ErrorName"
	end
	
	--������
	if x310160_g_ExpBonus > 0 then
		local level = GetLevel(sceneId,selfId)
	if level <70 then
		local bonusExp = level*x310160_g_ExpBonus
		AddExp(sceneId,selfId,bonusExp)
		
		local msg = format("#Y���#R����%d��#Y�Ľ���",bonusExp)
		
		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
	else
		local bonusExp = level*x310160_g_ExpBonus1
		AddExp(sceneId,selfId,bonusExp)
				
		local msg = format("#Y���#R����%d��#Y�Ľ���",bonusExp)
		
		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
    LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
  end
	end
	
	--������
	if x310160_g_ShengWang > 0 then
		local bonusShengWang = GetShengWang( sceneId,selfId) + x310160_g_ShengWang
		SetShengWang( sceneId,selfId,bonusShengWang)
		
		local msg = format("�������%d������ֵ�Ľ���",x310160_g_ShengWang)
		
		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
	end
	
	--������
	if x310160_g_MoneyBonus > 0 then
		local bonusMoney = level*x310160_g_MoneyBonus
		local buff 	=	9011
		local buff1 =	9013
		local buff2 =	9012
		if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
			AddMoney(sceneId,selfId,0,bonusMoney,x310160_g_scriptId)
		else
			AddMoney(sceneId,selfId,1,bonusMoney,x310160_g_scriptId)
		end
	end
	
	--����Ʒ
	local nItemCount = getn(x310160_g_ItemList)
	if nItemCount > 0 and x310160_g_ItemGL > 0  then

		--����Ƿ���Ի����Ʒ
		local bGet = random(1,100)
		if bGet <= x310160_g_ItemGL then
			
			--�����õ���Ʒ
			local bGetItem = random(1,nItemCount)
			
			local itemInfo = x310160_g_ItemList[bGetItem]
			
			BeginAddItem(sceneId)
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
            AddItem( sceneId, itemInfo[1],itemInfo[2] )
            else
            AddBindItem( sceneId, itemInfo[1],itemInfo[2] )
            end
            local ret = EndAddItem(sceneId,selfId)
            if ret > 0 then
            	
                AddItemListToPlayer(sceneId,selfId)
                
                --local msg = format("#Y�������#G@item_%d#Y�Ľ���",itemInfo[1],itemInfo[2])
			--	LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
		       -- LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
		       -- LuaAllScenceM2Wrold( sceneId, format( "#G�������ˣ�#Y%s#G�ڲµ�������������һ��#R�ر�ͼ#G��", name ), 1, 1)
		    else
		    	LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 2,1)
		        LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 3,1)
            end
		end
	end
	-- ���һö�󶼼��껪���ֱ�
    BeginAddItem( sceneId)
    AddItem( sceneId, 11990117, 1)
    if EndAddItem( sceneId, selfId) <= 0 then
        Msg2Player( sceneId, selfId, "��ı����������޷����#{_ITEM11990117}������", 8, 2)
    else
        AddItemListToPlayer( sceneId, selfId)
    end
	--��������Ʒ
	if IsHaveQuestNM( sceneId, selfId, x310160_g_MissionId) == 1 then
		
		--�ж������Ƿ����
		local misIndex = GetQuestIndexByID(sceneId,selfId,x310160_g_MissionId)
		if misIndex < 0 then
			return
		end
		
		--������ɣ�����
		if GetQuestParam( sceneId,selfId,misIndex,7) == 1 then
			return
		end
		
		--������
		local bGet = random(1,100)
		if bGet <= x310160_g_MissionGL then
			
			BeginAddItem(sceneId)
            AddItem( sceneId, x310160_g_MissionBonus,1 )
            local ret = EndAddItem(sceneId,selfId)
            if ret > 0 then
                AddItemListToPlayer(sceneId,selfId)
                
                --������ø���ʾ������ű�����������ʾ
		    else
		    	LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 2,1)
		        LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 3,1)
            end
		end
	end
end

----------------------------------------------------------------------------------------------
--������ʱ��
----------------------------------------------------------------------------------------------
function x310160_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5 )

	--��ر�
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		return		
	end
	
	--�����Ѿ���ʼ�����ǻ�û�н�������ô����Ϊ��ֻ����־
	if x310160_g_DengmiTimer.nStart >= 0 then
		--����־
		local strMsg = format("DML:<Info>x310160_OnTimerDoingStart already started sceneId = %d, actId=%d", sceneId,actId )
    	WriteLog( 1, strMsg )		
		return
	end
	
	--����Ŀ�ʼʱ���Ƿ���Ч
	if x310160_IsStartTimeValid() == 0 then
		
		--����־
		local strMsg = format("DML:<Info>x310160_OnTimerDoingStart starttime invalid sceneId = %d, actId=%d", sceneId,actId )
    	WriteLog( 1, strMsg )		
		return
	end

	--ȡ�õ��ո���
	local nCount = QuestDengmi_GetQuestionCount()
	if nCount > 0 then

		--��ʼ��
		for i,item in x310160_g_DengmiInfo do
			item.nDengmi = -1
			item.npcID = FindMonsterByGUID(sceneId,item.GUID)
			
			--����־
			local strMsg = format("DML:<Info>x310160_OnTimerDoingStart Initialise npc npcId = %d,GUID=%d", item.npcID, item.GUID )
		    WriteLog( 1, strMsg )		
			
		end
		
		x310160_g_DengmiTimer.nStart = -1
		x310160_g_DengmiTimer.nIndex = 0
		
		--������������
		x310160_SetStartDay( GetDayOfYear() )
		
		SetSystemTimerTick( sceneId, x310160_g_scriptId, "ProcTiming", actId, 1000 ) --5���ʼ
	end
	
	--����־
	local strMsg = format("DML:<Info>x310160_OnTimerDoingStart sceneId = %d, count=%d, actId=%d", sceneId, nCount,actId )
    WriteLog( 1, strMsg )
	
end

----------------------------------------------------------------------------------------------
--�������
----------------------------------------------------------------------------------------------
function x310160_ClearDengmi(sceneId)

	--������Ϣ
	x310160_g_DengmiInfo	= {
								{npcID=-1,GUID = 141506,nDengmi=-1},
								{npcID=-1,GUID = 141507,nDengmi=-1},
								{npcID=-1,GUID = 141508,nDengmi=-1},
								{npcID=-1,GUID = 141509,nDengmi=-1},
								{npcID=-1,GUID = 141510,nDengmi=-1},
						  	  }
	
	x310160_g_DengmiTimer	= { nStart = -1,nIndex = -1 }
	x310160_g_DengmiArray 	= {}
	
	x310160_ClearStartDay()

	local nHumanCount = GetScenePlayerCount( sceneId )
	for i=0,nHumanCount do

		local objId = GetScenePlayerObjId(sceneId,i)
		if IsPlayerStateNormal(sceneId,objId) == 1 and x310160_IsPlayerGaming(sceneId,objId) == 1 then
		
			--֪ͨ�ͻ���������
			QuestDengmi_SendDengmiInfo( sceneId, objId, -1, -1 )
			
			SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_NPC_FLAG,0)
			SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_CUR_DENGMI,0)
			
			--���¶Ի�������
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�������̳���ջ�����ˣ�")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,objId,objId)
			
		end
	end
	
end

----------------------------------------------------------------------------------------------
--���Tick
----------------------------------------------------------------------------------------------
function x310160_ProcTiming( sceneId, actId, uTime )


	----------------------------------------------------------------------------------------------
	--��ر�
	----------------------------------------------------------------------------------------------
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		
		--��������Ϣ
		x310160_ClearDengmi(sceneId)		
		
		--��¼��־
		local strMsg = format("DML:<Info>x310160_ProcTiming GM close sceneId = %d", sceneId )
    	WriteLog( 1, strMsg )			

		return		
	end
	
	----------------------------------------------------------------------------------------------
	--������
	----------------------------------------------------------------------------------------------
	if x310160_IsNextDay() == 1 then
		
		--��������Ϣ
		x310160_ClearDengmi(sceneId)
		
		--����־
		local strMsg = format("DML:<Info>x310160_ProcTiming nextday close sceneId = %d", sceneId )
    	WriteLog( 1, strMsg )
    	
    	return 
	end
	
	----------------------------------------------------------------------------------------------
	--��������
	----------------------------------------------------------------------------------------------
	local nCount = QuestDengmi_GetQuestionCount()
	if x310160_g_DengmiTimer.nIndex >= 370 then
		
		--��������Ϣ
		x310160_ClearDengmi(sceneId)
		
		--���Ȼ����
		local strMsg = format("DML:<Info>x310160_ProcTiming party close sceneId = %d", sceneId )
    	WriteLog( 1, strMsg )			
				
		return
	end

	----------------------------------------------------------------------------------------------
	--���õ���ʱ�͵�ǰ�����Ϣ
	----------------------------------------------------------------------------------------------
	x310160_g_DengmiTimer.nStart = x310160_GetValidTime()
	x310160_g_DengmiTimer.nIndex = x310160_g_DengmiTimer.nIndex + 1
	
	for i,item in x310160_g_DengmiInfo do
		
		item.nDengmi = random(0,nCount-1)
		local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestDengmi_GetQuestionInfo(item.nDengmi)
		
		x310160_g_DengmiArray[i] = {}		
		x310160_g_DengmiArray[i].id = id + 100000		
		x310160_g_DengmiArray[i].strDesc = strDesc
		x310160_g_DengmiArray[i].strAnswer1 = strAnswer1
		x310160_g_DengmiArray[i].strAnswer2 = strAnswer2
		x310160_g_DengmiArray[i].strAnswer3 = strAnswer3
		x310160_g_DengmiArray[i].strAnswer4 = strAnswer4
		x310160_g_DengmiArray[i].nAnswer = nAnswer + 11000
		
		--���Ȼ����
		local strMsg = format("DML:<Info>x310160_ProcTiming new dengmi sceneId=%d,i=%d,dengmi=%d,<%s>,<%s>,<%s>,<%s>,<%s>,%d", 
							  sceneId,i,id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer )
    	WriteLog( 1, strMsg )
	end
	
	----------------------------------------------------------------------------------------------
	--��ʼͬ��
	----------------------------------------------------------------------------------------------
	local nHumanCount = GetScenePlayerCount( sceneId )
	for i=0,nHumanCount do

		local objId = GetScenePlayerObjId(sceneId,i)
		if IsPlayerStateNormal(sceneId,objId) == 1 and x310160_IsPlayerGaming(sceneId,objId) == 1 then

			--��֤����Ƿ��ǽ������������
			local nDate   = GetQuestData(sceneId,objId,MD_QUEST_DENGMI_DATE[1],MD_QUEST_DENGMI_DATE[2],MD_QUEST_DENGMI_DATE[3])
			local nCount  = GetQuestData(sceneId,objId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3])
			local nNpcID  = GetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_NPC_FLAG)
			local nCurDay = GetDayOfYear()
			
			
			if x310160_IsPlayerGamingFull(sceneId,objId) == 1 then
					
				--֪ͨ�ͻ���������
				QuestDengmi_SendDengmiInfo( sceneId, objId, -1, -1 )
				
				SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_NPC_FLAG,0)
				SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_CUR_DENGMI,0)
				
				--���¶Ի�������
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t�������Ѿ�����10�ε����ˣ��������ʱ�������ɡ�")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,objId,nNpcID)
				
			else
				
				for n,item in x310160_g_DengmiInfo do
					--�ҵ���ҽ�����NPC
					if nNpcID == item.npcID then
							
						--�ڴ�����ж�λ����
						local dm = x310160_g_DengmiArray[n]
						
						--��ͻ���ͬ����Ŀ��������Ŀ����ʱ
						local nTime = x310160_g_TimerInterval/1000 - (x310160_GetValidTime() - x310160_g_DengmiTimer.nStart)
						if nTime > 0 then
							QuestDengmi_SendDengmiInfo( sceneId, objId, x310160_g_DengmiTimer.nIndex, nTime )
						end
						
						
						SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_NPC_FLAG,nNpcID)
						SetPlayerRuntimeData(sceneId,objId,RD_QUEST_DENGMI_CUR_DENGMI,dm.id)
						
						--���¶Ի�������
						BeginQuestEvent(sceneId)
							
							AddQuestText(sceneId,dm.strDesc)
							x310160_AddDengmiAnswerOption( sceneId, 
										   				   dm.strAnswer1, 
										   				   dm.strAnswer2, 
										   				   dm.strAnswer3, 
										   				   dm.strAnswer4 )
														
						EndQuestEvent(sceneId)
						DispatchQuestEventList(sceneId,objId,nNpcID)
						
						break
					end
				end
			end
		end
	end
	
	----------------------------------------------------------------------------------------------
	--������һ��Tick
	----------------------------------------------------------------------------------------------
	SetSystemTimerTick( sceneId, x310160_g_scriptId, "ProcTiming", actId, x310160_g_TimerInterval )
end


----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x310160_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--֪ͨ�ͻ����������
	QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
				
	SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
	SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
	
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		return
	end
	
    AddQuestNumText(sceneId,x310160_g_scriptId,"��Ҫ�µ���",3,x310160_g_scriptId);
        
end

----------------------------------------------------------------------------------------------
--��ӵ��մ�ѡ��
----------------------------------------------------------------------------------------------
function x310160_AddDengmiAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)

	--������ѡ��
	local arr_answer = { {strAnswer1,11001,0},{strAnswer2,11002,0},{strAnswer3,11003,0},{strAnswer4,11004,0} }
	for i=1,4 do
		
		local nCount = getn(arr_answer)
		local n = random(1,nCount)
		while arr_answer[n][3] == 1 do
			n = random(1,nCount)
		end
		
		arr_answer[n][3] = 1
		
		AddQuestNumText(sceneId,x310160_g_scriptId,arr_answer[n][1],3,arr_answer[n][2] )
	end
	
end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x310160_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )

	----------------------------------------------------------------------------------------------
	--�δ����
	----------------------------------------------------------------------------------------------
	if GetGameOpenById(x310160_g_GameId) ~= 1 then
		
		--֪ͨ�ͻ����������
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
		
		--���������ʾ
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"���ջ��Ѿ��رգ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	----------------------------------------------------------------------------------------------
	--��������Ч��
	----------------------------------------------------------------------------------------------
	if x310160_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	----------------------------------------------------------------------------------------------
	--���û�п�ʼ��ʱ�򣬲�������������������
	----------------------------------------------------------------------------------------------
	if x310160_g_DengmiTimer.nStart < 0 then
		
		--֪ͨ�ͻ����������
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
		
		--���������ʾ
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t���ջỹû��ʼ�أ����ļ���\n\t#G��ÿ�����ϵ�19��30--24��00���ջῪ�ţ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	----------------------------------------------------------------------------------------------
	--������
	----------------------------------------------------------------------------------------------
	if x310160_IsNextDay() == 1 then
		
		--֪ͨ�ͻ����������
		QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
		SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
		
		--���������ʾ
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t���ջỹû��ʼ�أ����ļ���\n\t#G��ÿ�����ϵ�19��30--24��00���ջῪ�ţ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	

	if idExt == x310160_g_scriptId then
		
		
		----------------------------------------------------------------------------------------------
		--��ʼ����
		----------------------------------------------------------------------------------------------
		
		local nFind = x310160_FindNpc(sceneId,npcId)
		if nFind > 0 then
			
			--��֤�Ƿ�����
			if x310160_IsPlayerGamingFull( sceneId,selfId ) == 1 then
					
				--֪ͨ�ͻ���������
				QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
							
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
				
				--���¶Ի�������
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t�������Ѿ�����10�ε����ˣ����������ɡ�")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
				
			--��ǰ���������Ƿ��Ѿ������NPC�������
			local nPreIndex = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3])
			if nPreIndex == x310160_g_DengmiTimer.nIndex then
				
				--���ô�����Ϣ
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,npcId)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,x310160_g_DengmiTimer.nIndex)
				
				--��ͻ���ͬ����Ŀ���������յ���ʱ
				local nTime = x310160_g_TimerInterval/1000 - (x310160_GetValidTime() - x310160_g_DengmiTimer.nStart)
				if nTime > 0 then
					QuestDengmi_SendDengmiInfo( sceneId, selfId, x310160_g_DengmiTimer.nIndex, nTime )
				end
				
				
				--���¶Ի�������
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"�������ȥ�ҵĽ�������µ��գ�������������ȴ���һ�����գ�")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				
				--��¼��־
				local name = GetName(sceneId,selfId)
				if name == nil then
					name = "Error"
				end
				local strMsg = format("DML:<Info>x310160_ProcEventEntry 000 sceneId=%d,name=%s,npcIndex=%d,preIndex=%d,index=%d", 
							  		   sceneId, name, nFind, nPreIndex, x310160_g_DengmiTimer.nIndex)
    			WriteLog( 1, strMsg )
				return
			end			
			
			
			--��鲢�������������
			x310160_CheckAndResetPlayerGameInfo( sceneId,selfId )
			

			--�ڴ�����ж�λ����
			local dm = x310160_g_DengmiArray[nFind]
			
			--����npcid�ʹ�����
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,npcId)
			SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,dm.id)

			
			--��ͻ���ͬ����Ŀ���������յ���ʱ
			local nTime = x310160_g_TimerInterval / 1000 - ( x310160_GetValidTime() - x310160_g_DengmiTimer.nStart )
			if nTime > 0 then
				QuestDengmi_SendDengmiInfo( sceneId, selfId, x310160_g_DengmiTimer.nIndex, nTime )
			end
			
			
			--���¶Ի�������
			BeginQuestEvent(sceneId)
				
				AddQuestText(sceneId,dm.strDesc)
				x310160_AddDengmiAnswerOption( sceneId, 
											   dm.strAnswer1, 
											   dm.strAnswer2, 
											   dm.strAnswer3, 
											   dm.strAnswer4 )
											
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
		end
		
	elseif idExt >= 11001 and idExt <= 11004 then
		
		----------------------------------------------------------------------------------------------
		--���ѡ�е�ĳ������
		----------------------------------------------------------------------------------------------
		
		--��֤�Ƿ�����
		local nPreDate  = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1],MD_QUEST_DENGMI_DATE[2],MD_QUEST_DENGMI_DATE[3])
		local nPreCount = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3])
		
		local nDate = GetDayOfYear()
		if nDate == nPreDate then
			
			--�����ղµ��մ����Ƿ�����
			if nPreCount >= x310160_g_MaxCount then
				
				--֪ͨ�ͻ����������
				QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
							
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
				
				--���¶Ի�������
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t�������Ѿ�����10�ε����ˣ����������ɡ�")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
			
			--ȡ��NPC��Index
			local nFind = 0
			for i,item in x310160_g_DengmiInfo do
				if item.npcID == npcId then
					nFind = i
					break
				end
			end
			
			if nFind <= 0 or nFind >= 6 then
				return
			end
			
			--ȡ����Ŀ��Ϣ
			local dm = x310160_g_DengmiArray[nFind]
			
			--���Ի�NPC
			local preNpcId= GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG)
			if npcId ~= preNpcId then
				
				--֪ͨ�ͻ����������
				QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
							
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
				SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
				
				--�Ի�NPCû����֤ͨ��
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t���ջ��Ѿ������������������ɡ�")				
				EndQuestEvent(sceneId)
				DispatchQuestEventList(sceneId,selfId,npcId)
				return
			end
			
			--���NPC��Ŀ�Ѿ�����������ٴ�
			local nPreIndex = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3])
			if nPreIndex == x310160_g_DengmiTimer.nIndex then
				return
			end
			
			
			--��ͻ���ͬ����Ŀ���������յ���ʱ
			local nTime = x310160_g_TimerInterval / 1000 - ( x310160_GetValidTime() - x310160_g_DengmiTimer.nStart )
			if nTime > 0 then
				QuestDengmi_SendDengmiInfo( sceneId, selfId, x310160_g_DengmiTimer.nIndex, nTime )
			end
			
			
			--�����Ŀ�����Ƿ�����һ��
			local nId = GetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI)
			if nId ~= dm.id then
				
				local nSelfPreCount = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3]) + 1
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3],nSelfPreCount)
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3],x310160_g_DengmiTimer.nIndex)
				
				--�����ʾ
				if x310160_IsPlayerGamingFull(sceneId,selfId) == 1 then
					
					--֪ͨ�ͻ���������
					QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
					
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,"\t���ź�����´���Ŷ��",name,3,1)
					LuaScenceM2Player( sceneId,selfId,"\t���ź�����´���Ŷ��",name,2,1)
					
					--���¶Ի�������
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t���ź�����´���Ŷ��" )
						AddQuestText(sceneId,"\t�������Ѿ�����10�ε����ˣ��������ʱ�������ɡ�")
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				else
					
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,format("\t���ź�����´���Ŷ�������㻹���Բ�%d�Ρ�",x310160_g_MaxCount - nSelfPreCount ),name,3,1)
					LuaScenceM2Player( sceneId,selfId,format("\t���ź�����´���Ŷ�������㻹���Բ�%d�Ρ�",x310160_g_MaxCount - nSelfPreCount ),name,2,1)
					
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,format("\t���ź�����´���Ŷ�������㻹���Բ�%d�Ρ�\n\t����Լ�����������ȴ����ո��£�����ȥ�ҵ�����������������µ��ա�",x310160_g_MaxCount - nSelfPreCount ) )				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
					
				end
				
				--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310160_g_GameID_Error)
				
				--��¼��־
				local name = GetName(sceneId,selfId)
				if name == nil then
					name = "Error"
				end
				local strMsg = format("DML:<Info>x310160_ProcEventEntry 001 name=%s,npcIndex=%d,index=%d",name,nFind,x310160_g_DengmiTimer.nIndex)
				WriteLog( 1, strMsg )
				return
			end
			
			
			--��Ŀ��ż��ͨ���ˣ������ټ����Ƿ���ȷ
			if dm.nAnswer == idExt then
				
				
				--�����
				
				local nSelfPreCount = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3]) + 1
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3],nSelfPreCount)
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3],x310160_g_DengmiTimer.nIndex)
				
				--�����ʾ
				if x310160_IsPlayerGamingFull(sceneId,selfId) == 1 then
					
					--֪ͨ�ͻ���������
					QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
					
					--�����ʾ
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,"\t��ϲ��¶��˵��ա�",name,3,1)
					LuaScenceM2Player( sceneId,selfId,"\t��ϲ��¶��˵��ա�",name,2,1)
					
					--���¶Ի�������
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t��ϲ��¶��˵��ա�" )
						AddQuestText(sceneId,"\t�������Ѿ�����10�ε����ˣ��������ʱ�������ɡ�")	
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				else
				
					--�����ʾ
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,format("\t��ϲ��¶��˵��գ�����컹���Բ�%d�Ρ�",x310160_g_MaxCount - nSelfPreCount ),name,3,1)
					LuaScenceM2Player( sceneId,selfId,format("\t��ϲ��¶��˵��գ�����컹���Բ�%d�Ρ�",x310160_g_MaxCount - nSelfPreCount ),name,2,1)
					
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,format("\t��ϲ��¶��˵��գ�����컹���Բ�%d�Ρ�\n\t����Լ�����������ȴ����ո��£�����ȥ�ҵ�����������������µ��ա�",x310160_g_MaxCount - nSelfPreCount ) )				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				
				end
				
				--������
				x310160_GiveBonus( sceneId,selfId )
				CallScriptFunction( 256224, "Finishdengmi", sceneId, selfId)	
				
				--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310160_g_GameID_Right)
				 
				 --��¼��־
				local name = GetName(sceneId,selfId)
				if name == nil then
					name = "Error"
				end
				local strMsg = format("DML:<Info>x310160_ProcEventEntry 002 name=%s,npcIndex=%d,index=%d",name,nFind,x310160_g_DengmiTimer.nIndex)
				WriteLog( 1, strMsg )
				
				return
				
			else
				
				--�����
				
				local nSelfPreCount = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3]) + 1
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3],nSelfPreCount)
				SetQuestData(sceneId,selfId,MD_QUEST_DENGMI_NPC[nFind][1],MD_QUEST_DENGMI_NPC[nFind][2],MD_QUEST_DENGMI_NPC[nFind][3],x310160_g_DengmiTimer.nIndex)
				
				--�����ʾ
				if x310160_IsPlayerGamingFull(sceneId,selfId) == 1 then
					
					--֪ͨ�ͻ���������
					QuestDengmi_SendDengmiInfo( sceneId, selfId, -1, -1 )
					
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_NPC_FLAG,0)
					SetPlayerRuntimeData(sceneId,selfId,RD_QUEST_DENGMI_CUR_DENGMI,0)
					
					--�����ʾ
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,"\t���ź�����´���Ŷ��",name,3,1)
					LuaScenceM2Player( sceneId,selfId,"\t���ź�����´���Ŷ��",name,2,1)
					
					--���¶Ի�������
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t���ź�����´���Ŷ��")	
						AddQuestText(sceneId,"\t�������Ѿ�����10�ε����ˣ��������ʱ�������ɡ�")				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
				else
				
					--�����ʾ
					local name = GetName(sceneId,selfId)
					LuaScenceM2Player( sceneId,selfId,format("\t���ź�����´���Ŷ�������㻹���Բ�%d�Ρ�",x310160_g_MaxCount - nSelfPreCount ),name,3,1)
					LuaScenceM2Player( sceneId,selfId,format("\t���ź�����´���Ŷ�������㻹���Բ�%d�Ρ�",x310160_g_MaxCount - nSelfPreCount ),name,2,1)
					
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,format("\t���ź�����´���Ŷ�������㻹���Բ�%d�Ρ�\n\t����Լ�����������ȴ����ո��£�����ȥ�ҵ�����������������µ��ա�",x310160_g_MaxCount - nSelfPreCount ) )				
					EndQuestEvent(sceneId)
					DispatchQuestEventList(sceneId,selfId,npcId)
					
				end
				
				--����淨��־
				GamePlayScriptLog( sceneId, selfId, x310160_g_GameID_Error)
				
				--��¼��־
				local name = GetName(sceneId,selfId)
				if name == nil then
					name = "Error"
				end
				local strMsg = format("DML:<Info>x310160_ProcEventEntry 003 name=%s,npcIndex=%d,index=%d",name,nFind,x310160_g_DengmiTimer.nIndex)
				WriteLog( 1, strMsg )
				return
				
			end			
			
		else
			
			--������ڲ��ԵĻ�����������ڴ��⣬˵��ʲô���?�����ﲻ��Ӧ
			return
			
		end
		
	end
		    
end


function x310160_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310160_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310160_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310160_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x310160_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x310160_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x310160_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x310160_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x310160_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

----------------------------------------------------------------------------------------------
--ȡ����Ч��ʱ��,�������ʱ���飬�������ȡʱ��Ĳ��5�����С��0�����϶���Ч������ȡ
--���ս����ȡʱ��������ϳ�������������������ͬ�ļ��
----------------------------------------------------------------------------------------------
function x310160_GetValidTime()

	local n1 = GetCurrentTime()
	local n2 = GetCurrentTime()
	
	local nResult = n2 - n1 
	while nResult > 5 or nResult < 0 do
		n1 = GetCurrentTime()
		n2 = GetCurrentTime()
		
		nResult = n2 - n1 
		
		--��¼��־
		local strMsg = format("DML:<Error>x310160_GetValidTime n1=%d,n2=%d",n1,n2)
		WriteLog( 1, strMsg )	
		
	end
	
	return n2
end

----------------------------------------------------------------------------------------------
--ȡ����Ч��Сʱ����
----------------------------------------------------------------------------------------------
function x310160_GetValidTimeHourMin()

	local h,m,s = GetHourMinSec()	
	return h,m

end