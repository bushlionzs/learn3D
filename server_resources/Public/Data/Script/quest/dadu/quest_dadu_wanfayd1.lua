--��������--����������������������գ��������Ѹ�һ��

--MisDescBegin
x256224_g_ScriptId = 256224
--x256224_g_MissionIdPre ={67,69,70,71}
x256224_g_MissionId = 3111
x256224_g_LevelLess	= 40
x256224_g_MissionIdNext = -1
x256224_g_Name	={}
x256224_g_ExtTarget={{type=20,n=1,target="���@npc_28828"},{type=20,n=1,target="���@npc_28829"},{type=20,n=1,target="���@npc_28830"},{type=20,n=1,target="����@npc_28831"},}
x256224_g_MissionName="�����ˡ��󶼼��껪"
x256224_g_MissionInfo="\t���ǵķ����������ǿɱȣ������洦���ڡ������ȥ@npc_139129��@npc_139133��@npc_139100��@npc_139104�������￴�����󶼼��껪һϵ����Ȥ�������ڵȴ����㡣"  --��������
x256224_g_MissionTarget=""		
x256224_g_MissionCompleted="\t�����˸߲��ҵ������Ͽ�����껪����������ĺ���졣\n\t�ǵ�ÿ�춼ȥ�������￴��������Ȥ֮������кܴ���ջ�"					--�������npc˵���Ļ�
x256224_g_ContinueInfo="\t��ô��ü�����ģ��󶼵ļ��껪��������"
x256224_g_MissionHelp =	""
x256224_g_DemandItem ={}
x256224_g_ExpBonus = 80000
x256224_g_BonusMoney1 =15000
x256224_g_BonusMoney2 =0
x256224_g_BonusMoney3 =0
x256224_g_BonusMoney4 =0
x256224_g_BonusMoney5 =200
x256224_g_BonusMoney6 =0
x256224_g_BonusItem	=	{{item=12030107,n=1},{item=12030011,n=20}}
x256224_g_BonusChoiceItem ={}
x256224_g_NpcGUID ={{ guid = 140417, name = "������"} }
--MisDescEnd
--**********************************
-- ����������ɱ��
x256224_g_MP_yizhe   = 1
-- ������ɱ��
x256224_g_MP_dengmi   = 2
-- ������ɱ��
x256224_g_MP_tiesan  = 3
-- ���������ɱ��
x256224_g_MP_wuting  = 4
-- ���ȼ�
x256224_g_MaxLevel   = 55

function x256224_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256224_g_LevelLess or level >= x256224_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x256224_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x256224_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256224_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256224_g_MissionId, state, -1 )
	end
end

function x256224_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x256224_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x256224_g_ExpBonus )
    end
    if x256224_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x256224_g_BonusMoney1 )
    end
    if x256224_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x256224_g_BonusMoney2 )
    end
    if x256224_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x256224_g_BonusMoney3 )
    end
    if x256224_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x256224_g_BonusMoney4 )
    end
    if x256224_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x256224_g_BonusMoney5 )
    end
    if x256224_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x256224_g_BonusMoney6 )
    end
    for i, item in x256224_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x256224_g_BonusChoiceItem do
        AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x256224_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256224_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x256224_g_MissionId) > 0 then
        if x256224_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256224_g_MissionName)
            AddQuestText(sceneId,x256224_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x256224_g_ScriptId, x256224_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256224_g_MissionName)
            AddQuestText(sceneId,x256224_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x256224_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256224_g_ScriptId, x256224_g_MissionId);
        end
    elseif x256224_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x256224_g_MissionName)
        AddQuestText(sceneId,x256224_g_MissionInfo)
        AddQuestText( sceneId,"#Y����Ŀ�꣺")
        for i, item in x256224_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x256224_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#GС��ʾ:#W")
            AddQuestText(sceneId,x256224_g_MissionHelp )
        end
        x256224_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x256224_g_ScriptId, x256224_g_MissionId);
    end
end

function x256224_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x256224_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256224_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

function x256224_OnYinDaoCompleted( sceneId, selfId, nMode)   
	if nMode==nil then
		return
	end

	if IsHaveQuestNM( sceneId, selfId, x256224_g_MissionId ) == 0 then
		return
	end

	local misIndex = GetQuestIndexByID(sceneId,selfId,x256224_g_MissionId)  

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

function x256224_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x256224_g_MissionId) > 0 then
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
    local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256224_g_MissionId  )
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

    if x256224_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x256224_g_MissionId, x256224_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x256224_g_MissionId)                                                  
            x256224_Msg2toplayer( sceneId, selfId,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256224_g_MP_yizhe,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256224_g_MP_dengmi,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256224_g_MP_tiesan,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256224_g_MP_wuting,0)
            x256224_ProcQuestLogRefresh( sceneId, selfId, x256224_g_MissionId)
        end
    end                                                                    
end

function x256224_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x256224_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x256224_g_MissionId)
    x256224_Msg2toplayer( sceneId, selfId, 1)
end

function x256224_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ�������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256224_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
    end
    for j, item in x256224_g_BonusChoiceItem do
        if item.item == selectRadioId then
            AddBindItem( sceneId, item.item, item.n )
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

function x256224_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256224_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256224_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û�дﵽ���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256224_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�����ռ䲻�㣬��������������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x256224_g_MissionId) > 0 then
        x256224_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x256224_g_MissionId)
        x256224_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x256224_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x256224_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
       	AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256224_g_MissionIdNext )	
end

function x256224_GetBonus( sceneId, selfId,NpcID)
	if x256224_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x256224_g_ExpBonus);
  	end
	if x256224_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256224_g_BonusMoney1)
	end
    if x256224_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256224_g_BonusMoney2)
    end
    if x256224_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x256224_g_BonusMoney3)
    end
    if x256224_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x256224_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x256224_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x256224_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x256224_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x256224_g_BonusMoney6)
    end
end

function x256224_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "������������"..x256224_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x256224_g_MissionName.."��", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "������������"..x256224_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x256224_g_MissionName.."��", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "�����������"..x256224_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "�����������"..x256224_g_MissionName.."��", 0, 3)      
        if x256224_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256224_g_ExpBonus.."#Y�Ľ���", 0, 2)
        end
        if x256224_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256224_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
        end
        if x256224_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256224_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
        end
        if x256224_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��"..x256224_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
        end
        if x256224_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256224_g_BonusMoney4.."#Y�Ľ���", 0, 2)
        end
        if x256224_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256224_g_BonusMoney5.."#Y�Ľ���", 0, 2)
        end
        if x256224_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256224_g_BonusMoney6.."#Y�Ľ���", 0, 2)
        end
    end
end

function x256224_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x256224_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256224_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x256224_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256224_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

function x256224_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256224_g_MissionId) < 1 then
        return
    end

    -- �������
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256224_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256224_g_MP_dengmi, 1)
    x256224_ProcQuestLogRefresh( sceneId, selfId, x256224_g_MissionId)
end

function x256224_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x256224_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x256224_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x256224_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x256224_g_MissionId, state, -1 )
    end
end

function x256224_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	--return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256224_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	--return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256224_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256224_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256224_OnProcOver( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256224_OpenCheck( sceneId, selfId, targetId )
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256224_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    if IsHaveQuest( sceneId, selfId, x256224_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256224_g_MissionId)
    local yizhe = GetQuestParam( sceneId, selfId, misIndex, x256224_g_MP_yizhe)
    local dengmi = GetQuestParam( sceneId, selfId, misIndex, x256224_g_MP_dengmi)
    local tiesan = GetQuestParam( sceneId, selfId, misIndex, x256224_g_MP_tiesan)
    local wuting= GetQuestParam( sceneId, selfId, misIndex, x256224_g_MP_wuting)
    local strTarget = format( "�����Ѿ���ɣ���ر�@npc_%d", x256224_g_NpcGUID[1].guid)

    if yizhe == 1 and dengmi == 1 and tiesan == 1 and wuting== 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        if yizhe == 0 then
            strTarget = "  #W���@npc_28828(0/1)\n"
        else
            strTarget = "  #G���@npc_28828(1/1)\n"
        end
        if dengmi == 0 then
            strTarget = strTarget.."  #W���@npc_28829(0/1)\n"
        else
            strTarget = strTarget.."  #G���@npc_28829(1/1)\n"
        end
        if tiesan == 0 then
            strTarget = strTarget.."  #W���@npc_28830(0/1)\n"
        else
            strTarget = strTarget.."  #G���@npc_28830(1/1)\n"
        end
        if wuting== 0 then
            strTarget = strTarget.."  #W����@npc_28831(0/1)"
        else
            strTarget = strTarget.."  #G����@npc_28831(1/1)"
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x256224_g_MissionName,          -- ��������
                                strTarget,
                                "",                             --����NPC
                                "ȥ@npc_139129��@npc_139133��@npc_139100��@npc_139104������ɴ󶼼��껪�ĸ�������",
                                "\t���ǵķ���������ǿɱȣ������洦���ڡ������ȥ@npc_139129��@npc_139133��@npc_139100��@npc_139104�������￴�����󶼼��껪һϵ����Ȥ�������ڵȴ����㡣",
                                "@npc_139129��@npc_139133��@npc_139100��@npc_139104�Ĵ󶼼��껪���񶼷ǳ���Ȥ����ɺ�����кܶ��ջ�"
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- ���һ����˰
function x256224_Finishyizhe( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256224_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256224_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256224_g_MP_yizhe, 1)

    x256224_ProcQuestLogRefresh( sceneId, selfId, x256224_g_MissionId)
end

-- ���һ������
function x256224_Finishdengmi( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256224_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256224_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256224_g_MP_dengmi, 1)

    x256224_ProcQuestLogRefresh( sceneId, selfId, x256224_g_MissionId)
end

-- ���һ������
function x256224_Finishtiesan( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256224_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256224_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256224_g_MP_tiesan, 1)

    x256224_ProcQuestLogRefresh( sceneId, selfId, x256224_g_MissionId)
end
-- ���һ������
function x256224_Finishwuting( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256224_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256224_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256224_g_MP_wuting, 1)

    x256224_ProcQuestLogRefresh( sceneId, selfId, x256224_g_MissionId)
end