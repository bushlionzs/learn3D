-- �ʵ�����
--MisDescBegin

x300971_g_ScriptId 					= 300971                  --�ű�ID
x300971_g_MissionId 				= 7790                    --����ID

x300971_g_MissionKind 				= 1                       --��������
x300971_g_LevelLess					= 80                      --�������ŵȼ�  <=0 ��ʾ������

x300971_g_MissionName				= "�����ҡ��ʵ�����"
x300971_g_MissionTarget				= "  �����˸��ռ�@npc_31131(%d/%d)"      --����Ŀ��
x300971_g_MissionInfo				= "\t����ʹ�����������˸��Ⱥ򣬽�ʹ���Ǵ���������Ʒ�������⽫�ʹ������ǡ�������Դ��Ϊ��Ҫ�����������ǹ���ǿʢ��������������Ҳ�������ⷪ��Ʒ�������񣬲�Ҫ���󣬼���������ȡ������Ʒ��"      --������Ϣ
x300971_g_ContinueInfo				= "\t��Ҫ���󣬼���������ȡ������Ʒ��"	  --���������Ϣ
x300971_g_MissionCompleted			= "��Ϊ���ǹ��Ҽ�����ǿʢ������׿Խ����!"	  --���������Ϣ
x300971_g_MissionHelp				= "\t��Ʒ��Ұ�ⳡ�����˸����ڣ����������������������Ʒ!"      --������ʾ��Ϣ
x300971_g_Missionruse				= "\tÿ�õ�һ����Ʒ�����д������齱�������п��ܻ�ö���߾��齱����"      --������

--Ŀ��
x300971_g_ExtTarget					= { {type=20,n=1,target=""} }


--����
x300971_g_ExpBonus					= 0     --���������� ����ֵ��0���ַ���Ϊ�գ���ʾû�и������
x300971_g_BonusItem					= {}	--��������Ʒ

x300971_g_BonusMoney1               = 0  --������������
x300971_g_BonusMoney2               = 0  --�������ǰ�����
x300971_g_BonusMoney3               = 0  --�������󶨽��
x300971_g_BonusMoney4               = 0  --��������͢����
x300971_g_BonusMoney5               = 0  --��������������
x300971_g_BonusMoney6               = 0  --����������

x300971_g_BonusChoiceItem           = {}

--MisDescEnd

x300971_g_GrowpointId				= 135 --��Ӧ������ID
x300971_g_Boss						= {type =9880,guid =-1,x = 128, z=128, facedir =3600000, title = ""}

x300971_g_CoffExp					= {120000, 12000, 2400, 1200} -- �ɼ�ʱ����
x300971_g_InherenceExp				= 770 -- �����츳���齱��
x300971_g_GuildMoney				= 100000 -- �������Ǯ����
x300971_g_MaxCount					= 5 -- һ���ܲɼ����ٴ�
-- ������NPC
x300971_g_TargetNPC                 = 139264

---------------------------------------------------------------------------------------------------
--�о��¼�
---------------------------------------------------------------------------------------------------
function x300971_ProcEnumEvent(sceneId, selfId, targetId, MissionId)

	local state = GetQuestStateNM(sceneId, selfId, targetId, x300971_g_MissionId)
	AddQuestNumText(sceneId,x300971_g_MissionId,x300971_g_MissionName,state, 0 )
end
---------------------------------------------------------------------------------------------------
--������ں���
---------------------------------------------------------------------------------------------------
function x300971_ProcEventEntry(sceneId, selfId, targetId, MissionId, nExtIdx)
	if IsHaveQuest( sceneId, selfId, x300971_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
		if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
			x300971_DispatchContinueInfo(sceneId, selfId, targetId) --δ���������ʾ
        else
            x300971_DispatchCompletedInfo(sceneId, selfId, targetId) --���������ʾ
        end
    else
		x300971_DispatchMissionInfo(sceneId, selfId, targetId)	--������Ϣ��ʾ
	end
end

---------------------------------------------------------------------------------------------------
--����������
---------------------------------------------------------------------------------------------------
function x300971_ProcAcceptCheck(sceneId, selfId, targetId)
	local bHaveMission	= IsHaveQuest(sceneId, selfId, x300971_g_MissionId)
	if( bHaveMission > 0) then
		return 0
	else
		return 1
	end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestAccept(sceneId, selfId, targetId, missionId)

    if IsHaveQuest(sceneId, selfId, x300971_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID(sceneId, selfId, x300971_g_MissionId)
		local count = GetQuestParam( sceneId, selfId, misIndex, 0)
        if GetQuestParam( sceneId, selfId, misIndex, 7) ~= 1 then
			Msg2Player(sceneId, selfId, "����Ϊδ���״̬��", 8, 2)
			Msg2Player(sceneId, selfId, "����Ϊδ���״̬", 8, 3)
			return
		end 

        x300971_SetDayCount(sceneId, selfId)

        DelQuest(sceneId, selfId, x300971_g_MissionId)
        Msg2Player(sceneId, selfId, "�����������:"..x300971_g_MissionName, 8, 3)
        Msg2Player(sceneId, selfId, "�����������:"..x300971_g_MissionName, 8, 2)
        
        AddGuildMoney(sceneId, selfId, x300971_g_GuildMoney)
        Msg2Player(sceneId, selfId, "���#R����Ǯ100��#cffcf00�Ľ���", 8, 2)
		Msg2Player(sceneId, selfId, "���#R����Ǯ100��#cffcf00�Ľ���", 8, 3)
	 	

		
        local level = GetLevel(sceneId, selfId)
        if level >= 80 then
			local refixInh = AddInherenceExp(sceneId, selfId, x300971_g_InherenceExp)
			local msg = format("���#R�츳ֵ%d��#cffcf00�Ľ�����",refixInh)
			Msg2Player(sceneId, selfId, msg, 8, 2)
			Msg2Player(sceneId, selfId, msg, 8, 3)
        end
    else
		if GetLevel( sceneId, selfId) < x300971_g_LevelLess then
			Msg2Player( sceneId, selfId, format("�ܱ�Ǹ�����ĵȼ�����%d�����޷����ܡ����ҡ��ʵ����", x300971_g_LevelLess), 8, 3)
			return
		end
		
		if GetGuildID( sceneId, selfId ) == -1 then
	 		--���ڰ����
			Msg2Player(sceneId, selfId, "�ܱ�Ǹ��û�а���޷���������", 8, 2)
			Msg2Player(sceneId, selfId, "�ܱ�Ǹ��û�а���޷���������", 8, 3)
			return
		end 

		if x300971_GetDayCount(sceneId, selfId) == 0 then
			Msg2Player( sceneId, selfId, "�������ȡ�������������������ɣ�", 8, 3)
			return
		end
		
		local ret = AddQuest( sceneId, selfId, x300971_g_MissionId, x300971_g_ScriptId, 0, 0, 0, 0) -- ������������
		if ret == 0 then
			Msg2Player(sceneId,selfId, "�����������������ʧ�ܣ�",8,3)
			return
		end
		
		-- ��ʾ���������Ϣ
		Msg2Player( sceneId, selfId, "�����������"..x300971_g_MissionName, 8, 3)
		Msg2Player( sceneId, selfId, "�����������"..x300971_g_MissionName, 8, 2)
		
	
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 0)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0)
		
		-- ����������ٺ�Q���
		x300971_ProcQuestLogRefresh( sceneId, selfId, x300971_g_MissionId)
		return 1
    end
end

---------------------------------------------------------------------------------------------------
--��������
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestAbandon( sceneId, selfId, MissionId)
	if IsHaveQuest( sceneId, selfId, x300971_g_MissionId) > 0 then
		DelQuest( sceneId, selfId, x300971_g_MissionId)
        x300971_SetDayCount(sceneId, selfId)
		Msg2Player( sceneId, selfId, "������������"..x300971_g_MissionName, 8, 3)
		Msg2Player( sceneId, selfId, "������������"..x300971_g_MissionName, 8, 2)
	end
end

---------------------------------------------------------------------------------------------------
--�ύ���񣬲��������Ƿ���ɻ���������ʾ���������Ϣ�������������Ϣ
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestSubmit( sceneId, selfId, targetId, selectRadioId, MissionId)
end

function x300971_BonusInfo(sceneId, selfId)

	local level = GetLevel(sceneId, selfId)

    --��������Ϣ
    AddQuestGuildMoneyBonus(sceneId, x300971_g_GuildMoney)
    
	if level >= 80 then
		local refixInhExp = RefixInherenceExp(sceneId, selfId, x300971_g_InherenceExp)
		AddQuestInherenceExpBonus(sceneId,refixInhExp)
	end
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300971_DispatchMissionInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)

    --������Ϣ
    AddQuestText( sceneId, "#Y"..x300971_g_MissionName)
    AddQuestText( sceneId, x300971_g_MissionInfo)
    AddQuestText( sceneId, " ")

	local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
	local count = GetQuestParam( sceneId, selfId, misIndex, 0)
	
	AddQuestText( sceneId,"#Y����Ŀ�꣺")
    AddQuestText( sceneId, format(x300971_g_MissionTarget, count, x300971_g_MaxCount))
	AddQuestText( sceneId, " ")
	AddQuestText(sceneId,"#Y������ʾ��")
    AddQuestText( sceneId, format(x300971_g_MissionHelp))
    AddQuestText( sceneId, " ")
							
    x300971_BonusInfo(sceneId, selfId)
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300971_g_ScriptId, x300971_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300971_DispatchContinueInfo( sceneId, selfId, targetId)
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
	local rnd = GetQuestParam( sceneId, selfId, misIndex, 1)
		
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300971_g_MissionName)
    AddQuestText( sceneId, format(x300971_g_ContinueInfo, x300971_g_TargetNPC))
	AddQuestText( sceneId, " ")
	
	AddQuestText( sceneId,"#Y��������")
	local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 7) == 0 then
		AddQuestText(sceneId, "δ���")
	else
		AddQuestText(sceneId, "�����")
	end
	
	x300971_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
    DispatchQuestDemandInfo( sceneId, selfId, targetId, x300971_g_ScriptId, x300971_g_MissionId,0)
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300971_DispatchCompletedInfo( sceneId, selfId, targetId)
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x300971_g_MissionName)
    AddQuestText( sceneId, x300971_g_MissionCompleted)
    AddQuestText( sceneId, " ")
    
    x300971_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, targetId, x300971_g_ScriptId, x300971_g_MissionId)
end

---------------------------------------------------------------------------------------------------
--���ﱻɱ����Ϣ����
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end

---------------------------------------------------------------------------------------------------
--��Ʒ�ı�
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
end

---------------------------------------------------------------------------------------------------
--����NPC�¼�
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestAttach( sceneId, selfId, targetId, npcGuid, misIndex, MissionId)
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300971_GetDayCount(sceneId, selfId)

	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_HUANGDIMILING_DATE[1], MD_HUANGDIMILING_DATE[2],MD_HUANGDIMILING_DATE[3])
	
	if today ~= lastday then
		return 1
	end
		
	return 0
end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x300971_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	SetQuestData(sceneId, selfId, MD_HUANGDIMILING_DATE[1], MD_HUANGDIMILING_DATE[2], MD_HUANGDIMILING_DATE[3], today)
end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300971_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
    local count = GetQuestParam( sceneId, selfId, misIndex, 0)
    
	BeginQuestEvent( sceneId)
    AddQuestLogCustomText( sceneId,
							"",									-- ����
                            x300971_g_MissionName,              -- ��������
                            format(x300971_g_MissionTarget, count, x300971_g_MaxCount),            --����Ŀ��
                            "@npc_"..x300971_g_TargetNPC,       --����NPC
                            format(x300971_g_Missionruse,x300971_g_TargetNPC), 				--������
                            x300971_g_MissionInfo,              --��������
                            x300971_g_MissionHelp			--����С��ʾ
                            )
                            
    x300971_BonusInfo(sceneId, selfId)
    
	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId)
end

--���ɺ�����ʼ
function x300971_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x300971_g_GrowpointId, sceneId, 0, -1)
end

--�ɼ�����
function x300971_OnOpen( sceneId, selfId, targetId, gpType, needItemID)
    if IsHaveQuestNM( sceneId, selfId, x300971_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
		local count = GetQuestParam( sceneId, selfId, misIndex, 0)
		if count == x300971_g_MaxCount then
			Msg2Player( sceneId, selfId, "ÿ����ÿ��ֻ�����ռ�5�ݹ�Ʒ,����������", 8, 3)
			return 1
		end
		return 0
    end
        Msg2Player( sceneId, selfId, "�ܱ�Ǹ����û�С����ҡ��ʵ����������޷��ɼ�", 8, 3)
    return 1
end

--��
function x300971_OnProcOver( sceneId, selfId, targetId )
end

--����
function x300971_OnRecycle( sceneId, selfId, targetId, gpType, needItemID)

    if IsHaveQuestNM( sceneId, selfId, x300971_g_MissionId) > 0 then
		local misIndex = GetQuestIndexByID( sceneId, selfId, x300971_g_MissionId)
		local count = GetQuestParam( sceneId, selfId, misIndex, 0)

		SetQuestByIndex( sceneId, selfId, misIndex, 0, count+1)
		if count+1 == x300971_g_MaxCount then
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
		end
		
		local level = GetLevel(sceneId, selfId)
		local rnd = random(1, 1000)
        local xp = 0
        if rnd == 1 then
			xp = level * x300971_g_CoffExp[1]
			if x300971_g_Boss.title~= "" then
				CreateMonster(sceneId, x300971_g_Boss.type, x300971_g_Boss.x, x300971_g_Boss.z, 1, 977, -1, x300971_g_Boss.guid, 21,-1,x300971_g_Boss.facedir, "", x300971_g_Boss.title)
			else
				CreateMonster(sceneId, x300971_g_Boss.type, x300971_g_Boss.x, x300971_g_Boss.z, 1, 977, -1, x300971_g_Boss.guid, 21,-1,x300971_g_Boss.facedir)
			end
			local killerName = GetName(sceneId,selfId)
			local msg1 = format("%s�ռ���ϡ�е��ⷪ��Ʒ������ͻϮ���˸����ṱƷ��Դ��",killerName)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_PLANE_SCROLL, 1)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_LEFTDOWN, 1)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_MAIN_RIGHTDOWN, 1)
		elseif rnd <= 101 then
			xp = level * x300971_g_CoffExp[2]
		elseif rnd <= 501 then
			xp = level * x300971_g_CoffExp[3]
		else
			xp = level * x300971_g_CoffExp[4]
		end
		AddExp(sceneId, selfId, xp);
		Msg2Player(sceneId, selfId, format( "�ռ��ⷪ��Ʒ���#R����%d��#cffcf00�Ľ���", xp), 8, 2)
		Msg2Player(sceneId, selfId, format( "�ռ��ⷪ��Ʒ���#R����%d��#cffcf00�Ľ���", xp), 8, 3)
	
		x300971_ProcQuestLogRefresh( sceneId, selfId, x300971_g_MissionId)
		return 1
    end

    return 0
end

function x300971_OnDie(sceneId, selfId, killerId)

end
	