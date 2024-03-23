--ѯ��״��

--MisDescBegin
x200000_g_ScriptId = 200000
x200000_g_MissionIdPre =13
x200000_g_MissionId = 15
x200000_g_LevelLess	= 	10 
x200000_g_MissionIdNext = -1
x200000_g_Name	={}
x200000_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_101003"}}
x200000_g_MissionName="���糡���ö�����Ǹ��<��>"
x200000_g_MissionInfo="\t���������ľ�ϣ����ö��������У���һֱ���ֳ�һ�㣬ϣ���Ժ����ܼ������ö����Ĵ�硣"  --��������
x200000_g_MissionTarget="���ö����Ļ�����@npc_101003"		
x200000_g_MissionCompleted="\t�ö���ѡ������ľ�棿һֱ�ǰ��ҵ��ֳ��������Ҳ����ţ���ƽʱ���ö�����ô�ã�����Ȼ�������ҵ�����磡�ѵ�����Ĳ������ҵ�����ô����\n\t�����İ����ö��������ѵ���ĺʹ���˵��һ������ľ����������ת��������Ƭ��ԭ������ô�� "					--�������npc˵���Ļ�
x200000_g_ContinueInfo=""
x200000_g_MissionHelp =	""
x200000_g_DemandItem ={}
x200000_g_ExpBonus = 3432
x200000_g_BonusMoney1 =220
x200000_g_BonusMoney2 =0
x200000_g_BonusMoney3 =0
x200000_g_BonusMoney4 =0
x200000_g_BonusMoney5 =25
x200000_g_BonusMoney6 =0
x200000_g_BonusItem	=	{}
x200000_g_BonusChoiceItem ={}
x200000_g_NpcGUID ={{ guid = 101003, name = "��ľ��"} }
--MisDescEnd
--**********************************

function x200000_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x200000_g_MissionId) > 0 then
		return 
	end
	
				if IsQuestHaveDone(sceneId, selfId, x200000_g_MissionIdPre)> 0 then
						if IsHaveQuest(sceneId,selfId, x200000_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x200000_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x200000_g_MissionId, state, -1 )
						end
				end
end

function x200000_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x200000_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x200000_g_ExpBonus )
		end
		if x200000_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x200000_g_BonusMoney1 )
		end
		if x200000_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x200000_g_BonusMoney2 )
		end
		if x200000_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x200000_g_BonusMoney3 )
		end
		if x200000_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x200000_g_BonusMoney4 )
		end
		if x200000_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x200000_g_BonusMoney5 )
		end
		if x200000_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x200000_g_BonusMoney6 )
		end
		for i, item in x200000_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x200000_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x200000_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x200000_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x200000_g_MissionId) > 0 then
			if x200000_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x200000_g_MissionName)
						AddQuestText(sceneId,x200000_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x200000_g_ScriptId, x200000_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x200000_g_MissionName)
						AddQuestText(sceneId,x200000_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x200000_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x200000_g_ScriptId, x200000_g_MissionId);
			end
  elseif x200000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x200000_g_MissionName)
			AddQuestText(sceneId,x200000_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x200000_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x200000_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x200000_g_MissionHelp )
			end
			x200000_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x200000_g_ScriptId, x200000_g_MissionId);
  end
	
end
--**********************************

function x200000_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x200000_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x200000_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x200000_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x200000_g_MissionId  )
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
		
		if x200000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x200000_g_MissionId, x200000_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x200000_Msg2toplayer( sceneId, selfId,0)
						--if x200000_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x200000_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x200000_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x200000_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x200000_g_MissionId)
	  x200000_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x200000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x200000_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x200000_g_BonusChoiceItem do
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
function x200000_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x200000_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x200000_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x200000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x200000_g_MissionId) > 0 then
				x200000_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x200000_g_MissionId)
				--CallScriptFunction( UTILITY_SCRIPT, "PlaySound", sceneId, selfId, 6 )
				x200000_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x200000_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x200000_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x200000_g_MissionIdNext )	
end

function x200000_GetBonus( sceneId, selfId,NpcID)
	  if x200000_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x200000_g_ExpBonus);
  	end
		if x200000_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x200000_g_BonusMoney1 )
	  end
		if x200000_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x200000_g_BonusMoney2 )
	  end
		if x200000_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x200000_g_BonusMoney3 )
		end
		if x200000_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x200000_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x200000_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x200000_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x200000_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x200000_g_BonusMoney6)
		end
end

function x200000_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x200000_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x200000_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x200000_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x200000_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x200000_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x200000_g_MissionName.."��", 0, 3)
				if x200000_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200000_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x200000_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x200000_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x200000_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x200000_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x200000_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x200000_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x200000_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x200000_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x200000_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200000_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x200000_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200000_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x200000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x200000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x200000_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x200000_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x200000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x200000_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x200000_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x200000_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x200000_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x200000_g_MissionId, state, -1 )
		end
end

function x200000_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x200000_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x200000_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x200000_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x200000_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x200000_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end