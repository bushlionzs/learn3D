--MisDescBegin

x300332_g_ScriptId 					= 	300332                  --�ű�ID
x300332_g_MissionId 				= 	8091                    --����ID

x300332_g_MissionKind 				= 	1                       --��������
x300332_g_LevelLess					= 	0                      --�������ŵȼ�  <=0 ��ʾ������

x300332_g_MissionName				= 	"�����ˡ�������"
x300332_g_MissionTarget				= 	"  ����@npc_%d(%d/1)"          --����Ŀ��
x300332_g_MissionInfo				= 	""            --������Ϣ
x300332_g_ContinueInfo				= 	"\t��ô����Ը�������Щ�ɶ�ĵ�����ô����������Ҫ������ɫ��ѡ�ˡ�"  --���������Ϣ
x300332_g_MissionCompleted			= 	"\t����û�뵽����ô��ͻ��ܵ����ͣ�����̫���ˣ�\n\t��һ���Ѽ��˲��ٵ����͵Ĳر�ͼ��Ƭ�ɣ����������͸���һЩ�ر�ͼ��Ƭ�������ռ���#R���Ų�ͬ�Ĳر�ͼ��Ƭ#W֮���һ����ϳ�һ�������Ĳر�ͼ��"  --���������Ϣ
x300332_g_MissionHelp				=	"\t#G��˵��Щ����������Ҳ�������ƵĲر�ͼ����������ǵĹ����У���Ҳ���п��ܻ��òر�ͼ��һ���֡�#W"          --������ʾ��Ϣ

--Ŀ��
x300332_g_ExtTarget					=	{ {type=20,n=10 ,target=""} }


--����
x300332_g_ExpBonus					= 	0                    	--���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x300332_g_BonusItem					=	{}	--��������Ʒ

x300332_g_BonusMoney1               = 	0   --������������
x300332_g_BonusMoney2               =   0   --�������ǰ�����
x300332_g_BonusMoney3               =   0   --�������󶨽��
x300332_g_BonusMoney4               =   0   --��������͢����
x300332_g_BonusMoney5               =   0   --��������������
x300332_g_BonusMoney6               =   0   --����������

x300332_g_BonusChoiceItem           =   {}


--MisDescEnd

--����Ŀ��˳��
x300332_MP_TARGET1					= 1         -- Ҫɱ��1
x300332_MP_TARGET4					= 4         -- 
x300332_MP_FINISH                   = 7         -- ��ҽ�����ʱ�ĵȼ�
x300332_MP_ISCOMPLETE				= 0	        -- ������� 0δ��ɣ� 1���

-- ����������ʾ
x300332_g_strAcceptMission          = "�����������񣺡����ˡ�������"
-- ����������ʾ
x300332_g_strAbandonMission         = "�����������񣺡����ˡ�������"
-- ���������ʾ
x300332_g_strFinishMission          = "����������񣺡����ˡ�������"
-- ����������ֹ���������ʱ��(����)
-- x300332_g_PunishTime                = 2

-- ��������������С�ȼ�
x300332_g_PlayerMinLevel            = 40
-- ���������������ȼ�
x300332_g_PlayerMaxLevel            = 80

x300332_SubmitNPCGUID				= 124057	--������NPC GUID

-- ������Ʒ���ļ���ͼ��Ƭ��Id�μ�common.tab
x300332_ItemID_Table                ={
                                        {index = 1, itemid = 12030109},-- �����ر�ͼ��Ƭ����β��
                                        {index = 2, itemid = 12030110},-- �����ر�ͼ��Ƭ����צ��
										{index = 3, itemid = 12030111},-- �����ر�ͼ��Ƭ������
										{index = 4, itemid = 12030112},-- �����ر�ͼ��Ƭ�����ף�
                                     }                                     


-- ����С��ʾ
x300332_g_MissionTips               = "\t#G��˵��Щ����������Ҳ�������ƵĲر�ͼ����������ǵĹ����У���Ҳ���п��ܻ��òر�ͼ��һ���֡�#W"
-- ��������
x300332_g_MissionDescription        = "\t��˵����������ʱ���������ү���պ��ҽ������ߵĽ����Ʊ���������������ɾ���ص���Ϊ���ڵ�ս�Һͽ��������������֪���ˡ�\n\t ��������Ž�����������̫��ɽ��̩ɽ��һЩ�����ͷ�ӵ�����������ھ���ͼ�ҵ��������ء���������Ҵ�Ԫ���𣬱���������ȻӦ���Ҵ�Ԫ���У�����������ί����ǰȥ������Щ�����ͣ�\n\t ��Ȼ����������Щ���������ϻ����������صĲر�ͼ��Ƭ��Ҫ������������Щ�����ͣ���ô��Щ�ر�ͼ��Ƭ�����Ǹ���ĳ��Ͱɣ�\n\t#Gע��������ÿ��ֻ�ܽ�ȡ10�Ρ�#W"
-- ������
x300332_g_MissionBook               = "\t�ҵ���������Щ�����ͣ����������㽫�õ���Ӧ�Ļر���"

x300332_g_MonsterTable              = {
                                        { monsterId = 3250, posId = 173500, name = "���Ƶ�����", minLevel = 40, maxLevel = 45 }, 
                                        { monsterId = 3251, posId = 173501, name = "��Į������", minLevel = 45, maxLevel = 50 }, 
                                        { monsterId = 3252, posId = 173502, name = "���е�����", minLevel = 50, maxLevel = 55 }, 
                                        { monsterId = 3253, posId = 173503, name = "�ڷ������", minLevel = 55, maxLevel = 60 }, 
                                        { monsterId = 3254, posId = 173504, name = "��˹������", minLevel = 60, maxLevel = 65 }, 
                                        { monsterId = 3255, posId = 173505, name = "��ɽ������", minLevel = 65, maxLevel = 70 }, 
                                        { monsterId = 3256, posId = 173506, name = "��ͷ������", minLevel = 70, maxLevel = 75 }, 
                                        { monsterId = 3257, posId = 173507, name = "���ĵ�����", minLevel = 75, maxLevel = 80 }, 
                                        { monsterId = 3258, posId = 173508, name = "��յ�����", minLevel = 80, maxLevel = 161}, 
}

-- ɱ�ּ���
x300332_g_KillTargetCount           = 1
x300332_g_MaxTimes                  = 10
x300332_g_strOverMaxTimes           = format( "ÿ��ֻ�ܽ�#R%d#cffcf00���������", x300332_g_MaxTimes)

--**********************************
--�о��¼�
--**********************************
function x300332_ProcEnumEvent( sceneId, selfId, NPCId, MissionId )
	local level = GetLevel( sceneId, selfId)
	if( level < x300332_g_PlayerMinLevel) then
		 return 1
	end

    local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300332_g_MissionId)
    if( bHaveMission <= 0 and level >= x300332_g_PlayerMinLevel) then
        local state = GetQuestStateNM( sceneId, selfId, NPCId, x300332_g_MissionId)
        AddQuestNumText( sceneId, x300332_g_MissionId, x300332_g_MissionName, state)
    end
end

--**********************************
--������ں���
--**********************************
function x300332_ProcEventEntry(sceneId, selfId, NPCId, MissionId, nExtIdx)	--����������ִ�д˽ű�
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId)
	if( bHaveMission > 0) then
		local bDone = x300332_CheckSubmit(sceneId, selfId, NPCId)
		if( bDone > 0) then
			if nExtIdx ~= -1 then
				x300332_DispatchCompletedInfo( sceneId, selfId, NPCId ) --���������ʾ
			end
		else
			if nExtIdx ~= -1 then
				x300332_DispatchContinueInfo( sceneId, selfId, NPCId ) --δ���������ʾ
			end
		end
	else
		x300332_DispatchMissionInfo( sceneId, selfId, NPCId )	--������Ϣ��ʾ
	end
end

---------------------------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------------------------
function x300332_ProcAcceptCheck( sceneId, selfId, npcId )
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId);
	if(bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

-- �Ƿ������������ĳͷ�ʱ����
-- function x300332_IsPunish( sceneId, selfId)
    -- if x300332_GetDate( sceneId, selfId) == GetDayOfYear() then
        -- if abs( GetMinOfDay() - x300332_GetAbandonTime( sceneId, selfId) ) >= x300332_g_PunishTime then
            -- return 0
        -- else
            -- return 1
        -- end
    -- else
        -- if GetMinOfDay() + 1440 - x300332_GetAbandonTime( sceneId, selfId) >= x300332_g_PunishTime then
            -- return 0
        -- else
            -- return 1
        -- end
    -- end
-- end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestAccept( sceneId, selfId, targetId, missionId )
	if IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId) > 0 then
    else
        -- ����Ƿ������������ĳͷ�ʱ����
        -- if x300332_IsPunish( sceneId, selfId) > 0 then
            -- Msg2Player( sceneId, selfId, "�����ϴη���������"..x300332_g_PunishTime.."���ӣ�������ȡ����", 8, 3)
            -- return
        -- end
        local today = GetDayOfYear()
        -- ��鵱����ɴ���
        if x300332_GetDate( sceneId, selfId) == today then
            if x300332_GetTimes( sceneId, selfId) >= x300332_g_MaxTimes then
                Msg2Player( sceneId, selfId, x300332_g_strOverMaxTimes, 8, 3)
                Msg2Player( sceneId, selfId, x300332_g_strOverMaxTimes, 8, 2)
                return
            end
        else
            -- ���������ɴ���
            x300332_SetTimes( sceneId, selfId, 0)
            x300332_SetDate( sceneId, selfId, today)
        end

    	local ret	= AddQuest( sceneId, selfId, x300332_g_MissionId, x300332_g_ScriptId, 1, 0, 0, 1)
    	if( ret == 0) then
    		BeginQuestEvent( sceneId)
    		AddQuestText( sceneId, "�����������������ʧ�ܣ�" )
    		EndQuestEvent( sceneId)
    		DispatchQuestTips( sceneId, selfId)
    		return 0;
    	end

        -- ������ҵȼ���������Ŀ���
    	local level = GetLevel( sceneId, selfId)
        local monsterId = 0
        local name = "������"
        for i, item in x300332_g_MonsterTable do
            if level >= item.minLevel and level < item.maxLevel then
                monsterId = item.monsterId
                name = item.name
                break
            end
        end

        local misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_TARGET1, monsterId)
    	SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_TARGET4, 0)
        -- ����������ɱ��
        SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_ISCOMPLETE, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_FINISH, 0)

        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300332_g_MissionName)
            AddQuestText( sceneId, "#r" )
            AddQuestText( sceneId, "#Y����Ŀ��:" )
    		AddQuestText( sceneId, format( "����3��%s��", name) )
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)

        -- ��ʾ��ʾ��Ϣ
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, x300332_g_strAcceptMission)
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        -- ϵͳ��Ϣ
        Msg2Player( sceneId, selfId, x300332_g_strAcceptMission, 8, 2)

    	x300332_QuestLogRefresh( sceneId, selfId, x300332_g_MissionId )

        -- ��ʾ������Ϣ
        x300332_ShowMissionInfo( sceneId, selfId, targetId)

        -- д��־
        GamePlayScriptLog( sceneId, selfId, 731)
	end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId);
	if bHaveMission > 0 then
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300332_g_MissionId); 
		DelQuest(sceneId, selfId, x300332_g_MissionId);

        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, x300332_g_strAbandonMission)
        EndQuestEvent( sceneId)
        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, x300332_g_strAbandonMission, 8, 2)

        -- ������������
        --x300332_SetDate( sceneId, selfId, GetDayOfYear() )
        -- ���·�������ʱ��
        --x300332_SetAbandonTime( sceneId, selfId, GetMinOfDay() )
        x300332_SetTimes( sceneId, selfId, x300332_GetTimes( sceneId, selfId) + 1)
	end
end

---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x300332_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId, selfId, x300332_g_MissionId);
	return GetQuestParam(sceneId, selfId, misIndex, x300332_MP_ISCOMPLETE);
end

---------------------------------------------------------------------------------------------------
--��ý���
---------------------------------------------------------------------------------------------------
function x300332_GetBonus( sceneId, selfId,NpcID, SelectId )
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
	--��������
	-- local level = GetLevel( sceneId, selfId)
	-- local exp =( 1000 * 0.01 * level * 50)
    -- if exp > 0 then
		-- AddExp( sceneId, selfId, exp)
  		-- Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", exp), 8, 2)
        -- BeginQuestEvent( sceneId)
        -- AddQuestText( sceneId, format( "���#R����%d��#cffcf00�Ľ���", exp) )
        -- EndQuestEvent( sceneId)
        -- DispatchQuestTips( sceneId, selfId)
	-- end

	--������Ǯ1
	if x300332_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300332_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("���#R����#{_MONEY%d}#W�Ľ�����", x300332_g_BonusMoney1),4,2)
	end

	--������Ǯ2
	if x300332_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300332_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("�������#{_MONEY%d}�Ľ�����", x300332_g_BonusMoney2),4,2)
	end

	--������Ǯ1
	if x300332_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300332_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("��ý�#{_MONEY%d}�Ľ�����", x300332_g_BonusMoney3),4,2)
	end

	--��������
	if x300332_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300332_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("��ý�������%d�Ľ�����", x300332_g_BonusMoney4),4,2)
	end

	--��͢����
	if x300332_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300332_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("��ó�͢����%d�Ľ�����", x300332_g_BonusMoney5),4,2)
	end

	--��͢����
	if x300332_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300332_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("�������ֵ%d�Ľ�����", x300332_g_BonusMoney6),4,2)
	end

 	--�����̶���Ʒ
		for i, item in x300332_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--������ѡ��Ʒ
	for i, item in x300332_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
			end

			--��ȡ��أ��뷵�أ���ֹ�ظ����
			return
		end
    end
end

---------------------------------------------------------------------------------------------------
--�ύ���񣬲��������Ƿ���ɻ���������ʾ���������Ϣ�������������Ϣ
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)
	--�ж��Ƿ�������
	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId);
	if bHaveMission > 0 then
		local today = GetDayOfYear()
        -- ��鵱����ɴ���
		if x300332_GetDate( sceneId, selfId) == today then
            if x300332_GetTimes( sceneId, selfId) >= x300332_g_MaxTimes then
                return
            end
        end
        
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300332_g_MissionId)
		local completed = GetQuestParam(sceneId, selfId, misIndex, x300332_MP_ISCOMPLETE)

		if completed == 1 then
            BeginAddItem( sceneId)
            if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                AddItem( sceneId, selectRadioId, 5)
            else
                AddBindItem( sceneId, selectRadioId, 5)
            end
            local ret = EndAddItem( sceneId, selfId)
            if ret > 0 then
                DelQuest( sceneId, selfId, x300332_g_MissionId)

                local today = GetDayOfYear()
                if x300332_GetDate( sceneId, selfId) == today then
                    -- ���µ�����ɴ���
                    x300332_SetTimes( sceneId, selfId, x300332_GetTimes( sceneId, selfId) + 1)
                else
                    -- ������������
                    x300332_SetDate( sceneId, selfId, today)
                    -- ���������ɴ���
                    x300332_SetTimes( sceneId, selfId, 1)
                end
                -- ������������
                --x300332_SetDate( sceneId, selfId, GetDayOfYear() )

                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, x300332_g_strFinishMission)
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
                Msg2Player( sceneId, selfId, x300332_g_strFinishMission, 8, 2)

		    	x300332_GetBonus( sceneId, selfId, NPCId, selectRadioId)
				
			--	x300332_UpdateTopList(sceneId,selfId)

                AddItemListToPlayer( sceneId, selfId)
                local str = format( "������@item_%d", selectRadioId)
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, str)
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
            else
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "�����������޷��õ���Ʒ��" )
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
            end
            -- д��־
            GamePlayScriptLog( sceneId, selfId, 732)
		else
			BeginQuestEvent( sceneId )
				AddQuestText( sceneId,"����û����ɣ�")
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId);
		end
	else
		BeginQuestEvent( sceneId )
			AddQuestText( sceneId,"���񲻴��ڣ���ȡ������Ϣʧ�ܣ�")
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);
		return
	end
end

---------------------------------------------------------------------------------------------------
--�����Ұ�������
---------------------------------------------------------------------------------------------------
function x300332_CheckPlayerBagFull( sceneId ,selfId)
	local result = 1

	local j = 0

	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������

	--��ͨ�Ľ������
	BeginAddItem(sceneId)
	for j, item in x300332_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end

    --������ѡ��Ʒ
	for j, item in x300332_g_BonusChoiceItem do
		AddItem( sceneId, item.item, item.n )
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if(ret > 0) then
		result = 1;
	else
		result = 0;
	end

	return result
end

-- �����������ʾ������Ϣ
function x300332_ShowMissionInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)
        -- ��������
		AddQuestText( sceneId, "#Y"..x300332_g_MissionName)
		AddQuestText( sceneId, x300332_g_MissionBook)
		AddQuestText( sceneId, " " )

		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
        local Pos1 = 0
        local mon1   = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET1)
        local m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)

        for i, item in x300332_g_MonsterTable do
            if item.monsterId == mon1 then
                Pos1 = item.posId
                break
            end
        end
        AddQuestText( sceneId, format( x300332_g_MissionTarget, Pos1, m1Kill) )
		AddQuestText( sceneId, " " )

		--��ʾ��Ϣ
		if x300332_g_MissionTips ~= "" then
			AddQuestText( sceneId, "#Y������ʾ��" )
			AddQuestText( sceneId, x300332_g_MissionTips)
			AddQuestText( sceneId, " ")
		end
	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300332_DispatchMissionInfo( sceneId, selfId, NPCId)
	local level = GetLevel( sceneId, selfId)
	
	BeginQuestEvent( sceneId)
		--������Ϣ
		AddQuestText( sceneId, "#Y"..x300332_g_MissionName)
		AddQuestText( sceneId, x300332_g_MissionDescription)
		AddQuestText( sceneId, "#r #r #r#Y��������:#W" )
               
		--��������Ϣ 

		--1������
		--if x300332_g_ExpBonus> 0 then
		--local level= GetLevel( sceneId, selfId)
		--local exp =( 1000 * 0.01 * level * 50)
		--if exp > 0 then
			--AddQuestExpBonus( sceneId, exp )
		--end
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 1].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 2].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 3].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 4].itemid, 5)

		--2����Ǯ1
		if x300332_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1( sceneId, x300332_g_BonusMoney1 )
		end

		--3����Ǯ2
		if x300332_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2( sceneId, x300332_g_BonusMoney2 )
		end
		--4����Ǯ3
		if x300332_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3( sceneId, x300332_g_BonusMoney3 )
		end

		--��������
		if x300332_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4( sceneId, x300332_g_BonusMoney4 )
		end

		--��͢����
		if x300332_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5( sceneId, x300332_g_BonusMoney5 )
		end

		--����ֵ
		if x300332_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6( sceneId, x300332_g_BonusMoney6 )
		end

		--5���̶���Ʒ
		for i, item in x300332_g_BonusItem do
		   	AddQuestItemBonus( sceneId, item.item, item.n)
	    end

		--6����ѡ��Ʒ
		for i, item in x300332_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus( sceneId, item.item, item.n)
	    end
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300332_g_ScriptId, x300332_g_MissionId)
	CallScriptFunction( 203794, "FinishDaobaoke", sceneId, selfId)	
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300332_DispatchContinueInfo( sceneId, selfId, NPCId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
    local Pos1 = 0
    local mon1   = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET1)
    local m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)

    for i, item in x300332_g_MonsterTable do
        if item.monsterId == mon1 then
            Pos1 = item.posId
            break
        end
    end

	BeginQuestEvent( sceneId)
		--���������Ϣ
		AddQuestText( sceneId, "#Y"..x300332_g_MissionName)
		AddQuestText( sceneId, format( x300332_g_ContinueInfo, Pos1) )
		AddQuestText( sceneId, " ")

		--����Ŀ��
		AddQuestText( sceneId,"#Y��������")

        AddQuestText( sceneId, format( x300332_g_MissionTarget, Pos1, m1Kill) )

  		--��������Ϣ

		--1������
		-- local level= GetLevel(sceneId,selfId)
		-- local exp =( 1000 * 0.01 * level * 50)
		-- if exp > 0 then
			-- AddQuestExpBonus( sceneId, exp)
		-- end

		--2����Ǯ1
		if x300332_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x300332_g_BonusMoney1 )
		end

		--3����Ǯ2
		if x300332_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300332_g_BonusMoney2 )
		end
		--4����Ǯ3
		if x300332_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300332_g_BonusMoney3 )
		end

		--��������
		if x300332_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300332_g_BonusMoney4 )
		end

		--��͢����
		if x300332_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300332_g_BonusMoney5 )
		end

		--����ֵ
		if x300332_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300332_g_BonusMoney6 )
		end


		--5���̶���Ʒ
		for i, item in x300332_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6����ѡ��Ʒ
		for i, item in x300332_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end

	    --������ʾ��Ϣ
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300332_g_ScriptId, x300332_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300332_DispatchCompletedInfo( sceneId, selfId, NPCId )
	BeginQuestEvent(sceneId)
		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x300332_g_MissionName)
		AddQuestText(sceneId,x300332_g_MissionCompleted)
		AddQuestText(sceneId," ")

  		--��������Ϣ

		--1������
		-- if x300332_g_ExpBonus > 0 then
			-- AddQuestExpBonus(sceneId, x300332_g_ExpBonus)
		-- end
		--local level= GetLevel(sceneId,selfId)
		--local exp =( 1000 * 0.01 * level * 50)
		--if exp > 0 then
			--AddQuestExpBonus(sceneId, exp )
		--end

		--2����Ǯ1
		if x300332_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x300332_g_BonusMoney1 )
		end

		--3����Ǯ2
		if x300332_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x300332_g_BonusMoney2 )
		end
		--4����Ǯ3
		if x300332_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x300332_g_BonusMoney3 )
		end

		--��������
		if x300332_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x300332_g_BonusMoney4 )
		end

		--��͢����
		if x300332_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x300332_g_BonusMoney5 )
		end

		--����ֵ
		if x300332_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x300332_g_BonusMoney6 )
		end


		--5���̶���Ʒ
		for i, item in x300332_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	    end

		--6����ѡ��Ʒ
		for i, item in x300332_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	    end
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 1].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 2].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 3].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 4].itemid, 5)
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300332_g_ScriptId, x300332_g_MissionId);
end

---------------------------------------------------------------------------------------------------
--���ﱻɱ����Ϣ����
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
    if IsPlayerStateNormal( sceneId, selfId) ~= 1 then
        return
    end

    local misIndex = 0
    local teamSize = GetNearTeamCount( sceneId, selfId)
    -- print( "��������������"..teamSize)

    if teamSize <= 1 then -- ����ӣ�����������
        if IsHaveQuest( sceneId, selfId, x300332_g_MissionId) <= 0 then
            return
        end
        misIndex = GetQuestIndexByID( sceneId, selfId, x300332_g_MissionId)
        if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
            -- ������������
            return
        end
        local mon1   = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET1)
        local m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)

        if objdataId == mon1 and m1Kill < x300332_g_KillTargetCount then
            SetQuestByIndex( sceneId, selfId, misIndex, x300332_MP_TARGET4, m1Kill + 1)
        else
            -- ���ɱ���Ĳ�������Ŀ���
            return
        end

        x300332_QuestLogRefresh( sceneId, selfId, x300332_g_MissionId)

        -- throw item by some probability
        local randnum = random( 1, 100)
        local itemid = 0
        if randnum >= 1 and randnum < 26 then
            itemid = x300332_ItemID_Table[ 1].itemid
        elseif randnum >= 26 and randnum < 51 then
            itemid = x300332_ItemID_Table[ 2].itemid
        elseif randnum >= 51 and randnum < 76 then
            itemid = x300332_ItemID_Table[ 3].itemid
        elseif randnum >= 76 and randnum < 101 then
            itemid = x300332_ItemID_Table[ 4].itemid
        else
            itemid = 0
        end

        if( itemid > 0) then
            BeginAddItem(sceneId)
            if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                AddItem( sceneId, itemid, 1)
            else
                AddBindItem( sceneId, itemid, 1)
            end
            local ret = EndAddItem(sceneId,selfId)
            if ret > 0 then
                AddItemListToPlayer(sceneId,selfId)
                local str = format( "������@item_%d", itemid)
                BeginQuestEvent( sceneId)
                AddQuestText( sceneId, str)
                EndQuestEvent( sceneId)
                DispatchQuestTips( sceneId, selfId)
            else
                BeginQuestEvent(sceneId)
                AddQuestText(sceneId,"��Ʒ���������޷��õ���Ʒ��")
                EndQuestEvent(sceneId)
                DispatchQuestTips(sceneId,selfId)
            end
        end

    	--��������Ƿ����
        m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)
    	if m1Kill >= x300332_g_KillTargetCount then
    		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    	end
    else
        for i = 0, teamSize - 1 do
            local memberId = GetNearTeamMember( sceneId, selfId, i)
            if memberId >= 0 and IsPlayerStateNormal( sceneId, memberId) == 1 then
                if IsHaveQuest( sceneId, memberId, x300332_g_MissionId) > 0 then -- ����ó�Ա��������������
                    misIndex = GetQuestIndexByID( sceneId, memberId, x300332_g_MissionId)
                    if GetQuestParam( sceneId, memberId, misIndex, 0) == 0 or GetQuestParam( sceneId, memberId, misIndex, 7) == 0 then -- ����ó�Ա����������û��ɲŰ�70%�ĸ��ʵ�����Ʒ
                        local mon1   = GetQuestParam( sceneId, memberId, misIndex, x300332_MP_TARGET1)
                        local m1Kill = GetQuestParam( sceneId, memberId, misIndex, x300332_MP_TARGET4)

                        local missionMonster = 1
                        if objdataId == mon1 and m1Kill < x300332_g_KillTargetCount then
                            SetQuestByIndex( sceneId, memberId, misIndex, x300332_MP_TARGET4, m1Kill + 1)
                        else
                            missionMonster = 0
                        end

                        if missionMonster == 1 then
                            x300332_QuestLogRefresh( sceneId, memberId, x300332_g_MissionId)

                            -- throw item by some probability
                            local randnum = random( 1, 100)
                            local itemid = 0
                            if randnum >= 1 and randnum < 26 then
                                itemid = x300332_ItemID_Table[ 1].itemid
                            elseif randnum >= 26 and randnum < 51 then
                                itemid = x300332_ItemID_Table[ 2].itemid
                            elseif randnum >= 51 and randnum < 76 then
                                itemid = x300332_ItemID_Table[ 3].itemid
                            elseif randnum >= 76 and randnum < 101 then
                                itemid = x300332_ItemID_Table[ 4].itemid
                            else
                                itemid = 0
                            end

                            if( itemid > 0) then
                                BeginAddItem( sceneId)
                                if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
                                    AddItem( sceneId, itemid, 1)
                                else
                                    AddBindItem( sceneId, itemid, 1)
                                end
                                local ret = EndAddItem( sceneId, memberId)
                                if ret > 0 then
                                    AddItemListToPlayer( sceneId, memberId)
                                    local str = format( "������@item_%d", itemid)
                                    BeginQuestEvent( sceneId)
                                    AddQuestText( sceneId, str)
                                    EndQuestEvent( sceneId)
                                    DispatchQuestTips( sceneId, memberId)
                                else
                                    BeginQuestEvent( sceneId)
                                    AddQuestText( sceneId, "��Ʒ���������޷��õ���Ʒ��" )
                                    EndQuestEvent( sceneId)
                                    DispatchQuestTips( sceneId, memberId)
                                end
                            end

                            --��������Ƿ����
                            m1Kill = GetQuestParam( sceneId, memberId, misIndex, x300332_MP_TARGET4)
                            if m1Kill >= x300332_g_KillTargetCount then
                                SetQuestByIndex( sceneId, memberId, misIndex, 0, 1)
                                SetQuestByIndex( sceneId, memberId, misIndex, 7, 1)
                            end
                        end
                    end
                end
            end
        end
    end
end

---------------------------------------------------------------------------------------------------
--��Ʒ�ı�
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

---------------------------------------------------------------------------------------------------
--����NPC�¼�
---------------------------------------------------------------------------------------------------
function x300332_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	if npcGuid == x300332_SubmitNPCGUID then
		local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300332_g_MissionId);
		if(bHaveMission > 0) then
			local state = GetQuestStateNM(sceneId,selfId,npcId,x300332_g_MissionId)
			AddQuestNumText(sceneId, x300332_g_MissionId, x300332_g_MissionName,state,32);
		end
	end
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300332_QuestLogRefresh( sceneId, selfId, MissionId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local times = x300332_GetTimes( sceneId, selfId)+1
    local Pos1 = 0
    local mon1   = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET1)
    local m1Kill = GetQuestParam( sceneId, selfId, misIndex, x300332_MP_TARGET4)
    
    for i, item in x300332_g_MonsterTable do
        if item.monsterId == mon1 then
            Pos1 = item.posId
            break
        end
    end

	BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                "�����ˡ������ͣ�"..times.."/10��",             -- ��������
                                format( x300332_g_MissionTarget, Pos1, m1Kill),
                                "",                             --����NPC
                                x300332_g_MissionBook,
                                x300332_g_MissionDescription,
                                x300332_g_MissionTips
                                )

        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 1].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 2].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 3].itemid, 5)
        AddQuestRadioItemBonus( sceneId, x300332_ItemID_Table[ 4].itemid, 5)
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

function x300332_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    x300332_QuestLogRefresh( sceneId, selfId, MissionId)
end

---------------------------------------------------------------------------------------------------
--ǿ�м�����
---------------------------------------------------------------------------------------------------
function x300332_OnForceAddMission( sceneId, selfId, npcId, MissionId)
end

-- ��÷�������ʱ��
function x300332_GetTimes( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DAOBAOKE_TIMES[ 1], MD_DAOBAOKE_TIMES[ 2], MD_DAOBAOKE_TIMES[ 3] )
end

-- ���÷�������ʱ��
function x300332_SetTimes( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DAOBAOKE_TIMES[ 1], MD_DAOBAOKE_TIMES[ 2], MD_DAOBAOKE_TIMES[ 3], value)
end

-- ��ý�����������
function x300332_GetDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_DAOBAOKE_DATE[ 1], MD_DAOBAOKE_DATE[ 2], MD_DAOBAOKE_DATE[ 3] )
end

-- ���ý�����������
function x300332_SetDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_DAOBAOKE_DATE[ 1], MD_DAOBAOKE_DATE[ 2], MD_DAOBAOKE_DATE[ 3], value)
end