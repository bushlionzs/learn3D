--�����ߡ����˼�<��>

--MisDescBegin
x270011_g_ScriptId = 270011
x270011_g_MissionIdPre =3505
x270011_g_MissionId = 3506
x270011_g_LevelLess	= 	45 
x270011_g_MissionIdNext = 3507
x270011_g_Name	={}
x270011_g_ExtTarget={{type=20,n=1,target="��@npc_141011���ȴ���������ɻ�������ɱ����ɻ�"}}
x270011_g_MissionName="�����ߡ����˼�<��>"
x270011_g_MissionInfo="\t�ã�������������£����������·�ǰȥ����Ӫ���������Ƿɻ�Уξ������ʣ�µ��¾Ϳ���ʿ����æ�ˡ�"  --��������
x270011_g_MissionTarget=""		
x270011_g_MissionCompleted="\t�벻������һ��������������������ͺ͵�����"					--�������npc˵���Ļ�
x270011_g_ContinueInfo="\t��ƻ������𣿻�����ݺݺ���ܰɣ�"
x270011_g_MissionHelp =	""
x270011_g_DemandItem ={}
x270011_g_BonusMoney1 =376
x270011_g_BonusMoney2 =0
x270011_g_BonusMoney3 =0
x270011_g_BonusMoney4 =0
x270011_g_BonusMoney5 =56
x270011_g_BonusMoney6 =0
x270011_g_BonusItem	=	{}
x270011_g_BonusChoiceItem ={}
x270011_g_ExpBonus = 112000
x270011_g_doing = 0
x270011_g_sunfeihu = -1
x270011_g_zhangsheng = -1
x270011_g_huwei1 = -1
x270011_g_huwei2 = -1
x270011_g_NpcGUID ={{ guid = 140401, name = "��ĸ"}}
x270011_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--MisDescEnd
--**********************************

function x270011_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270011_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270011_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x270011_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270011_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270011_g_MissionId, state, -1 )
		end
	end
end

function x270011_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270011_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270011_g_ExpBonus )
		end
		if x270011_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270011_g_BonusMoney1 )
		end
		if x270011_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270011_g_BonusMoney2 )
		end
		if x270011_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270011_g_BonusMoney3 )
		end
		if x270011_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270011_g_BonusMoney4 )
		end
		if x270011_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270011_g_BonusMoney5 )
		end
		if x270011_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270011_g_BonusMoney6 )
		end
		for i, item in x270011_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270011_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270011_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270011_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270011_g_MissionId) > 0 then
			if x270011_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270011_g_MissionName)
						AddQuestText(sceneId,x270011_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270011_g_ScriptId, x270011_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270011_g_MissionName)
						AddQuestText(sceneId,x270011_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270011_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270011_g_ScriptId, x270011_g_MissionId);
			end
  elseif x270011_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270011_g_MissionName)
			AddQuestText(sceneId,x270011_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270011_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270011_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270011_g_MissionHelp )
			end
			x270011_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270011_g_ScriptId, x270011_g_MissionId);
  end
	
end
--**********************************

function x270011_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270011_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270011_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270011_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
	
end
--**********************************
function x270011_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270011_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270011_g_MissionId  )
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
		if x270011_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270011_g_MissionId, x270011_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270011_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270011_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270011_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270011_g_MissionId)
	  x270011_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x270011_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270011_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270011_g_BonusChoiceItem do
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
function x270011_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270011_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270011_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270011_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270011_g_MissionId) > 0 then
				x270011_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270011_g_MissionId)
				x270011_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270011_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270011_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270011_g_MissionIdNext )	
end

function x270011_GetBonus( sceneId, selfId,NpcID)
	  if x270011_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270011_g_ExpBonus);
  	end
		if x270011_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270011_g_BonusMoney1 )
	  end
		if x270011_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270011_g_BonusMoney2 )
	  end
		if x270011_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270011_g_BonusMoney3 )
		end
		if x270011_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270011_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270011_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270011_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270011_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270011_g_BonusMoney6)
		end
end

function x270011_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270011_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270011_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270011_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270011_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270011_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270011_g_MissionName.."��", 0, 3)
				if x270011_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270011_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270011_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270011_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270011_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270011_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270011_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270011_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270011_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270011_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270011_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270011_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270011_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270011_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270011_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==1617 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x270011_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x270011_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 1 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												SetQuestByIndex(sceneId,humanObjId,misIndex,7,1)
												Msg2Player(sceneId, humanObjId, format("ɱ����ɻ�   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x270011_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end


function x270011_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
		if IsHaveQuest(sceneId,selfId, x270011_g_MissionId) > 0 then
			if x270011_g_doing == 0 then
				if x270011_CheckSubmit(sceneId, selfId) <= 0 then
					--if GetName(sceneId,x270011_g_sunfeihu)~="��ɻ�" then
							x270011_g_PROTECTINFO.StartTime = GetCurrentTime()
							x270011_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270011, "OnScneneTimer", 1)
							if x270011_g_PROTECTINFO.ScneneTimerIndex >= 0 then
									x270011_g_doing = 1
									x270011_g_sunfeihu=CreateMonster(sceneId, 1617,155,475,5,1,-1,-1,20,80000,180,"��ɻ�")
									x270011_g_huwei1=CreateMonster(sceneId, 1618,151,477,3,1,-1,-1,20,80000,180,"����")
									x270011_g_huwei2=CreateMonster(sceneId, 1618,151,473,3,1,-1,-1,20,80000,180,"����")
									if IsObjValid (sceneId,x270011_g_sunfeihu) == 1 then
											SetPatrolId(sceneId, x270011_g_sunfeihu, 49)
									end
									if IsObjValid (sceneId,x270011_g_huwei1) == 1 then
											SetPatrolId(sceneId, x270011_g_huwei1, 50)
									end
									if IsObjValid (sceneId,x270011_g_huwei2) == 1 then
											SetPatrolId(sceneId, x270011_g_huwei2, 51)
									end
							end
					--end
				end
			end
		end

end

function x270011_ProcTiming(sceneId, selfId, ScriptId, MissionId)
end

function x270011_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

function x270011_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270011_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270011_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270011_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x270011_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x270011_g_MissionId, state, -1 )
		end
end

function x270011_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270011_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270011_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270011_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270011_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270011_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270011_OnScneneTimer(sceneId)
	if x270011_g_doing==1   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 3   then
						x270011_g_doing = 2
						if IsObjValid (sceneId,x270011_g_sunfeihu) == 1 then
								NpcTalk(sceneId, x270011_g_sunfeihu, "��˵�ղ��ǹ�������û��", -1)
						end
		end
	elseif x270011_g_doing==2   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 6   then
						x270011_g_doing = 3
						if IsObjValid (sceneId,x270011_g_huwei1) == 1 then
								NpcTalk(sceneId, x270011_g_huwei1, "�����ղ�����ɵ�ˣ�û׼���˰ɣ�", -1)
						end
		end
	elseif x270011_g_doing==3   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 9   then
						x270011_g_doing = 4
						if IsObjValid (sceneId,x270011_g_sunfeihu) == 1 then
								NpcTalk(sceneId, x270011_g_sunfeihu, "�������ܣ��ܵ������Ҳ��ץ������", -1)
						end
		end
	elseif x270011_g_doing==4   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 12   then
						x270011_g_doing = 5
						if IsObjValid (sceneId,x270011_g_huwei2) == 1 then
								NpcTalk(sceneId, x270011_g_huwei2, "û׼�����ｫ��Ӣ�������Լ��ߵ߹����ˣ�", -1)
						end
		end
	elseif x270011_g_doing==5   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 14   then
						x270011_g_doing = 6
						if IsObjValid (sceneId,x270011_g_sunfeihu) == 1 then
								NpcTalk(sceneId, x270011_g_sunfeihu, "��������", -1)
						end
						if IsObjValid (sceneId,x270011_g_huwei1) == 1 then
								NpcTalk(sceneId, x270011_g_huwei1, "��������", -1)
						end
						x270011_g_zhangsheng=CreateMonster(sceneId, 1621,166,458,3,1,-1,-1,20,30000,0,"��ݺݺ","������")
		end
	elseif x270011_g_doing==6   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 16   then
						x270011_g_doing = 7
						if IsObjValid (sceneId,x270011_g_huwei1) == 1 then
								NpcTalk(sceneId, x270011_g_huwei1, "�����ⲻ�����ˣ�", -1)
						end
						if IsObjValid (sceneId,x270011_g_huwei1) == 1 then
								SetMonsterDir(sceneId,x270011_g_huwei1,180)
						end
		end
	elseif x270011_g_doing==7   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 18   then
						x270011_g_doing = 8
						if IsObjValid (sceneId,x270011_g_sunfeihu) == 1 then
								NpcTalk(sceneId, x270011_g_sunfeihu, "���������ˣ�ʡ���Ҳ����鷳��", -1)
						end
						if IsObjValid (sceneId,x270011_g_sunfeihu) == 1 then
								SetMonsterDir(sceneId,x270011_g_sunfeihu,180)
						end
						if IsObjValid (sceneId,x270011_g_huwei2) == 1 then
								SetMonsterDir(sceneId,x270011_g_huwei2,180)
						end
		end
	elseif x270011_g_doing==8   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 21   then
						x270011_g_doing = 9
						if IsObjValid (sceneId,x270011_g_huwei2) == 1 then
								NpcTalk(sceneId, x270011_g_huwei2, "ѽ������ô��ͷ���ˣ�", -1)
						end
						if IsObjValid (sceneId,x270011_g_zhangsheng) == 1 then
								SetPatrolId(sceneId, x270011_g_zhangsheng, 52)
						end
		end
	elseif x270011_g_doing==9   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 24   then
						x270011_g_doing = 10
						if IsObjValid (sceneId,x270011_g_sunfeihu) == 1 then
								NpcTalk(sceneId, x270011_g_sunfeihu, "�����ˣ�������ϲ����", -1)
								SetPatrolId(sceneId, x270011_g_sunfeihu, 53)
						end
		end
	elseif x270011_g_doing==10   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 26   then
						x270011_g_doing = 11
						if IsObjValid (sceneId,x270011_g_huwei2) == 1 then
								NpcTalk(sceneId, x270011_g_huwei2, "������������Űɣ�", -1)
						end
		end
	elseif x270011_g_doing==11   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 28   then
						x270011_g_doing = 12
						if IsObjValid (sceneId,x270011_g_huwei1) == 1 then
								NpcTalk(sceneId, x270011_g_huwei1, "�����Ҵ��һ����ʱ�������ܻ�����", -1)
								SetMonsterDir(sceneId,x270011_g_huwei1,90)
						end
						if IsObjValid (sceneId,x270011_g_huwei2) == 1 then
								SetMonsterDir(sceneId,x270011_g_huwei2,90)
						end
		end
	elseif x270011_g_doing==12   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 32   then
						x270011_g_doing = 13
						if IsObjValid (sceneId,x270011_g_sunfeihu) == 1 then
								NpcTalk(sceneId, x270011_g_sunfeihu, "�ҿ���Ҫ�ܵ����", -1)
						end
		end
	elseif x270011_g_doing==13   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 36   then
						x270011_g_doing = 14
						if IsObjValid (sceneId,x270011_g_zhangsheng) == 1 then
								SetMonsterDir(sceneId,x270011_g_zhangsheng,50)
						end
		end
	elseif x270011_g_doing==14   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 38   then
						x270011_g_doing = 15
						if IsObjValid (sceneId,x270011_g_sunfeihu) == 1 then
								NpcTalk(sceneId, x270011_g_sunfeihu, "ʲô���Ȼ���еģ��㵽����˭��", -1)
								SetMonsterCamp(sceneId,x270011_g_sunfeihu,21)
						end
		end
	elseif x270011_g_doing==15   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 40   then
						x270011_g_doing = 16
						if IsObjValid (sceneId,x270011_g_zhangsheng) == 1 then
								NpcTalk(sceneId, x270011_g_zhangsheng, "׳ʿ��ʣ�µİ������ˣ�", -1)
						end
		end
	elseif x270011_g_doing==16   then
		if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 43   then
						x270011_g_doing = 17
		end
	elseif x270011_g_doing==17 then
			if GetCurrentTime() - x270011_g_PROTECTINFO.StartTime >= 81   then
				x270011_g_doing=30
				x270011_CloseTimer(sceneId, x270011_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x270011_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270011_g_doing =0
	x270011_g_sunfeihu = -1
	x270011_g_huwei1 = -1
	x270011_g_huwei2 = -1
	x270011_g_zhangsheng = -1
	x270011_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end