--�����ھ����� add by ������090112��

--MisDescBegin

x300518_g_ScriptId = 300518
-- ��������
x300518_g_MissionName = "�����ˡ���������"
-- 
x300518_g_MissionHelp   = "\t��@item_12030020#Wȥ#aB#h00CCFF{goto_%d,%d,%d}(%d��%d)#aE#W̽��һ����������û��#G%s#W"
-- ����Ŀ��
x300518_g_MissionTarget = "  ��#aB#h00CCFF{goto_%d,%d,%d}(%d��%d)#aE#W����ʹ��@item_12030020#W�ھ�(%d/1)"
-- ������Ϣ
x300518_g_MissionInfo   = "\t����ҹ۲�ʥɽ֮�������쳣�����������������Ϊ�գ�ɽ�ж�Ȼ�кܶ���Ϊ��֪�Ļ�ʯ���ϣ��������ȵ�@npc_138502���ﹺ��һ��������������ȥ#aB#h00CCFF{goto_%d,%d,%d}(%d��%d)#aE����̽��һ����������û��#G%s#W��"
x300518_g_MissionInfo_High   = "\t����ҹ۲커�Ǻ������쳣����ˮԴ����������Ϊ�գ����϶�Ȼ�кܶ���Ϊ��֪�Ļ�ʯ���ϣ��������ȵ�@npc_138502���ﹺ��һ��������������ȥ#aB#h00CCFF{goto_%d,%d,%d}(%d��%d)#aE����̽��һ����������û��#G%s#W��"
-- ����δ���ʱNPC�Ի�����
x300518_g_MissionContinue   = "\t�㻹û���ҵ�#G%s#W�ء�"

--MisDescEnd
x300518_LevelToCapital		= 300		--������Ŀ�ʼ�ȼ�

x300518_OneRoundCount	= 10
x300518_HighBonusCircleCount = 10
-- 
x300518_g_DigNothing    = "����ʲôҲû�У�����������ʢ��(%d��%d)����ʹ�á�"

x300518_g_DigMissionID              = 6470
x300518_g_DigMissionID_End          = 6479

x300518_CountrySceneList	= {50, 150, 250, 350}
x300518_CapitalSceneId		= 0

--mission parameters index
x300518_UserLevelAccept		= 1
x300518_PositionGroup		= 2
x300518_ItemId			= 3
-- �ھ�Ŀ�������
x300518_g_CoordinateLib     = 
{
                                { posX = 422, posZ = 50  }, 
                                { posX = 378, posZ = 81  }, 
                                { posX = 428, posZ = 30 }, 
                                { posX = 411, posZ = 32 }, 
                                { posX = 425, posZ = 245 }, 
}

x300518_g_CoordinateLib_Cap     = 
{
                                { posX = 166, posZ = 68  }, 
                                { posX = 158, posZ = 109  }, 
                                { posX = 363, posZ = 271 }, 
                                { posX = 373, posZ = 371 }, 
                                { posX = 419, posZ = 436 }, 
}
-- �ھ�Ŀ��
x300518_g_DigTarget         =
{
                                { mission = 6470, id = 13013000, name = "������ʯ" }, 
                                { mission = 6471, id = 13013001, name = "�����ʯ" }, 
                                { mission = 6472, id = 13013002, name = "�����ʯ" }, 
                                { mission = 6473, id = 13013003, name = "���鰵ʯ" }, 
                                { mission = 6474, id = 13013004, name = "������ʯ" }, 
                                { mission = 6475, id = 13013000, name = "������ʯ" }, 
                                { mission = 6476, id = 13013001, name = "�����ʯ" }, 
                                { mission = 6477, id = 13013002, name = "�����ʯ" }, 
                                { mission = 6478, id = 13013003, name = "���鰵ʯ" }, 
                                { mission = 6479, id = 13013004, name = "������ʯ" }, 
}                                                   


-- ��Ч�ھ򡰰뾶����ʵ����һ��������
x300518_g_Radius    = 4

function x300518_ProcAcceptCheck( sceneId, selfId, targetId, MissionId)
    return 1
end

function x300518_ProcAccept( sceneId, selfId)
end

-- ��ʾ����δ���ʱNPC�ĶԻ���Ϣ
function x300518_ShowMissionContinueInfo( sceneId, selfId, targetId, MissionId)
    BeginQuestEvent( sceneId)
        -- ��������
        AddQuestText( sceneId, "#Y"..x300518_g_MissionName)
        local itemid, itemname = x300518_GetDigItem(MissionId)
       AddQuestText( sceneId, format( x300518_g_MissionContinue, itemname) )
    EndQuestEvent()
    DispatchQuestEventList( sceneId, selfId, targetId)
end

-- �ھ��¼������˺������ã��μ���������ʹ�ýű�common_cangbaotu_item.lua������0��ʾû�н������ھ�
function x300518_OnDigbyShovel( sceneId, selfId )

	--�жϵ�ǰ�����ǲ����ھ�����
	local MissionId = x300518_GetRandMissionId(sceneId, selfId)
	if (MissionId < x300518_g_DigMissionID or MissionId > x300518_g_DigMissionID_End) then
		return 0
	end

	-- �ж���û�������Ƿ����
	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)

	local isFinish = GetQuestParam( sceneId, selfId, misIndex, 0 )
	if isFinish ~= 0 then
		return 0
	end

        -- �õ��ھ�Ŀ�������
	local userlevelaccept = GetQuestParam( sceneId, selfId, misIndex, x300518_UserLevelAccept )
	local positiongroup = GetQuestParam( sceneId, selfId, misIndex, x300518_PositionGroup )

	local posX,posZ,destSceneId = x300518_GetDigPosition(sceneId, selfId, userlevelaccept, positiongroup)
	if (destSceneId ~= sceneId) then	--���ڳ���������
		return 0
	end
	local itemid,itemname =x300518_GetDigItem(MissionId)
	
	-- ��õ�ǰ����
        local x, z = GetWorldPos( sceneId, selfId)
	
        if abs( x - posX) > x300518_g_Radius or abs( z - posZ) > x300518_g_Radius then
		--�ھ�ص㲻��
            BeginQuestEvent( sceneId)
                AddQuestText( sceneId, format( x300518_g_DigNothing, posX, posZ) )
            EndQuestEvent()
            DispatchQuestTips( sceneId, selfId)
            Msg2Player( sceneId, selfId, format( x300518_g_DigNothing, posX, posZ), 8, 2)
            return 0
        end

        -- �ڵ���Ʒ����ӵ�����
        BeginAddItem( sceneId)
		AddItem( sceneId, itemid, 1)
        local result = EndAddItem( sceneId, selfId)
        if result == 0 then
            BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "�����������޷������ڵ�����Ʒ��" )
            EndQuestEvent( sceneId)
            DispatchQuestTips( sceneId, selfId)
            Msg2Player( sceneId, selfId, "�����������޷������ڵ�����Ʒ��", 8, 2)
            return 1
        end
        BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "��õ���"..itemname.."��" )
		AddItemListToPlayer( sceneId, selfId)
		SetQuestByIndex( sceneId, selfId, misIndex, x300518_ItemId, itemid) -- ���µõ���������Ʒ
        EndQuestEvent( sceneId)

        DispatchQuestTips( sceneId, selfId)
        Msg2Player( sceneId, selfId, "��õ���"..itemname.."��", 8, 2)
        
	-- ����������ɱ��
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
        Msg2Player(sceneId, selfId, "�����Ѿ���ɣ�����ȥ�㱨�ɣ�", 8, 3)
	-- ����Q���
        x300518_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)

        -- �����������ô���
        CallScriptFunction( 300331, "LogicDeplete", sceneId, selfId)

	return 1
end

-- �ύ���񣬷���0��ʾʧ�ܣ�����1�ɹ�
function x300518_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId, farScriptId, constMD_Rand, retMissionId)
    return 1
end

-- ��ʾ������Ϣ
function x300518_ShowMissionInfo( sceneId, selfId, targetId, MissionId)

	local userlevel = GetLevel(sceneId, selfId);
	
    BeginQuestEvent( sceneId)
        -- ��������
        AddQuestText( sceneId, "#Y"..x300518_g_MissionName)
        -- �����ȡ�ھ������Ŀ��
	local randgroup,posX,posZ,destSceneId
	if (userlevel < x300518_LevelToCapital) then
		randgroup = random( 1, getn( x300518_g_CoordinateLib) )
		posX = x300518_g_CoordinateLib[ randgroup].posX
		posZ = x300518_g_CoordinateLib[ randgroup].posZ
		destSceneId = x300518_CountrySceneList[GetCurCountry(sceneId, selfId)+1];
	else
		randgroup = random( 1, getn( x300518_g_CoordinateLib_Cap) )
		posX = x300518_g_CoordinateLib_Cap[ randgroup].posX
		posZ = x300518_g_CoordinateLib_Cap[ randgroup].posZ
		destSceneId = x300518_CapitalSceneId;
	end

        -- ��Ϊ�����Ѿ�����ӵ�MissionList�����Կɰ���Щ����д��Mission Parameter
        local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 0) -- ��ɱ��
        SetQuestByIndex( sceneId, selfId, misIndex, x300518_UserLevelAccept, userlevel) -- ������ʱ�ĵȼ�
        SetQuestByIndex( sceneId, selfId, misIndex, x300518_PositionGroup, randgroup) -- �������
	SetQuestByIndex( sceneId, selfId, misIndex, x300518_ItemId, -1)
        -- ��������
        AddQuestText( sceneId, "#Y����Ŀ�꣺" )
	local itemid, itemName = x300518_GetDigItem(MissionId)

	local strMisInfo
	if (destSceneId == x300518_CapitalSceneId ) then
		strMisInfo = x300518_g_MissionInfo_High
	else
		strMisInfo = x300518_g_MissionInfo
	end

        AddQuestText( sceneId, format( strMisInfo, destSceneId, posX, posZ, posX, posZ, itemName) )

    EndQuestEvent()
    DispatchQuestInfoNM( sceneId, selfId, targetId, x300518_g_ScriptId, MissionId, 1)

--    DispatchQuestEventList( sceneId, selfId, targetId)
end

--��������
function x300518_AutoAccept( sceneId, selfId, targetId, MissionId)
	return AddQuest( sceneId, selfId, MissionId, x300518_g_ScriptId, 0, 0, 0, 1)
end

function x300518_AfterAccept(sceneId, selfId, targetId, MissionId, misIndex)
	--ˢ��Q���
	x300518_ProcQuestLogRefresh(sceneId, selfId, MissionId, misIndex)
end

function x300518_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId)

	MissionId = x300518_GetRandMissionId(sceneId, selfId)
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0
	end

	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);

	local submitguid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	--����������ύ�ˣ���ʾѡ��
	if submitguid ~= -1 and submitguid == npcGuid then	
		local state = GetQuestStateNM(sceneId, selfId, npcGuid, MissionId);
		return AddQuestTextNM(sceneId, selfId, npcGuid, MissionId, state, -1);
	end

    return 1
end

function x300518_ProcQuestLogRefresh( sceneId, selfId, MissionId, misIndex)

	if (misIndex == nil) then
		misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	end
	local finished = GetQuestParam( sceneId, selfId, misIndex, 0)
	local userlevelaccept = GetQuestParam( sceneId, selfId, misIndex, x300518_UserLevelAccept )
	local positiongroup = GetQuestParam( sceneId, selfId, misIndex, x300518_PositionGroup )
	local posX,posZ,destSceneId = x300518_GetDigPosition(sceneId, selfId, userlevelaccept, positiongroup)
	local itemid,itemname =x300518_GetDigItem(MissionId)
	local strName;
	strName = x300518_g_MissionName;
	local circle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	if (circle >= x300518_OneRoundCount) then
		circle = 1
	else
		circle = circle + 1
	end

	strName = strName.."("..circle;
	strName = strName.."/"..x300518_OneRoundCount;
	strName = strName..")";

	local reply_npcid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex );

	BeginQuestEvent(sceneId)
	
	local strMisInfo
	if (destSceneId == x300518_CapitalSceneId ) then
		strMisInfo = x300518_g_MissionInfo_High
	else
		strMisInfo = x300518_g_MissionInfo
	end
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                strName,          -- ��������
                                format( x300518_g_MissionTarget, destSceneId, posX, posZ, posX, posZ, finished),
                                "@npc_"..reply_npcid,             --����NPC
                                format( x300518_g_MissionHelp, destSceneId, posX, posZ, posX, posZ, itemname),
                                format( strMisInfo, destSceneId, posX, posZ, posX, posZ, itemname),
                                "@item_12030020��@npc_138502�����ۣ�����ȥ�����ɣ�" )

	--������
	local curlevel = GetLevel(sceneId, selfId)
	local exp = x300518_GetExpAward ( sceneId, selfId, curlevel );
	local money,shengw = x300518_GetMoneyAward ( sceneId, selfId, curlevel );
	if(exp > 0) then
		AddQuestExpBonus(sceneId, exp)
	end
	if(money > 0) then
		AddQuestMoneyBonus2(sceneId, money)
	end
	if(shengw > 0) then
		AddQuestMoneyBonus5(sceneId, shengw)
	end
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- ����������
function x300518_ProcQuestAbandon(sceneId, selfId, MissionId)
	MissionId = x300518_GetRandMissionId(sceneId, selfId)
	if (IsHaveQuestNM(sceneId, selfId, MissionId) == 0) then
		return
	end
	local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
	local saveditemid = GetQuestParam( sceneId, selfId, misIndex, x300518_ItemId )
	if saveditemid >= 0 then
		DelItem( sceneId, selfId, saveditemid, 1)
	end

	CallScriptFunction( 300501, "ProcQuestAbandon", sceneId, selfId, MissionId)
end

function x300518_GetRandMissionId(sceneId, selfId)
	return  x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_RANDMISSIONID)
end

function x300518_SetMD(sceneId, selfId, MDNAME, value)
	SetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3], value);
end

function x300518_GetMD(sceneId, selfId, MDNAME)

	return GetQuestData(sceneId, selfId, MDNAME[1], MDNAME[2], MDNAME[3])
end

--���������û�б仯�������ø߽��������������µ�����
function x300518_CheckDayChanged(sceneId, selfId)
	local lastDay = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY)
	local today = GetDayOfYear()
	if lastDay ~= today then	--���ڱ仯
		x300518_SetMD(sceneId, selfId, MD_GUOJIARENWU_LASTDAY, today)
		x300518_SetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH, 0)
	end
end

--���齱��
function x300518_GetExpAward(sceneId, selfId, startlevel)

	x300518_CheckDayChanged(sceneId, selfId)
	local circle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)
	
	circle = circle + 1
	if (circle > x300518_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local exp_rate
	if GetLevel(sceneId, selfId) >= 60 then
		exp_rate = 3650
	else
		exp_rate = 2800
	end

	local BonusExp = startlevel * exp_rate * (circle * 2 - 1) / 200
	if (highcircle <= x300518_HighBonusCircleCount) then
		BonusExp = BonusExp * 5
	end
    -- �������룬���Ծ��鷭��
    BonusExp = BonusExp * 2
	return BonusExp;

end

--��Ǯ����
function x300518_GetMoneyAward(sceneId, selfId, startlevel)

	x300518_CheckDayChanged(sceneId, selfId)
	local circle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_CIRCLE)
	local highcircle = x300518_GetMD(sceneId, selfId, MD_GUOJIARENWU_HIGH)

	circle = circle + 1
	if (circle > x300518_OneRoundCount) then
		circle = 1
	end

	highcircle = highcircle + 1

	local BonusMoney = startlevel
	local shengw = 5
	if (highcircle <= x300518_HighBonusCircleCount) then
		BonusMoney = BonusMoney * 5
		shengw = 25
	end
	return BonusMoney, shengw;
end

function x300518_GetDigPosition(sceneId, selfId, userlevelaccept, positiongroup)

	local posX,posZ,destSceneId
	if (userlevelaccept < x300518_LevelToCapital) then
		if (positiongroup == nil or positiongroup < 1 or positiongroup > getn(x300518_g_CoordinateLib)) then
			return -1,-1,-1
		end
		posX = x300518_g_CoordinateLib[positiongroup].posX;
		posZ = x300518_g_CoordinateLib[positiongroup].posZ;
		destSceneId = x300518_CountrySceneList[GetCurCountry(sceneId, selfId)+1];
	else
		if (positiongroup == nil or positiongroup < 1 or positiongroup > getn(x300518_g_CoordinateLib_Cap)) then
			return -1,-1,-1
		end
		posX = x300518_g_CoordinateLib_Cap[positiongroup].posX;
		posZ = x300518_g_CoordinateLib_Cap[positiongroup].posZ;
		destSceneId = 0
	end

	return posX, posZ, destSceneId
end

function x300518_GetDigItem(MissionId)

	local itemid = -1
	local itemname = ""
	for i, item in x300518_g_DigTarget do
		if item.mission == MissionId then
			itemname = item.name
			itemid = item.id
			break
		end
	end

	return itemid,itemname
end