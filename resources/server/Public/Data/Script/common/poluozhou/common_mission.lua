--MisDescBegin

-- ��������������ű�ID
x305015_g_ScriptId = 305015
-- ��������С�ȼ�
x305015_g_LevelLess = 70
-- ��������
x305015_g_MissionName           = "�����ˡ��Ĺ�����"

x305015_g_AwardItemId = 13011012 --������Ʒid

x305015_g_ExpBonus					= 	0   --���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x305015_g_BonusItem					=	{}	--��������Ʒ

x305015_g_BonusMoney1               = 	0  --������������
x305015_g_BonusMoney2               =   0  --�������ǰ�����
x305015_g_BonusMoney3               =   0  --�������󶨽��
x305015_g_BonusMoney4               =   0  --��������͢����
x305015_g_BonusMoney5               =   0  --��������������
x305015_g_BonusMoney6               = 450  --����������

x305015_g_BonusChoiceItem           =   {}

--MisDescEnd

-- ��������
x305015_g_MissionDescription    = "\t���ʱ�����������Ǻ���������֮���ս�����Ӽ��ң���Ȼ�ҹ���ʿ���˷���ɱ�У���������Դ�������棬���ǲ�û��ռ�����ơ�\n\t����̽�������������˸�����������פ�أ��ѻ��˴����������ʣ���������ܽ�����ߣ������ܴ�������ʿ�������ҹ����ӵĲ���Ҳ����Ī��ĺô���"
-- ������
x305015_g_MissionFlow           = "\t����Ǳ�뵽���Զ����פ�أ�����Ҿ���������ʣ���ȼü֮�����мǣ�������һ��Ҫ�������ǣ�����й¶�˴��ж����������������ı�����"
-- ������ʾ
x305015_g_MissionHelp           = "\t����Ҫɱ�����̽���ſ��Գɹ���ñ�����������������ʡ�"
-- ����Ŀ��
x305015_g_strMissionTarget      = "ɱ��@npc_%d���ɼ���������@item_%d#W(%d/3)��"
-- ����������ʾ�ַ�
x305015_g_strMissionAbandon     = "����������񣺡����ˡ��Ĺ�����"
-- ��������ַ���
x305015_g_strMissionComplete    = "����������񣺡����ˡ��Ĺ�����"
-- ����������ʾ
x305015_g_strMissionAccept      = "����������񣺡����ˡ��Ĺ�����"
-- ���������Ϣ
x305015_g_MissionContinue       = "\t����ǰ��#G%s#W�������л��ܲ�ԭ%s���ռ�100��#G%s#W�󽻸��ҡ�"
-- ����ظ�NPC
x305015_g_NPC                   = "@npc_%d"
-- ������Ҫ�ɼ�������
x305015_g_TotalCount            = 3
-- Ŀ�����ID
x305015_g_MP_TargetCountryId    = 1
-- �����ռ�Ŀ����Ʒ��ID
x305015_g_MP_TargetItemId       = 2
-- �ռ�������Ʒ����
x305015_g_MP_ItemCount          = 3
-- ����˫�������齱����
x305015_g_MP_DoubleDay          = 4
-- ��������ϵ��
x305015_g_MoneyCoefficient      = 0
-- ����ϵ��
x305015_g_ExperienceCoefficient = 15000
-- ��������־ID
x305015_g_AcceptQuestID         = 1281
-- ��������־ID
x305015_g_FinishQuestID         = 1282
-- ¥��NPC��Guid
x305015_g_Loulan_NPC_Guid       = 142600
-- ����NPC��Guid
x305015_g_Kunlun_NPC_Guid       = 142601
-- ��ɽNPC��Guid
x305015_g_Laiyin_NPC_Guid       = 142602
-- �ػ�NPC��Guid
x305015_g_Dunhuang_NPC_Guid     = 142603
-- ����NPC���ñ�
x305015_g_MissionNPC_Table      = {
                                    { typeId = 9720, posX = 50, posZ = 50, ai = 2, aiscript = 0, objGuid = 142600, campId = 16, liveTime = -1, name = "¥��̽��", timerId = 93 }, 
                                    { typeId = 9720, posX = 206, posZ = 50, ai = 2, aiscript = 0, objGuid = 142602, campId = 17, liveTime = -1, name = "��ɽ̽��", timerId = 94 }, 
                                    { typeId = 9720, posX = 50, posZ = 206, ai = 2, aiscript = 0, objGuid = 142601, campId = 18, liveTime = -1, name = "����̽��", timerId = 95 }, 
                                    { typeId = 9720, posX = 206, posZ = 206, ai = 2, aiscript = 0, objGuid = 142603, campId = 19, liveTime = -1, name = "�ػ�̽��", timerId = 96 }, 
}
-- �����������(1--366)��ÿ���һ����ҽӴ�����ʱ���´�ֵ
x305015_g_MissionUpdateDate     = 0
-- 
x305015_g_Group1                = { 0, 0 }
x305015_g_Group2                = { 0, 0 }
-- ���Ҽ���ID��Ӧ��
x305015_g_CountryTable          = {
                                    { id = 0, name = "¥��", npcId = 142600 }, 
                                    { id = 1, name = "��ɽ", npcId = 142602 }, 
                                    { id = 2, name = "����", npcId = 142601 }, 
                                    { id = 3, name = "�ػ�", npcId = 142603 }, 
}
-- NPC����ʱ�䣨���룩
x305015_g_TargetNPC_ReliveTime  = 180000
-- �ɼ���ÿ�����ɼ���
x305015_g_MaxCount              = 3
-- ������Ʒ��
x305015_g_ItemTable             = { 13070010, 13070011, 13070012 }
-- ��������
x305015_g_RongYu                = 450
-- ���������Ӧ��
x305015_g_MissionTable          = {
                                    7100,  
                                    7101,  
                                    7102,  
                                    7103,  
}

function x305015_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    if GetLevel( sceneId, selfId) >= x305015_g_LevelLess then
        local missionId = 0
        for i, item in x305015_g_MissionTable do
            if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
                missionId = item
                break
            end
        end
        if missionId ~= 0 then
            local state = GetQuestStateNM( sceneId, selfId, targetId, x305015_GetMissionId( sceneId, selfId, missionId) )
            AddQuestNumText( sceneId, x305015_GetMissionId( sceneId, selfId, missionId), x305015_g_MissionName, state)
        else
            local state = GetQuestStateNM( sceneId, selfId, targetId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1] )
            AddQuestNumText( sceneId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1], x305015_g_MissionName, state)
        end
    end
end

function x305015_ProcEventEntry( sceneId, selfId, targetId, MissionId)
    if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������    
        -- ��ʾ����������Ϣ
        x305015_DispatchMissionInfo( sceneId, selfId, targetId)
    else--����ǲ��ǿ����ύ    
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
        local isFinish = GetQuestParam( sceneId, selfId, misIndex, 7)
		if isFinish > 0 then -- �������������
			x305015_MissionComplateInfo( sceneId, selfId, targetId, MissionId) -- ��ʾ�����Ϣ
		else
			x305015_MissionContinue( sceneId, selfId, targetId, MissionId) -- ��ʾ����δ�����Ϣ
		end
    end
end

-- ���������Ϣ
function x305015_MissionContinue( sceneId, selfId, targetId, MissionId)
	BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "#Y"..x305015_g_MissionName)
        AddQuestText( sceneId, "\t��ô����û���ҵ�������������ʣ�" )
	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- ��ʾ����������Ϣ
function x305015_DispatchMissionInfo( sceneId, selfId, NPCId )
	local level = GetLevel( sceneId, selfId)

	BeginQuestEvent( sceneId)

		--������Ϣ
		AddQuestText( sceneId, "#Y"..x305015_g_MissionName)
		AddQuestText( sceneId, x305015_g_MissionDescription)

		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, x305015_g_MissionFlow )
		AddQuestText( sceneId, " ")
		AddQuestText( sceneId, " ")

		--��ʾ��Ϣ
        AddQuestText( sceneId, "#YС��ʾ��")
        AddQuestText( sceneId, x305015_g_MissionHelp)
        -- AddQuestText( sceneId, " ")

		--��������Ϣ

		--1������
		local exp = GetLevel( sceneId, selfId) * x305015_g_ExperienceCoefficient
		if exp > 0 then
			AddQuestExpBonus( sceneId, exp)
		end

		--2����Ǯ1
        local money = level * x305015_g_MoneyCoefficient
		if money > 0 then
			AddQuestMoneyBonus1( sceneId, money)
		end

		--3����Ǯ2
		if x305015_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x305015_g_BonusMoney2 )
		end

		--4����Ǯ3
		if x305015_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x305015_g_BonusMoney3 )
		end

		--��������
		if x305015_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x305015_g_BonusMoney4 )
		end

		--��͢����
		if x305015_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x305015_g_BonusMoney5 )
		end

		--����ֵ
		if x305015_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x305015_g_BonusMoney6 )
		end

		--5���̶���Ʒ
		for i, item in x305015_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6����ѡ��Ʒ
		for i, item in x305015_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end

	EndQuestEvent()

	DispatchQuestInfoNM( sceneId, selfId, NPCId, x305015_g_ScriptId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1]);
end

-- ��鵱���Ƿ��Ѿ����ܹ�������񣬽��ܹ�����1�����򷵻�0
function x305015_CheckDayTimes( sceneId, selfId)
    local today = GetDayOfYear()

    if x305015_GetAcceptDate( sceneId, selfId) ~= today then
        return 0
    else
        return 1
    end
end

function x305015_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
    if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then   -- û���������
        -- ��鵱���Ƿ��Ѿ������������
        local today = GetDayOfYear()
        if x305015_GetAcceptDate( sceneId, selfId) == today then
            Msg2Player( sceneId, selfId, "������Ѿ���ɹ������������������", 8, 3)
            return
        end
    	local result = AddQuest( sceneId, selfId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1], x305015_g_ScriptId, 1, 0, 1, 0)
    	if( result == 0) then
    		local str = "�����������������ʧ�ܣ�"
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, str)
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
          	Msg2Player(sceneId, selfId, str, 8, 2)
    		return 0
        else
            -- ���½�����ʱ��
            x305015_SetAcceptDate( sceneId, selfId, today)

            -- ���յ�һ�ν�����
            local oppoId = 0
            -- ��ý�������ҹ���
            local country = GetCurCountry( sceneId, selfId)
            if today ~= x305015_g_MissionUpdateDate then
                x305015_g_MissionUpdateDate = today
                x305015_g_Group1[ 1] = country
                -- ����������Ŀ�����
                local allCountry = {}
                local count = 0
                -- �����֮�����������Id����allCountry
                for i = 0, 3 do
                    if country ~= i then
                        count = count + 1
                        allCountry[ count] = i
                    end
                end
                -- ���������������ѡһ��
                local rcount = 0
                x305015_g_Group1[ 2] = allCountry[ random( 1, count) ]
                oppoId = x305015_g_Group1[ 2]
                local remain = {}
                -- �ռ�ʣ����������
                for i, item in allCountry do
                    if x305015_g_Group1[ 2] ~= item then
                        rcount = rcount + 1
                        remain[ rcount] = item
                    end
                end
                x305015_g_Group2[ 1] = remain[ 1]
                x305015_g_Group2[ 2] = remain[ 2]

                -- ÿ��һ�ĵ�һ�ν�����ʱ�������ÿ�����ұ���˫��������
                -- if GetWeek() == 1 then
                    -- SetCountryQuestData( sceneId, 0, CD_INDEX_POLUOZHOU_RANDOM_DAY, random( 1, 7) - 1)
                    -- SetCountryQuestData( sceneId, 1, CD_INDEX_POLUOZHOU_RANDOM_DAY, random( 1, 7) - 1)
                    -- SetCountryQuestData( sceneId, 2, CD_INDEX_POLUOZHOU_RANDOM_DAY, random( 1, 7) - 1)
                    -- SetCountryQuestData( sceneId, 3, CD_INDEX_POLUOZHOU_RANDOM_DAY, random( 1, 7) - 1)
                -- end
            else
                -- ֱ�Ӵ�ȫ�ֱ���ȡ
                if country == x305015_g_Group1[ 1] or country == x305015_g_Group1[ 2] then
                    if country == x305015_g_Group1[ 1] then
                        oppoId = x305015_g_Group1[ 2]
                    else
                        oppoId = x305015_g_Group1[ 1]
                    end
                else
                    if country == x305015_g_Group2[ 1] then
                        oppoId = x305015_g_Group2[ 2]
                    else
                        oppoId = x305015_g_Group2[ 1]
                    end
                end
            end

            -- ��ȡ���˫��������
            -- GetCountryQuestData( sceneId, selfId, CD_INDEX_POLUOZHOU_RANDOM_DAY, x305015_g_ScriptId, -1, "GetRandomDay" )

            local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1] )
			local targetItem = x305015_g_ItemTable[ random( 1, 3) ]
            SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
            SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_TargetCountryId, oppoId)
            SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId, targetItem)
            local minute = GetMinOfDay()
            if GetWeek() == 3 and minute >= 1200 and minute <= 1230 then
                SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_DoubleDay, 2)
            end
            SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_ItemCount, 0)

            -- �����������
            x305015_ProcQuestLogRefresh( sceneId, selfId, MissionId)

    		Msg2Player( sceneId, selfId, x305015_g_strMissionAccept, 8, 2)
    		Msg2Player( sceneId, selfId, x305015_g_strMissionAccept, 8, 3)

            -- ��ʾ�����ȡ����
			local name = ""
			for i, item in x305015_g_CountryTable do
				if oppoId == item.id then
					name = item.name
				end
			end
    		BeginQuestEvent( sceneId)
			AddQuestText( sceneId, "#Y"..x305015_g_MissionName)
    		AddQuestText( sceneId, format( "\tѰ�Ҳ�����#G%s̽��#W��������©��Ϣ��Ȼ����%sԶ����פ����Χ��ȡ@item_%d#W��", name, name, targetItem) )
    		EndQuestEvent( sceneId)
            DispatchQuestEventList( sceneId, selfId, targetId)

            -- д��־
            GamePlayScriptLog( sceneId, selfId, x305015_g_AcceptQuestID)
        end
    else
        
        x305015_MissionComplate( sceneId, selfId, targetId, MissionId)
    end
end

function x305015_GetRandomDay( sceneId, selfId, MissionData, MissionId)
    if IsHaveQuestNM( sceneId, selfId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1] ) == 0 then
        return
    else
        local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1] )
        SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_DoubleDay, MissionData)
    end
end

function x305015_QuestLogRefresh( sceneId, selfId, MissionId)
    x305015_ProcQuestLogRefresh( sceneId, selfId, MissionId)
end

function x305015_GetMissionId( sceneId, selfId, MissionId)
    local missionId = x305015_g_MissionTable[ GetCurCountry( sceneId, selfId) + 1]
    if GetCurCountry( sceneId, selfId) ~= 0 then
        if MissionId == x305015_g_MissionTable[ 1] then
            missionId = MissionId
        end
    end

    return missionId
end

function x305015_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, MissionId) )
    local oppoId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetCountryId)
    local targetNPC = 0
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
    -- �����ұ�����������Ʒ������
    local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
	local npcId = 0
	local myCountry = GetCurCountry( sceneId, selfId)

    -- ���Ŀ�������
    for i, item in x305015_g_CountryTable do
        if oppoId == item.id then
            targetNPC = item.npcId
        end
    end
	-- �ظ�NPC
    for i, item in x305015_g_CountryTable do
        if myCountry == item.id then
			npcId = item.npcId
        end
    end

    BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "t",                            -- ����
                                x305015_g_MissionName,          -- ��������
                                format( x305015_g_strMissionTarget, targetNPC, itemId, itemCount),     -- ����Ŀ��
                                format( x305015_g_NPC, npcId),  -- ����NPC
                                x305015_g_MissionFlow,          -- ������
                                x305015_g_MissionDescription,   -- ��������
                                x305015_g_MissionHelp)          -- ������ʾ
    local exp = GetLevel( sceneId, selfId) * x305015_g_ExperienceCoefficient
    AddQuestExpBonus( sceneId, exp)
    -- 090302 ��������
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel > 80 then
        playerLevel = 80
    end
    --local money = playerLevel * x305015_g_MoneyCoefficient
    AddQuestMoneyBonus6(sceneId, x305015_g_BonusMoney6 )

    EndQuestEvent()
    DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x305015_Accept( sceneId, selfId, MissionId )
	return -1
end

function x305015_OnOpenItemBox( sceneId, selfId, targetId, growpointId, itemIndex)
    -- �����û������
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end

    if missionId == 0 then
        return 1
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )
    local oppoId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetCountryId)
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
    if itemId ~= itemIndex then
        Msg2Player( sceneId, selfId, "������������ʾ��������Ӧ����Դ��", 8, 3)
        return 1
    end
    local x, z = GetWorldPos( sceneId, selfId)
    -- local country = GetCurCountry( sceneId, selfId)
    if oppoId == 0 then    -- ¥��
        if FindMonsterByGUID( sceneId, x305015_g_Loulan_NPC_Guid) ~= 4294967295 then
            Msg2Player( sceneId, selfId, "����ȥɱ��#G¥��̽��#cffcf00�����ɼ���", 8, 3)
            return 1
        else
            if x > 1 and x < 80 and z > 1 and z < 80 then
                return 0
            else
                Msg2Player( sceneId, selfId, "������#G¥��̽��#cffcf00�����ɼ�", 8, 3)
                return 1
            end
        end
    elseif oppoId == 1 then    -- ��ɽ
        if FindMonsterByGUID( sceneId, x305015_g_Laiyin_NPC_Guid) ~= 4294967295 then
            Msg2Player( sceneId, selfId, "����ȥɱ��#G��ɽ̽��#cffcf00�����ɼ���", 8, 3)
            return 1
        else
            if x > 176 and x < 256 and z > 1 and z < 80 then
                return 0
            else
                Msg2Player( sceneId, selfId, "������#G��ɽ̽��#cffcf00�����ɼ�", 8, 3)
                return 1
            end
        end
    elseif oppoId == 2 then    -- ����
        if FindMonsterByGUID( sceneId, x305015_g_Kunlun_NPC_Guid) ~= 4294967295 then
            Msg2Player( sceneId, selfId, "����ȥɱ��#G����̽��#cffcf00�����ɼ���", 8, 3)
            return 1
        else
            if x > 1 and x < 80 and z > 176 and z < 256 then
                return 0
            else
                Msg2Player( sceneId, selfId, "������#G����̽��#cffcf00�����ɼ�", 8, 3)
                return 1
            end
        end
    elseif oppoId == 3 then    -- �ػ�
        if FindMonsterByGUID( sceneId, x305015_g_Dunhuang_NPC_Guid) ~= 4294967295 then
            Msg2Player( sceneId, selfId, "����ȥɱ��#G�ػ�̽��#cffcf00�����ɼ���", 8, 3)
            return 1
        else
            if x > 176 and x < 256 and z > 176 and z < 256 then
                return 0
            else
                Msg2Player( sceneId, selfId, "������#G�ػ�̽��#cffcf00�����ɼ�", 8, 3)
                return 1
            end
        end
    end
end

function x305015_OnRecycle( sceneId, selfId, targetId, growpointId, itemIndex)
    -- print( "***x305015_OnRecycle***"..growpointId.."index: "..itemIndex)
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end

    if missionId == 0 then
        return 0
    end

    -- ������ұ������е���Ʒ�������ñ��βɼ������
    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )
    local itemCount = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_ItemCount)
    local maxCount = x305015_g_MaxCount
    if itemCount > x305015_g_TotalCount - x305015_g_MaxCount then
        maxCount = x305015_g_TotalCount - itemCount
    end
    if maxCount == 0 then
        Msg2Player( sceneId, selfId, "�����Ѿ���ɣ����ܼ����ɼ�", 8, 3)
        return 0
    end
    local itemCount = random( 1, maxCount)
    BeginAddItem( sceneId)
    AddItem( sceneId, itemIndex, itemCount)
    if EndAddItem( sceneId, selfId) > 0 then
        AddItemListToPlayer( sceneId, selfId)

        -- �����������
        x305015_ProcQuestLogRefresh( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )

        return 1
    else
        Msg2Player( sceneId, selfId, "�޷��õ��ɼ���Ʒ�������������", 8, 3)
        return 0
    end
end

--ɱ������
--����ID, �Լ���ID(���״̬��Ϊ�������Ա��Id), �����λ�ú�, ����objId, ����ID
function x305015_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

--��Ʒ�ı�
function x305015_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)--Ѱ�Ҳ��ϵ�������ɺ�����Ӻϳ�����
    -- �����û������
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end

    if missionId == 0 then
        return 1
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
    if itemId ~= itemdataId then
        return 0
    end

    -- �����ұ�����������Ʒ������
    local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
    SetQuestByIndex( sceneId, selfId, misIndex, x305015_g_MP_ItemCount, itemCount)
    if itemCount >= x305015_g_TotalCount then
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        Msg2Player( sceneId, selfId, "��������ɣ���ȥ�������", 8, 3)
    else
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
    end

	return 0
end

function x305015_MissionComplateInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)
	AddQuestText( sceneId, "#Y"..x305015_g_MissionName.."#W\n\t������Ӣ�ۣ�����Զ�����Ľ�������Щ���ʲ�֪������ȶ����������˵��ֵܣ�" )
    local exp = GetLevel( sceneId, selfId) * x305015_g_ExperienceCoefficient
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end
    -- 090302 ��������
    local playerLevel = GetLevel( sceneId, selfId)
    if playerLevel > 80 then
        playerLevel = 80
    end
    --local money = playerLevel * x305015_g_MoneyCoefficient
    AddQuestMoneyBonus6( sceneId, x305015_g_BonusMoney6)
	EndQuestEvent( sceneId)
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end
	DispatchQuestInfoNM( sceneId, selfId, targetId, x305015_g_ScriptId, x305015_GetMissionId( sceneId, selfId, missionId) )
end

function x305015_MissionComplate( sceneId, selfId, targetId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, MissionId) )
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
    local doubleDay = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_DoubleDay)
    -- �����ұ�����������Ʒ������
    local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
    -- �����ҵȼ�
    local playerLevel = GetLevel( sceneId, selfId)
    DelQuest( sceneId, selfId, MissionId)
    -- ���վ���ֵ
    local xp = x305015_g_ExperienceCoefficient * playerLevel
    DelItem( sceneId, selfId, itemId, itemCount)
    AddExp( sceneId, selfId, xp)
    -- 090302 ��������
    -- if playerLevel > 80 then
        -- playerLevel = 80
    -- end
    -- local money = playerLevel * x305015_g_MoneyCoefficient
    --AddMoney( sceneId, selfId, 1, money)

    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, x305015_g_strMissionComplete)
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)
    Msg2Player( sceneId, selfId, x305015_g_strMissionComplete, 8, 2)

    Msg2Player( sceneId, selfId, format( "����#R����%d��#cffcf00�Ľ���", xp), 8, 2)
    BeginQuestEvent( sceneId)
    AddQuestText( sceneId, format( "����#R����%d��#cffcf00�Ľ���", xp) )
    EndQuestEvent( sceneId)
    DispatchQuestTips( sceneId, selfId)

    --Msg2Player( sceneId, selfId, format( "���#R����#{_MONEY%d}#cffcf00�Ľ���", money), 8, 3)
    --Msg2Player( sceneId, selfId, format( "���#R����#{_MONEY%d}#cffcf00�Ľ�����", money), 8, 2)

    -- ������
    AddHonor(sceneId, selfId, x305015_g_RongYu)
    Msg2Player( sceneId, selfId, format( "����#R%d������#cffcf00�Ľ���", x305015_g_RongYu), 8, 3)
    Msg2Player( sceneId, selfId, format( "����#R%d������#cffcf00�Ľ�����", x305015_g_RongYu), 8, 2)

    local minute = GetMinOfDay()
    if doubleDay == 2 and GetWeek() == 3 and minute >= 1200 and minute <= 1230 then
        --AddExp( sceneId, selfId, xp)
        --Msg2Player( sceneId, selfId, format( "��������������20��00-20��30֮���ȡ���������������ö���#R����%d��#cffcf00�Ľ���", xp), 8, 3)
        --Msg2Player( sceneId, selfId, format( "��������������20��00-20��30֮���ȡ���������������ö���#R����%d��#cffcf00�Ľ�����", xp), 8, 2)
    end

    -- ���½�����ʱ�䣬�����һ������񣬵ڶ��콻�������������ٽӵ�����
    local today = GetDayOfYear()
    x305015_SetAcceptDate( sceneId, selfId, today)

    -- д��־
    GamePlayScriptLog( sceneId, selfId, x305015_g_FinishQuestID)
end

function x305015_GetAcceptDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_POLO_DATE[ 1], MD_POLO_DATE[ 2], MD_POLO_DATE[ 3] )
end

function x305015_SetAcceptDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_POLO_DATE[ 1], MD_POLO_DATE[ 2], MD_POLO_DATE[ 3], value)
end

function x305015_ProcQuestAbandon( sceneId, selfId, MissionId)
    local missionId = 0
    for i, item in x305015_g_MissionTable do
        if IsHaveQuestNM( sceneId, selfId, item) ~= 0 then
            missionId = item
            break
        end
    end
    local misIndex = GetQuestIndexByID( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) )
    local itemId = GetQuestParam( sceneId, selfId, misIndex, x305015_g_MP_TargetItemId)
	if DelQuestNM( sceneId, selfId, x305015_GetMissionId( sceneId, selfId, missionId) ) == 1 then
		Msg2Player( sceneId, selfId, x305015_g_strMissionAbandon, 8, 3)
		Msg2Player( sceneId, selfId, x305015_g_strMissionAbandon.."��", 8, 2)
        x305015_SetAcceptDate( sceneId, selfId, GetDayOfYear() )
        -- �����ұ�����������Ʒ������
        local itemCount = GetItemCountInBag( sceneId, selfId, itemId)
        if itemCount > 0 then
            -- ɾ��������Ʒ
            DelItem( sceneId, selfId, itemId, itemCount)
        end
	end
end

function x305015_ProcQuestSubmit( sceneId, selfId, targetId, chooseId, MissionId )
end

function x305015_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end
