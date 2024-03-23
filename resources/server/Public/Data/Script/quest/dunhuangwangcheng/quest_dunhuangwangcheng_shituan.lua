--ѯ��״��

--MisDescBegin
x256056_g_ScriptId = 256056
x256056_g_MissionIdPre =1615
x256056_g_MissionId = 1616
x256056_g_LevelLess	= 	10 
x256056_g_MissionIdNext = 1617
x256056_g_Name	={}
x256056_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_138050"}}
x256056_g_MissionName="�����ߡ��ɹ���ʷ<��>"
x256056_g_MissionInfo="\t���������ط����Һ�Ȼ�����Ƥ�����˺ܶ࣬����Ҳ�����ָ������ˣ�����������ͼ��ү���Ǽķ���һ����Ƥ�����⣬���ø��㡣"  --��������
x256056_g_MissionTarget=""		
x256056_g_MissionCompleted="\t������ͼ����˺����Ƥ�����ڳģ�ȡ����ҳֽ����\n\t��ʵ��������������Ҫ�����ܾ�������ƾɵ���Ƥ��֮�С� "					--�������npc˵���Ļ�
x256056_g_ContinueInfo=""
x256056_g_MissionHelp =	""
--x256056_g_DemandItem ={{item=13010030,num=1}}
x256056_g_BonusMoney1 =253
x256056_g_BonusMoney2 =0
x256056_g_BonusMoney3 =0
x256056_g_BonusMoney4 =0
x256056_g_BonusMoney5 =26
x256056_g_BonusMoney6 =0
x256056_g_BonusItem	=	{}
x256056_g_BonusChoiceItem ={}
x256056_g_ExpBonus = 2932
x256056_g_NpcGUID ={{ guid = 138050, name = "����ͼ"} }

--MisDescEnd
x256056_g_zhubaoshangren =0
x256056_g_doing =0
x256056_g_huhelu =-1
x256056_g_huwei1 =-1
x256056_g_huwei2 =-1
x256056_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x256056_g_acceptid =-1
--**********************************

function x256056_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x256056_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x256056_g_MissionIdPre)> 0 then
	
						if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x256056_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x256056_g_MissionId, state, -1 )
						end
			
	end
end

function x256056_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256056_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256056_g_ExpBonus )
		end
		if x256056_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256056_g_BonusMoney1 )
		end
		if x256056_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256056_g_BonusMoney2 )
		end
		if x256056_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256056_g_BonusMoney3 )
		end
		if x256056_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256056_g_BonusMoney4 )
		end
		if x256056_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256056_g_BonusMoney5 )
		end
		if x256056_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256056_g_BonusMoney6 )
		end
		for i, item in x256056_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256056_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256056_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256056_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) > 0 then
			if x256056_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256056_g_MissionName)
						AddQuestText(sceneId,x256056_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256056_g_ScriptId, x256056_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256056_g_MissionName)
						AddQuestText(sceneId,x256056_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256056_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256056_g_ScriptId, x256056_g_MissionId);
			end
  elseif x256056_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256056_g_MissionName)
			AddQuestText(sceneId,x256056_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256056_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256056_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256056_g_MissionHelp )
			end
			x256056_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256056_g_ScriptId, x256056_g_MissionId);
  end
	
end
--**********************************

function x256056_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x256056_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x256056_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256056_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256056_g_MissionId  )
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
		
		if x256056_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256056_g_MissionId, x256056_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256056_Msg2toplayer( sceneId, selfId,0)
						--if x256056_CheckSubmit(sceneId, selfId, NPCId) > 0 then
						local misIndex = GetQuestIndexByID(sceneId,selfId,x256056_g_MissionId)                                                  
	    			SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			x256056_g_zhubaoshangren =FindMonsterByGUID( sceneId,138500)
    				if x256056_g_doing==0 then
								if x256056_g_huhelu==-1 then
										x256056_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 256056, "OnScneneTimer", 1)
										if x256056_g_PROTECTINFO.ScneneTimerIndex >= 0 then
											if IsObjValid (sceneId,x256056_g_zhubaoshangren) == 1 then
    			    					NpcTalk(sceneId, x256056_g_zhubaoshangren, "��ѽ�����ã������������ˡ�", -1)
    			    				end
    			    					x256056_g_doing =2
												x256056_g_huhelu=CreateMonster(sceneId, 139,285,126,3,1,-1,-1,20,-1,90,"����³","����̨����")
    			          		x256056_g_huwei1=CreateMonster(sceneId, 141,282,128,3,1,-1,-1,20,-1,90,"����³����")
    			          		x256056_g_huwei2=CreateMonster(sceneId, 141,282,124,3,1,-1,-1,20,-1,90,"����³����")		      
												-- SetPatrolId(sceneId, x256056_g_guojing, 3)	
    			    					--x256056_g_PROTECTINFO.PlayerNum = 1                    
												--x256056_g_PROTECTINFO.PlayerId[1] = selfId             
    			          		x256056_g_PROTECTINFO.StartTime = GetCurrentTime()
    			          end
    			  		end
    						--elseif x256056_g_doing<=5 then
    								--if x256056_g_PROTECTINFO.PlayerNum > 5  then
												--return
										--end
									--	x256056_g_PROTECTINFO.PlayerNum = x256056_g_PROTECTINFO.PlayerNum + 1
										--x256056_g_PROTECTINFO.PlayerId[x256056_g_PROTECTINFO.PlayerNum] = selfId
						  		--	AddQuest( sceneId, selfId, x256056_g_MissionId, x256056_g_ScriptId, 1, 0, 0)
					  			--	x256056_Msg2toplayer( sceneId, selfId,0)
							--else
								--BeginQuestEvent(sceneId)
								--strText = "#Y���ڲ��ܽ��������"
								--AddQuestText(sceneId,strText)
								--EndQuestEvent(sceneId)
								--DispatchQuestTips(sceneId,selfId)
						end
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256056_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256056_g_MissionId)
	  x256056_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x256056_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256056_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256056_g_BonusChoiceItem do
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
function x256056_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256056_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256056_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256056_g_MissionId) > 0 then
				x256056_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256056_g_MissionId)
				x256056_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256056_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256056_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		
    		
	 	end        
									
    		--AddItemListToPlayer(sceneId,selfId)

   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256056_g_MissionIdNext )	
end


function x256056_OnScneneTimer(sceneId)
	--if x256056_g_doing == 1   then
		--local nTeamCount = GetNearTeamCount(sceneId, x256056_g_acceptid)
		--for i=0, nTeamCount-1 do
			--local PlayerId = GetNearTeamMember(sceneId, x256056_g_acceptid, i)
			--if PlayerId ~= x256056_g_acceptid  then
				--if x256056_ProcAcceptCheck(sceneId, PlayerId, NPCId) > 0 then
					--local nPlayerX, nPlayerZ = GetWorldPos(sceneId, PlayerId)
					--local distance1 = floor(sqrt((78-nPlayerX)*(78-nPlayerX)+(174-nPlayerZ)*(174-nPlayerZ)))
					--print(distance1)
					--if distance1 < 5   then
						--CallScriptFunction((256056), "ProcEventEntry", sceneId, PlayerId, x256056_g_zhubaoshangren,x256056_g_MissionId )
					--end
				--end
			--end
		--end
		--x256056_g_doing =2
	--end
	if x256056_g_doing==2   then
		if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 1   then
						x256056_g_doing = 3
		end
elseif x256056_g_doing == 3   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 2   then
					if IsObjValid (sceneId,x256056_g_zhubaoshangren) == 1 then
						NpcTalk(sceneId, x256056_g_zhubaoshangren, "��ѽ����λ������ݹ��٣�Ҫ����鱦����ô��", -1)
					end
                       
        		x256056_g_doing =4
			end
	elseif x256056_g_doing == 4   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 5   then
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
						NpcTalk(sceneId, x256056_g_huhelu, "�ٷϻ�����˵����ͼ���ϼһ���������˵㶫����", -1)
          end        
						x256056_g_doing =5
			end
	elseif x256056_g_doing == 5   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 8   then
					if IsObjValid (sceneId,x256056_g_zhubaoshangren) == 1 then
						NpcTalk(sceneId, x256056_g_zhubaoshangren, "......����ͼ��СŮ�Ӳ���ʶ���ˡ�", -1)
          end    
						x256056_g_doing =6
			end
	elseif x256056_g_doing == 6   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 11   then
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
						NpcTalk(sceneId, x256056_g_huhelu, "��ƭ�ң��Ų������ӵ��������......", -1)
          end           
						x256056_g_doing =7
			end
	elseif x256056_g_doing == 7   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 14   then
					if IsObjValid (sceneId,x256056_g_huwei1) == 1 then
						NpcTalk(sceneId, x256056_g_huwei1, "ͷ��ͷ���ҿ����Ǹ��ղŸ������ͷ���......", -1)
					end
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
             SetMonsterDir(sceneId,x256056_g_huhelu,330)
          end
						x256056_g_doing =8
			end
	elseif x256056_g_doing == 8   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 16   then
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
						NpcTalk(sceneId, x256056_g_huhelu, "��ʲô���������������֪���ԣ��Ҳ�����ʷ���������˹���������С�����Ӱ������Ƥ��", -1)
          end
						x256056_g_doing =9
			end
	
	elseif x256056_g_doing == 9   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 18   then
					if IsObjValid (sceneId,x256056_g_huwei2) == 1 then
						NpcTalk(sceneId, x256056_g_huwei2, "ͷ�������ˣ�Ѳ�ߵľ��ٹ����ˣ�", -1)
          end
						x256056_g_doing =10
			end
	elseif x256056_g_doing == 10   then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 19   then
					if IsObjValid (sceneId,x256056_g_huhelu) == 1 then
						NpcTalk(sceneId, x256056_g_huhelu, "ʲô?......�ߣ�", -1)
          end
						x256056_g_doing =11
			end
	elseif x256056_g_doing==11 then
			if GetCurrentTime() - x256056_g_PROTECTINFO.StartTime >= 23   then
				--for i=1, x256056_g_PROTECTINFO.PlayerNum  do
					--if x256056_g_PROTECTINFO.PlayerId[i]~=0   then
						--if IsHaveQuest(sceneId,x256056_g_PROTECTINFO.PlayerId[i],x256056_g_MissionId) > 0 then
							--local nPlayerX, nPlayerZ = GetWorldPos(sceneId, x256056_g_PROTECTINFO.PlayerId[i])
							--local distance1 = floor(sqrt((78-nPlayerX)*(78-nPlayerX)+(174-nPlayerZ)*(174-nPlayerZ)))
						--if distance1 < 20   then
								--local misIndex = GetQuestIndexByID(sceneId, x256056_g_PROTECTINFO.PlayerId[i], x256056_g_MissionId)
								--SetQuestByIndex(sceneId,x256056_g_PROTECTINFO.PlayerId[i],misIndex,0,1)
								--SetQuestByIndex(sceneId,x256056_g_PROTECTINFO.PlayerId[i],misIndex,7,1)
								--BeginQuestEvent(sceneId)
								--AddQuestText(sceneId,format("    ����ľ��ץס�̿͵Ĺ���   %d/1", GetQuestParam(sceneId,x256056_g_PROTECTINFO.PlayerId[i],misIndex,0) ))
								--EndQuestEvent(sceneId)
								--DispatchQuestTips(sceneId,x256056_g_PROTECTINFO.PlayerId[i])
						--end
					--end
				--end
			--end
			x256056_g_doing=12
			x256056_CloseTimer(sceneId, x256056_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x256056_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	DeleteMonster (sceneId,x256056_g_huhelu )
	DeleteMonster (sceneId,x256056_g_huwei1 )
	DeleteMonster (sceneId,x256056_g_huwei2 )
	x256056_g_doing =0
	x256056_g_huhelu =-1
	x256056_g_huwei1 =-1
	x256056_g_huwei2 =-1
	x256056_g_acceptid =-1
	x256056_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x256056_GetBonus( sceneId, selfId,NpcID)
	  if x256056_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256056_g_ExpBonus);
  	end
		if x256056_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256056_g_BonusMoney1 )
	  end
		if x256056_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256056_g_BonusMoney2 )
	  end
		if x256056_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256056_g_BonusMoney3 )
		end
		if x256056_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256056_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256056_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256056_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256056_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256056_g_BonusMoney6)
		end
end

function x256056_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256056_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256056_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256056_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256056_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256056_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256056_g_MissionName.."��", 0, 3)
				if x256056_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256056_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256056_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256056_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256056_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256056_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256056_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256056_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256056_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256056_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256056_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256056_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256056_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256056_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256056_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256056_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256056_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256056_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256056_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256056_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256056_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256056_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256056_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256056_g_MissionId, state, -1 )
		end
end

function x256056_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256056_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256056_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256056_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256056_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256056_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end