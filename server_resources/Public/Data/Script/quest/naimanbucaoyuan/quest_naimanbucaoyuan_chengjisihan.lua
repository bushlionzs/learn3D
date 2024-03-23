--���糡���ɼ�˼��

--MisDescBegin
x202001_g_ScriptId = 202001
x202001_g_MissionIdPre =1027
x202001_g_MissionId = 1028
x202001_g_LevelLess	= 	30 
x202001_g_MissionIdNext = 1032
x202001_g_Name	={}
x202001_g_ExtTarget={{type=20,n=1,target="��@npc_105104���μӳƺ���ʽ"}}
x202001_g_MissionName="���糡���ɼ�˼��"
x202001_g_MissionInfo="\t�󺹼�����������Ը�����μӷ⺹�����������᲻��ÿ���˶��������ģ�"  --��������
x202001_g_MissionTarget=""		
x202001_g_MissionCompleted="\t���ɹ�����ͳһ��һλΰ��Ŀɺ�֮���ˣ����������ɹ�֮�ң�"					--�������npc˵���Ļ�
x202001_g_ContinueInfo=""
x202001_g_MissionHelp =	""
x202001_g_DemandItem ={}
x202001_g_ExpBonus = 55000
x202001_g_BonusMoney1 =285
x202001_g_BonusMoney2 =0
x202001_g_BonusMoney3 =0
x202001_g_BonusMoney4 =0
x202001_g_BonusMoney5 =49
x202001_g_BonusMoney6 =0
x202001_g_BonusItem	=	{{item=13020015,n=1}}
x202001_g_BonusChoiceItem ={}
x202001_g_doing = 0
x202001_g_huoerci = -1
x202001_g_kuokuochu = -1
x202001_g_yuelunfuren = -1
x202001_g_heelun = -1
x202001_g_huazheng = -1
x202001_g_chengjisihan = -1
x202001_g_muhuali = -1
x202001_g_zhebie = -1
x202001_g_shuchi = -1
x202001_g_chahetai = -1
x202001_g_zhelemie = -1
x202001_g_chilaowen = -1
x202001_g_wokuotai = -1
x202001_g_tuolei = -1
x202001_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--MisDescEnd
--**********************************

function x202001_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x202001_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x202001_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x202001_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x202001_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x202001_g_MissionId, state, -1 )
		elseif IsHaveQuest(sceneId,selfId, x202001_g_MissionId) > 0 then
			local misIndex = GetQuestIndexByID(sceneId,selfId,x202001_g_MissionId)
			if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
						AddQuestNumText(sceneId, x202001_g_MissionId, "�μӷ⺹��䣡",0,1)
			else
					local state = GetQuestStateNM(sceneId,selfId,NPCId,x202001_g_MissionId)
					AddQuestTextNM( sceneId, selfId, NPCId, x202001_g_MissionId, state, -1 )
			end
		end
	end
end

function x202001_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x202001_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x202001_g_ExpBonus )
		end
		if x202001_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x202001_g_BonusMoney1 )
		end
		if x202001_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x202001_g_BonusMoney2 )
		end
		if x202001_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x202001_g_BonusMoney3 )
		end
		if x202001_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x202001_g_BonusMoney4 )
		end
		if x202001_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x202001_g_BonusMoney5 )
		end
		if x202001_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x202001_g_BonusMoney6 )
		end
		for i, item in x202001_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x202001_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x202001_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x202001_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x202001_g_MissionId) > 0 then
		if which == -1 then   
			if x202001_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x202001_g_MissionName)
						AddQuestText(sceneId,x202001_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x202001_g_ScriptId, x202001_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x202001_g_MissionName)
						AddQuestText(sceneId,x202001_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x202001_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x202001_g_ScriptId, x202001_g_MissionId);
			end
		elseif which == 1 then
			local misIndex = GetQuestIndexByID(sceneId,selfId,x202001_g_MissionId)                                                  
	    SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("�μӷ⺹���   %d/1", GetQuestParam(sceneId,selfId,misIndex,0) ))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"�ڴ������У��뱣���ྲ��")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x202001_g_ScriptId, x202001_g_MissionId);
	    if x202001_g_doing == 0 then
	    		x202001_g_PROTECTINFO.StartTime = GetCurrentTime()
					x202001_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 202001, "OnScneneTimer", 1)
					if x202001_g_PROTECTINFO.ScneneTimerIndex >=0 then
							x202001_g_doing = 1
							x202001_g_huoerci=CreateMonster(sceneId, 91,29,135,3,1,-1,-1,20,63000,180,"�����")
							if IsObjValid (sceneId,x202001_g_huoerci) == 1 then
									SetPatrolId(sceneId, x202001_g_huoerci, 11)
							end
							x202001_g_kuokuochu =NPCId
          end
	    end
	  end
  elseif x202001_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x202001_g_MissionName)
			AddQuestText(sceneId,x202001_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x202001_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x202001_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x202001_g_MissionHelp )
			end
			x202001_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x202001_g_ScriptId, x202001_g_MissionId);
  end
	
end
--**********************************

function x202001_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x202001_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x202001_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x202001_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
end
--**********************************
function x202001_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x202001_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x202001_g_MissionId  )
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
		if x202001_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x202001_g_MissionId, x202001_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x202001_Msg2toplayer( sceneId, selfId,0)
						if x202001_CheckSubmit(sceneId, selfId, NPCId) > 0 then
							local misIndex = GetQuestIndexByID(sceneId,selfId,x202001_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x202001_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x202001_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x202001_g_MissionId)
	  x202001_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x202001_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x202001_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x202001_g_BonusChoiceItem do
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
function x202001_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x202001_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x202001_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x202001_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x202001_g_MissionId) > 0 then
				x202001_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x202001_g_MissionId)
				x202001_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x202001_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x202001_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x202001_g_MissionIdNext )	
end

function x202001_GetBonus( sceneId, selfId,NpcID)
	  if x202001_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x202001_g_ExpBonus);
  	end
		if x202001_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x202001_g_BonusMoney1 )
	  end
		if x202001_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x202001_g_BonusMoney2 )
	  end
		if x202001_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x202001_g_BonusMoney3 )
		end
		if x202001_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x202001_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x202001_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x202001_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x202001_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x202001_g_BonusMoney6)
		end
end

function x202001_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x202001_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x202001_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x202001_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x202001_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x202001_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x202001_g_MissionName.."��", 0, 3)
				if x202001_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x202001_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x202001_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x202001_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x202001_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x202001_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x202001_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x202001_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x202001_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x202001_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x202001_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x202001_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x202001_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x202001_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x202001_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x202001_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x202001_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x202001_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x202001_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x202001_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
end

function x202001_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x202001_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x202001_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x202001_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x202001_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x202001_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x202001_OnScneneTimer(sceneId)
	if x202001_g_doing==1   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 3   then
						x202001_g_doing = 2
						x202001_g_yuelunfuren =FindMonsterByGUID( sceneId,105116)
						x202001_g_heelun =CreateMonster(sceneId, 61,30,108,3,1,-1,-1,20,60000,180,"�ö���")
						x202001_g_huazheng =CreateMonster(sceneId, 61,34,110,3,1,-1,-1,20,60000,180,"����")
						if IsObjValid (sceneId,x202001_g_huoerci) == 1 then
									NpcTalk(sceneId, x202001_g_huoerci, "���Ѿ���ʤ�����ˣ�", -1)
						end
						if IsObjValid (sceneId,x202001_g_heelun) == 1 then
								SetPatrolId(sceneId, x202001_g_heelun, 0)
						end
						if IsObjValid (sceneId,x202001_g_huazheng) == 1 then
								SetPatrolId(sceneId, x202001_g_huazheng, 1)
						end
		end
	elseif x202001_g_doing==2   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 6   then
						x202001_g_doing = 3
						if IsObjValid (sceneId,x202001_g_yuelunfuren) == 1 then
								NpcTalk(sceneId, x202001_g_yuelunfuren, "�벻���Ҷ���ľ�����н���֮�ɾͣ�", -1)
						end
						if IsObjValid (sceneId,x202001_g_huazheng) == 1 then
								NpcTalk(sceneId, x202001_g_huazheng, "������������", -1)
						end
						x202001_g_chengjisihan  =CreateMonster(sceneId, 774,42,123,3,1,-1,-1,20,57000,180,"��ľ��")
						x202001_g_muhuali  =CreateMonster(sceneId, 773,42,126,3,1,-1,-1,20,57000,180,"ľ����")
						x202001_g_zhebie  =CreateMonster(sceneId, 773,42,128,3,1,-1,-1,20,57000,180,"�ܱ�")
						x202001_g_shuchi  =CreateMonster(sceneId, 773,42,120,3,1,-1,-1,20,57000,180,"����")
						x202001_g_chahetai  =CreateMonster(sceneId, 773,42,118,3,1,-1,-1,20,57000,180,"���̨")
						x202001_g_zhelemie  =CreateMonster(sceneId, 773,45,127,3,1,-1,-1,20,57000,180,"������")
						x202001_g_chilaowen  =CreateMonster(sceneId, 773,45,126,3,1,-1,-1,20,57000,180,"������")
						x202001_g_wokuotai  =CreateMonster(sceneId, 773,45,121,3,1,-1,-1,20,57000,180,"����̨")
						x202001_g_tuolei  =CreateMonster(sceneId, 773,45,119,3,1,-1,-1,20,57000,180,"����")
						if IsObjValid (sceneId,x202001_g_chengjisihan) == 1 then
            		SetPatrolId(sceneId, x202001_g_chengjisihan, 2)
            end
            if IsObjValid (sceneId,x202001_g_muhuali) == 1 then
            		SetPatrolId(sceneId, x202001_g_muhuali, 3)
            end
            if IsObjValid (sceneId,x202001_g_zhebie) == 1 then
            		SetPatrolId(sceneId, x202001_g_zhebie, 5)
            end
            if IsObjValid (sceneId,x202001_g_shuchi) == 1 then
            		SetPatrolId(sceneId, x202001_g_shuchi, 4)
            end
            if IsObjValid (sceneId,x202001_g_chahetai) == 1 then
            		SetPatrolId(sceneId, x202001_g_chahetai, 6)
            end
            if IsObjValid (sceneId,x202001_g_zhelemie) == 1 then
            		SetPatrolId(sceneId, x202001_g_zhelemie, 7)
            end
            if IsObjValid (sceneId,x202001_g_chilaowen) == 1 then
            		SetPatrolId(sceneId, x202001_g_chilaowen, 8)
            end
            if IsObjValid (sceneId,x202001_g_wokuotai) == 1 then
            		SetPatrolId(sceneId, x202001_g_wokuotai, 9)
            end
            if IsObjValid (sceneId,x202001_g_tuolei) == 1 then
            		SetPatrolId(sceneId, x202001_g_tuolei, 10)
            end
		end
	elseif x202001_g_doing==3   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 9   then
						x202001_g_doing = 4
						if IsObjValid (sceneId,x202001_g_chengjisihan) == 1 then
								NpcTalk(sceneId, x202001_g_chengjisihan, "��л���������������ʤ����", -1)
						end
		end
	elseif x202001_g_doing==4   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 12   then
						x202001_g_doing = 5
						if IsObjValid (sceneId,x202001_g_kuokuochu) == 1 then
								NpcTalk(sceneId, x202001_g_kuokuochu, "������˵��ľ��Ҫ��Ϊ�����ɹ���������Ĵ󺹣����ɼ�˼����", -1)
						end
		end
	elseif x202001_g_doing==5   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 18   then
						x202001_g_doing = 6
						if IsObjValid (sceneId,x202001_g_kuokuochu) == 1 then
								NpcTalk(sceneId, x202001_g_kuokuochu, "����ϳг������ּ�⣬���ܡ��ɼ�˼��������ƺţ�", -1)
						end
		end
	elseif x202001_g_doing==6   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 21   then
						x202001_g_doing = 7
						if IsObjValid (sceneId,x202001_g_muhuali) == 1 then
								NpcTalk(sceneId, x202001_g_muhuali, "��󺹽��ܣ�", -1)
						end
						if IsObjValid (sceneId,x202001_g_zhebie) == 1 then
								NpcTalk(sceneId, x202001_g_zhebie, "��󺹽��ܣ�", -1)
						end
						if IsObjValid (sceneId,x202001_g_shuchi) == 1 then
								NpcTalk(sceneId, x202001_g_shuchi, "��󺹽��ܣ�", -1)
						end
						if IsObjValid (sceneId,x202001_g_chahetai) == 1 then
								NpcTalk(sceneId, x202001_g_chahetai, "��󺹽��ܣ�", -1)
						end
						if IsObjValid (sceneId,x202001_g_zhelemie) == 1 then
								NpcTalk(sceneId, x202001_g_zhelemie, "��󺹽��ܣ�", -1)
						end
						if IsObjValid (sceneId,x202001_g_chilaowen) == 1 then
								NpcTalk(sceneId, x202001_g_chilaowen, "��󺹽��ܣ�", -1)
						end
						if IsObjValid (sceneId,x202001_g_wokuotai) == 1 then
								NpcTalk(sceneId, x202001_g_wokuotai, "��󺹽��ܣ�", -1)
						end
						if IsObjValid (sceneId,x202001_g_tuolei) == 1 then
								NpcTalk(sceneId, x202001_g_tuolei, "��󺹽��ܣ�", -1)
						end
		end
	elseif x202001_g_doing==7   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 23   then
						x202001_g_doing = 8
						if IsObjValid (sceneId,x202001_g_kuokuochu) == 1 then
								NpcTalk(sceneId, x202001_g_kuokuochu, "�����ͻ�����ľ�棡", -1)
						end
		end
	elseif x202001_g_doing==8   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 26   then
						x202001_g_doing = 9
						if IsObjValid (sceneId,x202001_g_kuokuochu) == 1 then
								NpcTalk(sceneId, x202001_g_kuokuochu, "�����������ľ�棡", -1)
						end
		end
	elseif x202001_g_doing==9   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 29   then
						x202001_g_doing = 10
						if IsObjValid (sceneId,x202001_g_kuokuochu) == 1 then
								NpcTalk(sceneId, x202001_g_kuokuochu, "Ŀ���л����ľ�棡", -1)
						end
    end
	elseif x202001_g_doing==10   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 32   then
						x202001_g_doing = 11
						if IsObjValid (sceneId,x202001_g_kuokuochu) == 1 then
								NpcTalk(sceneId, x202001_g_kuokuochu, "�����й����ľ�棡", -1)
						end
		end
	elseif x202001_g_doing==11   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 35   then
						x202001_g_doing = 12
						if IsObjValid (sceneId,x202001_g_kuokuochu) == 1 then
								NpcTalk(sceneId, x202001_g_kuokuochu, "����Ը��", -1)
						end
		end
	elseif x202001_g_doing==12   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 37   then
						x202001_g_doing = 13
						if IsObjValid (sceneId,x202001_g_zhebie) == 1 then
								NpcTalk(sceneId, x202001_g_zhebie, "����ı�ӥ��", -1)
						end
		end
	elseif x202001_g_doing==13   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 39   then
						x202001_g_doing = 14
						if IsObjValid (sceneId,x202001_g_muhuali) == 1 then
								NpcTalk(sceneId, x202001_g_muhuali, "�������Ȯ��", -1)
						end
		end
	elseif x202001_g_doing==14   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 41   then
						x202001_g_doing = 15
						if IsObjValid (sceneId,x202001_g_shuchi) == 1 then
								NpcTalk(sceneId, x202001_g_shuchi, "����ĳ�����", -1)
						end
		end
	elseif x202001_g_doing==15   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 43   then
						x202001_g_doing = 16
						if IsObjValid (sceneId,x202001_g_chahetai) == 1 then
								NpcTalk(sceneId, x202001_g_chahetai, "�����������", -1)
						end
		end
	elseif x202001_g_doing==16   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 45   then
						x202001_g_doing = 17
						if IsObjValid (sceneId,x202001_g_tuolei) == 1 then
								NpcTalk(sceneId, x202001_g_tuolei, "����Ľ��ʣ�", -1)
						end
		end
	elseif x202001_g_doing==17   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 47   then
						x202001_g_doing = 18
						if IsObjValid (sceneId,x202001_g_wokuotai) == 1 then
								NpcTalk(sceneId, x202001_g_wokuotai, "����Ľ𰰣�", -1)
						end
		end
	elseif x202001_g_doing==18   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 49   then
						x202001_g_doing = 19
						if IsObjValid (sceneId,x202001_g_chilaowen) == 1 then
								NpcTalk(sceneId, x202001_g_chilaowen, "�Թ�������ǣ�", -1)
						end
		end
	elseif x202001_g_doing==19   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 51   then
						x202001_g_doing = 20
						if IsObjValid (sceneId,x202001_g_zhelemie) == 1 then
								NpcTalk(sceneId, x202001_g_zhelemie, "��Ѫ�����ɺ���", -1)
						end
		end
	elseif x202001_g_doing==20   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 53   then
						x202001_g_doing = 21
						if IsObjValid (sceneId,x202001_g_kuokuochu) == 1 then
								NpcTalk(sceneId, x202001_g_kuokuochu, "�㣬��Ӧ��������Ӧ��̿����Ӧ��¯��ѪӦ������", -1)
						end
		end
	elseif x202001_g_doing==21   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 56   then
						x202001_g_doing = 22
						if IsObjValid (sceneId,x202001_g_kuokuochu) == 1 then
								NpcTalk(sceneId, x202001_g_kuokuochu, "�ӽ�����������ǵĳɼ�˼����", -1)
						end
		end
	elseif x202001_g_doing==22   then
		if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 59   then
						x202001_g_doing = 23
						if IsObjValid (sceneId,x202001_g_muhuali) == 1 then
								NpcTalk(sceneId, x202001_g_muhuali, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_zhebie) == 1 then
								NpcTalk(sceneId, x202001_g_zhebie, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_shuchi) == 1 then
								NpcTalk(sceneId, x202001_g_shuchi, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_chahetai) == 1 then
								NpcTalk(sceneId, x202001_g_chahetai, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_zhelemie) == 1 then
								NpcTalk(sceneId, x202001_g_zhelemie, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_chilaowen) == 1 then
								NpcTalk(sceneId, x202001_g_chilaowen, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_wokuotai) == 1 then
								NpcTalk(sceneId, x202001_g_wokuotai, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_tuolei) == 1 then
								NpcTalk(sceneId, x202001_g_tuolei, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_yuelunfuren) == 1 then
								NpcTalk(sceneId, x202001_g_yuelunfuren, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_heelun) == 1 then
								NpcTalk(sceneId, x202001_g_heelun, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_huazheng) == 1 then
								NpcTalk(sceneId, x202001_g_huazheng, "�ɼ�˼����", -1)
						end
						if IsObjValid (sceneId,x202001_g_huoerci) == 1 then
								NpcTalk(sceneId, x202001_g_huoerci, "�ɼ�˼����", -1)
						end
		end
	elseif x202001_g_doing==23 then
			if GetCurrentTime() - x202001_g_PROTECTINFO.StartTime >= 63   then
				x202001_g_doing=24
				x202001_CloseTimer(sceneId, x202001_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x202001_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x202001_g_doing = 0
	x202001_g_huoerci = -1
	x202001_g_kuokuochu = -1
	x202001_g_yuelunfuren = -1
	x202001_g_heelun = -1
	x202001_g_huazheng = -1
	x202001_g_chengjisihan = -1
	x202001_g_muhuali = -1
	x202001_g_zhebie = -1
	x202001_g_shuchi = -1
	x202001_g_chahetai = -1
	x202001_g_zhelemie = -1
	x202001_g_chilaowen = -1
	x202001_g_wokuotai = -1
	x202001_g_tuolei = -1
	x202001_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end