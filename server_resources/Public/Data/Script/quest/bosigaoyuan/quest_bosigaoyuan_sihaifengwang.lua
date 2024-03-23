--�����ߡ��ĺ�����

--MisDescBegin
x203318_g_ScriptId = 203318
x203318_g_MissionIdPre = 770
x203318_g_MissionId = 771
x203318_g_LevelLess	= 	84
x203318_g_MissionIdNext = -1
x203318_g_Name	={}
x203318_g_ExtTarget={{type=20,n=1,target="��@npc_116000����ս��"}}
x203318_g_MissionName="���糡���ĺ�����"
x203318_g_MissionInfo="\t�����������ħ��������Ҳ�Ѿ����־��ܣ��Ӵ��Ժ����޹����������ϣ���Ҳû���ܹ����Ҵ��ɹŵ۹�Ϊ�У��콫�������Ϣ�������󺹣�"  --��������
x203318_g_MissionTarget=""		
x203318_g_MissionCompleted="\t#Y@myname#W����ô���Ǵ��������ģ��Ǹղŷ⺹����ϴ󺹿����������쳣�˰ɡ�"					--�������npc˵���Ļ�
x203318_g_ContinueInfo="\t�칦�����Ͼ�Ҫ��ʼ�ˣ�"
x203318_g_MissionHelp =	""
x203318_g_DemandItem ={}
x203318_g_ExpBonus = 626000
x203318_g_BonusMoney1 =840
x203318_g_BonusMoney2 =0
x203318_g_BonusMoney3 =0
x203318_g_BonusMoney4 =0
x203318_g_BonusMoney5 =96
x203318_g_BonusMoney6 =0
x203318_g_BonusItem	=	{}
x203318_g_BonusChoiceItem ={}
x203318_g_doing = 0
x203318_g_accid = -1
x203318_g_mengguwushi1 = -1
x203318_g_mengguwushi2 = -1
x203318_g_mengguwushi3 = -1
x203318_g_mengguwushi4 = -1
x203318_g_mengguwushi5 = -1
x203318_g_mengguwushi6 = -1
x203318_g_mengguwushi7 = -1
x203318_g_mengguwushi8 = -1
x203318_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x203318_g_NpcGUID ={{ guid = 116000, name = "�ɼ�˼��"}, {guid = 116003, name ="�ٲ�̨"}}
--MisDescEnd
--**********************************

function x203318_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x203318_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x203318_g_MissionId, state, -1 )
		end
	end
end

function x203318_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203318_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203318_g_ExpBonus )
		end
		if x203318_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203318_g_BonusMoney1 )
		end
		if x203318_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203318_g_BonusMoney2 )
		end
		if x203318_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203318_g_BonusMoney3 )
		end
		if x203318_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203318_g_BonusMoney4 )
		end
		if x203318_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203318_g_BonusMoney5 )
		end
		if x203318_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203318_g_BonusMoney6 )
		end
		for i, item in x203318_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203318_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203318_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) > 0 then
		if which == -1 then   
			if x203318_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203318_g_MissionName)
						AddQuestText(sceneId,x203318_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203318_g_ScriptId, x203318_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203318_g_MissionName)
						AddQuestText(sceneId,x203318_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203318_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203318_g_ScriptId, x203318_g_MissionId);
			end
		elseif which == 1 then
			local misIndex = GetQuestIndexByID(sceneId,selfId,x203318_g_MissionId)                                                  
	    SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("�ι��칦��   %d/1", GetQuestParam(sceneId,selfId,misIndex,0) ))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"��������������˵����ӣ�")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x203318_g_ScriptId, x203318_g_MissionId);
			x203318_g_chengjisihan =FindMonsterByGUID( sceneId,116000)
			x203318_g_guobaoyu =FindMonsterByGUID( sceneId,116009)
			x203318_g_hubilie=FindMonsterByGUID( sceneId,116007)
			x203318_g_badu =FindMonsterByGUID( sceneId,116019)
			x203318_g_mengge =FindMonsterByGUID( sceneId,116006)
			x203318_g_qiuchuji =FindMonsterByGUID( sceneId,116005)
			x203318_g_xuliewu =FindMonsterByGUID( sceneId,116004)
			x203318_g_subutai =FindMonsterByGUID( sceneId,116003)
			x203318_g_zhebie =FindMonsterByGUID( sceneId,116002)
	    --if x203318_g_doing == 0 then
	    		x203318_g_PROTECTINFO.StartTime = GetCurrentTime()
					x203318_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203318, "OnScneneTimer", 1)
					if x203318_g_PROTECTINFO.ScneneTimerIndex >=0 then
							x203318_g_doing = 1
							x203318_g_accid = selfId
							x203318_g_mengguwushi1=CreateMonster(sceneId, 932,198,198,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi2=CreateMonster(sceneId, 932,195,198,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi3=CreateMonster(sceneId, 932,191,198,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi4=CreateMonster(sceneId, 932,188,198,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi5=CreateMonster(sceneId, 932,188,195,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi6=CreateMonster(sceneId, 932,191,195,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi7=CreateMonster(sceneId, 932,194,195,3,1,-1,-1,20,70000,0)
							x203318_g_mengguwushi8=CreateMonster(sceneId, 932,198,195,3,1,-1,-1,20,70000,0)
							--if IsObjValid (sceneId,x203318_g_guobaoyu) == 1 then
									--SetPatrolId(sceneId, x203318_g_guobaoyu, 7)
							--end
							if IsObjValid (sceneId,x203318_g_hubilie) == 1 then
									SetPatrolId(sceneId, x203318_g_hubilie, 9)
							end
							if IsObjValid (sceneId,x203318_g_badu) == 1 then
									SetPatrolId(sceneId, x203318_g_badu, 7)
							end
							if IsObjValid (sceneId,x203318_g_mengge) == 1 then
									SetPatrolId(sceneId, x203318_g_mengge, 10)
							end
							--if IsObjValid (sceneId,x203318_g_qiuchuji) == 1 then
									--SetPatrolId(sceneId, x203318_g_qiuchuji, 11)
							--end					
							if IsObjValid (sceneId,x203318_g_xuliewu) == 1 then
									SetPatrolId(sceneId, x203318_g_xuliewu, 8)
							end							
							--if IsObjValid (sceneId,x203318_g_subutai) == 1 then
									--SetPatrolId(sceneId, x203318_g_subutai, 8)
							--end	
							--if IsObjValid (sceneId,x203318_g_zhebie) == 1 then
									--SetPatrolId(sceneId, x203318_g_zhebie, 13)
							--end											
							x203318_g_chengjisihan =NPCId
							if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
									NpcTalk(sceneId, x203318_g_chengjisihan, "��ʿ�ǣ������Ǿٱ�������", -1)
							end
          end
	   -- end
	  end
  elseif x203318_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203318_g_MissionName)
			AddQuestText(sceneId,x203318_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203318_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203318_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203318_g_MissionHelp )
			end
			x203318_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203318_g_ScriptId, x203318_g_MissionId);
  end
	
end
--**********************************

function x203318_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x203318_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x203318_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
end
--**********************************
function x203318_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203318_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203318_g_MissionId  )
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
		if x203318_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203318_g_MissionId, x203318_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203318_Msg2toplayer( sceneId, selfId,0)
						if x203318_CheckSubmit(sceneId, selfId, NPCId) > 0 then
							local misIndex = GetQuestIndexByID(sceneId,selfId,x203318_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203318_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203318_g_MissionId)
	  x203318_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203318_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203318_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203318_g_BonusChoiceItem do
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
function x203318_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203318_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203318_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203318_g_MissionId) > 0 then
				x203318_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203318_g_MissionId)
				x203318_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203318_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203318_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203318_g_MissionIdNext )	
end

function x203318_GetBonus( sceneId, selfId,NpcID)
	  if x203318_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203318_g_ExpBonus);
  	end
		if x203318_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203318_g_BonusMoney1 )
	  end
		if x203318_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203318_g_BonusMoney2 )
	  end
		if x203318_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203318_g_BonusMoney3 )
		end
		if x203318_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203318_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203318_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203318_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203318_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203318_g_BonusMoney6)
		end
end

function x203318_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203318_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203318_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203318_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203318_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203318_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203318_g_MissionName.."��", 0, 3)
				if x203318_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203318_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203318_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203318_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203318_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203318_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203318_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203318_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203318_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203318_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203318_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203318_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203318_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203318_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203318_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203318_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203318_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203318_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203318_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203318_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	
		if IsHaveQuest(sceneId,selfId, x203318_g_MissionId) > 0 then
			
				if npcGuid == x203318_g_NpcGUID[1].guid then	
					local misIndex = GetQuestIndexByID(sceneId,selfId,x203318_g_MissionId)
					if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
						AddQuestNumText(sceneId, x203318_g_MissionId, "����λ�����������н�",0,1)
					end
				elseif npcGuid == x203318_g_NpcGUID[2].guid then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203318_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203318_g_MissionId, state, -1 )
				end
		end
end

function x203318_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203318_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203318_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203318_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203318_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203318_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x203318_OnScneneTimer(sceneId)
	if x203318_g_doing==1   then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 8   then
				x203318_g_doing = 2
				if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
						NpcTalk(sceneId, x203318_g_chengjisihan, "�һƽ������������ﶼ�Ѿ�����ɲģ����죬��Ҫ�������е����طָ���Щ�����ǡ�", -1)
						SetMonsterDir(sceneId,x203318_g_badu,180)
				end
		end
	elseif x203318_g_doing==2   then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 11   then
						x203318_g_doing = 3
						if IsObjValid (sceneId,x203318_g_subutai) == 1 then
								NpcTalk(sceneId, x203318_g_subutai, "��ƾ�󺹷Ը���", -1)
						end
		end
	elseif x203318_g_doing==3   then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 16   then
						x203318_g_doing = 4
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "����أ����ս֮�������湦���䴦�澳��������ս��׿�����ҽ�����Ϊ����֮�����ƹ��Ҵ��ɹŵ۹����������Ľ�����", -1)
						end
            if IsObjValid (sceneId,x203318_g_xuliewu) == 1 then
								NpcTalk(sceneId, x203318_g_xuliewu, "��л�󺹣�����أ��������������", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi3) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi3, "�ɼ�˼�����ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi1) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi1, "�ɼ�˼�����ɼ�˼����", -1)
						end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi) == 1 then
            
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi, 22)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi2) == 1 then
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi2, 23)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi3) == 1 then
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi3, 24)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi4) == 1 then
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi4, 25)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi5) == 1 then
            	--	SetPatrolId(sceneId, x203318_g_mingjiaodizi5, 26)
            --end
            --if IsObjValid (sceneId,x203318_g_mingjiaodizi6) == 1 then
            		--SetPatrolId(sceneId, x203318_g_mingjiaodizi6, 27)
            --end
		end
	elseif x203318_g_doing==4   then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 25  then
						x203318_g_doing = 5
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "�ɸ磬�¶���ı����������ƵУ��ӹ���ΰ������ɸ�Ϊ����֮����", -1)								
						end
						 if IsObjValid (sceneId,x203318_g_mengge) == 1 then
								NpcTalk(sceneId, x203318_g_mengge, "л�󺹣��ɸ�һ�������ɹŽ�����", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi6) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi6, "�ɼ�˼�����ɼ�˼����", -1)
						end
            if IsObjValid (sceneId,x203318_g_mengguwushi4) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi4, "�ɼ�˼�����ɼ�˼����", -1)
						end						
		end
	elseif x203318_g_doing==5   then
	 if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 35  then
						x203318_g_doing = 6
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "�ζ��������ޱȣ�������������ս֮ʱ����ʿ�䣡�񣬷�ζ�Ϊŷ��֮����", -1)								
						end
						if IsObjValid (sceneId,x203318_g_badu) == 1 then
								NpcTalk(sceneId, x203318_g_badu, "�ζ�����л�󺹣�", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi6) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi6, "������������", -1)
						end
						if IsObjValid (sceneId,x203318_g_subutai) == 1 then
								NpcTalk(sceneId, x203318_g_subutai, "ŷ�ޣ���ʲô����", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi3) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi3, "������������", -1)
						end
	 end
	elseif x203318_g_doing==6  then
		if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 45   then
						x203318_g_doing = 7
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "��ϣ���ƽ��������������μ�ס��һ�����壬ֻ�����ո�����Ļ�����������񣬲��ܸ���ǿ��������߲������ҳɼ�˼�����ɾ��Ӵ��ɹź�����Ҳ�������ң����Ǹ����������壬ǧǧ���������ƽ�밲��������", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi1) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi1, "�ɼ�˼�����ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengguwushi4) == 1 then
								NpcTalk(sceneId, x203318_g_mengguwushi4, "�ɼ�˼�����ɼ�˼����", -1)
						end
		end
	elseif x203318_g_doing==7 then
	  if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 55  then
						x203318_g_doing = 8
						if IsObjValid (sceneId,x203318_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x203318_g_chengjisihan, "����������һ���Σ��μ����ҵİ�����ľ�ϣ��μ��������ɣ������μ��˺ܶ�ܶ��ˡ�������Ƕ������ˣ��ң�Ҫ��л��Щ��������Ϊ�е��ˣ������ǣ�������ң�����ĳɼ�˼��������������죬������һ����", -1)
						end
						if IsObjValid (sceneId,x203318_g_mengge) == 1 then
								NpcTalk(sceneId, x203318_g_mengge, "�󺹣�", -1)
						end
						if IsObjValid (sceneId,x203318_g_xuliewu) == 1 then
								NpcTalk(sceneId, x203318_g_xuliewu, "�󺹡�����", -1)
						end
						if IsObjValid (sceneId,x203318_g_hubilie) == 1 then
								NpcTalk(sceneId, x203318_g_hubilie, "�󺹡���", -1)
						end
						if IsObjValid (sceneId,x203318_g_badu) == 1 then
								NpcTalk(sceneId, x203318_g_badu, "������", -1)
						end
			end
	elseif x203318_g_doing==8 then
			if GetCurrentTime() - x203318_g_PROTECTINFO.StartTime >= 70  then
				x203318_g_doing=9
				if x203318_g_doing ==9 then
				x203318_CloseTimer(sceneId, x203318_g_PROTECTINFO.ScneneTimerIndex)
				end
			end
	  end
 end




--**********************************
--�رռ�ʱ��
--**********************************
function x203318_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203318_g_doing =0
	x203318_g_accid = -1
	x203318_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}   --����ʱ����Ϊ��
	SetPos(sceneId,x203318_g_badu,186,200)
	SetPos(sceneId,x203318_g_xuliewu,186,194)
	SetPos(sceneId,x203318_g_mengge,201,200)
	SetPos(sceneId,x203318_g_hubilie,201,194)
	SetPatrolId(sceneId, x203318_g_hubilie, -1)
	SetPatrolId(sceneId, x203318_g_badu, -1)
  SetPatrolId(sceneId, x203318_g_mengge, -1)
	SetPatrolId(sceneId, x203318_g_xuliewu, -1)
	SetMonsterDir(sceneId,x203318_g_badu,180)
	SetMonsterDir(sceneId,x203318_g_xuliewu,180)
	SetMonsterDir(sceneId,x203318_g_mengge,180)
	SetMonsterDir(sceneId,x203318_g_hubilie,180)
	x203318_g_mengguwushi1 = -1
  x203318_g_mengguwushi2 = -1
  x203318_g_mengguwushi3 = -1
  x203318_g_mengguwushi4 = -1
  x203318_g_mengguwushi5 = -1
  x203318_g_mengguwushi6 = -1
end