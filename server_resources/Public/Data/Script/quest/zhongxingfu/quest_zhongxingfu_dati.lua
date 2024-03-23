--����

--MisDescBegin
x203305_g_ScriptId = 203305
x203305_g_MissionIdPre =477
x203305_g_MissionId = 480
x203305_g_LevelLess	= 	45 
x203305_g_MissionIdNext = 481
x203305_g_Name	={}
x203305_g_ExtTarget={{type=20,n=2,target="���@npc_110029������"}}
x203305_g_MissionName="���糡��������������Ľ"
x203305_g_MissionInfo="\t��������˵���ܶ�󺹵Ĵ�˵�������Ѿã����Ǵ�˵������Щ����֮����������ʹ󺹲�����ս���꣬һ������Щ�˽����࣬�ɷ�Ϊ�ҽ��һ����"  --��������
x203305_g_MissionTarget=""		
x203305_g_MissionCompleted="\tԭ����������������Ҳ����������֮�ˡ���"					--�������npc˵���Ļ�
x203305_g_ContinueInfo=""
x203305_g_MissionHelp =	""
x203305_g_DemandItem ={}
x203305_g_ExpBonus = 214000
x203305_g_BonusMoney1 =376
x203305_g_BonusMoney2 =0
x203305_g_BonusMoney3 =0
x203305_g_BonusMoney4 =0
x203305_g_BonusMoney5 =71
x203305_g_BonusMoney6 =0
x203305_g_BonusItem	=	{}
x203305_g_BonusChoiceItem ={}
x203305_g_NpcGUID ={}
x203305_g_answer1 ={"����......��������","����һֱ�����м�","�������»�"}
x203305_g_answer2 ={"����Ϊ�˴�һ��","�󺹲�������","����ȫ��֪����"}
x203305_g_question1 ={"\t��˵�󺹵ĵ�һλ�����ö�������������������������������󺹾Ȼ���֮������֮�������Σ� "}
x203305_g_question2 ={"\t��˵�պ�������ľ���轫�����ڽ�����踮���²������������������Ŵ��º��кη�Ӧ��"}
--MisDescEnd
--**********************************

function x203305_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionId) > 0 then
		return 
	end
    
	if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203305_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203305_g_MissionId, state, -1 )
	end
end

function x203305_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203305_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203305_g_ExpBonus )
		end
		if x203305_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203305_g_BonusMoney1 )
		end
		if x203305_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203305_g_BonusMoney2 )
		end
		if x203305_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203305_g_BonusMoney3 )
		end
		if x203305_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203305_g_BonusMoney4 )
		end
		if x203305_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203305_g_BonusMoney5 )
		end
		if x203305_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203305_g_BonusMoney6 )
		end
		for i, item in x203305_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203305_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203305_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203305_g_MissionId) > 0 then
	local zhiye =GetZhiye( sceneId, selfId)+1
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203305_g_MissionId)
	local daan =0
			if x203305_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which ==-1 then
						daan =2
						if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x203305_g_MissionName)
							AddQuestText(sceneId,x203305_g_question1[1])
							for i, item in x203305_g_answer1 do
								AddQuestNumText(sceneId, MissionId, x203305_g_answer1[i],3,i)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x203305_g_ScriptId, x203305_g_MissionId);
					  elseif GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x203305_g_MissionName)
							AddQuestText(sceneId,x203305_g_question2[1])
							for i, item in x203305_g_answer2 do
								AddQuestNumText(sceneId, MissionId, x203305_g_answer2[i],3,i+6)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x203305_g_ScriptId, x203305_g_MissionId);
					  end
					elseif which > -1 then
						if which <7 then
							if which ==2 then
									daan =1
							end
						elseif which == 7 then
									daan =1
						elseif daan == 2 then
							daan = 0
						end
					end
					if daan ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"ԭ����Ҳ��֪��......") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
					elseif daan ==1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"ԭ�����������������ˡ�") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
						SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
--                        print(11111)
						x203305_ProcEventEntry(sceneId, selfId, NPCId, MissionId,-1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203305_g_MissionName)
						AddQuestText(sceneId,x203305_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203305_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203305_g_ScriptId, x203305_g_MissionId);
			end
  elseif x203305_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203305_g_MissionName)
			AddQuestText(sceneId,x203305_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203305_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203305_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203305_g_MissionHelp )
			end
			x203305_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203305_g_ScriptId, x203305_g_MissionId);
  end
	
end
--**********************************

function x203305_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203305_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203305_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==2 then
	        return 1
	  end
	  return 0
	
end
--**********************************
function x203305_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203305_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203305_g_MissionId  )
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
		
		if x203305_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203305_g_MissionId, x203305_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			  x203305_ProcEventEntry(sceneId, selfId, NPCId, MissionId,-1)
		  				x203305_Msg2toplayer( sceneId, selfId,0)
							local misIndex = GetQuestIndexByID(sceneId,selfId,x203305_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    				if x203305_CheckSubmit(sceneId, selfId, NPCId) > 0 then
									SetQuestByIndex(sceneId,selfId,misIndex,0,2)
	    				end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203305_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203305_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203305_g_MissionId)
	  x203305_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203305_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203305_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203305_g_BonusChoiceItem do
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
function x203305_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x203305_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203305_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203305_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203305_g_MissionId) > 0 then
				x203305_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203305_g_MissionId)
				x203305_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203305_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203305_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203305_g_MissionIdNext )	
end

function x203305_GetBonus( sceneId, selfId,NpcID)
	  if x203305_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203305_g_ExpBonus);
  	end
		if x203305_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203305_g_BonusMoney1 )
	  end
		if x203305_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203305_g_BonusMoney2 )
	  end
		if x203305_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203305_g_BonusMoney3 )
		end
		if x203305_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203305_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203305_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203305_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203305_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203305_g_BonusMoney6)
		end
end

function x203305_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203305_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203305_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203305_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203305_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203305_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203305_g_MissionName.."��", 0, 3)
				if x203305_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203305_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203305_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203305_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203305_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203305_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203305_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203305_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203305_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203305_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203305_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203305_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203305_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203305_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203305_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203305_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203305_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203305_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203305_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203305_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	 
end

function x203305_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203305_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203305_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203305_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203305_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203305_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





