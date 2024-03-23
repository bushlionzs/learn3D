--�����顿�ӳ�����

--MisDescBegin
x203313_g_ScriptId = 203313
x203313_g_MissionIdPre =676
x203313_g_MissionId = 671
x203313_g_LevelLess	= 	75
x203313_g_MissionIdNext = -1
x203313_g_Name	={}
x203313_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_114033��������λ����һ���ӳ���ɳĮ"}}
x203313_g_MissionName="�����顿�ӳ�����"
x203313_g_MissionInfo="\t�����ǵ�������û�е�����ϵ����ߵ�ɽ���£�������һ��С·����ƥ����˳��ͨ���������Һ͹�����������������ǡ�"  --��������
x203313_g_MissionTarget=""		
x203313_g_MissionCompleted="\t̫���ˣ�����һ�ж��Ѿ�׼�����ˣ��������ڳ��ϵȴ����ǡ������ǻ�û��׷�������챣����λ������С·�ߣ�"					--�������npc˵���Ļ�
x203313_g_ContinueInfo=	""
x203313_g_MissionHelp =	""
x203313_g_DemandItem ={}
x203313_g_BonusMoney1 =750
x203313_g_BonusMoney2 =0
x203313_g_BonusMoney3 =0
x203313_g_BonusMoney4 =0
x203313_g_BonusMoney5 =86
x203313_g_BonusMoney6 =0
x203313_g_BonusItem	=	{}
x203313_g_BonusChoiceItem ={}
x203313_g_ExpBonus = 440000
x203313_g_NpcGUID ={{ guid = 114033, name = "����"}}

--MisDescEnd
x203313_g_doing = 0
x203313_g_mohemo = -1
x203313_g_zhalanding = -1
x203313_g_quchulv = -1
x203313_g_shibing1 = -1
x203313_g_shibing2 = -1
x203313_g_hedan = -1
x203313_g_xuliewu = -1
x203313_g_alibuge = -1
x203313_g_baierda = -1
x203313_g_mengguyongshi1 = -1
x203313_g_mengguyongshi2 = -1
x203313_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--**********************************


----------------------------------------------------------------------------------------------
--����Χ��ҷ���Ч������Ƶ��ʹ��
----------------------------------------------------------------------------------------------
function x203313_PlayeffectToNearPlayer(sceneId,npcID,nEffect)

	if IsObjValid(sceneId,npcID) ~= 1 then
		return
	end
	
	local nHumanCount = GetScenePlayerCount( sceneId )
	for i=0,nHumanCount do

		local objId = GetScenePlayerObjId(sceneId,i)
		if IsPlayerStateNormal(sceneId,objId) == 1 then
			
			if GetDist(sceneId,objId,npcID,25 ) <= 25 then
				CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,objId,nEffect)
			end
		end
	end

end

function x203313_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if GetLevel( sceneId, selfId) < x203313_g_LevelLess then
		return
   end

	if IsQuestHaveDone(sceneId, selfId, x203313_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203313_g_MissionIdPre)> 0 then
	
						if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) <= 0 then
								local state = GetQuestStateNM(sceneId,selfId,NPCId,x203313_g_MissionId)
								AddQuestTextNM( sceneId, selfId, NPCId, x203313_g_MissionId, state, -1 )
						end
			
	end
end

function x203313_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203313_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203313_g_ExpBonus )
		end
		if x203313_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203313_g_BonusMoney1 )
		end
		if x203313_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203313_g_BonusMoney2 )
		end
		if x203313_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203313_g_BonusMoney3 )
		end
		if x203313_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203313_g_BonusMoney4 )
		end
		if x203313_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203313_g_BonusMoney5 )
		end
		if x203313_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203313_g_BonusMoney6 )
		end
		for i, item in x203313_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203313_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203313_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203313_g_MissionId) > 0 then
		return 
	end
	if GetLevel( sceneId, selfId) < x203313_g_LevelLess then
		return
   end
	if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) > 0 then
			if x203313_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203313_g_MissionName)
						AddQuestText(sceneId,x203313_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203313_g_ScriptId, x203313_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203313_g_MissionName)
						AddQuestText(sceneId,x203313_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203313_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203313_g_ScriptId, x203313_g_MissionId);
			end
  elseif x203313_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203313_g_MissionName)
			AddQuestText(sceneId,x203313_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203313_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203313_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203313_g_MissionHelp )
			end
			x203313_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203313_g_ScriptId, x203313_g_MissionId);
  end
	
end
--**********************************

function x203313_ProcAcceptCheck(sceneId, selfId, NPCId)

		
						return 1
		

end
--**********************************
function x203313_CheckSubmit( sceneId, selfId, NPCId)


	        return 1
	
end
--**********************************
function x203313_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203313_g_MissionId) > 0 then
				return 
		end
			if GetLevel( sceneId, selfId) < x203313_g_LevelLess then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203313_g_MissionId  )
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
	
		if x203313_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203313_g_MissionId, x203313_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
				
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203313_Msg2toplayer( sceneId, selfId,0)
		  			BeginAddItem(sceneId)
							for i, item in x203313_g_DemandItem do
 								AddItem( sceneId, item.item, item.num )
							end
    				EndAddItem(sceneId,selfId)
    				--AddItemListToPlayer(sceneId,selfId)	
						--if x203313_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203313_g_MissionId)								                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203313_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203313_g_MissionId)
	  x203313_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x203313_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203313_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203313_g_BonusChoiceItem do
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
function x203313_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203313_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203313_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203313_g_MissionId) > 0 then
				x203313_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203313_g_MissionId)
				x203313_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203313_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203313_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		
    		
    			if x203313_g_doing==0 then
						if x203313_g_mohemo==-1 then
    			    			x203313_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
										x203313_g_doing =1
										x203313_g_mohemo=CreateMonster(sceneId, 851,207,137,3,1,-1,-1,20,30000,180,"Ħڭĩ")
									  x203313_g_zhalanding=CreateMonster(sceneId, 852,203,136,3,1,-1,-1,20,30000,180,"������")
									  x203313_g_quchulv=CreateMonster(sceneId, 854,208,140,3,1,-1,-1,20,30000,180,"������")
									  x203313_g_shibing1=CreateMonster(sceneId, 843,207,145,3,1,-1,-1,20,30000,180,"ͻ��ʿ��")
										x203313_g_shibing2=CreateMonster(sceneId, 843,197,141,3,1,-1,-1,20,30000,180,"ͻ��ʿ��")
										x203313_g_shibing2=CreateMonster(sceneId, 843,103,143,3,1,-1,-1,20,30000,180,"ͻ��ʿ��")
										x203313_g_hedan=CreateMonster(sceneId, 859,209,130,3,1,-1,-1,20,30000,0,"�ϵ�")
										x203313_g_xuliewu=CreateMonster(sceneId, 859,203,126,3,1,-1,-1,20,30000,0,"����أ")
										x203313_g_alibuge=CreateMonster(sceneId, 859,214,119,3,1,-1,-1,20,30000,0,"���ﲻ��")
										x203313_g_baierda=CreateMonster(sceneId, 859,207,118,3,1,-1,-1,20,30000,0,"�ݶ���")
    			          x203313_g_PROTECTINFO.StartTime = GetCurrentTime()
										x203313_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 203313, "OnScneneTimer", 1)
    			  end
    			--elseif x203313_g_doing<=5 then
    								--if x203313_g_PROTECTINFO.PlayerNum > 5  then
												--return
										--end
									--	x203313_g_PROTECTINFO.PlayerNum = x203313_g_PROTECTINFO.PlayerNum + 1
										--x203313_g_PROTECTINFO.PlayerId[x203313_g_PROTECTINFO.PlayerNum] = selfId
						  		--	AddQuest( sceneId, selfId, x203313_g_MissionId, x203313_g_ScriptId, 1, 0, 0)
					  			--	x203313_Msg2toplayer( sceneId, selfId,0)
					--else
								--BeginQuestEvent(sceneId)
								--strText = "#Y���ڲ��ܽ��������"
								--AddQuestText(sceneId,strText)
								--EndQuestEvent(sceneId)
								--DispatchQuestTips(sceneId,selfId)
					end
	 	end        
									
    		--AddItemListToPlayer(sceneId,selfId)

   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203313_g_MissionIdNext )	
end


function x203313_OnScneneTimer(sceneId)
	if x203313_g_doing==1   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 3   then
						x203313_g_doing = 2
						if IsObjValid (sceneId,x203313_g_zhalanding) == 1 then
								NpcTalk(sceneId, x203313_g_zhalanding, "�ٺ٣����ߣ�������ô���ף�", -1)
						end
		end
	elseif x203313_g_doing==2   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 6   then
						x203313_g_doing = 3
						if IsObjValid (sceneId,x203313_g_mohemo) == 1 then
								NpcTalk(sceneId, x203313_g_mohemo, "������λ�������һ�����Կ��Ƿ�����һ����·��", -1)
						end
		end
	elseif x203313_g_doing==3   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 10   then
						x203313_g_doing = 4
						if IsObjValid (sceneId,x203313_g_zhalanding) == 1 then
								NpcTalk(sceneId, x203313_g_zhalanding, "���ǲ�������������֮�����ɼ�˼����ʲô������", -1)
						end
		end
	elseif x203313_g_doing==4   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 15   then
						x203313_g_doing = 5
						if IsObjValid (sceneId,x203313_g_hedan) == 1 then
								NpcTalk(sceneId, x203313_g_hedan, "����أ�����ǿ��ߣ�", -1)
						end
		end
	elseif x203313_g_doing==5   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 20   then
						x203313_g_doing = 6
						if IsObjValid (sceneId,x203313_g_hedan) == 1 then
								NpcTalk(sceneId, x203313_g_hedan, "��ʿ�ǣ��Թ�����ɽ��������������ǰ����Ϊ�����Ǵ��ɹŹ���������������ƴ�ˣ�", -1)
								--CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 14)
								--������Χ���
								x203313_PlayeffectToNearPlayer(sceneId,x203313_g_hedan,14)
						end
		end
	elseif x203313_g_doing==6   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 25   then
						x203313_g_doing = 7
						if IsObjValid (sceneId,x203313_g_xuliewu) == 1 then
								NpcTalk(sceneId, x203313_g_xuliewu, "�ϵ����ϵ���", -1)	
						end
		end
	elseif x203313_g_doing==7   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 31   then
						x203313_g_doing = 8
						if IsObjValid (sceneId,x203313_g_hedan) == 1 then							
									NpcTalk(sceneId, x203313_g_hedan, "����أ������Ӣ��һ������ȥû��Թ�ޣ�ֻ��������չ˺ù��ɣ�", -1)
						end	
		end
	elseif x203313_g_doing==8   then
		if GetCurrentTime() - x203313_g_PROTECTINFO.StartTime >= 35   then
						x203313_g_doing = 9
						x203313_CloseTimer(sceneId, x203313_g_PROTECTINFO.ScneneTimerIndex)
					end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x203313_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x203313_g_doing = 0
	x203313_g_mohemo = -1
	x203313_g_zhalanding = -1
	x203313_g_quchulv = -1
	x203313_g_shibing1 = -1
	x203313_g_shibing2 = -1
	x203313_g_hedan = -1
	x203313_g_xuliewu = -1
	x203313_g_mengguyongshi1 = -1
	x203313_g_mengguyongshi2 = -1
	x203313_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
end


function x203313_GetBonus( sceneId, selfId,NpcID)
	  if x203313_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203313_g_ExpBonus);
  	end
		if x203313_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203313_g_BonusMoney1 )
	  end
		if x203313_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203313_g_BonusMoney2 )
	  end
		if x203313_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203313_g_BonusMoney3 )
		end
		if x203313_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203313_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203313_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203313_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203313_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203313_g_BonusMoney6)
		end
end

function x203313_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203313_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203313_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203313_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203313_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203313_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203313_g_MissionName.."��", 0, 3)
				if x203313_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203313_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203313_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203313_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203313_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203313_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203313_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203313_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203313_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203313_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203313_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203313_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203313_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203313_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203313_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203313_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203313_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203313_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203313_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203313_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x203313_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203313_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203313_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203313_g_MissionId, state, -1 )
		end
end

function x203313_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203313_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203313_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203313_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203313_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203313_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end