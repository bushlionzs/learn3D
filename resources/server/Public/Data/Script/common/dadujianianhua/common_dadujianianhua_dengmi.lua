x310163_g_scriptId 		= 310163

--������Ϣ
x310163_g_DengmiInfo	= {
							{index=1,npcID=-1,GUID = 141506,Done=0},
							{index=2,npcID=-1,GUID = 141507,Done=0},
							{index=3,npcID=-1,GUID = 141508,Done=0},
							{index=4,npcID=-1,GUID = 141509,Done=0},
						  }
						  
--���ձ��
x310163_g_DengmiNoMD	= {
							MD_DENGMI_NO1,
							MD_DENGMI_NO2,
							MD_DENGMI_NO3,
							MD_DENGMI_NO4,
						  }



--����ʱ����Ϣ
x310163_g_DengmiTimer	= { nStart = -1,nIndex = -1 }
x310163_g_DengmiArray 	= {}

--�������

x310163_g_GameId		= 1007			--�淨ID
x310163_g_LimitLevel	= 40			--��ͼ���
x310163_g_LimitSceneId	= 0				--�淨���ڳ��������������淨����������һ����Ӧ��Ϊ�Ƿ�


x310163_g_GameID_Right	= 961
x310163_g_GameID_Error	= 962


----------------------------------------------------------------------------------------------
--���½��������Ϣ
----------------------------------------------------------------------------------------------
--���飬����������
x310163_g_ExpBonus		= 500	--�������� ��ʽ=level*exp
x310163_g_ExpBonus1		= 650 --�������� ��ʽ=level*exp
x310163_g_ShengWang		= 0			--�����������̶�ֵ
x310163_g_MoneyBonus	= 15	--������������ʽ=level*money

--�����Ʒ
x310163_g_ItemRate		= 25			--�������
x310163_g_ItemList		= { 			--��Ʒ�б�
							{12030107,1}			
						  }

--����ĳ������ʱ�Ľ�����Ϣ
x310163_g_MissionGL		= 50			--�������
x310163_g_MissionId		= 9315			--����ID
x310163_g_MissionBonus	= 13015012		--���佱��

----------------------------------------------------------------------------------------------
--�����Ч��
----------------------------------------------------------------------------------------------
function x310163_CheckValid( sceneId,selfId)

	local level = GetLevel(sceneId,selfId)
	if level<x310163_g_LimitLevel then
		return -1
	end
	
	if sceneId ~= x310163_g_LimitSceneId then
		return -2
	end
	
	return 1

end

----------------------------------------------------------------------------------------------
--�������ʱ���Ƿ���Ч
----------------------------------------------------------------------------------------------
function x310163_IsStartTimeValid()
	local h,m = x310163_GetValidTimeHourMin()
	
	local cur  = h*60  + m
	local from = 19*60 + 30
	local to   = 24*60 + 00
	if cur < from or cur > to then
		
		--����־
		local strMsg = format("DML:<Info>x310163_IsStartTimeValid starttime invalid started  h=%d,m=%d", h, m )
    	WriteLog( 1, strMsg )
		return 0
	end
	
	return 1

end





----------------------------------------------------------------------------------------------
--�ж���Ҳµ����Ƿ��������
----------------------------------------------------------------------------------------------
function x310163_IsPlayerGamingFull( sceneId,selfId )

	local nDate   = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_DATE[1], MD_QUEST_DENGMI_DATE[2], MD_QUEST_DENGMI_DATE[3] )
	local nCount  = GetQuestData(sceneId,selfId,MD_QUEST_DENGMI_COUNT[1],MD_QUEST_DENGMI_COUNT[2],MD_QUEST_DENGMI_COUNT[3])

	local nCurDay = GetDayOfYear()
	if nCurDay == nDate then
		if nCount >= x310163_g_MaxCount then
			return 1
		end
	end

	return 0
end

----------------------------------------------------------------------------------------------
--����NPC
----------------------------------------------------------------------------------------------
function x310163_FindNpc(sceneId,npcId)
	
	for n,item in x310163_g_DengmiInfo do
		if npcId == item.npcID then
			return n
		end
	end
	
	return -1
							
end

----------------------------------------------------------------------------------------------
--��鲢����������
----------------------------------------------------------------------------------------------
function x310163_SaveDateMD( sceneId,selfId,nCurDay )

	SetQuestData(sceneId,selfId,MD_DENGMI_DATE[1],MD_DENGMI_DATE[2],MD_DENGMI_DATE[3],nCurDay)

end

----------------------------------------------------------------------------------------------
--����������Ե�����£�25%���ʸ��ر�ͼ
----------------------------------------------------------------------------------------------
function x310163_GiveJewMap( sceneId,selfId )
	local name = GetName(sceneId,selfId)
	local buff 	=	9011
	local buff1 =	9013
	local buff2 =	9012
	if name == nil then
		name = "Error"
	end
	local nItemCount = getn(x310163_g_ItemList)
	if nItemCount > 0 and x310163_g_ItemRate > 0  then

		--����Ƿ���Ի����Ʒ
		local bGet = random(1,100)
		if bGet <= x310163_g_ItemRate then
			
			--�����õ���Ʒ
			local nGetItem = random(1,nItemCount)
			
			local itemInfo = x310163_g_ItemList[nGetItem]
			
			BeginAddItem(sceneId)
			if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
            	AddItem( sceneId, itemInfo[1],itemInfo[2] )
            else
            	AddBindItem( sceneId, itemInfo[1],itemInfo[2] )
            end
            local ret = EndAddItem(sceneId,selfId)
            if ret > 0 then
            	
                AddItemListToPlayer(sceneId,selfId)
                
--                local msg = format("#Y�������#G@item_%d#Y�Ľ���",itemInfo[1],itemInfo[2])
--				LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--		       	LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--		       	LuaAllScenceM2Wrold( sceneId, format( "#G�������ˣ�#Y%s#G�ڲµ�������������һ��#R�ر�ͼ#G��", name ), 1, 1)
		    else
		    	LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 2,1)
		        LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 3,1)
            end
		end
	end
end
----------------------------------------------------------------------------------------------
--����������Ե�����£��Żᴥ�� multiΪscore
----------------------------------------------------------------------------------------------

function x310163_GetBonusExp( sceneId,selfId )

	--�δ����
	if GetGameOpenById(x310163_g_GameId) ~= 1 then
		return
	end
	
	--��������Ч��
	if x310163_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	local score = x310163_GetDengmiScore( sceneId ,selfId)
	local level = GetLevel(sceneId,selfId)
	return level*350*score
end


function x310163_GiveBonus( sceneId,selfId, multi )

	--�δ����
	if GetGameOpenById(x310163_g_GameId) ~= 1 then
		return
	end
	
	--��������Ч��
	if x310163_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	local level = GetLevel(sceneId,selfId)
	return level*875*multi
	
--	local level = GetLevel(sceneId,selfId)
--	local name = GetName(sceneId,selfId)
--	if name == nil then
--		name = "ErrorName"
--	end
--	
--	local bonusExp = 0
--	--������
--	if x310163_g_ExpBonus > 0 then
--		local level = GetLevel(sceneId,selfId)
--		if level <70 then
--			bonusExp = level*x310163_g_ExpBonus * multi
--			AddExp(sceneId,selfId,bonusExp)
--			
--			local msg = format("�������%d�㾭��ֵ�Ľ���",bonusExp)
--			
--			--LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--	        --LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--		else
--			bonusExp = level*x310163_g_ExpBonus1*multi
--			AddExp(sceneId,selfId,bonusExp)
--					
--			local msg = format("�������%d�㾭��ֵ�Ľ���",bonusExp)
--			
--			--LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--	    	--LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--	  	end
--	end
--	
--	--������
--	if x310163_g_ShengWang > 0 then
--		local bonusShengWang = GetShengWang( sceneId,selfId) + x310163_g_ShengWang
--		SetShengWang( sceneId,selfId,bonusShengWang)
--		
--		local msg = format("�������%d������ֵ�Ľ���",x310163_g_ShengWang*multi)
--		
--		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--	end
--	
--	--������
--	if x310163_g_MoneyBonus > 0 then
--		local bonusMoney = level*x310163_g_MoneyBonus*multi
--		local buff 	=	9011
--		local buff1 =	9013
--		if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 then
--			AddMoney(sceneId,selfId,0,bonusMoney,x310163_g_scriptId)
--		else
--			AddMoney(sceneId,selfId,1,bonusMoney,x310163_g_scriptId)
--		end
--	end
--	
--	
--	-- ���һö�󶼼��껪���ֱ�
--    BeginAddItem( sceneId)
--    AddItem( sceneId, 11990117, 1)
--    if EndAddItem( sceneId, selfId) <= 0 then
--        Msg2Player( sceneId, selfId, "��ı����������޷����#{_ITEM11990117}������", 8, 2)
--    else
--        AddItemListToPlayer( sceneId, selfId)
--    end
--	--��������Ʒ
--	if IsHaveQuestNM( sceneId, selfId, x310163_g_MissionId) == 1 then
--		
--		--�ж������Ƿ����
--		local misIndex = GetQuestIndexByID(sceneId,selfId,x310163_g_MissionId)
--		if misIndex < 0 then
--			return
--		end
--		
--		--������ɣ�����
--		if GetQuestParam( sceneId,selfId,misIndex,7) == 1 then
--			return
--		end
--		
--		--������
--		local bGet = random(1,100)
--		if bGet <= x310163_g_MissionGL then
--			
--			BeginAddItem(sceneId)
--            AddItem( sceneId, x310163_g_MissionBonus,1 )
--            local ret = EndAddItem(sceneId,selfId)
--            if ret > 0 then
--                AddItemListToPlayer(sceneId,selfId)
--                
--                --������ø���ʾ������ű�����������ʾ
--		    else
--		    	LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 2,1)
--		        LuaScenceM2Player(sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 3,1)
--            end
--		end
--	end
--	
--	return bonusExp
end

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x310163_ProcEnumEvent( sceneId, selfId, targetId, MissionId )


	if GetGameOpenById(x310163_g_GameId) ~= 1 then
		return
	end
	
	
	
	local md = GetQuestData(sceneId,selfId,MD_DENGMI_NO1[1],MD_DENGMI_NO1[2],MD_DENGMI_NO1[3])
	
    AddQuestNumText(sceneId,x310163_g_scriptId,"��Ҫ�µ���",3,x310163_g_scriptId)
        
    
    x310163_InitDengmiArray( sceneId, selfId)
end

----------------------------------------------------------------------------------------------
--��ӵ��մ�ѡ��
----------------------------------------------------------------------------------------------
function x310163_AddDengmiAnswerOption( sceneId,strAnswer1,strAnswer2,strAnswer3,strAnswer4)

	--������ѡ��
	local arr_answer = { {strAnswer1,11001,0},{strAnswer2,11002,0},{strAnswer3,11003,0},{strAnswer4,11004,0} }
	for i=1,4 do
		
		local nCount = getn(arr_answer)
		local n = random(1,nCount)
		while arr_answer[n][3] == 1 do
			n = random(1,nCount)
		end
		
		arr_answer[n][3] = 1
		
		AddQuestNumText(sceneId,x310163_g_scriptId,arr_answer[n][1],3,arr_answer[n][2] )
	end
	
end

----------------------------------------------------------------------------------------------
--�����ջ���
----------------------------------------------------------------------------------------------
function x310163_SetDengmiScore( sceneId ,selfId, score)
	SetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3],score)
end

function x310163_SetDengmiScoreInc( sceneId ,selfId, scoreInc)
	local score = GetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3])
	SetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3],score + scoreInc)
end
----------------------------------------------------------------------------------------------
--�����ջ���
----------------------------------------------------------------------------------------------
function x310163_GetDengmiScore( sceneId ,selfId)
	local score = GetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3])
	return score
end
----------------------------------------------------------------------------------------------
--��NPC�Ƿ���
----------------------------------------------------------------------------------------------
function x310163_NPCIsVisited( sceneId ,selfId, NPCindex)
	local Is = 0
	if NPCindex == 1 then
		Is = GetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3])
	elseif NPCindex == 2 then
		Is = GetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3])
	elseif NPCindex == 3 then
		Is = GetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3])
	elseif NPCindex == 4 then
		Is = GetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3])
	end
	return Is
end
----------------------------------------------------------------------------------------------
--���ô�NPC���
----------------------------------------------------------------------------------------------
function x310163_SetNPCVisited( sceneId ,selfId, NPCindex)
	if NPCindex == 1 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3],1)
	elseif NPCindex == 2 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3],1)
	elseif NPCindex == 3 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3],1)
	elseif NPCindex == 4 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3],1)
	end

end

----------------------------------------------------------------------------------------------
--���ô�NPC���
----------------------------------------------------------------------------------------------
function x310163_ResetDengmiMD( sceneId ,selfId)

	SetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3],0)
	SetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3],0)
	
end
----------------------------------------------------------------------------------------------
--���ô�NPC���
----------------------------------------------------------------------------------------------
function x310163_SetDengmiMD( sceneId ,selfId,NPCindex)
	if NPCindex == 1 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3],1)
	elseif NPCindex == 2 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3],1)
	elseif NPCindex == 3 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3],1)
	elseif NPCindex == 4 then
		SetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3],1)
	end

end
----------------------------------------------------------------------------------------------
--��ʼ�����
----------------------------------------------------------------------------------------------
function x310163_InitDengmiArray( sceneId ,selfId)
	local nDate   = GetQuestData(sceneId,selfId,MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3] )
	local nCurDay = GetDayOfYear()
	
	local accDay = x310163_GetAcceptDate( sceneId ,selfId)
	local nCount = QuestDengmi_GetQuestionCount()
	for i,item in x310163_g_DengmiInfo do
		--if item.nDengmi == nil or nDate ~= nCurDay then
		local md = x310163_g_DengmiNoMD[i]
		
		local md1 = GetQuestData(sceneId,selfId,MD_DENGMI_NO1[1],MD_DENGMI_NO1[2],MD_DENGMI_NO1[3])
		local no = GetQuestData(sceneId,selfId,md[1],md[2],md[3]) 
		if no == 0 or accDay ~= nCurDay then 
			local DengmiNo = random(0,nCount-1)
			item.nDengmi = DengmiNo

			
			local id,strDesc,strAnswer1,strAnswer2,strAnswer3,strAnswer4,nAnswer = QuestDengmi_GetQuestionInfo(item.nDengmi)
			
			x310163_g_DengmiArray[DengmiNo] = {}		
			x310163_g_DengmiArray[DengmiNo].id = id + 100000		
			x310163_g_DengmiArray[DengmiNo].strDesc = strDesc
			x310163_g_DengmiArray[DengmiNo].strAnswer1 = strAnswer1
			x310163_g_DengmiArray[DengmiNo].strAnswer2 = strAnswer2
			x310163_g_DengmiArray[DengmiNo].strAnswer3 = strAnswer3
			x310163_g_DengmiArray[DengmiNo].strAnswer4 = strAnswer4
			x310163_g_DengmiArray[DengmiNo].nAnswer = nAnswer + 11000
			SetQuestData(sceneId,selfId,md[1],md[2],md[3], DengmiNo) 
			
		end
		
	end
end	
	

function x310163_IsDengmiFinish( sceneId ,selfId)
	local npc1 = GetQuestData(sceneId,selfId,MD_DENGMI_NPC1[1],MD_DENGMI_NPC1[2],MD_DENGMI_NPC1[3])
	local npc2 = GetQuestData(sceneId,selfId,MD_DENGMI_NPC2[1],MD_DENGMI_NPC2[2],MD_DENGMI_NPC2[3])
	local npc3 = GetQuestData(sceneId,selfId,MD_DENGMI_NPC3[1],MD_DENGMI_NPC3[2],MD_DENGMI_NPC3[3])
	local npc4 = GetQuestData(sceneId,selfId,MD_DENGMI_NPC4[1],MD_DENGMI_NPC4[2],MD_DENGMI_NPC4[3])
	
	if npc1==1 and npc2==1 and npc3==1 and npc4==1 then
		return 1
	end
	return 0
end
----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x310163_ProcEventEntry( sceneId ,selfId, npcId,idScript,idExt )
	----------------------------------------------------------------------------------------------
	--�δ����
	----------------------------------------------------------------------------------------------
	
	if GetGameOpenById(x310163_g_GameId) ~= 1 then
		
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
	if x310163_CheckValid( sceneId,selfId ) ~= 1 then
		return
	end
	
	if IsHaveQuest(sceneId,selfId, x310163_g_MissionId) <= 0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t����ȥ�ҡ�����ʹ�١��̵³���ȡ���ջ�����\n\t#G��ÿ�����ϵ�19��30--24��00����̳����������ʹ�١��̵³������󶼵��ջ�����")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return 
	end
	----------------------------------------------------------------------------------------------
	--���û�п�ʼ��ʱ�򣬲�������������������
	----------------------------------------------------------------------------------------------
	if x310163_IsStartTimeValid( sceneId,selfId ) ~= 1 then
		

		
		--���������ʾ
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t���ջỹû��ʼ�أ����ļ���\n\t#G��ÿ�����ϵ�19��30--24��00���ջῪ�ţ�")				
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
		return
	end
	
	local nDate   = GetQuestData(sceneId,selfId,MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3] )
	local nCurDay = GetDayOfYear()
	if nDate == nCurDay then
		if x310163_IsDengmiFinish( sceneId ,selfId) == 1 then
			--���������ʾ
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t���Ѿ�����˽���Ĵ󶼵��ջᣬ������������")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
			return
		end
		
	--else
		--x310163_SaveDateMD( sceneId,selfId,nCurDay )
		--x310163_ResetDengmiMD(sceneId,selfId)
	end
	----------------------------------------------------------------------------------------------
	--������
	----------------------------------------------------------------------------------------------

	for i,item in x310163_g_DengmiInfo do
		item.npcID = FindMonsterByGUID(sceneId,item.GUID)
	end
	
	
	local nFind = x310163_FindNpc(sceneId,npcId)
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "Error"
	end
	
	if idExt == x310163_g_scriptId then
		----------------------------------------------------------------------------------------------
		--��ʼ����
		----------------------------------------------------------------------------------------------
		if x310163_NPCIsVisited( sceneId ,selfId, nFind) == 1 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t������Ѿ��¹��ҵĵ����ˣ���ȥ�������ô���ɴ󶼵��ջᡣ\n\t#G(4��������Ů�ֱ��ڴ��ڲ����ϡ����ϡ������������ĸ���λ���ƶ���)")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
			return
		end
		--�ڴ�����ж�λ����
			
		local MD = x310163_g_DengmiNoMD[nFind]
		
		local DengmiNo = GetQuestData(sceneId,selfId,MD[1],MD[2],MD[3])
		local dm = x310163_g_DengmiArray[DengmiNo]
		
		--����npcid�ʹ�����

		
		--���¶Ի�������
		BeginQuestEvent(sceneId)
			
		AddQuestText(sceneId,dm.strDesc)
		x310163_AddDengmiAnswerOption( sceneId, dm.strAnswer1, dm.strAnswer2, dm.strAnswer3, dm.strAnswer4 )
										
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,npcId)
			
	elseif idExt >= 11001 and idExt <= 11004 then
		
		----------------------------------------------------------------------------------------------
		--���ѡ�е�ĳ������
		----------------------------------------------------------------------------------------------
		if x310163_NPCIsVisited( sceneId ,selfId, nFind) == 1 then
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t������Ѿ��¹��ҵĵ����ˣ���ȥ�������ô���ɴ󶼵��ջᡣ\n\t#G(4��������Ů�ֱ��ڴ��ڲ����ϡ����ϡ������������ĸ���λ���ƶ���)")				
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			return
		end
		x310163_SetNPCVisited(sceneId ,selfId, nFind)
			
		
	--	local dm = x310163_g_DengmiArray[nFind]
		local MD = x310163_g_DengmiNoMD[nFind]
		
		local DengmiNo = GetQuestData(sceneId,selfId,MD[1],MD[2],MD[3])
		local dm = x310163_g_DengmiArray[DengmiNo]
		
		
		if dm.nAnswer == idExt then
			--�����

			
			--�����ʾ
			local name = GetName(sceneId,selfId)
			LuaScenceM2Player( sceneId,selfId,"\t��ϲ��¶��˵���",name,3,1)
			LuaScenceM2Player( sceneId,selfId,"\t��ϲ��¶��˵���",name,2,1)
			LuaScenceM2Player( sceneId,selfId,"\t������5����ջ���",name,3,1)
			LuaScenceM2Player( sceneId,selfId,"\t������5����ջ���",name,2,1)
			x310163_SetDengmiScoreInc(sceneId,selfId,5)
			--���¶Ի�������
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t��ϲ��¶��˵��գ����#R5��#W���ջ��֡�" )
				if x310163_IsDengmiFinish( sceneId ,selfId) == 1 then
					local score,bonusExp = x310163_OnDengmiFinish(sceneId ,selfId)
					local strMsg = format("\t�������õĵ��ջ����ǣ�#R%d��#W����������#R%d����#W��ӭ����������",score, bonusExp)
					local strMsg = "\t����������˵��գ���ӭ�������������Ƚ�����"
					AddQuestText(sceneId,strMsg)
				else
					AddQuestText(sceneId,"\t��ǰ������������������µ��ա�\n\t#G(4��������Ů�ֱ��ڴ��ڲ����ϡ����ϡ������������ĸ���λ���ƶ���)" )
				end
			EndQuestEvent(sceneId)
			
			DispatchQuestEventList(sceneId,selfId,npcId)
		
			x310163_GiveJewMap(sceneId,selfId)
			
			--������
			--x310163_GiveBonus( sceneId,selfId )
			--CallScriptFunction( 256224, "Finishdengmi", sceneId, selfId)	
			
			--����淨��־
			GamePlayScriptLog( sceneId, selfId, x310163_g_GameID_Right)
			 
			 --��¼��־
			local name = GetName(sceneId,selfId)
			if name == nil then
				name = "Error"
			end
		else
			--�����
			--�����ʾ
			local name = GetName(sceneId,selfId)
			LuaScenceM2Player( sceneId,selfId,"\t���ź�����´���",name,3,1)
			LuaScenceM2Player( sceneId,selfId,"\t���ź�����´���",name,2,1)
			LuaScenceM2Player( sceneId,selfId,"\t������1����ջ���",name,3,1)
			LuaScenceM2Player( sceneId,selfId,"\t������1����ջ���",name,2,1)
			x310163_SetDengmiScoreInc(sceneId,selfId,1)
			--���¶Ի�������
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"\t���ź���´��˵��գ������#R1��#W���ջ��֡�")	
				if x310163_IsDengmiFinish( sceneId ,selfId) == 1 then
					--local score,bonusExp = x310163_OnDengmiFinish(sceneId ,selfId)
					--local strMsg = format("\t�������õĵ��ջ����ǣ�#R%d��#W����������#R%d����#W��ӭ����������",score, bonusExp)
					--AddQuestText(sceneId,strMsg)
				else
					AddQuestText(sceneId,"\t��ǰ������������������µ��ա�\n\t#G(4��������Ů�ֱ��ڴ��ڲ����ϡ����ϡ������������ĸ���λ���ƶ���)" )
				end			
			EndQuestEvent(sceneId)
			DispatchQuestEventList(sceneId,selfId,npcId)
			
			
			--����淨��־
			GamePlayScriptLog( sceneId, selfId, x310163_g_GameID_Error)
			
			--��¼��־
			local name = GetName(sceneId,selfId)
			if name == nil then
				name = "Error"
			end
			
			if x310163_IsDengmiFinish( sceneId ,selfId) == 1 then
				--x310163_OnDengmiFinish(sceneId ,selfId)
			end
		
		end	
		
		CallScriptFunction( 310164, "OnMissionStep", sceneId, selfId, x310163_g_DengmiInfo[nFind].GUID)	
		
		
	end
		

end
----------------------------------------------------------------------------------------------
--�õ�������������
----------------------------------------------------------------------------------------------
function x310163_GetAcceptDate( sceneId,selfId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x310163_g_MissionId)
	return GetQuestParam( sceneId, selfId, misIndex, 6)
end

function x310163_OnDengmiFinish(sceneId ,selfId)
	local name = GetName(sceneId,selfId)
	if name == nil then
		name = "Error"
	end
			
	--local score = x310163_GetDengmiScore(sceneId ,selfId)

	--local bonusExp = x310163_GiveBonus( sceneId,selfId, score )
	--local bonusExp = x310163_GiveBonus( sceneId,selfId, score )
	local score = x310163_GetDengmiScore(sceneId ,selfId)
	local exp = x310163_GetBonusExp(sceneId ,selfId)
	local strMsg = format("�������õĵ��ջ����ǣ�%d�֣���������%d���飬��ӭ������������",score, exp)
	
	--LuaScenceM2Player( sceneId,selfId,strMsg,name,3,1)
	--LuaScenceM2Player( sceneId,selfId,strMsg,name,2,1)
	
	return score,exp
	
end

function x310163_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 0
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310163_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310163_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310163_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x310163_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--�ύ
----------------------------------------------------------------------------------------------
function x310163_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x310163_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x310163_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x310163_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

----------------------------------------------------------------------------------------------
--ȡ����Ч��ʱ��,�������ʱ���飬�������ȡʱ��Ĳ��5�����С��0�����϶���Ч������ȡ
--���ս����ȡʱ��������ϳ�������������������ͬ�ļ��
----------------------------------------------------------------------------------------------
function x310163_GetValidTime()

	local n1 = GetCurrentTime()
	local n2 = GetCurrentTime()
	
	local nResult = n2 - n1 
	while nResult > 5 or nResult < 0 do
		n1 = GetCurrentTime()
		n2 = GetCurrentTime()
		
		nResult = n2 - n1 
		
		--��¼��־
		local strMsg = format("DML:<Error>x310163_GetValidTime n1=%d,n2=%d",n1,n2)
		WriteLog( 1, strMsg )	
		
	end
	
	return n2
end

----------------------------------------------------------------------------------------------
--ȡ����Ч��Сʱ����
----------------------------------------------------------------------------------------------
function x310163_GetValidTimeHourMin()

	local h,m,s = GetHourMinSec()	
	return h,m

end