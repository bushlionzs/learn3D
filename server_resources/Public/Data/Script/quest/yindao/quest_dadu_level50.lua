--ѯ��״��

--MisDescBegin
x256299_g_ScriptId = 256299
x256299_g_MissionIdPre = -1
x256299_g_MissionId = 1600
x256299_g_LevelLess	= 	45 
x256299_g_MissionIdNext = -1
x256299_g_Name	={}
x256299_g_ExtTarget={{type=20,n=1,target="�������Ե�ָ��������50��"}}
x256299_g_MissionName="�����ˡ�Ŀ�꣺��ʮ��"
x256299_g_MissionInfo="\t��ã��װ������ѣ���������Щ��Ӧ��֪�������飺\n\tÿ���#G10��30����11��00#W��#G12��30����13��00#W��#G14��30����15��00#W��#G16��30����17��00#W��#G18��30����19��00#W��#G21��30����22��00#Wħ�����պ��ҵĲ������������#G���踮#W����ɱ���ǻ��ô������ֽ�����\n\t�󶼵�@npc_139100��@npc_139129��@npc_139133���ǻ���ÿ������#G19��30����24��00#W����������ɺ�ͻ��ø߶�ľ���ر���\n\tԽ����ҹ����Խ�Ǹ��ǣ�����#G23��00#W֮��ȥ�󶼵�@npc_139104�ĵ������棬���ɻ�ô������顣"  --��������
x256299_g_MissionTarget=""		
x256299_g_MissionCompleted="\t��ʮ����һ�������ĳɾͣ���Ҳ���µĿ�ʼ��\n\t������Ϊ��׼����һЩС���ϣ���ܶ������������������"					--�������npc˵���Ļ�
x256299_g_ContinueInfo="��̫�ļ�����Ϊ�����ʮ��׼���˲����������......��Ӧ���ȵ���ʮ��������"
x256299_g_MissionHelp =	""
x256299_g_DemandItem ={}
x256299_g_ExpBonus = 2000000
x256299_g_BonusMoney1 =150000
x256299_g_BonusMoney2 =0
x256299_g_BonusMoney3 =0
x256299_g_BonusMoney4 =0
x256299_g_BonusMoney5 =0
x256299_g_BonusMoney6 =0
x256299_g_BonusItem	=	{{item=12030253,n=1},{item=11060002,n=2}}
x256299_g_BonusChoiceItem ={}
x256299_g_NpcGUID ={{ guid = 140417, name = "������"} }
--MisDescEnd
--**********************************
-- ���ȼ�
x256299_g_MaxLevel      = 80

function x256299_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
     local level = GetLevel(sceneId, selfId)
	   if level < x256299_g_LevelLess or level >= x256299_g_MaxLevel then
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x256299_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x256299_g_MissionId) <= 0 then
		--if IsQuestHaveDone(sceneId, selfId, x256299_g_MissionIdPre) > 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256299_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256299_g_MissionId, state, -1 )
		end
	--end

end

function x256299_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256299_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256299_g_ExpBonus )
		end
		if x256299_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256299_g_BonusMoney1 )
		end
		if x256299_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256299_g_BonusMoney2 )
		end
		if x256299_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256299_g_BonusMoney3 )
		end
		if x256299_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256299_g_BonusMoney4 )
		end
		if x256299_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256299_g_BonusMoney5 )
		end
		if x256299_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256299_g_BonusMoney6 )
		end
		for i, item in x256299_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x256299_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x256299_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256299_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256299_g_MissionId) > 0 then
			if x256299_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256299_g_MissionName)
				AddQuestText(sceneId,x256299_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x256299_g_ScriptId, x256299_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256299_g_MissionName)
				AddQuestText(sceneId,x256299_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x256299_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256299_g_ScriptId, x256299_g_MissionId);
			end
  elseif x256299_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x256299_g_MissionName)
			AddQuestText(sceneId,x256299_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256299_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256299_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256299_g_MissionHelp )
			end
			x256299_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256299_g_ScriptId, x256299_g_MissionId);
  end
	
end
--**********************************

function x256299_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x256299_CheckSubmit( sceneId, selfId, NPCId)                                                 
	if GetLevel(sceneId, selfId)>= 50 then
	   return 1
	end
	 
	return 0
	
end

--**********************************
function x256299_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256299_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256299_g_MissionId  )
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
		
		if x256299_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256299_g_MissionId, x256299_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256299_Msg2toplayer( sceneId, selfId,0)
					if GetLevel(sceneId, selfId) >= 50 then
						local misIndex = GetQuestIndexByID(sceneId,selfId,x256299_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256299_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256299_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256299_g_MissionId)
	  x256299_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256299_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ�������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256299_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x256299_g_BonusChoiceItem do
        if item.item == selectRadioId then
            AddBindItem( sceneId, item.item, item.n )
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
function x256299_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256299_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256299_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256299_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ռ䲻�㣬��������������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256299_g_MissionId) > 0 then
				x256299_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256299_g_MissionId)
				x256299_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256299_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256299_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256299_g_MissionIdNext )	
end

function x256299_GetBonus( sceneId, selfId,NpcID)
	  if x256299_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256299_g_ExpBonus);
  	end
		if x256299_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256299_g_BonusMoney1 )
	  end
		if x256299_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256299_g_BonusMoney2 )
	  end
		if x256299_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256299_g_BonusMoney3 )
		end
		if x256299_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256299_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256299_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256299_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256299_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256299_g_BonusMoney6)
		end
end

function x256299_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256299_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256299_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256299_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256299_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256299_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256299_g_MissionName.."��", 0, 3)
				if x256299_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256299_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256299_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256299_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256299_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256299_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256299_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256299_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256299_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256299_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256299_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256299_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256299_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256299_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256299_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256299_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256299_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256299_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256299_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256299_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256299_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256299_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256299_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256299_g_MissionId, state, -1 )
		end
end

function x256299_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256299_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256299_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256299_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256299_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256299_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end