--���������Ŀ���<һ>

--MisDescBegin
x203303_g_ScriptId = 203303
x203303_g_MissionIdPre =475
x203303_g_MissionId = 476
x203303_g_LevelLess	= 	45 
x203303_g_MissionIdNext = 477
x203303_g_DemandKill ={{id=833,num=1}}
x203303_g_Name	={"��������"}
x203303_g_ExtTarget={{type=20,n=1,target="���ܹ�����@npc_22012"}}
x203303_g_MissionName="���糡�����������Ŀ���<һ>"
x203303_g_MissionInfo="\t#Y@myname#W������ʮ�ֿ�ϧ���Ҳ�������ҪѰ�ҵ����Ĺ�����\n\t������ңԶ�Ļ������������ǻ�������һֱ��Ϊΰ��ĳɼ�˼����ս��Ļ��������������ǶԴ���Ľ�Ѿã��˴���˵���������Ĺ�ͣ���������̸�������һ�ô󺹵ķ�ɡ�\n\t���������������������պյĽ��������ҵ��������ҡ����и�Ը������֪������û����Ȥָ��˴���ͬ��ǰ���������ӳ����У�"  --��������
x203303_g_MissionTarget=""		
x203303_g_MissionCompleted="\t������Ȼ���䲻�������Ҵ��۽磡"
x203303_g_ContinueInfo="\t�������ͣ������Ǽ�ʶһ�³ɼ�˼�����´󽫵ķ�ɰɣ�"
x203303_g_MissionHelp =	"#G���������û�л��������ӳ��������ӳ��ͻ�������ʧ�������Է��������½�ȡ������"
x203303_g_DemandItem ={}
x203303_g_ExpBonus = 214000
x203303_g_BonusMoney1 =376
x203303_g_BonusMoney2 =0
x203303_g_BonusMoney3 =0
x203303_g_BonusMoney4 =0
x203303_g_BonusMoney5 =71
x203303_g_BonusMoney6 =0
x203303_g_BonusItem	={}
x203303_g_BonusChoiceItem ={}
x203303_g_NpcGUID = 103001
x203303_g_Impact1 = 2092
x203303_g_npcid = 0
--MisDescEnd
--**********************************

function x203303_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    --DelQuest(sceneId, selfId, x203303_g_MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203303_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203303_g_MissionIdPre)> 0 then 
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203303_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203303_g_MissionId, state, -1 )
	end
end

function x203303_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203303_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203303_g_ExpBonus )
		end
		if x203303_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203303_g_BonusMoney1 )
		end
		if x203303_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203303_g_BonusMoney2 )
		end
		if x203303_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203303_g_BonusMoney3 )
		end
		if x203303_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203303_g_BonusMoney4 )
		end
		if x203303_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203303_g_BonusMoney5 )
		end
		if x203303_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203303_g_BonusMoney6 )
		end
		for i, item in x203303_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x203303_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--������ں���

--**********************************
function x203303_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
    x203303_g_npcid =   NPCId
	if IsQuestHaveDone(sceneId, selfId, x203303_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203303_g_MissionId) > 0 then
			if x203303_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203303_g_MissionName)
						AddQuestText(sceneId,x203303_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203303_g_ScriptId, x203303_g_MissionId);
			else
          
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203303_g_MissionName)
						AddQuestText(sceneId,x203303_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203303_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203303_g_ScriptId, x203303_g_MissionId);
			end
  elseif x203303_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203303_g_MissionName)
			AddQuestText(sceneId,x203303_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203303_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203303_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203303_g_MissionHelp )
			end
			x203303_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203303_g_ScriptId, x203303_g_MissionId);
  end
end
--**********************************
function x203303_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203303_g_MissionId) > 0 then
		return 0
	elseif GetLevel(sceneId, selfId)< x203303_g_LevelLess then
		return 0
	end
	return 1
end
--**********************************
function x203303_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203303_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == x203303_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	        return 1
	end
	return 0
end
--**********************************
function x203303_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203303_g_MissionId) > 0 then
				return 
		end
		
		--���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203303_g_MissionId  )
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
		
		if x203303_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203303_g_MissionId, x203303_g_ScriptId, 1, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			--SendSpecificImpactToUnit(sceneId, selfId, selfId, NPCId, x203303_g_Impact1, 0)
            CreateMonster(sceneId, 833,211,223,5,1,-1,-1,21,60000)
						x203303_Msg2toplayer( sceneId, selfId,0)
						--if x203303_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203303_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x203303_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203303_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203303_g_MissionId)
	  x203303_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x203303_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203303_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x203303_g_BonusChoiceItem do
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
function x203303_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x203303_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203303_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203303_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203303_g_MissionId) > 0 then
				x203303_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203303_g_MissionId)
                x203303_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203303_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203303_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		    end
    		    EndAddItem(sceneId,selfId)
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203303_g_MissionIdNext )	
   end
end

function x203303_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
   
end

function x203303_GetBonus( sceneId, selfId,NpcID)
	  if x203303_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203303_g_ExpBonus);
  	end
		if x203303_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203303_g_BonusMoney1 )
	  end
		if x203303_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203303_g_BonusMoney2 )
	  end
		if x203303_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203303_g_BonusMoney3 )
		end
		if x203303_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203303_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203303_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203303_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203303_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203303_g_BonusMoney6)
		end
end

function x203303_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203303_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203303_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203303_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203303_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203303_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203303_g_MissionName.."��", 0, 3)
				if x203303_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203303_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203303_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203303_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203303_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203303_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203303_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203303_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203303_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203303_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203303_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203303_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203303_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203303_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

--**********************************

function x203303_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==x203303_g_DemandKill[1].id then
			local MissionId = x203303_g_MissionId
			local guid = GetMonsterGUID(sceneId, selfId)
			local x,z = GetWorldPos(sceneId,selfId)
			local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
			for i = 0, Num-1 do
				local humanObjId = GetNearPlayerMember(sceneId, selfId,i);
				if humanObjId >= 0 then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if IsHaveQuestNM(sceneId, humanObjId, x203303_g_MissionId) == 1 then
	    	        local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId)
		            SetQuestByIndex( sceneId, humanObjId, misIndex, 0, 1)
				        SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1)
				        Msg2Player( sceneId, humanObjId, format("���ܻ��������ӳ�   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 8, 3)
				        Msg2Player( sceneId, humanObjId, format("���ܻ��������ӳ�   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 8, 2)
				 		end
			    end
				end
			end
	end 
end
--**********************************
function x203303_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203303_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203303_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203303_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203303_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203303_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203303_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203303_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203303_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203303_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





