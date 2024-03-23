--�����ֻ�̨boss

--MisDescBegin
x256233_g_ScriptId = 256233
--x256233_g_MissionIdPre =455
x256233_g_MissionId = 3125
x256233_g_LevelLess	= 	30
--x256233_g_MissionIdNext = 457
x256233_g_DemandKill ={{id=2533,num=1}}
x256233_g_Name	={"boss"}
x256233_g_ExtTarget={{type=20,n=1,target="ǰ��#G�ֻ�̨#Wʹ�á�#G���޻�ʯ#W���ٻ��������������صľ���"}}
x256233_g_MissionName="���������ֻ�̨�ľ���"
x256233_g_MissionInfo="\t�������˵���ֻ�̨�����ؾ��޵Ĵ�˵��\n\t��˵ֻҪӵ���Ǿ��޻�ʯ���Ϳ������ֻ�̨���ٻ�������µĹ��ޡ�"  --��������
x256233_g_MissionTarget=""		
x256233_g_MissionCompleted="\t�����治�򵥣���������Ӧ�õĽ�����"
x256233_g_ContinueInfo="����û�����ǿ��µľ�����������ڽ���̵�����һ�������̵깺��#G���޻�ʯ��#W���ٻ�����"
x256233_g_MissionHelp =	"#G�����޻�ʯ��#W�����ڽ���̵�����һ�������̵깺�򣬵���Ҫ���ĳ�ֵ�ﵽһ���Ľ����ܻ�����й�����Ӧ��Ʒ��Ȩ�ޡ�"
x256233_g_DemandItem ={}
x256233_g_BonusMoney1 =0
x256233_g_BonusMoney2 =0
x256233_g_BonusMoney3 =0
x256233_g_BonusMoney4 =0
x256233_g_BonusMoney5 =0
x256233_g_BonusMoney6 =0
x256233_g_BonusItem	={}
x256233_g_BonusChoiceItem ={}
x256233_g_ExpBonus = 450000

x256233_g_NpcGUID ={{ guid = 150525, name = "�ֻ�̨����"} }
x256233_g_Impact1 = 2092
x256233_g_npcid = 0
--MisDescEnd
x256233_g_ExpBonus1 = 100000
--**********************************

function x256233_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    --DelQuest(sceneId, selfId, x256233_g_MissionId)
    
	if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
		return 
	end
	--if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionIdPre)> 0 then 
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x256233_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x256233_g_MissionId, state, -1 )
	--end
end

function x256233_DispatchMissionInfo( sceneId, selfId, NPCId )

		if x256233_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256233_g_ExpBonus )
		end
		if x256233_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256233_g_BonusMoney1 )
		end
		if x256233_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256233_g_BonusMoney2 )
		end
		if x256233_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256233_g_BonusMoney3 )
		end
		if x256233_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256233_g_BonusMoney4 )
		end
		if x256233_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256233_g_BonusMoney5 )
		end
		if x256233_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256233_g_BonusMoney6 )
		end
		for i, item in x256233_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x256233_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--������ں���

--**********************************
function x256233_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
    x256233_g_npcid =   NPCId
	if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) > 0 then
			if x256233_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
            
					BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256233_g_MissionName)
						AddQuestText(sceneId,x256233_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x256233_g_ScriptId, x256233_g_MissionId);
			else
          
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256233_g_MissionName)
						AddQuestText(sceneId,x256233_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256233_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256233_g_ScriptId, x256233_g_MissionId);
			end
  elseif x256233_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256233_g_MissionName)
			AddQuestText(sceneId,x256233_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256233_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256233_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256233_g_MissionHelp )
			end
			x256233_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256233_g_ScriptId, x256233_g_MissionId);
  end
end
--**********************************
function x256233_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
		return 0
	elseif GetLevel(sceneId, selfId)< x256233_g_LevelLess then
		return 0
	end
	return 1
end
--**********************************
function x256233_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x256233_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,0) == x256233_g_DemandKill[1].num then
             
	    		SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	        return 1
	end
	return 0
end
--**********************************
function x256233_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
				return 
		end
		
		--���ǰ������
--		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256233_g_MissionId  )
--		if FrontMissiontId1 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
--				return 0
--			end
--		end
--		if FrontMissiontId2 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
--				return 0
--			end
--		end
--		if FrontMissiontId3 ~= -1 then
--			if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
--				return 0
--			end
--		end
		
		if x256233_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256233_g_MissionId, x256233_g_ScriptId, 1, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			
           
						x256233_Msg2toplayer( sceneId, selfId,0)
						--if x256233_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256233_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x256233_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256233_g_MissionId)
		
	  x256233_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x256233_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256233_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x256233_g_BonusChoiceItem do
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
function x256233_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId)
	if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256233_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256233_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256233_g_MissionId) > 0 then
				x256233_Msg2toplayer( sceneId, selfId,2)
				
				QuestCom(sceneId, selfId, x256233_g_MissionId)
                x256233_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256233_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256233_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		    end
    		    EndAddItem(sceneId,selfId)
    		    local nCount = GetNearTeamCount(sceneId, selfId)
    			if nCount > 0 then
	    			for i = 0,nCount - 1 do
	    				
	    				local objId = GetNearTeamMember(sceneId, selfId, i)
		    			if IsPlayerStateNormal(sceneId,objId ) == 1 and objId ~= selfId then --�Ƿ����
		    				AddExp(sceneId, objId, x256233_g_ExpBonus1);
		    			end
	    				
	    			end
    			end
				--CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256233_g_MissionIdNext )	
   end
end

function x256233_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
   	  local bFind  = 0
    for i ,item in x256233_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256233_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256233_g_MissionId, state, -1 )
		end
end

function x256233_GetBonus( sceneId, selfId,NpcID)
	  if x256233_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256233_g_ExpBonus);
  	end
		if x256233_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256233_g_BonusMoney1 )
	  end
		if x256233_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256233_g_BonusMoney2 )
	  end
		if x256233_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256233_g_BonusMoney3 )
		end
		if x256233_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256233_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256233_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256233_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256233_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256233_g_BonusMoney6)
		end
end

function x256233_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256233_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256233_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256233_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256233_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256233_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256233_g_MissionName.."��", 0, 3)
				if x256233_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256233_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256233_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256233_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256233_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256233_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256233_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256233_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256233_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256233_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256233_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256233_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256233_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256233_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

--**********************************

function x256233_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==x256233_g_DemandKill[1].id then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x256233_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x256233_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 1 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("�����ֻ�̨�����ؾ���   %d/1", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x256233_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end
--**********************************

function x256233_OnUseItem( sceneId, selfId, BagIndex, impactId )
	local sceneType = GetSceneType(sceneId) ;
	if sceneType == 1 then 	
	
		local fubentype = GetFubenData_Param(sceneId,0) ;		--ȡ�ø�����
		local fubenscript = GetFubenData_Param(sceneId,1) ; 	--ȡ�ýű���
		local level =GetLevel(sceneId, selfId)
		if IsQuestHaveDone(sceneId, selfId, x256233_g_MissionId) > 0 then
				Msg2Player(sceneId, selfId, "���Ѿ���ɹ��������ˡ�", 0, 3)
				return 
		end
		if IsHaveQuest(sceneId,selfId, x256233_g_MissionId) > 0 then
				Msg2Player(sceneId, selfId, "���Ѿ��������������", 0, 3)
				return
		end
		if 	fubentype==FUBEN_FUTUTA4  then      	--���ֻ�̨����
			if level	>=	x256233_g_LevelLess	 then
				
			   		AddQuest( sceneId, selfId, x256233_g_MissionId, x256233_g_ScriptId, 1, 0, 0,1)
			   		Msg2Player(sceneId, selfId, "����������񣺡��������ֻ�̨�ľ���", 0, 3)
     		   		CreateMonster(sceneId, 2533,62,58,5,1,-1,-1,21,1200000)
     		   		DelItem( sceneId,selfId,12030033,1 )	
     		
     		else
    		   Msg2Player(sceneId, selfId, "��ĵȼ�����", 0, 3)	
    		end
    	end
    else 
    		Msg2Player(sceneId, selfId, "ֻ�����ֻ�̨�����ڲ����ٻ�����", 0, 3)	
    	
	end
end
--**********************************
function x256233_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256233_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256233_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256233_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256233_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256233_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256233_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256233_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256233_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256233_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





