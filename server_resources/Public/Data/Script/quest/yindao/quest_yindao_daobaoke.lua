--��������--������

--MisDescBegin
x203794_g_ScriptId = 203794
--x203794_g_MissionIdPre ={67,69,70,71}
x203794_g_MissionId = 3694
x203794_g_LevelLess	= 45 
x203794_g_MissionIdNext = -1
x203794_g_Name	={}
x203794_g_ExtTarget={{type=20,n=1,target="�Ķ�һ��@npc_81014����"}}
x203794_g_MissionName="�����ˡ���Į������"
x203794_g_MissionInfo="\t������Ž��������֮ǰ�����ѹ����Ĵ�����������̫��ɽ��̩ɽɽ´�����ص����Ͷ������Ʊ������Ѿã������ھ���ͼ�ҵ��������ء���������������Ĵ���Ҳ������ȻӦ���Ҵ�Ԫ���У�����������ί����ǰȥ������Щ�����ͣ�"  --��������
x203794_g_MissionTarget=""		
x203794_g_MissionCompleted="\t������������ɵķǳ���ɫ������ٸ��϶����ϱ���͢�úõĽ�����ģ���ץ��ʱ��ú���Ϣ�ɡ�\n\t�ǵ�ÿ�춼ȥ�����￴����һ��������в��ٰ�����"					--�������npc˵���Ļ�
x203794_g_ContinueInfo="\t������ĺÿ찡���ҵ��ط�����"
x203794_g_MissionHelp =	""
x203794_g_DemandItem ={}
x203794_g_ExpBonus = 500000
x203794_g_BonusMoney1 =5000
x203794_g_BonusMoney2 =0
x203794_g_BonusMoney3 =0
x203794_g_BonusMoney4 =0
x203794_g_BonusMoney5 =0
x203794_g_BonusMoney6 =0
x203794_g_BonusItem	=	{}
x203794_g_BonusChoiceItem ={}
x203794_g_NpcGUID ={{ guid = 140417, name = "������"} }
--MisDescEnd
--**********************************
-- ��˰��ɱ��
--x203794_g_MP_Tax        = 1
-- ������ɱ��
--x203794_g_MP_Hunt       = 2
-- ��������ɱ��
x203794_g_MP_Daobaoke  = 3
-- ���ȼ�
x203794_g_MaxLevel      =65

function x203794_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x203794_g_LevelLess or level >= x203794_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x203794_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x203794_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x203794_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x203794_g_MissionId, state, -1 )
	end
end

function x203794_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x203794_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x203794_g_ExpBonus )
    end
    if x203794_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x203794_g_BonusMoney1 )
    end
    if x203794_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x203794_g_BonusMoney2 )
    end
    if x203794_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x203794_g_BonusMoney3 )
    end
    if x203794_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x203794_g_BonusMoney4 )
    end
    if x203794_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x203794_g_BonusMoney5 )
    end
    if x203794_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x203794_g_BonusMoney6 )
    end
    for i, item in x203794_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x203794_g_BonusChoiceItem do
        AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x203794_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203794_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x203794_g_MissionId) > 0 then
        if x203794_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x203794_g_MissionName)
            AddQuestText(sceneId,x203794_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x203794_g_ScriptId, x203794_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x203794_g_MissionName)
            AddQuestText(sceneId,x203794_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x203794_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203794_g_ScriptId, x203794_g_MissionId);
        end
    elseif x203794_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x203794_g_MissionName)
        AddQuestText(sceneId,x203794_g_MissionInfo)
        AddQuestText( sceneId,"#Y����Ŀ�꣺")
        for i, item in x203794_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x203794_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#GС��ʾ:#W")
            AddQuestText(sceneId,x203794_g_MissionHelp )
        end
        x203794_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x203794_g_ScriptId, x203794_g_MissionId);
    end
end

function x203794_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x203794_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203794_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

function x203794_OnYinDaoCompleted( sceneId, selfId, nMode)   
	if nMode==nil then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x203794_g_MissionId ) == 0 then
		return
	end

	local misIndex = GetQuestIndexByID(sceneId,selfId,x203794_g_MissionId)  

	local n1 = GetQuestParam( sceneId, selfId, misIndex, 0 )	
	--local n2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	--local n3 = GetQuestParam( sceneId, selfId, misIndex, 2 )                                                

    if nMode ==0 then --������
   		SetQuestByIndex(sceneId,selfId,misIndex,0,1)

   		--if n2==1 and n3==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	--elseif nMode==1 then --��˰
   	--	SetQuestByIndex(sceneId,selfId,misIndex,1,1)
   	--	if n1==1 and n3==1 then
   	--		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   	--	end
   	--elseif nMode==2 then	-- ����
   	--	SetQuestByIndex(sceneId,selfId,misIndex,2,1)
   	--	if n1==1 and n2==1 then
   	--		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   	--	end
   	--end
end

function x203794_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x203794_g_MissionId) > 0 then
        return 
    end
    if IsQuestFullNM(sceneId,selfId)==1 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�ɽ�������������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 
    end

    --���ǰ������
    local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203794_g_MissionId  )
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

    if x203794_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x203794_g_MissionId, x203794_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x203794_g_MissionId)                                                  
            x203794_Msg2toplayer( sceneId, selfId,0)
            --SetQuestByIndex(sceneId,selfId,misIndex,x203794_g_MP_Tax,0)
            --SetQuestByIndex(sceneId,selfId,misIndex,x203794_g_MP_Hunt,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x203794_g_MP_Daobaoke,0)
            x203794_ProcQuestLogRefresh( sceneId, selfId, x203794_g_MissionId)
        end
    end                                                                    
end

function x203794_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x203794_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x203794_g_MissionId)
    x203794_Msg2toplayer( sceneId, selfId, 1)
end

function x203794_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203794_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end
    for j, item in x203794_g_BonusChoiceItem do
        if item.item == selectRadioId then
            AddItem( sceneId, item.item, item.n )
            break
        end
    end
    local ret = EndAddItem(sceneId,selfId)
    if ret <= 0 then
        if result == 1 then
            result = 0
        end
    end
	return result
end

function x203794_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203794_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x203794_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û�дﵽ���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x203794_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�����ռ䲻�㣬�������������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x203794_g_MissionId) > 0 then
        x203794_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x203794_g_MissionId)
        x203794_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x203794_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x203794_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
       -- AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203794_g_MissionIdNext )	
end

function x203794_GetBonus( sceneId, selfId,NpcID)
	if x203794_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x203794_g_ExpBonus);
  	end
	if x203794_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203794_g_BonusMoney1)
	end
    if x203794_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203794_g_BonusMoney2)
    end
    if x203794_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x203794_g_BonusMoney3)
    end
    if x203794_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x203794_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x203794_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x203794_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x203794_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x203794_g_BonusMoney6)
    end
end

function x203794_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "������������"..x203794_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x203794_g_MissionName.."��", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "������������"..x203794_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x203794_g_MissionName.."��", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "�����������"..x203794_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "�����������"..x203794_g_MissionName.."��", 0, 3)
        if x203794_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x203794_g_ExpBonus.."#Y�Ľ���", 0, 2)
        end
        if x203794_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x203794_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
        end
        if x203794_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x203794_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
        end
        if x203794_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��"..x203794_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
        end
        if x203794_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203794_g_BonusMoney4.."#Y�Ľ���", 0, 2)
        end
        if x203794_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x203794_g_BonusMoney5.."#Y�Ľ���", 0, 2)
        end
        if x203794_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x203794_g_BonusMoney6.."#Y�Ľ���", 0, 2)
        end
    end
end

function x203794_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x203794_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203794_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x203794_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203794_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x203794_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x203794_g_MissionId) < 1 then
        return
    end

    -- �������
    local misIndex = GetQuestIndexByID( sceneId, selfId, x203794_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x203794_g_MP_Hunt, 1)
    x203794_ProcQuestLogRefresh( sceneId, selfId, x203794_g_MissionId)
end

function x203794_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x203794_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x203794_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x203794_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x203794_g_MissionId, state, -1 )
    end
end

function x203794_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203794_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203794_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203794_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203794_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203794_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x203794_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    --local tax = GetQuestParam( sceneId, selfId, misIndex, x203794_g_MP_Tax)
   -- local hunt = GetQuestParam( sceneId, selfId, misIndex, x203794_g_MP_Hunt)
    local Daobaoke= GetQuestParam( sceneId, selfId, misIndex, x203794_g_MP_Daobaoke)
    local strTarget = format( "�����Ѿ���ɣ���ر�@npc_%d", x203794_g_NpcGUID[1].guid)

    if Daobaoke== 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        --if tax == 0 then
        --    strTarget = "  #W���һ����@npc_82057(0/1)\n"
        --else
        --    strTarget = "  #G���һ����@npc_82057(1/1)\n"
        --end
        --if hunt == 0 then
        --    strTarget = strTarget.."  #W���һ����@npc_82058(0/1)\n"
        --else
        --    strTarget = strTarget.."  #G���һ����@npc_82058(1/1)\n"
        --end
        if Daobaoke== 0 then
            strTarget = "  #W�Ķ�һ��@npc_81014����(0/1)"
        else
            strTarget = strTarget.."  #G�Ķ�һ��@npc_81014����(1/1)"
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x203794_g_MissionName,          -- ��������
                                strTarget,
                                "",                             --����NPC
                                "ȥ��@npc_124057���Ķ�һ������",
                                "\t������Ž��������֮ǰ�����ѹ���������������̫��ɽ��̩ɽɽ´�����ص����Ͷ������Ʊ������Ѿã������ھ���ͼ�ҵ��������ء���������������Ĵ���Ҳ������ȻӦ���Ҵ�Ԫ���У�����������ί����ǰȥ������Щ�����ͣ�",
                                "@npc_124057�������Ƿǳ��򵥣��ر��߶�ġ�"
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- ���һ����˰
--function x203794_FinishTax( sceneId, selfId)
--    if IsHaveQuest( sceneId, selfId, x203794_g_MissionId) <= 0 then
--        return
--    end
--
--    local misIndex = GetQuestIndexByID( sceneId, selfId, x203794_g_MissionId)
--    SetQuestByIndex( sceneId, selfId, misIndex, x203794_g_MP_Tax, 1)
--
--    x203794_ProcQuestLogRefresh( sceneId, selfId, x203794_g_MissionId)
--end

-- ���һ������
--function x203794_FinishHunt( sceneId, selfId)
--    if IsHaveQuest( sceneId, selfId, x203794_g_MissionId) <= 0 then
--        return
--    end
--
--    local misIndex = GetQuestIndexByID( sceneId, selfId, x203794_g_MissionId)
--    SetQuestByIndex( sceneId, selfId, misIndex, x203794_g_MP_Hunt, 1)
--
--    x203794_ProcQuestLogRefresh( sceneId, selfId, x203794_g_MissionId)
--end

-- ���һ�ֵ�����
function x203794_FinishDaobaoke( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x203794_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x203794_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x203794_g_MP_Daobaoke, 1)

    x203794_ProcQuestLogRefresh( sceneId, selfId, x203794_g_MissionId)
end
