--�����ߡ����̾���<��>

--MisDescBegin
x270009_g_ScriptId = 270009
x270009_g_MissionIdPre =3532
x270009_g_MissionId = 3533
x270009_g_LevelLess	= 	50 
x270009_g_MissionIdNext = 3534
x270009_g_Name	={}
x270009_g_ExtTarget={{type=20,n=1,target="̽��������̵�״��"}}
x270009_g_MissionName="�����ߡ����̾���<��>"
x270009_g_MissionInfo="\t�հհգ�����Ц��̫�յߣ���Ц���˿��������úã�����ǲ������и��㱸�µĺ���"  --��������
x270009_g_MissionTarget=""		
x270009_g_MissionCompleted="\t#Y@myname#W��������ĳ��������㣬���ǲ������������������������������Ϣ����ĳ����Ҫ������"					--�������npc˵���Ļ�
x270009_g_ContinueInfo="\t��Щ��˹�ˣ�Ī���ǳ������ı��ӵ�����Ȼ�Ҵ�������������Ұ��"
x270009_g_MissionHelp =	""
x270009_g_DemandItem ={}
x270009_g_BonusMoney1 =376
x270009_g_BonusMoney2 =0
x270009_g_BonusMoney3 =0
x270009_g_BonusMoney4 =0
x270009_g_BonusMoney5 =110
x270009_g_BonusMoney6 =0
x270009_g_BonusItem	=	{}
x270009_g_BonusChoiceItem ={}
x270009_g_ExpBonus = 93000
x270009_g_doing = 0
x270009_g_acceptid =0
x270009_g_kanshou = 0
x270009_g_kanshou2 = 0
x270009_g_budaiheshang = 0
x270009_g_guozixing =0
x270009_g_liufutong = 0
x270009_g_yangdingtian = 0
x270009_g_yangxiao = 0
x270009_g_fanyao = 0
x270009_g_suduona = 0
x270009_g_bosijiaotu = 0
x270009_g_bosijiaotu2 = 0
x270009_g_bosijiaotu3 = 0
x270009_g_bosijiaotu4 = 0
x270009_g_mingjiaodizi =0
x270009_g_mingjiaodizi2 =0
x270009_g_mingjiaodizi3 =0
x270009_g_mingjiaodizi4 =0
x270009_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x270009_g_NpcGUID ={{ guid = 139806, name = "������"} }
--MisDescEnd
--**********************************

function x270009_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270009_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270009_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x270009_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270009_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270009_g_MissionId, state, -1 )
		end
	end
end

function x270009_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270009_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270009_g_ExpBonus )
		end
		if x270009_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270009_g_BonusMoney1 )
		end
		if x270009_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270009_g_BonusMoney2 )
		end
		if x270009_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270009_g_BonusMoney3 )
		end
		if x270009_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270009_g_BonusMoney4 )
		end
		if x270009_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270009_g_BonusMoney5 )
		end
		if x270009_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270009_g_BonusMoney6 )
		end
		for i, item in x270009_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270009_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270009_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270009_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270009_g_MissionId) > 0 then
			if x270009_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270009_g_MissionName)
						AddQuestText(sceneId,x270009_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270009_g_ScriptId, x270009_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270009_g_MissionName)
						AddQuestText(sceneId,x270009_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270009_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270009_g_ScriptId, x270009_g_MissionId);
			end
  elseif x270009_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270009_g_MissionName)
			AddQuestText(sceneId,x270009_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270009_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270009_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270009_g_MissionHelp )
			end
			x270009_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270009_g_ScriptId, x270009_g_MissionId);
  end
	
end
--**********************************

function x270009_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270009_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270009_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270009_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
	
end
--**********************************
function x270009_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270009_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270009_g_MissionId  )
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
		if x270009_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
				if x270009_g_doing == 0 then
					local retmiss = AddQuest( sceneId, selfId, x270009_g_MissionId, x270009_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270009_Msg2toplayer( sceneId, selfId,0)
		  			--SetPos(sceneId,selfId,24,311)
		  			x270009_g_PROTECTINFO.StartTime = GetCurrentTime()
						x270009_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270009, "OnScneneTimer", 1)
						x270009_g_doing = 1
						x270009_g_acceptid = selfId
						x270009_g_kanshou=CreateMonster(sceneId, 1610,24,313,3,1,-1,-1,20,-1,180,"���̵���")
						x270009_g_kanshou2=CreateMonster(sceneId, 1610,25,309,3,1,-1,-1,20,-1,0,"���̵���")
						x270009_g_budaiheshang =FindMonsterByGUID( sceneId,139823)
						SendSpecificImpactToUnit(sceneId, selfId, selfId, x270009_g_budaiheshang, 1281, 0);
						SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, 8700, 0);
						MonsterDoAction(sceneId, x270009_g_budaiheshang, 2, -1) 
					end
				else
					Msg2Player(sceneId, selfId, "������ʱ�޷����ܣ�", 0, 3)
				end

	 	end                                                                    
	     
end
--**********************************

function x270009_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270009_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270009_g_MissionId)
	  x270009_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x270009_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270009_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270009_g_BonusChoiceItem do
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
function x270009_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270009_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270009_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270009_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270009_g_MissionId) > 0 then
				x270009_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270009_g_MissionId)
				x270009_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270009_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270009_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270009_g_MissionIdNext )	
end

function x270009_GetBonus( sceneId, selfId,NpcID)
	  if x270009_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270009_g_ExpBonus);
  	end
		if x270009_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270009_g_BonusMoney1 )
	  end
		if x270009_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270009_g_BonusMoney2 )
	  end
		if x270009_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270009_g_BonusMoney3 )
		end
		if x270009_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270009_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270009_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270009_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270009_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270009_g_BonusMoney6)
		end
end

function x270009_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270009_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270009_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270009_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270009_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270009_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270009_g_MissionName.."��", 0, 3)
				if x270009_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270009_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270009_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270009_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270009_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270009_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270009_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270009_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270009_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270009_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270009_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270009_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270009_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270009_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270009_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270009_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270009_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270009_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270009_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270009_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270009_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270009_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x270009_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x270009_g_MissionId, state, -1 )
		end
end

function x270009_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270009_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270009_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270009_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270009_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270009_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270009_OnScneneTimer(sceneId)
	if x270009_g_doing==1   then
		if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 2   then
						x270009_g_doing = 2
						NpcTalk(sceneId, x270009_g_budaiheshang, "��˹�˵��߹����ø��ƺ�������̽��������Ϊ���ǿ���������", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�������У���˹�˵��߹����ø��ƺ�������̽��������Ϊ���ǿ���������",0,-1)
		end
	elseif x270009_g_doing==2   then
		if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 5   then
						x270009_g_doing = 3
						NpcTalk(sceneId, x270009_g_kanshou, "С�ӣ���һ���žͷ����㲻�Ծ���", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"���̵��ӣ�С�ӣ���һ���žͷ����㲻�Ծ���",0,-1)
		end
	elseif x270009_g_doing == 3   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 7   then
						NpcTalk(sceneId, x270009_g_kanshou2, "�ǰ������ҹ������ͣ����ӵ�Ҫ���������������ѡ��", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"���̵��ӣ��ǰ������ҹ������ͣ����ӵ�Ҫ���������������ѡ��",0,-1)
        		x270009_g_doing =4
			end
	elseif x270009_g_doing == 4   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 10   then
						LuaScenceM2Near(sceneId, x270009_g_acceptid,"���̵��ӣ���˹���̽����ˣ���ҿ�����",0,-1)
						SetMonsterDir(sceneId,x270009_g_budaiheshang,120)
						SetMonsterDir(sceneId,x270009_g_kanshou,120)
						SetMonsterDir(sceneId,x270009_g_kanshou2,120)
						NpcTalk(sceneId, x270009_g_budaiheshang, "����������", -1)
						NpcTalk(sceneId, x270009_g_kanshou, "����������", -1)
						NpcTalk(sceneId, x270009_g_kanshou2, "����������", -1)
						x270009_g_guozixing =FindMonsterByGUID( sceneId,139832)
						x270009_g_liufutong =FindMonsterByGUID( sceneId,139833)
						x270009_g_yangdingtian =FindMonsterByGUID( sceneId,139806)
						x270009_g_yangxiao =FindMonsterByGUID( sceneId,139808)
						x270009_g_fanyao =FindMonsterByGUID( sceneId,139807)
						x270009_g_mingjiaodizi =FindMonsterByGUID( sceneId,139802)
						x270009_g_mingjiaodizi2 =FindMonsterByGUID( sceneId,139803)
						x270009_g_mingjiaodizi3 =FindMonsterByGUID( sceneId,139809)
						x270009_g_mingjiaodizi4 =FindMonsterByGUID( sceneId,139810)
						SetPatrolId(sceneId, x270009_g_guozixing, 7)
						SetPatrolId(sceneId, x270009_g_liufutong, 8)
						SetPatrolId(sceneId, x270009_g_yangdingtian, 11)
						SetPatrolId(sceneId, x270009_g_yangxiao, 10)
						SetPatrolId(sceneId, x270009_g_fanyao, 9)
						SetPatrolId(sceneId, x270009_g_mingjiaodizi, 5)
						SetPatrolId(sceneId, x270009_g_mingjiaodizi2, 6)
						SetPatrolId(sceneId, x270009_g_mingjiaodizi3, 3)
						SetPatrolId(sceneId, x270009_g_mingjiaodizi4, 4)
						x270009_g_doing =5
			end
	elseif x270009_g_doing == 5   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 13   then
						NpcTalk(sceneId, x270009_g_budaiheshang, "ʲô����ô������ˣ����ǿ�ȥ��", -1)
            LuaScenceM2Near(sceneId,  x270009_g_acceptid,"�������У�ʲô����ô������ˣ����ǿ�ȥ��",0,-1)
						x270009_g_doing =6
			end
	elseif x270009_g_doing == 6   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 16   then
						x270009_g_doing =7
						NpcTalk(sceneId, x270009_g_kanshou2, "�ǣ�", -1)
						NpcTalk(sceneId, x270009_g_kanshou, "�ǣ�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"���̵��ӣ���",0,-1)
						SetPatrolId(sceneId, x270009_g_kanshou, 1)
						SetPatrolId(sceneId, x270009_g_kanshou2, 2)
			end
	elseif x270009_g_doing == 7   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 18   then
						x270009_g_doing =8
						NpcTalk(sceneId, x270009_g_budaiheshang, "�ߣ���Ϊ�����ж��ͶԸ�������������", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�������У��ߣ���Ϊ�����ж��ͶԸ�������������",0,-1)
			end
	elseif x270009_g_doing == 8   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 21   then
						x270009_g_doing =9
						NpcTalk(sceneId, x270009_g_budaiheshang, "�ߣ��Ҵ���ȥ���������ȥ��", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�������У��ߣ��Ҵ���ȥ���������ȥ��",0,-1)
            SendSpecificImpactToUnit(sceneId, x270009_g_budaiheshang, x270009_g_budaiheshang, x270009_g_budaiheshang, 1281, 0);
            x270009_g_suduona=CreateMonster(sceneId, 1608,67.4494,258.27,3,1,-1,-1,20,-1,0,"�ն���","��˹����")
						x270009_g_bosijiaotu=CreateMonster(sceneId, 1609,68.1070,256.22,3,1,-1,-1,20,-1,0)
						x270009_g_bosijiaotu2=CreateMonster(sceneId, 1609,68.1941,254.3468,3,1,-1,-1,20,-1,0)
						x270009_g_bosijiaotu3=CreateMonster(sceneId, 1609,68.1436,260.37,3,1,-1,-1,20,-1,0)
						x270009_g_bosijiaotu4=CreateMonster(sceneId, 1609,68,262.3472,3,1,-1,-1,20,-1,0)
						SetPatrolId(sceneId, x270009_g_suduona, 12)
						SetPatrolId(sceneId, x270009_g_bosijiaotu, 13)
						SetPatrolId(sceneId, x270009_g_bosijiaotu2, 14)
						SetPatrolId(sceneId, x270009_g_bosijiaotu3, 15)
						SetPatrolId(sceneId, x270009_g_bosijiaotu4, 16)
			end
	elseif x270009_g_doing == 9   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 22   then
						x270009_g_doing =10
						if IsHaveQuest(sceneId,x270009_g_acceptid, x270009_g_MissionId) > 0 then
								SetPos(sceneId,x270009_g_acceptid,52,265)
						end
						SetPos(sceneId,x270009_g_budaiheshang,51,263)
			end
	elseif x270009_g_doing == 10   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 25   then
						x270009_g_doing =11
						NpcTalk(sceneId, x270009_g_suduona, "СŮ���ն��ȸ��������밲��", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�ն��ȣ�СŮ���ն��ȸ��������밲��",0,-1)
			end
	elseif x270009_g_doing == 11   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 28   then
						x270009_g_doing =12
						NpcTalk(sceneId, x270009_g_yangdingtian, "�ϻ���˵�������ô�����ʥ�أ���Ϊ���£�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�����죺�ϻ���˵�������ô�����ʥ�أ���Ϊ���£�",0,-1)
			end
	elseif x270009_g_doing == 12   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 31   then
						x270009_g_doing =13
						NpcTalk(sceneId, x270009_g_suduona, "�ã��������ˬ�죬�ҾͲ��������ˡ������ص����ջ��ҽ�ʥ�ʥ����ģ�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�ն��ȣ��ã��������ˬ�죬�ҾͲ��������ˡ������ص����ջ��ҽ�ʥ�ʥ����ģ�",0,-1)
			end
	elseif x270009_g_doing == 13   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 34   then
						x270009_g_doing =14
						NpcTalk(sceneId, x270009_g_suduona, "�����õ�ʥ�������ȴ����ȱ����һ�������������ⶫ��һ�������������ϡ�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�ն��ȣ������õ�ʥ�������ȴ����ȱ����һ������,�����ⶫ��һ�������������ϡ�",0,-1)
			end
	elseif x270009_g_doing == 14   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 37   then
						x270009_g_doing =15
						NpcTalk(sceneId, x270009_g_yangdingtian, "ʲô����ô˵����ʧ�ٵ�ʥ�����Ǳ���������ˣ����ݹ���ĳ�˲������ˡ�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�����죺ʲô����ô˵����ʧ�ٵ�ʥ�����Ǳ���������ˣ����ݹ���ĳ�˲������ˡ�",0,-1)
			end
	elseif x270009_g_doing == 15   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 40   then
						x270009_g_doing =16
						NpcTalk(sceneId, x270009_g_budaiheshang, "�����ǣ�������ͱ������ˡ����������������ƽ䣡", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�������У������ǣ�������ͱ������ˡ����������������ƽ䣡",0,-1)
			end
	elseif x270009_g_doing == 16   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 43   then
						x270009_g_doing =17
						NpcTalk(sceneId, x270009_g_suduona, "�ߣ�������Ӳ�������ж�������ڿ�����վ��վ�����˰ɡ�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�ն��ȣ��ߣ�������Ӳ�������ж�������ڿ�����վ��վ�����˰ɡ�",0,-1)
			end
	elseif x270009_g_doing == 17   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 46   then
						x270009_g_doing =18
						NpcTalk(sceneId, x270009_g_yangdingtian, "��������ôȷ�ϣ�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�����죺��������ôȷ�ϣ�",0,-1)
			end
	elseif x270009_g_doing == 18   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 48   then
						x270009_g_doing =19
						SendSpecificImpactToUnit(sceneId, x270009_g_yangdingtian, x270009_g_yangdingtian, x270009_g_yangdingtian, 3101, 0);
						SendSpecificImpactToUnit(sceneId, x270009_g_yangdingtian, x270009_g_yangdingtian, x270009_g_bosijiaotu, 3060, 0);
						SendSpecificImpactToUnit(sceneId, x270009_g_yangdingtian, x270009_g_yangdingtian, x270009_g_bosijiaotu2, 3060, 0);
			end
	elseif x270009_g_doing == 19   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 50   then
						x270009_g_doing =20
						NpcTalk(sceneId, x270009_g_suduona, "ʲô���ѵ�����û�з�����", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�ն��ȣ�ʲô���ѵ�����û�з�����",0,-1)
			end
	elseif x270009_g_doing == 20   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 53   then
						x270009_g_doing =21
						NpcTalk(sceneId, x270009_g_suduona, "С�ӣ�ԭ���������̵��ˣ���Ȼ�����ƭ�ˣ������ߣ�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�ն��ȣ�С�ӣ�ԭ���������̵��ˣ���Ȼ�����ƭ�ˣ������ߣ�",0,-1)
			end
	elseif x270009_g_doing == 21   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 56   then
						x270009_g_doing =22
						NpcTalk(sceneId, x270009_g_yangdingtian, "�������������λ�����ˣ��������ǲ�˹���ˡ�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�����죺�������������λ�����ˣ��������ǲ�˹���ˡ�",0,-1)
            DeleteMonster (sceneId,x270009_g_bosijiaotu3 )
						DeleteMonster (sceneId,x270009_g_bosijiaotu4 )
						DeleteMonster (sceneId,x270009_g_suduona )
			end
	elseif x270009_g_doing == 22   then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 60   then
						x270009_g_doing =23
						NpcTalk(sceneId, x270009_g_yangdingtian, "��������������Ϊ���ǲ�˹�����ġ����������Ѿ������ˣ�ǡ��������������ѣ�ϣ���������ҽ̶ɹ��ѹء�", -1)
            LuaScenceM2Near(sceneId, x270009_g_acceptid,"�����죺��������������Ϊ���ǲ�˹�����ġ����������Ѿ������ˣ�ǡ��������������ѣ�ϣ���������ҽ̶ɹ��ѹء�",0,-1)
			end
	elseif x270009_g_doing==23 then
			if GetCurrentTime() - x270009_g_PROTECTINFO.StartTime >= 65   then
					if IsHaveQuest(sceneId,x270009_g_acceptid, x270009_g_MissionId) > 0 then
									local misIndex = GetQuestIndexByID(sceneId, x270009_g_acceptid, x270009_g_MissionId)
									SetQuestByIndex(sceneId,x270009_g_acceptid,misIndex,0,1)
									SetQuestByIndex(sceneId,x270009_g_acceptid,misIndex,7,1)
									BeginQuestEvent(sceneId)
									AddQuestText(sceneId,format("̽��������̵�״��   %d/1", GetQuestParam(sceneId,x270009_g_acceptid,misIndex,0) ))
									EndQuestEvent(sceneId)
									DispatchQuestTips(sceneId,x270009_g_acceptid)
									CancelSpecificImpact(sceneId,x270009_g_acceptid,8700)
					end
				x270009_g_doing=24
				x270009_CloseTimer(sceneId, x270009_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x270009_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270009_g_doing =0
	x270009_g_acceptid =0
	x270009_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	DeleteMonster (sceneId,x270009_g_kanshou )
	DeleteMonster (sceneId,x270009_g_kanshou2 )
	SetPatrolId(sceneId, x270009_g_guozixing, -1)
	SetPatrolId(sceneId, x270009_g_liufutong, -1)
	SetPatrolId(sceneId, x270009_g_yangdingtian, -1)
	SetPatrolId(sceneId, x270009_g_yangxiao, -1)
	SetPatrolId(sceneId, x270009_g_fanyao, -1)
	SetPatrolId(sceneId, x270009_g_mingjiaodizi, -1)
	SetPatrolId(sceneId, x270009_g_mingjiaodizi2, -1)
	SetPatrolId(sceneId, x270009_g_mingjiaodizi3, -1)
	SetPatrolId(sceneId, x270009_g_mingjiaodizi4, -1)
	SetPos(sceneId,x270009_g_budaiheshang,22.49,311.9)
	SetPos(sceneId,x270009_g_guozixing,42.8,254.6)
	SetPos(sceneId,x270009_g_liufutong,47.5,254.7)
	SetPos(sceneId,x270009_g_yangdingtian,45.1,255)
	SetPos(sceneId,x270009_g_yangxiao,33.8,259)
	SetPos(sceneId,x270009_g_fanyao,36.6,259.4)
	SetPos(sceneId,x270009_g_mingjiaodizi,45.7,274.9)
	SetPos(sceneId,x270009_g_mingjiaodizi2,49.7,274.8)
	SetPos(sceneId,x270009_g_mingjiaodizi3,45.4,305.4)
	SetPos(sceneId,x270009_g_mingjiaodizi4,50.3,305.4)
	SetMonsterDir(sceneId,x270009_g_budaiheshang,90)
	SetMonsterDir(sceneId,x270009_g_guozixing,0)
	SetMonsterDir(sceneId,x270009_g_liufutong,0)
	SetMonsterDir(sceneId,x270009_g_yangdingtian,0)
	SetMonsterDir(sceneId,x270009_g_yangxiao,0)
	SetMonsterDir(sceneId,x270009_g_fanyao,0)
	SetMonsterDir(sceneId,x270009_g_mingjiaodizi,0)
	SetMonsterDir(sceneId,x270009_g_mingjiaodizi2,0)
	SetMonsterDir(sceneId,x270009_g_mingjiaodizi3,0)
	SetMonsterDir(sceneId,x270009_g_mingjiaodizi4,0)
	
end

function x270009_ProcQuestLogRefresh( sceneId,selfId,missionId)

    --BeginQuestEvent(sceneId)
    --EndQuestEvent()
		--DispatchQuestLogUpdate(sceneId, selfId, x270009_g_MissionId);

end