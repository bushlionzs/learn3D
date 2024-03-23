--ͻ�����ǵ�ȼ�ź�

--MisDescBegin
x203315_g_ScriptId = 203315
x203315_g_MissionIdPre ={721,722}
x203315_g_MissionId = 723
x203315_g_LevelLess	= 	80 
x203315_g_MissionIdNext = 724
x203315_g_Name	={}
x203315_g_noDemandItem ={{id=13060029,num=1}}
x203315_g_ExtTarget={{type=20,n=1,target="��@npc_115038�ų����Ƽ�"}}
x203315_g_MissionName="�����顿��ս�͸�����<��>"
x203315_g_MissionInfo="\t�͸�������Ѿ���ˮ��ȫΧ��������������������Ҳ���Ѿ������������Ƿ����ܹ���ʱ���ˣ�\n\t�ڿյ��ϵ�ȼ��������ǿ����źžͻᵽ�����ϡ�"  --��������
x203315_g_MissionTarget=""		
x203315_g_MissionCompleted="\t��������һս������������;ĩ·�����������ӵ�����ȥ�� "					--�������npc˵���Ļ�
x203315_g_ContinueInfo="\t�����������̻���ʲô�أ�"
x203315_g_MissionHelp =	"#G�����Ե�������ϵ�#RB#G�����򿪱�����Ȼ���Ҽ����#R���Ƽ�#G����ʹ�á�"
x203315_g_DemandItem ={}
x203315_g_BonusMoney1 =800
x203315_g_BonusMoney2 =0
x203315_g_BonusMoney3 =0
x203315_g_BonusMoney4 =0
x203315_g_BonusMoney5 =91
x203315_g_BonusMoney6 =0
x203315_g_BonusItem	=	{}
x203315_g_BonusChoiceItem ={}
x203315_g_ExpBonus = 528000
x203315_g_NpcGUID ={{ guid = 115009, name = "����أ"} }
--MisDescEnd
x203315_g_doing = 0
x203315_g_guobaoyu =-1
x203315_g_badu =-1
x203315_g_xuliewu=-1
x203315_g_zhalanding =-1
x203315_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x203315_g_Impact1   = 7520--Ч��ID
--**********************************

function x203315_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x203315_g_MissionId) > 0 then
		return 
	end
  if IsQuestHaveDone(sceneId, selfId, x203315_g_MissionIdPre[1])> 0 then   
	  if IsQuestHaveDone(sceneId, selfId, x203315_g_MissionIdPre[2])> 0 then 
						if IsHaveQuest(sceneId,selfId, x203315_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x203315_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x203315_g_MissionId, state, -1 )
						end
		end
	end
end

function x203315_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203315_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203315_g_ExpBonus )
		end
		if x203315_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203315_g_BonusMoney1 )
		end
		if x203315_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203315_g_BonusMoney2 )
		end
		if x203315_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203315_g_BonusMoney3 )
		end
		if x203315_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203315_g_BonusMoney4 )
		end
		if x203315_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203315_g_BonusMoney5 )
		end
		if x203315_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203315_g_BonusMoney6 )
		end
		for i, item in x203315_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203315_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203315_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203315_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203315_g_MissionId) > 0 then
			if x203315_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203315_g_MissionName)
						AddQuestText(sceneId,x203315_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203315_g_ScriptId, x203315_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203315_g_MissionName)
						AddQuestText(sceneId,x203315_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203315_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203315_g_ScriptId, x203315_g_MissionId);
			end
  elseif x203315_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203315_g_MissionName)
			AddQuestText(sceneId,x203315_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203315_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203315_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203315_g_MissionHelp )
			end
			x203315_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203315_g_ScriptId, x203315_g_MissionId);
  end
	
end
--**********************************

function x203315_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203315_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203315_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == 1 then
			return 1
	end
	return 0
end
--**********************************
function x203315_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203315_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203315_g_MissionId  )
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
		
		if x203315_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
		  BeginAddItem(sceneId)                                                    
			AddItem( sceneId,x203315_g_noDemandItem[1].id, x203315_g_noDemandItem[1].num )             
			local ret = EndAddItem(sceneId,selfId)                                 
	  		if ret > 0 then
	  			local retmiss = AddQuest( sceneId, selfId, x203315_g_MissionId, x203315_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203315_Msg2toplayer( sceneId, selfId,0)
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

function x203315_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203315_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203315_g_MissionId)
	  x203315_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x203315_g_noDemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x203315_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203315_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203315_g_BonusChoiceItem do
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
function x203315_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203315_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203315_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203315_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203315_g_MissionId) > 0 then
				x203315_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203315_g_MissionId)
				x203315_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203315_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203315_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203315_g_MissionIdNext )	
end

function x203315_GetBonus( sceneId, selfId,NpcID)
	  if x203315_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203315_g_ExpBonus);
  	end
		if x203315_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203315_g_BonusMoney1 )
	  end
		if x203315_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203315_g_BonusMoney2 )
	  end
		if x203315_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203315_g_BonusMoney3 )
		end
		if x203315_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203315_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203315_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203315_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203315_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203315_g_BonusMoney6)
		end
end

function x203315_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203315_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203315_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203315_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203315_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203315_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203315_g_MissionName.."��", 0, 3)
				if x203315_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203315_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203315_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203315_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203315_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203315_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203315_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203315_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203315_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203315_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203315_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203315_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203315_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203315_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203315_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203315_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
			local misIndex = GetQuestIndexByID(sceneId,selfId,x203315_g_MissionId)
			SetQuestByIndex(sceneId,selfId,misIndex,1,1)
end

function x203315_ProcTiming(ssceneId, selfId, ScriptId, MissionId)
	
end

function x203315_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
			local misIndex = GetQuestIndexByID(sceneId,selfId,x203315_g_MissionId)
			SetQuestByIndex(sceneId,selfId,misIndex,1,0)
end

function x203315_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203315_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203315_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203315_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203315_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203315_g_MissionId, state, -1 )
		end
end

function x203315_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203315_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203315_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203315_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203315_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203315_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x203315_OnScneneTimer(sceneId, selfId)
	if x203315_g_doing==1   then
		if GetCurrentTime() - x203315_g_PROTECTINFO.StartTime >= 8   then
			if IsObjValid (sceneId,x203315_g_guobaoyu) == 1 then
				NpcTalk(sceneId, x203315_g_guobaoyu, "������������������ĩ�գ��������е����������ǵĳɼ�˼���Կ��Ϊ�����ˡ������", -1)
			end
			--if IsObjValid (sceneId,x203315_g_badu) == 1 then
			--SetPatrolId(sceneId, x203315_g_badu, 1)	
			--end
        x203315_g_doing = 2
		end
	elseif x203315_g_doing == 2   then
			if GetCurrentTime() - x203315_g_PROTECTINFO.StartTime >= 13   then
				if IsObjValid (sceneId,x203315_g_badu) == 1 then
						NpcTalk(sceneId, x203315_g_badu, "���ڵȵ�����һ�죬��ҪΪ��ȥ����ʿ�Ǳ���", -1)
				end
				--if IsObjValid (sceneId,x203315_g_tiemuzhen) == 1 then
				--	SetPatrolId(sceneId, x203315_g_tiemuzhen, 0)	
				--end
        x203315_g_doing =3
			end
	elseif x203315_g_doing == 3   then
			if GetCurrentTime() - x203315_g_PROTECTINFO.StartTime >= 18   then
				if IsObjValid (sceneId,x203315_g_zhalanding) == 1 then
						NpcTalk(sceneId, x203315_g_zhalanding, "����أ����Ҫ̫���⣬����һ�죬��Ҫ�����һ��ս��", -1)
				end
						x203315_g_doing =4
			end
	
	elseif x203315_g_doing == 4   then
			if GetCurrentTime() - x203315_g_PROTECTINFO.StartTime >= 22   then
              --NpcTalk(sceneId, x203315_g_xuliewu ,"�����顿����أ����ʿ�ǣ��尡��", -1)
              NpcTalk(sceneId, x203315_g_guobaoyu ,"������������", -1)
          if IsObjValid (sceneId,x203315_g_xuliewu) == 1 then
						NpcTalk(sceneId, x203315_g_xuliewu, "������", -1)
					end
					--if IsObjValid (sceneId,x203315_g_guobaoyu) == 1 then
					--SetPatrolId(sceneId, x203315_g_guobaoyu, 7)
					--end
					--if IsObjValid (sceneId,x203315_g_tiemuzhen) == 1 then
        	--SetPatrolId(sceneId, x203315_g_tiemuzhen, 6)
        	--end
        	--if IsObjValid (sceneId,x203315_g_zhamuhe) == 1 then
        	--SetPatrolId(sceneId, x203315_g_zhamuhe, 8)
        	--end
						x203315_g_doing =5
			end
	elseif x203315_g_doing == 5   then
			if GetCurrentTime() - x203315_g_PROTECTINFO.StartTime >= 25   then
						x203315_g_doing =6
						x203315_CloseTimer(sceneId, x203315_g_PROTECTINFO.ScneneTimerIndex)
			end

	end
end

function x203315_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203315_g_doing = 0
	x203315_g_guobaoyu =-1
	x203315_g_badu =-1
	x203315_g_xuliewu=-1
	x203315_g_zhalanding =-1
	x203315_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	
end

function x203315_useitem(sceneId,selfId)
			local misIndex = GetQuestIndexByID(sceneId,selfId,x203315_g_MissionId)
  		if (GetQuestParam(sceneId,selfId,misIndex,1)==1) then
         SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x203315_g_Impact1, 0);
  		    SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		 			if x203315_g_doing==0 then
		 					BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"���Ƽ� 1/1")
							DispatchQuestTips(sceneId,selfId) 
							EndQuestEvent(sceneId)
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
				 			x203315_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203315, "OnScneneTimer", 1)
				 			if x203315_g_PROTECTINFO.ScneneTimerIndex >= 0 then
									x203315_g_guobaoyu=CreateMonster(sceneId, 910,56,57,3,1,-1,-1,20,25000,210,"������")
        					x203315_g_badu=CreateMonster(sceneId, 911,59,51,3,1,-1,-1,20,25000,240,"�ζ�")
        					x203315_g_zhalanding=CreateMonster(sceneId, 866,53,50,3,1,-1,-1,21,25000,40,"������")
        					--if IsObjValid (sceneId,x203315_g_muhuali) == 1 then
        							--SetPatrolId(sceneId, x203315_g_muhuali, 2)
        					--end
        					x203315_g_doing =1
									x203315_g_PROTECTINFO.StartTime = GetCurrentTime()
									DelItem(sceneId, selfId, 13060029, 1)
							end
					else
							BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"��ȼ���Ƽ� 1/1")
							DispatchQuestTips(sceneId,selfId) 
							EndQuestEvent(sceneId)
							DelItem(sceneId, selfId, 13060029, 1)
							SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
     			  	return 1
			end
			if (GetQuestParam(sceneId,selfId,misIndex,1)==0) then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"���ȵ��յش���ʹ��")
				DispatchQuestTips(sceneId,selfId) 
				EndQuestEvent(sceneId)
			end
           
			return 0

end