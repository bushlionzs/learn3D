-- 
x310162_g_scriptId 		= 310162
x310162_g_MissionId     = 9320
x310163_g_DengmiMissionId	= 9315			--����ID
x310162_g_TianfuItems				= {11010100,11010101,11010102}

function x310162_Yizhesanyou_Reward( sceneId, selfId)
    -- ���⽱��
    local rewardExt = 0
    local itemExt = 0

    SetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3], GetDayOfYear() )

    local playerLevel = GetLevel( sceneId, selfId)
	local xp = playerLevel * 7000
    if xp > 0 then
        AddExp( sceneId, selfId, xp)
        Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", xp).."��", 8, 2)
        Msg2Player( sceneId, selfId, format( "���#R����%d��#cffcf00�Ľ���", xp), 8, 3)
    end
    
    SetShengWang( sceneId, selfId, GetShengWang( sceneId, selfId) + 150)
    Msg2Player( sceneId, selfId, format( "���#R%d������#cffcf00�Ľ���", 150).."��", 8, 2)
    Msg2Player( sceneId, selfId, format( "���#R%d������#cffcf00�Ľ���", 150), 8, 3)
    -- ����Daycount
    local count = GetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3] )
    SetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3], count + 1)
    local value = random( 1, 100)
    if value > 20 and value <= 40 then
        BeginAddItem( sceneId)
        AddItem( sceneId, 12030107, 1)
        if EndAddItem( sceneId, selfId) <= 0 then
            Msg2Player( sceneId, selfId, "������ˡ��¡��������ѡ�������ı����������޷���òر�ͼ������", 8, 2)
        else
            AddItemListToPlayer( sceneId, selfId)
        end
    end
    x310162_AddTianfuItem( sceneId, selfId)
    CallScriptFunction( 256224, "Finishyizhe", sceneId, selfId)
    Msg2Player( sceneId, selfId, format( "������ˡ��¡���������"), 8, 3)
end

function x310162_Dengmi_Reward( sceneId, selfId)

	local nCurDay = GetDayOfYear()
	SetQuestData(sceneId,selfId,MD_DENGMI_DATE[1],MD_DENGMI_DATE[2],MD_DENGMI_DATE[3],nCurDay)
	
	local level = GetLevel(sceneId,selfId)
	local name = GetName(sceneId,selfId)

	if name == nil then
		name = "ErrorName"
	end
	
	
	
	--������
	local score = GetQuestData(sceneId,selfId,MD_DENGMI_SCORE[1],MD_DENGMI_SCORE[2],MD_DENGMI_SCORE[3])
	local bonusExp = level*7000
	AddExp(sceneId,selfId,bonusExp)

	local msg = format("�������#R%d�㾭��ֵ#cffcf00�Ľ���",bonusExp)

	LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
    LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--	if level < 70 then
--		local bonusExp = level * 500 * 10
--		AddExp(sceneId,selfId,bonusExp)
--
--		local msg = format("�������%d�㾭��ֵ�Ľ���",bonusExp)
--
--		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--	else
--		local bonusExp = level * 650 * 10
--		AddExp(sceneId,selfId,bonusExp)
--
--		local msg = format("�������%d�㾭��ֵ�Ľ���",bonusExp)
--
--		LuaScenceM2Player(sceneId, selfId, msg, name , 2,1)
--        LuaScenceM2Player(sceneId, selfId, msg, name , 3,1)
--    end
--
    local bonusMoney = level*300
    local buff 	=	9011
    local buff1 =	9013
    local buff2 =	9012
    if IsHaveSpecificImpact( sceneId, selfId, buff) == 1 or IsHaveSpecificImpact( sceneId, selfId, buff1) == 1  or IsHaveSpecificImpact( sceneId, selfId, buff2) == 1 then
        AddMoney( sceneId, selfId, 0, bonusMoney, x310162_g_scriptId)
    else
        AddMoney( sceneId, selfId, 1, bonusMoney, x310162_g_scriptId)
    end

    BeginAddItem( sceneId)
    AddItem( sceneId, 12030107, 2)
    local res = EndAddItem( sceneId, selfId)
    if res > 0 then
        AddItemListToPlayer( sceneId, selfId)
    else
        LuaScenceM2Player( sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 2, 1)
        LuaScenceM2Player( sceneId, selfId, "#cffcf00��Ʒ���������޷��õ�������Ʒ��", name , 3, 1)
    end
	x310162_AddTianfuItem( sceneId, selfId)
    SetQuestData( sceneId, selfId, MD_QUEST_DENGMI_COUNT[1], MD_QUEST_DENGMI_COUNT[2], MD_QUEST_DENGMI_COUNT[3], 10)
    SetQuestData( sceneId, selfId, MD_QUEST_DENGMI_DATE[1], MD_QUEST_DENGMI_DATE[2], MD_QUEST_DENGMI_DATE[3], GetDayOfYear() )
end

function x310162_Tiesan_Reward( sceneId, selfId)
    local level = GetLevel( sceneId, selfId)
    local award1 = floor(100*70*level)
    local award2 = floor(100*70*level)
    local award = 0
    if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
        award = award1;
    elseif GetLevel(sceneId, selfId) >=70 then
        award = award2;
    end
    AddExp(sceneId, selfId, award)
    Msg2Player( sceneId, selfId, format("#Y���#R����%d#Y�Ľ���", award), 8, 3)
    Msg2Player( sceneId, selfId, format("#Y���#R����%d#Y�Ľ�����", award), 8, 2)

    local nShengWang = GetShengWang( sceneId, selfId)
    nShengWang = nShengWang + 200
    SetShengWang( sceneId, selfId, nShengWang )
    message = format("�������%d�Ľ�����", 200)
    BeginQuestEvent(sceneId);
        AddQuestText(sceneId, message);
    EndQuestEvent();
    DispatchQuestTips(sceneId, selfId);
    Msg2Player(sceneId,selfId,message,4,2)
    local day = GetDayOfYear()
    SetQuestData(sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[1], MD_TIEREN_ACCEPTTIME_DAY[2], MD_TIEREN_ACCEPTTIME_DAY[3], day)
    SetQuestData(sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3], 1)

	x310162_AddTianfuItem( sceneId, selfId)
    -- ���һ�Ųر�ͼ
    BeginAddItem( sceneId)
    AddItem( sceneId, 12030107, 1)
    if EndAddItem( sceneId, selfId) <= 0 then
        Msg2Player( sceneId, selfId, "�����������޷���òر�ͼ������", 8, 2)
    else
        AddItemListToPlayer( sceneId, selfId)
        Msg2Player( sceneId, selfId, "���һ�Ųر�ͼ�Ľ�����", 8, 2)
    end
end

function x310162_Yizhe_Check( sceneId, selfId)
    local curTime = GetMinOfDay()
    if curTime < 1170 then
        Msg2Player( sceneId, selfId, "�������ѻ��δ��ʼ�����ڼ��껪�ʱ��19��30����24��00��ʹ��", 8, 3)
        return 0
    end

    -- ����ɫ�����ǲ������������
    if IsHaveQuestNM( sceneId, selfId, 9320) > 0 then
        Msg2Player( sceneId, selfId, "���Ѿ�������������ˣ���ȥ��ɰɡ�", 8, 3)
        return 0
    end

	local nCurDay = GetDayOfYear()
    if nCurDay == GetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3] ) then
        if GetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3] ) > 1 then
            Msg2Player( sceneId, selfId, "�������Ѿ�����������񣬲�����ʹ�����ֱ�", 8, 3)
            return 0
        end
    else
        SetQuestData( sceneId, selfId, MD_YIZHESANYOU_DATE[ 1], MD_YIZHESANYOU_DATE[ 2], MD_YIZHESANYOU_DATE[ 3], GetDayOfYear() )
        SetQuestData( sceneId, selfId, MD_YIZHESANYOU_COUNTER[ 1], MD_YIZHESANYOU_COUNTER[ 2], MD_YIZHESANYOU_COUNTER[ 3], 1)
    end

    return 1
end

function x310162_Dengmi_Check( sceneId, selfId)
    local curTime = GetMinOfDay()
    if curTime < 1170 then
        Msg2Player( sceneId, selfId, "���ջ��δ��ʼ�����ڼ��껪�ʱ��19��30����24��00��ʹ��", 8, 3)
        return 0
    end

	if IsHaveQuest(sceneId,selfId, x310163_g_DengmiMissionId) > 0 then
		Msg2Player( sceneId, selfId, "���Ѿ�������̳���ջ����񣬲�����ʹ�����ֱ�", 8, 3)
		return 0
	end
	
	
    if GetQuestData( sceneId, selfId, MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3] ) == GetDayOfYear() and 
       GetQuestData( sceneId, selfId, MD_DENGMI_SCORE[1], MD_DENGMI_SCORE[2], MD_DENGMI_SCORE[3] ) > 0 then
        Msg2Player( sceneId, selfId, "������Ѿ��μӹ���̳���ջ��ˣ�������ʹ�����ֱ�", 8, 3)
        return 0
    end

    return 1
end

function x310162_Tiesan_Check( sceneId, selfId)
    local curTime = GetMinOfDay()
    if curTime < 1170 then
        Msg2Player( sceneId, selfId, "����������δ��ʼ�����ڼ��껪�ʱ��19��30����24��00��ʹ��", 8, 3)
        return 0
    end

    if IsHaveQuestNM( sceneId, selfId, 7537) > 0 or IsHaveQuestNM( sceneId, selfId, 7538) > 0 or IsHaveQuestNM( sceneId, selfId, 7539) > 0 or IsHaveQuestNM( sceneId, selfId, 7551) > 0 or IsHaveQuestNM( sceneId, selfId, 7552) > 0 then
        Msg2Player( sceneId, selfId, "���Ѿ�������������ˣ���ȥ��ɰ�", 8, 3)
        return 0
    end

	local nCurDay = GetDayOfYear()
    if nCurDay == GetQuestData( sceneId, selfId, MD_TIEREN_ACCEPTTIME_DAY[ 1], MD_TIEREN_ACCEPTTIME_DAY[ 2], MD_TIEREN_ACCEPTTIME_DAY[ 3] ) then
        if GetQuestData( sceneId, selfId, MD_TIEREN_COMMITTIME[1], MD_TIEREN_COMMITTIME[2], MD_TIEREN_COMMITTIME[3] ) >= 1 then
            Msg2Player( sceneId, selfId, "�������Ѿ���ȡ������������������ʹ�����ֱ�", 8, 3)
            return 0
        end
    end

    return 1
end

-- 
x310162_g_ScriptTable   = {
                            { guid = 139129, costCount = 40, check = x310162_Yizhe_Check,  proc = x310162_Yizhesanyou_Reward, description = "\t��Ҫ��#R40#Wö#{_ITEM11990117}���һ��#G��������#Wô��\n\tʹ�ü��껪���ֱ�����������Ѻ���������������ѹ���������ƴΣ����齱���̶�Ϊ�еȽ�����������ɼ���ȸ������Ĭ��Ϊ�ɼ���������ȸ�����ر�ͼ��ü���ͬ�����������" }, 
                            { guid = 139133, costCount = 40, check = x310162_Dengmi_Check, proc = x310162_Dengmi_Reward,      description = "\t��Ҫ��#R40#Wö#{_ITEM11990117}��ɽ������е�#G��̳����#Wô��\n\tʹ�ü��껪���ֱҿ�һ���Ի�����е��ս��������ղ����ٴβµ��ա�" }, 
                            { guid = 139100, costCount = 50, check = x310162_Tiesan_Check, proc = x310162_Tiesan_Reward,      description = "\t��Ҫ��#R50#Wö#{_ITEM11990117}��ɽ����#G��������#Wô��\n\tʹ�ü��껪���ֱҿ���˲������������������������ղ����ٴβμ��������" }, 
}
-- 
x310162_g_CurrencyID    = 11990117

----------------------------------------------------------------------------------------------
--ö��
----------------------------------------------------------------------------------------------
function x310162_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    -- 
  local level = GetLevel( sceneId, selfId)
  if level <40 then
   return
  end
  AddQuestNumText( sceneId, x310162_g_scriptId, "ʹ�ü��껪���ֱ�", 3, 1)
end

----------------------------------------------------------------------------------------------
--�ű�Ĭ���¼�
----------------------------------------------------------------------------------------------
function x310162_ProcEventEntry( sceneId ,selfId, npcId, idScript, idExt)
    local id = GetMonsterGUID( sceneId, npcId)
    for i, item in x310162_g_ScriptTable do
    	if id == 139133 then
	    	local nDate   = GetQuestData(sceneId,selfId,MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3] )
			local nCurDay = GetDayOfYear()
			if nCurDay == nDate then
				BeginQuestEvent(sceneId)
		        AddQuestText(sceneId,"#Y"..x310164_g_MissionName)
		        AddQuestText(sceneId,"ÿ��ֻ�ܲ���һ�Σ�����������")
		        EndQuestEvent()
		        DispatchQuestEventList(sceneId, selfId, npcId, x310162_g_ScriptId, x310162_g_MissionId);
		        return
		    end
		    
		    if IsHaveQuest(sceneId,selfId, x310163_g_DengmiMissionId) > 0 then
		    	BeginQuestEvent(sceneId)
		        AddQuestText(sceneId,"#Y"..x310164_g_MissionName)
		        AddQuestText(sceneId,"���Ѿ�������̳���ջ����񣬲�����ʹ�����ֱ�")
		        EndQuestEvent()
		        DispatchQuestEventList(sceneId, selfId, npcId, x310162_g_ScriptId, x310162_g_MissionId);
				--Msg2Player( sceneId, selfId, "���Ѿ�������̳���ջ����񣬲�����ʹ�����ֱ�", 8, 3)
				return 0
			end
	
		  
	    end
    
    
        if id == item.guid then
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, "#Y���껪���ֱ�" )
                AddQuestText( sceneId, item.description)
            EndQuestEvent()
            DispatchQuestInfo( sceneId, selfId, npcId, x310162_g_scriptId, -1)
            break
        end
    end
end

function x310162_AddTianfuItem( sceneId, selfId)
	local level = GetLevel( sceneId, selfId)
	if level >= 80 then
		if random( 1, 100) <= 22 then
			local nIndex = random(1,3)
			BeginAddItem( sceneId)
	        AddItem( sceneId, x310162_g_TianfuItems[nIndex], 1)
	        if EndAddItem( sceneId, selfId) <= 0 then
	            Msg2Player( sceneId, selfId, "������ı����������޷�����츳���߽�����", 8, 2)
	        else
	            AddItemListToPlayer( sceneId, selfId)
	        end
		end
	end
end

function x310162_ProcAcceptCheck( sceneId, selfId, NPCId)
    local count = GetItemCount( sceneId, selfId, x310162_g_CurrencyID)
    local id = GetMonsterGUID( sceneId, NPCId)
    
--    if id == 139133 then
--    	local nCurDay = GetDayOfYear()
--		SetQuestData(sceneId,selfId,MD_DENGMI_DATE[1], MD_DENGMI_DATE[2], MD_DENGMI_DATE[3], nCurDay )
--    end
    
    
    local need = 0
    local elem = nil
    for i, item in x310162_g_ScriptTable do
        if id == item.guid then
            need = item.costCount
            elem = item
            break
        end
    end

    if count >= need then
        if elem.check( sceneId, selfId) == 1 then
            if DelItem( sceneId, selfId, 11990117, need) == 1 then
                elem.proc( sceneId, selfId)
            else
                Msg2Player( sceneId, selfId, "�۳�#{_ITEM11990117}ʧ��", 8, 3)
                return 0
            end
        end
    else
        Msg2Player( sceneId, selfId, format( "�����ϵ�#{_ITEM11990117}����%dö", need), 8, 3)
        return 0
    end

 	
 
    return 1
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310162_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310162_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--����
----------------------------------------------------------------------------------------------
function x310162_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--����Ƿ�����ύ
----------------------------------------------------------------------------------------------
function x310162_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--ɱ����������
----------------------------------------------------------------------------------------------
function x310162_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--���������¼�
----------------------------------------------------------------------------------------------
function x310162_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--���߸ı�
----------------------------------------------------------------------------------------------
function x310162_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


