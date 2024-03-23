--�д���ȡ

--MisDescBegin
x203800_g_ScriptId = 203800
x203800_g_MissionIdPre =-1
x203800_g_MissionId = 1469
x203800_g_LevelLess	= 	40
x203800_g_MissionIdNext = 1470
x203800_g_Name	={}
x203800_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_139104"}}
x203800_g_MissionName="�����ˡ��󶼵�����<һ>"
x203800_g_MissionInfo="\t����˵�ڴ��и��ط��������裬�����椶��Ƕ����ȸ����ޣ���֪����ȥ��û�������Ҫȥ�����Ļ�������@npc_139104�ɡ�"  --��������
x203800_g_MissionTarget=""		
x203800_g_MissionCompleted="\t˧����Ů��ע���ˣ��������ȫ����������������ϣ������һ�µľ������Ұɣ�"					--�������npc˵���Ļ�
x203800_g_ContinueInfo=""
x203800_g_MissionHelp =	""
x203800_g_DemandItem ={}
x203800_g_ExpBonus = 30000
x203800_g_BonusMoney1 =0
x203800_g_BonusMoney2 =0
x203800_g_BonusMoney3 =0
x203800_g_BonusMoney4 =0
x203800_g_BonusMoney5 =0
x203800_g_BonusMoney6 =0
x203800_g_BonusItem	=	{{item=12030011,n=20}}
x203800_g_BonusChoiceItem ={}
x203800_g_NpcGUID ={{ guid = 139104, name = "��ʮ��"} }
--MisDescEnd
--**********************************
x203800_g_MaxLevel   = 160

function x203800_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x203800_g_LevelLess or level >= x203800_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x203800_g_MissionId) > 0 then
		return 
	end
	--if IsQuestHaveDone(sceneId, selfId, x203800_g_MissionIdPre)> 0 then
						if IsHaveQuest(sceneId,selfId, x203800_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x203800_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x203800_g_MissionId, state, -1 )
						end
	--end
end

function x203800_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203800_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203800_g_ExpBonus )
		end
		if x203800_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203800_g_BonusMoney1 )
		end
		if x203800_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203800_g_BonusMoney2 )
		end
		if x203800_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203800_g_BonusMoney3 )
		end
		if x203800_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203800_g_BonusMoney4 )
		end
		if x203800_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203800_g_BonusMoney5 )
		end
		if x203800_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203800_g_BonusMoney6 )
		end
		for i, item in x203800_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203800_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203800_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203800_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203800_g_MissionId) > 0 then
			if x203800_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203800_g_MissionName)
						AddQuestText(sceneId,x203800_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203800_g_ScriptId, x203800_g_MissionId);
			else
						--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 39,0 )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203800_g_MissionName)
						AddQuestText(sceneId,x203800_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203800_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203800_g_ScriptId, x203800_g_MissionId);
			end
  elseif x203800_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203800_g_MissionName)
			AddQuestText(sceneId,x203800_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203800_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203800_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203800_g_MissionHelp )
			end
			x203800_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203800_g_ScriptId, x203800_g_MissionId);
  end
	
end
--**********************************

function x203800_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203800_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203800_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203800_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203800_g_MissionId  )
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
		
		if x203800_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203800_g_MissionId, x203800_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203800_Msg2toplayer( sceneId, selfId,0)
						--if x203800_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203800_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203800_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203800_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203800_g_MissionId)
	  x203800_Msg2toplayer( sceneId, selfId,1)
	  --CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 39,0 )
			
end
--**********************************
function x203800_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203800_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x203800_g_BonusChoiceItem do
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
function x203800_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203800_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203800_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203800_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203800_g_MissionId) > 0 then
				x203800_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203800_g_MissionId)
				x203800_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203800_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x203800_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
  		CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203800_g_MissionIdNext )	
end

function x203800_GetBonus( sceneId, selfId,NpcID)
	  if x203800_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203800_g_ExpBonus);
  	end
		if x203800_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203800_g_BonusMoney1 )
	  end
		if x203800_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203800_g_BonusMoney2 )
	  end
		if x203800_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203800_g_BonusMoney3 )
		end
		if x203800_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203800_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203800_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203800_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203800_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203800_g_BonusMoney6)
		end
end

function x203800_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203800_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203800_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203800_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203800_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203800_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203800_g_MissionName.."��", 0, 3)
				if x203800_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203800_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203800_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203800_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203800_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203800_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203800_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203800_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203800_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203800_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203800_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203800_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203800_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203800_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203800_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203800_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203800_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203800_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203800_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203800_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203800_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203800_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203800_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203800_g_MissionId, state, -1 )
				--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 39,1 )
		end
end

function x203800_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203800_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203800_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203800_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203800_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203800_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end