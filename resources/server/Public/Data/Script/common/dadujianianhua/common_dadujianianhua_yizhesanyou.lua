--MisDescBegin

x300569_g_ScriptId 					= 300569                  --�ű�ID
x300569_g_MissionId 				= 9320                    --����ID

x300569_g_MissionKind 				= 2                       --��������
x300569_g_LevelLess					= 40                      --�������ŵȼ�  <=0 ��ʾ������

x300569_g_MissionName				= "���¡���������"                                        --��������(512)
x300569_g_MissionTarget				= "\t����ȫ�����һظ��������Ĺ�Ʒ"      --����Ŀ��
x300569_g_MissionInfo				= "\t#Y@myname#W��СŮ��ȫ���������������ˡ�\n\t�����ҵķ��һʱ���죬���Ҹ�����׼�����׸������ұ��µĹ�Ʒ����ʧ�ڴ���������Щ��Ʒ�����Ҹ������������֮������Ǿʹ˶�ʧ�������ҷ������ɱ��֮����\n\t���Ŵ�Ԫ������Ǹ����ʵ�֮�ˣ���֪��ɷ��æ���ǹ�Ʒ�һأ�"            --������Ϣ
x300569_g_ContinueInfo				= "\t��Ʒ......���������Ǻá�"  --���������Ϣ
x300569_g_MissionCompleted			= "\t��......���Ƕ�ʧ�Ĺ�Ʒ��\n\t��Ԫ�����Ȼ�������壬�ѹֿ�ʥ���ƣ����Ӱ��ƣ�ȡ֮�е����ҽ��շ���������ʶ��\n\t#Y@myname#W����������һ�ݡ�"  --���������Ϣ
x300569_g_MissionHelp				= "#G\t�ڱ������У�������ڲɼ��������ҵ��߼��ĸ�����Ʒ������õľ��齱��Ҳ�����ӡ�"          --������ʾ��Ϣ
-- ���������ʾ��Ϣ
x300569_g_strMissionAbandon         = "�����������񣺡��¡���������"

--Ŀ��
x300569_g_ExtTarget					= { {type=20,n=1,target=""} }
x300569_g_TianfuItems				= {11010100,11010101,11010102}

--����
x300569_g_ExpBonus					= 0     --���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x300569_g_BonusItem					= {}	--��������Ʒ

x300569_g_BonusMoney1               = 0  --������������
x300569_g_BonusMoney2               = 0  --�������ǰ�����
x300569_g_BonusMoney3               = 0  --�������󶨽��
x300569_g_BonusMoney4               = 0  --��������͢����
x300569_g_BonusMoney5               = 0  --��������������
x300569_g_BonusMoney6               = 0  --����������

x300569_g_BonusChoiceItem           = {}

--MisDescEnd

x300569_g_MaxCount					= 1

--����Ŀ��˳��

x300569_g_strMissionFull            = "�����������������ʧ��"
x300569_g_strMissionAccept          = "�����������񣺡��¡���������"
x300569_g_strMissionBook            ="��ȫ����˵����������#G����·#W��#G���������ϲ�#Wͣ����һ��ʱ�䡣"
x300569_g_strSubMissionInfo         = "\t�һض�ʧ�Ĺ�Ʒ��"
x300569_g_strMissionFinished        = "����������񣺡��¡���������"
x300569_g_strMissionRefrain         = "������Ѿ��������������"
x300569_g_strMissionTarget1         = "\t�ҵ���ʧ�Ĺ�Ʒ#G#{_ITEM13810084} #{_ITEM13810089} #{_ITEM13810092} #{_ITEM13810101} #{_ITEM13810104}#W�����佻��@npc_139130"
x300569_g_strMissionTarget2         = "%s  ��@npc_72050�ҵ�#{_ITEM13810084}(%d/1)\n%s  ��@npc_72051�ҵ�#{_ITEM13810089}(%d/1)\n%s  ��@npc_72052�ҵ�#{_ITEM13810092}(%d/1)\n%s  ��@npc_72053�ҵ�#{_ITEM13810101}(%d/1)\n%s  ��@npc_72054�ҵ�#{_ITEM13810104}(%d/1)"
x300569_g_strMissionTitle           = "���¡���������"
-- ���������¼��־ID
x300569_g_AcceptMissionLogID        = 951
-- ��������¼��־ID
x300569_g_FinishMissionLogID        = 952
-- ������NPC
x300569_g_TargetNPC                 = 139130
-- ������NPC
x300569_g_MissionNPC                = 139129
-- ����ظ�NPC
x300569_g_MissionReply              = "@npc_139130"
-- ������Ʒ�б�
x300569_g_MissionItemTable          = {
                                        { itemId = 13810084, PosId = 72050, gpId = 323, strName = "������" }, -- ��������Ʒ�Ͳɼ���ID �ɼ��ص㣺������
																				{ itemId = 13810089, PosId = 72051, gpId = 325, strName = "��Ƥ��" }, -- ��������Ʒ�Ͳɼ���ID �ɼ��ص㣺������
                                        { itemId = 13810092, PosId = 72052, gpId = 326, strName = "������" }, -- ��������Ʒ�Ͳɼ���ID �ɼ��ص㣺������
                                        { itemId = 13810101, PosId = 72053, gpId = 329, strName = "������" }, -- ��������Ʒ�Ͳɼ���ID �ɼ��ص㣺������
                                        { itemId = 13810104, PosId = 72054, gpId = 330, strName = "����ľ" }, -- ��������Ʒ�Ͳɼ���ID �ɼ��ص㣺������
}
-- ���齱��ϵ��
x300569_g_CoffExp                   = 7000
-- ��������ϵ��
x300569_g_CoffMoney                 = 0
-- ÿ��������ɽ�������ֵ
x300569_g_Credit                    = 150
-- ����������ɫ�����Ӷ������˻�Ҫ����������ʱ����ʾ��Ϣ
x300569_g_strRefuse                 = "\t��л���ˣ������ʧ�ĸ�����Ʒ�Ѿ����һ��ˡ��������׼��ǰȥ���������ұ��¡�"
-- �淨����id
x300569_g_IsEnableId                = 1006
-- �淨����ʱ��(��0����ĵ�x����)
x300569_g_OpenTime                  = 1170
-- �淨�ر�ʱ��(��0����ĵ�x����)
x300569_g_EndTime                   = 1440
-- ��������ʱ�������ʱ����ʾ��Ϣ
x300569_g_strNotMissionTime         = "ֻ����ÿ�յ�#G19��30--24��00#cffcf00�ڲſ���ȡ����"

-- ���⽱����ƷID
x300569_g_AdditionItem              = 12030107

---------------------------------------------------------------------------------------------------
--�о��¼�
---------------------------------------------------------------------------------------------------
function x300569_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    if GetLevel( sceneId, selfId) < x300569_g_LevelLess then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
        return 0
    end

    AddQuestNumText( sceneId, x300569_g_MissionId, x300569_g_MissionName, GetQuestStateNM( sceneId, selfId, NPCId, x300569_g_MissionId), 1)
end

---------------------------------------------------------------------------------------------------
--������ں���
---------------------------------------------------------------------------------------------------
function x300569_ProcEventEntry( sceneId, selfId, NPCId, MissionId, nExtIdx)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

	if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then  -- ����Ѿ��ӹ��������
        local npcGuid = GetMonsterGUID( sceneId, NPCId)
        if npcGuid == x300569_g_TargetNPC then
            local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                x300569_DispatchContinueInfo( sceneId, selfId, NPCId) --δ���������ʾ
            else
                x300569_DispatchCompletedInfo( sceneId, selfId, NPCId) --���������ʾ
            end
        end
	else
		x300569_DispatchMissionInfo( sceneId, selfId, NPCId)	--������Ϣ��ʾ
	end
end

---------------------------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------------------------
function x300569_ProcAcceptCheck( sceneId, selfId, npcId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId)
	if( bHaveMission > 0) then
		return 0;
	else
		return 1;
	end
end

function x300569_AddTianfuItem( sceneId, selfId)
	local level = GetLevel( sceneId, selfId)
	if level >= 80 then
		if random( 1, 100) <= 22 then
			local nIndex = random(1,3)
			BeginAddItem( sceneId)
	        AddItem( sceneId, x300569_g_TianfuItems[nIndex], 1)
	        if EndAddItem( sceneId, selfId) <= 0 then
	            Msg2Player( sceneId, selfId, "������ı����������޷�����츳���߽�����", 8, 2)
	        else
	            AddItemListToPlayer( sceneId, selfId)
	        end
		end
	end
end
---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestAccept( sceneId, selfId, targetId, missionId)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    local name = GetName( sceneId, selfId)
    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
       -- �����������������ʱ��������Ķ��⽱��
        local rewardExt = 0
        local itemExt = 0
        if IsHaveQuestNM( sceneId, selfId, 1482) > 0 then
            if random( 1, 100) <= 70 then
                rewardExt = 1
                BeginAddItem( sceneId)
                itemExt = 13015012
                AddItem( sceneId, itemExt, 1)
                if EndAddItem( sceneId, selfId) <= 0 then
                    Msg2Player( sceneId, selfId, "�޷��õ�������⽱����Ʒ����������", 8, 3)
                    return
                end
            end
        end
        -- ������Ʒ�������ý���ϵ��
        for i, item in x300569_g_MissionItemTable do
			if DelItem( sceneId, selfId, item.itemId, 1) == 0 then
				Msg2Player( sceneId, selfId, "�ύ��Ʒʧ�ܡ�", 8, 2)
				Msg2Player( sceneId, selfId, "�ύ��Ʒʧ��", 8, 3)
				return 0
			end 
		end

        -- ��������������������ڲ�һ��ʱ����������ӱ��
        local today = GetDayOfYear()
        if today ~= x300569_GetMissionDate( sceneId, selfId) then
            x300569_SetMissionDate( sceneId, selfId, today)
            x300569_SetDayCount( sceneId, selfId, 1)
        end


        DelQuest( sceneId, selfId, x300569_g_MissionId)
        
        
        LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionFinished, name, 3, 1)
        LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionFinished.."��", name, 2, 1)
        CallScriptFunction( 256224, "Finishyizhe", sceneId, selfId)	
        x300569_SetMissionDate( sceneId, selfId, GetDayOfYear() )
        local playerLevel = GetLevel( sceneId, selfId)
        local xp = playerLevel * x300569_g_CoffExp
        if xp > 0 then
			AddExp( sceneId, selfId, xp)
			Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", xp).."��", 8, 2)
			Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", xp), 8, 3)
        end
        
        local money = playerLevel * x300569_g_CoffMoney
        if money > 0 then
            AddMoney( sceneId, selfId, money, 0)
            Msg2Player( sceneId, selfId, format( "���#R����#{_MONEY%d}#cffcf00�Ľ���", money).."��", 8, 2)
            Msg2Player( sceneId, selfId, format( "���#R����#{_MONEY%d}#cffcf00�Ľ���", money), 8, 3)
        end
        SetShengWang( sceneId, selfId, GetShengWang( sceneId, selfId) + x300569_g_Credit)
        Msg2Player( sceneId, selfId, format( "���#R%d������#cffcf00�Ľ���", x300569_g_Credit).."��", 8, 2)
        Msg2Player( sceneId, selfId, format( "���#R%d������#cffcf00�Ľ���", x300569_g_Credit), 8, 3)
        -- ����Daycount                           
        x300569_SetDayCount( sceneId, selfId, x300569_GetDayCount( sceneId, selfId) + 1)
        if rewardExt == 1 then
            AddItemListToPlayer( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( "���@item_%d#cffcf00�Ķ��⽱��", itemExt).."��", 8, 2)
            Msg2Player( sceneId, selfId, format( "���@item_%d#cffcf00�Ķ��⽱��", itemExt), 8, 3)
        end
        
        x300569_AddTianfuItem( sceneId, selfId)
        
        local value = random( 1, 100)
        local buff 	=	9011
				local buff1 =	9013
				local buff2 =	9012
        if value > 20 and value <= 40 then
            BeginAddItem( sceneId)
            if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
            	AddItem( sceneId, x300569_g_AdditionItem, 1)
            else
           		AddBindItem( sceneId, x300569_g_AdditionItem, 1)
           	end
            if EndAddItem( sceneId, selfId) <= 0 then
                Msg2Player( sceneId, selfId, "������ˡ��¡��������ѡ�������ı����������޷���òر�ͼ������", 8, 2)
            else
            	AddItemListToPlayer( sceneId, selfId)
                -- LuaAllScenceM2Wrold( sceneId, "#G���#Y"..GetName( sceneId, selfId).."#G����ɡ��¡���������ʱ����Ļ����һ��#R�ر�ͼ#G��", 1, 1)
            end
        end
        
        -- ���һö�󶼼��껪���ֱ�
        BeginAddItem( sceneId)
        AddItem( sceneId, 11990117, 5)
        if EndAddItem( sceneId, selfId) <= 0 then
            Msg2Player( sceneId, selfId, "������ˡ��¡��������ѡ�������ı����������޷����#{_ITEM11990117}������", 8, 2)
        else
            AddItemListToPlayer( sceneId, selfId)
        end
        GamePlayScriptLog( sceneId, selfId, x300569_g_FinishMissionLogID)
    else
        -- ʱ����
        local nowTime = GetMinOfDay()
        if nowTime < x300569_g_OpenTime or nowTime >= x300569_g_EndTime then
            Msg2Player( sceneId, selfId, x300569_g_strNotMissionTime.."��", 8, 2)
            Msg2Player( sceneId, selfId, x300569_g_strNotMissionTime, 8, 3)
            return
        end

        local npcGuid = GetMonsterGUID( sceneId, targetId)
        if npcGuid == x300569_g_TargetNPC then
            return
        end

        local today = GetDayOfYear()
        if x300569_GetMissionDate( sceneId, selfId) == today then
            if x300569_GetDayCount( sceneId, selfId) > x300569_g_MaxCount then
                -- ��ʾ����5����ɫ�����Ӷ�������
                BeginQuestEvent( sceneId)
                    AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
                    AddQuestText( sceneId, x300569_g_strRefuse)
                EndQuestEvent()
                DispatchQuestEventList( sceneId, selfId, targetId)
                Msg2Player( sceneId, selfId, format("�������Ѿ�����������񣬲����ٽ���"), 8, 3)
                return 0
            end
        else
            x300569_SetMissionDate( sceneId, selfId, today)
            x300569_SetDayCount( sceneId, selfId, 1)
        end

        --���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, x300569_g_MissionId)
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

        if AddQuest( sceneId, selfId, x300569_g_MissionId, x300569_g_ScriptId, 0, 0, 1, 1) == 0 then
            LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionFull, name, 3, 1)
            return 0
        else
            -- ��ʾ���������Ϣ
            LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionAccept, name, 3, 1)
            LuaScenceM2Player( sceneId, selfId, x300569_g_strMissionAccept, name, 2, 1)
        end

        local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
		
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
            AddQuestText( sceneId, x300569_g_strMissionTarget1 )
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, targetId)

        SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
        
        SetQuestByIndex( sceneId, selfId, misIndex, 1, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[1].itemId ) > 0 and 1 or 0))
        SetQuestByIndex( sceneId, selfId, misIndex, 2, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[2].itemId ) > 0 and 1 or 0))
        SetQuestByIndex( sceneId, selfId, misIndex, 3, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[3].itemId ) > 0 and 1 or 0))
        SetQuestByIndex( sceneId, selfId, misIndex, 4, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[4].itemId ) > 0 and 1 or 0))
        SetQuestByIndex( sceneId, selfId, misIndex, 5, (HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[5].itemId ) > 0 and 1 or 0))

        -- ����������ٺ�Q���
        x300569_ProcQuestLogRefresh( sceneId, selfId, x300569_g_MissionId)

        -- д��־
        GamePlayScriptLog( sceneId, selfId, x300569_g_AcceptMissionLogID)
    end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestAbandon( sceneId, selfId, MissionId)
	local bHaveMission	= IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId)
	if bHaveMission > 0 then
       
        -- ����Ѿ��ɼ�����Ʒ����ɾ��
        for i, item in x300569_g_MissionItemTable do
            if GetItemCountInBag( sceneId, selfId, item.itemId) > 0 and DelItem( sceneId, selfId, item.itemId, 1) == 0 then
                Msg2Player( sceneId, selfId, "ɾ��������Ʒʧ�ܣ��޷���������", 8, 2)
                Msg2Player( sceneId, selfId, "ɾ��������Ʒʧ�ܣ��޷���������", 8, 3)
                return 0
            end
        end

		DelQuest( sceneId, selfId, x300569_g_MissionId)

        local today = GetDayOfYear()
        if today == x300569_GetMissionDate( sceneId, selfId) then
            x300569_SetDayCount( sceneId, selfId, x300569_GetDayCount( sceneId, selfId) + 1)
        else
            x300569_SetMissionDate( sceneId, selfId, today)
            -- ��Ϊ�����Ѿ���һ��
            x300569_SetDayCount( sceneId, selfId, 2)
        end

		Msg2Player( sceneId, selfId, x300569_g_strMissionAbandon, 8, 3)
		Msg2Player( sceneId, selfId, x300569_g_strMissionAbandon, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x300569_CheckSubmit( sceneId, selfId, NPCId)

	local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)

    if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
        return 1
    else
        return 0
    end
end

---------------------------------------------------------------------------------------------------
--��ý���
---------------------------------------------------------------------------------------------------
function x300569_GetBonus( sceneId, selfId,NpcID, SelectId)
	--������Ǯ1
	if x300569_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x300569_g_BonusMoney1 )
	    Msg2Player(sceneId,selfId,format("�������#{_MONEY%d}�Ľ�����", x300569_g_BonusMoney1),4,2)
	end

	--������Ǯ2
	if x300569_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x300569_g_BonusMoney2 )
	    Msg2Player(sceneId,selfId,format("�������#{_MONEY%d}�Ľ�����", x300569_g_BonusMoney2),4,2)
	end

	--������Ǯ1
	if x300569_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x300569_g_BonusMoney3 )
	    Msg2Player(sceneId,selfId,format("��ý�#{_MONEY%d}�Ľ�����", x300569_g_BonusMoney3),4,2)
	end

	--��������
	if x300569_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
		nRongYu = nRongYu + x300569_g_BonusMoney4
		SetRongYu( sceneId, selfId, nRongYu )
		Msg2Player(sceneId,selfId,format("�������%d�Ľ�����", x300569_g_BonusMoney4),4,2)
	end

	--��͢����
	if x300569_g_BonusMoney5 > 0 then
		local nShengWang = GetShengWang( sceneId, selfId )
		nShengWang = nShengWang + x300569_g_BonusMoney5
		SetShengWang( sceneId, selfId, nShengWang )
		Msg2Player(sceneId,selfId,format("�������%d�Ľ�����", x300569_g_BonusMoney5),4,2)
	end

	--��͢����
	if x300569_g_BonusMoney6 > 0 then
		AddHonor(sceneId,selfId,x300569_g_BonusMoney6)
		Msg2Player(sceneId,selfId,format("�������ֵ%d�Ľ�����", x300569_g_BonusMoney6),4,2)
	end

 	--�����̶���Ʒ
	for i, item in x300569_g_BonusItem do
 		BeginAddItem(sceneId)
		AddItem( sceneId, item.item, item.n )
		if EndAddItem( sceneId, selfId) > 0 then
			AddItemListToPlayer(sceneId,selfId)
		else
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
    end

	--������ѡ��Ʒ
	for i, item in x300569_g_BonusChoiceItem do
	    if item.item == SelectId then
	        BeginAddItem(sceneId)
			AddItem( sceneId, item.item, item.n )
			if EndAddItem( sceneId, selfId) > 0 then
				AddItemListToPlayer( sceneId, selfId)
			else
				BeginQuestEvent( sceneId)
				AddQuestText( sceneId, "��Ʒ���������޷��õ�������Ʒ��" )
				EndQuestEvent()
				DispatchQuestTips( sceneId, selfId)
			end

			--��ȡ��أ��뷵�أ���ֹ�ظ����
			return
		end
    end
end

---------------------------------------------------------------------------------------------------
--�ύ���񣬲��������Ƿ���ɻ���������ʾ���������Ϣ�������������Ϣ
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestSubmit( sceneId, selfId, NPCId, selectRadioId, MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300569_DispatchMissionInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)

    --������Ϣ
    AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
    AddQuestText( sceneId, x300569_g_MissionInfo)
    AddQuestText( sceneId, " ")
           
    --����Ŀ��
    AddQuestText( sceneId, "#Y����Ŀ�꣺")
    AddQuestText( sceneId, x300569_g_MissionTarget)
    AddQuestText( sceneId, " ")

    --��ʾ��Ϣ
    if x300569_g_MissionHelp ~= "" then
        AddQuestText( sceneId, "#YС��ʾ��")
        AddQuestText( sceneId, x300569_g_MissionHelp)
        AddQuestText( sceneId, " ")
    end                 

    local level = GetLevel( sceneId, selfId)
    --��������Ϣ

    --1������
    local playerLevel = GetLevel( sceneId, selfId)
    local exp = level * x300569_g_CoffExp
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end

    --2����Ǯ1������
    if x300569_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1( sceneId, x300569_g_BonusMoney1)
    end

    --3����Ǯ2������
    if x300569_g_CoffMoney > 0 then
        AddQuestMoneyBonus2( sceneId, x300569_g_CoffMoney * level)
    end
    --4����Ǯ3
    if x300569_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3( sceneId, x300569_g_BonusMoney3)
    end

    --��������
    if x300569_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4( sceneId, x300569_g_BonusMoney4)
    end

    --��͢����
    if x300569_g_Credit > 0 then
        AddQuestMoneyBonus5( sceneId, x300569_g_Credit)
    end

    --����ֵ
    if x300569_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6( sceneId, x300569_g_BonusMoney6)
    end

    --5���̶���Ʒ
    for i, item in x300569_g_BonusItem do
        AddQuestItemBonus( sceneId, item.item, item.n)
    end

    --6����ѡ��Ʒ
    for i, item in x300569_g_BonusChoiceItem do
        AddQuestRadioItemBonus( sceneId, item.item, item.n)
    end

	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300569_g_ScriptId, x300569_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300569_DispatchContinueInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
    AddQuestText( sceneId, x300569_g_ContinueInfo)
    AddQuestText( sceneId, " ")
	EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, NPCId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300569_DispatchCompletedInfo( sceneId, selfId, NPCId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300569_g_MissionName)
    AddQuestText( sceneId, x300569_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    -- ����ϵ��
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
    local level = GetLevel( sceneId, selfId)
	local exp = level * x300569_g_CoffExp
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end
    
    -- ��������
    local money = level * x300569_g_CoffMoney
    if money > 0 then
        AddQuestMoneyBonus2( sceneId, money)
    end
    if x300569_g_Credit > 0 then
        AddQuestMoneyBonus5( sceneId, x300569_g_Credit)
    end
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, NPCId, x300569_g_ScriptId, x300569_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--���ﱻɱ����Ϣ����
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------------------------
--��Ʒ�ı�
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
	
	if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 and IsQuestHaveDoneNM( sceneId, selfId, x300569_g_MissionId ) <= 0 then
		local needitem = 0
		for i, item in x300569_g_MissionItemTable do
			if  itemdataId == item.itemId then
				needitem = 1
				
				SetQuestByIndex( sceneId, selfId, misIndex, i, 1)
			end
		end
		if needitem ~= 1 then
			return
		end
        
		x300569_ProcQuestLogRefresh( sceneId, selfId, x300569_g_MissionId)
		
		for i, item in x300569_g_MissionItemTable do
			if item.itemId ~= itemdataId and HaveItemInBag( sceneId, selfId, item.itemId ) < 0 then
				return
			end
		end
		
		Msg2Player( sceneId, selfId, "#Y���ҵ������й�Ʒ����ȥ����������ʹ�ɡ�", 8, 3)
		
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
	end
end

---------------------------------------------------------------------------------------------------
--����NPC�¼�
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
    
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
        if npcGuid == x300569_g_TargetNPC then
            if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 and GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
                AddQuestNumText( sceneId, x300569_g_MissionId, x300569_g_MissionName, 6)
            else
                AddQuestNumText( sceneId, x300569_g_MissionId, x300569_g_MissionName, 7)
            end
        end
    end
end

function x300569_GetMissionDate( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3] )
end

function x300569_SetMissionDate( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3], value)
end

function x300569_GetDayCount( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3] )
end

function x300569_SetDayCount( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3], value)
end

function x300569_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
 
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
        
        local index = -1
        for i, item in x300569_g_MissionItemTable do
			if item.gpId == gpType then
				index = i
				break
			end
        end
        
        if index ~= -1 then
			if HaveItemInBag( sceneId, selfId, x300569_g_MissionItemTable[index].itemId ) < 0 then
                return 0
            else
            	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
                Msg2Player( sceneId, selfId, "���Ѿ����������и�����Ʒ����ȥ�Ҹ�����ʹ�ύ����ɡ�", 8, 3)
               else
               	Msg2Player( sceneId, selfId, "���Ѿ��õ��˴˸�����Ʒ����ȥ�ҵ���ĸ�����Ʒ�ɡ�", 8, 3)
               end
                return 1
            end
        else
			Msg2Player( sceneId, selfId, "���ƺ�������Ҫ�ҵĸ�����Ʒ��", 8, 3)
            return 1
        end
    else
        Msg2Player( sceneId, selfId, "��û�н��ܡ��¡��������ѣ����ܲɼ�", 8, 3)
        return 1
    end
end

function x300569_OnRecycle( sceneId, selfId, targetId, gpType, needItemID)
    if GetGameOpenById( x300569_g_IsEnableId) <= 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, x300569_g_MissionId) > 0 then
   
        local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
        
        if GetQuestParam( sceneId, selfId, misIndex, 0) == 0 then
			for i, item in x300569_g_MissionItemTable do
			
				if item.itemId == needItemID and item.gpId == gpType and HaveItemInBag( sceneId, selfId, needItemID ) < 0 then
					-- ���ѡ��ɼ���Ʒ
					BeginAddItem( sceneId)
					
					AddItem( sceneId, needItemID, 1)
	                
					-- ���ÿ�βɼ���60%���������ø�������һ�ᣨid:12030080���������������(id:12030081)��������������(id:12030082)���ֵ���֮һ�����ֵ��߲��󶨣��ɽ��ס�
					if random(1, 100) <= 60 then
						local rnd = random(1, 3)
						if rnd == 1 then
							AddItem( sceneId, 12030080, 1)
						elseif rnd == 2 then
							AddItem( sceneId, 12030081, 1)
						else
							AddItem( sceneId, 12030082, 1)
						end
						
					end
	                
					if EndAddItem( sceneId, selfId) > 0 then
						AddItemListToPlayer( sceneId, selfId)
						return 1
					else
						Msg2Player( sceneId, selfId, "�޷��õ��ɼ���Ʒ�������������", 8, 3)
					end
				end
			end
        end
    else
        Msg2Player( sceneId, selfId, "��û�н��ܡ��¡��������ѣ����ܲɼ�", 8, 3)
    end

    return 0
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300569_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300569_g_MissionId)
	
	local fmt = {}
	for i = 1, 5 do
		fmt[i] = {}
		if GetQuestParam(sceneId, selfId, misIndex, i) == 1 then
			fmt[i][1] = "#G"
			fmt[i][2] = 1
		else
			fmt[i][1] = "#W"
			fmt[i][2] = 0
		end
	end
		
    local target = format(x300569_g_strMissionTarget2,
		fmt[1][1], fmt[1][2],
		fmt[2][1], fmt[2][2],
		fmt[3][1], fmt[3][2],
		fmt[4][1], fmt[4][2],
		fmt[5][1], fmt[5][2])
		
	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                               x300569_g_MissionName,               -- ����
                               x300569_g_strMissionTitle,               -- ��������
                               target,			-- ����Ŀ��
                               x300569_g_MissionReply,              -- ����NPC
                               x300569_g_strMissionBook,            -- ������
                               x300569_g_MissionInfo,               -- ��������
                               x300569_g_MissionHelp)               -- ������ʾ
    local level = GetLevel( sceneId, selfId)
    local exp = level * x300569_g_CoffExp
    if exp > 0 then
        AddQuestExpBonus( sceneId, exp)
    end
    	
    -- ��������
    local money = level * x300569_g_CoffMoney
    if money > 0 then
        AddQuestMoneyBonus2( sceneId, money)
    end
    if x300569_g_Credit > 0 then
        AddQuestMoneyBonus5( sceneId, x300569_g_Credit)
    end
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end
