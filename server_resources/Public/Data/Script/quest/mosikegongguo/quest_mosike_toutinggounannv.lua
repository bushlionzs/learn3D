--���ִ󹫷��˵ļ���

--MisDescBegin
x203328_g_ScriptId = 203328
x203328_g_MissionIdPre = 810
x203328_g_MissionId = 811
x203328_g_LevelLess	= 	88 
x203328_g_MissionIdNext = 812
x203328_g_Name	={}
x203328_g_ExtTarget={{type=20,n=1,target="����@npc_117023�ڵ�#G���#W��̽��󹫵�����"}}
x203328_g_MissionName="���糡���󹫷���"
x203328_g_MissionInfo="\t�ղſ������������Ĵ���һ�����ų�ȥ�����ƻص��˳Ƕ���һ���ط����ƺ����ڵ���˭���ܿ�����Լ��ʲô���ڴ���ı�����������ݣ���̽���������������Ҫ�����ˡ�"  --��������
x203328_g_MissionTarget=""		
x203328_g_MissionCompleted="\t���ζ����󡰺ٺ١���Ц˵����\n\t�ߺߣ���һ�й�Ȼ���գ�һ�ٽ����е���ȫ�ߣ���ʱ�����Ǻ���˹������һ�𷴿����ǣ������������������׾ٶ���⼸���󹫵����أ�\n\tֻ���벻�����������Ǵ�Ҳ��ĸ��ĵ�����ڹꣿ��"					--�������npc˵���Ļ�
x203328_g_ContinueInfo="\t���кη��֣�"
x203328_g_MissionHelp =	""
x203328_g_DemandItem ={}
x203328_g_ExpBonus = 684000
x203328_g_BonusMoney1 =880
x203328_g_BonusMoney2 =0
x203328_g_BonusMoney3 =0
x203328_g_BonusMoney4 =0
x203328_g_BonusMoney5 =106
x203328_g_BonusMoney6 =0
x203328_g_BonusItem	=	{}
x203328_g_BonusChoiceItem ={}
x203328_g_doing = 0
x203328_g_acceptid =0
x203328_g_jifudagong = -1
x203328_g_dagongfuren = -1
x203328_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x203328_g_NpcGUID ={{ guid = 117002	, name = "αװ�İζ�"} }
x203328_g_GroupPoint	={ {type=10,id =125,target = "���䳵"} } --ֻ����id��type���Ǵ��������������
--MisDescEnd
--**********************************

function x203328_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203328_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203328_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x203328_g_MissionId) <= 0 then	
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203328_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203328_g_MissionId, state, -1 )
		end
	end
end

function x203328_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203328_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203328_g_ExpBonus )
		end
		if x203328_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203328_g_BonusMoney1 )
		end
		if x203328_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203328_g_BonusMoney2 )
		end
		if x203328_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203328_g_BonusMoney3 )
		end
		if x203328_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203328_g_BonusMoney4 )
		end
		if x203328_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203328_g_BonusMoney5 )
		end
		if x203328_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203328_g_BonusMoney6 )
		end
		for i, item in x203328_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203328_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203328_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203328_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203328_g_MissionId) > 0 then
			if x203328_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203328_g_MissionName)
						AddQuestText(sceneId,x203328_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203328_g_ScriptId, x203328_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203328_g_MissionName)
						AddQuestText(sceneId,x203328_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203328_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203328_g_ScriptId, x203328_g_MissionId);
			end
  elseif x203328_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
 
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203328_g_MissionName)
			AddQuestText(sceneId,x203328_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203328_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203328_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203328_g_MissionHelp )
			end
			x203328_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203328_g_ScriptId, x203328_g_MissionId);
  end
	
end
--**********************************

function x203328_ProcAcceptCheck(sceneId, selfId, NPCId)
		--if IsQuestHaveDone(sceneId, selfId, x203328_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId, selfId, x203328_g_MissionId)<= 0 then
			return 1
		end
		return 0

end
--**********************************
function x203328_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203328_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
end
--**********************************
function x203328_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203328_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203328_g_MissionId  )
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
		
		if x203328_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203328_g_MissionId, x203328_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203328_Msg2toplayer( sceneId, selfId,0)
						if x203328_CheckSubmit(sceneId, selfId, NPCId) > 0 then
							local misIndex = GetQuestIndexByID(sceneId,selfId,x203328_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203328_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203328_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203328_g_MissionId)
	  x203328_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203328_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203328_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203328_g_BonusChoiceItem do
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
function x203328_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203328_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203328_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203328_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203328_g_MissionId) > 0 then
				x203328_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203328_g_MissionId)
				x203328_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203328_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203328_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203328_g_MissionIdNext )	
end

function x203328_GetBonus( sceneId, selfId,NpcID)
	  if x203328_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203328_g_ExpBonus);
  	end
		if x203328_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203328_g_BonusMoney1 )
	  end
		if x203328_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203328_g_BonusMoney2 )
	  end
		if x203328_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203328_g_BonusMoney3 )
		end
		if x203328_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203328_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203328_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203328_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203328_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203328_g_BonusMoney6)
		end
end

function x203328_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203328_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203328_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203328_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203328_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203328_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203328_g_MissionName.."��", 0, 3)
				if x203328_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203328_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203328_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203328_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203328_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203328_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203328_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203328_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203328_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203328_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203328_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203328_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203328_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203328_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203328_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203328_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203328_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203328_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203328_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203328_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203328_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203328_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203328_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203328_g_MissionId, state, -1 )
		end
end

function x203328_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203328_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203328_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203328_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203328_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203328_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x203328_Growpoint( sceneId, selfId,openorremove)
		if IsHaveQuest(sceneId,selfId, x203328_g_MissionId) <= 0 then
				return 1
		end
		if IsHaveQuest(sceneId,selfId, 7537) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)			--�������жϣ��Ƿ����б���buff
						return 0
		elseif IsHaveQuest(sceneId,selfId, 7538) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)
						return 0
		elseif IsHaveQuest(sceneId,selfId, 7539) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)
						return 0
		elseif IsHaveSpecificImpact(sceneId, selfId, 7516) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)
						return 0
		elseif IsHaveSpecificImpact(sceneId, selfId, 7517) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)
						return 0
		end
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203328_g_MissionId)
		if openorremove == 0 then
			if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then
					return 0
			else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t���Ѿ�֪������Ҫ���ˣ������ٶ��ڳ��ڵ������ȥ�����ˡ�")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId);
					return 1
			end
		elseif openorremove == 1 then
			if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then
				if x203328_g_doing == 0 then
					x203328_g_PROTECTINFO.StartTime = GetCurrentTime()
					x203328_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203328, "OnScneneTimer", 1)
					if x203328_g_PROTECTINFO.ScneneTimerIndex >= 0 then
							x203328_g_doing = 1
							x203328_g_acceptid = selfId
							x203328_g_jifudagong=CreateMonster(sceneId, 2110,206,50,3,1,-1,-1,20,41000,90,"������")
							x203328_g_dagongfuren=CreateMonster(sceneId, 2115,210,50,3,1,-1,-1,20,41000,270,"�������Ǵ󹫷���")
						--	if IsObjValid (sceneId,x203328_g_jifudagong) == 1 then
						--			SetPatrolId(sceneId, x203328_g_jifudagong, 17)
						--	end
						--	if IsObjValid (sceneId,x203328_g_dagongfuren) == 1 then
						--			SetPatrolId(sceneId, x203328_g_dagongfuren, 18)
						--	end
						--	return 1
					end
				else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t��ո�Ҫ���������������Ѿ���һ�����ˡ�")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId);
					return 0
				end
			else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t���Ѿ�֪������Ҫ���ˣ������ٵ�������ȥ�����ˡ�")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId);
					return 0
			end
		end
end

function x203328_OnScneneTimer(sceneId)
	if x203328_g_jifudagong < 0 then
			x203328_CloseTimer(sceneId, x203328_g_PROTECTINFO.ScneneTimerIndex)
	elseif x203328_g_dagongfuren < 0 then
			x203328_CloseTimer(sceneId, x203328_g_PROTECTINFO.ScneneTimerIndex)
	end
	if x203328_g_doing==1   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime <= 1   then
			if IsPlayerStateNormal(sceneId,x203328_g_acceptid) ==1 then
				SetPos(sceneId,x203328_g_acceptid,203,47)
				--SetPos(sceneId,playerId,203,47)
				SendSpecificImpactToUnit(sceneId, x203328_g_acceptid, x203328_g_acceptid, x203328_g_acceptid, 8704, 0);
			end
		elseif GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 5   then
						x203328_g_doing = 2
						if IsObjValid (sceneId,x203328_g_jifudagong) == 1 then
								NpcTalk(sceneId, x203328_g_jifudagong, "�������ˣ�˦�����ǵĸ�����治���ס�", -1)
						end
		end
	elseif x203328_g_doing==2   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 8   then
						x203328_g_doing = 3
						if IsObjValid (sceneId,x203328_g_dagongfuren) == 1 then
								NpcTalk(sceneId, x203328_g_dagongfuren, "������������ɪ���Ǹ����֪�����ָ���ô����", -1)
						end
		end
	elseif x203328_g_doing==3   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 11   then
						x203328_g_doing = 4
						if IsObjValid (sceneId,x203328_g_jifudagong) == 1 then
								NpcTalk(sceneId, x203328_g_jifudagong, "�Ͼ������Ƿǳ�ʱ�ڣ�Ҫ��������Щ�ɹ��ˣ��Ҳ�ϣ�������ʱ���ֳ��������������ǵĴ�ƣ�", -1)
						end
		end
	elseif x203328_g_doing==4   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 14   then
						x203328_g_doing = 5
						if IsObjValid (sceneId,x203328_g_dagongfuren) == 1 then
								NpcTalk(sceneId, x203328_g_dagongfuren, "�������ʲôʱ�����Ȣ�ң��������Ҹ����Ǹ����ҷϣ�", -1)
						end
		end
	elseif x203328_g_doing==5   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 17   then
						x203328_g_doing = 6
						if IsObjValid (sceneId,x203328_g_jifudagong) == 1 then
								NpcTalk(sceneId, x203328_g_jifudagong, "��ѽ�����������һ��ô��������׼�����ˣ���Ҫ����Щ�ɹ��˺������𡢿�ɽ������ɪ����Щ��һ���򾡣������˵�����������ɱ��������ʱ�򣬺ٺ٣�����������������������", -1)
						end
		end
	elseif x203328_g_doing==6   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 20   then
						x203328_g_doing = 7
						if IsObjValid (sceneId,x203328_g_dagongfuren) == 1 then
								NpcTalk(sceneId, x203328_g_dagongfuren, "�㣬�ɲ���ƭ�ң������Ҹ����Ĳ����㣡", -1)
						end
		end
	elseif x203328_g_doing==7   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 23   then
						x203328_g_doing = 8
						if IsObjValid (sceneId,x203328_g_jifudagong) == 1 then
								NpcTalk(sceneId, x203328_g_jifudagong, "��Ȼ����Ȼ����ʱ������һ���֣�������˹��������������ǵ������ˣ������ǲ����󹫣�Ҳ���ܰ�������ô����", -1)
						end
		end
	elseif x203328_g_doing==8   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 26   then
						x203328_g_doing = 9
						if IsObjValid (sceneId,x203328_g_dagongfuren) == 1 then
								NpcTalk(sceneId, x203328_g_dagongfuren, "�ߣ��ư������ģ�", -1)
						end
		end
	elseif x203328_g_doing==9   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 29   then
						x203328_g_doing = 10
						if IsObjValid (sceneId,x203328_g_jifudagong) == 1 then
								NpcTalk(sceneId, x203328_g_jifudagong, "�ٺ٣���ʱ���Ұ�����������Ȣ������", -1)
						end
		end
	elseif x203328_g_doing==10   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 32   then
						x203328_g_doing = 11
						if IsObjValid (sceneId,x203328_g_dagongfuren) == 1 then
								NpcTalk(sceneId, x203328_g_dagongfuren, "���컬��ģ��ߣ�", -1)
            		SetMonsterDir(sceneId,x203328_g_dagongfuren,60)
            end
		end
	elseif x203328_g_doing==11   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 35   then
						x203328_g_doing = 12
						if IsObjValid (sceneId,x203328_g_jifudagong) == 1 then
								NpcTalk(sceneId, x203328_g_jifudagong, "���ˣ��������ҵ��Ȼ�ȥ�ˣ��������������㣬��͵����ҵĺ���Ϣ�ɡ�", -1)
						end
						if IsObjValid (sceneId,x203328_g_dagongfuren) == 1 then
           	 		SetMonsterDir(sceneId,x203328_g_dagongfuren,120)
            end
		end
	elseif x203328_g_doing==12   then
		if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 38   then
						x203328_g_doing = 13
						if IsObjValid (sceneId,x203328_g_dagongfuren) == 1 then
								NpcTalk(sceneId, x203328_g_dagongfuren, "�ã��ǵ����������ң�", -1)
						end
		end
	elseif x203328_g_doing==13 then
			if GetCurrentTime() - x203328_g_PROTECTINFO.StartTime >= 41   then
				if IsPlayerStateNormal(sceneId,x203328_g_acceptid) ==1 then
									local misIndex = GetQuestIndexByID(sceneId, x203328_g_acceptid, x203328_g_MissionId)
									SetQuestByIndex(sceneId,x203328_g_acceptid,misIndex,0,1)
									SetQuestByIndex(sceneId,x203328_g_acceptid,misIndex,7,1)
									BeginQuestEvent(sceneId)
									AddQuestText(sceneId,format("̽������󹫵�����   %d/1", GetQuestParam(sceneId,x203328_g_acceptid,misIndex,0) ))
									EndQuestEvent(sceneId)
									DispatchQuestTips(sceneId,x203328_g_acceptid)
									CancelSpecificImpact(sceneId,x203328_g_acceptid,8704)
				end
				x203328_g_doing=14
				x203328_CloseTimer(sceneId, x203328_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x203328_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203328_g_doing =0
	x203328_g_acceptid =-1
	x203328_g_jifudagong = -1
	x203328_g_dagongfuren = -1
	x203328_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end