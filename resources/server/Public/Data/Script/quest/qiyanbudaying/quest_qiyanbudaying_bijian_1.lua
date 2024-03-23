--ѯ��״��

--MisDescBegin
x200503_g_ScriptId = 200503
x200503_g_MissionIdPre =63
x200503_g_MissionId = 64
x200503_g_LevelLess	= 	15 
x200503_g_MissionIdNext = 66
x200503_g_Name	={}
x200503_g_ExtTarget={{type=20,n=1,target="�ظ�@npc_102004"}}
x200503_g_MissionName="���糡������<��>"
x200503_g_MissionInfo="\t��Ȼ�Һ������������ʵ��������ֻ�дӹ����⺢�����������ˣ�ϣ������β�Ҫ��Ϊ��ǿ��̫���ͷ�����ȵȵȡ���������˰ѹ���������"  --��������
x200503_g_MissionTarget=""		
x200503_g_MissionCompleted="��ľ����δ�����������ɹŲ�ԭ�Ͼ�������һ��������Ϊ�е�������"					--�������npc˵���Ļ�
x200503_g_ContinueInfo=""
x200503_g_MissionHelp =	""
x200503_g_DemandItem ={}
x200503_g_ExpBonus = 3618
x200503_g_BonusMoney1 =231
x200503_g_BonusMoney2 =0
x200503_g_BonusMoney3 =0
x200503_g_BonusMoney4 =0
x200503_g_BonusMoney5 =31
x200503_g_BonusMoney6 =0
x200503_g_BonusItem	=	{{item=13020012,n=1}}
x200503_g_BonusChoiceItem ={}
x200503_g_NpcGUID ={{ guid = 102004, name = "����"} }

--MisDescEnd
x200503_g_wanghan =-1
x200503_g_doing =0
x200503_g_huoadai =-1
x200503_g_guojing =-1
x200503_g_tuolei =-1
x200503_g_shibing2 =-1
x200503_g_shibing3 =-1
x200503_g_shibing4 =-1
x200503_g_tiemuzhen =-1
x200503_g_zhamuhe =-1
x200503_g_muhuali =-1
--x200503_g_shibing5 =-1
x200503_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x200503_g_acceptid =-1
--**********************************

function x200503_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x200503_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x200503_g_MissionIdPre)> 0 then
	
						if IsHaveQuest(sceneId,selfId, x200503_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x200503_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x200503_g_MissionId, state, -1 )
						end
			
	end
end

function x200503_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x200503_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x200503_g_ExpBonus )
		end
		if x200503_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x200503_g_BonusMoney1 )
		end
		if x200503_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x200503_g_BonusMoney2 )
		end
		if x200503_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x200503_g_BonusMoney3 )
		end
		if x200503_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x200503_g_BonusMoney4 )
		end
		if x200503_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x200503_g_BonusMoney5 )
		end
		if x200503_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x200503_g_BonusMoney6 )
		end
		for i, item in x200503_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x200503_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x200503_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x200503_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x200503_g_MissionId) > 0 then
			if x200503_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x200503_g_MissionName)
						AddQuestText(sceneId,x200503_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x200503_g_ScriptId, x200503_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x200503_g_MissionName)
						AddQuestText(sceneId,x200503_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x200503_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x200503_g_ScriptId, x200503_g_MissionId);
			end
  elseif x200503_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x200503_g_MissionName)
			AddQuestText(sceneId,x200503_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x200503_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x200503_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x200503_g_MissionHelp )
			end
			x200503_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x200503_g_ScriptId, x200503_g_MissionId);
  end
	
end
--**********************************

function x200503_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x200503_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x200503_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x200503_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x200503_g_MissionId  )
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
		
		if x200503_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x200503_g_MissionId, x200503_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x200503_Msg2toplayer( sceneId, selfId,0)
		  			
						
						  ---------------------------------------------------------
 					 x200503_g_wanghan =FindMonsterByGUID( sceneId,102004)
    							if x200503_g_doing==0 then
										if x200503_g_huoadai==-1 then
												if IsObjValid (sceneId,x200503_g_wanghan) == 1 then
    							    			NpcTalk(sceneId, x200503_g_wanghan, "�ѹ�����С�Ӵ�������", -1)
    							    	end
														x200503_g_doing =2
														x200503_g_guojing=CreateMonster(sceneId, 498,101,149,3,1,-1,102000,20,30000,250)
    							          x200503_g_shibing3=CreateMonster(sceneId, 639,102,151,3,1,-1,102016,20,30000,250)
    							          x200503_g_shibing4=CreateMonster(sceneId, 639,104,149,3,1,-1,102016,20,30000,250)
    							          --x200503_g_shibing5=CreateMonster(sceneId, 639,81,175,3,1,-1,102016,20,23000,180)
    							          --x200503_g_guojing=CreateMonster(sceneId, 305,87,172,3,1,-1,102029,20,23000,180)
														x200503_g_tuolei=CreateMonster(sceneId, 306,92,145,3,1,-1,102030,20,30000)
														x200503_g_huoadai=CreateMonster(sceneId, 308,110,158,3,1,-1,102031,20,30000)
														-- SetPatrolId(sceneId, x200503_g_guojing, 3)	
    							    			--x200503_g_PROTECTINFO.PlayerNum = 1                    
														--x200503_g_PROTECTINFO.PlayerId[1] = selfId             
    							          x200503_g_PROTECTINFO.StartTime = GetCurrentTime()
														x200503_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 200503, "OnScneneTimer", 1)
    							  end
    							--elseif x200503_g_doing<=5 then
    												--if x200503_g_PROTECTINFO.PlayerNum > 5  then
																--return
														--end
													--	x200503_g_PROTECTINFO.PlayerNum = x200503_g_PROTECTINFO.PlayerNum + 1
														--x200503_g_PROTECTINFO.PlayerId[x200503_g_PROTECTINFO.PlayerNum] = selfId
										  		--	AddQuest( sceneId, selfId, x200503_g_MissionId, x200503_g_ScriptId, 1, 0, 0)
									  			--	x200503_Msg2toplayer( sceneId, selfId,0)
									--else
												--BeginQuestEvent(sceneId)
												--strText = "#Y���ڲ��ܽ��������"
												--AddQuestText(sceneId,strText)
												--EndQuestEvent(sceneId)
												--DispatchQuestTips(sceneId,selfId)
									end
 --------------------------------------------------------
						
		  			BeginAddItem(sceneId)
							--for i, item in x200503_g_DemandItem do
 							--	AddItem( sceneId, item.item, item.num )
							--end
    				EndAddItem(sceneId,selfId)
    				--AddItemListToPlayer(sceneId,selfId)	
						--if x200503_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x200503_g_MissionId)								                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x200503_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x200503_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x200503_g_MissionId)
	  x200503_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x200503_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x200503_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x200503_g_BonusChoiceItem do
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
function x200503_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x200503_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x200503_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x200503_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x200503_g_MissionId) > 0 then
				x200503_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x200503_g_MissionId)
				--DelItem( sceneId,selfId,13010030,1 )
				x200503_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x200503_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x200503_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		
    		
	 	end        
									
    		AddItemListToPlayer(sceneId,selfId)

   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x200503_g_MissionIdNext )	
end


  function x200503_OnScneneTimer(sceneId)
 
	if x200503_g_doing==2   then
		if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 2   then
					x200503_g_doing = 3
					if IsObjValid (sceneId,x200503_g_tuolei) == 1 then
						SetPatrolId(sceneId, x200503_g_tuolei, 5)	
					end
					if IsObjValid (sceneId,x200503_g_huoadai) == 1 then
        		SetPatrolId(sceneId, x200503_g_huoadai, 4)
        	end
		end
	elseif x200503_g_doing == 3   then
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 3   then
			  x200503_g_doing =4
				if IsObjValid (sceneId,x200503_g_wanghan) == 1 then
						NpcTalk(sceneId, x200503_g_wanghan, "��������֧��ɱ��ľ��ļ�����Ķ�Ū���ģ�", -1)
				end
      end
	elseif x200503_g_doing == 4   then
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 5   then
						x200503_g_doing =5
						if IsObjValid (sceneId,x200503_g_guojing) == 1 then
								NpcTalk(sceneId, x200503_g_guojing, "......", -1)
						end
			end
	elseif x200503_g_doing == 5   then
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 7   then
						x200503_g_doing =6
						if IsObjValid (sceneId,x200503_g_wanghan) == 1 then
								NpcTalk(sceneId, x200503_g_wanghan, "��˵����С�ӣ��ϳ�ȥ���ˣ�", -1)
						end
			end
	elseif x200503_g_doing == 6   then
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 9   then
						x200503_g_doing =7
						if IsObjValid (sceneId,x200503_g_tuolei) == 1 then
								NpcTalk(sceneId, x200503_g_tuolei, "��Ҫ���������ҵİ�����......��ô���ܻ��ɱ�ҵĸ�������", -1)
						end
			end
	elseif x200503_g_doing == 7   then
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 11   then    
			x200503_g_tiemuzhen=CreateMonster(sceneId, 662,105,140,3,1,-1,102016,20,23000,320)        
			          x200503_g_zhamuhe=CreateMonster(sceneId, 499,105,137,3,1,-1,102043,20,23000,320)
			          x200503_g_muhuali=CreateMonster(sceneId, 1905,108,140,3,1,-1,102044,20,23000,320)
						x200503_g_doing =8
						if IsObjValid (sceneId,x200503_g_huoadai) == 1 then
								NpcTalk(sceneId, x200503_g_huoadai, "ס�֣��Ҿ�����Ҫ�ҵĴ̿ͣ���������������Ϊһ��С������ʲô���£�", -1)
						end
			end
	elseif x200503_g_doing == 8   then
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 13   then
						x200503_g_doing =9
						if IsObjValid (sceneId,x200503_g_tiemuzhen) == 1 then
							SetPatrolId(sceneId, x200503_g_tiemuzhen, 10)	             
							if IsObjValid (sceneId,x200503_g_zhamuhe) == 1 then 
								SetPatrolId(sceneId, x200503_g_zhamuhe, 11)	      
							if IsObjValid (sceneId,x200503_g_muhuali) == 1 then 
								SetPatrolId(sceneId, x200503_g_muhuali, 12)	      
						if IsObjValid (sceneId,x200503_g_tiemuzhen) == 1 then                                                                                                                                  						
								NpcTalk(sceneId, x200503_g_tiemuzhen, "�������һ����ʤ�̣����������׵Ļ����������ˡ�", -1) 
						if IsObjValid (sceneId,x200503_g_wanghan) == 1 then
								NpcTalk(sceneId, x200503_g_wanghan, "�á��Ҷ���ľ���Ȼ���¹��ˣ���ɱ��Ĵ̿���Ҳ����ץ���ˣ��ͽ����������ã�", -1)
						end     
						end
						end
						end
			end
	end  
	elseif x200503_g_doing == 9   then
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 17   then
						x200503_g_doing =10
						if IsObjValid (sceneId,x200503_g_tiemuzhen) == 1 then
								NpcTalk(sceneId, x200503_g_tiemuzhen, "�����ڳ����ˣ��������������ӣ��㵱ʱ��ɱ�����ɳ�Ϊ��������ҳ�����������׷����������", -1)
						end
			end
	elseif x200503_g_doing == 10   then
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 20   then
						x200503_g_doing =11
						if IsObjValid (sceneId,x200503_g_tiemuzhen) == 1 then                                                                                       
								NpcTalk(sceneId, x200503_g_tiemuzhen, "����������Ѱܣ���������ڱ���Ӫ��Ч����", -1)   
						end
			end
	elseif x200503_g_doing==11 then
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 23   then
			x200503_g_doing=12 
			  if IsObjValid (sceneId,x200503_g_huoadai) == 1 then                                                                          
			  		NpcTalk(sceneId, x200503_g_huoadai, "�벻��......��ľ�澹Ȼ��˴�ȣ���ԸΪ�󺹳�������ˮ��ʹ��ϣ���ʯ��ʹ���飡", -1)  
			end
	end  
	elseif x200503_g_doing==12 then                                           
			if GetCurrentTime() - x200503_g_PROTECTINFO.StartTime >= 26   then    
	      if IsObjValid (sceneId,x200503_g_tiemuzhen) == 1 then                                        
	      		NpcTalk(sceneId, x200503_g_tiemuzhen, "�ã��ӽ��Ժ�������ҵ�---�ܱ������֣���", -1)  
	      		x200503_CloseTimer(sceneId, x200503_g_PROTECTINFO.ScneneTimerIndex) 
	         		end 
	         end    
end
end

        	

--**********************************
--�رռ�ʱ��
--**********************************
function x200503_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x200503_g_doing =0
	x200503_g_huoadai =-1
	x200503_g_guojing =-1
	x200503_g_tuolei =-1
	x200503_g_shibing2 =-1
	x200503_g_shibing3 =-1
	x200503_g_shibing4 =-1
	x200503_g_tiemuzhen =-1 
	x200503_g_zhamuhe =-1   
	x200503_g_muhuali =-1   
	--x200503_g_shibing5 =-1
	x200503_g_acceptid =-1
	x200503_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x200503_GetBonus( sceneId, selfId,NpcID)
	  if x200503_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x200503_g_ExpBonus);
  	end
		if x200503_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x200503_g_BonusMoney1 )
	  end
		if x200503_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x200503_g_BonusMoney2 )
	  end
		if x200503_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x200503_g_BonusMoney3 )
		end
		if x200503_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x200503_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x200503_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x200503_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x200503_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x200503_g_BonusMoney6)
		end
end

function x200503_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x200503_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x200503_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x200503_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x200503_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x200503_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x200503_g_MissionName.."��", 0, 3)
				if x200503_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200503_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x200503_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x200503_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x200503_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x200503_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x200503_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x200503_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x200503_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x200503_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x200503_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200503_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x200503_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x200503_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x200503_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x200503_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x200503_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x200503_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x200503_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x200503_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x200503_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x200503_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x200503_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x200503_g_MissionId, state, -1 )
		end
end

function x200503_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x200503_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x200503_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x200503_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x200503_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x200503_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end