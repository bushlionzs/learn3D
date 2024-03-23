--vipʦͽ

--MisDescBegin
x256280_g_ScriptId = 256280
x256280_g_MissionIdPre =-1
x256280_g_MissionId = 2620
x256280_g_LevelLess	= 	41 
x256280_g_LevelMax	= 	160 
x256280_g_MissionIdNext = -1
x256280_g_Name	={}
x256280_g_MasterDistance = 15
x256280_g_ExtTarget={{type=20,n=1,target="�ڽ���̵�����һ�������̵깺��һ��#Gʦ����л#W����ʦ����ӽ��佻��ʦͽ����Ա"}}
x256280_g_MissionName="�����ˡ�ʦͽ֮��"
x256280_g_MissionInfo="\t����㻹û��ʦ�����������������Ѱ��һλ��\n\t�����ҵ�ʦ��֮���ҽ��飬�ڽ���̵�����һ�������̵깺��һ��#Gʦ����л#W��Ȼ������ʦ�����һ����������һ�úõĽ������ǡ�"  --��������
x256280_g_MissionTarget=""		
x256280_g_MissionCompleted="\t�ܺã���������ʦͽ�����ദ�Ĳ��������Ҹ����ǵ�һЩСС�Ľ�����"					--�������npc˵���Ļ�
x256280_g_ContinueInfo="\t�ڽ���̵�����һ�������̵깺��һ��#Gʦ����л#W����ʦ����ӽ��佻��ʦͽ����Ա��"
x256280_g_MissionHelp =	""
x256280_g_DemandItem =	{12030211}						
x256280_g_BonusMoney1 =0
x256280_g_BonusMoney2 =0
x256280_g_BonusMoney3 =0
x256280_g_BonusMoney4 =0
x256280_g_BonusMoney5 =0
x256280_g_BonusMoney6 =0
x256280_g_BonusItem	=	{}
x256280_g_BonusChoiceItem ={}
x256280_g_ExpBonus = 1660000
x256280_g_GoodBadValue =35000
x256280_g_NpcGUID ={{ guid = 123726, name = "��Ү����"} }
--MisDescEnd

x256280_g_BonusMoney8 =0
x256280_g_GuildExpBonus =0
--**********************************

function x256280_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

    local level = GetLevel(sceneId, selfId) 
	if level < x256280_g_LevelLess  then	--�ȼ�����
		return
	end



	if IsQuestHaveDone(sceneId, selfId, x256280_g_MissionId) > 0 then --����ɹ�����
		return 
	end
	
	--if IsQuestHaveDone(sceneId, selfId, x256280_g_MissionIdPre)> 0 then 
	if IsHaveQuest(sceneId,selfId, x256280_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256280_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256280_g_MissionId, state, -1 )
	--end
	end

end

function x256280_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256280_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256280_g_ExpBonus )
		end
		if x256280_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256280_g_BonusMoney1 )
		end
		if x256280_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256280_g_BonusMoney2 )
		end
		if x256280_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256280_g_BonusMoney3 )
		end
		if x256280_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256280_g_BonusMoney4 )
		end
		if x256280_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256280_g_BonusMoney5 )
		end
		if x256280_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256280_g_BonusMoney6 )
		end
		for i, item in x256280_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x256280_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x256280_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256280_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256280_g_MissionId) > 0 then
			if x256280_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256280_g_MissionName)
				AddQuestText(sceneId,x256280_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x256280_g_ScriptId, x256280_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256280_g_MissionName)
				AddQuestText(sceneId,x256280_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x256280_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256280_g_ScriptId, x256280_g_MissionId);
			end
  elseif x256280_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x256280_g_MissionName)
			AddQuestText(sceneId,x256280_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256280_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256280_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256280_g_MissionHelp )
			end
			x256280_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256280_g_ScriptId, x256280_g_MissionId);
  end
	
end
--**********************************

function x256280_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x256280_CheckSubmit( sceneId, selfId, NPCId)  
                                                  
		if  IsHaveQuest(sceneId, selfId,x256280_g_MissionId) ~=1 then
			return 0
		end
		
	   	local 	misIndex = GetQuestIndexByID(sceneId, selfId,x256280_g_MissionId)                                                  
	   	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	   		return 1
	   	else 
	   		return 0
	   	end
	   	
	
end

--**********************************
function x256280_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256280_g_MissionId) > 0 then
				return 
		end
		
		--local level = GetLevel(sceneId, selfId)
		--if level >= 50 then
		--	Msg2Player(sceneId, selfId, "ֻ��ͽ�ܲ��ܽ��ܱ�����", 0, 3)
		--	return
		--end
		--if IsHavePrentice(sceneId, selfId)	==  1 then
		--	Msg2Player(sceneId, selfId, "�������ͽ������ȡ������", 0, 3)
		--	return 
		--end
		
		
	
		if IsQuestFullNM(sceneId,selfId)==1 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�ɽ�������������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 
		end
		
		--���ǰ������
--		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256280_g_MissionId  )
--		if FrontMissiontId1 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
--				return 0
--			end
--		end
--		if FrontMissiontId2 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
--				return 0
--			end
--		end
--		if FrontMissiontId3 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
--				return 0
--			end
--		end
		
		if x256280_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then

					local retmiss = AddQuest( sceneId, selfId, x256280_g_MissionId, x256280_g_ScriptId, 0, 0, 1,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256280_Msg2toplayer( sceneId, selfId,0)
		  			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 25,1 )
						--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 26,1 )
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 46,1 )
		  			
					for i, item in x256280_g_DemandItem do
						
						if GetItemCount(sceneId,selfId,item) >= 1 then	
						
							local misIndex = GetQuestIndexByID(sceneId,selfId,x256280_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 25,0 )
							--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 26,0 )
								CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 46,0 )
						end
					end
					--x256280_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
					end
		  			
	 	end                                                                    
	     
end
--**********************************

function x256280_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256280_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256280_g_MissionId)
	  x256280_Msg2toplayer( sceneId, selfId,1)
	  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 25,0 )
		--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 26,0 )
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 46,0 )	
end
--**********************************
function x256280_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256280_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256280_g_BonusChoiceItem do
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

function x256280_IsCanSubmit( sceneId, selfId )
	local teamSize = GetTeamSize(sceneId, selfId)
	if (teamSize < 2) then
		return "��Ķ����в���2�ˣ��޷��ύ������";
	end
	
	local isMasterHere = 0
	for i = 0, teamSize - 1 do
		local targetId = GetTeamMemberId(sceneId, selfId, i)
		if 1 == IsInDist(sceneId, selfId, targetId, x256280_g_MasterDistance) then
			if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
				isMasterHere = 1
			end
		end
	end
	
	if 0 == isMasterHere then
		return "���ʦ�����ڶ����л��߲��ڸ������޷��ύ������";
	end
	return 1
end
--**********************************

function x256280_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)


  		local teamSize = GetTeamSize(sceneId, selfId)
		if (teamSize < 2) then
			Msg2Player(sceneId, selfId, "��Ҫ�����ʦ�����һ������ɱ�����", 0, 3)
			return 
		end
		local isMasterHere = 0
			for i = 0, teamSize - 1 do
			local targetId = GetTeamMemberId(sceneId, selfId, i)
			if 1 == IsInDist(sceneId, selfId, targetId, x256280_g_MasterDistance) then
				if 1 == GetObjType(sceneId, targetId) and 1 == IsMaster(sceneId, selfId, targetId) then
					isMasterHere = 1
				end
			end
		end
	
		if 0 == isMasterHere then
			Msg2Player(sceneId, selfId, "���ʦ�����ڶ����л��߲��ڸ������޷���ɱ�����", 0, 3)
			return
		end
	if IsHaveQuest(sceneId,selfId, x256280_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256280_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256280_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ռ䲻�㣬�������������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256280_g_MissionId) > 0 then
				x256280_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256280_g_MissionId)
				DelItem(sceneId, selfId,12030211,1)
				x256280_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256280_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256280_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    			end
    			EndAddItem(sceneId,selfId)
    			local nCount = GetNearTeamCount(sceneId, selfId)
    			if nCount > 0 then
	    			for i = 0,nCount - 1 do
	    				
	    				local objId = GetNearTeamMember(sceneId, selfId, i)
		    			if IsPlayerStateNormal(sceneId,objId ) == 1 and objId ~= selfId then --�Ƿ����
		    						
									if IsMaster(sceneId, selfId, objId) ==  1 then
										local value = GetPlayerGoodBadValue(sceneId, objId)
										value = value + x256280_g_GoodBadValue
										SetPlayerGoodBadValue(sceneId, objId, value)
										Msg2Player(sceneId,  objId, "������������#R35000�㡣", 0, 3)
										Msg2Player(sceneId,  objId, "������������#R35000�㡣", 0, 2)
									end
		    			end
	    				
	    			end
    			end
    		--AddItemListToPlayer(sceneId,selfId)
   
  end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256280_g_MissionIdNext )	
end

function x256280_GetBonus( sceneId, selfId,NpcID)
	  if x256280_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256280_g_ExpBonus);
  	end
		if x256280_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256280_g_BonusMoney1 )
	  end
		if x256280_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256280_g_BonusMoney2 )
	  end
		if x256280_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256280_g_BonusMoney3 )
		end
		if x256280_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256280_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256280_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256280_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256280_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256280_g_BonusMoney6)
		end
		
		if x256280_g_BonusMoney8 > 0 then
		AddGuildUserPoint(sceneId,selfId,x256280_g_BonusMoney8)	--���Ӱﹱ
		local BonusMoney8 = x256280_g_BonusMoney8
		local pointText = "���#R�ﹱ"..BonusMoney8.."��#o�Ľ���"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, pointText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)			
  		Msg2Player(sceneId,selfId,pointText,8,2)
		end
-- ������ᾭ��
	local bangExp = x256280_g_GuildExpBonus 
	if bangExp > 0 then
		AddGuildExp(sceneId,selfId,bangExp)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���#R��ᾭ��"..bangExp.."��#o�Ľ���");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)			
  		Msg2Player(sceneId,selfId,"���#R��ᾭ��"..bangExp.."��#o�Ľ���",8,2)
	end
end

function x256280_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256280_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256280_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256280_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256280_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256280_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256280_g_MissionName.."��", 0, 3)
				if x256280_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256280_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256280_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256280_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256280_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256280_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256280_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256280_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256280_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256280_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256280_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256280_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256280_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256280_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256280_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256280_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256280_OnTimer(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "OnTimer",sceneId, selfId, ScriptId, MissionId )
		
end

function x256280_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256280_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId,optype)
	if	optype	==	0	then
		return
	end
	
	for i, item in x256280_g_DemandItem do
	
		if itemdataId == item then

			if GetItemCount(sceneId,selfId,item) >= 1 then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256280_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 25,0 )
						--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 26,0 )
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 46,0 )
		  	else
		  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256280_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		  	end
		  	
		  	break
	  	
	  	end
	  	
	end

end


function x256280_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256280_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256280_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256280_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256280_g_MissionId, state, -1 )
		end
end

function x256280_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256280_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256280_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256280_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256280_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256280_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end