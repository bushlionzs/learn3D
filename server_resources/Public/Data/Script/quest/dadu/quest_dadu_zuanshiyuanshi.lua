--�һ���ʯ

--MisDescBegin
x270101_g_ScriptId = 270101
x270101_g_MissionIdPre = 3132
x270101_g_MissionId = 3131
x270101_g_LevelLess	= 65 
--x270101_g_MissionIdNext = 3006
x270101_g_DemandKill ={}
x270101_g_Name	={}
x270101_g_ExtTarget={{type=20,n=1,target="@npc_140910�ҵ�#G��¼#W�һ���ʯԭʯ"}}
x270101_g_MissionName="�����ˡ���ȡ��ʯ"
x270101_g_MissionInfo="\t��Ȼ�������˽��ܣ���Ҳ�����������ԣ�װ����������Ҫ����ʯ�ͽ�ձ���ʹ����ʯԭʯ����������ʯԭʯ��Ψһ�������ھ�Ҥ��\n\t�����ͨ��ʯ���ƽ����Ҥ��������¼���ܹ���󣬿�ʹ�ô�����ԭ����ʯ������һ�����ʯԭʯ��ʯ���ƾ������ߣ������ھͿ���ȥ��������ʯԭʯ��������������������������ܽ�����һ��ԭʯ���ҽ�����͸�����������ԭʯ����ȥ�ɣ���һ��ֻ����һ�λ��ᣡ"  --��������
x270101_g_MissionTarget="@npc_140910�ҵ�#G��¼#W�һ���ʯԭʯ"		
x270101_g_MissionCompleted="\t�����õ���һ����������ʯԭʯ�Ϳ�����������һ��ɴ��켫Ʒ��װ����ʯ���߽�ա�"
x270101_g_ContinueInfo="\t������ܽ�����һ��ԭʯ���ҽ�����͸�����������ԭʯ����ȥ�ɣ���һ��ֻ����һ�λ��ᣡ"
x270101_g_MissionHelp =	""
x270101_g_DemandItem ={11990113}
x270101_g_BonusMoney1 =0
x270101_g_BonusMoney2 =0
x270101_g_BonusMoney3 =0
x270101_g_BonusMoney4 =0
x270101_g_BonusMoney5 =0
x270101_g_BonusMoney6 =0
x270101_g_BonusItem	={{id=11990113,num=2}}
x270101_g_BonusChoiceItem ={}
x270101_g_ExpBonus = 10000
--x270101_g_NpcGUID = {{guid = 140915	, name = "�Ϲ�ʯ"}}
--x270101_g_Impact1 = 2092
--x270101_g_npcid = 0
--x270101_g_chaerke =0
--x270101_g_dog =0
--x270101_g_pangxie = 0
--x270101_g_acceptid =0
--x270101_g_GroupPoint	=	{ {type=10,id =176,target = "ʯ��"}  }--ר�����ڲɼ�����Ч�ã����������δ�ؾ����������ı�Ҫ���أ���ˣ�ֻҪ��ؾͿ��������������

--MisDescEnd
--**********************************

function x270101_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
   
	if IsQuestHaveDone(sceneId, selfId, x270101_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270101_g_MissionIdPre)> 0 then 
			--if IsQuestHaveDone(sceneId, selfId, x270101_g_MissionIdPre[2])> 0 then 
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x270101_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x270101_g_MissionId, state, -1 )
			--end
	end
end

function x270101_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270101_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270101_g_ExpBonus )
		end
		if x270101_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270101_g_BonusMoney1 )
		end
		if x270101_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270101_g_BonusMoney2 )
		end
		if x270101_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270101_g_BonusMoney3 )
		end
		if x270101_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270101_g_BonusMoney4 )
		end
		if x270101_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270101_g_BonusMoney5 )
		end
		if x270101_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270101_g_BonusMoney6 )
		end
		for i, item in x270101_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x270101_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--������ں���

--**********************************
function x270101_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270101_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270101_g_MissionId) > 0 then
			if x270101_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270101_g_MissionName)
						AddQuestText(sceneId,x270101_g_ContinueInfo)
					  --AddQuestText(sceneId,"#Y����Ŀ��#W") 
					  --AddQuestText(sceneId,x270101_g_MissionTarget) 
						-- AddQuestText(sceneId,format("\n    �����ʯԭʯ   %d/%d", GetItemCount(sceneId,selfId,x270101_g_DemandItem.id),x270101_g_DemandItem.num ))
					EndQuestEvent()
						
						DispatchQuestEventList(sceneId, selfId, NPCId);
			else
          
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270101_g_MissionName)
						AddQuestText(sceneId,x270101_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270101_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270101_g_ScriptId, x270101_g_MissionId);
			end
  elseif x270101_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270101_g_MissionName)
			AddQuestText(sceneId,x270101_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270101_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270101_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270101_g_MissionHelp )
			end
			x270101_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270101_g_ScriptId, x270101_g_MissionId);
  end
end
--**********************************
function x270101_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x270101_g_MissionId) > 0 then
		return 0
	elseif GetLevel(sceneId, selfId)< x270101_g_LevelLess then
		return 0
	end
	return 1
	
end
--**********************************
function x270101_CheckSubmit( sceneId, selfId, NPCId)
		if  IsHaveQuest(sceneId, selfId,x270101_g_MissionId) ~=1 then
			return 0
		end
		
	   	local 	misIndex = GetQuestIndexByID(sceneId, selfId,x270101_g_MissionId)                                                  
	   	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	   		return 1
	   	else 
	   		return 0
	   	end
	   	
end
--**********************************
function x270101_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		
		
		if IsQuestHaveDone(sceneId, selfId, x270101_g_MissionId) > 0 then
				return 
		end
		--���ǰ������
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270101_g_MissionId  )
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
		if x270101_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270101_g_MissionId, x270101_g_ScriptId, 0, 0, 1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "�����������޷���������", 0, 3)
						return 0
					else
		  			-- SendSpecificImpactToUnit(sceneId, selfId, selfId, NPCId, x270101_g_Impact1, 0)
            -- CreateMonster(sceneId, 811,132,70,5,1,-1,-1,21,120000)
						x270101_Msg2toplayer( sceneId, selfId,0)
						--if x270101_CheckSubmit(sceneId, selfId, NPCId) > 0 then
					for i, item in x270101_g_DemandItem do
						if GetItemCount(sceneId,selfId,item) >= 1 then		
							local misIndex = GetQuestIndexByID(sceneId,selfId,x270101_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
						end
					end
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x270101_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270101_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270101_g_MissionId)

	  x270101_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x270101_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270101_g_BonusItem do
		AddBindItem( sceneId, item.id, item.num )
  end
  for j, item in x270101_g_BonusChoiceItem do
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
function x270101_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
  --x270101_g_chaerke =FindMonsterByGUID( sceneId,138016)
  --x270101_g_dog =FindMonsterByGUID( sceneId,138017)
	if IsHaveQuest(sceneId,selfId, x270101_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270101_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270101_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270101_g_MissionId) > 0 then
				x270101_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270101_g_MissionId)
				--x270101_g_acceptid =selfId
				--x270101_g_pangxie=CreateMonster(sceneId,1839, 37, 190, 1, 0, -1,-1,20,15000,180,"С�з","����˵ĳ���")
				--SetPatrolId(sceneId, x270101_g_pangxie, 0)
				--NpcTalk(sceneId, x270101_g_chaerke, "С�з��#35����棡#42", x270101_g_acceptid)
				--NpcTalk(sceneId, x270101_g_dog, "����������", x270101_g_acceptid)
        x270101_GetBonus( sceneId, selfId,NPCId)			
				BeginAddItem(sceneId)
				for i, item in x270101_g_BonusItem do
 						AddBindItem( sceneId, item.id, item.num )
				end
				for i, item in x270101_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		    end
    		    
    		    EndAddItem(sceneId,selfId)
    		    AddItemListToPlayer(sceneId,selfId)
						DelItem(sceneId, selfId, x270101_g_DemandItem[1], 1)
				--CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270101_g_MissionIdNext )	
				
   end
end

function x270101_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

   
end

function x270101_GetBonus( sceneId, selfId,NpcID)
	  if x270101_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270101_g_ExpBonus);
  	end
		if x270101_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270101_g_BonusMoney1 )
	  end
		if x270101_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270101_g_BonusMoney2 )
	  end
		if x270101_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270101_g_BonusMoney3 )
		end
		if x270101_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270101_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270101_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270101_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270101_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270101_g_BonusMoney6)
		end
end

--**********************************

function x270101_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

 --if IsHaveQuest(sceneId, selfId, x270101_g_MissionId) > 0 then 
	-- local misIndex = GetQuestIndexByID(sceneId,selfId,x270101_g_MissionId)  
	-- local num = GetQuestParam(sceneId,selfId,misIndex,0) 
	-- 	 if objdataId == x270101_g_DemandKill[1].id then 
 --      		 if GetItemCount(sceneId,selfId,x270101_g_DemandItem[1].id) < x270101_g_DemandItem[1].num then
 --      		    	        SetQuestByIndex(sceneId,selfId,misIndex,0,num+1)
 --      		           BeginAddItem(sceneId)                                                    
	--			 							AddItem( sceneId,x270101_g_DemandItem[1].id, 1 )             
	--			 						local ret = EndAddItem(sceneId,selfId)                                 
	--	        				 if ret > 0 then     
	--	        				 	BeginQuestEvent(sceneId)       
	--		                AddQuestText(sceneId,format("#cffcf00ץ��#G�з#cffcf00  %d/%d", GetQuestParam(sceneId,selfId,misIndex,0),x270101_g_DemandItem[1].num )) 
	--		                EndQuestEvent()    
	--		                DispatchQuestTips(sceneId, selfId)
	--		                AddItemListToPlayer(sceneId,selfId) 
	--	        	 			else                                                             
	--	        	 				BeginQuestEvent(sceneId)                                      
	--			     					AddQuestText(sceneId,"��Ʒ��������")                    
	--			        			EndQuestEvent(sceneId)                                        
	--			        			DispatchQuestTips(sceneId,selfId) 
	--			 						end
	--			 						        
	--		                if GetQuestParam(sceneId,selfId,misIndex,0) >= x270101_g_DemandKill[1].num then
	--		                SetQuestByIndex(sceneId,selfId,misIndex,7,1)
 --                     end  
	--		                		--if GetQuestParam(sceneId,selfId,misIndex,0) >=5 then
	--		                				--SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	--		                		--end
	--		                	
	--		                end         
 --      		 end
 --  --if num =	 x270101_g_DemandKill[1].num then
 --  --SetQuestByIndex(sceneId,selfId,misIndex,7,1)
 --  --end
 --     end  
end
--**********************************

function x270101_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270101_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270101_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270101_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270101_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270101_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270101_g_MissionName.."��", 0, 3)
				if x270101_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270101_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270101_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270101_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270101_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270101_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270101_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270101_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270101_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270101_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270101_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270101_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270101_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270101_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end
function x270101_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270101_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270101_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270101_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId,optype)
	if	optype	==	0	then
		return
	end
	
	for i, item in x270101_g_DemandItem do
	
		if itemdataId == item then

			if GetItemCount(sceneId,selfId,item) >= 1 then
					local misIndex = GetQuestIndexByID(sceneId,selfId,x270101_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,1)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
		  	else
		  			local misIndex = GetQuestIndexByID(sceneId,selfId,x270101_g_MissionId)                                                  
		    		SetQuestByIndex(sceneId,selfId,misIndex,0,0)
		    		SetQuestByIndex(sceneId,selfId,misIndex,7,0)
		  	end
		  	
		  	break
	  	
	  	end
	  	
	end

end


function x270101_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270101_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270101_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270101_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270101_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270101_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





