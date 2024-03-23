--��������--�����������Ϸ���Ĵ�����������������±����һ��

--MisDescBegin
x256225_g_ScriptId = 256225
--x256225_g_MissionIdPre ={67,69,70,71}
x256225_g_MissionId = 3112
x256225_g_LevelLess	= 40 
x256225_g_MissionIdNext = -1
x256225_g_Name	={}
x256225_g_ExtTarget={{type=20,n=1,target="���һ��@npc_28832"},{type=20,n=1,target="���һ��@npc_28833"},{type=20,n=1,target="���һ��@npc_28834"},{type=20,n=1,target="���һ��@npc_28835"},}
x256225_g_MissionName="�����ˡ��󶼵��ջ�"
x256225_g_MissionInfo="\t�����ķ����ͻ��֮�أ�ÿ�춼�кܶ��·����������ȥ@npc_139084��@npc_139115��@npc_139083��@npc_139116�������￴������Щ��������֮�ˣ������������ջ��Ȼ���"  --��������
x256225_g_MissionTarget=""		
x256225_g_MissionCompleted="\t����������ʶ����Щ������ʿ�����ض�������������\n\t��û��ƭ��ɣ����ǵĽ���������Ӧ�ú����⣬ÿ�쳣ȥ�����������߶������ջ�ġ�"					--�������npc˵���Ļ�
x256225_g_ContinueInfo="\t��̫�ļ������¾�Ҫÿһ�����ļ�ʵ���������۲�Ҫ����Ŭһ�����ͻ���ɵġ�"
x256225_g_MissionHelp =	""
x256225_g_DemandItem ={}
x256225_g_BonusMoney1 =8000
x256225_g_BonusMoney2 =0
x256225_g_BonusMoney3 =0
x256225_g_BonusMoney4 =0
x256225_g_BonusMoney5 =500
x256225_g_BonusMoney6 =0
x256225_g_BonusItem	=	{{item=11050002,n=3},{item=11000201,n=3},}
x256225_g_BonusChoiceItem ={}
x256225_g_ExpBonus = 30000
x256225_g_NpcGUID ={{ guid = 140417, name = "������"} }
--MisDescEnd
--**********************************
-- ��˰��ɱ��
x256225_g_MP_douxi   = 1
-- ������ɱ��
x256225_g_MP_fawang  = 2
-- ������ɱ��
x256225_g_MP_caishen  = 3
-- ������ɱ��
x256225_g_MP_biwu   = 4
-- ���ȼ�
x256225_g_MaxLevel   = 160

function x256225_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256225_g_LevelLess or level >= x256225_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x256225_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256225_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256225_g_MissionId, state, -1 )
	end
end

function x256225_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x256225_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x256225_g_ExpBonus )
    end
    if x256225_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x256225_g_BonusMoney1 )
    end
    if x256225_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x256225_g_BonusMoney2 )
    end
    if x256225_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x256225_g_BonusMoney3 )
    end
    if x256225_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x256225_g_BonusMoney4 )
    end
    if x256225_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x256225_g_BonusMoney5 )
    end
    if x256225_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x256225_g_BonusMoney6 )
    end
    for i, item in x256225_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x256225_g_BonusChoiceItem do
        AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x256225_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256225_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) > 0 then
        if x256225_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256225_g_MissionName)
            AddQuestText(sceneId,x256225_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x256225_g_ScriptId, x256225_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256225_g_MissionName)
            AddQuestText(sceneId,x256225_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x256225_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256225_g_ScriptId, x256225_g_MissionId);
        end
    elseif x256225_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x256225_g_MissionName)
        AddQuestText(sceneId,x256225_g_MissionInfo)
        AddQuestText( sceneId,"#Y����Ŀ�꣺")
        for i, item in x256225_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x256225_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#GС��ʾ:#W")
            AddQuestText(sceneId,x256225_g_MissionHelp )
        end
        x256225_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x256225_g_ScriptId, x256225_g_MissionId);
    end
end

function x256225_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x256225_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256225_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

function x256225_OnYinDaoCompleted( sceneId, selfId, nMode)   
	if nMode==nil then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x256225_g_MissionId ) == 0 then
		return
	end

	local misIndex = GetQuestIndexByID(sceneId,selfId,x256225_g_MissionId)  

	local n1 = GetQuestParam( sceneId, selfId, misIndex, 0 )	
	local n2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local n3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local n4 = GetQuestParam( sceneId, selfId, misIndex, 3 )                                                

    if nMode ==0 then --����
   		SetQuestByIndex(sceneId,selfId,misIndex,0,1)

   		if n2==1 and n3==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==1 then --��˰
   		SetQuestByIndex(sceneId,selfId,misIndex,1,1)
   		if n1==1 and n3==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==2 then	-- ����
   		SetQuestByIndex(sceneId,selfId,misIndex,2,1)
   		if n1==1 and n2==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==3 then --��˰
   		SetQuestByIndex(sceneId,selfId,misIndex,3,1)
   		if n1==1 and n2==1 and n3==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	end
end

function x256225_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x256225_g_MissionId) > 0 then
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
    local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3	= GetFrontQuestIdNM( sceneId, selfId,x256225_g_MissionId  )
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


    if x256225_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x256225_g_MissionId, x256225_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x256225_g_MissionId)                                                  
            x256225_Msg2toplayer( sceneId, selfId,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256225_g_MP_douxi,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256225_g_MP_fawang,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256225_g_MP_caishen,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256225_g_MP_biwu,0)
            x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
        end
    end                                                                    
end

function x256225_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x256225_g_MissionId)
    x256225_Msg2toplayer( sceneId, selfId, 1)
end

function x256225_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256225_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end
    for j, item in x256225_g_BonusChoiceItem do
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

function x256225_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256225_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û�дﵽ���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256225_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�����ռ䲻�㣬�������������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x256225_g_MissionId) > 0 then
        x256225_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x256225_g_MissionId)
        x256225_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x256225_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x256225_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
        AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256225_g_MissionIdNext )	
end

function x256225_GetBonus( sceneId, selfId,NpcID)
	if x256225_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x256225_g_ExpBonus);
  	end
	if x256225_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256225_g_BonusMoney1)
	end
    if x256225_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256225_g_BonusMoney2)
    end
    if x256225_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x256225_g_BonusMoney3)
    end
    if x256225_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x256225_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x256225_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x256225_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x256225_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x256225_g_BonusMoney6)
    end
end

function x256225_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "������������"..x256225_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x256225_g_MissionName.."��", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "������������"..x256225_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x256225_g_MissionName.."��", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "�����������"..x256225_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "�����������"..x256225_g_MissionName.."��", 0, 3)
        if x256225_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256225_g_ExpBonus.."#Y�Ľ���", 0, 2)
        end
        if x256225_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256225_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
        end
        if x256225_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256225_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
        end
        if x256225_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��"..x256225_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
        end
        if x256225_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256225_g_BonusMoney4.."#Y�Ľ���", 0, 2)
        end
        if x256225_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256225_g_BonusMoney5.."#Y�Ľ���", 0, 2)
        end
        if x256225_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256225_g_BonusMoney6.."#Y�Ľ���", 0, 2)
        end
    end
end

function x256225_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x256225_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256225_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x256225_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256225_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x256225_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) < 1 then
        return
    end

    -- �������
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_fawang, 1)
    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end

function x256225_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x256225_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x256225_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x256225_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x256225_g_MissionId, state, -1 )
    end
end

function x256225_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	--return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256225_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	--return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256225_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256225_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256225_OnProcOver( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256225_OpenCheck( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256225_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end
    
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    local douxi = GetQuestParam( sceneId, selfId, misIndex, x256225_g_MP_douxi)
    local fawang= GetQuestParam( sceneId, selfId, misIndex, x256225_g_MP_fawang)
    local caishen = GetQuestParam( sceneId, selfId, misIndex, x256225_g_MP_caishen)
    local biwu= GetQuestParam( sceneId, selfId, misIndex, x256225_g_MP_biwu)
    local strTarget = format( "�����Ѿ���ɣ���ر�@npc_%d", x256225_g_NpcGUID[1].guid)

    if douxi == 1 and fawang== 1 and caishen == 1 and biwu== 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        if douxi == 0 then
            strTarget = "  #W���һ��@npc_28832(0/1)\n"
        else
            strTarget = "  #G���һ��@npc_28832(1/1)\n"
        end
        if fawang== 0 then
            strTarget = strTarget.."  #W���һ��@npc_28833(0/1)\n"
        else
            strTarget = strTarget.."  #G���һ��@npc_28833(1/1)\n"
        end
        if caishen == 0 then
            strTarget = strTarget.."  #W���һ��@npc_28834(0/1)\n"
        else
            strTarget = strTarget.."  #G���һ��@npc_28834(1/1)\n"
        end
        if biwu== 0 then
            strTarget = strTarget.."  #W���һ��@npc_28835(0/1)"
        else
            strTarget = strTarget.."  #G���һ��@npc_28835(1/1)"
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x256225_g_MissionName,          -- ��������
                                strTarget,
                                "",                             --����NPC
                                "ȥ@npc_139084��@npc_139115��@npc_139083��@npc_139116������ɵ����ǷԸ������顣",
                                "\t�����ķ����ͻ��֮�أ�ÿ�춼�кܶ��·����������ȥ@npc_139084��@npc_139115��@npc_139083��@npc_139116�������￴������Щ��������֮�ˣ������������ջ��Ȼ���",
                                "@npc_139084��@npc_139115��@npc_139083��@npc_139116Ҫ����������ǻر����"
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- ���һ����˰
function x256225_Finishdouxi( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_douxi, 1)

    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end

-- ���һ������
function x256225_Finishfawang( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_fawang, 1)

    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end

-- ���һ������
function x256225_Finishcaishen( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_caishen, 1)

    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end
-- ���һ������
function x256225_Finishbiwu( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256225_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256225_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256225_g_MP_biwu, 1)

    x256225_ProcQuestLogRefresh( sceneId, selfId, x256225_g_MissionId)
end