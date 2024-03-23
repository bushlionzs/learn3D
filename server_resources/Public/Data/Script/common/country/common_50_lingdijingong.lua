--MisDescBegin

x300950_g_ScriptId 					= 300950                  --�ű�ID
x300950_g_MissionId 				= 7760                    --����ID

x300950_g_MissionKind 				= 1                       --��������
x300950_g_LevelLess					= 40                      --�������ŵȼ�  <=0 ��ʾ������

x300950_g_MissionName				= "�����ҡ����ݳǽ���"
x300950_g_MissionTarget				= "  �ҵ�#{_ITEM%d}(%d/%d)"      --����Ŀ��
x300950_g_MissionInfo				= "\tǿ��Ĺ��Ҳ�����������һ������������ϵ��������ͼ�ڻ�ʹ����ع��ʺ���ɳ�������ľ��飬�����и��߼ӳɡ�ȥ����Щ������ȱ��������ס��������Ϊ��������ս��"      --������Ϣ
x300950_g_ContinueInfo				= "\t�ҵ�#{_ITEM%d}"	  --���������Ϣ
x300950_g_MissionCompleted			= "\t��л��Ϊ���ͼ�����������Ĺ��ף�"	  --���������Ϣ
x300950_g_MissionHelp				= "\tÿ�����貿��Ϊ��������������������˽����Ը�����������"      --������ʾ��Ϣ
x300950_g_Missionruse				= "\tʹ������ܣ�����1��#{_ITEM%d}"      --������

--Ŀ��
x300950_g_ExtTarget					= { {type=20,n=1,target=""} }


--����
x300950_g_ExpBonus					= 0     --���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x300950_g_BonusItem					= {}	--��������Ʒ

x300950_g_BonusMoney1               = 0  --������������
x300950_g_BonusMoney2               = 0  --�������ǰ�����
x300950_g_BonusMoney3               = 0  --�������󶨽��
x300950_g_BonusMoney4               = 0  --��������͢����
x300950_g_BonusMoney5               = 0  --��������������
x300950_g_BonusMoney6               = 0  --����������

x300950_g_BonusChoiceItem           = {}

--MisDescEnd

x300950_g_MaxCount					= 3

-- ������NPC
x300950_g_TargetNPC                 = 400600

-- ������Ʒ�б�
x300950_g_MissionItemTable          = {
                                        { itemId = 11041000, count = 1  }, 
										{ itemId = 11041010, count = 1  }, 
                                        { itemId = 11041020, count = 1  }, 
                                        { itemId = 11041030, count = 1  }, 
                                        { itemId = 11041040, count = 1	}, 
                                        { itemId = 11041050, count = 1	}, 
}

x300950_g_LairdMap					= 6 -- ���ݳ�
-- ���齱��ϵ��
x300950_g_CoffExp                   = 1500
-- �淨����id
x300950_g_IsEnableId                = 1050
-- �淨����ʱ��(��0����ĵ�x����)
x300950_g_OpenTime                  = 540
-- �淨�ر�ʱ��(��0����ĵ�x����)
x300950_g_EndTime                   = 1380

x300950_g_SaveItem                   = -1
x300950_g_SaveItemDay                = -1

-- �ص�
function x300950_CallbackEnumEvent(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById( x300950_g_IsEnableId) <= 0 then
        return
    end
    
    local country = GetCurCountry(sceneId, selfId)
    local nLairdCountry = GetSceneLairdCountryId(x300950_g_LairdMap)
    if nLairdCountry ~= country then
		return
	end
    
    if MissionId == 0 then
		if IsHaveQuest(sceneId, selfId, x300950_g_MissionId) <= 0 then
			return 
		end
		
		local npcGuid = GetMonsterGUID(sceneId,targetId)
		if npcGuid ~= x300950_g_TargetNPC then
			return
		end
	else
		if IsHaveQuest(sceneId, selfId, x300950_g_MissionId) > 0 then
			return 
		end
    end
    
    local state = GetQuestStateNM(sceneId, selfId, targetId, x300950_g_MissionId)
	AddQuestNumText(sceneId,x300950_g_MissionId,x300950_g_MissionName,state,MissionId )
end

---------------------------------------------------------------------------------------------------
--�о��¼�
---------------------------------------------------------------------------------------------------
function x300950_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
end

---------------------------------------------------------------------------------------------------
--������ں���
---------------------------------------------------------------------------------------------------
function x300950_ProcEventEntry(sceneId, selfId, targetId, MissionId, nExtIdx)

	if nExtIdx > 0 then
		if IsHaveQuest( sceneId, selfId, x300950_g_MissionId) > 0 then

			x300950_DispatchContinueInfo(sceneId, selfId, targetId) --δ���������ʾ
        else
			x300950_DispatchMissionInfo(sceneId, selfId, targetId)	--������Ϣ��ʾ
		end
	else
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300950_g_MissionId)
		if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
            x300950_DispatchContinueInfo(sceneId, selfId, targetId) --δ���������ʾ
        else
            x300950_DispatchCompletedInfo(sceneId, selfId, targetId) --���������ʾ
        end
	end
end

---------------------------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------------------------
function x300950_ProcAcceptCheck(sceneId, selfId, targetId)
	local bHaveMission	= IsHaveQuest(sceneId, selfId, x300950_g_MissionId)
	if( bHaveMission > 0) then
		return 0
	else
		return 1
	end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300950_ProcQuestAccept(sceneId, selfId, targetId, missionId)

    if IsHaveQuest(sceneId, selfId, x300950_g_MissionId) > 0 then
		-- ʱ����
        local nowTime = GetMinOfDay()
        if nowTime < x300950_g_OpenTime or nowTime >= x300950_g_EndTime then
            Msg2Player( sceneId, selfId, "ֻ����ÿ�յ�#G9��00--23��00#cffcf00�ڲſ��ύ����", 8, 2)
            Msg2Player( sceneId, selfId, "ֻ����ÿ�յ�#G9��00--23��00#cffcf00�ڲſ��ύ����", 8, 3)
            return
        end
        
		local country = GetCurCountry(sceneId, selfId)
		local nLairdCountry = GetSceneLairdCountryId(x300950_g_LairdMap)
		if nLairdCountry ~= country then
			Msg2Player( sceneId, selfId, "�ܱ�Ǹ������ز�������Ĺ���", 8, 3)
			return
		end
		
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300950_g_MissionId)
		local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
        if DelItem(sceneId, selfId, x300950_g_MissionItemTable[rnd].itemId, 1) == 0 then
			Msg2Player(sceneId, selfId, "�ύ��Ʒʧ�ܡ�", 8, 2)
			Msg2Player(sceneId, selfId, "�ύ��Ʒʧ��", 8, 3)
			return
		end 
		
		
		--����ͼ�ھ���
		local nGuildID = GetSceneLairdGuildId(x300950_g_LairdMap)
		if nGuildID < 0 then
			--�����Ч
			return
		end
		
		local nLairdLevel = GetSceneLairdLevel(x300950_g_LairdMap)
		if nLairdLevel > 5 then
			--�ȼ�����,�����ټӳ���
			return
		end

        x300950_SetDayCount(sceneId, selfId)

        DelQuest(sceneId, selfId, x300950_g_MissionId)
        Msg2Player(sceneId, selfId, "�����������:"..x300950_g_MissionName, 8, 3)
        Msg2Player(sceneId, selfId, "�����������:"..x300950_g_MissionName, 8, 2)
       
		local mutli = 1
		-- if CountryIsFortuneTime(sceneId,selfId,0)==1 then -- ������
			-- mutli = mutli+1
		-- end
		
		-- if CountryIsFortuneTime(sceneId,selfId,1)==1 then -- ������
			-- mutli = mutli+1
		-- end
		
        local level = GetLevel(sceneId, selfId)
        if x300950_g_CoffExp > 0 then
        
			local xp = level * x300950_g_CoffExp * mutli * nLairdLevel
			AddExp(sceneId, selfId, xp)
			Msg2Player(sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", xp), 8, 2)
			Msg2Player(sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", xp), 8, 3)
			
        end
        
        if level >= 80 then
        
			local refixInh = floor(AddInherenceExp(sceneId, selfId, 2.5*level*mutli))
			local msg = format("������%d���츳ֵ��",refixInh)
			Msg2Player(sceneId, selfId, msg, 8, 2)
			Msg2Player(sceneId, selfId, msg, 8, 3)
			
        end
        
		
		local nCurLairdExp = GetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP) + 1
		SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,nCurLairdExp)
		
		local nLevelup = 0
		
		--�ȼ�û����,�ӳɾ���
		if nLairdLevel == 1 and nCurLairdExp >= 10500 then
			SetSceneLairdLevel(x300950_g_LairdMap,2)
			SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,nCurLairdExp-10500)
			nLevelup = 1
		elseif nLairdLevel == 2 and nCurLairdExp >= 11667 then
			SetSceneLairdLevel(x300950_g_LairdMap,3)
			SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,nCurLairdExp-11667)
			nLevelup = 1
		elseif nLairdLevel == 3 and nCurLairdExp >= 12834 then
			SetSceneLairdLevel(x300950_g_LairdMap,4)
			SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,nCurLairdExp-12834)
			nLevelup = 1
		elseif nLairdLevel == 4 and nCurLairdExp >= 14001 then
			SetSceneLairdLevel(x300950_g_LairdMap,5)
			SetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP,0)
			nLevelup = 1
		end
		
		--�����ᴥ����һЩ�¼�
		if nLevelup == 1 then
		
			--������ǰ�������
			CreateMonster(sceneId, 3059, 65, 141, 24, -1, -1, -1, 21, -1, 0, "", "" )
			
			--���������������
			GameBattleLairdLevelupEvent(x300950_g_LairdMap)
			
			--��ʾ
			local strSceneName = GetSceneInfo(sceneId,"NAME")
			local strLevelMsg = format("%sͼ����Ϊ%d����������䣬������������֮�ꡣ",strSceneName,(nLairdLevel + 1) )			
			
			LuaAllScenceM2Wrold(sceneId,strLevelMsg,CHAT_PLANE_SCROLL,1)
			LuaAllScenceM2Wrold(sceneId,strLevelMsg,CHAT_LEFTDOWN,1)
			LuaAllScenceM2Wrold(sceneId,strLevelMsg,CHAT_MAIN_RIGHTDOWN,1)
		end
    else
		-- ʱ����
        local nowTime = GetMinOfDay()
        if nowTime < x300950_g_OpenTime or nowTime >= x300950_g_EndTime then
            Msg2Player( sceneId, selfId, "ֻ����ÿ�յ�#G9��00--23��00#cffcf00�ڲſ���ȡ����", 8, 2)
            Msg2Player( sceneId, selfId, "ֻ����ÿ�յ�#G9��00--23��00#cffcf00�ڲſ���ȡ����", 8, 3)
            return
        end
        
        
		if GetLevel( sceneId, selfId) < x300950_g_LevelLess then
			Msg2Player( sceneId, selfId, format("�ܱ�Ǹ�����ĵȼ�����%d�����޷����ܡ����ҡ�ͼ�ڽ�������", x300950_g_LevelLess), 8, 3)
			return
		end
    
        local country = GetCurCountry(sceneId, selfId)
		local nLairdCountry = GetSceneLairdCountryId(x300950_g_LairdMap)
		if nLairdCountry ~= country then
			Msg2Player( sceneId, selfId, "û�����", 8, 3)
			return
		end
        
		if x300950_GetDayCount(sceneId, selfId) == 0 then
			Msg2Player( sceneId, selfId, "ͬһ�����һ��ֻ�����"..x300950_g_MaxCount.."������", 8, 3)
            return
		end
		
		local ret = AddQuest( sceneId, selfId, x300950_g_MissionId, x300950_g_ScriptId, 0, 0, 1, 0) -- ������������
		if ret == 0 then
			Msg2Player(sceneId,selfId, "�����������������ʧ�ܣ�",8,3)
			return
		end
		
		-- ��ʾ���������Ϣ
		Msg2Player( sceneId, selfId, "�����������"..x300950_g_MissionName, 8, 3)
		Msg2Player( sceneId, selfId, "�����������"..x300950_g_MissionName, 8, 2)
		
		x300950_SetSaveItem(sceneId, selfId)
		local rnd = x300950_g_SaveItem
	
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300950_g_MissionId)
			
		local count = GetItemCountInBag(sceneId, selfId, x300950_g_MissionItemTable[rnd].itemId)

		SetQuestByIndex( sceneId, selfId, misIndex, 7, count >= x300950_g_MissionItemTable[rnd].count and 1 or 0)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, count >= x300950_g_MissionItemTable[rnd].count and 1 or 0)
		SetQuestByIndex( sceneId, selfId, misIndex, 1, rnd)
		
		-- ����������ٺ�Q���
		x300950_ProcQuestLogRefresh( sceneId, selfId, x300950_g_MissionId)
		return 1
    end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300950_ProcQuestAbandon( sceneId, selfId, MissionId)
	if IsHaveQuest( sceneId, selfId, x300950_g_MissionId) > 0 then
		DelQuest( sceneId, selfId, x300950_g_MissionId)
        x300950_SetDayCount(sceneId, selfId)
		Msg2Player( sceneId, selfId, "������������"..x300950_g_MissionName, 8, 3)
		Msg2Player( sceneId, selfId, "������������"..x300950_g_MissionName, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--�ύ���񣬲��������Ƿ���ɻ���������ʾ���������Ϣ�������������Ϣ
---------------------------------------------------------------------------------------------------
function x300950_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId)
end

function x300950_BonusInfo(sceneId, selfId)
	local mutli = 1
	-- if CountryIsFortuneTime(sceneId,selfId,0)==1 then -- ������
		-- mutli = mutli+1
	-- end
	
	-- if CountryIsFortuneTime(sceneId,selfId,1)==1 then -- ������
		-- mutli = mutli+1
	-- end
	
	local level = GetLevel(sceneId, selfId)
	
	--����ͼ�ھ���
	local nGuildID = GetSceneLairdGuildId(x300950_g_LairdMap)
	if nGuildID < 0 then
		--�����Ч
		return
	end
	
	local nLairdLevel = GetSceneLairdLevel(x300950_g_LairdMap)

    --��������Ϣ
    if x300950_g_CoffExp > 0 then
		local exp = level * x300950_g_CoffExp*mutli*nLairdLevel
        AddQuestExpBonus(sceneId, exp)
    end
	if level >= 80 then
		local refixInhExp = floor(RefixInherenceExp(sceneId, selfId, 2.5*level*mutli))
		AddQuestInherenceExpBonus(sceneId,refixInhExp)
	end	
	
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300950_DispatchMissionInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)

    --������Ϣ
    AddQuestText( sceneId, "#Y"..x300950_g_MissionName)
    AddQuestText( sceneId, x300950_g_MissionInfo)
    AddQuestText( sceneId, " ")
	
	x300950_SetSaveItem(sceneId, selfId)
	local rnd = x300950_g_SaveItem

	local misIndex = GetQuestIndexByID( sceneId, selfId, x300950_g_MissionId)
	
	local count = GetItemCountInBag(sceneId, selfId, x300950_g_MissionItemTable[rnd].itemId)
	if count > x300950_g_MissionItemTable[rnd].count then
		count = x300950_g_MissionItemTable[rnd].count
	end
	AddQuestText( sceneId,"#Y����Ŀ�꣺")
    AddQuestText( sceneId, format(x300950_g_MissionTarget, x300950_g_MissionItemTable[rnd].itemId, 
								count, x300950_g_MissionItemTable[rnd].count))
	AddQuestText( sceneId, " ")
	AddQuestText(sceneId,"#Y������ʾ��")
    AddQuestText( sceneId, format(x300950_g_MissionHelp, x300950_g_MissionItemTable[rnd].itemId))
    AddQuestText( sceneId, " ")
							
    x300950_BonusInfo(sceneId, selfId)
   
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300950_g_ScriptId, x300950_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300950_DispatchContinueInfo( sceneId, selfId, targetId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300950_g_MissionId)
	local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
		
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300950_g_MissionName)
    AddQuestText( sceneId, format(x300950_g_ContinueInfo, x300950_g_MissionItemTable[rnd].itemId))
	AddQuestText( sceneId, " ")
	
	if IsHaveQuest(sceneId, selfId, x300950_g_MissionId) > 0 then

		AddQuestText( sceneId,"#Y��������")
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300950_g_MissionId)
		if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
			AddQuestText(sceneId, "δ���")
		else
			AddQuestText(sceneId, "�����")
		end
	    x300950_BonusInfo(sceneId, selfId)
    end
    
	EndQuestEvent()
    DispatchQuestDemandInfo( sceneId, selfId, targetId, x300950_g_ScriptId, x300950_g_MissionId,0)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300950_DispatchCompletedInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300950_g_MissionName)
    AddQuestText( sceneId, x300950_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    
    x300950_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300950_g_ScriptId, x300950_g_MissionId)

end

---------------------------------------------------------------------------------------------------
--���ﱻɱ����Ϣ����
---------------------------------------------------------------------------------------------------
function x300950_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------------------------
--��Ʒ�ı�
---------------------------------------------------------------------------------------------------
function x300950_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
	
	if IsHaveQuest( sceneId, selfId, x300950_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300950_g_MissionId)
		local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
		local count = GetItemCountInBag(sceneId, selfId, x300950_g_MissionItemTable[rnd].itemId)
		SetQuestByIndex( sceneId, selfId, misIndex, 7, count >= x300950_g_MissionItemTable[rnd].count and 1 or 0)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, count >= x300950_g_MissionItemTable[rnd].count and 1 or 0)
		
		x300950_ProcQuestLogRefresh( sceneId, selfId, x300950_g_MissionId)
	end
end

---------------------------------------------------------------------------------------------------
--����NPC�¼�
---------------------------------------------------------------------------------------------------
function x300950_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId)
	if IsHaveQuestNM( sceneId, selfId, x300950_g_MissionId) == 0 then	-- ���û���������
		return
	end
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300950_GetDayCount(sceneId, selfId)

	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_LINGDIJINGONG_1_DATE[1], MD_LINGDIJINGONG_1_DATE[2],MD_LINGDIJINGONG_1_DATE[3])
	
	if today ~= lastday then
		return 1
	end
		
	local daycount = GetQuestData(sceneId, selfId, MD_LINGDIJINGONG_1_DAYCOUNT[1], MD_LINGDIJINGONG_1_DAYCOUNT[2],MD_LINGDIJINGONG_1_DAYCOUNT[3])
	return daycount < x300950_g_MaxCount and 1 or 0
end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x300950_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_LINGDIJINGONG_1_DATE[1], MD_LINGDIJINGONG_1_DATE[2],MD_LINGDIJINGONG_1_DATE[3])

	if today ~= lastday then
		SetQuestData(sceneId, selfId, MD_LINGDIJINGONG_1_DATE[1], MD_LINGDIJINGONG_1_DATE[2], MD_LINGDIJINGONG_1_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_LINGDIJINGONG_1_DAYCOUNT[1], MD_LINGDIJINGONG_1_DAYCOUNT[2], MD_LINGDIJINGONG_1_DAYCOUNT[3], 1)
	else
		local count = GetQuestData(sceneId, selfId, MD_LINGDIJINGONG_1_DAYCOUNT[1], MD_LINGDIJINGONG_1_DAYCOUNT[2],MD_LINGDIJINGONG_1_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, MD_LINGDIJINGONG_1_DAYCOUNT[1], MD_LINGDIJINGONG_1_DAYCOUNT[2], MD_LINGDIJINGONG_1_DAYCOUNT[3], count+1)
	end
end

function x300950_SetSaveItem(sceneId, selfId)
	if x300950_g_SaveItem == -1 then
		x300950_g_SaveItem = random(1, getn(x300950_g_MissionItemTable))
		if x300950_g_SaveItem < 1 then x300950_g_SaveItem = 1 end
		if x300950_g_SaveItem > getn(x300950_g_MissionItemTable) then x300950_g_SaveItem = getn(x300950_g_MissionItemTable) end
		x300950_g_SaveItemDay = GetDayOfYear()
	elseif x300950_g_SaveItemDay == -1 or x300950_g_SaveItemDay ~= GetDayOfYear() then
		x300950_g_SaveItem = random(1, getn(x300950_g_MissionItemTable))
		if x300950_g_SaveItem < 1 then x300950_g_SaveItem = 1 end
		if x300950_g_SaveItem > getn(x300950_g_MissionItemTable) then x300950_g_SaveItem = getn(x300950_g_MissionItemTable) end
		x300950_g_SaveItemDay = GetDayOfYear()
	end
end
---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300950_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300950_g_MissionId)
    local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
	local count = GetItemCountInBag(sceneId, selfId, x300950_g_MissionItemTable[rnd].itemId)
	if count > x300950_g_MissionItemTable[rnd].count then
		count = x300950_g_MissionItemTable[rnd].count
	end
	
	BeginQuestEvent( sceneId)
    AddQuestLogCustomText( sceneId,
							"",									-- ����
                            x300950_g_MissionName,              -- ��������
                            format(x300950_g_MissionTarget, x300950_g_MissionItemTable[rnd].itemId, 
								count, x300950_g_MissionItemTable[rnd].count),            --����Ŀ��
                            "@npc_"..x300950_g_TargetNPC,       --����NPC
                             format(x300950_g_Missionruse,x300950_g_MissionItemTable[rnd].itemId), 				--������
                            x300950_g_MissionInfo,              --��������
                            x300950_g_MissionHelp			--����С��ʾ
                            )
                            
    x300950_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end