--ѯ��״��

--MisDescBegin
x256226_g_ScriptId = 256226
x256226_g_MissionIdPre =3050
x256226_g_MissionId = 3092
x256226_g_LevelLess	= 	25 
x256226_g_MissionIdNext = 3051
x256226_g_Name	={}
x256226_g_ExtTarget={{type=20,n=1,target="��#G�����̵�#W�����ٴ��Ҵ���һ��@npc_82066"}}
x256226_g_MissionName="�����ˡ���һ������װ"
x256226_g_MissionInfo="\t�װ������ѣ����ҵ������кܶ�������װ��������Щ��װ��������������Ե�������\n\t��������̵��������#G��ȡ����������װ#W��ѡ������������װ���̵ꡣ������#G�����װ#W��ѡȡ��ϲ����һ��#G�Ҽ��������װ#W���������㹻������±�һ��ɹ���\n\t�������Ƽ������ȶһ�����������װ�еı���������㲻С�Ľ���װ�������ɵ���̵��е�#G�ع�#W�ٽ���װ��ء�"  --��������
x256226_g_MissionTarget=""		
x256226_g_MissionCompleted="\t���װ����Ȼ�����պ�ɳ�����������𵽲��ɵ͹������á�\n\tһ��Ҫ��ס���պ��ڻ���㹻��������������������һ�װ����"					--�������npc˵���Ļ�
x256226_g_ContinueInfo="\t�㲻��һ�һ��������װ��"
x256226_g_MissionHelp =	""
x256226_g_DemandItem =	   {10014001,10024001,10034001,10044001,10054001,10064001,10074001,10084001,10094001,10104001,10114001,10124001,10234001,10234011,10234021,10234031,10234041,10234051,10254001,10254011,10254021,10254031,10254041,10254051,10274001,10274011,10274021,10274031,10274041,10274051}						
x256226_g_BonusMoney1 =0
x256226_g_BonusMoney2 =0
x256226_g_BonusMoney3 =0
x256226_g_BonusMoney4 =0
x256226_g_BonusMoney5 =0
x256226_g_BonusMoney6 =0
x256226_g_BonusItem	=	{}
x256226_g_BonusChoiceItem ={}
x256226_g_ExpBonus = 10200
x256226_g_NpcGUID ={{ guid = 138538, name = "�����̵�"} }
--MisDescEnd
--**********************************
x256226_g_MaxLevel   = 40

function x256226_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256226_g_LevelLess or level >= x256226_g_MaxLevel then
		return
	end



	if IsQuestHaveDone(sceneId, selfId, x256226_g_MissionId) > 0 then
		return 
	end
	
	if IsQuestHaveDone(sceneId, selfId, x256226_g_MissionIdPre)> 0 then 
	if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256226_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256226_g_MissionId, state, -1 )
	end
	end

end

function x256226_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256226_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256226_g_ExpBonus )
		end
		if x256226_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256226_g_BonusMoney1 )
		end
		if x256226_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256226_g_BonusMoney2 )
		end
		if x256226_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256226_g_BonusMoney3 )
		end
		if x256226_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256226_g_BonusMoney4 )
		end
		if x256226_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256226_g_BonusMoney5 )
		end
		if x256226_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256226_g_BonusMoney6 )
		end
		for i, item in x256226_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x256226_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x256226_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256226_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) > 0 then
			if x256226_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256226_g_MissionName)
				AddQuestText(sceneId,x256226_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x256226_g_ScriptId, x256226_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256226_g_MissionName)
				AddQuestText(sceneId,x256226_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x256226_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256226_g_ScriptId, x256226_g_MissionId);
			end
  elseif x256226_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x256226_g_MissionName)
			AddQuestText(sceneId,x256226_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256226_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256226_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256226_g_MissionHelp )
			end
			x256226_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256226_g_ScriptId, x256226_g_MissionId);
  end
	
end
--**********************************

function x256226_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x256226_CheckSubmit( sceneId, selfId, NPCId)  
                                                  
		if  IsHaveQuest(sceneId, selfId,x256226_g_MissionId) ~=1 then
			return 0
		end
		
	   	local 	misIndex = GetQuestIndexByID(sceneId, selfId,x256226_g_MissionId)                                                  
	   	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	   		return 1
	   	else 
	   		return 0
	   	end
	   	
	
end

--**********************************
function x256226_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256226_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256226_g_MissionId  )
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
		
		if x256226_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then

					local retmiss = AddQuest( sceneId, selfId, x256226_g_MissionId, x256226_g_ScriptId, 0, 0, 1,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256226_Msg2toplayer( sceneId, selfId,0)
		  			
					for i, item in x256226_g_DemandItem do
						if GetItemCount(sceneId,selfId,x256226_g_DemandItem[i]) >= 1 then		
							local misIndex = GetQuestIndexByID(sceneId,selfId,x256226_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
								--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
						end
					end
					--x256226_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
					end
		  			
	 	end                                                                    
	     
end
--**********************************

function x256226_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256226_g_MissionId)
	  x256226_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
		--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )	
end
--**********************************
function x256226_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ�������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256226_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256226_g_BonusChoiceItem do
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
function x256226_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256226_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256226_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ռ䲻�㣬��������������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256226_g_MissionId) > 0 then
				x256226_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256226_g_MissionId)
				x256226_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256226_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256226_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256226_g_MissionIdNext )	
end

function x256226_GetBonus( sceneId, selfId,NpcID)
	  if x256226_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256226_g_ExpBonus);
  	end
		if x256226_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256226_g_BonusMoney1 )
	  end
		if x256226_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256226_g_BonusMoney2 )
	  end
		if x256226_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256226_g_BonusMoney3 )
		end
		if x256226_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256226_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256226_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256226_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256226_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256226_g_BonusMoney6)
		end
end

function x256226_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256226_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256226_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256226_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256226_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256226_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256226_g_MissionName.."��", 0, 3)
				if x256226_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256226_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256226_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256226_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256226_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256226_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256226_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256226_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256226_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256226_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256226_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256226_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256226_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256226_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256226_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256226_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256226_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256226_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256226_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId,optype)
	if	optype	==	0	then
		return
	end
	
	for i, item in x256226_g_DemandItem do
	
		if itemdataId == item then

			if GetItemCount(sceneId,selfId,item) >= 1 then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x256226_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
		  	else
		  			local misIndex = GetQuestIndexByID(sceneId,selfId,x256226_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		  	end
		  	
		  	break
	  	
	  	end
	  	
	end

end


function x256226_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256226_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256226_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256226_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256226_g_MissionId, state, -1 )
				if x256226_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,1 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
				end	
		end
end

function x256226_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256226_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256226_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256226_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256226_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256226_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end