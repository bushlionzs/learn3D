--MisDescBegin

x300565_g_ScriptId 					= 300565                  --�ű�ID
x300565_g_MissionId 				= 9302                    --����ID

x300565_g_MissionKind 				= 2                       --��������
x300565_g_LevelLess					= 40                      --�������ŵȼ�  <=0 ��ʾ������

x300565_g_MissionName				= "�����ˡ�����±���"                                        --��������(512)
x300565_g_MissionTarget				= "  �ҵ�@npc_%d"      --����Ŀ��
x300565_g_MissionInfo				= "\t���Ǵ�����������ټ�����������ʿ���ٿ����ִ�ᣬ��ѡ��һ�������������\n\t��λʩ�������书����������Ҳ��μ������ִ�ᣬ����ȥ����������@npc_%d��"            --������Ϣ
x300565_g_MissionInfo1	            = "\t�����ӷ�\n\tʩ��Ҳ�����μ������ִ��ģ��ҹ�ʩ��Ŀ�о��⣬��Ȼ���ڹ���տ֮�ˣ������ȥ��@npc_%d�д�һ����"
x300565_g_ContinueInfo				= "\tʩ��Ϊ�λ��ڴ��ǻ���Ī���������ӣ�"  --���������Ϣ
x300565_g_MissionCompleted			= "\t����������й�Ȼ��Ӣ�ű��������벻����ô��ʩ���͵�ʤ��������ϲʩ���ˡ�\n\t���ִ��ٰ�֮�գ�����ʩ����Ҫ���ٱ��¡�"  --���������Ϣ
x300565_g_MissionHelp				= ""          --������ʾ��Ϣ
-- ���������ʾ��Ϣ
x300565_g_strMissionAbandon         = "�����������񣺡����ˡ�����±���"

--Ŀ��
x300565_g_ExtTarget					= { {type=20,n=1,target=""} }


--����
x300565_g_ExpBonus					= 0             --���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x300565_g_BonusItem					= {}	--��������Ʒ

x300565_g_BonusMoney1               = 0  --������������
x300565_g_BonusMoney2               = 0  --�������ǰ�����
x300565_g_BonusMoney3               = 0  --�������󶨽��
x300565_g_BonusMoney4               = 0  --��������͢����
x300565_g_BonusMoney5               = 0  --��������������
x300565_g_BonusMoney6               = 0  --����������

x300565_g_BonusChoiceItem           = {}


--MisDescEnd

-- ��������ű�MapServer������loadscriptonce��������

--����Ŀ��˳��
x300565_MP_FINDMASTER               = 1 -- �ҵ���ʦ���
x300565_MP_TARGETINDEX              = 2 -- �����ٻ����ָ��ֵ�NPC��x300565_g_TargetNPCList������
x300565_MP_ISCOMPLETE				= 7	-- ������� 0δ��ɣ� 1���

x300565_g_strMissionFull            = "�����������������ʧ��"
x300565_g_strMissionAccept          = "�����������񣺡����ˡ�����±���"
x300565_g_strMissionBook            = "\t@npc_139300���ڴ�������ڵȴ���·����Ӣ�����������ǿ��ǰ���ɡ�"
x300565_g_strMonsterHasCreated      = "\t������λ�����Ѿ�����ս��#G���������һ������д�#W�����ģ��Ҳ������������ж�Ϊʤ��"
x300565_g_strMonsterCreated         = "\t���ϴ�ʦ�������ģ�\n\t�õģ��Ҿͺ����д�һ�������ص��ģ���ֻ��ʹ�����ɹ�����"
x300565_g_strMissionFinished        = "����������񣺡����ˡ�����±���"
x300565_g_strMissionRefrain         = "�ܱ�Ǹ��������Ѿ����������񣬲����ٴ���ȡ��"
x300565_g_strMissionTarget2         = "\tսʤ#G%s#W(%d/1)"
x300565_g_strMissionInfo2           = "\t��@npc_%d�д�����"
x300565_g_strMissionInfo3           = "\tսʤ#S%s"
x300565_g_strMissionBook1           = "\t�ظ�@npc_139300"
-- ���������¼��־ID
x300565_g_AcceptMissionLogID        = 931
-- ��������¼��־ID
x300565_g_FinishMissionLogID        = 932
-- ������ʦguid
x300565_g_TargetNPC                 = 139300
-- ������NPC
x300565_g_MissionNPC                = 139116
-- ������NPC
x300565_g_MissionReply              = "@npc_139300"
-- ɱ����Ч��Χ��������ʿ������ʱ������������е������������������Ͷ������
x300565_g_Range                     = 20
-- ���齱��ϵ��
--x300565_g_CoffExp                   = 2000
-- ��������ϵ��
x300565_g_CoffCredit                = 0
-- ����NPC�б�
x300565_g_TargetNPCList             = {
                                        { id = 139323, monsterId = 0, constId = 1056, bornTime = -1, name = "�����" }, 
                                        { id = 139326, monsterId = 0, constId = 1052, bornTime = -1, name = "����ʦ̫"}, 
                                        { id = 139320, monsterId = 0, constId = 1050, bornTime = -1, name = "������" }, 
                                        { id = 139331, monsterId = 0, constId = 1051, bornTime = -1, name = "����²" }, 
                                        { id = 139338, monsterId = 0, constId = 1054, bornTime = -1, name = "������" }, 
                                        { id = 139341, monsterId = 0, constId = 1053, bornTime = -1, name = "���ž���" }, 
                                        { id = 139346, monsterId = 0, constId = 1055, bornTime = -1, name = "����־" }, 
}
-- �淨����id
x300565_g_IsEnableId                = 1004
-- ��������Ʒ�б�
x300565_g_RewardTable               = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}

---------------------------------------------------------------------------------------------------
--�о��¼�
---------------------------------------------------------------------------------------------------
function x300565_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)

    if GetLevel( sceneId, selfId) < x300565_g_LevelLess then
        return 0
    end

    -- print( "*-*-*-*-*-*" )
    local npcGuid = GetMonsterGUID( sceneId, NPCId)
    if npcGuid == x300565_g_TargetNPC then
        return 0
    end
    if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then
        return 0
    end
    AddQuestNumText( sceneId, x300565_g_MissionId, x300565_g_MissionName, GetQuestStateNM( sceneId, selfId, NPCId, x300565_g_MissionId), 1)
end

---------------------------------------------------------------------------------------------------
--������ں���
---------------------------------------------------------------------------------------------------
function x300565_ProcEventEntry( sceneId, selfId, NPCId, MissionId, nExtIdx)

    if GetGameOpenById( x300565_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) == 0 then
        x300565_ShowTips(sceneId, selfId, "�˻���첻���ţ������뵽�󶼰�������ѯÿ��������")
        return
    end
    
	if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then  -- ����Ѿ��ӹ��������
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
        local npcGuid = GetMonsterGUID( sceneId, NPCId)
        local index = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX)
        if npcGuid == x300565_g_MissionNPC then
            local bDone = x300565_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x300565_DispatchCompletedInfo( sceneId, selfId, NPCId) --���������ʾ
            else
                x300565_DispatchContinueInfo( sceneId, selfId, NPCId) --δ���������ʾ
            end
        elseif npcGuid == x300565_g_TargetNPC then
            local bDone = x300565_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x300565_DispatchCompletedInfo( sceneId, selfId, NPCId) --���������ʾ
            else
                if GetQuestParam( sceneId, selfId, misIndex, x300565_MP_FINDMASTER) == 0 then
	                -- ���ѡ��һ��NPC
	                local index1 = random( 1, getn( x300565_g_TargetNPCList) )
	                local npcId = x300565_g_TargetNPCList[ index1].id
	                SetQuestByIndex( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX, index1)
	                BeginQuestEvent( sceneId)
	                    AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
	                    AddQuestText( sceneId, format( x300565_g_MissionInfo1, npcId) )
	                    AddQuestText( sceneId, " ")
	                    AddQuestText( sceneId, "#Y����Ŀ�꣺")
	                    AddQuestText( sceneId, format( x300565_g_MissionTarget, npcId) )
	                    AddQuestText( sceneId, " ")
	                EndQuestEvent( sceneId)
	                DispatchQuestEventList( sceneId, selfId, NPCId)
	                SetQuestByIndex( sceneId, selfId, misIndex, x300565_MP_FINDMASTER, 1)
	                x300565_ProcQuestLogRefresh( sceneId, selfId, MissionId)
                else
                	x300565_DispatchContinueInfo( sceneId, selfId, NPCId) --δ���������ʾ
                end
            end
        elseif index ~= 0 then
            if npcGuid ~= x300565_g_TargetNPCList[ index].id then
                return
            end
            if x300565_g_TargetNPCList[ index].monsterId == 0 then
                BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, x300565_g_strMonsterCreated)
                EndQuestEvent( sceneId)
                DispatchQuestEventList( sceneId, selfId, NPCId)

                local x, z = GetWorldPos( sceneId, NPCId)
                -- �������ָ���
                x300565_g_TargetNPCList[ index].monsterId = CreateMonster( sceneId, x300565_g_TargetNPCList[ index].constId, x + random( -2, 2), z + random( -2, 2), 1, 0, x300565_g_ScriptId, -1, 21, 1200000)
                if x300565_g_TargetNPCList[ index].monsterId >= 0 then
                    x300565_g_TargetNPCList[ index].bornTime = GetMinOfDay()
                end
            else
                -- �����Ѿ���������
                local liveTime = 0
                if GetMinOfDay() < x300565_g_TargetNPCList[ index].bornTime then
                    liveTime = GetMinOfDay() + 1440 - x300565_g_TargetNPCList[ index].bornTime
                else
                    liveTime = GetMinOfDay() - x300565_g_TargetNPCList[ index].bornTime
                end
                if liveTime >= 20 then
                    -- ������˱�����20�����˻�û���������Զ���ʧ����Ҫ�ٴδ���
                    BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, x300565_g_strMonsterCreated)
                    EndQuestEvent( sceneId)
                    DispatchQuestEventList( sceneId, selfId, NPCId)

                    local x, z = GetWorldPos( sceneId, NPCId)
                    -- �������ָ���
                    x300565_g_TargetNPCList[ index].monsterId = CreateMonster( sceneId, x300565_g_TargetNPCList[ index].constId, x + random( -2, 2), z + random( -2, 2), 1, 0, x300565_g_ScriptId, -1, 21, 1200000)
                    if x300565_g_TargetNPCList[ index].monsterId >= 0 then
                        x300565_g_TargetNPCList[ index].bornTime = GetMinOfDay()
                    end
                else
                    BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, x300565_g_strMonsterHasCreated)
                    EndQuestEvent( sceneId)
                    DispatchQuestEventList( sceneId, selfId, NPCId)
                end
            end
            SetQuestByIndex( sceneId, selfId, misIndex, x300565_MP_FINDMASTER, 2)
            x300565_ProcQuestLogRefresh( sceneId, selfId, MissionId)
        end
	else
		x300565_DispatchMissionInfo( sceneId, selfId, NPCId)	--������Ϣ��ʾ
	end
end

---------------------------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------------------------
function x300565_ProcAcceptCheck( sceneId, selfId, npcId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId)
	if( bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestAccept( sceneId, selfId, targetId, missionId)

    local name = GetName( sceneId, selfId)
    if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then
    else
        local npcGuid = GetMonsterGUID( sceneId, targetId)
        if npcGuid ~= x300565_g_MissionNPC then
            return 0
        end
        local today = GetDayOfYear()
        if x300565_GetMissionDate( sceneId, selfId) == today then
            Msg2Player( sceneId, selfId, x300565_g_strMissionRefrain, 8, 3)
            return 0
        end
        
        --���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x300565_g_MissionId  )
		if FrontMissiontId1 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId2 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
				return 0
			end
		end
		if FrontMissiontId3 ~= -1 then
			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
				return 0
			end
		end
        
        if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == GetDayOfYear() then
            if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
                Msg2Player( sceneId, selfId, "�㲻������ȡ������ճ�������", 8, 3)
                return 0
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
        end

        local ret = AddQuest( sceneId, selfId, x300565_g_MissionId, x300565_g_ScriptId, 0, 0, 0, 1)
        if ret == 0 then
            LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionFull, name, 3, 1)
            return 0
        else
            -- ��ʾ���������Ϣ
            LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionAccept, name, 3, 1)
            LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionAccept, name, 2, 1)
        end

        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
            AddQuestText( sceneId, x300565_g_strMissionBook)
        EndQuestEvent( sceneId)
        DispatchQuestEventList( sceneId, selfId, targetId)

        local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 1, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 2, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)

        -- д��־
        GamePlayScriptLog( sceneId, selfId, x300565_g_AcceptMissionLogID)
    end
end

---------------------------------------------------------------------------------------------------
function x300565_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end
--��������
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300565_g_MissionId)
	if bHaveMission > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
		DelQuest( sceneId, selfId, x300565_g_MissionId)
		
        --x300565_SetMissionDate( sceneId, selfId, GetDayOfYear() )
        local today = GetDayOfYear()
        SetQuestData( sceneId, selfId, MD_WULINDAHUI_DATE[ 1], MD_WULINDAHUI_DATE[ 2], MD_WULINDAHUI_DATE[ 3], today)
		if today == GetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3] ) then
            local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
            if count < 3 then
                SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1 + count)
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3], today)
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1)
        end

		Msg2Player( sceneId, selfId, x300565_g_strMissionAbandon, 8, 3)
		Msg2Player( sceneId, selfId, x300565_g_strMissionAbandon, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x300565_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end

---------------------------------------------------------------------------------------------------
--��ý���
---------------------------------------------------------------------------------------------------
function x300565_GetBonus( sceneId, selfId,NpcID, SelectId)
	--������Ǯ1
	if x300565_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300565_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("�������#{_MONEY%d}�Ľ�����", x300565_g_BonusMoney1),4,2)
	end

	--������Ǯ2
	if x300565_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300565_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("�������#{_MONEY%d}�Ľ�����", x300565_g_BonusMoney2),4,2)
	end

	--������Ǯ1
	if x300565_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300565_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("��ý�#{_MONEY%d}�Ľ�����", x300565_g_BonusMoney3),4,2)
	end

	--��������
	if x300565_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300565_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("��ý�������%d�Ľ�����", x300565_g_BonusMoney4),4,2)
	end

	--��͢����
	if x300565_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300565_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("��ó�͢����%d�Ľ�����", x300565_g_BonusMoney5),4,2)
	end

	--��͢����
	if x300565_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300565_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("�������ֵ%d�Ľ�����", x300565_g_BonusMoney6),4,2)
	end

 	--�����̶���Ʒ
	for i, item in x300565_g_BonusItem do
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
	for i, item in x300565_g_BonusChoiceItem do
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
function x300565_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)
    if GetGameOpenById( x300565_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) == 0 then
        return
    end

	if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) <= 0 then
        return 0
    end
    
    local today = GetDayOfYear()
    local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
    if today == GetQuestData(sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2],MD_RICHANG_DAY[3] ) and count >= 3 then
        Msg2Player( sceneId, selfId, "������ճ������Ѿ������ٽ��ˣ�����������", 8, 3)
        return 0
    end

    -- ������ѡ��Ľ����ǲ��ǿ��ж��ǰ󶨵�
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300565_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
            break
        end
    end

    -- ����������������ѡ����Ʒ��������Խ���¸�������ʱ�Ĵ���
    if count == 0 then
        for i, item in x300565_g_RewardTable do
            for j, iter in item.items do
                if selectRadioId == iter.id then
                    if j <= 2 then
                        canBind = 1
                    end
                    count = iter.cnt
                    id = iter.id
                    break
                end
            end
        end
    end

    if id == 0 or count == 0 then
        return 0
    end

	BeginAddItem(sceneId)
    if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
        if canBind == 1 then
            AddItem( sceneId, id, count)
        else
            AddBindItem( sceneId, id, count)
        end
    else
		AddBindItem( sceneId, id, count)
    end
		
	local ret = EndAddItem(sceneId,selfId)
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)

        Msg2Player( sceneId, selfId, format( "���������Ʒ��@itemid_%d",id), 8, 3)
	else
        Msg2Player( sceneId, selfId, "�����ռ䲻�㣬�޷������������Ʒ��������ʧ��", 8, 3)
        return 0
	end
    CallScriptFunction( 256225, "Finishbiwu", sceneId, selfId)
    CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300565_g_MissionId)
    DelQuest( sceneId, selfId, x300565_g_MissionId)
    local name = GetName( sceneId, selfId)
    LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionFinished, name, 3, 1)
    LuaScenceM2Player( sceneId, selfId, x300565_g_strMissionFinished.."��", name, 2, 1)
    x300565_SetMissionDate( sceneId, selfId, GetDayOfYear() )
    GamePlayScriptLog( sceneId, selfId, x300565_g_FinishMissionLogID)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300565_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)

    --������Ϣ
    AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
    AddQuestText( sceneId, format( x300565_g_MissionInfo, x300565_g_TargetNPC) )
    AddQuestText( sceneId, " ")

    --����Ŀ��
    AddQuestText( sceneId, "#Y����Ŀ�꣺")
    AddQuestText( sceneId, format( x300565_g_MissionTarget, x300565_g_TargetNPC) )
    AddQuestText( sceneId, " ")

    --��ʾ��Ϣ
    if x300565_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#Y������ʾ��")
        AddQuestText( sceneId, x300565_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

    --��������Ϣ
	local level = GetLevel(sceneId, selfId)
    for i, item in x300565_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end

	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300565_g_ScriptId, x300565_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300565_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
    AddQuestText( sceneId, x300565_g_ContinueInfo)
    AddQuestText( sceneId, " ")
    local playerLevel = GetLevel( sceneId, selfId)
    -- if x300565_g_CoffExp > 0 then
        -- AddQuestExpBonus( sceneId, playerLevel * x300565_g_CoffExp)
    -- end
    -- if x300565_g_CoffCredit > 0 then
        -- AddQuestMoneyBonus5( sceneId, x300565_g_CoffCredit)
    -- end
    -- AddQuestItemBonus( sceneId, 11050002, 5)
    -- AddQuestText( sceneId, " " )
    -- AddQuestText( sceneId, "#Y�������ݣ�" )
    --AddQuestText( sceneId, format( "����ֵ��%d��", playerLevel * x300565_g_CoffExp) )
    --AddQuestText( sceneId, format( "������%d��", x300565_g_CoffCredit) )
	EndQuestEvent( sceneId)
	DispatchQuestEventList( sceneId, selfId, NPCId)
	--DispatchQuestInfoNM( sceneId, selfId, NPCId, x300565_g_ScriptId, x300565_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300565_DispatchCompletedInfo( sceneId, selfId, NPCId)
    if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300565_g_MissionName)
        AddQuestText( sceneId, x300565_g_MissionCompleted)
        AddQuestText( sceneId, " ")
        local level = GetLevel(sceneId, selfId)
        for i, item in x300565_g_RewardTable do
            if level >= item.minLevel and level < item.maxLevel then
                for j, iter in item.items do
                    AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
                end
                break
            end
        end
        EndQuestEvent()
        DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300565_g_ScriptId, x300565_g_MissionId)
    else
        BeginQuestEvent( sceneId)
            AddQuestText( "�������޴�����" )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    end
end

---------------------------------------------------------------------------------------------------
--���ﱻɱ����Ϣ����
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

function x300565_OnDie( sceneId, selfId, killerId)
    -- ���ұ�ɱ�����ǲ������ָ���
    local index = 0
    for i, item in x300565_g_TargetNPCList do
        if selfId == item.monsterId then
            index = i
        end
    end
    if index == 0 then
        return
    else
        x300565_g_TargetNPCList[ index].monsterId = 0
    end

    if GetGameOpenById( x300565_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) == 0 then
        return
    end

    -- ��ù��ﱻɱ��ʱ��λ��
    local x, z = GetWorldPos( sceneId, selfId)
    -- ��õ�ǰ������������
    local humanCount = GetScenePlayerCount( sceneId)
    for i = 0, humanCount - 1 do
        local humanId = GetScenePlayerObjId( sceneId, i)
        if humanId >= 0 and IsPlayerStateNormal( sceneId, humanId) == 1 and IsHaveQuestNM( sceneId, humanId, x300565_g_MissionId) > 0 then
            -- 
            local playerx, playerz = GetWorldPos( sceneId, humanId)
            if abs( x - playerx) <= x300565_g_Range and abs( z - playerz) <= x300565_g_Range and GetHp( sceneId, humanId) > 0 then
                local misIndex = GetQuestIndexByID( sceneId, humanId, x300565_g_MissionId)
                if GetQuestParam( sceneId, humanId, misIndex, x300565_MP_TARGETINDEX) == index and GetQuestParam( sceneId, humanId, misIndex, 0) == 0 then
                    SetQuestByIndex( sceneId, humanId, misIndex, 7, 1)
                    SetQuestByIndex( sceneId, humanId, misIndex, 0, 1)
                    Msg2Player( sceneId, humanId, "��������ɣ���ȥ��������ʦ�������", 8, 3)
                    x300565_ProcQuestLogRefresh( sceneId, humanId, x300565_g_MissionId)
                end
            end
        end
    end
end

---------------------------------------------------------------------------------------------------
--��Ʒ�ı�
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
end

---------------------------------------------------------------------------------------------------
--����NPC�¼�
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestAttach( sceneId, selfId, NPCId, npcGuid, misIndex, MissionId)
    if GetGameOpenById( x300565_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) == 0 then
        return
    end

    if IsHaveQuestNM( sceneId, selfId, x300565_g_MissionId) > 0 then
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
        local index = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX)
        if index ~= 0 and npcGuid == x300565_g_TargetNPCList[ index].id and GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
            AddQuestNumText( sceneId, x300565_g_MissionId, "��Ҫ��ս", 13, 3)
        elseif npcGuid == x300565_g_TargetNPC and GetQuestParam( sceneId, selfId, misIndex, x300565_MP_FINDMASTER) == 0 then
            AddQuestNumText( sceneId, x300565_g_MissionId, "����±���", 13, 2)
        elseif npcGuid == x300565_g_TargetNPC then
            AddQuestNumText( sceneId, x300565_g_MissionId, x300565_g_MissionName, GetQuestStateNM( sceneId, selfId, NPCId, x300565_g_MissionId), 4)
        end
    end
end

function x300565_GetMissionDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_WULINDAHUI_DATE[ 1], MD_WULINDAHUI_DATE[ 2], MD_WULINDAHUI_DATE[ 3] )
end

function x300565_SetMissionDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_WULINDAHUI_DATE[ 1], MD_WULINDAHUI_DATE[ 2], MD_WULINDAHUI_DATE[ 3], value)
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300565_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300565_g_MissionId)
    local strTarget = ""
    local strDetail = ""
    local strGonglue = x300565_g_strMissionBook
    local findNPC = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_FINDMASTER)
	BeginQuestEvent( sceneId)
    if findNPC == 2 then
        local index = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX)
        if x300565_g_TargetNPCList[ index].monsterId == 0 then
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
                strTarget = format( x300565_g_strMissionTarget2, x300565_g_TargetNPCList[ index].name, 1)
                strDetail = x300565_g_strMissionBook1
                strGonglue = x300565_g_strMissionBook1
            else
                -- �ٻ�֮�󵫻�û������ʱ������ͣ��ά����������ʱ��Ҫ�ָ���ǰһ���׶Σ������ٻ���ȱ����ٻ�
                strTarget = format( x300565_g_MissionTarget, x300565_g_TargetNPCList[ index].id)
                SetQuestByIndex( sceneId, selfId, misIndex, x300565_MP_FINDMASTER, 1)
            end
        else
            -- սʤ���ָ���
            strTarget = format( x300565_g_strMissionTarget2, x300565_g_TargetNPCList[ index].name, 0)
            strDetail = format( x300565_g_strMissionInfo3, x300565_g_TargetNPCList[ index].name)
            strGonglue = format( x300565_g_strMissionInfo2, x300565_g_TargetNPCList[ index].id)
        end
    elseif findNPC == 1 then
        -- �ҵ����ָ���
        local index = GetQuestParam( sceneId, selfId, misIndex, x300565_MP_TARGETINDEX)
        strTarget = format( x300565_g_MissionTarget, x300565_g_TargetNPCList[ index].id)
        strDetail = format( x300565_g_MissionInfo1, x300565_g_TargetNPCList[ index].id)
        strGonglue = format( x300565_g_strMissionInfo2, x300565_g_TargetNPCList[ index].id)
    elseif findNPC == 0 then
        -- �ҵ�������ʦ
        strTarget = format( x300565_g_MissionTarget, x300565_g_TargetNPC)
        strDetail = format( x300565_g_MissionInfo, x300565_g_TargetNPC)
    end
    AddQuestLogCustomText( sceneId,
                           x300565_g_MissionName,               -- ����
                           x300565_g_MissionName,               -- ��������
                           strTarget,                           -- ���������ʾ������Ŀ��
                           x300565_g_MissionReply,              -- ����NPC
                           strGonglue,            -- ������
                           strDetail,               -- ��������
                           x300565_g_MissionHelp)               -- ������ʾ
    -- ��ʾ����
	local level = GetLevel(sceneId, selfId)
    for i, item in x300565_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end
