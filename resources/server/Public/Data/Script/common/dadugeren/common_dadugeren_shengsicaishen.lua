--MisDescBegin

x300566_g_ScriptId 					= 300566                  --�ű�ID
x300566_g_MissionId 				= 9310                    --����ID

x300566_g_MissionKind 				= 2                       --��������
x300566_g_LevelLess					= 40                      --�������ŵȼ�  <=0 ��ʾ������

x300566_g_MissionName				= "�����ˡ���������"                                        --��������(512)
x300566_g_MissionTarget				= "  �ҵ�@npc_140006"      --����Ŀ��
x300566_g_MissionInfo				= "\t���գ���������������һ�ֲֹ������ջ��Բ��ѡ���·��ҽ����������������˵���⾿���Ǻ��ֲ�֢��\n\t���գ�������@npc_140006�����ؽ�������ҽ����ţǰ���ΰ����Σ�Ҳ��֪���������Σ����������ļ�����"            --������Ϣ
x300566_g_ContinueInfo				= "\t�ѵ���Ҳ�������⼸ζҩ�������޲ߣ��������Ǻá�"  --���������Ϣ
x300566_g_MissionCompleted			= "\t��ô��������������е�ҩ�����Ҵ���о��ˣ�\n\t#Y@myname#W����ζ������������������ΰ��һ��СС���⣬������Ҫ�ƴǡ�"  --���������Ϣ
x300566_g_MissionHelp				= "#W@npc_140006���ڴ󶼶��Ϸ����ΰ��ܶ��ڡ�����������Ҫ����Ʒ��������ͨ��#G�����#W����������Ҳ������������ҹ���"          --������ʾ��Ϣ
-- ���������ʾ��Ϣ
x300566_g_strMissionAbandon         = "�����������񣺡����ˡ���������"

--Ŀ��
x300566_g_ExtTarget					= { {type=20,n=1,target=""} }


--����
x300566_g_ExpBonus					= 0             --���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x300566_g_BonusItem					= {}	--��������Ʒ

x300566_g_BonusMoney1               = 0  --������������
x300566_g_BonusMoney2               = 0  --�������ǰ�����
x300566_g_BonusMoney3               = 0  --�������󶨽��
x300566_g_BonusMoney4               = 0  --��������͢����
x300566_g_BonusMoney5               = 0  --��������������
x300566_g_BonusMoney6               = 0  --����������

x300566_g_BonusChoiceItem           = {}
x300566_g_GroupPoint	=	{ {type=10,id =188,target = "ľ��"},{type=10,id =189,target = "ˮ��"},{type=10,id =190,target = "����"},{type=10,id =191,target = "ɣ֦"},{type=10,id =192,target = "��ʯ"}}--ר�����ڲɼ�����Ч�ã����������δ�ؾ����������ı�Ҫ���أ���ˣ�ֻҪ��ؾͿ��������������



--MisDescEnd

--����Ŀ��˳��
x300566_MP_GETSUBMISSION            = 1 -- ������������
x300566_MP_ITEM1                    = 2
x300566_MP_ITEM2                    = 3
x300566_MP_ITEM3                    = 4
x300566_MP_ITEM4                    = 5
x300566_MP_ITEMINDEX                = 6
x300566_MP_ISCOMPLETE				= 7	-- ������� 0δ��ɣ� 1���

x300566_g_strMissionFull            = "�����������������ʧ��"
x300566_g_strMissionAccept          = "�����������񣺡����ˡ���������"
x300566_g_strMissionBook            = "\t��˵����ҽ����ţ����ҽ�Σ��Ӳ��໰������꿪��һ���Źֵ�ҩ������ƮȻ��ȥ��\n\t��Ϊ������ǣ�ֻҪ�����˰�ҩ����ҩ���£��޲�ҩ��������"
x300566_g_strSubMissionInfo         = "\t��������ҽ����ţ�Ѿ���������Ϲ�����������δ˵�����õ��Ǻ��ֲ�֢��ֻ�ǿ�����ҩ������ȥ��\n\t��ҩ���й��а�����������£��������ΰ︻�����£��������ֲ�֪�ܴӺδ�������"
x300566_g_strMissionFinished        = "����������񣺡����ˡ���������"
x300566_g_strMissionRefrain         = "������Ѿ�����������������������ɡ�"
x300566_g_strMissionTarget2         = "\t�ռ�@item_%d#W(%d/1)"
-- ���������¼��־ID
x300566_g_AcceptMissionLogID        = 941
-- ��������¼��־ID
x300566_g_FinishMissionLogID        = 942
-- ������guid
x300566_g_TargetNPC                 = 140006
-- ������NPC
x300566_g_MissionNPC                = 139083
-- ����ظ�NPC
x300566_g_MissionReply              = "@npc_140006"
-- �ռ���Ʒ�б�
x300566_g_ItemTable                 = {
                                        { mp = x300566_MP_ITEM1, 
                                            itemlist = { 12020001,12020002,12020003,12020004,12020005,12020006 }, -- ��Ʒid�б�
                                        },       -- �̵깺�����Ʒ
                                        { mp = x300566_MP_ITEM2, 
                                            itemlist = { 14030001,14030006,14030011,12052471,12052481,12052491}, -- ��Ʒid�б�
                                        },       -- �ɼ�����Ʒ
                                        { mp = x300566_MP_ITEM3, 
                                            itemlist = { 12052531,11041030,11041040,11041010,11041000,11041050 }, -- ��Ʒid�б�
                                        },       -- ����ʹ�õõ�����Ʒ
                                        { mp = x300566_MP_ITEM4, 
                                            itemlist =  { 10260040,10250040,10230040,10200040,10280040,10290040 },  -- ��Ʒid�б�
                                        },       -- ɱ�ֵõ�����Ʒ
}
-- ����ʹ������
x300566_g_UsePositionX              = 100
x300566_g_UsePositionZ              = 100
-- ���齱��ϵ��
x300566_g_CoffExp                   = 0
-- ��������ϵ��
x300566_g_CoffMoney                 = 500
-- ������Ʒ1Ŀ��
x300566_g_strMissionItem1Target     = "  �ռ�@item_%d#W(%d/1)\n"
-- ������Ʒ2Ŀ��
x300566_g_strMissionItem2Target     = "  �ռ�@item_%d#W(%d/1)\n"
-- ������Ʒ3Ŀ��
x300566_g_strMissionItem3Target     = "  �ռ�@item_%d#W(%d/1)\n"
-- ������Ʒ4Ŀ��
x300566_g_strMissionItem4Target     = "  �ռ�@item_%d#W(%d/1)"
-- �����Ʒʱ����ʾ
x300566_g_strGetItem                = "������@item_%d#cffcf00"
-- ������2
x300566_g_strGongLue2               = "�ҵ�����ҩ��"
-- ��������2
x300566_g_strMissionDescription2    = "������Ȼ𣬿�����Ҫ�Ͻ�ȥ��@npc_140006�ҵ������ֺ�����ҩ���ˡ�"
-- ������3
x300566_g_strGongLue3               = "��ҩ����@npc_140006��"
-- ��������3
x300566_g_strMissionDescription3    = "����������ҩ�������ǿ�ȥ����@npc_140006�ɡ�"
-- �淨����id
x300566_g_IsEnableId                = 1005
-- ��������Ʒ�б�
x300566_g_RewardTable       = {
                                { minLevel = 40, maxLevel = 60,  items = { { id = 11000201, cnt = 8 }, { id = 11050002, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 60, maxLevel = 80,  items = { { id = 11000202, cnt = 8 }, { id = 11050003, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
                                { minLevel = 80, maxLevel = 999, items = { { id = 11000203, cnt = 8 }, { id = 11050004, cnt = 8 }, { id = 12030120, cnt = 1 }, { id = 12030130, cnt = 1 }, { id = 12030140, cnt = 1 } } }, 
}

---------------------------------------------------------------------------------------------------
--�о��¼�
---------------------------------------------------------------------------------------------------
function x300566_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)

    if GetLevel( sceneId, selfId) < x300566_g_LevelLess then
        return 0
    end
    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then
        return 0
    end

    AddQuestNumText( sceneId, x300566_g_MissionId, x300566_g_MissionName, GetQuestStateNM( sceneId, selfId, NPCId, x300566_g_MissionId), 1)
end

---------------------------------------------------------------------------------------------------
--������ں���
---------------------------------------------------------------------------------------------------
function x300566_ProcEventEntry( sceneId, selfId, NPCId, MissionId, nExtIdx)

    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        x300566_ShowTips(sceneId, selfId, "�˻���첻���ţ������뵽�󶼰�������ѯÿ��������")
        return
    end

	if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then  -- ����Ѿ��ӹ��������
        local npcGuid = GetMonsterGUID( sceneId, NPCId)
        if npcGuid == x300566_g_MissionNPC then
            local bDone = x300566_CheckSubmit( sceneId, selfId, NPCId)
            if bDone > 0 then
                x300566_DispatchCompletedInfo( sceneId, selfId, NPCId) --���������ʾ
            else
                x300566_DispatchContinueInfo( sceneId, selfId, NPCId) --δ���������ʾ
            end
        elseif npcGuid == x300566_g_TargetNPC then
            local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_GETSUBMISSION) == 1 then
                    x300566_DispatchContinueInfo( sceneId, selfId, NPCId) --δ���������ʾ
                else
                    BeginQuestEvent( sceneId)
                        AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
                        AddQuestText( sceneId, x300566_g_strSubMissionInfo)
                    EndQuestEvent( sceneId)
                    DispatchQuestEventList( sceneId, selfId, NPCId)

                    -- ���ѡȡ������Ʒ
                    local index = random( 1, getn( x300566_g_ItemTable[ 1].itemlist) )
                    SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX, index)
                    SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_GETSUBMISSION, 1)
                    -- ��鱳�����Ƿ��Ѿ���Ҫ�ռ�����Ʒ������о�ֱ��������ر��
                    for i, item in x300566_g_ItemTable do
                        if HaveItemInBag( sceneId, selfId, item.itemlist[ index] ) > 0 then
                            SetQuestByIndex( sceneId, selfId, misIndex, item.mp, 1)
                        end
                    end
                    x300566_ProcQuestLogRefresh( sceneId, selfId, MissionId)
                end
            else
                x300566_DispatchCompletedInfo( sceneId, selfId, NPCId) --���������ʾ
            end
        end
	else
		x300566_DispatchMissionInfo( sceneId, selfId, NPCId)	--������Ϣ��ʾ
	end
	 
end

---------------------------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------------------------
function x300566_ProcAcceptCheck( sceneId, selfId, npcId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId)
	if( bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestAccept( sceneId, selfId, targetId, missionId)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        return 0
    end

    local name = GetName( sceneId, selfId)
    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then
    else
        local today = GetDayOfYear()
        if x300566_GetMissionDate( sceneId, selfId) == today then
            Msg2Player( sceneId, selfId, x300566_g_strMissionRefrain, 8, 3)
            return 0
        end
        if GetQuestData( sceneId, selfId, MD_RICHANG_DAY[ 1], MD_RICHANG_DAY[ 2], MD_RICHANG_DAY[ 3] ) == today then
            if GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[ 1], MD_RICHANG_COUNT[ 2], MD_RICHANG_COUNT[ 3] ) >= 3 then
                Msg2Player( sceneId, selfId, "�㲻������ȡ������ճ�������", 8, 3)
                return 0
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 0)
        end
        --���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x300566_g_MissionId  )
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
		
        local ret = AddQuest( sceneId, selfId, x300566_g_MissionId, x300566_g_ScriptId, 0, 0, 1, 1)
        if ret == 0 then
            LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionFull, name, 3, 1)
            return 0
        else
            -- ��ʾ���������Ϣ
            LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionAccept, name, 3, 1)
            LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionAccept, name, 2, 1)
        end

        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
            AddQuestText( sceneId, x300566_g_strMissionBook)
        EndQuestEvent( sceneId)
        DispatchQuestEventList( sceneId, selfId, targetId)

        local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)

        -- д��־
        GamePlayScriptLog( sceneId, selfId, x300566_g_AcceptMissionLogID)
    end
end

---------------------------------------------------------------------------------------------------
function x300566_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end
--��������
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId)
	if bHaveMission > 0 then
        -- local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
        -- local index = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX)
        -- if index ~= 0 then
            -- -- ɾ�����������Ҫ����Ʒ�����˴��̵깺��ķǰ���Ʒ
            -- DelItem( sceneId, selfId, x300566_g_ItemTable[ 2].itemlist[ index], 1)
            -- DelItem( sceneId, selfId, x300566_g_ItemTable[ 3].itemlist[ index], 1)
            -- DelItem( sceneId, selfId, x300566_g_ItemTable[ 4].itemlist[ index], 1)
        -- end
		DelQuest( sceneId, selfId, x300566_g_MissionId)
        --x300566_SetMissionDate( sceneId, selfId, GetDayOfYear() )
        local today = GetDayOfYear()
        SetQuestData( sceneId, selfId, MD_SHENGSICAISHEN_DATE[ 1], MD_SHENGSICAISHEN_DATE[ 2], MD_SHENGSICAISHEN_DATE[ 3], today)
		if today == GetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3] ) then
            local count = GetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3] )
            if count < 3 then
                SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1 + count)
            end
        else
            SetQuestData( sceneId, selfId, MD_RICHANG_DAY[1], MD_RICHANG_DAY[2], MD_RICHANG_DAY[3], today)
            SetQuestData( sceneId, selfId, MD_RICHANG_COUNT[1], MD_RICHANG_COUNT[2], MD_RICHANG_COUNT[3], 1)
        end

		Msg2Player( sceneId, selfId, x300566_g_strMissionAbandon, 8, 3)
		Msg2Player( sceneId, selfId, x300566_g_strMissionAbandon, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x300566_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end

---------------------------------------------------------------------------------------------------
--��ý���
---------------------------------------------------------------------------------------------------
function x300566_GetBonus( sceneId, selfId,NpcID, SelectId)
	--������Ǯ1
	if x300566_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300566_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("�������#{_MONEY%d}�Ľ�����", x300566_g_BonusMoney1),4,2)
	end

	--������Ǯ2
	if x300566_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300566_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("�������#{_MONEY%d}�Ľ�����", x300566_g_BonusMoney2),4,2)
	end

	--������Ǯ1
	if x300566_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300566_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("��ý�#{_MONEY%d}�Ľ�����", x300566_g_BonusMoney3),4,2)
	end

	--��������
	if x300566_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300566_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("��ý�������%d�Ľ�����", x300566_g_BonusMoney4),4,2)
	end

	--��͢����
	if x300566_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300566_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("��ó�͢����%d�Ľ�����", x300566_g_BonusMoney5),4,2)
	end

	--��͢����
	if x300566_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300566_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("�������ֵ%d�Ľ�����", x300566_g_BonusMoney6),4,2)
	end

 	--�����̶���Ʒ
	for i, item in x300566_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		local ret = EndAddItem(sceneId,selfId)
		if ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"������������������������")
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--������ѡ��Ʒ
	for i, item in x300566_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			local ret = EndAddItem(sceneId,selfId)
			if ret > 0 then
				AddItemListToPlayer(sceneId,selfId)
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"������������������������")
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
function x300566_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 then
        return
    end
    
    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) < 0 then
    	return
    end
 
    
    -- check first
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
    local name = GetName( sceneId, selfId)
    local index = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX)
    for i, item in x300566_g_ItemTable do
        if GetItemCountInBag( sceneId, selfId, item.itemlist[ index] ) < 1 then
            LuaScenceM2Player( sceneId, selfId, format( "û��@item_%d#cffcf00���ܽ�����", item.itemlist[ index] ), name, 3, 1)
            return
        end
    end

    if CallScriptFunction( 270300, "OnSubmissionFinished", sceneId, selfId, x300566_g_MissionId) == 0 then
        Msg2Player( sceneId, selfId, "������ճ������Ѿ������ٽ��ˣ�����������", 8, 3)
        return 0
    end

    -- remove from bag of player
    for i, item in x300566_g_ItemTable do
        DelItem( sceneId, selfId, item.itemlist[ index], 1)
    end
    DelQuest( sceneId, selfId, x300566_g_MissionId)
    CallScriptFunction( 256225, "Finishcaishen", sceneId, selfId)	
    LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionFinished, name, 3, 1)
    LuaScenceM2Player( sceneId, selfId, x300566_g_strMissionFinished.."��", name, 2, 1)
    x300566_SetMissionDate( sceneId, selfId, GetDayOfYear() )
    -- ������ѡ��Ľ����ǲ��ǿ��ж��ǰ󶨵�
	local level = GetLevel( sceneId, selfId)
    local canBind = 0
    local count = 0
    local id = 0
    for i, item in x300566_g_RewardTable do
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
        for i, item in x300566_g_RewardTable do
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
		
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("���������Ʒ��@itemid_%d",id))
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�����ռ䲻�㣬�޷������������Ʒ��������ʧ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
    GamePlayScriptLog( sceneId, selfId, x300566_g_FinishMissionLogID)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300566_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)

    --������Ϣ
    AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
    AddQuestText( sceneId, x300566_g_MissionInfo)
    AddQuestText( sceneId, " ")
           
    --����Ŀ��
    AddQuestText( sceneId, "#Y����Ŀ�꣺")
    AddQuestText( sceneId, x300566_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --��ʾ��Ϣ
    if x300566_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#Y������ʾ��")
        AddQuestText( sceneId, x300566_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

    --��������Ϣ
    local level = GetLevel( sceneId, selfId)
    for i, item in x300566_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end


	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300566_g_ScriptId, x300566_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300566_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
    AddQuestText( sceneId, x300566_g_ContinueInfo)
    AddQuestText( sceneId, " ")
    -- local exp = GetLevel( sceneId, selfId) * x300340_g_ExperienceCoefficient
    -- if exp > 0 then
        -- AddQuestExpBonus( sceneId, exp)
    -- end
    -- -- 090302 ��������
    -- local playerLevel = GetLevel( sceneId, selfId)
    -- if playerLevel > 80 then
        -- playerLevel = 80
    -- end
    -- local money = playerLevel * x300340_g_MoneyCoefficient
    -- AddQuestMoneyBonus1( sceneId, money)
	EndQuestEvent( sceneId)
    DispatchQuestEventList( sceneId, selfId, NPCId)
	--DispatchQuestInfoNM( sceneId, selfId, NPCId, x300566_g_ScriptId, x300566_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300566_DispatchCompletedInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300566_g_MissionName)
    AddQuestText( sceneId, x300566_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    local level = GetLevel( sceneId, selfId)
    for i, item in x300566_g_RewardTable do
        if level >= item.minLevel and level < item.maxLevel then
            for j, iter in item.items do
                AddQuestRadioItemBonus( sceneId, iter.id, iter.cnt)
            end
            break
        end
    end
	EndQuestEvent( sceneId)
    DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300566_g_ScriptId, x300566_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--���ﱻɱ����Ϣ����
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------------------------
--��Ʒ�ı�
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        return 0
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
    local index = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX)
    if itemdataId == x300566_g_ItemTable[ 1].itemlist[ index] then
        if HaveItemInBag( sceneId, selfId, itemdataId) > 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM1, 1)
            Msg2Player( sceneId, selfId, format( x300566_g_strGetItem, itemdataId), 8, 3)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM1, 0)
        end
        x300566_ProcQuestLogRefresh( sceneId, selfId, x300566_g_MissionId)
    elseif itemdataId == x300566_g_ItemTable[ 2].itemlist[ index] then
        if HaveItemInBag( sceneId, selfId, itemdataId) > 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM2, 1)
            Msg2Player( sceneId, selfId, format( x300566_g_strGetItem, itemdataId), 8, 3)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM2, 0)
        end
        x300566_ProcQuestLogRefresh( sceneId, selfId, x300566_g_MissionId)
    elseif itemdataId == x300566_g_ItemTable[ 3].itemlist[ index] then
        if HaveItemInBag( sceneId, selfId, itemdataId) > 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM3, 1)
            Msg2Player( sceneId, selfId, format( x300566_g_strGetItem, itemdataId), 8, 3)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM3, 0)
        end
        x300566_ProcQuestLogRefresh( sceneId, selfId, x300566_g_MissionId)
    elseif itemdataId == x300566_g_ItemTable[ 4].itemlist[ index] then
        if HaveItemInBag( sceneId, selfId, itemdataId) > 0 then
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM4, 1)
            Msg2Player( sceneId, selfId, format( x300566_g_strGetItem, itemdataId), 8, 3)
        else
            SetQuestByIndex( sceneId, selfId, misIndex, x300566_MP_ITEM4, 0)
        end
        x300566_ProcQuestLogRefresh( sceneId, selfId, x300566_g_MissionId)
    else
        return
    end

    if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM1) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM2) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM3) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM4) == 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        Msg2Player( sceneId, selfId, "ҩ���Ѿ����룬��ȥ���������İɡ�", 8, 3)
    else
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
    end
end

---------------------------------------------------------------------------------------------------
--����NPC�¼�
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
        if npcGuid == x300566_g_TargetNPC then
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 and GetQuestParam( sceneId, selfId, misIndex, x300566_MP_GETSUBMISSION) == 0 then
                AddQuestNumText( sceneId, x300566_g_MissionId, "�����Ĳ���ô���ˣ�", 13)
            else
                AddQuestNumText( sceneId, x300566_g_MissionId, x300566_g_MissionName, 7)
            end
        end
    end
end

function x300566_GetMissionDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_SHENGSICAISHEN_DATE[ 1], MD_SHENGSICAISHEN_DATE[ 2], MD_SHENGSICAISHEN_DATE[ 3] )
end

function x300566_SetMissionDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_SHENGSICAISHEN_DATE[ 1], MD_SHENGSICAISHEN_DATE[ 2], MD_SHENGSICAISHEN_DATE[ 3], value)
end

function x300566_OnUseItem( sceneId, selfId)
end

function x300566_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID)
    if GetGameOpenById( x300566_g_IsEnableId) <= 0 and IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) == 0 then
        return 0
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
    if IsHaveQuestNM( sceneId, selfId, x300566_g_MissionId) > 0 then
        if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM2) == 1 then
            Msg2Player( sceneId, selfId, "���Ѿ��ɼ���ҩ����", 8, 3)
            return 1
        else
            return 0
        end
    else
        return 1
    end
end

function x300566_OnRecycle( sceneId, selfId, targetId, gpType, needItemID)
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300566_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300566_g_MissionId)
    local index = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEMINDEX)
    if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM1) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM2) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM3) == 1 and
        GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM4) == 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
    end
	BeginQuestEvent( sceneId)
    if GetQuestParam( sceneId, selfId, misIndex, x300566_MP_GETSUBMISSION) == 1 then
        local strMissionTarget = ""
        local item1 = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM1)
        local item2 = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM2)
        local item3 = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM3)
        local item4 = GetQuestParam( sceneId, selfId, misIndex, x300566_MP_ITEM4)

        -- "����@npc_%d#W(%d/1)\n"
        if item1 == 1 then
            strMissionTarget = "#G"..format( x300566_g_strMissionItem1Target, x300566_g_ItemTable[ 1].itemlist[ index], item1)
        else
            strMissionTarget = "#W"..format( x300566_g_strMissionItem1Target, x300566_g_ItemTable[ 1].itemlist[ index], item1)
        end

        -- "�ɼ�@npc_%d#W(%d/1)\n"
        if item2 == 1 then
            strMissionTarget = strMissionTarget.."#G"..format( x300566_g_strMissionItem2Target, x300566_g_ItemTable[ 2].itemlist[ index], item2)
        else
            strMissionTarget = strMissionTarget.."#W"..format( x300566_g_strMissionItem2Target, x300566_g_ItemTable[ 2].itemlist[ index], item2)
        end

        -- "��@npc_%dʹ��@item_%d#W(%d/1)\n"
        if item3 == 1 then
            strMissionTarget = strMissionTarget.."#G"..format( x300566_g_strMissionItem3Target, x300566_g_ItemTable[ 3].itemlist[ index], item3)
        else
            strMissionTarget = strMissionTarget.."#W"..format( x300566_g_strMissionItem3Target, x300566_g_ItemTable[ 3].itemlist[ index], item3)
        end

        -- "ɱ��@npc_%d���@item_%d#W(%d/1)"
        if item4 == 1 then
            strMissionTarget = strMissionTarget.."#G"..format( x300566_g_strMissionItem4Target, x300566_g_ItemTable[ 4].itemlist[ index], item4)
        else
            strMissionTarget = strMissionTarget.."#W"..format( x300566_g_strMissionItem4Target, x300566_g_ItemTable[ 4].itemlist[ index], item4)
        end

        if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
            AddQuestLogCustomText( sceneId,
                                   x300566_g_MissionName,               -- ����
                                   x300566_g_MissionName,               -- ��������
                                   strMissionTarget,                    -- ����Ŀ��
                                   x300566_g_MissionReply,              -- ����NPC
                                   x300566_g_strGongLue3,               -- ������
                                   x300566_g_strMissionDescription3,    -- ��������
                                   x300566_g_MissionHelp)               -- ������ʾ
        else
            AddQuestLogCustomText( sceneId,
                                   x300566_g_MissionName,               -- ����
                                   x300566_g_MissionName,               -- ��������
                                   strMissionTarget,                    -- ����Ŀ��
                                   x300566_g_MissionReply,              -- ����NPC
                                   x300566_g_strGongLue2,               -- ������
                                   x300566_g_strMissionDescription2,    -- ��������
                                   x300566_g_MissionHelp)               -- ������ʾ
        end
    else
        AddQuestLogCustomText( sceneId,
                               x300566_g_MissionName,               -- ����
                               x300566_g_MissionName,               -- ��������
                               x300566_g_MissionTarget,             -- ����Ŀ��
                               x300566_g_MissionReply,              -- ����NPC
                               x300566_g_strMissionBook,            -- ������
                               x300566_g_MissionInfo,               -- ��������
                               x300566_g_MissionHelp)               -- ������ʾ
    end
    local level = GetLevel( sceneId, selfId)
    for i, item in x300566_g_RewardTable do
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
