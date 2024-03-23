--MisDescBegin

-- ��ԭ��������ű�ID
x300340_g_ScritpId = 300340
-- ����ID
x300340_g_MissionId = 8051
-- ��������С�ȼ�
x300340_g_LevelLess = 20
-- ��������
x300340_g_MissionName           = "�����ˡ���ԭ����"
-- 
x300340_g_NeedGold = 10000
x300340_g_KillMissionId =  7012
x300340_g_Material_Thread = 13011010

-- ������¯�㡱��ƷID
x300340_g_MissionPropertyId =  12030021

x300340_g_AwardItemId = 13011012 --������Ʒid

x300340_g_ExpBonus					= 	0                    	--���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x300340_g_BonusItem					=	{}	--��������Ʒ

x300340_g_BonusMoney1               = 	0  --������������
x300340_g_BonusMoney2               =   0  --�������ǰ�����
x300340_g_BonusMoney3               =   0  --�������󶨽��
x300340_g_BonusMoney4               =   0  --��������͢����
x300340_g_BonusMoney5               =   0  --��������������
x300340_g_BonusMoney6               =   0  --����������

x300340_g_BonusChoiceItem           =   {}

--MisDescEnd

x300340_g_MissionTable              = {
                                        { minLevel = 20, maxLevel = 40, placeId = 36, placeName = "@npcsp_��Ȫ��_82004",  itemId = 13013100, itemName = "�䱦Ƥë",	monsterName="����" }, 
                                        { minLevel = 40, maxLevel = 60, placeId = 37, placeName = "@npcsp_����ɽ_82005",  itemId = 13013101, itemName = "��Ŀ��֭",	monsterName="����" }, 
                                        { minLevel = 60, maxLevel = 9999, placeId = 39, placeName = "@npcsp_��Ҷ��_82006",  itemId = 13013102, itemName = "Ѫ���",	monsterName="����" }
}

-- ��������

x300340_g_MissionDescription    = "\t������ԭ�У������������Ĳ����Ƿ��������⣬��Щ��ҩ�������ǲ��ɶ�õ���Ʒ����֪����ɷ�֪��#G��ԭ����#Wһ˵���Ҿ����ռ����ǡ�\n\tǰ��#G%s#W�������л���%s���ռ�100��@item_%d#W�󽻸��ҡ�\n\t������һ��@item_12030021#W�������͸��㣬���ڲ�ԭ�����ܼ���#G%s#W��ʹ�ðɣ�������ú��õĻ�����ȥ@npc_138502���ﹺ��"
-- ������ʾ
x300340_g_MissionHelp           = "\t#G����¯��������Թ��е�����ض����������������Ʒ���������Ҫ����Ļ�����ȥ@npc_138502������ɡ�"
-- ����Ŀ��
x300340_g_strMissionTarget      = "  ��%s�ռ�@item_%d#W(%d/100)"
-- ����������ʾ�ַ�
x300340_g_strMissionAbandon     = "����������񣺡����ˡ���ԭ����"
-- ��������ַ���
x300340_g_strMissionComplete    = "����������񣺡����ˡ���ԭ����"
-- ����������ʾ
x300340_g_strMissionAccept      = "����������񣺡����ˡ���ԭ����"
-- ���������Ϣ
x300340_g_MissionContinue       = "\t����ǰ��#G%s#W�������л��ܲ�ԭ%s���ռ�100��#G%s#W�󽻸��ҡ�"

x300340_g_MissionProcess				=	"\t����ǰ��#G%s#W�������л��ܲ�ԭ����ռ�100��@item_%d#W��"
-- ������¯�㡱�ĳ���ʱ�䣨�룩
x300340_g_FanqiTime             = 180
-- ������¯�㡱�����÷�Χ
x300340_g_Range                 = 4
-- ����ظ�NPC
x300340_g_NPC                   = "@npc_138558"
-- �������Ҫ�ռ�����Ʒ����
x300340_g_FinishCount           = 100
-- �����ռ�Ŀ����Ʒ��ID
x300340_g_MP_TargetItemId       = 1
-- ʹ�á�����¯�㡱X����
x300340_g_MP_PosX               = 2
-- ʹ�á�����¯�㡱Z����
x300340_g_MP_PosZ               = 3
-- ʹ�á�����¯�㡱ʱ��
x300340_g_MP_UseTime            = 4
-- ����Ŀ�곡��
x300340_g_MP_TargetScene        = 5
-- ��������ϵ��
x300340_g_MoneyCoefficient      = 300
-- ����ϵ��
x300340_g_ExperienceCoefficient = 3000

function x300340_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    if GetLevel( sceneId, selfId) >= x300340_g_LevelLess then
        local state = GetQuestStateNM( sceneId, selfId, targetId, MissionId)
        -- print( state)
        AddQuestNumText( sceneId, x300340_g_MissionId, x300340_g_MissionName, state)
    end
end

function x300340_ProcEventEntry( sceneId, selfId, targetId, MissionId )
    if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������    
        -- ��ʾ����������Ϣ
        x300340_DispatchMissionInfo( sceneId, selfId, targetId)
    else--����ǲ��ǿ����ύ    
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
        local itemId = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
		if isFinish > 0 and GetItemCountInBag( sceneId, selfId, itemId) >= 100 then -- �������������
			x300340_MissionComplateInfo( sceneId, selfId, targetId, MissionId) -- ��ʾ�����Ϣ
		else
            --print( "***********" )
			x300340_MissionContinue( sceneId, selfId, targetId, MissionId) -- ��ʾ����δ�����Ϣ
		end
    end
end

-- ���������Ϣ
function x300340_MissionContinue( sceneId, selfId, targetId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    local taritem = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
    local strItem = ""
    local strPalace = ""
    local strMonster = ""
    for i, item in x300340_g_MissionTable do
        if item.itemId == taritem then
            strItem = item.itemName
            strPalace = item.placeName
            strMonster = item.monsterName
            break
        end
    end
	BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "#Y"..x300340_g_MissionName)
        AddQuestText( sceneId, format( x300340_g_MissionContinue, strPalace, strMonster, strItem) )

	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- ��ʾ����������Ϣ
function x300340_DispatchMissionInfo( sceneId, selfId, NPCId )
	local level = GetLevel( sceneId, selfId)
    local bFind = 0
    local strDescription = ""
    local itemId = 0
    local baseScene = ( GetCurCountry( sceneId, selfId) ) * 100 + 50

    -- ������ҵȼ��ó����񳡾�����Ʒ
    for i, item in x300340_g_MissionTable do
        if level >= item.minLevel and level < item.maxLevel then
            SetPlayerRuntimeData( sceneId, selfId, RD_GUJI_SCENEID, baseScene + item.placeId)
            SetPlayerRuntimeData( sceneId, selfId, RD_GUJI_ITEMID, item.itemId)
            itemId = item.itemId
            strDescription = format( x300340_g_MissionDescription, item.placeName, item.monsterName, item.itemId, item.placeName)
            bFind = 1
            break
        end
    end

    if bFind == 0 then
        return
    end

	BeginQuestEvent( sceneId)

		--������Ϣ
		AddQuestText( sceneId, "#Y"..x300340_g_MissionName)
		AddQuestText( sceneId, strDescription)

		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, format( "�ռ�@item_%d#W��", itemId ) )
		AddQuestText( sceneId, " ")
		AddQuestText( sceneId, " ")

		--��ʾ��Ϣ
        AddQuestText( sceneId, "#YС��ʾ��")
        AddQuestText( sceneId, x300340_g_MissionHelp)
        -- AddQuestText( sceneId, " ")

		--��������Ϣ

		--1������
		local exp = GetLevel( sceneId, selfId) * x300340_g_ExperienceCoefficient
		if exp > 0 then
			AddQuestExpBonus( sceneId, exp)
		end

		--2����Ǯ1
        local money = level * x300340_g_MoneyCoefficient
		if money > 0 then
			AddQuestMoneyBonus1( sceneId, money)
		end

		--3����Ǯ2
		if x300340_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300340_g_BonusMoney2 )
		end

		--4����Ǯ3
		if x300340_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300340_g_BonusMoney3 )
		end

		--��������
		if x300340_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300340_g_BonusMoney4 )
		end

		--��͢����
		if x300340_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300340_g_BonusMoney5 )
		end

		--����ֵ
		if x300340_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300340_g_BonusMoney6 )
		end

		--5���̶���Ʒ
		for i, item in x300340_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6����ѡ��Ʒ
		for i, item in x300340_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end

	EndQuestEvent()

	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300340_g_ScritpId, x300340_g_MissionId);
end

-- ��鵱���Ƿ��Ѿ����ܹ�������񣬽��ܹ�����1�����򷵻�0
function x300340_CheckDayTimes( sceneId, selfId)
    local today = GetDayOfYear()

    if x300340_GetAcceptTime( sceneId, selfId) ~= today then
        return 0
    else
        return 1
    end
end

function x300340_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
    if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then   -- û���������
        -- ��鵱���Ƿ��Ѿ������������
        if x300340_CheckDayTimes( sceneId, selfId) ~= 0 then
        	local str = "������Ѿ���ɹ������������������"
            BeginQuestEvent( sceneId)
            AddQuestText( sceneId, str )
            EndQuestEvent()
            DispatchQuestTips( sceneId, selfId)
            Msg2Player(sceneId, selfId, str, 8, 2)
            return
        end
        -- ��鱳���Ƿ�����
        BeginAddItem( sceneId)
            AddItem( sceneId, x300340_g_MissionPropertyId, 1)
        local result = EndAddItem( sceneId, selfId)
        if result == 0 then
        	local str = "�����������޷����������ߣ��������ʧ�ܣ�";
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, str )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
          	Msg2Player(sceneId, selfId, str, 8, 2)
    		
            return 0
        end
    	local ret	= AddQuest( sceneId, selfId, x300340_g_MissionId, x300340_g_ScritpId, 1, 0, 0, 1);
    	if( ret == 0) then
    		local str = "�����������������ʧ�ܣ�"
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, str )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
          	Msg2Player(sceneId, selfId, str, 8, 2)
    		return 0
        else
            -- ���½�����ʱ��
            local today = GetDayOfYear()
            x300340_SetAcceptTime( sceneId, selfId, today)
            
            local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId, GetPlayerRuntimeData( sceneId, selfId, RD_GUJI_ITEMID) )
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_TargetScene, GetPlayerRuntimeData( sceneId, selfId, RD_GUJI_SCENEID) )
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_PosX, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_PosZ, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, x300340_g_MP_UseTime, 0)

            x300340_ProcQuestLogRefresh( sceneId, selfId, MissionId)

    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, x300340_g_strMissionAccept);
    		EndQuestEvent( sceneId);
    		DispatchQuestTips( sceneId, selfId);
    		Msg2Player( sceneId, selfId, x300340_g_strMissionAccept, 8, 2)
    		Msg2Player( sceneId, selfId, x300340_g_strMissionAccept, 8, 3)

            -- ���������Ʒ
            AddItemListToPlayer( sceneId, selfId)
            local str = "��������Ʒ��@item_"..x300340_g_MissionPropertyId;
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, str);
    		EndQuestEvent( sceneId);
    		DispatchQuestTips( sceneId, selfId);
            -- Msg2Player( sceneId, selfId, "", 8, 3)

            -- д��־
            GamePlayScriptLog( sceneId, selfId, 441)
        end
    else
        -- 
        x300340_MissionComplate( sceneId, selfId, targetId, MissionId)
    end
end

function x300340_QuestLogRefresh( sceneId, selfId, MissionId)
    x300340_ProcQuestLogRefresh( sceneId, selfId, MissionId)
end

function x300340_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    local taritem = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
    local strItem = ""
    local strPalace = ""
    local strMonster = ""
    for i, item in x300340_g_MissionTable do
        if item.itemId == taritem then
            strItem = item.itemName
            strPalace = item.placeName
            strMonster = item.monsterName
            break
        end
    end

    -- �쿴��ұ�������Ʒ��������
    local itemSize = GetItemCount( sceneId, selfId, taritem)
    if itemSize >= x300340_g_FinishCount then
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    end

    BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x300340_g_MissionName,          -- ��������
                                format( x300340_g_strMissionTarget, strPalace, taritem, itemSize),     -- ����Ŀ��
                                x300340_g_NPC,                  -- ����NPC
                                format(x300340_g_MissionProcess, strPalace, taritem),          -- ������
                                format( x300340_g_MissionDescription, strPalace, strMonster, taritem, strPalace),   -- ��������
                                x300340_g_MissionHelp )          -- ������ʾ
    local exp = GetLevel( sceneId, selfId) * x300340_g_ExperienceCoefficient
    AddQuestExpBonus( sceneId, exp)
    -- 090302 ��������
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel > 80 then
        playerLevel = 80
    end
    local money = playerLevel * x300340_g_MoneyCoefficient
    AddQuestMoneyBonus1( sceneId, money)

    EndQuestEvent()
    DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x300340_Accept( sceneId, selfId, MissionId )
	return -1
end

--ɱ������
--����ID, �Լ���ID(���״̬��Ϊ�������Ա��Id), �����λ�ú�, ����objId, ����ID
function x300340_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
    
    if IsPlayerStateNormal( sceneId, selfId) ~= 1 then
        return
    end
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    -- ������񳡾�Id
    local misScene = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetScene)
    -- print( "���񳡾�ID��"..misScene)
    -- print( "��ǰ����ID��"..sceneId)
    -- ���ɱ�ֳ����ǲ������񳡾�
    if misScene == sceneId then
        -- �������ڡ�����¯�㡱����Ч��Χ�ڱ��
        local bUseFanqi = 0
        -- ��õ�ǰʱ��
        local curTime = GetCurrentTime()

        -- ʹ�á�����¯�㡱ʱ�����3���ӵ���Ҷ���
        local useItemArray = {}
        -- ��ö��鸽������
        local nearteamnum = GetNearTeamCount( sceneId, selfId)
        local useTime = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_UseTime)
        if nearteamnum <= 1 and curTime - useTime < x300340_g_FanqiTime then
            useItemArray[ 1] = selfId
        else
            for i = 0, nearteamnum - 1 do
                -- ��ö����Ա��ID
                local memberId = GetNearTeamMember( sceneId, selfId, i)

                if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
                    -- �鿴��û������
                    local mIndex = GetQuestIndexByID( sceneId, memberId, x300340_g_MissionId)
                    if mIndex >= 0 then
                        local useitem = GetQuestParam( sceneId, memberId, mIndex, x300340_g_MP_UseTime)
                        if curTime - useitem < x300340_g_FanqiTime then
                            useItemArray[ i + 1] = memberId
                        end
                    end
                end
            end
        end

        -- ������鱻ɱ�����Ƿ�����Щ���ߵ���Ч��Χ��
        for i, id in useItemArray do
            -- ��ñ�ɱ�������������
            local x, z = GetWorldPos( sceneId, objId)
            local mIndex = GetQuestIndexByID( sceneId, id, x300340_g_MissionId)
            -- ���ʹ�á�����¯�㡱������
            local ux = GetQuestParam( sceneId, id, mIndex, x300340_g_MP_PosX)
            local uz = GetQuestParam( sceneId, id, mIndex, x300340_g_MP_PosZ)
            -- print(ux)
            -- print(uz)
            if ux ~= 0 and uz ~= 0 then
                -- print( abs( x - ux) )
                -- print( abs( z - uz) )
                if abs( x - ux) < x300340_g_Range and abs( z - uz) < x300340_g_Range then
                    -- ����������ڶ����Աʹ�õġ�����¯�㡱����Ч��Χ��
                    bUseFanqi = 1
                    break
                end
            end
        end

        -- print( bUseFanqi)
        local DropItem = 0
        if bUseFanqi == 1 then
            -- ��100%�ĸ��ʵ��������������Ʒ������������ĳ�Ա
            DropItem = 1
        else
            -- �����ˡ�����¯�㡱��ʱ���û������Ч��ΰ֮�⣬��10%�ĸ��ʵ��������������Ʒ������������ĳ�Ա
            local temp = random( 1, 100)
            -- print( "random = "..temp)
            if temp > 45 and temp <= 55 then
                DropItem = 1
            end
        end

        -- ���������ƷId
        local toGiveItem = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)

        -- ��������Ʒ�ŵ���ұ�����
        if DropItem == 1 then
            if nearteamnum <= 1 then   -- �����������������Ա������Χ
                local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
                if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                    BeginAddItem( sceneId)
                    AddItem( sceneId, toGiveItem, 1)
                    local result = EndAddItem( sceneId, selfId)
                    if result == 0 then
                		BeginQuestEvent( sceneId)
                		AddQuestText( sceneId, "�����������޷��õ�������Ʒ" )
                		EndQuestEvent( sceneId)
                		DispatchQuestTips( sceneId, selfId)
                        return
                    end
                    AddItemListToPlayer( sceneId, selfId)
                    local str = "#Y��������Ʒ��#G#{_ITEM"..toGiveItem.."}";
                    BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, str.."#Y ("..GetItemCount(sceneId, selfId, toGiveItem).."/"..x300340_g_FinishCount..")" )
                    EndQuestEvent( sceneId)
                    DispatchQuestTips( sceneId, selfId )
                    --Msg2Player(sceneId, selfId, str, 8, 2);
                    x300340_ProcQuestLogRefresh( sceneId, selfId, x300340_g_MissionId)
                end
            else  -- ���������
                local Count = 1
                local arrMember = {}
                -- �ռ�����������������Id
                for i = 0, nearteamnum - 1 do
                    -- ��ö����Ա��ID
                    local memberId = GetNearTeamMember( sceneId, selfId, i)
                    if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
                        local misIndex = GetQuestIndexByID( sceneId, memberId, x300340_g_MissionId)
                        if IsHaveQuestNM( sceneId, memberId, x300340_g_MissionId) ~= 0 and GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then -- ��������������δ���
                            arrMember[ Count] = memberId
                            Count = Count + 1
                        end
                    end
                end
                if Count == 1 then
                    -- ������������ֱ�ӷ���
                    return
                end
                -- �������ѡһ���˵õ�������Ʒ
                local i = random( 1, getn( arrMember) )
                local misIndex = GetQuestIndexByID( sceneId, arrMember[ i], x300340_g_MissionId)
                toGiveItem = GetQuestParam( sceneId, arrMember[ i], misIndex, x300340_g_MP_TargetItemId)
                BeginAddItem( sceneId)
                AddItem( sceneId, toGiveItem, 1)
                local result = EndAddItem( sceneId, arrMember[ i] )
                if result == 0 then
                    BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, "�����������޷��õ�������Ʒ" )
                    EndQuestEvent( sceneId)
                    DispatchQuestTips( sceneId, arrMember[ i] )
                    return
                end
                AddItemListToPlayer( sceneId, arrMember[ i] )
                local str = "#Y��������Ʒ��#G#{_ITEM"..toGiveItem.."}";
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId,  str.."#Y ("..GetItemCount(sceneId, arrMember[ i], toGiveItem).."/"..x300340_g_FinishCount..")" )
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, arrMember[ i] )
                --Msg2Player(sceneId, selfId, str, 8, 2)
                x300340_ProcQuestLogRefresh( sceneId, arrMember[ i], x300340_g_MissionId)
            end
            -- ֻҪ�õ�һ��������Ʒ������������ɱ��
            -- local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
            -- SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        end
    end
end

--��Ʒ�ı�
function x300340_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--Ѱ�Ҳ��ϵ�������ɺ�����Ӻϳ�����
	return 0
end

function x300340_MissionComplateInfo( sceneId, selfId, targetId)
	-- DelQuest( sceneId, selfId, MissionId )
	BeginQuestEvent( sceneId)
	AddQuestText( sceneId, "#Y"..x300340_g_MissionName.."#W\n\tлл�㣬���ֱ�ǲ�ԭ���ư��ߣ���Ϊ���������" )
    local exp = GetLevel( sceneId, selfId) * x300340_g_ExperienceCoefficient
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end
    -- 090302 ��������
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel > 80 then
        playerLevel = 80
    end
    local money = playerLevel * x300340_g_MoneyCoefficient
    AddQuestMoneyBonus1( sceneId, money)
	EndQuestEvent( sceneId)
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300340_g_ScritpId, x300340_g_MissionId)
end

function x300340_MissionComplate( sceneId, selfId, targetId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
    -- �����ұ�����������Ʒ������
    local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
    -- �����ҵȼ�
    local playerLevel = GetLevel( sceneId, selfId)
    DelQuest( sceneId, selfId, MissionId)
    -- ���վ���ֵ
    local xp = x300340_g_ExperienceCoefficient * playerLevel
    DelItem( sceneId, selfId, itemId, itemCount)
    AddExp( sceneId, selfId, xp)
    -- 090302 ��������
    if playerLevel > 80 then
        playerLevel = 80
    end
    local money = playerLevel * x300340_g_MoneyCoefficient
    AddMoney( sceneId, selfId, 1, money)

    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, x300340_g_strMissionComplete)
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)
    Msg2Player( sceneId, selfId, x300340_g_strMissionComplete, 8, 2)

    Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", xp), 8, 2)
    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, format( "���#R����%d��#cffcf00�Ľ���", xp) )
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)

    Msg2Player( sceneId, selfId, format( "���#R����#{_MONEY%d}#cffcf00�Ľ���", money), 8, 3)
    Msg2Player( sceneId, selfId, format( "���#R����#{_MONEY%d}#cffcf00�Ľ�����", money), 8, 2)

    -- ���½�����ʱ�䣬�����һ������񣬵ڶ��콻�������������ٽӵ�����
    local today = GetDayOfYear()
    x300340_SetAcceptTime( sceneId, selfId, today)

    -- д��־
    GamePlayScriptLog( sceneId, selfId, 442)
end

-- 
function x300340_GetAcceptTime( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_GUJI_ACCEPTTIME[ 1], MD_GUJI_ACCEPTTIME[ 2], MD_GUJI_ACCEPTTIME[ 3] )
end

function x300340_SetAcceptTime( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_GUJI_ACCEPTTIME[ 1], MD_GUJI_ACCEPTTIME[ 2], MD_GUJI_ACCEPTTIME[ 3], value)
end

function x300340_ProcQuestAbandon( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300340_g_MissionId)
    local id = GetQuestParam( sceneId, selfId, misIndex, x300340_g_MP_TargetItemId)
    local count = GetItemCountInBag( sceneId, selfId, id)
    if count > 0 then
        DelItem( sceneId, selfId, id, count)
    end

	local ret = 0
	local MissionName = GetQuestNameNM( sceneId, selfId, x300340_g_MissionId)
	ret = DelQuestNM( sceneId, selfId, x300340_g_MissionId)
	if ret == 1 then
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, x300340_g_strMissionAbandon);
		EndQuestEvent( sceneId);
		DispatchQuestTips( sceneId, selfId);
		Msg2Player( sceneId, selfId, x300340_g_strMissionAbandon, 8, 2)
	end

    local today = GetDayOfYear()

    x300340_SetAcceptTime( sceneId, selfId, today)
end

function x300340_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end

function x300340_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end
