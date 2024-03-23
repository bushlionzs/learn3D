--�����ߡ����ַ粨<��>

--MisDescBegin
x270004_g_ScriptId = 270004
x270004_g_MissionIdPre =3562
x270004_g_MissionId = 3568
x270004_g_LevelLess	= 	50 
x270004_g_MissionIdNext = 3569
x270004_g_Name	={}
x270004_g_ExtTarget={{type=20,n=1,target="����@npcsp_��ؤ_136281�õ���֤"}}
x270004_g_MissionName="�����ߡ����ַ粨<��>"
x270004_g_MissionInfo="\t������ʦ̫������������˱�������ͷ����˵����\n\t���ű��ɳ����µļ�������ȷʵ�ܾ�δ�飬��Ҳ�������ұ��˴󶼸�������û�з��ֵ��ӵ����١�\n\t��ؤ�����е����ɱ��������������ԨԴ���������û�в����֮ǰ�������ԩ�����ǡ�\n\t����������������һ�ˣ������Ƿ��ܴ��Ǽ�����ؤ�����ҵ�ʲô������"  --��������
x270004_g_MissionTarget=""		
x270004_g_MissionCompleted="\t������ʦ̫������߬��������ʯ��������ɫ�Ǻ죬�������ؿ������Լ������Σ���˵����\n\t�⡭�����⣬���Ҷ�ü��ɽ���桰С��а��������ʦ��ؤ�����ΰ������Ǿ��ұ����Ĺ�����֮�����ɵ�ԨԴ���Ϊ����������µ��ӣ�����ƶ�ᶨҪ�����ʸ����ף�"					--�������npc˵���Ļ�
x270004_g_ContinueInfo="\t����Ϣ����"
x270004_g_MissionHelp =	""
x270004_g_DemandItem ={{id=13020312,num=1}}
x270004_g_BonusMoney1 =376
x270004_g_BonusMoney2 =0
x270004_g_BonusMoney3 =0
x270004_g_BonusMoney4 =0
x270004_g_BonusMoney5 =61
x270004_g_BonusMoney6 =0
x270004_g_BonusItem	=	{}
x270004_g_BonusChoiceItem ={}
x270004_g_ExpBonus = 145000
x270004_g_NpcGUID ={{ guid = 136281, name = "��ؤ��"},{ guid = 136282, name = "��ؤ��"} }
--MisDescEnd
--**********************************

function x270004_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270004_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270004_g_MissionId, state, -1 )
	end
end

function x270004_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270004_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270004_g_ExpBonus )
		end
		if x270004_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270004_g_BonusMoney1 )
		end
		if x270004_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270004_g_BonusMoney2 )
		end
		if x270004_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270004_g_BonusMoney3 )
		end
		if x270004_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270004_g_BonusMoney4 )
		end
		if x270004_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270004_g_BonusMoney5 )
		end
		if x270004_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270004_g_BonusMoney6 )
		end
		for i, item in x270004_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270004_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270004_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionId) > 0 then
		return 
	end
	if which == -1 then
		if IsHaveQuest(sceneId,selfId, x270004_g_MissionId) > 0 then
			if x270004_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270004_g_MissionName)
						AddQuestText(sceneId,x270004_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270004_g_ScriptId, x270004_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270004_g_MissionName)
						AddQuestText(sceneId,x270004_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270004_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270004_g_ScriptId, x270004_g_MissionId);
			end
		elseif x270004_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270004_g_MissionName)
			AddQuestText(sceneId,x270004_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270004_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270004_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270004_g_MissionHelp )
			end
			x270004_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270004_g_ScriptId, x270004_g_MissionId);
  	end
	else
			local liu = FindMonsterByGUID( sceneId,136281)
			local zhang = FindMonsterByGUID( sceneId,136282)
			if IsObjValid (sceneId,liu) == 1 then
			SetMonsterCamp(sceneId,liu,21)
			end
			if IsObjValid (sceneId,zhang) == 1 then
			SetMonsterCamp(sceneId,zhang,21)
			end
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"������ؤͻȻ����������˹�����")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x270004_g_ScriptId, x270004_g_MissionId);
	end
  
end
--**********************************

function x270004_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270004_CheckSubmit( sceneId, selfId, NPCId)
		if GetItemCount(sceneId,selfId,x270004_g_DemandItem[1].id) >= x270004_g_DemandItem[1].num then
				local misIndex = GetQuestIndexByID(sceneId,selfId,x270004_g_MissionId)
				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    	SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	      return 1
	  else
	  		local misIndex = GetQuestIndexByID(sceneId,selfId,x270004_g_MissionId)
				SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    	SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
end
--**********************************
function x270004_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270004_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270004_g_MissionId  )
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
		if x270004_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270004_g_MissionId, x270004_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270004_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270004_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270004_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270004_g_MissionId)
	  x270004_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270004_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
end
--**********************************
function x270004_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270004_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270004_g_BonusChoiceItem do
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
function x270004_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270004_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270004_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270004_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270004_g_MissionId) > 0 then
				x270004_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270004_g_MissionId)
				x270004_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270004_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270004_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x270004_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270004_g_MissionIdNext )	
end

function x270004_GetBonus( sceneId, selfId,NpcID)
	  if x270004_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270004_g_ExpBonus);
  	end
		if x270004_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270004_g_BonusMoney1 )
	  end
		if x270004_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270004_g_BonusMoney2 )
	  end
		if x270004_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270004_g_BonusMoney3 )
		end
		if x270004_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270004_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270004_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270004_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270004_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270004_g_BonusMoney6)
		end
end

function x270004_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270004_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270004_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270004_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270004_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270004_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270004_g_MissionName.."��", 0, 3)
				if x270004_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270004_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270004_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270004_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270004_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270004_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270004_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270004_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270004_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270004_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270004_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270004_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270004_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270004_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270004_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==3820 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
            if humanObjId ~= -1 then
                if IsHaveQuest(sceneId,humanObjId, x270004_g_MissionId) > 0 then
                    if GetItemCount(sceneId,humanObjId,x270004_g_DemandItem[1].id) < x270004_g_DemandItem[1].num then
                                BeginAddItem(sceneId)
                                AddItem( sceneId, x270004_g_DemandItem[1].id, x270004_g_DemandItem[1].num )
                                local ret = EndAddItem(sceneId,humanObjId)
                                if ret > 0 then
                                    AddItemListToPlayer(sceneId,humanObjId)
                                    x270004_CheckSubmit( sceneId, humanObjId, 0)
                                    Msg2Player(sceneId, humanObjId, "�õ���#G�������#Y   1/1", 0, 3)
                                else
                                    BeginQuestEvent(sceneId)
                                    AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
                                    EndQuestEvent(sceneId)
                                    DispatchQuestTips(sceneId,humanObjId)
                                end
                    end
                end
            end
		end
	end
end


function x270004_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270004_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270004_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270004_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270004_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270004_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270004_g_MissionId) > 0 then
				AddQuestNumText(sceneId, x270004_g_MissionId, "����������ɵ�Ů������",0, 1)
		end
end

function x270004_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270004_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270004_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270004_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270004_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270004_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
