--���糡����Ű֮��<һ>

--MisDescBegin
x203336_g_ScriptId = 203336
x203336_g_MissionIdPre = 851
x203336_g_MissionId = 852
x203336_g_LevelLess	= 90
x203336_g_MissionIdNext = 853
x203336_g_Name	={}
x203336_g_ExtTarget={{type=20,n=1,target="ѯ��@npc_118011"}}
x203336_g_MissionName="���糡����Ű֮��<һ>"
x203336_g_MissionInfo="\t�����Ҿ��е�����֮ʿ��ÿ����ô���ھ���α��ģ��ȵ����߰ɣ������������������ѡһ����"  --��������
x203336_g_MissionTarget=""		
x203336_g_MissionCompleted="\t����ô�ļ������Ͼ����ˡ�"	--�������npc˵���Ļ�
x203336_g_ContinueInfo=	""
x203336_g_MissionHelp =	""
x203336_g_DemandItem ={}
x203336_g_BonusMoney1 =920
x203336_g_BonusMoney2 =0
x203336_g_BonusMoney3 =0
x203336_g_BonusMoney4 =0
x203336_g_BonusMoney5 =116
x203336_g_BonusMoney6 =0
x203336_g_BonusItem	=	{}
x203336_g_BonusChoiceItem ={}
x203336_g_ExpBonus = 742000
x203336_g_NpcGUID ={{ guid = 118011, name = "����"}}

--MisDescEnd
x203336_g_doing = 0
x203336_g_shibing1 = -1
x203336_g_shibing2 = -1
x203336_g_meinv1 = -1
x203336_g_meinv2 = -1
x203336_g_meinv3 = -1
x203336_g_meinv4 = -1
x203336_g_meinv5 = -1
x203336_g_alibuge = -1
x203336_g_baierda = -1
x203336_g_mengguyongshi1 = -1
x203336_g_mengguyongshi2 = -1
x203336_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--**********************************

----------------------------------------------------------------------------------------------
--����Χ��ҷ���Ч������Ƶ��ʹ��
----------------------------------------------------------------------------------------------
  -- function x203336_PlayeffectToNearPlayer(sceneId,npcID,nEffect)
  --
  --	if IsObjValid(sceneId,npcID) ~= 1 then
  --		return
  --	end
  --	
  --	local nHumanCount = GetScenePlayerCount( sceneId )
  --	for i=0,nHumanCount do
  --
  --		local objId = GetScenePlayerObjId(sceneId,i)
  --		if IsPlayerStateNormal(sceneId,objId) == 1 then
  --			
  --			if GetDist(sceneId,objId,npcID,25 ) <= 25 then
  --				CallScriptFunction(SCENE_SCRIPT_ID,"PlayEffect",sceneId,objId,nEffect)
  --			end
  --		end
  --	end
  --
  --end

function x203336_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if GetLevel( sceneId, selfId) < x203336_g_LevelLess then
		return
   end

	if IsQuestHaveDone(sceneId, selfId, x203336_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203336_g_MissionIdPre)> 0 then
	
						if IsHaveQuest(sceneId,selfId, x203336_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x203336_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x203336_g_MissionId, state, -1 )
						end
			
	end
end

function x203336_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203336_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203336_g_ExpBonus )
		end
		if x203336_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203336_g_BonusMoney1 )
		end
		if x203336_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203336_g_BonusMoney2 )
		end
		if x203336_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203336_g_BonusMoney3 )
		end
		if x203336_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203336_g_BonusMoney4 )
		end
		if x203336_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203336_g_BonusMoney5 )
		end
		if x203336_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203336_g_BonusMoney6 )
		end
		for i, item in x203336_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203336_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203336_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203336_g_MissionId) > 0 then
		return 
	end
	if GetLevel( sceneId, selfId) < x203336_g_LevelLess then
		return
   end
	if IsHaveQuest(sceneId,selfId, x203336_g_MissionId) > 0 then
			if x203336_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203336_g_MissionName)
						AddQuestText(sceneId,x203336_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203336_g_ScriptId, x203336_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203336_g_MissionName)
						AddQuestText(sceneId,x203336_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203336_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203336_g_ScriptId, x203336_g_MissionId);
			end
  elseif x203336_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203336_g_MissionName)
			AddQuestText(sceneId,x203336_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203336_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203336_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203336_g_MissionHelp )
			end
			x203336_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203336_g_ScriptId, x203336_g_MissionId);
  end
	
end
--**********************************

function x203336_ProcAcceptCheck(sceneId, selfId, NPCId)

		
						return 1
		

end
--**********************************
function x203336_CheckSubmit( sceneId, selfId, NPCId)


	        return 1
	
end
--**********************************
function x203336_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203336_g_MissionId) > 0 then
				return 
		end
			if GetLevel( sceneId, selfId) < x203336_g_LevelLess then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203336_g_MissionId  )
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
	
		if x203336_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203336_g_MissionId, x203336_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
				
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203336_Msg2toplayer( sceneId, selfId,0)
		  			BeginAddItem(sceneId)
							for i, item in x203336_g_DemandItem do
 								AddItem( sceneId, item.item, item.num )
							end
    				EndAddItem(sceneId,selfId)
    				--AddItemListToPlayer(sceneId,selfId)	
						--if x203336_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203336_g_MissionId)								                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203336_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203336_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203336_g_MissionId)
	  x203336_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203336_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203336_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203336_g_BonusChoiceItem do
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
function x203336_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203336_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203336_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203336_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203336_g_MissionId) > 0 then
				x203336_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203336_g_MissionId)
				x203336_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203336_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203336_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		
    		
    			if x203336_g_doing==0 then
						if x203336_g_shibing1==-1 then
    			    			x203336_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
										x203336_g_doing =1
										x203336_g_shibing1=CreateMonster(sceneId,2117,117,202,3,1,-1,-1,20,30000,320,"�ɹ�ʿ��")
									    x203336_g_shibing2=CreateMonster(sceneId,2117,122,204,3,1,-1,-1,20,30000,320,"�ɹ�ʿ��")
									    x203336_g_meinv2=CreateMonster(sceneId,2502,118,203,3,1,-1,-1,20,30000,320,"��ץ�Ĺ���")
									    x203336_g_meinv1=CreateMonster(sceneId,71,119,204,3,1,-1,-1,20,30000,320,"��ץ�Ĺ���")
									    x203336_g_meinv3=CreateMonster(sceneId,73,121,203,3,1,-1,-1,20,30000,320,"��ץ�Ĺ���")
									    x203336_g_meinv4=CreateMonster(sceneId,74,120,202,3,1,-1,-1,20,30000,320,"��ץ�Ĺ���")
									    x203336_g_meinv5=CreateMonster(sceneId,71,121,201,3,1,-1,-1,20,30000,320,"��ץ�Ĺ���")
									    x203336_g_PROTECTINFO.StartTime = GetCurrentTime()
										x203336_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203336, "OnScneneTimer", 1)
    			  end
    			--elseif x203336_g_doing<=5 then
    								--if x203336_g_PROTECTINFO.PlayerNum > 5  then
												--return
										--end
									--	x203336_g_PROTECTINFO.PlayerNum = x203336_g_PROTECTINFO.PlayerNum + 1
										--x203336_g_PROTECTINFO.PlayerId[x203336_g_PROTECTINFO.PlayerNum] = selfId
						  		--	AddQuest( sceneId, selfId, x203336_g_MissionId, x203336_g_ScriptId, 1, 0, 0)
					  			--	x203336_Msg2toplayer( sceneId, selfId,0)
					--else
								--BeginQuestEvent(sceneId)
								--strText = "#Y���ڲ��ܽ��������"
								--AddQuestText(sceneId,strText)
								--EndQuestEvent(sceneId)
								--DispatchQuestTips(sceneId,selfId)
					end
	 	end        
									
    		--AddItemListToPlayer(sceneId,selfId)

   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203336_g_MissionIdNext )	
end


function x203336_OnScneneTimer(sceneId)
	if x203336_g_doing==1   then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 5   then
						x203336_g_doing = 2
						if IsObjValid (sceneId,x203336_g_shibing2) == 1 then
								NpcTalk(sceneId, x203336_g_shibing2, "���ӵ�����Ҫ���˶������ˣ�", -1)
						end
		end
	elseif x203336_g_doing==2   then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 2 then
						x203336_g_doing = 3
						if IsObjValid (sceneId,x203336_g_shibing1) == 1 then
								NpcTalk(sceneId, x203336_g_shibing1, "���Ƕ����ϣ�", -1)
						end
		end
	elseif x203336_g_doing==3   then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 2 then
						x203336_g_doing = 4
						if IsObjValid (sceneId,x203336_g_meinv1) == 1 then
								NpcTalk(sceneId, x203336_g_meinv1, "�������Ƿ��һؼҰ������أ�", -1)
						end
		end
	elseif x203336_g_doing==4   then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 5  then
						x203336_g_doing = 5
						if IsObjValid (sceneId,x203336_g_shibing2) == 1 then
								NpcTalk(sceneId, x203336_g_shibing2, "�������ˣ�", -1)
						end
		end
	elseif x203336_g_doing==5   then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 2  then
						x203336_g_doing = 6
						if IsObjValid (sceneId,x203336_g_meinv4) == 1 then
								NpcTalk(sceneId, x203336_g_meinv4, "���ء������أ�", -1)
						end
	  end
	elseif x203336_g_doing==6   then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 2 then
						x203336_g_doing = 7
						if IsObjValid (sceneId,x203336_g_meinv5) == 1 then
								NpcTalk(sceneId, x203336_g_meinv5, "��Ҫ�ؼң���Ҫ�ؼң�", -1)
						end
		end
	elseif x203336_g_doing==7   then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 5   then
						x203336_g_doing = 8
						if IsObjValid (sceneId,x203336_g_shibing1) == 1 then
								NpcTalk(sceneId, x203336_g_shibing1, "�������ˣ�", -1)
						end
		end
	elseif x203336_g_doing==8   then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 5   then
						x203336_g_doing = 9
						if IsObjValid (sceneId,x203336_g_meinv3) == 1 then
								NpcTalk(sceneId, x203336_g_meinv3, "���ء������أ�", -1)
						end						
		end
	elseif x203336_g_doing==9   then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 5  then
						x203336_g_doing = 10
						if IsObjValid (sceneId,x203336_g_shibing2) == 1 then
								NpcTalk(sceneId, x203336_g_shibing2, "�������滹�м���ģ������ģ�", -1)					
						end
		end
	elseif x203336_g_doing==10  then
		if GetCurrentTime() - x203336_g_PROTECTINFO.StartTime >= 5   then
						x203336_g_doing = 11
						x203336_CloseTimer(sceneId, x203336_g_PROTECTINFO.ScneneTimerIndex)
		        end
    end
   
end


--**********************************
--�رռ�ʱ��
--**********************************
function x203336_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203336_g_doing = 0
	x203336_g_shibing1 = -1
	x203336_g_shibing2 = -1
	x203336_g_meinv2 = -1
	x203336_g_meinv1 = -1
	x203336_g_meinv3 = -1
	x203336_g_meinv4 = -1
	x203336_g_meinv5 = -1
	x203336_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x203336_GetBonus( sceneId, selfId,NpcID)
	  if x203336_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203336_g_ExpBonus);
  	end
		if x203336_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203336_g_BonusMoney1 )
	  end
		if x203336_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203336_g_BonusMoney2 )
	  end
		if x203336_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203336_g_BonusMoney3 )
		end
		if x203336_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203336_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203336_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203336_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203336_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203336_g_BonusMoney6)
		end
end

function x203336_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203336_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203336_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203336_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203336_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203336_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203336_g_MissionName.."��", 0, 3)
				if x203336_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203336_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203336_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203336_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203336_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203336_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203336_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203336_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203336_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203336_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203336_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203336_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203336_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203336_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203336_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203336_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203336_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203336_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203336_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203336_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203336_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203336_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203336_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203336_g_MissionId, state, -1 )
		end
end

function x203336_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203336_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203336_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203336_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203336_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203336_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end