--���糡����ͷ����

--MisDescBegin
x203311_g_ScriptId = 203311
x203311_g_MissionIdPre ={613,614,615}
x203311_g_MissionId = 619
x203311_g_LevelLess	= 	65 
x203311_g_MissionIdNext = 621
x203311_g_Name	={}
x203311_g_ExtTarget={{type=20,n=1,target="��@npc_113120���г�������@npc_113115"}}
x203311_g_MissionName="���糡����ͷħ��"
x203311_g_MissionInfo="\t̫���ˣ����ˮ����֮�궼�Ѿ��õ��ˣ�ֻҪ�����Ƿ���һ��ͻ��Զ��ںϳ���֮������������֮�����������濪���ش��ٻ�������ħ����������û����ȫ�ָ�����֮ǰ�����������죡"  --��������
x203311_g_MissionTarget=""		
x203311_g_MissionCompleted="\t̫���ˣ����ڳ�������ͷħ����ϣ�������챣������أ����ƽ�����¡�"					--�������npc˵���Ļ�
x203311_g_ContinueInfo="\t����������ͷħ����"
x203311_g_MissionHelp =	""
x203311_g_DemandItem ={{id=13020433,num=1}}
x203311_g_ExpBonus = 248000
x203311_g_BonusMoney1 =650
x203311_g_BonusMoney2 =0
x203311_g_BonusMoney3 =0
x203311_g_BonusMoney4 =0
x203311_g_BonusMoney5 =76
x203311_g_BonusMoney6 =0
x203311_g_BonusItem	=	{}
x203311_g_BonusChoiceItem ={}

x203311_g_NpcGUID ={ }
x203311_g_long = -1
--MisDescEnd
--**********************************

function x203311_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[1])> 0  and IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[2])> 0  and IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[3])> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203311_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203311_g_MissionId, state, -1 )
	end
end

function x203311_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203311_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203311_g_ExpBonus )
		end
		if x203311_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203311_g_BonusMoney1 )
		end
		if x203311_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203311_g_BonusMoney2 )
		end
		if x203311_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203311_g_BonusMoney3 )
		end
		if x203311_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203311_g_BonusMoney4 )
		end
		if x203311_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203311_g_BonusMoney5 )
		end
		if x203311_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203311_g_BonusMoney6 )
		end
		for i, item in x203311_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203311_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203311_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionId) > 0 then
		return 
	end
	if which == -1 then
		if IsHaveQuest(sceneId,selfId, x203311_g_MissionId) > 0 then
			if x203311_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203311_g_MissionName)
						AddQuestText(sceneId,x203311_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203311_g_ScriptId, x203311_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203311_g_MissionName)
						AddQuestText(sceneId,x203311_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203311_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203311_g_ScriptId, x203311_g_MissionId);
			end
		elseif x203311_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203311_g_MissionName)
			AddQuestText(sceneId,x203311_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203311_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203311_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203311_g_MissionHelp )
			end
			x203311_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203311_g_ScriptId, x203311_g_MissionId);
  	end
  end
  
end
--**********************************

function x203311_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[1])> 0 then
			if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[2])> 0 then
			if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionIdPre[3])> 0 then
					return 1
			end
		end
		end
		return 0

end
--**********************************
function x203311_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203311_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) >= 1 then
					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		return 1
	    end
	 		return 0
end
--**********************************
function x203311_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203311_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203311_g_MissionId  )
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
		if x203311_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x203311_g_DemandItem[1].id, x203311_g_DemandItem[1].num )             
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x203311_g_MissionId, x203311_g_ScriptId, 1, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203311_Msg2toplayer( sceneId, selfId,0)
						AddItemListToPlayer(sceneId,selfId) 
		  		end
	  		else                                                             
		  		BeginQuestEvent(sceneId)                                      
		  		AddQuestText(sceneId,"��Ʒ����������������������")                    
		  		EndQuestEvent(sceneId)                                        
		  		DispatchQuestTips(sceneId,selfId)                      
	   		end        
	 	end                                                                    
	     
end
--**********************************

function x203311_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203311_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203311_g_MissionId)
	  x203311_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x203311_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
end
--**********************************
function x203311_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203311_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203311_g_BonusChoiceItem do
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
function x203311_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203311_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203311_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203311_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203311_g_MissionId) > 0 then
				x203311_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203311_g_MissionId)
				x203311_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203311_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203311_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x203311_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203311_g_MissionIdNext )	
end

function x203311_GetBonus( sceneId, selfId,NpcID)
	  if x203311_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203311_g_ExpBonus);
  	end
		if x203311_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203311_g_BonusMoney1 )
	  end
		if x203311_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203311_g_BonusMoney2 )
	  end
		if x203311_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203311_g_BonusMoney3 )
		end
		if x203311_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203311_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203311_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203311_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203311_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203311_g_BonusMoney6)
		end
end

function x203311_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203311_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203311_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203311_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203311_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203311_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203311_g_MissionName.."��", 0, 3)
				if x203311_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203311_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203311_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203311_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203311_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203311_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203311_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203311_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203311_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203311_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203311_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203311_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203311_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203311_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203311_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==1714 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x203311_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x203311_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 1 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("��������ͷħ��   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x203311_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end

function x203311_useitem(sceneId,selfId)
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203311_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,1) == 0 then
				local distanceRet = 25 - (169 - PlayerPosX) * (169 - PlayerPosX) - (221 - PlayerPosZ) * (221 - PlayerPosZ)
				if distanceRet >= 0 then
					if IsObjValid (sceneId,x203311_g_long) == 0 then
							DelItem( sceneId,selfId,x203311_g_DemandItem[1].id, x203311_g_DemandItem[1].num )
							x203311_g_long=CreateMonster(sceneId, 1714,169,221,5,1,-1,-1,21,180000,45,"��ͷħ��")
							return 1
					elseif IsObjValid (sceneId,x203311_g_long) == 1 then
							if GetName(sceneId,x203311_g_long)~="��ͷħ��" then
									DelItem( sceneId,selfId,x203311_g_DemandItem[1].id, x203311_g_DemandItem[1].num )
									x203311_g_long=CreateMonster(sceneId, 1714,169,221,5,1,-1,-1,21,180000,45,"��ͷħ��")
									return 1
							end
					else
							Msg2Player(sceneId, selfId, "����ʱ�޷���������", 0, 3)
					end
				else
						Msg2Player(sceneId, selfId, "�����޷�ʹ�������Ʒ", 0, 3)
						return 0
				end
		end
end


function x203311_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203311_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203311_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203311_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203311_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	 
end

function x203311_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203311_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203311_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203311_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203311_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203311_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
