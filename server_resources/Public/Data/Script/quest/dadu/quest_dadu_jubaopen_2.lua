--�����ߡ��պ�«��ư<��>

--MisDescBegin
x270015_g_ScriptId = 270015
x270015_g_MissionIdPre =3599
x270015_g_MissionId = 3600
x270015_g_LevelLess	= 	55 
x270015_g_MissionIdNext = 3601
x270015_g_Name	={}
x270015_g_noDemandItem ={{id=13020325,num=1},{id=13020326,num=1}}
x270015_g_ExtTarget ={{type=20,n=1,target="��@npc_143176�Ѻ����Ｆ���뺣��"}}
x270015_g_ExtTargetmul={{type=20,n=1,target="��@npc_143176�Ѻ����Ｆ���뺣��"},
												{type=20,n=1,target="��@npc_143176��һ��"},
												{type=20,n=1,target="��@npc_143177��һ��"},
												{type=20,n=1,target="��@npc_143178��һ��"},
												{type=20,n=1,target="��@npc_143179��һ��"},
												{type=20,n=1,target="���̾۱���"}}
x270015_g_MissionName="�����ߡ��պ�«��ư<��>"
x270015_g_MissionInfo="\t�����Ҹ�����������¥������ĺ����Ｆ�������������Щ�Ｆ���ǵ�����֮ǰ�Ȱ��Ｆ�������"  --��������
x270015_g_MissionTarget=""		
x270015_g_MissionCompleted="\tʲô���۱����Ѿ�������ү�����ˣ���"					--�������npc˵���Ļ�
x270015_g_ContinueInfo="\t�̵���ô��Ҫ��һ�β��У��ǾͶ��̼��Ρ�"
x270015_g_MissionHelp =	""
x270015_g_DemandItem ={}
x270015_g_BonusMoney1 =376
x270015_g_BonusMoney2 =0
x270015_g_BonusMoney3 =0
x270015_g_BonusMoney4 =0
x270015_g_BonusMoney5 =66
x270015_g_BonusMoney6 =0
x270015_g_BonusItem	=	{}
x270015_g_BonusChoiceItem ={}
x270015_g_ExpBonus = 171000
--MisDescEnd
x270015_g_doing = 0
x270015_g_longwang =-1
x270015_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--**********************************

function x270015_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270015_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270015_g_MissionIdPre)> 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x270015_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x270015_g_MissionId, state, -1 )
	end
end

function x270015_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270015_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270015_g_ExpBonus )
		end
		if x270015_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270015_g_BonusMoney1 )
		end
		if x270015_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270015_g_BonusMoney2 )
		end
		if x270015_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270015_g_BonusMoney3 )
		end
		if x270015_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270015_g_BonusMoney4 )
		end
		if x270015_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270015_g_BonusMoney5 )
		end
		if x270015_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270015_g_BonusMoney6 )
		end
		for i, item in x270015_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270015_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270015_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270015_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270015_g_MissionId) > 0 then
			if x270015_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270015_g_MissionName)
						AddQuestText(sceneId,x270015_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270015_g_ScriptId, x270015_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270015_g_MissionName)
						AddQuestText(sceneId,x270015_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270015_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270015_g_ScriptId, x270015_g_MissionId);
			end
  elseif x270015_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270015_g_MissionName)
			AddQuestText(sceneId,x270015_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270015_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270015_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270015_g_MissionHelp )
			end
			x270015_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270015_g_ScriptId, x270015_g_MissionId);
  end
	
end
--**********************************

function x270015_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x270015_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x270015_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == 1 then
			return 1
	end
	return 0
end
--**********************************
function x270015_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270015_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270015_g_MissionId  )
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
		
		if x270015_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		  BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x270015_g_noDemandItem[1].id, x270015_g_noDemandItem[1].num ) 
			AddItem( sceneId,x270015_g_noDemandItem[2].id, x270015_g_noDemandItem[2].num )              
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x270015_g_MissionId, x270015_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270015_Msg2toplayer( sceneId, selfId,0)
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

function x270015_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270015_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270015_g_MissionId)
	  x270015_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270015_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x270015_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270015_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270015_g_BonusChoiceItem do
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
function x270015_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270015_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270015_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270015_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270015_g_MissionId) > 0 then
				x270015_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270015_g_MissionId)
				x270015_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270015_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270015_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		for i, item in x270015_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270015_g_MissionIdNext )	
end

function x270015_GetBonus( sceneId, selfId,NpcID)
	  if x270015_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270015_g_ExpBonus);
  	end
		if x270015_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270015_g_BonusMoney1 )
	  end
		if x270015_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270015_g_BonusMoney2 )
	  end
		if x270015_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270015_g_BonusMoney3 )
		end
		if x270015_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270015_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270015_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270015_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270015_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270015_g_BonusMoney6)
		end
end

function x270015_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270015_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270015_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270015_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270015_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270015_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270015_g_MissionName.."��", 0, 3)
				if x270015_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270015_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270015_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270015_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270015_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270015_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270015_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270015_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270015_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270015_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270015_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270015_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270015_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270015_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270015_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270015_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
end

function x270015_ProcTiming(ssceneId, selfId, ScriptId, MissionId)
	
end

function x270015_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

function x270015_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270015_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x270015_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270015_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270015_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270015_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270015_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270015_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270015_OnScneneTimer(sceneId, selfId)
	if x270015_g_longwang < 0 then
			x270015_CloseTimer(sceneId, x270015_g_PROTECTINFO.ScneneTimerIndex)
			return
	end
	if x270015_g_doing==1   then
		if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 1   then
			if IsObjValid (sceneId,x270015_g_longwang) == 1 then
				NpcTalk(sceneId, x270015_g_longwang, "Ӣ�ۣ����������ͨ�ɣ�", -1)
			end
      x270015_g_doing = 2
		end
	elseif x270015_g_doing == 2   then
			if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 5   then
				if IsObjValid (sceneId,x270015_g_longwang) == 1 then
						NpcTalk(sceneId, x270015_g_longwang, "������������������Ҫ֪�������������ͨ������", -1)
				end
        x270015_g_doing =3
			end
	elseif x270015_g_doing == 3   then
			if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 8   then
				if IsObjValid (sceneId,x270015_g_longwang) == 1 then
						NpcTalk(sceneId, x270015_g_longwang, "������ո��Ѿ�����������һ���㣬��ة�౻������ȥ֮��һֱ���ڿ��ﲻ�ϳ�����", -1)
				end
						x270015_g_doing =4
			end
	elseif x270015_g_doing == 4   then
			if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 12   then
				if IsObjValid (sceneId,x270015_g_longwang) == 1 then
						NpcTalk(sceneId, x270015_g_longwang, "�۱������������ô���ڴ˺�����ͣ���أ�������Ѿ��ص�����ȥ�ˣ�", -1)
				end
						x270015_g_doing =5
			end
	elseif x270015_g_doing == 5   then
			if GetCurrentTime() - x270015_g_PROTECTINFO.StartTime >= 16   then
				if IsObjValid (sceneId,x270015_g_longwang) == 1 then
						NpcTalk(sceneId, x270015_g_longwang, "������Ҿ������ˣ������Σ��������", -1)
				end
						x270015_g_doing =6
						x270015_CloseTimer(sceneId, x270015_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end

function x270015_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270015_g_doing = 0
	x270015_g_longwang =-1
	x270015_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	
end

function x270015_ProcQuestLogRefresh( sceneId,selfId,missionId)
				local misIndex = GetQuestIndexByID(sceneId,selfId,x270015_g_MissionId)
				local exttarget =GetQuestParam(sceneId,selfId,misIndex,1)+1
				BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- ����
                                "",                 -- ��������
                                x270015_g_ExtTargetmul[exttarget].target,               --����Ŀ��
                                "",                         --����NPC
                                "",                   --������
                                "",                --��������
                                ""        --����С��ʾ
                                )

				EndQuestEvent()
				DispatchQuestLogUpdate(sceneId, selfId, x270015_g_MissionId);

end

function x270015_useitem(sceneId,selfId,which)
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270015_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,1) == 0 then
			if which == 1 then 
				local distanceRet = 25 - (185 - PlayerPosX) * (185 - PlayerPosX) - (201 - PlayerPosZ) * (201 - PlayerPosZ)
				if distanceRet >= 0 then
						DelItem( sceneId,selfId,x270015_g_noDemandItem[1].id, x270015_g_noDemandItem[1].num )
						Msg2Player(sceneId, selfId, "����Ŀ��ı�", 0, 3)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t����Ｆ���뵽ˮ�У�û���κη�Ӧ��������Ӧ������ȥ��һ���ˣ�")
						SetQuestByIndex(sceneId,selfId,misIndex,1,1)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						x270015_ProcQuestLogRefresh( sceneId,selfId,x270015_g_MissionId)
						return 1
				else
						Msg2Player(sceneId, selfId, "�����޷�ʹ�������Ʒ", 0, 3)
						return 0
				end
			else
						Msg2Player(sceneId, selfId, "�����޷�ʹ�������Ʒ", 0, 3)
						return 0
			end
		elseif GetQuestParam(sceneId,selfId,misIndex,1) == 1 then
				local distanceRet = 25 - (185 - PlayerPosX) * (185 - PlayerPosX) - (201 - PlayerPosZ) * (201 - PlayerPosZ)
				if distanceRet >= 0 then
						Msg2Player(sceneId, selfId, "����Ŀ��ı�", 0, 3)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\tһ����ȥ������һ���������õ����裬��ô��Ҳ�����Ǿ۱��裬Ӧ�û����ط������ˡ�")
						SetQuestByIndex(sceneId,selfId,misIndex,1,2)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						x270015_ProcQuestLogRefresh( sceneId,selfId,x270015_g_MissionId)
						return 1
				else
						Msg2Player(sceneId, selfId, "�����޷�ʹ�������Ʒ", 0, 3)
						return 0
				end
		elseif GetQuestParam(sceneId,selfId,misIndex,1) == 2 then
				local distanceRet = 25 - (185 - PlayerPosX) * (185 - PlayerPosX) - (190 - PlayerPosZ) * (190 - PlayerPosZ)
				if distanceRet >= 0 then
						Msg2Player(sceneId, selfId, "����Ŀ��ı�", 0, 3)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\tһ����ȥ��������һ��ʯ�裬�����������Զ��������ʿ�������ľ۱��軹����һ������ٻ�һ���ط��ɡ�")
						SetQuestByIndex(sceneId,selfId,misIndex,1,3)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						x270015_ProcQuestLogRefresh( sceneId,selfId,x270015_g_MissionId)
						return 1
				else
						Msg2Player(sceneId, selfId, "�����޷�ʹ�������Ʒ", 0, 3)
						return 0
				end
		elseif GetQuestParam(sceneId,selfId,misIndex,1) == 3 then
				local distanceRet = 25 - (200 - PlayerPosX) * (200 - PlayerPosX) - (185 - PlayerPosZ) * (185 - PlayerPosZ)
				if distanceRet >= 0 then
						Msg2Player(sceneId, selfId, "����Ŀ��ı�", 0, 3)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\tһ����ȥ��β������ˣ�����һֻ���ڹ꣬�������������䲻�ȸղŵ�ʯ��С������ͷ�Ŷ��Ѿ������˿������֮����������ӵ��˺��")
						SetQuestByIndex(sceneId,selfId,misIndex,1,4)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						x270015_ProcQuestLogRefresh( sceneId,selfId,x270015_g_MissionId)
						return 1
				else
						Msg2Player(sceneId, selfId, "�����޷�ʹ�������Ʒ", 0, 3)
						return 0
				end
		elseif GetQuestParam(sceneId,selfId,misIndex,1) == 4 then
				local distanceRet = 25 - (174 - PlayerPosX) * (174 - PlayerPosX) - (206 - PlayerPosZ) * (206 - PlayerPosZ)
				if distanceRet >= 0 then
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						SetQuestByIndex(sceneId,selfId,misIndex,1,5)
						Msg2Player(sceneId, selfId, "����Ŀ�����", 0, 3)
						DelItem( sceneId,selfId,x270015_g_noDemandItem[2].id, x270015_g_noDemandItem[2].num )
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"\t��ε����ܳ�������Ѿ�������ʱ���������Ϲ���һ���ˣ����Ҵ������ڣ�")
						SetQuestByIndex(sceneId,selfId,misIndex,1,5)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, selfId, x270015_g_ScriptId, x270015_g_MissionId);
						if x270015_g_doing==0   then
								x270015_g_PROTECTINFO.StartTime = GetCurrentTime()
								x270015_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270015, "OnScneneTimer", 1)
								if x270015_g_PROTECTINFO.ScneneTimerIndex >= 0 then
										x270015_g_doing = 1
										x270015_g_longwang =CreateMonster(sceneId, 3902,170,203,3,1,-1,-1,20,20000,90,"����")
								end
						end
						return 1
				else
						Msg2Player(sceneId, selfId, "�����޷�ʹ�������Ʒ", 0, 3)
						return 0
				end
		end
end
