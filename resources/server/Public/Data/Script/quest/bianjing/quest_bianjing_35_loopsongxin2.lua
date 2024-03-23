--�����ߡ��ߴ��ʽ�

--MisDescBegin
x260001_g_ScriptId = 260001
x260001_g_MissionIdPre =-1
x260001_g_MissionId = 2117
x260001_g_LevelLess	= 	35 
x260001_g_MissionIdNext = 2116
x260001_g_Name	={}
x260001_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_129216"}}
x260001_g_MissionName="��ѭ����û������"
x260001_g_MissionInfo="\t�⼸��ûʲô���⣬�����ֶ࣬��������ʽ������ʲôʱ�����С�û�������⡱����"  --��������
x260001_g_MissionTarget=""		
x260001_g_MissionCompleted="\t��Щ�츽������̫�࣬�������ڵĶ������˰�·�ϡ���ȥ���߼�˼�ӣ��������������ԡ� "					--�������npc˵���Ļ�
x260001_g_ContinueInfo=""
x260001_g_MissionHelp =	""
x260001_g_DemandItem ={}
x260001_g_BonusMoney1 =0
x260001_g_BonusMoney2 =0
x260001_g_BonusMoney3 =0
x260001_g_BonusMoney4 =0
x260001_g_BonusMoney5 =0
x260001_g_BonusMoney6 =0
x260001_g_BonusItem	=	{}
x260001_g_BonusChoiceItem ={}
x260001_g_ExpBonus = 20
x260001_g_NpcGUID ={{ guid = 129216, name = "�����"} }
--MisDescEnd
--**********************************

function x260001_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x260001_g_MissionId) > 0 then
		return 
	end
	if GetLevel(sceneId, selfId)> 34 then
		if GetLevel(sceneId, selfId)< 46 then
			if IsHaveQuest(sceneId,selfId, x260001_g_MissionId) <= 0 then
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x260001_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x260001_g_MissionId, state, -1 )
			end
		end
	end
end

function x260001_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x260001_g_ExpBonus> 0 then
		local addexpture = x260001_g_ExpBonus*GetLevel(sceneId, selfId)
			AddQuestExpBonus(sceneId, addexpture )
		end
		if x260001_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x260001_g_BonusMoney1 )
		end
		if x260001_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x260001_g_BonusMoney2 )
		end
		if x260001_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x260001_g_BonusMoney3 )
		end
		if x260001_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x260001_g_BonusMoney4 )
		end
		if x260001_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x260001_g_BonusMoney5 )
		end
		if x260001_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x260001_g_BonusMoney6 )
		end
		for i, item in x260001_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x260001_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x260001_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x260001_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x260001_g_MissionId) > 0 then
			if x260001_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x260001_g_MissionName)
						AddQuestText(sceneId,x260001_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x260001_g_ScriptId, x260001_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x260001_g_MissionName)
						AddQuestText(sceneId,x260001_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x260001_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x260001_g_ScriptId, x260001_g_MissionId);
			end
  elseif x260001_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x260001_g_MissionName)
			AddQuestText(sceneId,x260001_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x260001_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x260001_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x260001_g_MissionHelp )
			end
			x260001_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x260001_g_ScriptId, x260001_g_MissionId);
  end
	
end
--**********************************

function x260001_ProcAcceptCheck(sceneId, selfId, NPCId)
		--if IsQuestHaveDone(sceneId, selfId, x260001_g_MissionIdPre)> 0 then
					return 1
		--end
		--return 0

end
--**********************************
function x260001_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x260001_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x260001_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x260001_g_MissionId  )
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
		
		if x260001_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x260001_g_MissionId, x260001_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x260001_Msg2toplayer( sceneId, selfId,0)
						--if x260001_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x260001_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	   				--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x260001_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x260001_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x260001_g_MissionId)
	  x260001_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x260001_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x260001_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x260001_g_BonusChoiceItem do
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
--**********************************
function x260001_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x260001_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x260001_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x260001_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x260001_g_MissionId) > 0 then
				x260001_Msg2toplayer( sceneId, selfId,2)
				--QuestCom(sceneId, selfId, x260001_g_MissionId)
				x260001_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x260001_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x260001_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x260001_g_MissionIdNext )	
end

function x260001_GetBonus( sceneId, selfId,NpcID)
	  if x260001_g_ExpBonus > 0 then
	  local addexpture = x260001_g_ExpBonus*GetLevel(sceneId, selfId)
			AddExp(sceneId, selfId, addexpture);
  	end
		if x260001_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x260001_g_BonusMoney1 )
	  end
		if x260001_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x260001_g_BonusMoney2 )
	  end
		if x260001_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x260001_g_BonusMoney3 )
		end
		if x260001_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x260001_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x260001_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x260001_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x260001_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x260001_g_BonusMoney6)
		end
end

function x260001_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x260001_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x260001_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x260001_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x260001_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x260001_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x260001_g_MissionName.."��", 0, 3)
				local expAward =x260001_g_ExpBonus*GetLevel(sceneId, selfId)
				Msg2Player(sceneId, selfId, "#Y���#R����"..expAward.."#Y�Ľ���", 0, 2)
		end
end

function x260001_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x260001_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x260001_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x260001_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x260001_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x260001_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x260001_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x260001_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x260001_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x260001_g_MissionId, state, -1 )
		end
end

function x260001_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x260001_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x260001_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x260001_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x260001_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x260001_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x260001_ProcQuestLogRefresh( sceneId,selfId,missionId)

    BeginQuestEvent(sceneId)
    AddQuestExpBonus(sceneId, x260001_g_ExpBonus*GetLevel(sceneId, selfId) )
		EndQuestEvent()
		DispatchQuestLogUpdate(sceneId, selfId, x260001_g_MissionId);

end