--�����ߡ�Ԥ��֮��

--MisDescBegin
x256113_g_ScriptId = 256113
x256113_g_MissionIdPre =681
x256113_g_MissionId = 673
x256113_g_LevelLess	= 	75
x256113_g_Name	={}
x256113_g_ExtTarget={{type=20,n=1,target="�������������@npc_114007���ص�����"}}
x256113_g_MissionName="���糡���������"
x256113_g_MissionInfo="\tһ����ɱ��������أ��������λ������������Ƭ�����Ĵ�ɳĮ���ϵ����˴������ɹ���ʿ���Լ������������˳ɼ�˼�������ϣ�"  --��������
x256113_g_MissionTarget=""		
x256113_g_MissionCompleted="\t�ص��ɹŹ�����λ�����ֱ�޸�������أ���ɸ磬�ɼ�˼��ʹʧ������������֮����������ģ����Ħڭĩ���˾�һ���ۡ�"					--�������npc˵���Ļ�
x256113_g_ContinueInfo="\t��������ɹ�������־�ųɼ�˼����Ϊ������������֮����"
x256113_g_MissionHelp =	""
x256113_g_DemandItem ={{id=13020024,num=1}}
x256113_g_ExpBonus = 1800000
x256113_g_BonusMoney1 =750
x256113_g_BonusMoney2 =0
x256113_g_BonusMoney3 =0
x256113_g_BonusMoney4 =0
x256113_g_BonusMoney5 =86
x256113_g_BonusMoney6 =0
x256113_g_BonusItem	=	{}
x256113_g_BonusChoiceItem ={}
x256113_g_NpcGUID ={{ guid = 114007, name = "Կ������"}}
--MisDescEnd
--**********************************

function x256113_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x256113_g_MissionId) > 0 then
		return 
	end
			if IsHaveQuest(sceneId,selfId, x256113_g_MissionId) > 0 then
	return 
	end	
	if GetLevel(sceneId, selfId) >= x256113_g_LevelLess then
		if IsQuestHaveDone(sceneId, selfId, x256113_g_MissionIdPre)> 0 then
	   	if IsHaveQuest(sceneId,selfId, x256113_g_MissionId) <= 0 then
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x256113_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x256113_g_MissionId, state, -1 )
			end
		end
	end
end

function x256113_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256113_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256113_g_ExpBonus )
		end
		if x256113_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256113_g_BonusMoney1 )
		end
		if x256113_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256113_g_BonusMoney2 )
		end
		if x256113_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256113_g_BonusMoney3 )
		end
		if x256113_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256113_g_BonusMoney4 )
		end
		if x256113_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256113_g_BonusMoney5 )
		end
		if x256113_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256113_g_BonusMoney6 )
		end
		for i, item in x256113_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256113_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256113_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256113_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256113_g_MissionId) > 0 then
			if x256113_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256113_g_MissionName)
						AddQuestText(sceneId,x256113_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256113_g_ScriptId, x256113_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256113_g_MissionName)
						AddQuestText(sceneId,x256113_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256113_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256113_g_ScriptId, x256113_g_MissionId);
			end
  elseif x256113_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256113_g_MissionName)
			AddQuestText(sceneId,x256113_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256113_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256113_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256113_g_MissionHelp )
			end
			x256113_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256113_g_ScriptId, x256113_g_MissionId);
  end
	
end
--**********************************

function x256113_ProcAcceptCheck(sceneId, selfId, NPCId)
		--if IsQuestHaveDone(sceneId, selfId, x256113_g_MissionIdPre)> 0 then
					return 1
		--end
		--return 0

end
--**********************************
function x256113_CheckSubmit( sceneId, selfId, NPCId)
		if GetItemCount(sceneId,selfId,x256113_g_DemandItem[1].id) >= x256113_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256113_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256113_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
	
end
--**********************************
function x256113_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256113_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256113_g_MissionId  )
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
		
		
		if x256113_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256113_g_MissionId, x256113_g_ScriptId, 1, 0, 0, 1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256113_Msg2toplayer( sceneId, selfId,0)
		  			x256113_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
						if x256113_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256113_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256113_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256113_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256113_g_MissionId)
	  x256113_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x256113_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256113_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256113_g_BonusChoiceItem do
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
function x256113_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256113_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256113_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256113_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256113_g_MissionId) > 0 then
				x256113_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256113_g_MissionId)
				x256113_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256113_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256113_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x256113_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
end

function x256113_GetBonus( sceneId, selfId,NpcID)
	  if x256113_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256113_g_ExpBonus);
  	end
		if x256113_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256113_g_BonusMoney1 )
	  end
		if x256113_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256113_g_BonusMoney2 )
	  end
		if x256113_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256113_g_BonusMoney3 )
		end
		if x256113_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256113_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256113_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256113_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256113_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256113_g_BonusMoney6)
		end
end

function x256113_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256113_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256113_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256113_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256113_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256113_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256113_g_MissionName.."��", 0, 3)
				if x256113_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256113_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256113_g_BonusMoney1 > 0 then
					local money =x256113_g_BonusMoney1
	  		  Msg2Player( sceneId, selfId, format( "#Y���#R����#{_MONEY%d}#cffcf00#Y�Ľ���", money).."��", 8, 2)
	  		end
				if x256113_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256113_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256113_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256113_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256113_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256113_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256113_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256113_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256113_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256113_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256113_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256113_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256113_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256113_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256113_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
		if GetItemCount(sceneId,selfId,x256113_g_DemandItem[1].id) >= x256113_g_DemandItem[1].num then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256113_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256113_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256113_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,GetItemCount(sceneId,selfId,x256113_g_DemandItem[1].id))
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
end


function x256113_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
local bFind  = 0
    for i ,item in x256113_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256113_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256113_g_MissionId)        ---ȡ������״̬ ������״̬��Ӱ�ť AddQuestTextNM
				AddQuestTextNM( sceneId, selfId, npcId, x256113_g_MissionId, state, -1 )
		end
end

function x256113_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256113_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256113_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256113_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256113_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256113_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end