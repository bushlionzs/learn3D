--���糡��Ӫ��

--MisDescBegin
x202000_g_ScriptId = 202000
x202000_g_MissionIdPre =1022
x202000_g_MissionId = 1023
x202000_g_LevelLess	= 	30 
x202000_g_MissionIdNext = 1012
x202000_g_Name	={}
x202000_g_ExtTarget={{type=20,n=5,target="���5��@npc_105322"}}
x202000_g_MissionName="���糡��Ӫ��"
x202000_g_MissionInfo="\t��֪���������������а취�ȳ��������յ���ʿ���Ƕ���װ��������棬Ҫ�Ͻ��ȳ����ǣ����������������ܿڣ�"  --��������
x202000_g_MissionTarget=""		
x202000_g_MissionCompleted="\t����������Щ�ֵ������ܿ��ˣ����ǻ�õ��������ף���ģ���Щ���������˶�����ȵģ�����Ƿ��һ������"					--�������npc˵���Ļ�
x202000_g_ContinueInfo="\t��Щ���Ǹ��ҳ��������ĵ��֣�һ��Ҫ�����ǳ�����"
x202000_g_MissionHelp =	""
x202000_g_DemandItem ={}
x202000_g_ExpBonus = 55000
x202000_g_BonusMoney1 =285
x202000_g_BonusMoney2 =0
x202000_g_BonusMoney3 =0
x202000_g_BonusMoney4 =0
x202000_g_BonusMoney5 =49
x202000_g_BonusMoney6 =0
x202000_g_BonusItem	=	{}
x202000_g_BonusChoiceItem ={}
x202000_g_GroupPoint	={ {type=10,id =311,target = "װ�����"} }
--MisDescEnd
--**********************************

function x202000_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x202000_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x202000_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x202000_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x202000_g_MissionId, state, -1 )
	end
end

function x202000_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x202000_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x202000_g_ExpBonus )
		end
		if x202000_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x202000_g_BonusMoney1 )
		end
		if x202000_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x202000_g_BonusMoney2 )
		end
		if x202000_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x202000_g_BonusMoney3 )
		end
		if x202000_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x202000_g_BonusMoney4 )
		end
		if x202000_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x202000_g_BonusMoney5 )
		end
		if x202000_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x202000_g_BonusMoney6 )
		end
		for i, item in x202000_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x202000_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x202000_ProcEventEntry(sceneId, selfId, NPCId, MissionId, which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x202000_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x202000_g_MissionId) > 0 then
			if x202000_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x202000_g_MissionName)
						AddQuestText(sceneId,x202000_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x202000_g_ScriptId, x202000_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x202000_g_MissionName)
						AddQuestText(sceneId,x202000_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x202000_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x202000_g_ScriptId, x202000_g_MissionId);
			end
  elseif x202000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x202000_g_MissionName)
			AddQuestText(sceneId,x202000_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x202000_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x202000_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x202000_g_MissionHelp )
			end
			x202000_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x202000_g_ScriptId, x202000_g_MissionId);
  end
	
end
--**********************************

function x202000_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x202000_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x202000_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x202000_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) >= 5 then
					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	    end
	 		return 0
	
end
--**********************************
function x202000_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x202000_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x202000_g_MissionId  )
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
		if x202000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x202000_g_MissionId, x202000_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x202000_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x202000_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x202000_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x202000_g_MissionId)
	  x202000_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x202000_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x202000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x202000_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x202000_g_BonusChoiceItem do
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
function x202000_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x202000_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x202000_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x202000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x202000_g_MissionId) > 0 then
				x202000_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x202000_g_MissionId)
				x202000_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x202000_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x202000_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x202000_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x202000_g_MissionIdNext )	
end

function x202000_GetBonus( sceneId, selfId,NpcID)
	  if x202000_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x202000_g_ExpBonus);
  	end
		if x202000_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x202000_g_BonusMoney1 )
	  end
		if x202000_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x202000_g_BonusMoney2 )
	  end
		if x202000_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x202000_g_BonusMoney3 )
		end
		if x202000_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x202000_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x202000_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x202000_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x202000_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x202000_g_BonusMoney6)
		end
end

function x202000_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x202000_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x202000_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x202000_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x202000_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x202000_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x202000_g_MissionName.."��", 0, 3)
				if x202000_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x202000_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x202000_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x202000_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x202000_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x202000_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x202000_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x202000_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x202000_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x202000_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x202000_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x202000_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x202000_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x202000_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x202000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x202000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x202000_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x202000_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x202000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x202000_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x202000_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x202000_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x202000_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x202000_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x202000_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x202000_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x202000_Growpoint(sceneId,selfId,which)
		if IsHaveQuest(sceneId,selfId, x202000_g_MissionId) <= 0 then
				return 1
		end
		if which ==0 then
							return 0
		elseif which == 1 then
				if IsHaveQuest(sceneId,selfId, x202000_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,selfId,x202000_g_MissionId)
										if GetQuestParam(sceneId,selfId,misIndex,0) < 5 then
												SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
												Msg2Player(sceneId, selfId, format("��ȱ�������ʿ   %d/5", GetQuestParam(sceneId,selfId,misIndex,0)), 0, 3)
												x202000_CheckSubmit( sceneId, selfId)
										end
										local x,z =GetWorldPos(sceneId,selfId)
										local creatid =CreateMonster(sceneId, 152,x,z,3,1,-1,-1,20,4000,180,"��������ʿ")
										SendSpecificImpactToUnit(sceneId, creatid, creatid, creatid, 8712, 0);
        end
    		return 1
    end
		
end