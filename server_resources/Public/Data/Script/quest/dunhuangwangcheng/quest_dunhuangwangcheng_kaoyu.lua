--�����ߡ�����

--MisDescBegin
x256057_g_ScriptId = 256057
x256057_g_MissionIdPre =1607
x256057_g_MissionId = 1608
x256057_g_MissionIdNext = 1609
x256057_g_LevelLess	= 	10
x256057_g_Name	={}
x256057_g_ExtTarget={{type=20,n=1,target="ȥ@npc_82003����"}}
x256057_g_MissionName="�����ߡ�ͷ���Ҫ��<��>"
x256057_g_MissionInfo="\t������³�����۾�������\n\t�㻹��Ÿ�ʲô���������������ӿ����ˣ��Ǽ��ˣ��������¾ƣ�"  --��������
x256057_g_MissionTarget=""		
x256057_g_MissionCompleted="\t��û���������㿾�����㻹�治�����첻��ԭ���Ǹ��������ˣ��Ժ�������ɡ�"					--�������npc˵���Ļ�
x256057_g_ContinueInfo="\t�����أ�"
x256057_g_MissionHelp =	"#G����³ǰ������һ����ѣ����������ʺϿ��㡣"
x256057_g_DemandItem ={{id=13030089,num=1}}
x256057_g_BonusMoney1 =176
x256057_g_BonusMoney2 =0
x256057_g_BonusMoney3 =0
x256057_g_BonusMoney4 =0
x256057_g_BonusMoney5 =21
x256057_g_BonusMoney6 =0
x256057_g_BonusItem	=	{}
x256057_g_BonusChoiceItem ={}
x256057_g_ExpBonus = 1140
x256057_g_NpcGUID ={}
x256057_g_GroupPoint	=	{ {type=10,id =178,target = "���"} }--ר�����ڲɼ�����Ч�ã����������δ�ؾ����������ı�Ҫ���أ���ˣ�ֻҪ��ؾͿ��������������
--MisDescEnd
--**********************************

function x256057_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x256057_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x256057_g_MissionIdPre)> 0 then 
			
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x256057_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x256057_g_MissionId, state, -1 )
		
	end
end

function x256057_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256057_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256057_g_ExpBonus )
		end
		if x256057_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256057_g_BonusMoney1 )
		end
		if x256057_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256057_g_BonusMoney2 )
		end
		if x256057_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256057_g_BonusMoney3 )
		end
		if x256057_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256057_g_BonusMoney4 )
		end
		if x256057_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256057_g_BonusMoney5 )
		end
		if x256057_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256057_g_BonusMoney6 )
		end
		for i, item in x256057_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256057_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256057_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256057_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256057_g_MissionId) > 0 then
			if x256057_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256057_g_MissionName)
						AddQuestText(sceneId,x256057_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256057_g_ScriptId, x256057_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256057_g_MissionName)
						AddQuestText(sceneId,x256057_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256057_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256057_g_ScriptId, x256057_g_MissionId);
			end
  elseif x256057_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256057_g_MissionName)
			AddQuestText(sceneId,x256057_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256057_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256057_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256057_g_MissionHelp )
			end
			x256057_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256057_g_ScriptId, x256057_g_MissionId);
  end
	
end
--**********************************

function x256057_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x256057_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x256057_CheckSubmit( sceneId, selfId, NPCId)
		if GetItemCount(sceneId,selfId,x256057_g_DemandItem[1].id) >= x256057_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256057_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256057_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
	
end
--**********************************
function x256057_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256057_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256057_g_MissionId  )
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
		
		if x256057_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256057_g_MissionId, x256057_g_ScriptId, 0, 0, 1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
									BeginAddItem(sceneId)   
									AddItem( sceneId,13030087, 1 ) 
									EndQuestEvent()
									AddQuestText(sceneId,"���������Ʒ������")
			  					--DispatchQuestTips(sceneId, selfId)
			 					 AddItemListToPlayer(sceneId,selfId) 
		  			x256057_Msg2toplayer( sceneId, selfId,0)
		  			x256057_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
						if x256057_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256057_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256057_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256057_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256057_g_MissionId)
		DelItem(sceneId, selfId, 13030087, 1)
		DelItem(sceneId, selfId, 13030089, 1)
		
	  x256057_Msg2toplayer( sceneId, selfId,1)
	  
end
--**********************************
function x256057_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256057_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256057_g_BonusChoiceItem do
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
function x256057_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256057_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256057_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256057_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256057_g_MissionId) > 0 then
				x256057_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256057_g_MissionId)
				x256057_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256057_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256057_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x256057_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
    		CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256057_g_MissionIdNext )	
   end
end

function x256057_GetBonus( sceneId, selfId,NpcID)
	  if x256057_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256057_g_ExpBonus);
  	end
		if x256057_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256057_g_BonusMoney1 )
	  end
		if x256057_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256057_g_BonusMoney2 )
	  end
		if x256057_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256057_g_BonusMoney3 )
		end
		if x256057_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256057_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256057_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256057_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256057_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256057_g_BonusMoney6)
		end
end

function x256057_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256057_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256057_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256057_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256057_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256057_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256057_g_MissionName.."��", 0, 3)
				if x256057_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256057_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256057_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256057_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256057_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256057_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256057_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256057_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256057_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256057_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256057_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256057_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256057_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256057_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256057_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256057_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256057_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256057_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256057_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
		if GetItemCount(sceneId,selfId,x256057_g_DemandItem[1].id) >= x256057_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256057_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256057_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256057_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256057_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
end


function x256057_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x256057_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256057_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256057_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256057_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256057_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256057_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end