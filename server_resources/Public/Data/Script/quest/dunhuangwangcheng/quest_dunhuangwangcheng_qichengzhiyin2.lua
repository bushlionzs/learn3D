--����

--MisDescBegin
x256052_g_ScriptId = 256052
x256052_g_MissionIdPre =2816
x256052_g_MissionId = 2817
x256052_g_LevelLess	= 	30 
x256052_g_MissionIdNext = -1
x256052_g_Name	={}
x256052_g_ExtTarget={{type=20,n=2,target="�ش�@npc_137078������"}}
x256052_g_MissionName="����ѧ����˵�����"
x256052_g_MissionInfo="\t���Ѿ������㲻�ٹ�����˵�֪ʶ�ˣ���֪�����Ƿ��Ѿ�����������������㼸������ɡ�"  --��������
x256052_g_MissionTarget=""		
x256052_g_MissionCompleted="\t�����úܺã�������˼��ܵ�֪ʶ���Ѿ������������ˡ�"					--�������npc˵���Ļ�
x256052_g_ContinueInfo=""
x256052_g_MissionHelp =	""
x256052_g_DemandItem ={}
x256052_g_BonusMoney1 =0
x256052_g_BonusMoney2 =0
x256052_g_BonusMoney3 =0
x256052_g_BonusMoney4 =0
x256052_g_BonusMoney5 =0
x256052_g_BonusMoney6 =0
x256052_g_BonusItem	=	{}
x256052_g_BonusChoiceItem ={}
x256052_g_ExpBonus = 3000
x256052_g_NpcGUID ={}
x256052_g_answer1 ={"��˪��","����","����","ȫ��"}
x256052_g_answer2 ={"2������","1���ش�","2���ش�","4���ش�"}
x256052_g_question1 ={"\t�����ĸ������Ǳ������ܣ�"}
x256052_g_question2 ={"\t���������Ҫѧϰ3���ش�����ô��Ӧ����ʲô���ܣ�"}
--MisDescEnd
--**********************************

function x256052_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x256052_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x256052_g_MissionId, state, -1 )
	end
end

function x256052_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256052_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256052_g_ExpBonus )
		end
		if x256052_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256052_g_BonusMoney1 )
		end
		if x256052_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256052_g_BonusMoney2 )
		end
		if x256052_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256052_g_BonusMoney3 )
		end
		if x256052_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256052_g_BonusMoney4 )
		end
		if x256052_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256052_g_BonusMoney5 )
		end
		if x256052_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256052_g_BonusMoney6 )
		end
		for i, item in x256052_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256052_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256052_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256052_g_MissionId) > 0 then
	local zhiye =GetZhiye( sceneId, selfId)+1
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256052_g_MissionId)
	local daan =0
			if x256052_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which ==-1 then
						daan =2
						if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x256052_g_MissionName)
							AddQuestText(sceneId,x256052_g_question1[1])
							for i, item in x256052_g_answer1 do
								AddQuestNumText(sceneId, MissionId, x256052_g_answer1[i],3,i)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x256052_g_ScriptId, x256052_g_MissionId);
					  elseif GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x256052_g_MissionName)
							AddQuestText(sceneId,x256052_g_question2[1])
							for i, item in x256052_g_answer2 do
								AddQuestNumText(sceneId, MissionId, x256052_g_answer2[i],3,i+6)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x256052_g_ScriptId, x256052_g_MissionId);
					  end
					elseif which > -1 then
						if which <7 then
							if which ==4 then
									daan =1
							end
						elseif which == 9 then
									daan =1
						elseif daan == 2 then
							daan = 0
						end
					end
					if daan ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"�����ˣ������´�") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
					elseif daan ==1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"��ϲ�����ˣ�") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
						SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
						x256052_ProcEventEntry(sceneId, selfId, NPCId, MissionId,-1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256052_g_MissionName)
						AddQuestText(sceneId,x256052_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256052_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256052_g_ScriptId, x256052_g_MissionId);
			end
  elseif x256052_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256052_g_MissionName)
			AddQuestText(sceneId,x256052_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256052_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256052_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256052_g_MissionHelp )
			end
			x256052_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256052_g_ScriptId, x256052_g_MissionId);
  end
	
end
--**********************************

function x256052_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x256052_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x256052_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==2 then
	        return 1
	  end
	  return 0
	
end
--**********************************
function x256052_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256052_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256052_g_MissionId  )
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
		
		
		if x256052_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256052_g_MissionId, x256052_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256052_Msg2toplayer( sceneId, selfId,0)
						local misIndex = GetQuestIndexByID(sceneId,selfId,x256052_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			if x256052_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								SetQuestByIndex(sceneId,selfId,misIndex,0,2)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256052_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256052_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256052_g_MissionId)
	  x256052_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256052_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256052_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256052_g_BonusChoiceItem do
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
function x256052_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256052_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256052_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256052_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256052_g_MissionId) > 0 then
				x256052_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256052_g_MissionId)
				x256052_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256052_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256052_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256052_g_MissionIdNext )	
end

function x256052_GetBonus( sceneId, selfId,NpcID)
	  if x256052_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256052_g_ExpBonus);
  	end
		if x256052_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256052_g_BonusMoney1 )
	  end
		if x256052_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256052_g_BonusMoney2 )
	  end
		if x256052_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256052_g_BonusMoney3 )
		end
		if x256052_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256052_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256052_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256052_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256052_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256052_g_BonusMoney6)
		end
end

function x256052_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256052_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256052_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256052_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256052_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256052_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256052_g_MissionName.."��", 0, 3)
				if x256052_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256052_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256052_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256052_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256052_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256052_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256052_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256052_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256052_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256052_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256052_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256052_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256052_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256052_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256052_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256052_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256052_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256052_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256052_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256052_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	 
end

function x256052_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256052_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256052_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256052_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256052_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256052_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





