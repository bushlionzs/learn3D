--ѯ��״��

--MisDescBegin
x256218_g_ScriptId = 256218
x256218_g_MissionIdPre =3051
x256218_g_MissionId = 3093
x256218_g_LevelLess	= 	25 
x256218_g_MissionIdNext = 3052
x256218_g_Name	={}
x256218_g_ExtTarget={{type=20,n=1,target="��#Gˮ��#W��һ��#G����װ#W@npc_82068"}}
x256218_g_MissionName="�����ˡ���һ������"
x256218_g_MissionInfo="\t�װ������ѣ�������������㹻��#Gˮ��#W����ʹ�㽫һ��#G��������װ��#W������3�ǡ� \n\t���������װ�����Ǵ�ʦ���������������#Gװ������#W��ѡ���򿪴��ǵĹ�������ͬʱ����Ҳ���Զ��򿪡�\n\t �Ҽ������Ҫ#G�����װ��#W����װ�����Զ�������ǹ������У���ʱ���������·�ѡ��#G��ʯ#W�����#G����#W�ȼ���Ȼ����#G�Զ����ǻ����#W�Ϳ��Խ��д��ǵĲ����ˡ�\n\t������ɺ����رչ����������Ǿʹ˽������Ѵ��ǵ�װ��Ҳ���Զ��ص����ı����С�\n\t #Gע��װ����ǰ�����ǲ���ʧ�ܵģ�֮��Ϳ��ܻ���ִ���ʧ�ܵ������#W\n\t#G��-���Ǵ���ʧ�ܽ���ص����ǣ���������ʧ�ܽ���ص����ǣ�#W"  --��������
x256218_g_MissionTarget=""		
x256218_g_MissionCompleted="\t�������Ѿ���ϸ�����Ǽ�������3���ǵ�����װ�����о���Σ����Ǻ��װ��ȷʵ������ǰҪǿ���˲��ٰɡ�"					--�������npc˵���Ļ�
x256218_g_ContinueInfo="\t�㲻Ը��Ϊ����Ǽ�����װ������������"
x256218_g_MissionHelp =	""
x256218_g_DemandItem =	   {10014001,10024001,10034001,10044001,10054001,10064001,10074001,10084001,10094001,10104001,10114001,10124001,10234001,10234011,10234021,10234031,10234041,10234051,10254001,10254011,10254021,10254031,10254041,10254051,10274001,10274011,10274021,10274031,10274041,10274051,10244001, 10244011, 10244021,	10244031,	10244041,	10244051,	10264001,	10264011,	10264021,	10264031,	10264041,	10264051,	10204001, 10204011,	10204021,	10204031,	10204041,	10204051}					
x256218_g_BonusMoney1 =0
x256218_g_BonusMoney2 =0
x256218_g_BonusMoney3 =0
x256218_g_BonusMoney4 =0
x256218_g_BonusMoney5 =0
x256218_g_BonusMoney6 =0
x256218_g_BonusItem	=	{}
x256218_g_BonusChoiceItem ={}
x256218_g_ExpBonus = 10200
x256218_g_NpcGUID ={{ guid = 138553, name = "�й���"} }
--MisDescEnd
--**********************************
x256218_g_MaxLevel   = 40

function x256218_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    local level = GetLevel(sceneId, selfId)
	if level < x256218_g_LevelLess or level >= x256218_g_MaxLevel then
		return
	end


	if IsQuestHaveDone(sceneId, selfId, x256218_g_MissionId) > 0 then
		return 
	end
	
	if IsQuestHaveDone(sceneId, selfId, x256218_g_MissionIdPre)> 0 then 
	if IsHaveQuest(sceneId,selfId, x256218_g_MissionId) <= 0 then
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256218_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256218_g_MissionId, state, -1 )
	end
	end

end

function x256218_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256218_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256218_g_ExpBonus )
		end
		if x256218_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256218_g_BonusMoney1 )
		end
		if x256218_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256218_g_BonusMoney2 )
		end
		if x256218_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256218_g_BonusMoney3 )
		end
		if x256218_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256218_g_BonusMoney4 )
		end
		if x256218_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256218_g_BonusMoney5 )
		end
		if x256218_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256218_g_BonusMoney6 )
		end
		for i, item in x256218_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	 	end
		for i, item in x256218_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  	end
end
--**********************************

function x256218_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256218_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256218_g_MissionId) > 0 then
			if x256218_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256218_g_MissionName)
				AddQuestText(sceneId,x256218_g_ContinueInfo)
				EndQuestEvent()
				DispatchQuestEventList(sceneId, selfId, NPCId, x256218_g_ScriptId, x256218_g_MissionId);
			else
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"#Y"..x256218_g_MissionName)
				AddQuestText(sceneId,x256218_g_MissionCompleted)
				AddQuestText(sceneId," ")
				x256218_DispatchMissionInfo( sceneId, selfId, NPCId )
				EndQuestEvent()
				DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256218_g_ScriptId, x256218_g_MissionId);
			end
  elseif x256218_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  		AddQuestText(sceneId,"#Y"..x256218_g_MissionName)
			AddQuestText(sceneId,x256218_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x256218_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256218_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256218_g_MissionHelp )
			end
			x256218_DispatchMissionInfo( sceneId, selfId, NPCId )
	  		EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256218_g_ScriptId, x256218_g_MissionId);
  end
	
end
--**********************************

function x256218_ProcAcceptCheck(sceneId, selfId, NPCId)
		
	return 1
		

end
--**********************************
function x256218_CheckSubmit( sceneId, selfId, NPCId)  
                                                  
		if  IsHaveQuest(sceneId, selfId,x256218_g_MissionId) ~=1 then
			return 0
		end
		
	   	local 	misIndex = GetQuestIndexByID(sceneId, selfId,x256218_g_MissionId)                                                  
	   	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	   		return 1
	   	else 
	   		return 0
	   	end
	   	
	
end

--**********************************
function x256218_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256218_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256218_g_MissionId  )
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
		
		if x256218_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256218_g_MissionId, x256218_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
			  			x256218_Msg2toplayer( sceneId, selfId,0)
						for i, item in x256218_g_DemandItem do
							local equip	=	GetEquipItemCountByLess(sceneId, selfId, 3,0,item)
							local bag	=	GetBagItemCountByLess(sceneId, selfId, 3,0,item)  --0--���� 1--��� 2--��ʯ
							if equip >= 1 or bag >=1 then
								
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256218_g_MissionId)                                                  
			    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
			    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
			    				CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 27,0 )
									CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 28,0 )
									CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 30,0 )
			    				break
							end
						end
					end
	 	end                                                                    
	     
end
--**********************************

function x256218_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256218_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x256218_g_MissionId)
	  x256218_Msg2toplayer( sceneId, selfId,1)
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 27,0 )
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 28,0 )
		CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 30,0 )	
end
--**********************************
function x256218_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256218_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256218_g_BonusChoiceItem do
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
function x256218_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256218_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256218_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256218_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ռ䲻�㣬�������������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256218_g_MissionId) > 0 then
				x256218_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256218_g_MissionId)
				x256218_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256218_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x256218_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x256218_g_MissionIdNext )	
end

function x256218_GetBonus( sceneId, selfId,NpcID)
	  if x256218_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256218_g_ExpBonus);
  	end
		if x256218_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256218_g_BonusMoney1 )
	  end
		if x256218_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256218_g_BonusMoney2 )
	  end
		if x256218_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256218_g_BonusMoney3 )
		end
		if x256218_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256218_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256218_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256218_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256218_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256218_g_BonusMoney6)
		end
end

function x256218_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256218_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256218_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256218_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256218_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256218_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256218_g_MissionName.."��", 0, 3)
				if x256218_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256218_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256218_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256218_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256218_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256218_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256218_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256218_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256218_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256218_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256218_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256218_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256218_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256218_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256218_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256218_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256218_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256218_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256218_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256218_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x256218_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x256218_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x256218_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x256218_g_MissionId, state, -1 )
				if x256218_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 27,1 )
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 28,1 )
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 30,1 )
				 end
		end
end

function x256218_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256218_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256218_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256218_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256218_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256218_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end