--Ī˹�ƹ��� �������ɱ��

--MisDescBegin
x203325_g_ScriptId = 203325
x203325_g_MissionIdPre = 805
x203325_g_MissionId = 806
x203325_g_LevelLess	= 88
x203325_g_MissionIdNext = 807
x203325_g_DemandKill ={{id=2137,num=1}}
x203325_g_Name	={"Ī˹����̽"}
x203325_g_ExtTarget={{type=20,n=1,target="����@npc_117014"}}
x203325_g_MissionName="���糡��������Ů��<��>"
x203325_g_MissionInfo="\t�Ӹղ�����̸����ʱ���Ҿͷ���������һ������һֱ̽ͷ̽�ԣ��ƺ�����͵�����ǵ�̸�����������ҵ��ˣ��϶���Ī˹�ƴ����������ҵģ�ǧ��������й¶�����ǵ���Լ��"  --��������
x203325_g_MissionTarget="����@npc_117014"		
x203325_g_MissionCompleted="\t�治���Ǵ��ɹŹ�����ʿ�������¾���ʰ����������ӣ�ʣ�µ����齻���Һ��ˡ�"
x203325_g_ContinueInfo="\t��ô���Ǽһﲻ��Ī˹�ƴ󹫵�����ô��"
x203325_g_MissionHelp =	""
--x203325_g_DemandItem ={{id=13030081,num=1}}
x203325_g_ExpBonus =684000
x203325_g_BonusMoney1 =880
x203325_g_BonusMoney2 =0
x203325_g_BonusMoney3 =0
x203325_g_BonusMoney4 =0
x203325_g_BonusMoney5 =106
x203325_g_BonusMoney6 =0
x203325_g_BonusItem	={}
x203325_g_BonusChoiceItem ={}
x203325_g_NpcGUID = 117014
--x203325_g_Impact1 = 2092
x203325_g_npcid = 0
x203325_g_chaerke =0
x203325_g_dog =0
x203325_g_pangxie = 0
x203325_g_acceptid =0
--MisDescEnd
--**********************************

function x203325_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    --DelQuest(sceneId, selfId, x203325_g_MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionId) > 0 then
		return 
	else
	if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionIdPre)> 0 then 
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x203325_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x203325_g_MissionId, state, -1 )
	end
	end
end

function x203325_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203325_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203325_g_ExpBonus )
		end
		if x203325_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203325_g_BonusMoney1 )
		end
		if x203325_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203325_g_BonusMoney2 )
		end
		if x203325_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203325_g_BonusMoney3 )
		end
		if x203325_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203325_g_BonusMoney4 )
		end
		if x203325_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203325_g_BonusMoney5 )
		end
		if x203325_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203325_g_BonusMoney6 )
		end
		for i, item in x203325_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203325_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--������ں���

--**********************************
function x203325_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
    x203325_g_npcid =   NPCId
	if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203325_g_MissionId) > 0 then
			if x203325_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203325_g_MissionName)
						AddQuestText(sceneId,x203325_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203325_g_ScriptId, x203325_g_MissionId);
			else
          
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203325_g_MissionName)
						AddQuestText(sceneId,x203325_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203325_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203325_g_ScriptId, x203325_g_MissionId);
			end
  elseif x203325_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203325_g_MissionName)
			AddQuestText(sceneId,x203325_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203325_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203325_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203325_g_MissionHelp )
			end
			x203325_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203325_g_ScriptId, x203325_g_MissionId);
  end
end
--**********************************
function x203325_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionId) > 0 then
		return 0
	elseif GetLevel(sceneId, selfId)< x203325_g_LevelLess then
		return 0
	end
	return 1
end
--**********************************
function x203325_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203325_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == x203325_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	        return 1
	end
	return 0
end
--**********************************
function x203325_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203325_g_MissionId) > 0 then
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
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203325_g_MissionId  )
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
		
		if x203325_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		x203325_g_mitan =FindMonsterByGUID( sceneId,117014)
					local retmiss = AddQuest( sceneId, selfId, x203325_g_MissionId, x203325_g_ScriptId, 1, 0, 0)  --���һ�����񷵻ؽ��   --ɱ�� ��
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)                                         -- 3 ��ʾ�����0�ǣ�
						return 0
					else
						if IsObjValid (sceneId,x203325_g_mitan) == 1 then                                                       -- npc��Ч�����ڣ�
							--local x203325_g_liliang =FindMonsterByGUID( sceneId,117014)
			  			SetMonsterCamp(sceneId,x203325_g_mitan,21)
			  		end
            --CreateMonster(sceneId, 811,132,70,5,1,-1,-1,21,120000)
						x203325_Msg2toplayer( sceneId, selfId,0)
						--if x203325_CheckSubmit(sceneId, selfId, NPCId) > 0 then
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203325_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x203325_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203325_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203325_g_MissionId)
	  x203325_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x203325_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203325_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203325_g_BonusChoiceItem do
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
function x203325_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x203325_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203325_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203325_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203325_g_MissionId) > 0 then
				x203325_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203325_g_MissionId)
                x203325_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203325_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203325_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		    end
    		    EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203325_g_MissionIdNext )	
   end
end

function x203325_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
   
end

function x203325_GetBonus( sceneId, selfId,NpcID)
	  if x203325_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203325_g_ExpBonus);
  	end
		if x203325_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203325_g_BonusMoney1 )
	  end
		if x203325_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203325_g_BonusMoney2 )
	  end
		if x203325_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203325_g_BonusMoney3 )
		end
		if x203325_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203325_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203325_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203325_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203325_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203325_g_BonusMoney6)
		end
end

function x203325_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203325_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203325_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203325_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203325_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203325_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203325_g_MissionName.."��", 0, 3)
				if x203325_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203325_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203325_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203325_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203325_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203325_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203325_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203325_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203325_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203325_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203325_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203325_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203325_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203325_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

--**********************************

function x203325_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
   if	objdataId ==x203325_g_DemandKill[1].id then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,selfId, x203325_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,selfId,x203325_g_MissionId)
										if GetQuestParam(sceneId,selfId,misIndex,0) < 1 then
												SetQuestByIndex(sceneId,selfId,misIndex,0,GetQuestParam(sceneId,selfId,misIndex,0)+1)
												SetQuestByIndex(sceneId,selfId,misIndex,7,1)
												Msg2Player(sceneId, selfId, format("����Ī˹����̽  %d/1", GetQuestParam(sceneId,selfId,misIndex,0)), 0, 3)
												x203325_CheckSubmit( sceneId, selfId)
										end
                end
            end
		end
	end 
end
--**********************************
function x203325_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203325_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203325_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203325_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203325_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203325_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203325_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203325_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203325_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203325_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





