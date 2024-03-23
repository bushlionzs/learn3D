--�����ߡ������Ե<��>

--MisDescBegin
x270010_g_ScriptId = 270010
x270010_g_MissionIdPre =3500
x270010_g_MissionId = 3501
x270010_g_LevelLess	= 	45 
x270010_g_MissionIdNext = 3502
x270010_g_Name	={}
x270010_g_noDemandItem ={{id=13020314,num=1}}
x270010_g_ExtTarget={{type=20,n=1,target="��@npc_141010���¾�̳ѯ�ʺ����үү"}}
x270010_g_MissionName="�����ߡ������Ե<��>"
x270010_g_MissionInfo="\t�ҿ�������Ҳ��һ���˲ţ�ݺݺ��ò���磬��������ϲ����ԵҲ��ʧΪ��һ�����£������һ���Щ����Ҫ����үү�������\n\t������ȥ��һ̳���ƣ��������ڳǱߵĴ����£�������һ�����ú��ߺ������ͷ�Ⱦƣ������ȵ�����ʱ����������˵������£���һ��������㡣"  --��������
x270010_g_MissionTarget=""		
x270010_g_MissionCompleted="\t��������ϲ��˵����\n\tүү�����ô˵ô����ѽ���ǿ�����̫���ˣ��ҽ������ǳ���֮�������д�����ǣ�Ҳ��ʧΪ����һ����"					--�������npc˵���Ļ�
x270010_g_ContinueInfo="\t������үү����"
x270010_g_MissionHelp =	""
x270010_g_DemandItem ={}
x270010_g_BonusMoney1 =376
x270010_g_BonusMoney2 =0
x270010_g_BonusMoney3 =0
x270010_g_BonusMoney4 =0
x270010_g_BonusMoney5 =56
x270010_g_BonusMoney6 =0
x270010_g_BonusItem	=	{}
x270010_g_BonusChoiceItem ={}
x270010_g_ExpBonus = 112000
--MisDescEnd
x270010_g_doing = 0
x270010_g_yuelao =-1
x270010_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--**********************************

function x270010_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270010_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270010_g_MissionIdPre)> 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x270010_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x270010_g_MissionId, state, -1 )
	end
end

function x270010_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270010_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270010_g_ExpBonus )
		end
		if x270010_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270010_g_BonusMoney1 )
		end
		if x270010_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270010_g_BonusMoney2 )
		end
		if x270010_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270010_g_BonusMoney3 )
		end
		if x270010_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270010_g_BonusMoney4 )
		end
		if x270010_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270010_g_BonusMoney5 )
		end
		if x270010_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270010_g_BonusMoney6 )
		end
		for i, item in x270010_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270010_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270010_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270010_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270010_g_MissionId) > 0 then
			if x270010_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270010_g_MissionName)
						AddQuestText(sceneId,x270010_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270010_g_ScriptId, x270010_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270010_g_MissionName)
						AddQuestText(sceneId,x270010_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270010_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270010_g_ScriptId, x270010_g_MissionId);
			end
  elseif x270010_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270010_g_MissionName)
			AddQuestText(sceneId,x270010_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270010_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270010_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270010_g_MissionHelp )
			end
			x270010_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270010_g_ScriptId, x270010_g_MissionId);
  end
	
end
--**********************************

function x270010_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x270010_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x270010_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == 1 then
			return 1
	end
	return 0
end
--**********************************
function x270010_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270010_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270010_g_MissionId  )
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
		if x270010_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		  BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x270010_g_noDemandItem[1].id, x270010_g_noDemandItem[1].num )             
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x270010_g_MissionId, x270010_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270010_Msg2toplayer( sceneId, selfId,0)
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

function x270010_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270010_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270010_g_MissionId)
	  x270010_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270010_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x270010_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270010_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270010_g_BonusChoiceItem do
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
function x270010_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270010_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270010_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270010_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270010_g_MissionId) > 0 then
				x270010_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270010_g_MissionId)
				x270010_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270010_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270010_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270010_g_MissionIdNext )	
end

function x270010_GetBonus( sceneId, selfId,NpcID)
	  if x270010_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270010_g_ExpBonus);
  	end
		if x270010_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270010_g_BonusMoney1 )
	  end
		if x270010_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270010_g_BonusMoney2 )
	  end
		if x270010_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270010_g_BonusMoney3 )
		end
		if x270010_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270010_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270010_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270010_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270010_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270010_g_BonusMoney6)
		end
end

function x270010_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270010_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270010_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270010_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270010_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270010_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270010_g_MissionName.."��", 0, 3)
				if x270010_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270010_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270010_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270010_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270010_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270010_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270010_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270010_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270010_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270010_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270010_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270010_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270010_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270010_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270010_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270010_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
end

function x270010_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	
end

function x270010_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

function x270010_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270010_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x270010_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270010_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270010_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270010_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270010_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270010_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270010_OnScneneTimer(sceneId, selfId)
	if x270010_g_yuelao < 0 then
			x270010_CloseTimer(sceneId, x270010_g_PROTECTINFO.ScneneTimerIndex)
			return
	end
	if x270010_g_doing==1   then
		if GetCurrentTime() - x270010_g_PROTECTINFO.StartTime >= 1   then
		  x270010_g_doing = 2
			if IsObjValid (sceneId,x270010_g_yuelao) == 1 then
				NpcTalk(sceneId, x270010_g_yuelao, "������Ů�������İɣ�", -1)
			end
    end
	elseif x270010_g_doing == 2   then
			if GetCurrentTime() - x270010_g_PROTECTINFO.StartTime >= 5   then
			  	x270010_g_doing =3
					if IsObjValid (sceneId,x270010_g_yuelao) == 1 then
						NpcTalk(sceneId, x270010_g_yuelao, "�㲻��˵��֪����Ҫ��ʲô��", -1)
					end
      end
	elseif x270010_g_doing == 3   then
			if GetCurrentTime() - x270010_g_PROTECTINFO.StartTime >= 8   then
					x270010_g_doing =4
					if IsObjValid (sceneId,x270010_g_yuelao) == 1 then
						NpcTalk(sceneId, x270010_g_yuelao, "��͸�����������ܳɣ��Ǹ��ܲ�������顣", -1)
					end
			end
	
	elseif x270010_g_doing == 4   then
			if GetCurrentTime() - x270010_g_PROTECTINFO.StartTime >= 12   then
					x270010_g_doing =5
					if IsObjValid (sceneId,x270010_g_yuelao) == 1 then
						NpcTalk(sceneId, x270010_g_yuelao, "������ȥ�Ⱦ��ˣ����ȥ�������ɣ�", -1)
					end
						x270010_CloseTimer(sceneId, x270010_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end

function x270010_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270010_g_doing = 0
	x270010_g_yuelao =-1
	x270010_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	
end

function x270010_useitem(sceneId,selfId)
		local x,z = GetWorldPos(sceneId,selfId)
		local distanceRet = 100 - (181 - x) * (181 - x) - (445 - z) * (445 - z)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270010_g_MissionId)
		if sceneId == 0 then
  		if distanceRet >= 0 then
          SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		 			if x270010_g_doing==0 then
		 					BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"ѯ�ʺ����үү  1/1")
							DispatchQuestTips(sceneId,selfId) 
							EndQuestEvent(sceneId)
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
				 			x270010_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270010, "OnScneneTimer", 1)
				 			if x270010_g_PROTECTINFO.ScneneTimerIndex >= 0 then
									x270010_g_yuelao=CreateMonster(sceneId, 445,181,444,3,1,-1,-1,20,15000,0,"����")
        					x270010_g_doing =1
									x270010_g_PROTECTINFO.StartTime = GetCurrentTime()
									DelItem(sceneId, selfId, 13020314, 1)
							end
					else
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"ѯ�ʺ����үү  1/1")
							DispatchQuestTips(sceneId,selfId) 
							EndQuestEvent(sceneId)
							DelItem(sceneId, selfId, 13020314, 1)
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
     			  	return 1
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"���ﲻ��ʹ��")
				DispatchQuestTips(sceneId,selfId) 
				EndQuestEvent(sceneId)
			end
		end
           
			return 0
end
