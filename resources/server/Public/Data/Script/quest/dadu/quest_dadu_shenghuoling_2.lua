--�����ߡ�����ʥ��

--MisDescBegin
x270002_g_ScriptId = 270002
x270002_g_MissionIdPre =3542
x270002_g_MissionId = 3543
x270002_g_LevelLess	= 	40 
x270002_g_MissionIdNext = 3534
x270002_g_Name	={}
x270002_g_ExtTarget={{type=20,n=1,target="��@npc_139827���μӵ�ȼʥ����ʽ"}}
x270002_g_MissionName="�����ߡ�����ʥ��"
x270002_g_MissionInfo="\t#Y@myname#W����������İ����£�ʥ����ʧ�����ã��ҽ����¶���м����������������Ͼ���ȼʥ����ʥ���������䣬��Զָ���������̣�"  --��������
x270002_g_MissionTarget=""		
x270002_g_MissionCompleted="\t�ţ���������һ����죬���Ժ����ٲ������ǵ�������ˣ�"					--�������npc˵���Ļ�
x270002_g_ContinueInfo="\t��˵���̵�ȼʥ�����ʽ���ر����ʶ����ô��"
x270002_g_MissionHelp =	""
x270002_g_DemandItem ={}
x270002_g_BonusMoney1 =376
x270002_g_BonusMoney2 =0
x270002_g_BonusMoney3 =0
x270002_g_BonusMoney4 =0
x270002_g_BonusMoney5 =51
x270002_g_BonusMoney6 =0
x270002_g_BonusItem	=	{}
x270002_g_BonusChoiceItem ={}
x270002_g_ExpBonus = 93000
x270002_g_doing = 0
x270002_g_accid = -1
x270002_g_yangdingtian = -1
x270002_g_xiexun = -1
x270002_g_yintianzheng = -1
x270002_g_weiyixiao = -1
x270002_g_daiyisi = -1
x270002_g_mingjiaodizi = -1
x270002_g_mingjiaodizi2 = -1
x270002_g_mingjiaodizi3 = -1
x270002_g_mingjiaodizi4 = -1
x270002_g_mingjiaodizi5 = -1
x270002_g_mingjiaodizi6 = -1
x270002_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x270002_g_NpcGUID ={{ guid = 139827, name = "���˿"}, { guid = 140417, name = "������"}}
--MisDescEnd
--**********************************

function x270002_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x270002_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270002_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x270002_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270002_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270002_g_MissionId, state, -1 )
		end
	end
end

function x270002_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270002_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270002_g_ExpBonus )
		end
		if x270002_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270002_g_BonusMoney1 )
		end
		if x270002_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270002_g_BonusMoney2 )
		end
		if x270002_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270002_g_BonusMoney3 )
		end
		if x270002_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270002_g_BonusMoney4 )
		end
		if x270002_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270002_g_BonusMoney5 )
		end
		if x270002_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270002_g_BonusMoney6 )
		end
		for i, item in x270002_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270002_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270002_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270002_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270002_g_MissionId) > 0 then
		if which == -1 then   
			if x270002_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270002_g_MissionName)
						AddQuestText(sceneId,x270002_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270002_g_ScriptId, x270002_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270002_g_MissionName)
						AddQuestText(sceneId,x270002_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270002_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270002_g_ScriptId, x270002_g_MissionId);
			end
		elseif which == 1 then
			local misIndex = GetQuestIndexByID(sceneId,selfId,x270002_g_MissionId)                                                  
	    SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    BeginQuestEvent(sceneId)
			AddQuestText(sceneId,format("�ι۵�ȼʥ����ʽ   %d/1", GetQuestParam(sceneId,selfId,misIndex,0) ))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"����˵�������������飬�������̻���Զ�ǵ���Ķ��ݵģ�")
			EndQuestEvent()
			DispatchQuestEventList(sceneId, selfId, NPCId, x270002_g_ScriptId, x270002_g_MissionId);
	    if x270002_g_doing == 0 then
	    		x270002_g_PROTECTINFO.StartTime = GetCurrentTime()
					x270002_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270002, "OnScneneTimer", 1)
					if x270002_g_PROTECTINFO.ScneneTimerIndex >=0 then
							x270002_g_doing = 1
							x270002_g_accid = selfId
							x270002_g_xiexun=CreateMonster(sceneId, 18,97,252,3,1,-1,-1,20,55000,180,"лѷ","��ëʨ��")
							x270002_g_yintianzheng=CreateMonster(sceneId, 419,98,251,3,1,-1,-1,20,55000,0,"������","��üӥ��")
							x270002_g_weiyixiao=CreateMonster(sceneId, 18,99,252,3,1,-1,-1,20,55000,0,"ΤһЦ","��������")
							if IsObjValid (sceneId,x270002_g_xiexun) == 1 then
									SetPatrolId(sceneId, x270002_g_xiexun, 19)
							end
							if IsObjValid (sceneId,x270002_g_yintianzheng) == 1 then
									SetPatrolId(sceneId, x270002_g_yintianzheng, 20)
							end
							if IsObjValid (sceneId,x270002_g_weiyixiao) == 1 then
									SetPatrolId(sceneId, x270002_g_weiyixiao, 21)
							end
							x270002_g_daiyisi =NPCId
							if IsObjValid (sceneId,x270002_g_daiyisi) == 1 then
									NpcTalk(sceneId, x270002_g_daiyisi, "ʥ����ʽ���ڿ�ʼ��", -1)
							end
          end
	    end
	  end
  elseif x270002_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270002_g_MissionName)
			AddQuestText(sceneId,x270002_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270002_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270002_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270002_g_MissionHelp )
			end
			x270002_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270002_g_ScriptId, x270002_g_MissionId);
  end
	
end
--**********************************

function x270002_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270002_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270002_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270002_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
end
--**********************************
function x270002_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270002_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270002_g_MissionId  )
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
		if x270002_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270002_g_MissionId, x270002_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270002_Msg2toplayer( sceneId, selfId,0)
						if x270002_CheckSubmit(sceneId, selfId, NPCId) > 0 then
							local misIndex = GetQuestIndexByID(sceneId,selfId,x270002_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270002_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270002_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270002_g_MissionId)
	  x270002_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x270002_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270002_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270002_g_BonusChoiceItem do
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
function x270002_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270002_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270002_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270002_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270002_g_MissionId) > 0 then
				x270002_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270002_g_MissionId)
				x270002_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270002_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270002_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270002_g_MissionIdNext )	
end

function x270002_GetBonus( sceneId, selfId,NpcID)
	  if x270002_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270002_g_ExpBonus);
  	end
		if x270002_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270002_g_BonusMoney1 )
	  end
		if x270002_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270002_g_BonusMoney2 )
	  end
		if x270002_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270002_g_BonusMoney3 )
		end
		if x270002_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270002_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270002_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270002_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270002_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270002_g_BonusMoney6)
		end
end

function x270002_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270002_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270002_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270002_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270002_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270002_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270002_g_MissionName.."��", 0, 3)
				if x270002_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270002_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270002_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270002_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270002_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270002_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270002_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270002_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270002_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270002_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270002_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270002_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270002_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270002_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270002_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270002_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270002_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270002_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270002_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270002_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
		if IsHaveQuest(sceneId,selfId, x270002_g_MissionId) > 0 then
				if npcGuid == x270002_g_NpcGUID[1].guid then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x270002_g_MissionId)
					if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then 
						AddQuestNumText(sceneId, x270002_g_MissionId, "�������������е�ȼʥ����ʽ",0,1)
					end
				elseif npcGuid == x270002_g_NpcGUID[2].guid then
						local state = GetQuestStateNM(sceneId,selfId,npcId,x270002_g_MissionId)
						AddQuestTextNM( sceneId, selfId, npcId, x270002_g_MissionId, state, -1 )
				end
		end
end

function x270002_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270002_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270002_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270002_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270002_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270002_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270002_OnScneneTimer(sceneId)
	if x270002_g_doing==1   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 7   then
						x270002_g_doing = 2
						if IsObjValid (sceneId,x270002_g_yintianzheng) == 1 then
								NpcTalk(sceneId, x270002_g_yintianzheng, "�Ҿ�֪���ҽ̻�ƽ���ɹ�����ѹصġ�", -1)
						end
		end
	elseif x270002_g_doing==2   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 10   then
						x270002_g_doing = 3
						if IsObjValid (sceneId,x270002_g_weiyixiao) == 1 then
								NpcTalk(sceneId, x270002_g_weiyixiao, "��ζ��������λ��������������", -1)
						end
		end
	elseif x270002_g_doing==3   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 13   then
						x270002_g_doing = 4
						if IsObjValid (sceneId,x270002_g_yintianzheng) == 1 then
								NpcTalk(sceneId, x270002_g_yintianzheng, "�������������������ҽ�֮���£�", -1)
						end
            x270002_g_mingjiaodizi=CreateMonster(sceneId, 1610,96,252.7,3,1,-1,-1,20,42000,180,"���̵���")
            x270002_g_mingjiaodizi2=CreateMonster(sceneId, 1610,97,253,3,1,-1,-1,20,42000,180,"���̵���")
            x270002_g_mingjiaodizi3=CreateMonster(sceneId, 1610,97,254,3,1,-1,-1,20,42000,180,"���̵���")
            x270002_g_mingjiaodizi4=CreateMonster(sceneId, 1610,103,252,3,1,-1,-1,20,42000,180,"���̵���")
            x270002_g_mingjiaodizi5=CreateMonster(sceneId, 1610,102,252,3,1,-1,-1,20,42000,180,"���̵���")
            x270002_g_mingjiaodizi6=CreateMonster(sceneId, 1610,103,252,3,1,-1,-1,20,42000,180,"���̵���")
            if IsObjValid (sceneId,x270002_g_mingjiaodizi) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi, 22)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi2) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi2, 23)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi3) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi3, 24)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi4) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi4, 25)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi5) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi5, 26)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi6) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi6, 27)
            end
		end
	elseif x270002_g_doing==4   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 19   then
						x270002_g_doing = 5
						if IsObjValid (sceneId,x270002_g_daiyisi) == 1 then
								NpcTalk(sceneId, x270002_g_daiyisi, "���������볡��ȼʥ��", -1)
						end
		end
	elseif x270002_g_doing==5   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 21   then
						x270002_g_doing = 6
						if IsObjValid (sceneId,x270002_g_yintianzheng) == 1 then
            		SetMonsterDir(sceneId,x270002_g_yintianzheng,30)
            end
            if IsObjValid (sceneId,x270002_g_weiyixiao) == 1 then
            		SetMonsterDir(sceneId,x270002_g_weiyixiao,30)
            end
            if IsObjValid (sceneId,x270002_g_xiexun) == 1 then
            		SetMonsterDir(sceneId,x270002_g_xiexun,30)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi,30)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi2) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi2,30)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi3) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi3,30)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi4) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi4,30)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi5) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi5,30)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi6) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi6,30)
            end
            x270002_g_yangdingtian=CreateMonster(sceneId, 1616,101,255,3,1,-1,-1,20,34000,180,"������")
            if IsObjValid (sceneId,x270002_g_yangdingtian) == 1 then
            		SetPatrolId(sceneId, x270002_g_yangdingtian, 28)
            end
		end
	elseif x270002_g_doing==6   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 23   then
						x270002_g_doing = 7
						if IsObjValid (sceneId,x270002_g_mingjiaodizi) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi,120)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi2) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi2,120)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi3) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi3,120)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi4) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi4,300)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi5) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi5,300)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi6) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi6,300)
            end
		end
	elseif x270002_g_doing==7   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 29   then
						x270002_g_doing = 8
						if IsObjValid (sceneId,x270002_g_yintianzheng) == 1 then
            		SetMonsterDir(sceneId,x270002_g_yintianzheng,120)
            end
            if IsObjValid (sceneId,x270002_g_weiyixiao) == 1 then
            		SetMonsterDir(sceneId,x270002_g_weiyixiao,120)
            end
            if IsObjValid (sceneId,x270002_g_xiexun) == 1 then
            		SetMonsterDir(sceneId,x270002_g_xiexun,120)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi,210)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi2) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi2,210)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi3) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi3,210)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi4) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi4,210)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi5) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi5,210)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi6) == 1 then
            		SetMonsterDir(sceneId,x270002_g_mingjiaodizi6,210)
            end
		end
	elseif x270002_g_doing==8   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 35   then
						x270002_g_doing = 9
						if IsObjValid (sceneId,x270002_g_yintianzheng) == 1 then
            		SetMonsterDir(sceneId,x270002_g_yintianzheng,210)
            end
            if IsObjValid (sceneId,x270002_g_weiyixiao) == 1 then
            		SetMonsterDir(sceneId,x270002_g_weiyixiao,210)
            end
            if IsObjValid (sceneId,x270002_g_xiexun) == 1 then
            		SetMonsterDir(sceneId,x270002_g_xiexun,210)
            end
		end
	elseif x270002_g_doing==9   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 38   then
			if IsPlayerStateNormal(sceneId,x270002_g_accid) ==1 then
						x270002_g_doing = 10
						if IsObjValid (sceneId,x270002_g_yintianzheng) == 1 then
								SetPatrolId(sceneId, x270002_g_yintianzheng, 29)
						end
						if IsObjValid (sceneId,x270002_g_weiyixiao) == 1 then
            		SetPatrolId(sceneId, x270002_g_weiyixiao, 30)
            end
            if IsObjValid (sceneId,x270002_g_xiexun) == 1 then
            		SetPatrolId(sceneId, x270002_g_xiexun, 31)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi, 32)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi2) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi2, 33)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi3) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi3, 34)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi4) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi4, 35)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi5) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi5, 36)
            end
            if IsObjValid (sceneId,x270002_g_mingjiaodizi6) == 1 then
            		SetPatrolId(sceneId, x270002_g_mingjiaodizi6, 37)
            end
            if IsPlayerStateNormal(sceneId,x270002_g_accid) ==1 then
            		CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, x270002_g_accid, 6 )
            end
      end
		end
	elseif x270002_g_doing==10   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 43   then
						x270002_g_doing = 11
						if IsObjValid (sceneId,x270002_g_yangdingtian) == 1 then
								NpcTalk(sceneId, x270002_g_yangdingtian, "����ʥ�𣬷��Ҳ������������ˣ��ǻ�ʵ�࣡", -1)
						end
		end
	elseif x270002_g_doing==11   then
		if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 47   then
						x270002_g_doing = 12
						if IsObjValid (sceneId,x270002_g_yangdingtian) == 1 then
								NpcTalk(sceneId, x270002_g_yangdingtian, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
						if IsObjValid (sceneId,x270002_g_yintianzheng) == 1 then
								NpcTalk(sceneId, x270002_g_yintianzheng, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
						if IsObjValid (sceneId,x270002_g_weiyixiao) == 1 then
								NpcTalk(sceneId, x270002_g_weiyixiao, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
						if IsObjValid (sceneId,x270002_g_xiexun) == 1 then
								NpcTalk(sceneId, x270002_g_xiexun, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
						if IsObjValid (sceneId,x270002_g_mingjiaodizi) == 1 then
								NpcTalk(sceneId, x270002_g_mingjiaodizi, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
						if IsObjValid (sceneId,x270002_g_mingjiaodizi2) == 1 then
								NpcTalk(sceneId, x270002_g_mingjiaodizi2, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
						if IsObjValid (sceneId,x270002_g_mingjiaodizi3) == 1 then
								NpcTalk(sceneId, x270002_g_mingjiaodizi3, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
						if IsObjValid (sceneId,x270002_g_mingjiaodizi4) == 1 then
								NpcTalk(sceneId, x270002_g_mingjiaodizi4, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
						if IsObjValid (sceneId,x270002_g_mingjiaodizi5) == 1 then
								NpcTalk(sceneId, x270002_g_mingjiaodizi5, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
						if IsObjValid (sceneId,x270002_g_mingjiaodizi6) == 1 then
								NpcTalk(sceneId, x270002_g_mingjiaodizi6, "����λ�������οࣿΪ�Ƴ���Ω�����̡�", -1)
						end
		end
	elseif x270002_g_doing==12 then
			if GetCurrentTime() - x270002_g_PROTECTINFO.StartTime >= 55   then
				x270002_g_doing=13
				x270002_CloseTimer(sceneId, x270002_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x270002_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270002_g_doing =0
	x270002_g_accid = -1
	x270002_g_yangdingtian = -1
	x270002_g_xiexun = -1
	x270002_g_yintianzheng = -1
	x270002_g_weiyixiao = -1
	x270002_g_daiyisi = -1
	x270002_g_mingjiaodizi = -1
	x270002_g_mingjiaodizi2 = -1
	x270002_g_mingjiaodizi3 = -1
	x270002_g_mingjiaodizi4 = -1
	x270002_g_mingjiaodizi5 = -1
	x270002_g_mingjiaodizi6 = -1
	x270002_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end