--�����ߡ�����֮��

--MisDescBegin
x256110_g_ScriptId = 256110
x256110_g_MissionIdPre =486
x256110_g_MissionId = 487
x256110_g_LevelLess	= 	45
x256110_g_Name	={}
x256110_g_ExtTarget={{type=20,n=1,target="�������������@npc_110039���ص����ǡ�"}}
x256110_g_MissionName="���糡���������"
x256110_g_MissionInfo="\t�����ܺ�����һ��Զ�����磬��������Ҳ�����ǵ����˸�����һ������֮�֣����ǽԴ�ϲ��"  --��������
x256110_g_MissionTarget=""		
x256110_g_MissionCompleted="\t�������𴨹�������������Զ�߸߷ɣ�����������ð���ĺ��ף�Ҳ�����˸����˵���֮�࣬ʵ�˴��ҡ�"					--�������npc˵���Ļ�
x256110_g_ContinueInfo="\t���Ķ�α������ɹŵ���Լ���ɼ�˼����׷��̫���ߵ��ˣ�һ�춼�����뿪�������ǣ��ͷ����������ġ�"
x256110_g_MissionHelp =	""
x256110_g_DemandItem ={{id=13020021,num=1}}
x256110_g_ExpBonus = 900000
x256110_g_BonusMoney1 =590
x256110_g_BonusMoney2 =0
x256110_g_BonusMoney3 =0
x256110_g_BonusMoney4 =0
x256110_g_BonusMoney5 =56
x256110_g_BonusMoney6 =0
x256110_g_BonusItem	=	{{item=11000201,n=20}}
x256110_g_BonusChoiceItem ={}
x256110_g_NpcGUID ={{ guid = 110039, name = "Կ������"}}
--MisDescEnd
--**********************************

function x256110_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x256110_g_MissionId) > 0 then
		return 
	end
		if IsHaveQuest(sceneId,selfId, x256110_g_MissionId) > 0 then
	return 
	end	
	if GetLevel(sceneId, selfId) >= x256110_g_LevelLess then
		if IsQuestHaveDone(sceneId, selfId, x256110_g_MissionIdPre)> 0 then
	   	if IsHaveQuest(sceneId,selfId, x256110_g_MissionId) <= 0 then
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x256110_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x256110_g_MissionId, state, -1 )
			end
		end
	end
end

function x256110_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256110_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256110_g_ExpBonus )
		end
		if x256110_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256110_g_BonusMoney1 )
		end
		if x256110_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256110_g_BonusMoney2 )
		end
		if x256110_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256110_g_BonusMoney3 )
		end
		if x256110_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256110_g_BonusMoney4 )
		end
		if x256110_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256110_g_BonusMoney5 )
		end
		if x256110_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256110_g_BonusMoney6 )
		end
		for i, item in x256110_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256110_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256110_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256110_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256110_g_MissionId) > 0 then
			if x256110_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256110_g_MissionName)
						AddQuestText(sceneId,x256110_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256110_g_ScriptId, x256110_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256110_g_MissionName)
						AddQuestText(sceneId,x256110_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256110_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256110_g_ScriptId, x256110_g_MissionId);
			end
  elseif x256110_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256110_g_MissionName)
			AddQuestText(sceneId,x256110_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256110_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256110_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256110_g_MissionHelp )
			end
			x256110_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256110_g_ScriptId, x256110_g_MissionId);
  end
	
end
--**********************************

function x256110_ProcAcceptCheck(sceneId, selfId, NPCId)
		--if IsQuestHaveDone(sceneId, selfId, x256110_g_MissionIdPre)> 0 then
					return 1
		--end
		--return 0

end
--**********************************
function x256110_CheckSubmit( sceneId, selfId, NPCId)
		if GetItemCount(sceneId,selfId,x256110_g_DemandItem[1].id) >= x256110_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256110_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256110_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
	
end
--**********************************
function x256110_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256110_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256110_g_MissionId  )
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
		
		
		if x256110_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256110_g_MissionId, x256110_g_ScriptId, 1, 0, 0, 1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256110_Msg2toplayer( sceneId, selfId,0)
		  			x256110_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
						if x256110_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256110_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256110_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256110_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256110_g_MissionId)
	  x256110_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x256110_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256110_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x256110_g_BonusChoiceItem do
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
--**********************************
function x256110_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256110_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256110_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256110_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256110_g_MissionId) > 0 then
				x256110_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256110_g_MissionId)
				x256110_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256110_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256110_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddBindItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x256110_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		AddItemListToPlayer(sceneId,selfId)
   end
end

function x256110_GetBonus( sceneId, selfId,NpcID)
	  if x256110_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256110_g_ExpBonus);
  	end
		if x256110_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256110_g_BonusMoney1 )
	  end
		if x256110_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256110_g_BonusMoney2 )
	  end
		if x256110_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256110_g_BonusMoney3 )
		end
		if x256110_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256110_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256110_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256110_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256110_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256110_g_BonusMoney6)
		end
end

function x256110_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256110_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256110_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256110_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256110_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256110_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256110_g_MissionName.."��", 0, 3)
				if x256110_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256110_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256110_g_BonusMoney1 > 0 then
					local money =x256110_g_BonusMoney1
	  		  Msg2Player( sceneId, selfId, format( "#Y���#R����#{_MONEY%d}#cffcf00#Y�Ľ���", money).."��", 8, 2)
	  		end
				if x256110_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256110_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256110_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256110_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256110_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256110_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256110_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256110_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256110_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256110_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256110_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256110_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256110_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256110_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256110_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
		if GetItemCount(sceneId,selfId,x256110_g_DemandItem[1].id) >= x256110_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256110_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256110_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256110_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256110_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
end


function x256110_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
local bFind  = 0
    for i ,item in x256110_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256110_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256110_g_MissionId)        ---ȡ������״̬ ������״̬��Ӱ�ť AddQuestTextNM
				AddQuestTextNM( sceneId, selfId, npcId, x256110_g_MissionId, state, -1 )
		end
end

function x256110_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256110_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256110_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256110_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256110_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256110_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end