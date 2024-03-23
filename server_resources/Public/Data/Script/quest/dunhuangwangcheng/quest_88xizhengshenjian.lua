--�����ߡ�����֮��

--MisDescBegin
x256116_g_ScriptId = 256116
x256116_g_MissionIdPre = 827
x256116_g_MissionId = 828
x256116_g_LevelLess	= 	88
x256116_g_Name	={}
x256116_g_ExtTarget={{type=20,n=1,target="�������������@npc_117000"}}
x256116_g_MissionName="���糡���������"
x256116_g_MissionInfo="\tĪ˹��һս���ζ�ƾ���Լ����˵��ǻۺ�������Ī˹�ƴ󹫲��õ���ıһ�������ƣ������������������ף�һ�ٶ��˹�������ĳ��С���Ī˹�ơ�"  --��������
x256116_g_MissionTarget=""		
x256116_g_MissionCompleted="\tĪ˹�ƴ���ı��¶�������̶�������������ֻ�������ϳ����ɼ�˼�������ӣ�δ���Ľ��ʴ󺹰ζ���ȡ��������·�ϵĵ�һ����ʤ��"					--�������npc˵���Ļ�
x256116_g_ContinueInfo="\t������սʷ����һ��ƪ����������Ļ��"
x256116_g_MissionHelp = ""
x256116_g_DemandItem ={{id=13020027,num=1}}
x256116_g_ExpBonus = 2190000
x256116_g_BonusMoney1 =1400
x256116_g_BonusMoney2 =0
x256116_g_BonusMoney3 =0
x256116_g_BonusMoney4 =0
x256116_g_BonusMoney5 =106
x256116_g_BonusMoney6 =0
x256116_g_BonusItem	=	{}
x256116_g_BonusChoiceItem ={}
x256116_g_NpcGUID ={{ guid = 117000, name = "Կ������"}}
--MisDescEnd
--**********************************

function x256116_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x256116_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256116_g_MissionId) > 0 then
	return 
	end	
	if GetLevel(sceneId, selfId) >= x256116_g_LevelLess then
		if IsQuestHaveDone(sceneId, selfId, x256116_g_MissionIdPre)> 0 then
	   	if IsHaveQuest(sceneId,selfId, x256116_g_MissionId) <= 0 then
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x256116_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x256116_g_MissionId, state, -1 )
			end
		end
	end
end

function x256116_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256116_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256116_g_ExpBonus )
		end
		if x256116_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256116_g_BonusMoney1 )
		end
		if x256116_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256116_g_BonusMoney2 )
		end
		if x256116_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256116_g_BonusMoney3 )
		end
		if x256116_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256116_g_BonusMoney4 )
		end
		if x256116_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256116_g_BonusMoney5 )
		end
		if x256116_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256116_g_BonusMoney6 )
		end
		for i, item in x256116_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256116_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256116_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256116_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256116_g_MissionId) > 0 then
			if x256116_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256116_g_MissionName)
						AddQuestText(sceneId,x256116_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256116_g_ScriptId, x256116_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256116_g_MissionName)
						AddQuestText(sceneId,x256116_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256116_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256116_g_ScriptId, x256116_g_MissionId);
			end
  elseif x256116_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256116_g_MissionName)
			AddQuestText(sceneId,x256116_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256116_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256116_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256116_g_MissionHelp )
			end
			x256116_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256116_g_ScriptId, x256116_g_MissionId);
  end
	
end
--**********************************

function x256116_ProcAcceptCheck(sceneId, selfId, NPCId)
		--if IsQuestHaveDone(sceneId, selfId, x256116_g_MissionIdPre)> 0 then
					return 1
		--end
		--return 0

end
--**********************************
function x256116_CheckSubmit( sceneId, selfId, NPCId)
		if GetItemCount(sceneId,selfId,x256116_g_DemandItem[1].id) >= x256116_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256116_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256116_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
	
end
--**********************************
function x256116_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256116_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256116_g_MissionId  )
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
		
		
		if x256116_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256116_g_MissionId, x256116_g_ScriptId, 1, 0, 0, 1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256116_Msg2toplayer( sceneId, selfId,0)
		  			x256116_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
						if x256116_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256116_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256116_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256116_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256116_g_MissionId)
	  x256116_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x256116_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256116_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256116_g_BonusChoiceItem do
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
function x256116_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256116_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256116_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256116_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256116_g_MissionId) > 0 then
				x256116_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256116_g_MissionId)
				x256116_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256116_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256116_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x256116_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
end

function x256116_GetBonus( sceneId, selfId,NpcID)
	  if x256116_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256116_g_ExpBonus);
  	end
		if x256116_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256116_g_BonusMoney1 )
	  end
		if x256116_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256116_g_BonusMoney2 )
	  end
		if x256116_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256116_g_BonusMoney3 )
		end
		if x256116_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256116_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256116_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256116_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256116_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256116_g_BonusMoney6)
		end
end

function x256116_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256116_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256116_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256116_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256116_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256116_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256116_g_MissionName.."��", 0, 3)
				if x256116_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256116_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256116_g_BonusMoney1 > 0 then
					local money =x256116_g_BonusMoney1
	  		  Msg2Player( sceneId, selfId, format( "#Y���#R����#{_MONEY%d}#cffcf00#Y�Ľ���", money).."��", 8, 2)
	  		end
				if x256116_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256116_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256116_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256116_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256116_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256116_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256116_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256116_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256116_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256116_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256116_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256116_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256116_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256116_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256116_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
		if GetItemCount(sceneId,selfId,x256116_g_DemandItem[1].id) >= x256116_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256116_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256116_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256116_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256116_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
end


function x256116_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
local bFind  = 0
    for i ,item in x256116_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256116_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256116_g_MissionId)        ---ȡ������״̬ ������״̬��Ӱ�ť AddQuestTextNM
				AddQuestTextNM( sceneId, selfId, npcId, x256116_g_MissionId, state, -1 )
		end
end

function x256116_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256116_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256116_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256116_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256116_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256116_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end