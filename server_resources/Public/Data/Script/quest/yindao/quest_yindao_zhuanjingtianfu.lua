--ѯ��״��

--MisDescBegin
x203829_g_ScriptId = 203829
x203829_g_MissionIdPre = -1
x203829_g_MissionId = 4082
x203829_g_LevelLess	= 	80 
x203829_g_MissionIdNext = -1
x203829_g_Name	={}
x203829_g_ExtTarget={{type=20,n=1,target="��@npc_141103�����һ��ר��ѵ��"}}
x203829_g_MissionName="�����������޲���"
x203829_g_MissionInfo="\tѧϰר���츳֮������������������ҵ��˺���������ͽ�ר���������䵽����֮�ϰɡ�\n \n#GС��ʾ:#W\n\t1.ѧϰר���츳��Ҫ#R�츳�ȼ��ﵽ50������#W��\n\t2.ѧϰר���츳���������ר���츳��ʦ�Ի���ѡ��ר��ѵ������ר��������棬���Լ���ʣ��������䵽��Ӧְҵ�ϡ�"  --��������
x203829_g_MissionTarget=""		
x203829_g_MissionCompleted="\t�ܺã�����һ���õĿ�ʼ������ѧϰר���츳�Ļ������������ҵ��˺�����ߡ�"					--�������npc˵���Ļ�
x203829_g_ContinueInfo="\t�㲻�����Լ�����ǿ��������\n�츳�ȼ�����50���󣬿������ҽ���ר���츳ר��ѵ��������Լ���ĳһ�ض�ְҵ���˺���"
x203829_g_MissionHelp =	""
x203829_g_DemandItem ={}
x203829_g_ExpBonus = 500000
x203829_g_BonusMoney1 =800
x203829_g_BonusMoney2 =0
x203829_g_BonusMoney3 =0
x203829_g_BonusMoney4 =0
x203829_g_BonusMoney5 =90
x203829_g_BonusMoney6 =0
x203829_g_BonusItem	=	{}
x203829_g_BonusChoiceItem ={}
x203829_g_NpcGUID ={{ guid = 141103, name = "ר���츳��ʦ"} }
--MisDescEnd
--**********************************
-- ���ȼ�
x203829_g_MaxLevel      = 120

function x203829_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
     local level = GetLevel(sceneId, selfId)
	   if level < x203829_g_LevelLess or level >= x203829_g_MaxLevel then
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x203829_g_MissionId) > 0 then
		return 
	end

	if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) <= 0 then
		--if IsQuestHaveDone(sceneId, selfId, x203829_g_MissionIdPre) > 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x203829_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x203829_g_MissionId, state, -1 )
		end
	--end

end

function x203829_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203829_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203829_g_ExpBonus )
		end
		if x203829_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203829_g_BonusMoney1 )
		end
		if x203829_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203829_g_BonusMoney2 )
		end
		if x203829_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203829_g_BonusMoney3 )
		end
		if x203829_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203829_g_BonusMoney4 )
		end
		if x203829_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203829_g_BonusMoney5 )
		end
		if x203829_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203829_g_BonusMoney6 )
		end
		for i, item in x203829_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x203829_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x203829_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203829_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) > 0 then
			if x203829_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203829_g_MissionName)
				AddQuestText(sceneId,x203829_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x203829_g_ScriptId, x203829_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x203829_g_MissionName)
				AddQuestText(sceneId,x203829_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x203829_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203829_g_ScriptId, x203829_g_MissionId);
			end
  elseif x203829_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x203829_g_MissionName)
			AddQuestText(sceneId,x203829_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203829_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203829_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203829_g_MissionHelp )
			end
			x203829_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203829_g_ScriptId, x203829_g_MissionId);
  end
	
end
--**********************************

function x203829_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x203829_CheckSubmit( sceneId, selfId, NPCId)                                                 
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203829_g_MissionId)
	if GetQuestParam( sceneId, selfId, misIndex, 0) == 1 and GetQuestParam( sceneId, selfId, misIndex, 7) == 1 then
	    return 1
	else
	    return 0
	end
end

--**********************************
function x203829_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203829_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203829_g_MissionId  )
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
		
		if x203829_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203829_g_MissionId, x203829_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203829_Msg2toplayer( sceneId, selfId,0)
					--�ж�����Ѿ������ר��ϵ�� ��������Ϊ���
					local retComplete = GetQuestData( sceneId, selfId, MD_ZHUANGONG_COEFFICIENT[1], MD_ZHUANGONG_COEFFICIENT[2], MD_ZHUANGONG_COEFFICIENT[3] )
					if retComplete == 1 then
						local misidx = GetQuestIndexByID(sceneId,selfId,x203829_g_MissionId)
						SetQuestByIndex(sceneId,selfId,misidx,0,1)
						SetQuestByIndex(sceneId,selfId,misidx,7,1)
					end
				end
	 	end                                                                    
	     
end
--**********************************

function x203829_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203829_g_MissionId)
	  x203829_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203829_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203829_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x203829_g_BonusChoiceItem do
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
function x203829_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203829_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203829_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ռ䲻�㣬�������������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203829_g_MissionId) > 0 then
				x203829_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203829_g_MissionId)
				x203829_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203829_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x203829_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203829_g_MissionIdNext )	
end

function x203829_GetBonus( sceneId, selfId,NpcID)
	  if x203829_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203829_g_ExpBonus);
  	end
		if x203829_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203829_g_BonusMoney1 )
	  end
		if x203829_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203829_g_BonusMoney2 )
	  end
		if x203829_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203829_g_BonusMoney3 )
		end
		if x203829_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203829_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203829_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203829_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203829_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203829_g_BonusMoney6)
		end
end

function x203829_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203829_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203829_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203829_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203829_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203829_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203829_g_MissionName.."��", 0, 3)
				if x203829_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203829_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203829_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203829_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203829_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203829_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203829_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203829_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203829_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203829_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203829_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203829_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203829_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203829_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203829_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203829_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203829_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203829_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203829_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203829_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203829_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203829_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203829_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203829_g_MissionId, state, -1 )
		end
end

function x203829_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203829_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203829_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203829_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203829_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203829_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end