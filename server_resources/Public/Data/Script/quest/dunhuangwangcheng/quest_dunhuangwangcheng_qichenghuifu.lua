--��˻ָ�

--MisDescBegin
x256250_g_ScriptId = 256250
x256250_g_MissionIdPre =3053
x256250_g_MissionId = 3054
x256250_g_LevelLess	= 	25 
x256250_g_MissionIdNext = 3055
x256250_g_Name	={}
x256250_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_138506"}}
x256250_g_MissionName="�����ˡ���˻ָ�"
x256250_g_MissionInfo="\t�������ƺ���Щƣ�룬�������@npc_138506����Ϊ�����˻ظ��������Ҳ���Ҫ���ϡ�\n\t��ס���Դ�����Ҫ��Դ�����һ������Ҳ��Ҫ��Ĺ�ע���չˡ�"  --��������
x256250_g_MissionTarget=""		
x256250_g_MissionCompleted="\tҪ����˻ָ���������������ʶԵط��ˣ��������ǵİ��������˶���������ң��ҿ���˲�佫���е���˻ָ������״̬����ֻ��Ҫ����һ����Ǯ��������һ�����ѡ� "					--�������npc˵���Ļ�
x256250_g_ContinueInfo=""
x256250_g_MissionHelp =	""
x256250_g_DemandItem ={}
x256250_g_BonusMoney1 =0
x256250_g_BonusMoney2 =0
x256250_g_BonusMoney3 =0
x256250_g_BonusMoney4 =0
x256250_g_BonusMoney5 =0
x256250_g_BonusMoney6 =0
x256250_g_BonusItem	=	{{item=12050000,n=3}}
x256250_g_BonusChoiceItem ={}
x256250_g_ExpBonus = 11500
x256250_g_NpcGUID ={{ guid = 138506, name = "�¶���"} }
--MisDescEnd
--**********************************
x256250_g_MaxLevel   = 40

function x256250_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256250_g_LevelLess or level >= x256250_g_MaxLevel then
		return
	end

	if IsQuestHaveDone(sceneId, selfId, x256250_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x256250_g_MissionIdPre)> 0 then
						if IsHaveQuest(sceneId,selfId, x256250_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x256250_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x256250_g_MissionId, state, -1 )
						end
	end
end

function x256250_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256250_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256250_g_ExpBonus )
		end
		if x256250_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256250_g_BonusMoney1 )
		end
		if x256250_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256250_g_BonusMoney2 )
		end
		if x256250_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256250_g_BonusMoney3 )
		end
		if x256250_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256250_g_BonusMoney4 )
		end
		if x256250_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256250_g_BonusMoney5 )
		end
		if x256250_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256250_g_BonusMoney6 )
		end
		for i, item in x256250_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256250_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256250_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256250_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256250_g_MissionId) > 0 then
			if x256250_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256250_g_MissionName)
						AddQuestText(sceneId,x256250_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256250_g_ScriptId, x256250_g_MissionId);
			else
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 40,0 )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256250_g_MissionName)
						AddQuestText(sceneId,x256250_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256250_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256250_g_ScriptId, x256250_g_MissionId);
			end
  elseif x256250_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256250_g_MissionName)
			AddQuestText(sceneId,x256250_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256250_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256250_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256250_g_MissionHelp )
			end
			x256250_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256250_g_ScriptId, x256250_g_MissionId);
  end
	
end
--**********************************

function x256250_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x256250_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x256250_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256250_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256250_g_MissionId  )
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
		
		if x256250_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256250_g_MissionId, x256250_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256250_Msg2toplayer( sceneId, selfId,0)
						--if x256250_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256250_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256250_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256250_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256250_g_MissionId)
	  x256250_Msg2toplayer( sceneId, selfId,1)
	  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 40,0 )
			
end
--**********************************
function x256250_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ�������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256250_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256250_g_BonusChoiceItem do
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
function x256250_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256250_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256250_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256250_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256250_g_MissionId) > 0 then
				x256250_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256250_g_MissionId)
				x256250_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256250_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256250_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
  CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256250_g_MissionIdNext )	
end

function x256250_GetBonus( sceneId, selfId,NpcID)
	  if x256250_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256250_g_ExpBonus);
  	end
		if x256250_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256250_g_BonusMoney1 )
	  end
		if x256250_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256250_g_BonusMoney2 )
	  end
		if x256250_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256250_g_BonusMoney3 )
		end
		if x256250_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256250_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256250_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256250_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256250_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256250_g_BonusMoney6)
		end
end

function x256250_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256250_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256250_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256250_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256250_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256250_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256250_g_MissionName.."��", 0, 3)
				if x256250_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256250_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256250_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256250_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256250_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256250_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256250_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256250_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256250_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256250_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256250_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256250_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256250_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256250_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256250_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256250_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256250_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256250_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256250_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256250_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256250_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256250_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256250_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256250_g_MissionId, state, -1 )
				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 40,1 )
		end
end

function x256250_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256250_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256250_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256250_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256250_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256250_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end