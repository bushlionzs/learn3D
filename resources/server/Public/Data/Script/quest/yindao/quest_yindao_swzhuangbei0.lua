--ѯ��״��

--MisDescBegin
x203758_g_ScriptId = 203758
x203758_g_MissionIdPre =4212
x203758_g_MissionId = 4216
x203758_g_LevelLess	= 	20
x203758_g_MissionIdNext = 2695
x203758_g_Name	={}
x203758_g_ExtTarget={{type=20,n=1,target="��@npc_123727���Ҵ���һ������װ"}}
x203758_g_MissionName="�����ˡ���һ������װ"
x203758_g_MissionInfo="\t�װ������ѣ����ҵ������кܶ�������װ��������Щ��װ��������������Ե�������\n\t��������̵��������#G��ȡ����������װ#c000000��ѡ������������װ���̵ꡣ������#G�����װ#c000000��ѡȡ��ϲ����һ��#G�Ҽ��������װ#c000000���������㹻������±�һ��ɹ���\n\t�������Ƽ������ȶһ�����������װ�еı���������㲻С�Ľ���װ�������ɵ���̵��е�#G�ع�#c000000�ٽ���װ��ء�"  --��������
x203758_g_MissionTarget=""		
x203758_g_MissionCompleted="\t���װ����Ȼ�����պ�ɳ�����������𵽲��ɵ͹������á�\n\tһ��Ҫ��ס���պ��ڻ���㹻��������������������һ�װ����"					--�������npc˵���Ļ�
x203758_g_ContinueInfo="\t�㲻��һ�һ��������װ��"
x203758_g_MissionHelp =	""
x203758_g_DemandItem ={10014001,10024001,10034001,10044001,10054001,10064001,10074001,10084001,10094001,10104001,10114001,10124001,10234001,10234011,10234021,10234031,10234041,10234051,10254001,10254011,10254021,10254031,10254041,10254051,10274001,10274011,10274021,10274031,10274041,10274051,10354001,10414001,10204061,10239218,10259218,10269218,10279218,10249218,10364001,10424001,10204071,10239222,10259222,10269222,10279222,10249222,10374001,10434001,10204081,10239226,10259226,10269226,10279226,10249226,10384001,10444001,10204091,10239230,10259230,10269230,10279230,10249230,10394001,10455001,10204101,10239234,10259234,10269234,10279234,10249234,10404001,10464001,10204111,10239238,10259238,10269238,10279238,10249238,10354001,10414001,10239218,10259218,10279218,10364001,10424001,10239222,10259222,10279222,10374001,10434001,10239226,10259226,10279226,10384001,10444001,10239230,10259230,10279230,10394001,10454001,10239234,10259234,10279234,10404001,10464001,10239238,10259238,10279238}
x203758_g_ExpBonus = 10200
x203758_g_BonusMoney1 =0
x203758_g_BonusMoney2 =0
x203758_g_BonusMoney3 =0
x203758_g_BonusMoney4 =0
x203758_g_BonusMoney5 =0
x203758_g_BonusMoney6 =0
x203758_g_BonusItem	=	{{item=11000200,n=5}}
x203758_g_BonusChoiceItem ={}
x203758_g_NpcGUID ={{ guid = 123727, name = "�����̵�"} }
--MisDescEnd
--**********************************
x203758_g_MaxLevel   = 40

function x203758_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x203758_g_LevelLess or level >= x203758_g_MaxLevel then
		return
	end



	if IsQuestHaveDone(sceneId, selfId, x203758_g_MissionId) > 0 then
		return 
	end
	
	if IsQuestHaveDone(sceneId, selfId, x203758_g_MissionIdPre)> 0 then 
	if IsHaveQuest(sceneId,selfId, x203758_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x203758_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x203758_g_MissionId, state, -1 )
	end
	end

end

function x203758_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203758_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203758_g_ExpBonus )
		end
		if x203758_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203758_g_BonusMoney1 )
		end
		if x203758_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203758_g_BonusMoney2 )
		end
		if x203758_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203758_g_BonusMoney3 )
		end
		if x203758_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203758_g_BonusMoney4 )
		end
		if x203758_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203758_g_BonusMoney5 )
		end
		if x203758_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203758_g_BonusMoney6 )
		end
		for i, item in x203758_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x203758_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x203758_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203758_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203758_g_MissionId) > 0 then
			if x203758_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203758_g_MissionName)
				AddQuestText(sceneId,x203758_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x203758_g_ScriptId, x203758_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203758_g_MissionName)
				AddQuestText(sceneId,x203758_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x203758_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203758_g_ScriptId, x203758_g_MissionId);
			end
  elseif x203758_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x203758_g_MissionName)
			AddQuestText(sceneId,x203758_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203758_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203758_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#c000000")
				AddQuestText(sceneId,x203758_g_MissionHelp )
			end
			x203758_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203758_g_ScriptId, x203758_g_MissionId);
  end
	
end
--**********************************

function x203758_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x203758_CheckSubmit( sceneId, selfId, NPCId)  
                                                  
		if  IsHaveQuest(sceneId, selfId,x203758_g_MissionId) ~=1 then
			return 0
		end
		
	   	local 	misIndex = GetQuestIndexByID(sceneId, selfId,x203758_g_MissionId)                                                  
	   	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	   		return 1
	   	else 
	   		return 0
	   	end
	   	
	
end

--**********************************
function x203758_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203758_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203758_g_MissionId  )
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
		
		if x203758_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then

					local retmiss = AddQuest( sceneId, selfId, x203758_g_MissionId, x203758_g_ScriptId, 0, 0, 1,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203758_Msg2toplayer( sceneId, selfId,0)
		  			
					for i, item in x203758_g_DemandItem do
						if GetItemCount(sceneId,selfId,x203758_g_DemandItem[i]) >= 1 then		
							local misIndex = GetQuestIndexByID(sceneId,selfId,x203758_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
								--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
						end
					end
					--x203758_ProcQuestItemChanged(sceneId, selfId, -1, MissionId)
					end
		  			
	 	end                                                                    
	     
end
--**********************************

function x203758_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203758_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203758_g_MissionId)
	  x203758_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
		--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )	
end
--**********************************
function x203758_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203758_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x203758_g_BonusChoiceItem do
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
function x203758_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203758_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203758_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203758_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ռ䲻�㣬�������������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203758_g_MissionId) > 0 then
				x203758_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203758_g_MissionId)
				x203758_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203758_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x203758_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203758_g_MissionIdNext )	
end

function x203758_GetBonus( sceneId, selfId,NpcID)
	  if x203758_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203758_g_ExpBonus);
  	end
		if x203758_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203758_g_BonusMoney1 )
	  end
		if x203758_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203758_g_BonusMoney2 )
	  end
		if x203758_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203758_g_BonusMoney3 )
		end
		if x203758_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203758_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203758_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203758_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203758_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203758_g_BonusMoney6)
		end
end

function x203758_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203758_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203758_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203758_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203758_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203758_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203758_g_MissionName.."��", 0, 3)
				if x203758_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203758_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203758_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203758_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203758_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203758_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203758_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203758_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203758_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203758_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203758_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203758_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203758_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203758_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203758_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203758_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203758_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203758_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203758_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId,optype)
	if	optype	==	0	then
		return
	end
	
	for i, item in x203758_g_DemandItem do
	
		if itemdataId == item then

			if GetItemCount(sceneId,selfId,item) >= 1 then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x203758_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,0 )
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
		  	else
		  			local misIndex = GetQuestIndexByID(sceneId,selfId,x203758_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		  	end
		  	
		  	break
	  	
	  	end
	  	
	end

end


function x203758_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203758_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203758_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203758_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203758_g_MissionId, state, -1 )
				if x203758_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 32,1 )
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 33,0 )
				end	
		end
end

function x203758_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203758_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203758_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203758_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203758_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203758_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end