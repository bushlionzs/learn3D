--��������

--MisDescBegin
x256009_g_ScriptId = 256009
--x256009_g_MissionIdPre =2704
x256009_g_MissionId = 3000
x256009_g_LevelLess	= 	1 
x256009_g_MissionIdNext = 3001
x256009_g_Name	={}
x256009_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_138023"}}
x256009_g_MissionName="�����֡�ʹ�ŵ�ż��"
x256009_g_MissionInfo="\t��ӭ�����ɼ�˼�������磬��ʿ#Y@myname#W��\n\t������ɽ����֮ǰ����ȥ������ߵĹ���ǫ̸һ̸��"  --��������
x256009_g_MissionTarget=""		
x256009_g_MissionCompleted="\t#Y@myname#W������ĸպã�������Щ��Ҫ������Ҫ�����㡣"					--�������npc˵���Ļ�
x256009_g_ContinueInfo=""
x256009_g_MissionHelp =	"�����������#R���#G�������ǫ�������Ի��������Ե�������ϵ�#RQ#G�����������б�ѡ����Ҫ��ɵ����񣬵��#R����Ŀ��#G�е���ɫ�����������Զ�Ѱ·��"
x256009_g_DemandItem ={}
x256009_g_BonusMoney1 =99999999
x256009_g_BonusMoney2 =99999999
x256009_g_BonusMoney3 =99999999
x256009_g_BonusMoney4 =99999999
x256009_g_BonusMoney5 =99999999
x256009_g_BonusMoney6 =99999999
x256009_g_BonusItem	=	{}
x256009_g_BonusChoiceItem ={}
x256009_g_ExpBonus = 5
x256009_g_NpcGUID = {}
--MisDescEnd
--**********************************

function x256009_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x256009_g_MissionId) > 0 then
		return 
	end
		local state = GetQuestStateNM(sceneId,selfId,NPCId,x256009_g_MissionId)
		AddQuestTextNM( sceneId, selfId, NPCId, x256009_g_MissionId, state, -1 )
	  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 2,1 ) -- �ڶ��� 1 �򿪽��� 0 �رս��� ? 
end

function x256009_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x256009_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x256009_g_ExpBonus )
		end
		if x256009_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x256009_g_BonusMoney1 )
		end
		if x256009_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x256009_g_BonusMoney2 )
		end
		if x256009_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x256009_g_BonusMoney3 )
		end
		if x256009_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x256009_g_BonusMoney4 )
		end
		if x256009_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x256009_g_BonusMoney5 )
		end
		if x256009_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x256009_g_BonusMoney6 )
		end
		for i, item in x256009_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x256009_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x256009_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x256009_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x256009_g_MissionId) > 0 then
			if x256009_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256009_g_MissionName)
						AddQuestText(sceneId,x256009_g_MissionCompleted)
						EndQuestEvent()
						
						DispatchQuestEventList(sceneId, selfId, NPCId, x256009_g_ScriptId, x256009_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x256009_g_MissionName)
						AddQuestText(sceneId,x256009_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x256009_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 2,0 ) -- �ڶ��� 1 �򿪽��� 0 �رս���  
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1 ) -- �ڶ��� 1 �򿪽��� 0 �رս���  
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x256009_g_ScriptId, x256009_g_MissionId);
			end
  elseif x256009_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x256009_g_MissionName)
			AddQuestText(sceneId,x256009_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")  
			for i, item in x256009_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x256009_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x256009_g_MissionHelp )
			end
			x256009_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x256009_g_ScriptId, x256009_g_MissionId);
  end
	
end
--**********************************

function x256009_ProcAcceptCheck(sceneId, selfId, NPCId)

					return 1

end
--**********************************
function x256009_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x256009_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x256009_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x256009_g_MissionId  )
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
		
		
		if x256009_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x256009_g_MissionId, x256009_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x256009_Msg2toplayer( sceneId, selfId,0)
						if x256009_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x256009_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x256009_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x256009_g_MissionId) > 0 then
				return 
		end
	  	BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"���޷�����������") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			
end
--**********************************
function x256009_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x256009_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x256009_g_BonusChoiceItem do
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
function x256009_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x256009_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256009_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x256009_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x256009_g_MissionId) > 0 then
				x256009_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x256009_g_MissionId)
				x256009_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x256009_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x256009_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
   end
   CallScriptFunction(203419, "ProcEventEntry", sceneId, selfId, NPCId, x256009_g_MissionIdNext )	
end

function x256009_GetBonus( sceneId, selfId,NpcID)
	  if x256009_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x256009_g_ExpBonus);
  	end
		if x256009_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x256009_g_BonusMoney1 )
	  end
		if x256009_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x256009_g_BonusMoney2 )
	  end
		if x256009_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x256009_g_BonusMoney3 )
		end
		if x256009_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x256009_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x256009_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x256009_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x256009_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x256009_g_BonusMoney6)
		end
end

function x256009_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x256009_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x256009_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x256009_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x256009_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x256009_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x256009_g_MissionName.."��", 0, 3)
				if x256009_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256009_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x256009_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256009_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x256009_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x256009_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x256009_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x256009_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x256009_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x256009_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x256009_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256009_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x256009_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x256009_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x256009_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x256009_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x256009_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x256009_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x256009_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x256009_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x256009_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x256009_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x256009_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x256009_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x256009_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x256009_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end