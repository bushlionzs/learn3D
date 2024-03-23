--����

--MisDescBegin
x203101_g_ScriptId = 203101
x203101_g_MissionIdPre =355
x203101_g_MissionId = 356
x203101_g_LevelLess	= 	50 
x203101_g_MissionIdNext = 357
x203101_g_Name	={}
x203101_g_ExtTarget={{type=20,n=2,target="���Żش�@npc_108002������"}}
x203101_g_MissionName="���糡���ܲ�ͨ������"
x203101_g_MissionInfo="\t���㿴������������������õĵ��ۣ��㱨���𴦻����µ����ţ�ʲô����˵�����𴦻���С�ӵĵ��ӣ���ô����ɶ�þ��ȵģ����ڣ��𴦻�֮�������ܲ�ͨ��ǰ����������ʵʵ�ģ�����������������Ϸ���������ܻش��������������⣬������Ӯ��"  --��������
x203101_g_MissionTarget=""		
x203101_g_MissionCompleted="\t�벻��������ĺܰ�������̫��ϧ�ˣ���׼����һ��Ҳ�������ͽ������һ����ġ��ٺ٣������˰ɣ�"					--�������npc˵���Ļ�
x203101_g_ContinueInfo=""
x203101_g_MissionHelp =	""
x203101_g_DemandItem ={}
x203101_g_ExpBonus = 112000
x203101_g_BonusMoney1 =295
x203101_g_BonusMoney2 =0
x203101_g_BonusMoney3 =0
x203101_g_BonusMoney4 =0
x203101_g_BonusMoney5 =56
x203101_g_BonusMoney6 =0
x203101_g_BonusItem	=	{}
x203101_g_BonusChoiceItem ={}
x203101_g_NpcGUID ={}
x203101_g_answer1 ={"��","Ů��","�书"}
x203101_g_answer2 ={"����ɽ","����ɽ","�ϱ�ɽ"}
x203101_g_question1 ={"\t��²��Ͻл�������ʲô�� "}
x203101_g_question2 ={"\t��˵����ȫ������ﻹ�и�ʲô��ʲ�ӹ�Ĺ�ɣ�ϲ��ס�ض����֪������ס������ɽ�ĵ��£�"}
--MisDescEnd
--**********************************

function x203101_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203101_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203101_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203101_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203101_g_MissionId, state, -1 )
	end
end

function x203101_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203101_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203101_g_ExpBonus )
		end
		if x203101_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203101_g_BonusMoney1 )
		end
		if x203101_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203101_g_BonusMoney2 )
		end
		if x203101_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203101_g_BonusMoney3 )
		end
		if x203101_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203101_g_BonusMoney4 )
		end
		if x203101_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203101_g_BonusMoney5 )
		end
		if x203101_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203101_g_BonusMoney6 )
		end
		for i, item in x203101_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203101_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203101_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203101_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203101_g_MissionId) > 0 then
	local zhiye =GetZhiye( sceneId, selfId)+1
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203101_g_MissionId)
	local daan =0
			if x203101_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which ==-1 then
						daan =2
						if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x203101_g_MissionName)
							AddQuestText(sceneId,x203101_g_question1[1])
							for i, item in x203101_g_answer1 do
								AddQuestNumText(sceneId, MissionId, x203101_g_answer1[i],3,i)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x203101_g_ScriptId, x203101_g_MissionId);
					  elseif GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"#Y"..x203101_g_MissionName)
							AddQuestText(sceneId,x203101_g_question2[1])
							for i, item in x203101_g_answer2 do
								AddQuestNumText(sceneId, MissionId, x203101_g_answer2[i],3,i+6)
							end 
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x203101_g_ScriptId, x203101_g_MissionId);
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
						AddQuestText(sceneId,"�����ˣ������´�") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
					elseif daan ==1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"��ϲ�����ˣ�") 
						EndQuestEvent()
						DispatchQuestTips(sceneId, selfId)
						SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
						x203101_ProcEventEntry(sceneId, selfId, NPCId, MissionId,-1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203101_g_MissionName)
						AddQuestText(sceneId,x203101_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203101_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203101_g_ScriptId, x203101_g_MissionId);
			end
  elseif x203101_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203101_g_MissionName)
			AddQuestText(sceneId,x203101_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203101_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203101_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203101_g_MissionHelp )
			end
			x203101_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203101_g_ScriptId, x203101_g_MissionId);
  end
	
end
--**********************************

function x203101_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203101_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203101_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203101_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==2 then
	        return 1
	  end
	  return 0
	
end
--**********************************
function x203101_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203101_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203101_g_MissionId  )
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
		
		if x203101_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203101_g_MissionId, x203101_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203101_Msg2toplayer( sceneId, selfId,0)
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203101_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			if x203101_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								SetQuestByIndex(sceneId,selfId,misIndex,0,2)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203101_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203101_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203101_g_MissionId)
	  x203101_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203101_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203101_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203101_g_BonusChoiceItem do
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
function x203101_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x203101_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203101_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203101_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203101_g_MissionId) > 0 then
				x203101_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203101_g_MissionId)
				x203101_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203101_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203101_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203101_g_MissionIdNext )	
end

function x203101_GetBonus( sceneId, selfId,NpcID)
	  if x203101_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203101_g_ExpBonus);
  	end
		if x203101_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203101_g_BonusMoney1 )
	  end
		if x203101_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203101_g_BonusMoney2 )
	  end
		if x203101_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203101_g_BonusMoney3 )
		end
		if x203101_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203101_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203101_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203101_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203101_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203101_g_BonusMoney6)
		end
end

function x203101_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203101_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203101_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203101_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203101_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203101_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203101_g_MissionName.."��", 0, 3)
				if x203101_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203101_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203101_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203101_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203101_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203101_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203101_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203101_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203101_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203101_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203101_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203101_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203101_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203101_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203101_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203101_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203101_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203101_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203101_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203101_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	 
end

function x203101_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203101_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203101_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203101_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203101_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203101_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





