--�߷���ɽ��

--MisDescBegin
x203327_g_ScriptId = 203327
x203327_g_MissionIdPre = 808
x203327_g_MissionId = 809
x203327_g_LevelLess	= 	88
x203327_g_MissionIdNext = 810
x203327_g_Name	={}
x203327_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_117005"}}
x203327_g_MissionName="���糡���߷���ɽ��<��>"
x203327_g_MissionInfo="\t�ã������ȥ������ɯ���治֪����ͻȻ���ҵ�����ʲô�£��ң����е㼤������\n\t�����ɣ�����ȥ�������������Ͼ͵����ң��ҵ�׼��һ�£�"  --��������
x203327_g_MissionTarget=""		
x203327_g_MissionCompleted="\t�ã��Ҿ���������������ɡ� "					--�������npc˵���Ļ�
x203327_g_ContinueInfo=""
x203327_g_MissionHelp =	""
x203327_g_DemandItem ={}
x203327_g_ExpBonus = 684000
x203327_g_BonusMoney1 =880
x203327_g_BonusMoney2 =0
x203327_g_BonusMoney3 =0
x203327_g_BonusMoney4 =0
x203327_g_BonusMoney5 =106
x203327_g_BonusMoney6 =0
x203327_g_BonusItem	=	{}
x203327_g_BonusChoiceItem ={}
x203327_g_NpcGUID ={{ guid = 117005, name = "�������"} }

--MisDescEnd
x203327_g_litaowandagong =-1
x203327_g_doing =0
x203327_g_kashandagong =-1
--x203327_g_kashandagong =-1
--x203327_g_litaowandagong =-1
--x203327_g_mengguwushi2 =-1
--x203327_g_mengguwushi3 =-1
--x203327_g_mengguwushi4 =-1
x203327_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0} --����ʱ�ӿؼ�
x203327_g_acceptid =-1
--**********************************

function x203327_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203327_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203327_g_MissionIdPre)> 0 then
			if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203327_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203327_g_MissionId, state, -1 )
			end		
	end
end

function x203327_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203327_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203327_g_ExpBonus )
		end
		if x203327_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203327_g_BonusMoney1 )
		end
		if x203327_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203327_g_BonusMoney2 )
		end
		if x203327_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203327_g_BonusMoney3 )
		end
		if x203327_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203327_g_BonusMoney4 )
		end
		if x203327_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203327_g_BonusMoney5 )
		end
		if x203327_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203327_g_BonusMoney6 )
		end
		for i, item in x203327_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203327_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203327_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203327_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) > 0 then
			if x203327_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203327_g_MissionName)
						AddQuestText(sceneId,x203327_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203327_g_ScriptId, x203327_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203327_g_MissionName)
						AddQuestText(sceneId,x203327_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203327_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203327_g_ScriptId, x203327_g_MissionId);
			end
  elseif x203327_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203327_g_MissionName)
			AddQuestText(sceneId,x203327_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203327_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203327_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203327_g_MissionHelp )
			end
			x203327_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203327_g_ScriptId, x203327_g_MissionId);
  end
	
end
--**********************************

function x203327_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203327_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203327_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203327_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203327_g_MissionId  )
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
		
		if x203327_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203327_g_MissionId, x203327_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203327_Msg2toplayer( sceneId, selfId,0)
		  			--BeginAddItem(sceneId)																																----���������Ʒ
						--	for i, item in x203327_g_DemandItem do
 						--		AddItem( sceneId, item.item, item.num )
						--	end
    				--EndAddItem(sceneId,selfId)                                                          ----���������Ʒ
    				--AddItemListToPlayer(sceneId,selfId)	
						--if x203327_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203327_g_MissionId)								                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203327_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203327_g_MissionId)
	  x203327_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203327_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203327_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203327_g_BonusChoiceItem do
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
function x203327_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203327_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203327_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203327_g_MissionId) > 0 then
				x203327_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203327_g_MissionId)
				--DelItem( sceneId,selfId,13010030,1 )                                                --ɾ�����ŵ���Ʒ
				x203327_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203327_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203327_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		
    		x203327_g_litaowandagong =FindMonsterByGUID( sceneId,117005)
    			if x203327_g_doing==0 then
						if x203327_g_kashandagong==-1 then
								if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
    			    			NpcTalk(sceneId, x203327_g_litaowandagong, "�����ˣ������ǰ���ע�����ܣ���Ҫ�����ǵ�צ��������", -1)
    			    	end
    			    			x203327_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
										x203327_g_doing =1
										x203327_g_kashandagong=CreateMonster(sceneId, 2106,140,48,3,1,-1,-1,20,52500,180)      
    			          x203327_g_PROTECTINFO.StartTime = GetCurrentTime()
										x203327_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203327, "OnScneneTimer", 1)
    			  end
					end
	 	end        
									
    		--AddItemListToPlayer(sceneId,selfId)

   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203327_g_MissionIdNext )	
end


function x203327_OnScneneTimer(sceneId)
	if x203327_g_doing==1   then				
	   if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 4   then
			  x203327_g_doing = 3
			 
				if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
				
						NpcTalk(sceneId, x203327_g_litaowandagong, "ɽ��³������Ϊ��ɽ�������һ���ӱ������裬���˿�����ô���㣬������һ�����Ǹ��󹫣�", -1)
				end
     end
	 elseif x203327_g_doing == 3   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 9   then
						x203327_g_doing =5
						if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								NpcTalk(sceneId, x203327_g_kashandagong, "�ң��Ҳ��룬�����Ҵ򲻹����ǣ����¡���", -1)
						end
			end
	 elseif x203327_g_doing == 5   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 13  then
						x203327_g_doing =6
						if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
								NpcTalk(sceneId, x203327_g_litaowandagong, "�£�����ʲô����Ϊһ�����ˣ�ͳ�ο�ɽ�Ĵ󹫣��㾹Ȼ��һ��Ů��˵���£�", -1)
						end
			end
	 elseif x203327_g_doing == 6   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 18   then
						x203327_g_doing =7
						if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								NpcTalk(sceneId, x203327_g_kashandagong, "���������Ҳ��������ǣ������£��£�����ʧ���ˣ���ῴ�����ң��»�ǣ���㣡", -1)
						end
			end
	 elseif x203327_g_doing == 7   then
			--if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 11   then
						--x203327_g_doing =8
						--if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								--NpcTalk(sceneId, x203327_g_kashandagong, "ס�֣��Ҿ�����Ҫ�ҵĴ̿ͣ����������ղ��󺹣���Ϊһ��С������ʲô���£�", -1)
						--end
	    --end
	---elseif x203327_g_doing == 8   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 23   then
						x203327_g_doing =9
						if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
								NpcTalk(sceneId, x203327_g_litaowandagong, "���Ǽ����Ǳ�Ϊ�飬����������ŭ����������ƣ��ɹŴ��һͳ˹��������Ѿ��Ǳ�Ȼ֮�ƣ�", -1)
						end
			end
	 elseif x203327_g_doing == 9  then   
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 28   then 	
						x203327_g_doing =10			
						if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
								NpcTalk(sceneId, x203327_g_litaowandagong, "�ң�����ɯ���������������ͳ���ߣ�Ҳ��һ��Ů�ˣ���ֻ��޸�һ��Ӣ�ۣ�������һ��ί����ȫ�Ĺ��ܣ�", -1)
						end
			end
	 elseif x203327_g_doing == 10   then	
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 32   then 
				x203327_g_doing =11		                                     				
						if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								NpcTalk(sceneId, x203327_g_kashandagong, "�ã���Ȼ����ô˵����ҲҪ���㿴������ɽ��³����ɽ�󹫣�Ҳ��һ�����Ӻ���", -1)
						end
			end
	 elseif x203327_g_doing == 11   then
			if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 37   then      
				x203327_g_doing =12	
				if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then 
					NpcTalk(sceneId, x203327_g_litaowandagong, "�ã����ɹŴ�������źţ����Ǿ���Ӧ��ϡ��²��ɣ��Һ���һ��ȥ�ϵ�����������ǣ�", -1)                                          
						---x203327_g_doing =10
				end		
						---if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
								---NpcTalk(sceneId, x203327_g_kashandagong, "�벻��......��ľ�澹Ȼ��˴�ȣ���ԸΪ�󺹳�������ˮ��ʹ��ϣ���ʯ��ʹ���飡", -1)
						---end
			end
	 elseif x203327_g_doing == 12   then 
	     if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 42  then 
				x203327_g_doing =13		                                     				
						if IsObjValid (sceneId,x203327_g_kashandagong) == 1 then
	  				NpcTalk(sceneId, x203327_g_kashandagong, "�ã�����Ը���������ȥ���ϵۣ�Ҳ��Ը�ڶ�ħצ����������������ң���Ҫ������������������ֻ���", -1)
	---elseif x203327_g_doing == 10   then
			--if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 15   then
						--x203327_g_doing =11
						--if IsObjValid (sceneId,x203327_g_litaowandagong) == 1 then
								--NpcTalk(sceneId, x203327_g_litaowandagong, "�ã��ӽ��Ժ�������ҵ�---�ܱ������֣�", -1)
						end
			end
    elseif x203327_g_doing==13 then
			 if GetCurrentTime() - x203327_g_PROTECTINFO.StartTime >= 45  then
			  x203327_g_doing=13
			   x203327_CloseTimer(sceneId, x203327_g_PROTECTINFO.ScneneTimerIndex)
			 end
	 end
end



--**********************************
--�رռ�ʱ��
--**********************************
function x203327_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203327_g_doing =0
	x203327_g_litaowandagong =-1
  x203327_g_doing =0
  x203327_g_kashandagong =-1
  --x203327_g_kashandagong =-1
  --x203327_g_litaowandagong =-1
  --x203327_g_mengguwushi2 =-1
  --x203327_g_mengguwushi3 =-1
  --x203327_g_mengguwushi4 =-1
	x203327_g_acceptid =-1
	x203327_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x203327_GetBonus( sceneId, selfId,NpcID)
	  if x203327_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203327_g_ExpBonus);
  	end
		if x203327_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203327_g_BonusMoney1 )
	  end
		if x203327_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203327_g_BonusMoney2 )
	  end
		if x203327_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203327_g_BonusMoney3 )
		end
		if x203327_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203327_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203327_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203327_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203327_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203327_g_BonusMoney6)
		end
end

function x203327_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203327_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203327_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203327_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203327_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203327_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203327_g_MissionName.."��", 0, 3)
				if x203327_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203327_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203327_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203327_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203327_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203327_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203327_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203327_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203327_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203327_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203327_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203327_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203327_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203327_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203327_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203327_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203327_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203327_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203327_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203327_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203327_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203327_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203327_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203327_g_MissionId, state, -1 )
		end
end

function x203327_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203327_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203327_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203327_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203327_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203327_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end