--�����ߡ����̾���<��>

--MisDescBegin
x270000_g_ScriptId = 270000
x270000_g_MissionIdPre =3532
x270000_g_MissionId = 3533
x270000_g_LevelLess	= 	40 
x270000_g_MissionIdNext = 3534
x270000_g_Name	={}
x270000_g_ExtTarget={{type=20,n=1,target="̽��������̵�״��"}}
x270000_g_MissionName="�����ߡ����̾���<��>"
x270000_g_MissionInfo="\t������һ������������Ӳ������Ϊ�У�����֮�£���λ���ѣ���ȴԹ�������ˣ�\n\t�úã�����ǲ������и��㱸�µĺ���"  --��������
x270000_g_MissionTarget=""		
x270000_g_MissionCompleted="\t#Y@myname#W��������ĳ�������˲�����������Ϊ�ˣ�����ȷʵ������������㣬ֻ������ǰ����˹���̽���ͻȻ���Űݷã������ҽ�����ʥ�����˲�˹�������У�Ҫ�����ǹ黹ʥ�������˹���̡��ҽ̵����֮����ɹ������ˣ������ұ�ܾ��ˡ�"					--�������npc˵���Ļ�
x270000_g_ContinueInfo="\t��Щ��˹�ˣ�Ī���ǳ������ı��ӵ�����Ȼ�Ҵ�������������Ұ��"
x270000_g_MissionHelp =	""
x270000_g_DemandItem ={}
x270000_g_BonusMoney1 =376
x270000_g_BonusMoney2 =0
x270000_g_BonusMoney3 =0
x270000_g_BonusMoney4 =0
x270000_g_BonusMoney5 =51
x270000_g_BonusMoney6 =0
x270000_g_BonusItem	=	{}
x270000_g_BonusChoiceItem ={}
x270000_g_ExpBonus = 93000
x270000_g_doing = 0
x270000_g_acceptid =-1
x270000_g_kanshou = -1
x270000_g_kanshou2 = -1
x270000_g_budaiheshang = -1
--x270000_g_guozixing =-1
--x270000_g_liufutong = -1
x270000_g_yangdingtian = -1
x270000_g_yangxiao = -1
x270000_g_fanyao = -1
x270000_g_suduona = -1
x270000_g_bosijiaotu = -1
x270000_g_bosijiaotu2 = -1
x270000_g_bosijiaotu3 = -1
x270000_g_bosijiaotu4 = -1
x270000_g_mingjiaodizi =-1
x270000_g_mingjiaodizi2 =-1
x270000_g_mingjiaodizi3 =0
x270000_g_mingjiaodizi4 =0
x270000_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x270000_g_NpcGUID ={{ guid = 141300, name = "������"} }
--MisDescEnd
--**********************************

function x270000_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270000_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270000_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x270000_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270000_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270000_g_MissionId, state, -1 )
		end
	end
end

function x270000_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270000_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270000_g_ExpBonus )
		end
		if x270000_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270000_g_BonusMoney1 )
		end
		if x270000_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270000_g_BonusMoney2 )
		end
		if x270000_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270000_g_BonusMoney3 )
		end
		if x270000_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270000_g_BonusMoney4 )
		end
		if x270000_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270000_g_BonusMoney5 )
		end
		if x270000_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270000_g_BonusMoney6 )
		end
		for i, item in x270000_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270000_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270000_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270000_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270000_g_MissionId) > 0 then
			if x270000_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270000_g_MissionName)
						AddQuestText(sceneId,x270000_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270000_g_ScriptId, x270000_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270000_g_MissionName)
						AddQuestText(sceneId,x270000_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270000_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270000_g_ScriptId, x270000_g_MissionId);
			end
  elseif x270000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270000_g_MissionName)
			AddQuestText(sceneId,x270000_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270000_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270000_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270000_g_MissionHelp )
			end
			x270000_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270000_g_ScriptId, x270000_g_MissionId);
	else
			Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷����ܴ�����", 0, 3)
  end
	
end
--**********************************

function x270000_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270000_g_MissionIdPre)> 0 then
				if IsHaveQuest(sceneId,selfId, 7537) > 0 then
						return 0
				elseif IsHaveQuest(sceneId,selfId, 7538) > 0 then
						return 0
				elseif IsHaveQuest(sceneId,selfId, 7539) > 0 then
						return 0
				elseif IsHaveSpecificImpact(sceneId, selfId, 7516) > 0 then
						return 0
				elseif IsHaveSpecificImpact(sceneId, selfId, 7517) > 0 then
						return 0
				end
				return 1
		end
		return 0

end
--**********************************
function x270000_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270000_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
	
end
--**********************************
function x270000_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270000_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270000_g_MissionId  )
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
		if x270000_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
				if x270000_g_doing == 0 then
					local retmiss = AddQuest( sceneId, selfId, x270000_g_MissionId, x270000_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270000_Msg2toplayer( sceneId, selfId,0)
		  			x270000_g_PROTECTINFO.StartTime = GetCurrentTime()
						x270000_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270000, "OnScneneTimer", 1)
						if x270000_g_PROTECTINFO.ScneneTimerIndex >= 0 then
								x270000_g_doing = 1
								x270000_g_acceptid = selfId
								x270000_g_kanshou=CreateMonster(sceneId, 1610,229.9439,46.9169,3,1,-1,-1,20,65000,180,"���̵���")
								x270000_g_kanshou2=CreateMonster(sceneId, 1610,233.5248,47.1331,3,1,-1,-1,20,65000,180,"���̵���")
								x270000_g_budaiheshang =FindMonsterByGUID( sceneId,141310)
								SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 8700, 0);
								Msg2Player(sceneId, selfId, "�㱻����Ѩλװ����һ����ڴ��", 0, 3)
								if IsObjValid (sceneId,x270000_g_budaiheshang) == 1 then
									MonsterDoAction(sceneId, x270000_g_budaiheshang, 2, -1) 
								end
						end
		  		end
				else
					Msg2Player(sceneId, selfId, "������ʱ�޷����ܣ�", 0, 3)
				end
		else
				Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷����ܴ�����", 0, 3)
	 	end                                                                    
	     
end
--**********************************

function x270000_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270000_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270000_g_MissionId)
	  x270000_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x270000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270000_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270000_g_BonusChoiceItem do
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
function x270000_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270000_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270000_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270000_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270000_g_MissionId) > 0 then
				x270000_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270000_g_MissionId)
				x270000_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270000_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270000_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270000_g_MissionIdNext )	
end

function x270000_GetBonus( sceneId, selfId,NpcID)
	  if x270000_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270000_g_ExpBonus);
  	end
		if x270000_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270000_g_BonusMoney1 )
	  end
		if x270000_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270000_g_BonusMoney2 )
	  end
		if x270000_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270000_g_BonusMoney3 )
		end
		if x270000_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270000_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270000_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270000_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270000_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270000_g_BonusMoney6)
		end
end

function x270000_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270000_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270000_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270000_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270000_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270000_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270000_g_MissionName.."��", 0, 3)
				if x270000_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270000_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270000_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270000_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270000_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270000_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270000_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270000_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270000_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270000_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270000_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270000_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270000_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270000_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270000_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270000_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270000_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270000_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270000_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270000_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270000_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270000_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x270000_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x270000_g_MissionId, state, -1 )
		end
end

function x270000_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270000_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270000_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270000_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270000_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270000_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270000_OnScneneTimer(sceneId)
	if x270000_g_doing==1   then
		if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 2   then
						x270000_g_doing = 2
						if IsObjValid (sceneId,x270000_g_budaiheshang) == 1 then
								NpcTalk(sceneId, x270000_g_budaiheshang, "��˹�˵��߹����ø��ƺ�������̽��������Ϊ���ǿ���������", -1)
						end
		end
	elseif x270000_g_doing==2   then
		if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 4   then
						x270000_g_doing = 3
						if IsObjValid (sceneId,x270000_g_kanshou) == 1 then
								NpcTalk(sceneId, x270000_g_kanshou, "С������һ��ɽ�ͷ����㲻�Ծ���", -1)
								SetPatrolId(sceneId, x270000_g_kanshou, 0)
								SetPatrolId(sceneId, x270000_g_kanshou2, 1)
						end
		end
	elseif x270000_g_doing == 3   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 7   then
        		x270000_g_doing =4
						if IsObjValid (sceneId,x270000_g_kanshou2) == 1 then
								NpcTalk(sceneId, x270000_g_kanshou2, "�ǰ������ҹ������ͣ����ӵ�Ҫ���������������ѡ��", -1)
						end
			end
	elseif x270000_g_doing == 4   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 10   then
						x270000_g_doing =5
						if IsObjValid (sceneId,x270000_g_budaiheshang) == 1 then
								SetMonsterDir(sceneId,x270000_g_budaiheshang,120)
								NpcTalk(sceneId, x270000_g_budaiheshang, "����������", -1)
						end
						if IsObjValid (sceneId,x270000_g_kanshou) == 1 then
								SetMonsterDir(sceneId,x270000_g_kanshou,120)
								NpcTalk(sceneId, x270000_g_kanshou, "����������", -1)
						end
						if IsObjValid (sceneId,x270000_g_kanshou2) == 1 then
								SetMonsterDir(sceneId,x270000_g_kanshou2,120)
								NpcTalk(sceneId, x270000_g_kanshou2, "����������", -1)
								SetMonsterDir(sceneId,x270000_g_kanshou,180)
								SetMonsterDir(sceneId,x270000_g_kanshou2,0)
						end
						--x270000_g_guozixing =FindMonsterByGUID( sceneId,141317)
						--x270000_g_liufutong =FindMonsterByGUID( sceneId,141318)
						x270000_g_yangdingtian =FindMonsterByGUID( sceneId,141300)
						x270000_g_yangxiao =FindMonsterByGUID( sceneId,141302)
						x270000_g_fanyao =FindMonsterByGUID( sceneId,141301)
						x270000_g_mingjiaodizi =FindMonsterByGUID( sceneId,141322)
						x270000_g_mingjiaodizi2 =FindMonsterByGUID( sceneId,141323)
						x270000_g_mingjiaodizi3 =FindMonsterByGUID( sceneId,141324)
						x270000_g_mingjiaodizi4 =FindMonsterByGUID( sceneId,141325)
						--if IsObjValid (sceneId,x270000_g_guozixing) == 1 then
						--		SetPatrolId(sceneId, x270000_g_guozixing, 9)
						--end
						--if IsObjValid (sceneId,x270000_g_liufutong) == 1 then
							--	SetPatrolId(sceneId, x270000_g_liufutong, 10)
						--end
						if IsObjValid (sceneId,x270000_g_yangdingtian) == 1 then
								SetPatrolId(sceneId, x270000_g_yangdingtian, 2)
						end
						if IsObjValid (sceneId,x270000_g_yangxiao) == 1 then
								SetPatrolId(sceneId, x270000_g_yangxiao, 3)
						end
						if IsObjValid (sceneId,x270000_g_fanyao) == 1 then
								SetPatrolId(sceneId, x270000_g_fanyao, 4)
						end
						if IsObjValid (sceneId,x270000_g_mingjiaodizi) == 1 then
								SetPatrolId(sceneId, x270000_g_mingjiaodizi, 5)
						end
						if IsObjValid (sceneId,x270000_g_mingjiaodizi2) == 1 then
								SetPatrolId(sceneId, x270000_g_mingjiaodizi2, 6)
						end
						if IsObjValid (sceneId,x270000_g_mingjiaodizi3) == 1 then
								SetPatrolId(sceneId, x270000_g_mingjiaodizi3, 7)
						end
						if IsObjValid (sceneId,x270000_g_mingjiaodizi4) == 1 then
								SetPatrolId(sceneId, x270000_g_mingjiaodizi4, 8)
						end
			end
	elseif x270000_g_doing == 5   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 13   then
				x270000_g_doing =6
				if IsObjValid (sceneId,x270000_g_budaiheshang) == 1 then
						NpcTalk(sceneId, x270000_g_budaiheshang, "ʲô����ô������ˣ����ǿ�ȥ��", -1)
				end
			end
	elseif x270000_g_doing == 6   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 16   then
						x270000_g_doing =7
						if IsObjValid (sceneId,x270000_g_kanshou2) == 1 then
								NpcTalk(sceneId, x270000_g_kanshou2, "�ǣ�", -1)
						end
						if IsObjValid (sceneId,x270000_g_kanshou) == 1 then
								NpcTalk(sceneId, x270000_g_kanshou, "�ǣ�", -1)
						end
						if IsObjValid (sceneId,x270000_g_kanshou) == 1 then
								SetPatrolId(sceneId, x270000_g_kanshou, 9)
						end
						if IsObjValid (sceneId,x270000_g_kanshou2) == 1 then
								SetPatrolId(sceneId, x270000_g_kanshou2, 10)
						end
			end
	elseif x270000_g_doing == 7   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 18   then
						x270000_g_doing =8
						if IsObjValid (sceneId,x270000_g_budaiheshang) == 1 then
								NpcTalk(sceneId, x270000_g_budaiheshang, "�ߣ���Ϊ�����ж��ͶԸ�������������", -1)
						end
			end
	elseif x270000_g_doing == 8   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 21   then
						x270000_g_doing =9
						if IsObjValid (sceneId,x270000_g_budaiheshang) == 1 then
								NpcTalk(sceneId, x270000_g_budaiheshang, "�ߣ��Ҵ���ȥ���������ȥ��", -1)
						end
            x270000_g_suduona=CreateMonster(sceneId, 1608,235.5737,65.7265,3,1,-1,-1,20,36000,0,"�ն���","��˹����")
						x270000_g_bosijiaotu=CreateMonster(sceneId, 1609,234.2818,66.7210,3,1,-1,-1,20,36000,0)
						x270000_g_bosijiaotu2=CreateMonster(sceneId, 1609,236.6045,66.9977,3,1,-1,-1,20,36000,0)
						x270000_g_bosijiaotu3=CreateMonster(sceneId, 1609,234.1153,68.5531,3,1,-1,-1,20,36000,0)
						x270000_g_bosijiaotu4=CreateMonster(sceneId, 1609,236.3321,68.9795,3,1,-1,-1,20,36000,0)
						if IsObjValid (sceneId,x270000_g_suduona) == 1 then
								SetPatrolId(sceneId, x270000_g_suduona, 11)
						end
						if IsObjValid (sceneId,x270000_g_bosijiaotu) == 1 then
								SetPatrolId(sceneId, x270000_g_bosijiaotu, 12)
						end
						if IsObjValid (sceneId,x270000_g_bosijiaotu2) == 1 then
								SetPatrolId(sceneId, x270000_g_bosijiaotu2, 13)
						end
						if IsObjValid (sceneId,x270000_g_bosijiaotu3) == 1 then
								SetPatrolId(sceneId, x270000_g_bosijiaotu3, 14)
						end
						if IsObjValid (sceneId,x270000_g_bosijiaotu4) == 1 then
								SetPatrolId(sceneId, x270000_g_bosijiaotu4, 15)
						end
			end
	elseif x270000_g_doing == 9   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 22   then
						x270000_g_doing =10
						if IsPlayerStateNormal(sceneId,x270000_g_acceptid) ==1 then
							if IsHaveQuest(sceneId,x270000_g_acceptid, x270000_g_MissionId) > 0 then
								SetPos(sceneId,x270000_g_acceptid,232,50)
							end
						end
						if IsObjValid (sceneId,x270000_g_budaiheshang) == 1 then
								SetPos(sceneId,x270000_g_budaiheshang,231,52)
								SetMonsterDir(sceneId,x270000_g_budaiheshang,190)
								SetMonsterDir(sceneId,x270000_g_yangdingtian,140)
								SetMonsterDir(sceneId,x270000_g_yangxiao,140)
								SetMonsterDir(sceneId,x270000_g_fanyao,185)
								SetMonsterDir(sceneId,x270000_g_mingjiaodizi,140)
								SetMonsterDir(sceneId,x270000_g_mingjiaodizi2,140)
								SetMonsterDir(sceneId,x270000_g_mingjiaodizi3,140)
								SetMonsterDir(sceneId,x270000_g_mingjiaodizi4,120)
						end
			end
	elseif x270000_g_doing == 10   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 25   then
						x270000_g_doing =11
						if IsObjValid (sceneId,x270000_g_suduona) == 1 then
								NpcTalk(sceneId, x270000_g_suduona, "СŮ���ն��ȸ��������밲��", -1)
						end
			end
	elseif x270000_g_doing == 11   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 28   then
						x270000_g_doing =12
						if IsObjValid (sceneId,x270000_g_yangdingtian) == 1 then
								NpcTalk(sceneId, x270000_g_yangdingtian, "�ϻ���˵�������ô�����ʥ�أ���Ϊ���£�", -1)
						end
			end
	elseif x270000_g_doing == 12   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 31   then
						x270000_g_doing =13
						if IsObjValid (sceneId,x270000_g_suduona) == 1 then
								NpcTalk(sceneId, x270000_g_suduona, "�ã��������ˬ�죬�ҾͲ��������ˡ������ص����ջ��ҽ�ʥ�ʥ����ģ�", -1)
						end
			end
	elseif x270000_g_doing == 13   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 34   then
						x270000_g_doing =14
						if IsObjValid (sceneId,x270000_g_suduona) == 1 then
								NpcTalk(sceneId, x270000_g_suduona, "�����õ�ʥ�������ȴ����ȱ����һ�������������ⶫ��һ�������������ϡ�", -1)
						end
			end
	elseif x270000_g_doing == 14   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 37   then
						x270000_g_doing =15
						if IsObjValid (sceneId,x270000_g_yangdingtian) == 1 then
								NpcTalk(sceneId, x270000_g_yangdingtian, "ʲô����ô˵����ʧ�ٵ�ʥ�����Ǳ���������ˣ����ݹ���ĳ�˲������ˡ�", -1)
						end
			end
	elseif x270000_g_doing == 15   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 40   then
						x270000_g_doing =16
						if IsObjValid (sceneId,x270000_g_budaiheshang) == 1 then
								NpcTalk(sceneId, x270000_g_budaiheshang, "�����ǣ�������ͱ������ˡ����������������ƽ䣡", -1)
						end
			end
	elseif x270000_g_doing == 16   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 43   then
						x270000_g_doing =17
						if IsObjValid (sceneId,x270000_g_suduona) == 1 then
								NpcTalk(sceneId, x270000_g_suduona, "�ߣ�������Ӳ�������ж�������ڿ�����վ��վ�����˰ɡ�", -1)
						end
			end
	elseif x270000_g_doing == 17   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 46   then
						x270000_g_doing =18
						if IsObjValid (sceneId,x270000_g_yangdingtian) == 1 then
								NpcTalk(sceneId, x270000_g_yangdingtian, "��������ôȷ�ϣ�", -1)
						end
			end
	elseif x270000_g_doing == 18   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 48   then
						x270000_g_doing =19
						if IsObjValid (sceneId,x270000_g_bosijiaotu) == 1 then
								SendSpecificImpactToUnit(sceneId, x270000_g_bosijiaotu, x270000_g_bosijiaotu, x270000_g_bosijiaotu, 3060, 0);
						end
						if IsObjValid (sceneId,x270000_g_bosijiaotu2) == 1 then
								SendSpecificImpactToUnit(sceneId, x270000_g_bosijiaotu2, x270000_g_bosijiaotu2, x270000_g_bosijiaotu2, 3060, 0);
						end
			end
	elseif x270000_g_doing == 19   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 50   then
						x270000_g_doing =20
						if IsObjValid (sceneId,x270000_g_suduona) == 1 then
								NpcTalk(sceneId, x270000_g_suduona, "ʲô���ѵ�����û�з�����", -1)
						end
			end
	elseif x270000_g_doing == 20   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 53   then
						x270000_g_doing =21
						if IsObjValid (sceneId,x270000_g_suduona) == 1 then
								NpcTalk(sceneId, x270000_g_suduona, "С�ӣ�ԭ���������̵��ˣ���Ȼ�����ƭ�ˣ������ߣ�", -1)
						end
			end
	elseif x270000_g_doing == 21   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 56   then
						x270000_g_doing =22
						if IsObjValid (sceneId,x270000_g_yangdingtian) == 1 then
								NpcTalk(sceneId, x270000_g_yangdingtian, "�������������λ�����ˣ��������ǲ�˹���ˡ�", -1)
						end
			end
	elseif x270000_g_doing == 22   then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 60   then
						x270000_g_doing =23
						if IsObjValid (sceneId,x270000_g_yangdingtian) == 1 then
								NpcTalk(sceneId, x270000_g_yangdingtian, "��������������Ϊ���ǲ�˹�����ġ����������Ѿ������ˣ�ǡ��������������ѣ�ϣ���������ҽ̶ɹ��ѹء�", -1)
						end
			end
	elseif x270000_g_doing==23 then
			if GetCurrentTime() - x270000_g_PROTECTINFO.StartTime >= 65   then
				x270000_g_doing=24
				if IsPlayerStateNormal(sceneId,x270000_g_acceptid) ==1 then
					if IsHaveQuest(sceneId,x270000_g_acceptid, x270000_g_MissionId) > 0 then
									local misIndex = GetQuestIndexByID(sceneId, x270000_g_acceptid, x270000_g_MissionId)
									SetQuestByIndex(sceneId,x270000_g_acceptid,misIndex,0,1)
									SetQuestByIndex(sceneId,x270000_g_acceptid,misIndex,7,1)
									BeginQuestEvent(sceneId)
									AddQuestText(sceneId,format("̽��������̵�״��   %d/1", GetQuestParam(sceneId,x270000_g_acceptid,misIndex,0) ))
									EndQuestEvent(sceneId)
									DispatchQuestTips(sceneId,x270000_g_acceptid)
									CancelSpecificImpact(sceneId,x270000_g_acceptid,8700)
					end
				end
				x270000_CloseTimer(sceneId, x270000_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x270000_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270000_g_doing =0
	x270000_g_acceptid =-1
	x270000_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	--SetPatrolId(sceneId, x270000_g_guozixing, -1)
	--SetPatrolId(sceneId, x270000_g_liufutong, -1)
	SetPatrolId(sceneId, x270000_g_yangdingtian, -1)
	SetPatrolId(sceneId, x270000_g_yangxiao, -1)
	SetPatrolId(sceneId, x270000_g_fanyao, -1)
	SetPatrolId(sceneId, x270000_g_mingjiaodizi, -1)
	SetPatrolId(sceneId, x270000_g_mingjiaodizi2, -1)
	SetPatrolId(sceneId, x270000_g_mingjiaodizi3, -1)
	SetPatrolId(sceneId, x270000_g_mingjiaodizi4, -1)
	SetPos(sceneId,x270000_g_budaiheshang,233,35)
	--SetPos(sceneId,x270000_g_guozixing,42.8,254.6)
	--SetPos(sceneId,x270000_g_liufutong,47.5,254.7)
	--SetPos(sceneId,x270000_g_yangdingtian,45.1,255)
	--SetPos(sceneId,x270000_g_yangxiao,33.8,259)
	--SetPos(sceneId,x270000_g_fanyao,36.6,259.4)
	--SetPos(sceneId,x270000_g_mingjiaodizi,45.7,274.9)
	--SetPos(sceneId,x270000_g_mingjiaodizi2,49.7,274.8)
	--SetPos(sceneId,x270000_g_mingjiaodizi3,45.4,305.4)
	--SetPos(sceneId,x270000_g_mingjiaodizi4,50.3,305.4)
	SetMonsterDir(sceneId,x270000_g_budaiheshang,90)
	--SetMonsterDir(sceneId,x270000_g_guozixing,0)
	--SetMonsterDir(sceneId,x270000_g_liufutong,0)
	--SetMonsterDir(sceneId,x270000_g_yangdingtian,0)
	--SetMonsterDir(sceneId,x270000_g_yangxiao,0)
	--SetMonsterDir(sceneId,x270000_g_fanyao,0)
	--SetMonsterDir(sceneId,x270000_g_mingjiaodizi,0)
	--SetMonsterDir(sceneId,x270000_g_mingjiaodizi2,0)
	--SetMonsterDir(sceneId,x270000_g_mingjiaodizi3,0)
	--SetMonsterDir(sceneId,x270000_g_mingjiaodizi4,0)
	
end

function x270000_ProcQuestLogRefresh( sceneId,selfId,missionId)

    --BeginQuestEvent(sceneId)
    --EndQuestEvent()
		--DispatchQuestLogUpdate(sceneId, selfId, x270000_g_MissionId);

end