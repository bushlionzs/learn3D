--��������--��ɰ�������һ��

--MisDescBegin
x256266_g_ScriptId = 256266
x256266_g_MissionIdPre = 2614
x256266_g_MissionId = 2606
x256266_g_LevelLess	= 42
x256266_g_MissionIdNext = 4064
x256266_g_Name	={}
x256266_g_ExtTarget={{type=20,n=1,target="�������"},{type=20,n=1,target="��ᰵս"},{type=20,n=1,target="���ͼ��"},{type=20,n=1,target="����ħ"},}
x256266_g_MissionName="�����ˡ��˰�֮��"
x256266_g_MissionInfo="\t��ã����װ������ѣ�����Ը�ļ��������������İ�ᡣ\n\tΪ�������ǵİ��һ�����ǿ�������������ֵ�Ҫ������ɰ��еİ�����ޣ���ᰵս�����ͼ�ڣ�����ħ��������ɺ����õ��ܷ��Ļر���"  --��������
x256266_g_MissionTarget=""			
x256266_g_MissionCompleted="\t���е��ֵܶ���ı���ʮ�����⣬ϣ�����Ժ��ٽ�������"					--�������npc˵���Ļ�
x256266_g_ContinueInfo="\t�����������Ҫ�Ͱ����ֵܺ�����ɵģ��㲻Ҫ̫�ļ���"
x256266_g_MissionHelp =	""
x256266_g_DemandItem ={}
x256266_g_BonusMoney1 =0
x256266_g_BonusMoney2 =0
x256266_g_BonusMoney3 =0
x256266_g_BonusMoney4 =0
x256266_g_BonusMoney5 =0
x256266_g_BonusMoney6 =0
x256266_g_BonusMoney8 =200
x256266_g_BonusItem	=	{}
x256266_g_BonusChoiceItem ={}
x256266_g_ExpBonus = 450000
x256266_g_NpcGUID ={{ guid = 129020, name = "������񷢲���"} }
--MisDescEnd
--**********************************
-- �������
--x256266_g_MP_nz   = 1
-- �������
x256266_g_MP_hss   = 1
-- ��ᰵս
x256266_g_MP_anzhan  = 2
-- �ռ���ľ
x256266_g_MP_danmu  = 3
-- ���˹ȳ���
x256266_g_MP_chuyao   = 4
-- ���ȼ�
x256266_g_MaxLevel   = 160
function x256266_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if GetGuildID( sceneId, selfId ) == -1 then
		--���ڰ����
		return
	end
    local level = GetLevel(sceneId, selfId)
	if level < x256266_g_LevelLess or level >= x256266_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x256266_g_MissionId) > 0 then
		return 
	end

  if IsQuestHaveDone(sceneId, selfId, x256266_g_MissionIdPre)> 0 then 	
	if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256266_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256266_g_MissionId, state, -1 )
	end
	end
end

function x256266_DispatchMissionInfo( sceneId, selfId, NPCId )
    if x256266_g_ExpBonus> 0 then
        AddQuestExpBonus(sceneId, x256266_g_ExpBonus )
    end
    if x256266_g_BonusMoney1 > 0 then
        AddQuestMoneyBonus1(sceneId, x256266_g_BonusMoney1 )
    end
    if x256266_g_BonusMoney2 > 0 then
        AddQuestMoneyBonus2(sceneId, x256266_g_BonusMoney2 )
    end
    if x256266_g_BonusMoney3 > 0 then
        AddQuestMoneyBonus3(sceneId, x256266_g_BonusMoney3 )
    end
    if x256266_g_BonusMoney4 > 0 then
        AddQuestMoneyBonus4(sceneId, x256266_g_BonusMoney4 )
    end
    if x256266_g_BonusMoney5 > 0 then
        AddQuestMoneyBonus5(sceneId, x256266_g_BonusMoney5 )
    end
    if x256266_g_BonusMoney6 > 0 then
        AddQuestMoneyBonus6(sceneId, x256266_g_BonusMoney6 )
    end
    if x256266_g_BonusMoney8 > 0 then
		AddQuestMoneyBonus8(sceneId, x256266_g_BonusMoney8 )
	end
    for i, item in x256266_g_BonusItem do
        AddQuestItemBonus(sceneId, item.item, item.n)
    end
    for i, item in x256266_g_BonusChoiceItem do
        AddQuestRadioItemBonus(sceneId, item.item, item.n)
    end
end

function x256266_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256266_g_MissionId) > 0 then
		return
	end
	if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) > 0 then
        if x256266_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256266_g_MissionName)
            AddQuestText(sceneId,x256266_g_ContinueInfo)
            EndQuestEvent()
            DispatchQuestEventList(sceneId, selfId, NPCId, x256266_g_ScriptId, x256266_g_MissionId);
        else
            BeginQuestEvent(sceneId)
            AddQuestText(sceneId,"#Y"..x256266_g_MissionName)
            AddQuestText(sceneId,x256266_g_MissionCompleted)
            AddQuestText(sceneId," ")
            x256266_DispatchMissionInfo( sceneId, selfId, NPCId )
            EndQuestEvent()
            DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256266_g_ScriptId, x256266_g_MissionId);
        end
    elseif x256266_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"#Y"..x256266_g_MissionName)
        AddQuestText(sceneId,x256266_g_MissionInfo)
        AddQuestText( sceneId,"#Y����Ŀ�꣺")
        AddQuestText( sceneId,"�ҵ�@npc_129020���:")
        for i, item in x256266_g_ExtTarget do
            AddQuestText( sceneId,item.target)
        end 
        if x256266_g_MissionHelp ~= "" then
            AddQuestText(sceneId,"\n#GС��ʾ:#W")
            AddQuestText(sceneId,x256266_g_MissionHelp )
        end
        x256266_DispatchMissionInfo( sceneId, selfId, NPCId )
        EndQuestEvent()
        DispatchQuestInfoNM(sceneId, selfId, NPCId, x256266_g_ScriptId, x256266_g_MissionId);
    end
end

function x256266_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x256266_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256266_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

--function x256266_OnYinDaoCompleted( sceneId, selfId, nMode)   
--	if nMode==nil then
--		return
--	end
--
--	if IsHaveQuestNM( sceneId, selfId, x256266_g_MissionId ) == 0 then
--		return
--	end
--
--	local misIndex = GetQuestIndexByID(sceneId,selfId,x256266_g_MissionId)  
--
--	--local n1 = GetQuestParam( sceneId, selfId, misIndex, 0 )	
--	local n2 = GetQuestParam( sceneId, selfId, misIndex, 1 )
--	local n3 = GetQuestParam( sceneId, selfId, misIndex, 2 )
--	local n4 = GetQuestParam( sceneId, selfId, misIndex, 3 ) 
--	local n5 = GetQuestParam( sceneId, selfId, misIndex, 4 )                                                    
--
--   -- if nMode ==0 then --����
--   		--SetQuestByIndex(sceneId,selfId,misIndex,0,1)
--
--   		--if n2==1 and n3==1 and n4==1 and n5==1 then
--   		--	SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   	--	end
--   	elseif nMode==1 then --��˰
--   		SetQuestByIndex(sceneId,selfId,misIndex,1,1)
--   		if n3==1 and n4==1 and n5==1 then
--   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   		end
--   	elseif nMode==2 then	-- ����
--   		SetQuestByIndex(sceneId,selfId,misIndex,2,1)
--   		if n2==1 and n4==1 and n5==1 then
--   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   		end
--   	elseif nMode==3 then --��˰
--   		SetQuestByIndex(sceneId,selfId,misIndex,3,1)
--   		if n2==1 and n3==1 and n5==1 then
--   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   		end
--   	elseif nMode==4 then --��˰
--   		SetQuestByIndex(sceneId,selfId,misIndex,4,1)
--   		if n2==1 and n3==1 and n4==1 then
--   			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
--   		end
--   	end
--end

function x256266_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
    if IsQuestHaveDone(sceneId, selfId, x256266_g_MissionId) > 0 then
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
	  local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256266_g_MissionId  )
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

    if x256266_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
        local retmiss = AddQuest( sceneId, selfId, x256266_g_MissionId, x256266_g_ScriptId, 0, 0, 0, 1)
        if retmiss ==0 then
            Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
            return 0
        else
            local misIndex = GetQuestIndexByID(sceneId,selfId,x256266_g_MissionId)                                                  
            x256266_Msg2toplayer( sceneId, selfId,0)
           -- SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_nz,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_hss,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_anzhan,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_danmu,0)
            SetQuestByIndex(sceneId,selfId,misIndex,x256266_g_MP_chuyao,0)
            x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
        end
    end                                                                    
end

function x256266_ProcQuestAbandon(sceneId, selfId, MissionId)
    if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) <= 0 then
        return 
    end
    DelQuest( sceneId, selfId, x256266_g_MissionId)
    x256266_Msg2toplayer( sceneId, selfId, 1)
end

function x256266_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256266_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
    end
    for j, item in x256266_g_BonusChoiceItem do
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

function x256266_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256266_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"��û�дﵽ���������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif x256266_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
        BeginQuestEvent(sceneId)
        AddQuestText(sceneId,"�����ռ䲻�㣬�������������")
        EndQuestEvent(sceneId)
        DispatchQuestTips(sceneId,selfId)
        return 0
	elseif DelQuest(sceneId, selfId, x256266_g_MissionId) > 0 then
        x256266_Msg2toplayer( sceneId, selfId,2)
        QuestCom(sceneId, selfId, x256266_g_MissionId)
        x256266_GetBonus( sceneId, selfId,NPCId)
        BeginAddItem(sceneId)
        for i, item in x256266_g_BonusItem do
            AddBindItem( sceneId, item.item, item.n )
        end
        for i, item in x256266_g_BonusChoiceItem do
            if item.item == selectRadioId then
                AddItem( sceneId, item.item, item.n )
            end
        end
        EndAddItem(sceneId,selfId)
       	--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256266_g_MissionIdNext )	
end

function x256266_GetBonus( sceneId, selfId,NpcID)
	if x256266_g_ExpBonus > 0 then
		AddExp(sceneId, selfId, x256266_g_ExpBonus);
  	end
	if x256266_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256266_g_BonusMoney1)
	end
    if x256266_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256266_g_BonusMoney2)
    end
    if x256266_g_BonusMoney3 > 0 then
        AddMoney( sceneId, selfId, 3, x256266_g_BonusMoney3)
    end
    if x256266_g_BonusMoney4 > 0 then
        local nRongYu = GetRongYu( sceneId, selfId )
        nRongYu = nRongYu + x256266_g_BonusMoney4
        SetRongYu( sceneId, selfId, nRongYu )
    end
    if x256266_g_BonusMoney5 > 0 then
        local nShengWang = GetShengWang( sceneId, selfId)
        nShengWang = nShengWang + x256266_g_BonusMoney5
        SetShengWang( sceneId, selfId, nShengWang )
    end
    if x256266_g_BonusMoney6 > 0 then
        AddHonor(sceneId,selfId,x256266_g_BonusMoney6)
    end
    if x256266_g_BonusMoney8 > 0 then
		AddGuildUserPoint(sceneId,selfId,x256266_g_BonusMoney8)	--���Ӱﹱ
		local BonusMoney8 = x256266_g_BonusMoney8
		local pointText = "#Y���#R�ﹱ"..BonusMoney8.."��#Y�Ľ���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, pointText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)			
  		Msg2Player(sceneId,selfId,pointText,8,2)
	end
end

function x256266_Msg2toplayer( sceneId, selfId,type)
    if type == 0 then
        Msg2Player(sceneId, selfId, "������������"..x256266_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x256266_g_MissionName.."��", 0, 3)
    elseif type == 1 then
        Msg2Player(sceneId, selfId, "������������"..x256266_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "������������"..x256266_g_MissionName.."��", 0, 3)
    elseif type == 2 then
        Msg2Player(sceneId, selfId, "�����������"..x256266_g_MissionName.."��", 0, 2)
        Msg2Player(sceneId, selfId, "�����������"..x256266_g_MissionName.."��", 0, 3)      
        if x256266_g_ExpBonus > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256266_g_ExpBonus.."#Y�Ľ���", 0, 2)
        end
        if x256266_g_BonusMoney1 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256266_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
        end
        if x256266_g_BonusMoney2 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256266_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
        end
        if x256266_g_BonusMoney3 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��"..x256266_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
        end
        if x256266_g_BonusMoney4 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256266_g_BonusMoney4.."#Y�Ľ���", 0, 2)
        end
        if x256266_g_BonusMoney5 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256266_g_BonusMoney5.."#Y�Ľ���", 0, 2)
        end
        if x256266_g_BonusMoney6 > 0 then
            Msg2Player(sceneId, selfId, "#Y���#R����"..x256266_g_BonusMoney6.."#Y�Ľ���", 0, 2)
        end
    end
end

function x256266_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end

function x256266_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256266_ProcTiming(sceneId, selfId, ScriptId, MissionId)
    CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
end

function x256266_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256266_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end

--function x256266_LevelUp( sceneId, selfId)
--    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) < 1 then
--        return
--    end
--
--    -- �������
--    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
--    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_hss, 1)
--    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
--end

function x256266_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x256266_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
    if IsHaveQuest(sceneId,selfId, x256266_g_MissionId) > 0 then
        local state = GetQuestStateNM(sceneId,selfId,npcId,x256266_g_MissionId)
        AddQuestTextNM( sceneId, selfId, npcId, x256266_g_MissionId, state, -1 )
    end
end

function x256266_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256266_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256266_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256266_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256266_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256266_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x256266_ProcQuestLogRefresh( sceneId, selfId, MissionId)
    local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
    --local nz = GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_nz)
    local hss = GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_hss)
    local anzhan = GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_anzhan)
    local danmu= GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_danmu)
    local chuyao= GetQuestParam( sceneId, selfId, misIndex, x256266_g_MP_chuyao)
    local strTarget = format( "�����Ѿ���ɣ���ر�@npc_%d", x256266_g_NpcGUID[1].guid)

    if hss == 1 and anzhan == 1 and danmu== 1 and chuyao== 1 then
        SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
        SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    else
        if hss== 0 or anzhan  == 0 or danmu == 0 or chuyao == 0 then      
           strTarget = "  #W�ҵ�@npc_129020���:\n"
        end
        if hss == 0 then
       
            strTarget =strTarget.."  #W�������(0/1)\n"
        else
            strTarget =strTarget.."  #G�������(1/1)\n"
        end
        if anzhan == 0 then
            strTarget = strTarget.."  #W��ᰵս(0/1)\n"
        else
            strTarget = strTarget.."  #G��ᰵս(1/1)\n"
        end
        if danmu== 0 then
            strTarget = strTarget.."  #W���ͼ��(0/1)\n"
        else
            strTarget = strTarget.."  #G���ͼ��(1/1)\n"
        end
         if chuyao== 0 then
            strTarget = strTarget.."  #W����ħ(0/1)"
        else
            strTarget = strTarget.."  #G����ħ(1/1)"
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                             -- ����
                                x256266_g_MissionName,          -- ��������
                                strTarget,
                                "",                             --����NPC
                                "�ҵ�@npc_129020��ɰ�����ޣ���ᰵս�����ͼ�ڣ�����ħ",
                                "\t��ã����װ������ѣ�����Ը�ļ��������������İ�ᡣ\n\tΪ�������ǵİ��һ�����ǿ�������������ֵ�Ҫ������ɰ��еİ�����ޣ���ᰵս�����ͼ�ڣ�����ħ��������ɺ����õ��ܷ��Ļر���",
                                "@npc_129020�������ǻر��߶�����񣬵���Ҫע�ⰲȫ��"
                                )
       	if x256266_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256266_g_ExpBonus )
		end
		if x256266_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256266_g_BonusMoney1 )
		end
		if x256266_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256266_g_BonusMoney2 )
		end
		if x256266_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256266_g_BonusMoney3 )
		end
		if x256266_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256266_g_BonusMoney4 )
		end
		if x256266_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256266_g_BonusMoney5 )
		end
		if x256266_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256266_g_BonusMoney6 )
		end
		if x256266_g_BonusMoney8 > 0 then
			AddQuestMoneyBonus8(sceneId, x256266_g_BonusMoney8 )
		end
		--if x256266_g_GuildExpBonus>0 then
		--	AddQuestGuildExpBonus(sceneId,x256266_g_GuildExpBonus)
		--end
		for i, item in x256266_g_BonusItem do
	   		AddQuestItemBonus(sceneId, item.item, item.n)
 		end
		for i, item in x256266_g_BonusChoiceItem do
    		AddQuestRadioItemBonus(sceneId, item.item, item.n)
  		end

	EndQuestEvent()
	DispatchQuestLogUpdate( sceneId, selfId, MissionId);
end

-- �������
--function x256266_Finishnz( sceneId, selfId)
--    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
--        return
--    end
--
--    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
--    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_nz, 1)
--
--    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
--end

-- ��ɰ������
function x256266_Finishhss( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_hss, 1)

    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
end

-- ��ɰ�ս
function x256266_Finishanzhan( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_anzhan, 1)

    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
end
-- ��ɺ�ľ
function x256266_Finishdanmu( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_danmu, 1)

    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
end
-- ��ɳ���
function x256266_Finishchuyao( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) <= 0 then
        return
    end

    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, x256266_g_MP_chuyao, 1)

    x256266_ProcQuestLogRefresh( sceneId, selfId, x256266_g_MissionId)
end

function x256266_LevelUp( sceneId, selfId)
    if IsHaveQuest( sceneId, selfId, x256266_g_MissionId) < 1 then
        return
    end

    -- ���ȼ�����65��ʱ�Զ��������
    if   GetLevel(sceneId, selfId) >= 65 then
    local misIndex = GetQuestIndexByID( sceneId, selfId, x256266_g_MissionId)
    SetQuestByIndex( sceneId, selfId, misIndex, 0, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 1, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 2, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 3, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 4, 1)
    SetQuestByIndex( sceneId, selfId, misIndex, 7, 1)
    end
end 