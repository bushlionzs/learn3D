--���糡�����鲻��

--MisDescBegin
x203306_g_ScriptId = 203306
x203306_g_MissionIdPre =485
x203306_g_MissionId = 486
x203306_g_LevelLess	= 45
x203306_g_MissionIdNext = 487
x203306_g_DemandKill ={{id=835,num=1}}
x203306_g_Name	={"����"}
x203306_g_ExtTarget={{type=20,n=1,target="����@npc_110041"}}
x203306_g_MissionName="���糡�����鲻��"
x203306_g_MissionInfo="\t�������㽲��������һƷ��������С��÷����ȴ��Ϊ�ɹŹ����Ĳ��ò��ֿ���ϣ�����ܳ�ȫһ�Գ������ˡ�\n\t�����Աߵ�����ȴ���в��ʣ�ԾԾ���ԡ�"  --��������
x203306_g_MissionTarget="����@npc_110041"		
x203306_g_MissionCompleted="\t(�����������ִ����˽��֣���Ը��������Ĺ����޸���)\n\t��ˣ�������á��������Ѳ��棬������ֻ����İ�����һ��Զ�߸߷ɣ����ǣ����ء���"
x203306_g_ContinueInfo=""
x203306_g_MissionHelp =	""
--x203306_g_DemandItem ={{id=13030081,num=1}}
x203306_g_ExpBonus =214000
x203306_g_BonusMoney1 =376
x203306_g_BonusMoney2 =0
x203306_g_BonusMoney3 =0
x203306_g_BonusMoney4 =0
x203306_g_BonusMoney5 =71
x203306_g_BonusMoney6 =0
x203306_g_BonusChoiceItem ={}
x203306_g_BonusItem	={{item=13020021,n=1}}
x203306_g_NpcGUID = 110041
--x203306_g_Impact1 = 2092
x203306_g_npcid = 0
x203306_g_chaerke =0
x203306_g_dog =0
x203306_g_pangxie = 0
x203306_g_acceptid =0
--MisDescEnd

--**********************************

function x203306_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

    --DelQuest(sceneId, selfId, x203306_g_MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203306_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203306_g_MissionIdPre)> 0 then 
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203306_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203306_g_MissionId, state, -1 )
	end
end

function x203306_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203306_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203306_g_ExpBonus )
		end
		if x203306_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203306_g_BonusMoney1 )
		end
		if x203306_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203306_g_BonusMoney2 )
		end
		if x203306_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203306_g_BonusMoney3 )
		end
		if x203306_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203306_g_BonusMoney4 )
		end
		if x203306_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203306_g_BonusMoney5 )
		end
		if x203306_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203306_g_BonusMoney6 )
		end
		for i, item in x203306_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203306_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--������ں���

--**********************************
function x203306_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
    x203306_g_npcid =   NPCId
	if IsQuestHaveDone(sceneId, selfId, x203306_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203306_g_MissionId) > 0 then
			if x203306_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203306_g_MissionName)
						AddQuestText(sceneId,x203306_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203306_g_ScriptId, x203306_g_MissionId);
			else
          
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203306_g_MissionName)
						AddQuestText(sceneId,x203306_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203306_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203306_g_ScriptId, x203306_g_MissionId);
			end
  elseif x203306_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203306_g_MissionName)
			AddQuestText(sceneId,x203306_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203306_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203306_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203306_g_MissionHelp )
			end
			x203306_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203306_g_ScriptId, x203306_g_MissionId);
  end
end
--**********************************
function x203306_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203306_g_MissionId) > 0 then
		return 0
	elseif GetLevel(sceneId, selfId)< x203306_g_LevelLess then
		return 0
	end
	return 1
end
--**********************************
function x203306_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203306_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == x203306_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	        return 1
	end
	return 0
end
--**********************************
function x203306_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203306_g_MissionId) > 0 then
				return 
		end
		
		--���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203306_g_MissionId  )
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
		
		if x203306_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203306_g_MissionId, x203306_g_ScriptId, 1, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
					if IsObjValid (sceneId,82) == 1 then
						--local x203306_g_liliang =FindMonsterByGUID( sceneId,110041)
		  			SetMonsterCamp(sceneId,82,21)
		  		end
            --CreateMonster(sceneId, 811,132,70,5,1,-1,-1,21,120000)
						x203306_Msg2toplayer( sceneId, selfId,0)
						--if x203306_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203306_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x203306_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203306_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203306_g_MissionId)
	  x203306_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x203306_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203306_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203306_g_BonusChoiceItem do
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
function x203306_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x203306_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203306_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203306_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203306_g_MissionId) > 0 then
				x203306_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203306_g_MissionId)
                x203306_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203306_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203306_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		    end
    		    EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203306_g_MissionIdNext )	
   end
end

function x203306_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
   
end

function x203306_GetBonus( sceneId, selfId,NpcID)
	  if x203306_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203306_g_ExpBonus);
  	end
		if x203306_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203306_g_BonusMoney1 )
	  end
		if x203306_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203306_g_BonusMoney2 )
	  end
		if x203306_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203306_g_BonusMoney3 )
		end
		if x203306_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203306_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203306_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203306_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203306_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203306_g_BonusMoney6)
		end
end

function x203306_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203306_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203306_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203306_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203306_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203306_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203306_g_MissionName.."��", 0, 3)
				if x203306_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203306_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203306_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203306_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203306_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203306_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203306_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203306_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203306_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203306_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203306_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203306_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203306_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203306_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

--**********************************

function x203306_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==x203306_g_DemandKill[1].id then
			local MissionId = x203306_g_MissionId
			local guid = GetMonsterGUID(sceneId, selfId)
			local x,z = GetWorldPos(sceneId,selfId)
			local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
			for i = 0, Num-1 do
				local humanObjId = GetNearPlayerMember(sceneId, selfId,i);
				if humanObjId >= 0 then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if IsHaveQuestNM(sceneId, humanObjId, x203306_g_MissionId) == 1 then
	    	        local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId)
		            SetQuestByIndex( sceneId, humanObjId, misIndex, 0, 1)
				        SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1)
				        Msg2Player( sceneId, humanObjId, format("��������   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 8, 3)
				        Msg2Player( sceneId, humanObjId, format("��������   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 8, 2)
				 		end
			    end
				end
			end
	end 
end
--**********************************
function x203306_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203306_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203306_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203306_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203306_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203306_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203306_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203306_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203306_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203306_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





