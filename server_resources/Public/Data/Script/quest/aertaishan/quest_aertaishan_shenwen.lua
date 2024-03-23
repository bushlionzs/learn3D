--����

--MisDescBegin
x203111_g_ScriptId = 203111
x203111_g_MissionIdPre =501
x203111_g_MissionId = 502
x203111_g_LevelLess	= 	60 
x203111_g_MissionIdNext = 503
x203111_g_Name	={"����","�����²" }
x203111_g_ExtTarget={{type=20,n=1,target="���ʷ�²@npc_111012"}}
x203111_g_MissionName="���糡������"
x203111_g_MissionTalk={"��ȴΪ��ҪͶ����","���պ��������ںδ���","˵����ʵ����"}
x203111_g_MissionInfo="\t����ץ�˸����պ��ҵ����£�һ����С�Ӿ��Ǹ����ͷ���ɺ����ǲ��������Ļ�������Һú�������������"  --��������
x203111_g_MissionTarget=""		
x203111_g_MissionCompleted="\t�߼��ļ�������������ɵĽ������ĵ��ˣ����Լǵõ���ĵȼ�����Ժ󾭳�����ѧϰ�µļ��ܡ�\n\t�˲���һ�ڳԳ����ӣ�������ȴ��һ��һ�ڳԳ����ġ���֮�Ժ����ϰ�����ܳ�Ϊһ����ʦ��"
x203111_g_ContinueInfo={"\t��ɱ�ҡ��� ��ɱ�ҡ��� ��������Ͷ����λ�������ġ� ",
												"\t��ʵ���պ��Ҵ���......������������������;ĩ·���󲿷ָ��������˶���ڲ��ѣ���......����������Ͷ������λ������Ҫ�����Ұ���",
												"\t�����������Ǵ�ǰ����ɽ·���ߵģ������������ʱ׷���Ļ���һ���ܸ��ϡ�ֻ���λ������...��С��һ����·......"}
x203111_g_MissionHelp =	""
x203111_g_DemandItem ={}
x203111_g_ExpBonus = 214000
x203111_g_BonusMoney1 =376
x203111_g_BonusMoney2 =0
x203111_g_BonusMoney3 =0
x203111_g_BonusMoney4 =0
x203111_g_BonusMoney5 =71
x203111_g_BonusMoney6 =0
x203111_g_BonusItem	=	{}
x203111_g_BonusChoiceItem ={}
x203111_g_NpcGUID = {{ guid = 111012, name = "�����²"} }
--MisDescEnd
--**********************************

function x203111_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203111_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203111_g_MissionIdPre) > 0 then
				if IsHaveQuest(sceneId,selfId, x203111_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203111_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203111_g_MissionId, state, -1 )
				end
	end
end

function x203111_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203111_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203111_g_ExpBonus )
		end
		if x203111_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203111_g_BonusMoney1 )
		end
		if x203111_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203111_g_BonusMoney2 )
		end
		if x203111_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203111_g_BonusMoney3 )
		end
		if x203111_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203111_g_BonusMoney4 )
		end
		if x203111_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203111_g_BonusMoney5 )
		end
		if x203111_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203111_g_BonusMoney6 )
		end
		for i, item in x203111_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x203111_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--������ں���

--**********************************

function x203111_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203111_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203111_g_MissionId) > 0 then
			if x203111_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which == -1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203111_g_MissionName)
						AddQuestText(sceneId,x203111_g_ContinueInfo[1])
						AddQuestNumText(sceneId, MissionId, x203111_g_MissionTalk[1],0,0)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203111_g_ScriptId, x203111_g_MissionId);
					elseif which ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203111_g_MissionName)
						AddQuestText(sceneId,x203111_g_ContinueInfo[2])
						AddQuestNumText(sceneId, MissionId, x203111_g_MissionTalk[2],1,1)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203111_g_ScriptId, x203111_g_MissionId);
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203111_g_MissionId)  
						SetQuestByIndex(sceneId,selfId,misIndex,1,1)                                                
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203111_g_MissionName)
						AddQuestText(sceneId,x203111_g_ContinueInfo[3])
						AddQuestText(sceneId," ")
						x203111_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203111_g_ScriptId, x203111_g_MissionId);
			end
  elseif x203111_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203111_g_MissionName)
			AddQuestText(sceneId,x203111_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203111_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203111_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203111_g_MissionHelp )
			end
			x203111_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203111_g_ScriptId, x203111_g_MissionId);
  end
end
--**********************************
function x203111_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203111_g_MissionId) > 0 then
		return 0
	elseif IsQuestHaveDone(sceneId, selfId, x203111_g_MissionIdPre) <= 0 then
		return 0
	end
	return 1
end
--**********************************
function x203111_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203111_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,1) == 1 then
	        return 1
	end
	return 0
end
--**********************************
function x203111_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203111_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203111_g_MissionId  )
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
		
		if x203111_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203111_g_MissionId, x203111_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203111_Msg2toplayer( sceneId, selfId,0)
						--if x203111_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203111_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x203111_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203111_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203111_g_MissionId)
	  x203111_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x203111_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203111_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x203111_g_BonusChoiceItem do
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
function x203111_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203111_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203111_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203111_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203111_g_MissionId) > 0 then
				x203111_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203111_g_MissionId)
				x203111_GetBonus( sceneId, selfId,NPCId)
				--CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203111_g_MissionIdNext )	
   end
end

function x203111_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203111_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203111_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203111_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203111_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203111_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203111_g_MissionName.."��", 0, 3)
				if x203111_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203111_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203111_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203111_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203111_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203111_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203111_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203111_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203111_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203111_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203111_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203111_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203111_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203111_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203111_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x203111_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203111_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203111_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203111_g_MissionId, 7, -1 )
		end
end

function x203111_GetBonus( sceneId, selfId,NpcID)
	  if x203111_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203111_g_ExpBonus);
  	end
		if x203111_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203111_g_BonusMoney1 )
	  end
		if x203111_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203111_g_BonusMoney2 )
	  end
		if x203111_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203111_g_BonusMoney3 )
		end
		if x203111_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203111_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203111_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203111_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203111_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203111_g_BonusMoney6)
		end
end

--**********************************

function x203111_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end
--**********************************
function x203111_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203111_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203111_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203111_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203111_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203111_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203111_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203111_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203111_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203111_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





