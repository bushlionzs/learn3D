--ѯ��״��

--MisDescBegin
x200500_g_ScriptId = 200500
x200500_g_MissionIdPre ={58,60}
x200500_g_MissionId = 59
x200500_g_LevelLess	= 	15 
x200500_g_MissionIdNext = 61
x200500_g_Name	={}
x200500_g_ExtTarget={{type=20,n=1,target="��������ѩɽ�һ�@npc_14019���ø�@npc_102024"}}
x200500_g_MissionName="���糡��Ѱ����"
x200500_g_MissionInfo="\t���Ǵ�æ�ӳ���ʱ���������˲�����ѩɽ��ɽ��������ȥ���ҵ�����ȡ�����ɣ�С�������ѩ�ǡ�"  --��������
x200500_g_MissionTarget=""		
x200500_g_MissionCompleted="\t�ܺã�����Ϳ��Զ����ˡ� "					--�������npc˵���Ļ�
x200500_g_ContinueInfo="\tҪ��û��������ȥ����ľ���̫�����ˣ��������ˡ�"   --δ�������NPC�԰�
x200500_g_MissionHelp =	""
x200500_g_DemandItem ={13010031}
x200500_g_BonusMoney1 =231
x200500_g_BonusMoney2 =0
x200500_g_BonusMoney3 =0
x200500_g_BonusMoney4 =0
x200500_g_BonusMoney5 =31
x200500_g_BonusMoney6 =0
x200500_g_BonusItem	=	{}
x200500_g_BonusChoiceItem ={}
x200500_g_ExpBonus = 3618
x200500_g_NpcGUID ={{ guid = 102024, name = "ľ����"} }
x200500_g_GroupPoint	=	{ {type=10,id =3,target = "��"} }--ר�����ڲɼ�����Ч�ã����������δ�ؾ����������ı�Ҫ���أ���ˣ�ֻҪ��ؾͿ��������������

--MisDescEnd
x200500_g_muhuali =-1
x200500_g_doing =0
x200500_g_zhamuhe =-1
x200500_g_tiemuzhen =-1
--x200500_g_tuolei =-1
x200500_g_shibing2 =-1
x200500_g_shibing4 =-1
x200500_g_shibing5 =-1
x200500_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x200500_g_acceptid =-1
--**********************************

function x200500_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x200500_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x200500_g_MissionIdPre[1])> 0 then
		if IsQuestHaveDone(sceneId, selfId, x200500_g_MissionIdPre[2])> 0 then
						if IsHaveQuest(sceneId,selfId, x200500_g_MissionId) <= 0 then
								x200500_CheckSubmit(sceneId, selfId, NPCId)
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x200500_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x200500_g_MissionId, state, -1 )
						end
		end	
			
	end
end

function x200500_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x200500_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x200500_g_ExpBonus )
		end
		if x200500_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x200500_g_BonusMoney1 )
		end
		if x200500_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x200500_g_BonusMoney2 )
		end
		if x200500_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x200500_g_BonusMoney3 )
		end
		if x200500_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x200500_g_BonusMoney4 )
		end
		if x200500_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x200500_g_BonusMoney5 )
		end
		if x200500_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x200500_g_BonusMoney6 )
		end
		for i, item in x200500_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x200500_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x200500_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x200500_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x200500_g_MissionId) > 0 then
			if x200500_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x200500_g_MissionName)
						AddQuestText(sceneId,x200500_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x200500_g_ScriptId, x200500_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x200500_g_MissionName)
						AddQuestText(sceneId,x200500_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x200500_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x200500_g_ScriptId, x200500_g_MissionId);
			end
  elseif x200500_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x200500_g_MissionName)
			AddQuestText(sceneId,x200500_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x200500_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x200500_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x200500_g_MissionHelp )
			end
			x200500_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x200500_g_ScriptId, x200500_g_MissionId);
  end
	
end
--**********************************

function x200500_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x200500_CheckSubmit( sceneId, selfId, NPCId)
if GetItemCount(sceneId,selfId,x200500_g_DemandItem[1]) >= 1 then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x200500_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 18,0 ) 
	    		return 1
	    		
	  else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x200500_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
	
end
--**********************************
function x200500_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x200500_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x200500_g_MissionId  )
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
		
		if x200500_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x200500_g_MissionId, x200500_g_ScriptId, 1, 1, 1,1)
					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 18,1 )
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			--x200500_Msg2toplayer( sceneId, selfId,0)
		  			--BeginAddItem(sceneId)
						--	for i, item in x200500_g_DemandItem do
 						--		AddItem( sceneId, item.item, item.num )
						--	end
    				--EndAddItem(sceneId,selfId)
    				--AddItemListToPlayer(sceneId,selfId)	
						--if x200500_CheckSubmit(sceneId, selfId, NPCId) > 0 then
							--	local misIndex = GetQuestIndexByID(sceneId,selfId,x200500_g_MissionId)								                                                  
	    				--	SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    				--	SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    					for i, item in x200500_g_DemandItem do                                            
	    								if GetItemCount(sceneId,selfId,item) >= 1 then		                              
	    									local misIndex = GetQuestIndexByID(sceneId,selfId,x200500_g_MissionId)        
	    			    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)                                			
	    			    					SetQuestByIndex(sceneId,selfId,misIndex,7,1) 
	    			    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 18,0 ) 
	    			    			end
	    			    end					
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x200500_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x200500_g_MissionId) <= 0 then
				return 
		end
		DelItem( sceneId,selfId,x200500_g_DemandItem[1],1 )
		DelQuest(sceneId, selfId, x200500_g_MissionId)
	  x200500_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 18,0 ) 		
end
--**********************************
function x200500_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x200500_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x200500_g_BonusChoiceItem do
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
 function x200500_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x200500_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x200500_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x200500_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x200500_g_MissionId) > 0 then
				x200500_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x200500_g_MissionId)
				DelItem( sceneId,selfId,13010031,1 )
				--DelItem( sceneId,selfId,x200500_g_DemandItem[1],1 )
				x200500_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x200500_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x200500_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    	end
     CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x200500_g_MissionIdNext )
     
     	
      x200500_g_muhuali =FindMonsterByGUID( sceneId,102024)
  			if x200500_g_doing==0 then
					--if x200500_g_zhamuhe==1 then
							if IsObjValid (sceneId,x200500_g_muhuali) == 1 then
  			    			NpcTalk(sceneId, x200500_g_muhuali, "���������ǵİ�����ľ�棡����ô���ˣ���֪��������һ���ᱣ����û�µġ�", -1)
  			    	end
  			    			x200500_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
									x200500_g_doing =2
									x200500_g_shibing2=CreateMonster(sceneId, 663,50,74,3,1,-1,102016,20,23000,180)
  			          x200500_g_shibing4=CreateMonster(sceneId, 663,46,74,3,1,-1,102016,20,23000,180)
  			          --x200500_g_shibing5=CreateMonster(sceneId, 663,52,74,3,1,-1,102016,20,23000,180)
  			          x200500_g_tiemuzhen=CreateMonster(sceneId, 662,48,70,3,1,-1,102005,20,23000,180)
									--x200500_g_tuolei=CreateMonster(sceneId, 306,84,173,3,1,-1,102030,20,23000)
									--x200500_g_zhamuhe=CreateMonster(sceneId, 308,110,180,3,1,-1,102031,20,23000)
									-- SetPatrolId(sceneId, x200500_g_guojing, 3)	
  			    			--x200500_g_PROTECTINFO.PlayerNum = 1                    
									--x200500_g_PROTECTINFO.PlayerId[1] = selfId             
  			          x200500_g_PROTECTINFO.StartTime = GetCurrentTime()
									x200500_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 200500, "OnScneneTimer", 1)
  			  --end
  			--elseif x200500_g_doing<=5 then
  								--if x200500_g_PROTECTINFO.PlayerNum > 5  then
											--return
									--end
								--	x200500_g_PROTECTINFO.PlayerNum = x200500_g_PROTECTINFO.PlayerNum + 1
									--x200500_g_PROTECTINFO.PlayerId[x200500_g_PROTECTINFO.PlayerNum] = selfId
					  		--	AddQuest( sceneId, selfId, x200500_g_MissionId, x200500_g_ScriptId, 1, 0, 0)
				  			--	x200500_Msg2toplayer( sceneId, selfId,0)
				--else
							--BeginQuestEvent(sceneId)
							--strText = "#Y���ڲ��ܽ��������"
							--AddQuestText(sceneId,strText)
							--EndQuestEvent(sceneId)
							--DispatchQuestTips(sceneId,selfId)
				--end
			
				end      
end
  
						
    		--AddItemListToPlayer(sceneId,selfId)

function x200500_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)

			if GetItemCount(sceneId,selfId,x200500_g_DemandItem[1]) >= 1 then
			
					local misIndex = GetQuestIndexByID(sceneId,selfId,x200500_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    	CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 18,0 ) 	
	 		else
	  			local misIndex = GetQuestIndexByID(sceneId,selfId,x200500_g_MissionId)                                                  
	    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  	end
end

function x200500_OnScneneTimer(sceneId)
	if x200500_g_doing==2   then
		if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 2   then
					x200500_g_doing = 3
				--	if IsObjValid (sceneId,x200500_g_tuolei) == 1 then
				--		SetPatrolId(sceneId, x200500_g_tuolei, 5)	
				--	end
					if IsObjValid (sceneId,x200500_g_tiemuzhen) == 1 then
        		SetPatrolId(sceneId, x200500_g_tiemuzhen, 9)
        						if IsObjValid (sceneId,x200500_g_shibing2) == 1 then
        		SetPatrolId(sceneId, x200500_g_shibing2, 13)
        						if IsObjValid (sceneId,x200500_g_shibing4) == 1 then
        		SetPatrolId(sceneId, x200500_g_shibing4, 14)
        	end
        	end
        	end
		end
	elseif x200500_g_doing == 3   then
			if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 7   then
			  x200500_g_doing =4
				if IsObjValid (sceneId,x200500_g_muhuali) == 1 then
						NpcTalk(sceneId, x200500_g_muhuali, "��ľ�棬���ǵĺð�����ƽ����������̫���ˡ�", -1)
				end
      end
	--elseif x200500_g_doing == 4   then
	--		if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 5   then
	--					x200500_g_doing =5
	--					if IsObjValid (sceneId,x200500_g_guojing) == 1 then
	--							NpcTalk(sceneId, x200500_g_guojing, "......", -1)
	--					end
	--		end
	elseif x200500_g_doing == 4   then
			if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 10   then
						x200500_g_doing =5
						if IsObjValid (sceneId,x200500_g_tiemuzhen) == 1 then
								NpcTalk(sceneId, x200500_g_tiemuzhen, "�ҵĺð���֪���������ˣ��ҵĲ����ϾͶ����ˡ�", -1)
						end
			end
	elseif x200500_g_doing == 5   then
			if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 14   then
						x200500_g_doing =6
						if IsObjValid (sceneId,x200500_g_tiemuzhen) == 1 then
								NpcTalk(sceneId, x200500_g_tiemuzhen, "�������˴������������ղ����������أ��������ӣ��������ҡ������һ��Ҫ����", -1)
						end
			end
			x200500_g_zhamuhe =FindMonsterByGUID( sceneId,102019)
	elseif x200500_g_doing == 6   then
			if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 17   then
						x200500_g_doing =7
						if IsObjValid (sceneId,x200500_g_muhuali) == 1 then
								NpcTalk(sceneId, x200500_g_muhuali, "�������Ҫһ�𱨡�", -1)       
									if IsObjValid (sceneId,x200500_g_zhamuhe) == 1 then                  
											NpcTalk(sceneId, x200500_g_zhamuhe, "�������Ҫһ�𱨡�", -1)  
						end    
						x200500_CloseTimer(sceneId, x200500_g_PROTECTINFO.ScneneTimerIndex)
								end
			end
	--elseif x200500_g_doing == 8   then
	--		if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 13   then
	--					x200500_g_doing =9
	--					if IsObjValid (sceneId,x200500_g_muhuali) == 1 then
	--							NpcTalk(sceneId, x200500_g_muhuali, "������ߵ����Ѿ���������ڳ���������", -1)
	--					end
	--		end
	--
	--elseif x200500_g_doing == 9   then
	--		if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 17   then
	--					x200500_g_doing =10
	--					if IsObjValid (sceneId,x200500_g_zhamuhe) == 1 then
	--							NpcTalk(sceneId, x200500_g_zhamuhe, "�벻��......��ľ�澹Ȼ��˴�ȣ���ԸΪ�󺹳�������ˮ��ʹ��ϣ���ʯ��ʹ���飡", -1)
	--					end
	--		end
	--elseif x200500_g_doing == 10   then
	--		if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 20   then
	--					x200500_g_doing =11
	--					if IsObjValid (sceneId,x200500_g_muhuali) == 1 then
	--							NpcTalk(sceneId, x200500_g_muhuali, "�ã��ӽ��Ժ�������ҵ�---�ܱ������֣���", -1)
	--					end
	--		end
	--elseif x200500_g_doing==11 then
	--		if GetCurrentTime() - x200500_g_PROTECTINFO.StartTime >= 23   then
	--		x200500_g_doing=12
	--		x200500_CloseTimer(sceneId, x200500_g_PROTECTINFO.ScneneTimerIndex)
	--		end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x200500_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x200500_g_doing =0
	x200500_g_zhamuhe =-1
	x200500_g_muhuali =-1
	--x200500_g_guojing =-1
	--x200500_g_tuolei =-1
	x200500_g_tiemuzhen =-1
	x200500_g_shibing2 =-1
	x200500_g_shibing4 =-1
	--x200500_g_shibing5 =-1
	x200500_g_acceptid =-1
	x200500_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end
    		
   ----------------------------@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@------------------------------------ 		


function x200500_GetBonus( sceneId, selfId,NpcID)
	  if x200500_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x200500_g_ExpBonus);
  	end
		if x200500_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x200500_g_BonusMoney1 )
	  end
		if x200500_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x200500_g_BonusMoney2 )
	  end
		if x200500_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x200500_g_BonusMoney3 )
		end
		if x200500_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x200500_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x200500_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x200500_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x200500_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x200500_g_BonusMoney6)
		end
end

function x200500_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x200500_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x200500_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x200500_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x200500_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x200500_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x200500_g_MissionName.."��", 0, 3)
				if x200500_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200500_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x200500_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x200500_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x200500_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x200500_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x200500_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x200500_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x200500_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x200500_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x200500_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200500_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x200500_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200500_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x200500_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x200500_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x200500_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x200500_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end


function x200500_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x200500_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x200500_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x200500_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x200500_g_MissionId, state, -1 )
		end
end

function x200500_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x200500_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x200500_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x200500_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x200500_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x200500_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end