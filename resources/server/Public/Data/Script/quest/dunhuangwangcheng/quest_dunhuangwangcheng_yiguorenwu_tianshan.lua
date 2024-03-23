--��������--�����������һ��

--MisDescBegin
x256269_g_ScriptId = 256269
x256269_g_MissionIdPre = 2625
x256269_g_MissionId = 2609
x256269_g_LevelLess	= 40
x256269_g_MissionIdNext = -1
x256269_g_Name	={}
x256269_g_ExtTarget={{type=20,n=1,target="@npc_28816"},{type=20,n=1,target="@npc_28817"},{type=20,n=1,target="@npc_28818"},{type=20,n=1,target="@npc_28819"},}
x256269_g_MissionName="�����ˡ�����ʹ��"
x256269_g_MissionInfo="\t�ҵ���ܾ��ˣ���������������Ϊ���ˣ�Ӧ�ÿ�ʼΪ���Ҿ�һ�����ˡ�\n\t�ҵ�@npc_128502��@npc_128503��@npc_128504��@npc_128505�����������������������÷��Ľ�����"  --��������
x256269_g_MissionTarget=""		
x256269_g_MissionCompleted="\t���Ϊ��Ч�����£������ҵȳ���Ӧ��֮��\n\t�ǵ�ÿ�춼ȥ��������������񣬳�����ջ�ǵ��㣬��Ľ���Ҳ�����١�"					--�������npc˵���Ļ�
x256269_g_ContinueInfo="\tʧ�ܲ����£����µ������Դ�ɥʧ��־��"
x256269_g_MissionHelp =	""
x256269_g_DemandItem ={}
x256269_g_ExpBonus = 55000
x256269_g_BonusMoney1 =5000
x256269_g_BonusMoney2 =0
x256269_g_BonusMoney3 =0
x256269_g_BonusMoney4 =0
x256269_g_BonusMoney5 =200
x256269_g_BonusMoney6 =0
x256269_g_BonusItem	=	{}
x256269_g_BonusChoiceItem ={}
x256269_g_NpcGUID ={{ guid = 128552, name = "��������"} }
--MisDescEnd
--**********************************
-- �����ɱ��ɱ��
x256269_g_MP_cisha  = 1
-- ������ɱ��
x256269_g_MP_duoqi   = 2
-- ������ɱ��
x256269_g_MP_chujian  = 3
-- �鱨��ɱ��
x256269_g_MP_qingbao  = 4
-- ���ȼ�
x256269_g_MaxLevel   = 55

function x256269_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

    local level = GetLevel(sceneId, selfId)
	if level < x256269_g_LevelLess or level >= x256269_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x256269_g_MissionId) > 0 then
		return 
	end
	
  if IsQuestHaveDone(sceneId, selfId, x256269_g_MissionIdPre)> 0 then 
	if IsHaveQuest(sceneId,selfId, x256269_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256269_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256269_g_MissionId, state, -1 )
	end
	end
end

function x256269_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x256269_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x256269_g_ExpBonus )
    end
    if x256269_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x256269_g_BonusMoney1 )
    end
    if x256269_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x256269_g_BonusMoney2 )
    end
    if x256269_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x256269_g_BonusMoney3 )
    end
    if x256269_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x256269_g_BonusMoney4 )
    end
    if x256269_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x256269_g_BonusMoney5 )
    end
    if x256269_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x256269_g_BonusMoney6 )
    end
    for i, item in x256269_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x256269_g_BonusChoiceItem do
       AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x256269_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256269_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x256269_g_MissionId) > 0 then
        if x256269_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256269_g_MissionName)
            AddQuestText(sceneId,x256269_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x256269_g_ScriptId, x256269_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256269_g_MissionName)
            AddQuestText(sceneId,x256269_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x256269_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256269_g_ScriptId, x256269_g_MissionId);
        end
    elseif x256269_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x256269_g_MissionName)
        AddQuestText(sceneId,x256269_g_MissionInfo)
        AddQuestText( sceneId,"#Y����Ŀ�꣺")
        AddQuestText( sceneId,"�����������")
        for i, item in x256269_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x256269_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#GС��ʾ:#W")
            AddQuestText(sceneId,x256269_g_MissionHelp )
        end
        x256269_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x256269_g_ScriptId, x256269_g_MissionId);
    end
end

function x256269_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x256269_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256269_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

function x256269_OnYinDaoCompleted( sceneId, selfId, nMode)   
	if nMode==nil then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x256269_g_MissionId ) == 0 then
		return
	end

	local misIndex = GetQuestIndexByID(sceneId,selfId,x256269_g_MissionId)  

	local n1 = GetQuestParam( sceneId, selfId, misIndex, 0 )	
	local n2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
	local n3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
	local n4 = GetQuestParam( sceneId, selfId, misIndex, 3 )                                                

    if nMode ==0 then 
   		SetQuestByIndex(sceneId,selfId,misIndex,0,1)

   		if n2==1 and n3==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==1 then 
   		SetQuestByIndex(sceneId,selfId,misIndex,1,1)
   		if n1==1 and n3==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==2 then	
   		SetQuestByIndex(sceneId,selfId,misIndex,2,1)
   		if n1==1 and n2==1 and n4==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	elseif nMode==3 then 
   		SetQuestByIndex(sceneId,selfId,misIndex,3,1)
   		if n1==1 and n2==1 and n3==1 then
   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
   		end
   	end
end

function x256269_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x256269_g_MissionId) > 0 then
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
    local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256269_g_MissionId  )
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


    if x256269_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x256269_g_MissionId, x256269_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x256269_g_MissionId)                                                  
            x256269_Msg2toplayer( sceneId, selfId,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256269_g_MP_cisha,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256269_g_MP_duoqi,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256269_g_MP_chujian,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256269_g_MP_qingbao,0)
            x256269_ProcQuestLogRefresh( sceneId, selfId, x256269_g_MissionId)
        end
    end                                                                    
end

function x256269_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x256269_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x256269_g_MissionId)
    x256269_Msg2toplayer( sceneId, selfId, 1)
end

function x256269_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256269_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end
    for j, item in x256269_g_BonusChoiceItem do
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

function x256269_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256269_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256269_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û�дﵽ���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256269_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�����ռ䲻�㣬�������������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x256269_g_MissionId) > 0 then
        x256269_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x256269_g_MissionId)
        x256269_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x256269_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x256269_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
       	--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256269_g_MissionIdNext )	
end

function x256269_GetBonus( sceneId, selfId,NpcID)
	if x256269_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x256269_g_ExpBonus);
  	end
	if x256269_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256269_g_BonusMoney1)
	end
    if x256269_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256269_g_BonusMoney2)
    end
    if x256269_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x256269_g_BonusMoney3)
    end
    if x256269_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x256269_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x256269_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x256269_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x256269_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x256269_g_BonusMoney6)
    end
end

function x256269_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "������������"..x256269_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x256269_g_MissionName.."��", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "������������"..x256269_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x256269_g_MissionName.."��", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "�����������"..x256269_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "�����������"..x256269_g_MissionName.."��", 0, 3)      
        if x256269_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256269_g_ExpBonus.."#Y�Ľ���", 0, 2)
        end
        if x256269_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256269_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
        end
        if x256269_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256269_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
        end
        if x256269_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��"..x256269_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
        end
        if x256269_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256269_g_BonusMoney4.."#Y�Ľ���", 0, 2)
        end
        if x256269_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256269_g_BonusMoney5.."#Y�Ľ���", 0, 2)
        end
        if x256269_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256269_g_BonusMoney6.."#Y�Ľ���", 0, 2)
        end
    end
end

function x256269_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x256269_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256269_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x256269_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256269_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x256269_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256269_g_MissionId) < 1 then
        return
    end

    -- �������
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256269_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256269_g_MP_duoqi, 1)
    x256269_ProcQuestLogRefresh( sceneId, selfId, x256269_g_MissionId)
end

function x256269_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x256269_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x256269_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x256269_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x256269_g_MissionId, state, -1 )
    end
end

function x256269_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256269_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256269_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256269_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256269_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256269_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256269_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    local cisha= GetQuestParam( sceneId, selfId, misIndex, x256269_g_MP_cisha)
    local duoqi = GetQuestParam( sceneId, selfId, misIndex, x256269_g_MP_duoqi)
    local chujian = GetQuestParam( sceneId, selfId, misIndex, x256269_g_MP_chujian)
    local qingbao= GetQuestParam( sceneId, selfId, misIndex, x256269_g_MP_qingbao)
    local strTarget = format( "�ر�@npc_%d", x256269_g_NpcGUID[1].guid)

    if cisha== 1 and duoqi == 1 and chujian == 1 and qingbao== 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        if cisha== 0 or duoqi == 0 or chujian == 0 or qingbao == 0 then
          strTarget = "  #W�������\n"
        end
         if cisha== 0 then
            strTarget = strTarget.."  #W���һ��@npc_28819(0/1)\n"
        else
            strTarget = strTarget.."  #G���һ��@npc_28819(1/1)\n"
        end
        if duoqi == 0 then
            strTarget = strTarget.."  #W���һ��@npc_28816(0/1)\n"
        else
            strTarget = strTarget.."  #G���һ��@npc_28816(1/1)\n"
        end
        if chujian == 0 then
            strTarget = strTarget.."  #W���һ��@npc_28817(0/1)\n"
        else
            strTarget = strTarget.."  #G���һ��@npc_28817(1/1)\n"
        end
        if qingbao== 0 then
            strTarget = strTarget.."  #W���һ��@npc_28818(0/1)"
        else
            strTarget = strTarget.."  #G���һ��@npc_28818(1/1)"
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x256269_g_MissionName,          -- ��������
                                strTarget,
                                "",                             --����NPC
                                "�ҵ�@npc_128502��@npc_128503��@npc_128504��@npc_128505�������������������",
                                "\t�ҵ���ܾ��ˣ���������������Ϊ���ˣ�Ӧ�ÿ�ʼΪ���Ҿ�һ�����ˡ�\n\t�ҵ�@npc_128502��@npc_128503��@npc_128504��@npc_128505�����������������������÷��Ľ�����",
                                "��������ǻر��߶�����񣬵���Ҫע�ⰲȫ��"
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- ��ɴ�ɱ
function x256269_Finishcisha( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256269_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256269_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256269_g_MP_cisha, 1)

    x256269_ProcQuestLogRefresh( sceneId, selfId, x256269_g_MissionId)
end

-- ��ɶ���
function x256269_Finishduoqi( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256269_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256269_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256269_g_MP_duoqi, 1)

    x256269_ProcQuestLogRefresh( sceneId, selfId, x256269_g_MissionId)
end

-- ��ɳ���
function x256269_Finishchujian( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256269_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256269_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256269_g_MP_chujian, 1)

    x256269_ProcQuestLogRefresh( sceneId, selfId, x256269_g_MissionId)
end
-- ����鱨
function x256269_Finishqingbao( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256269_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256269_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256269_g_MP_qingbao, 1)

    x256269_ProcQuestLogRefresh( sceneId, selfId, x256269_g_MissionId)
end