-- �����ˡ�Ѱ����ʦ

--MisDescBegin
x203790_g_ScriptId = 203790
x203790_g_MissionIdPre =3660
x203790_g_MissionId = 4260
x203790_g_LevelLess	= 	20
x203790_g_MissionIdNext = {4264,4265,4266,4267,4268,4269,4270,4271,4272,4273,4274,4275}
x203790_g_Name	={}
x203790_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_123726"}}
x203790_g_MissionName="�����ˡ�Ѱ����ʦ"
x203790_g_MissionInfo="\t���Ƿ�������������ٶȱ����ˣ�����������кܶ಻��ĵط������ڵ�����Ҫһλʦ����������ӿ��ٵ�������\n\tȥ��@npc_123726�ɣ���������ҵ������ʦ����"  --��������
x203790_g_MissionTarget=""		
x203790_g_MissionCompleted="\t����Ҫһλ������ʦ����û���⣬���ҵİ����£�һ��������Ը�� "					--�������npc˵���Ļ�
x203790_g_ContinueInfo=""
x203790_g_MissionHelp =	""
x203790_g_DemandItem ={}
x203790_g_ExpBonus = 1500
x203790_g_BonusMoney1 =258
x203790_g_BonusMoney2 =0
x203790_g_BonusMoney3 =0
x203790_g_BonusMoney4 =0
x203790_g_BonusMoney5 =37
x203790_g_BonusMoney6 =0
x203790_g_BonusItem	=	{}
x203790_g_BonusChoiceItem ={}
x203790_g_NpcGUID ={{ guid = 123726, name = "ʦͽ����Ա"} }
--MisDescEnd     
x203790_g_ScriptIdNext =203701
--**********************************

function x203790_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	local level = GetLevel( sceneId, selfId)
	if IsQuestHaveDone(sceneId, selfId, x203790_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203790_g_MissionIdPre)> 0 then
			local bHaveMission = IsHaveQuestNM(sceneId,selfId, x203790_g_MissionId)	
			if (  bHaveMission <= 0 and level >= x203790_g_LevelLess ) then						
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x203790_g_MissionId)
				AddQuestTextNM( sceneId, selfId, NPCId, x203790_g_MissionId, state, -1 )
				 --CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,1 ) 		
			end
	end
		
end

function x203790_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203790_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203790_g_ExpBonus )
		end
		if x203790_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203790_g_BonusMoney1 )
		end
		if x203790_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203790_g_BonusMoney2 )
		end
		if x203790_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203790_g_BonusMoney3 )
		end
		if x203790_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203790_g_BonusMoney4 )
		end
		if x203790_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203790_g_BonusMoney5 )
		end
		if x203790_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203790_g_BonusMoney6 )
		end
		for i, item in x203790_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203790_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203790_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203790_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203790_g_MissionId) > 0 then
			if x203790_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203790_g_MissionName)
						AddQuestText(sceneId,x203790_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203790_g_ScriptId, x203790_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203790_g_MissionName)
						AddQuestText(sceneId,x203790_g_MissionCompleted)
						AddQuestText(sceneId," ")
						--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1 )  
						x203790_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )  
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203790_g_ScriptId, x203790_g_MissionId);
			end
  elseif x203790_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203790_g_MissionName)
			AddQuestText(sceneId,x203790_g_MissionInfo)
			AddQuestText( sceneId,"\n#Y����Ŀ�꣺") 		  
			for i, item in x203790_g_ExtTarget do  	
			AddQuestText( sceneId,item.target)		
			end 
			if x203790_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203790_g_MissionHelp )
			end
			x203790_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203790_g_ScriptId, x203790_g_MissionId);
			--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,0 )
			--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 ) 	
  end
	
end
--**********************************

function x203790_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203790_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203790_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203790_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203790_g_MissionId  )
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
		if x203790_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203790_g_MissionId, x203790_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then                                          ------���ʧ�� ==0 ��1 �ɹ�                                                                  
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203790_Msg2toplayer( sceneId, selfId,0)
						--if x203790_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203790_g_MissionId)       ---- ȡ������״̬                                               
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)                                 ---0��1 ���� 0/1
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)                                 ---7,1  ������״̬��Ϊ���
	    					--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )   
	    					--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 )   
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203790_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203790_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203790_g_MissionId)
	  x203790_Msg2toplayer( sceneId, selfId,1) 
			
end
--**********************************
function x203790_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203790_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203790_g_BonusChoiceItem do
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
function x203790_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203790_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203790_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203790_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203790_g_MissionId) > 0 then
				x203790_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203790_g_MissionId)
				x203790_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203790_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203790_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   local zhiye =GetZhiye( sceneId, selfId)+1
   CallScriptFunction( x203790_g_ScriptIdNext, "ProcEventEntry", sceneId, selfId, NPCId, x203790_g_MissionIdNext[zhiye] )	
end

function x203790_GetBonus( sceneId, selfId,NpcID)
	  if x203790_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203790_g_ExpBonus);
  	end
		if x203790_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203790_g_BonusMoney1 )
	  end
		if x203790_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203790_g_BonusMoney2 )
	  end
		if x203790_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203790_g_BonusMoney3 )
		end
		if x203790_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203790_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203790_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203790_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203790_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203790_g_BonusMoney6)
		end
end

function x203790_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203790_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203790_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203790_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203790_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203790_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203790_g_MissionName.."��", 0, 3)
				if x203790_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203790_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203790_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203790_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203790_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203790_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203790_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203790_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203790_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203790_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203790_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203790_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203790_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203790_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203790_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203790_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203790_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203790_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203790_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203790_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203790_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203790_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203790_g_MissionId)        ---ȡ������״̬ ������״̬��Ӱ�ť AddQuestTextNM
				AddQuestTextNM( sceneId, selfId, npcId, x203790_g_MissionId, state, -1 )
		end
end

function x203790_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203790_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203790_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203790_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203790_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203790_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end