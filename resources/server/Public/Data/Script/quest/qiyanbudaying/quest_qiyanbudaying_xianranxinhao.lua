--��ȼ�ź�

--MisDescBegin
x200501_g_ScriptId = 200501
x200501_g_MissionIdPre =58
x200501_g_MissionId = 63
x200501_g_LevelLess	= 	15 
x200501_g_MissionIdNext = 64
x200501_g_Name	={}
x200501_g_noDemandItem ={{id=13020003,num=1}}
x200501_g_ExtTarget={{type=20,n=1,target="��@npc_14020��ȼ�̻�"}}
x200501_g_MissionName="���糡����ȼ�ź�"
x200501_g_MissionInfo="\t�����ҵİ�����常���Ѿ����ˣ���Ҫ���������˳����ҵķ�ŭ���㣬��ȥӪ��İ͸�̨��ȼ�̻����ҵİ���ָ·�������͵���\n\t���ˣ������̻�֮����ȥ���ٲ�̨�ɣ����������ش�Ӫ���ٴθ�л�㣡"  --��������
x200501_g_MissionTarget=""		
x200501_g_MissionCompleted="\t�����������˵�ս����Ȼû�����Ҳμӣ���ȥս������ô��ץū���أ� "					--�������npc˵���Ļ�
x200501_g_ContinueInfo="\t�����������̻���ʲô�أ�"
x200501_g_MissionHelp =	"#G�����Ե�������ϵ�#RB#G�����򿪱�����Ȼ���Ҽ����#R��ľ����̻�#G����ʹ�á�"
x200501_g_DemandItem ={}
x200501_g_BonusMoney1 =242
x200501_g_BonusMoney2 =0
x200501_g_BonusMoney3 =0
x200501_g_BonusMoney4 =0
x200501_g_BonusMoney5 =31
x200501_g_BonusMoney6 =0
x200501_g_BonusItem	=	{{item = 11000200,n=5}}
x200501_g_BonusChoiceItem ={}
x200501_g_ExpBonus = 3877
x200501_g_NpcGUID ={{ guid = 102006, name = "�ٲ�̨"} }
--MisDescEnd
x200501_g_doing = 0
x200501_g_muhuali =-1
x200501_g_zhamuhe =-1
x200501_g_tiemuzhen =-1
x200501_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x200501_g_Impact1   = 7520--Ч��ID
--**********************************

function x200501_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x200501_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x200501_g_MissionIdPre)> 0 then
						if IsHaveQuest(sceneId,selfId, x200501_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x200501_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x200501_g_MissionId, state, -1 )
						end
	end
end

function x200501_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x200501_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x200501_g_ExpBonus )
		end
		if x200501_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x200501_g_BonusMoney1 )
		end
		if x200501_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x200501_g_BonusMoney2 )
		end
		if x200501_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x200501_g_BonusMoney3 )
		end
		if x200501_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x200501_g_BonusMoney4 )
		end
		if x200501_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x200501_g_BonusMoney5 )
		end
		if x200501_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x200501_g_BonusMoney6 )
		end
		for i, item in x200501_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x200501_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x200501_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x200501_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x200501_g_MissionId) > 0 then
			if x200501_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x200501_g_MissionName)
						AddQuestText(sceneId,x200501_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x200501_g_ScriptId, x200501_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x200501_g_MissionName)
						AddQuestText(sceneId,x200501_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x200501_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x200501_g_ScriptId, x200501_g_MissionId);
			end
  elseif x200501_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x200501_g_MissionName)
			AddQuestText(sceneId,x200501_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x200501_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x200501_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x200501_g_MissionHelp )
			end
			x200501_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x200501_g_ScriptId, x200501_g_MissionId);
  end
	
end
--**********************************

function x200501_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x200501_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x200501_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == 1 then
			return 1
	end
	return 0
end
--**********************************
function x200501_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x200501_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x200501_g_MissionId  )
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
		
		if x200501_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		  BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x200501_g_noDemandItem[1].id, x200501_g_noDemandItem[1].num )             
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x200501_g_MissionId, x200501_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x200501_Msg2toplayer( sceneId, selfId,0)
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

function x200501_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x200501_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x200501_g_MissionId)
	  x200501_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x200501_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x200501_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x200501_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x200501_g_BonusChoiceItem do
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
function x200501_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x200501_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x200501_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x200501_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x200501_g_MissionId) > 0 then
				x200501_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x200501_g_MissionId)
				x200501_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x200501_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x200501_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x200501_g_MissionIdNext )	
end

function x200501_GetBonus( sceneId, selfId,NpcID)
	  if x200501_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x200501_g_ExpBonus);
  	end
		if x200501_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x200501_g_BonusMoney1 )
	  end
		if x200501_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x200501_g_BonusMoney2 )
	  end
		if x200501_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x200501_g_BonusMoney3 )
		end
		if x200501_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x200501_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x200501_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x200501_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x200501_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x200501_g_BonusMoney6)
		end
end

function x200501_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x200501_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x200501_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x200501_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x200501_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x200501_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x200501_g_MissionName.."��", 0, 3)
				if x200501_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200501_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x200501_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x200501_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x200501_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x200501_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x200501_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x200501_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x200501_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x200501_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x200501_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200501_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x200501_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200501_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x200501_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x200501_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
			local misIndex = GetQuestIndexByID(sceneId,selfId,x200501_g_MissionId)
			SetQuestByIndex(sceneId,selfId,misIndex,1,1)
end

function x200501_ProcTiming(ssceneId, selfId, ScriptId, MissionId)
	
end

function x200501_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
			local misIndex = GetQuestIndexByID(sceneId,selfId,x200501_g_MissionId)
			SetQuestByIndex(sceneId,selfId,misIndex,1,0)
end

function x200501_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x200501_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x200501_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x200501_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x200501_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x200501_g_MissionId, state, -1 )
		end
end

function x200501_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x200501_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x200501_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x200501_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x200501_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x200501_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x200501_OnScneneTimer(sceneId, selfId)
	if x200501_g_doing==1   then
		if GetCurrentTime() - x200501_g_PROTECTINFO.StartTime >= 8   then
			if IsObjValid (sceneId,x200501_g_muhuali) == 1 then
				NpcTalk(sceneId, x200501_g_muhuali, "��Զ�Ϳ������̻��ˣ�", -1)
			end
			if IsObjValid (sceneId,x200501_g_zhamuhe) == 1 then
				SetPatrolId(sceneId, x200501_g_zhamuhe, 1)	
			end
        x200501_g_doing = 2
		end
	elseif x200501_g_doing == 2   then
			if GetCurrentTime() - x200501_g_PROTECTINFO.StartTime >= 13   then
				if IsObjValid (sceneId,x200501_g_zhamuhe) == 1 then
						NpcTalk(sceneId, x200501_g_zhamuhe, "���������Ļ�������", -1)
				end
				if IsObjValid (sceneId,x200501_g_tiemuzhen) == 1 then
						SetPatrolId(sceneId, x200501_g_tiemuzhen, 0)	
				end
        x200501_g_doing =3
			end
	elseif x200501_g_doing == 3   then
			if GetCurrentTime() - x200501_g_PROTECTINFO.StartTime >= 18   then
				if IsObjValid (sceneId,x200501_g_tiemuzhen) == 1 then
						NpcTalk(sceneId, x200501_g_tiemuzhen, "�ã��������������һ�������������񲿡�", -1)
				end
						x200501_g_doing =4
			end
	
	elseif x200501_g_doing == 4   then
			if GetCurrentTime() - x200501_g_PROTECTINFO.StartTime >= 22   then
             LuaThisScenceM2Wrold (sceneId,  "���糡����ľ�棺������", 0, -1)
             LuaThisScenceM2Wrold (sceneId,  "���糡��ľ���裬��ľ�ϣ����������񲿣�", 0, -1)
          if IsObjValid (sceneId,x200501_g_tiemuzhen) == 1 then
						NpcTalk(sceneId, x200501_g_tiemuzhen, "������", -1)
					end
					if IsObjValid (sceneId,x200501_g_muhuali) == 1 then
						SetPatrolId(sceneId, x200501_g_muhuali, 7)
					end
					if IsObjValid (sceneId,x200501_g_tiemuzhen) == 1 then
        		SetPatrolId(sceneId, x200501_g_tiemuzhen, 6)
        	end
        	if IsObjValid (sceneId,x200501_g_zhamuhe) == 1 then
        		SetPatrolId(sceneId, x200501_g_zhamuhe, 8)
        	end
						x200501_g_doing =5
			end
	elseif x200501_g_doing == 5   then
			if GetCurrentTime() - x200501_g_PROTECTINFO.StartTime >= 25   then
						x200501_g_doing =6
						x200501_CloseTimer(sceneId, x200501_g_PROTECTINFO.ScneneTimerIndex)
			end

	end
end

function x200501_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x200501_g_doing = 0
	x200501_g_muhuali =-1
	x200501_g_zhamuhe =-1
	x200501_g_tiemuzhen =-1
	x200501_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	
end

function x200501_useitem(sceneId,selfId)
			local misIndex = GetQuestIndexByID(sceneId,selfId,x200501_g_MissionId)
  		if (GetQuestParam(sceneId,selfId,misIndex,1)==1) then
         SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x200501_g_Impact1, 0);
  		    SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		 			if x200501_g_doing==0 then
		 					BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"��ȼ�̻� 1/1")
							DispatchQuestTips(sceneId,selfId) 
							EndQuestEvent(sceneId)
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
				 			x200501_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 200501, "OnScneneTimer", 1)
				 			if x200501_g_PROTECTINFO.ScneneTimerIndex >= 0 then
									x200501_g_muhuali=CreateMonster(sceneId, 310,105,123,3,1,-1,-1,20,25000)
        					x200501_g_tiemuzhen=CreateMonster(sceneId, 309,102,147,3,1,-1,-1,20,25000)
        					x200501_g_zhamuhe=CreateMonster(sceneId, 300,126,130,3,1,-1,-1,20,25000)
        					if IsObjValid (sceneId,x200501_g_muhuali) == 1 then
        							SetPatrolId(sceneId, x200501_g_muhuali, 2)
        					end
        					x200501_g_doing =1
									x200501_g_PROTECTINFO.StartTime = GetCurrentTime()
									DelItem(sceneId, selfId, 13020003, 1)
							end
					else
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"��ȼ�̻� 1/1")
							DispatchQuestTips(sceneId,selfId) 
							EndQuestEvent(sceneId)
							DelItem(sceneId, selfId, 13020003, 1)
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
     			  	return 1
			end
			if (GetQuestParam(sceneId,selfId,misIndex,1)==0) then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"���ȵ�Ӫ����ʹ��")
				DispatchQuestTips(sceneId,selfId) 
				EndQuestEvent(sceneId)
			end
           
			return 0

end