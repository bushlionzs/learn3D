--�����ߡ�����Ԫ��<һ>

--MisDescBegin
x270007_g_ScriptId = 270007
x270007_g_MissionIdPre =3573
x270007_g_MissionId = 3574
x270007_g_LevelLess	= 	50 
x270007_g_MissionIdNext = -1
x270007_g_Name	={}
x270007_g_ExtTarget={{type=20,n=8,target="ɱ����ðɮ�˵���ħ��ͽ"}}
x270007_g_MissionName="�����ߡ�����Ԫ��<һ>"
x270007_g_MissionInfo="\t��ħ�̵Ľ��������ˣ������ڻ��������ħ�̵���Ǳ�������С�Ҫ�����ҵ���������ǣ����������鷳��������Щ��ɮ��Ӧ�ò���𾭣��������˵��ɫ���ǿա�������ܽӳ��¾䣬��˵��������ɮ�ˡ�"  --��������
x270007_g_MissionTarget=""		
x270007_g_MissionCompleted="\t�벻���̶�ʱ�������оͻ����������յĽ��ɡ�"					--�������npc˵���Ļ�
x270007_g_ContinueInfo="\t˵��������������ɱ������Ҫ��ԥ��"
x270007_g_MissionHelp =	"���������Զ�Ѱ·������ݾ�������ɴ�����"
x270007_g_DemandItem ={}
x270007_g_BonusMoney1 =376
x270007_g_BonusMoney2 =0
x270007_g_BonusMoney3 =0
x270007_g_BonusMoney4 =0
x270007_g_BonusMoney5 =61
x270007_g_BonusMoney6 =0
x270007_g_BonusItem	=	{}
x270007_g_BonusChoiceItem ={}
x270007_g_ExpBonus = 145000
x270007_g_NpcGUID ={{ guid = 136251, name = "�����ɮ��"},{ guid = 136252, name = "�����ɮ��"} }
--MisDescEnd
--**********************************

function x270007_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270007_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270007_g_MissionId, state, -1 )
	end
end

function x270007_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270007_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270007_g_ExpBonus )
		end
		if x270007_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270007_g_BonusMoney1 )
		end
		if x270007_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270007_g_BonusMoney2 )
		end
		if x270007_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270007_g_BonusMoney3 )
		end
		if x270007_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270007_g_BonusMoney4 )
		end
		if x270007_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270007_g_BonusMoney5 )
		end
		if x270007_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270007_g_BonusMoney6 )
		end
		for i, item in x270007_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270007_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270007_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionId) > 0 then
		return 
	end
	if which == -1 then
		if IsHaveQuest(sceneId,selfId, x270007_g_MissionId) > 0 then
			if x270007_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270007_g_MissionName)
						AddQuestText(sceneId,x270007_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270007_g_MissionName)
						AddQuestText(sceneId,x270007_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270007_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
			end
		elseif x270007_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270007_g_MissionName)
			AddQuestText(sceneId,x270007_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270007_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270007_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270007_g_MissionHelp )
			end
			x270007_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
  	end
	elseif which == 1 then
			SetMonsterCamp(sceneId,NPCId,21)
			NpcTalk(sceneId, NPCId, "ɫ�����ͷ��ɫ��ô���ǿգ�", -1)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t����ͻȻ¶��һ���׶�����������������")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
	elseif which == 2 then
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"\t��ʩ���¾��ǡ��ռ���ɫ��")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x270007_g_ScriptId, x270007_g_MissionId);
	end
  
end
--**********************************

function x270007_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270007_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270007_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) >= 8 then
					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	    end
	 		return 0
end
--**********************************
function x270007_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270007_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270007_g_MissionId  )
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
		if x270007_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270007_g_MissionId, x270007_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270007_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270007_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270007_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270007_g_MissionId)
	  x270007_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270007_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
end
--**********************************
function x270007_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270007_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270007_g_BonusChoiceItem do
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
function x270007_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270007_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270007_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270007_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270007_g_MissionId) > 0 then
				x270007_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270007_g_MissionId)
				x270007_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270007_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270007_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x270007_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270007_g_MissionIdNext )	
end

function x270007_GetBonus( sceneId, selfId,NpcID)
	  if x270007_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270007_g_ExpBonus);
  	end
		if x270007_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270007_g_BonusMoney1 )
	  end
		if x270007_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270007_g_BonusMoney2 )
	  end
		if x270007_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270007_g_BonusMoney3 )
		end
		if x270007_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270007_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270007_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270007_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270007_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270007_g_BonusMoney6)
		end
end

function x270007_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270007_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270007_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270007_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270007_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270007_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270007_g_MissionName.."��", 0, 3)
				if x270007_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270007_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270007_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270007_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270007_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270007_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270007_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270007_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270007_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270007_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270007_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270007_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270007_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270007_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270007_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==3801 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x270007_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x270007_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 8 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("ɱ����ðɮ��   %d/8", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x270007_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end


function x270007_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270007_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270007_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270007_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270007_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270007_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270007_g_MissionId) > 0 then
				AddQuestNumText(sceneId, x270007_g_MissionId, "ɫ���ǿ�",0, 1)
		end
end

function x270007_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270007_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270007_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270007_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270007_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270007_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
