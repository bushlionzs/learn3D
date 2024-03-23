--��������

--MisDescBegin
x203500_g_ScriptId = 203500
--x203500_g_MissionIdPre =2704
x203500_g_MissionId = 3200
x203500_g_LevelLess	= 	1 
x203500_g_MissionIdNext = {3217,3218,3219,3220,3221,3222,3223,3224,3225,3226,3227,3228}
x203500_g_Name	={}
x203500_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_125000"}}
x203500_g_MissionName="�����֡�������"
x203500_g_MissionInfo="\t��ӭ�����ɼ�˼�������磡�������Ķ�һ�£�#r��#r\tͨ���������#G���#W����������#G����#W�������Ϸ�е�������Ժ���#G��̸#W��#r\t#W����������NPCͷ����#Y��ɫ���ʺ�#W��#Y��#W����������ʹ�������������#G�������#W��#r��#r\t���ڣ��������Ե�#G��ӥ����#Wͷ���Ľ�ɫ�ʺš�#Y��#W���������Ѿ��Ⱥ�������ˣ�����̸̸�ɡ�"  --��������
x203500_g_MissionTarget=""		
x203500_g_MissionCompleted="\t#Y@myname#W,��ӭ�㣡\n\t���ź����������ҵ��������ң�ս���Ѿ����ӵ���һ������͵�¥��������\n\t���գ���Ԫ�ʵۺ����ұ�����ּ��¥��������ʼ������\n\t����¥����������ʿ�������Լ���¥������Ծ����ޣ�������ҵ��"					--�������npc˵���Ļ�
x203500_g_ContinueInfo=""
x203500_g_MissionHelp =	"�����������#R���#G�����ӥ���ϣ������Ի��������Ե�������ϵ�#RQ#G�����������б�ѡ����Ҫ��ɵ����񣬵��#R����Ŀ��#G�е���ɫ�����������Զ�Ѱ·��"
x203500_g_DemandItem ={}
x203500_g_ExpBonus = 23
x203500_g_BonusMoney1 =6
x203500_g_BonusMoney2 =0
x203500_g_BonusMoney3 =0
x203500_g_BonusMoney4 =0
x203500_g_BonusMoney5 =12
x203500_g_BonusMoney6 =0
x203500_g_BonusItem	=	{}
x203500_g_BonusChoiceItem ={}
x203500_g_NpcGUID = {}
--MisDescEnd
x203500_g_ScriptIdNext ={203515,203516,203517,203518,203519,203520,203521,203522,203523,203524,203525,203526}
--**********************************

function x203500_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	local level = GetLevel( sceneId, selfId)
    CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x203500_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203500_g_MissionId) <= 0 then
		if level >20 then
			return 
		end		
	end
	local state = GetQuestStateNM(sceneId,selfId,NPCId,x203500_g_MissionId)
	AddQuestTextNM( sceneId, selfId, NPCId, x203500_g_MissionId, state, -1 )
	CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 2,1 ) -- �ڶ��� 1 �򿪽��� 0 �رս��� ? 
end

function x203500_DispatchMissionInfo( sceneId, selfId, NPCId )
	if x203500_g_ExpBonus> 0 then
		AddQuestExpBonus(sceneId, x203500_g_ExpBonus )
	end
	if x203500_g_BonusMoney1 > 0 then
		AddQuestMoneyBonus1(sceneId, x203500_g_BonusMoney1 )
	end
	if x203500_g_BonusMoney2 > 0 then
		AddQuestMoneyBonus2(sceneId, x203500_g_BonusMoney2 )
	end
	if x203500_g_BonusMoney3 > 0 then
		AddQuestMoneyBonus3(sceneId, x203500_g_BonusMoney3 )
	end
	if x203500_g_BonusMoney4 > 0 then
		AddQuestMoneyBonus4(sceneId, x203500_g_BonusMoney4 )
	end
	if x203500_g_BonusMoney5 > 0 then
		AddQuestMoneyBonus5(sceneId, x203500_g_BonusMoney5 )
	end
	if x203500_g_BonusMoney6 > 0 then
		AddQuestMoneyBonus6(sceneId, x203500_g_BonusMoney6 )
	end
	for i, item in pairs(x203500_g_BonusItem) do
		AddQuestItemBonus(sceneId, item.item, item.n)
	end
	for i, item in pairs(x203500_g_BonusChoiceItem) do
		AddQuestRadioItemBonus(sceneId, item.item, item.n)
	end
end
--**********************************

function x203500_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203500_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203500_g_MissionId) > 0 then
			if x203500_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203500_g_MissionName)
						AddQuestText(sceneId,x203500_g_MissionCompleted)
						EndQuestEvent()
						
						DispatchQuestEventList(sceneId, selfId, NPCId, x203500_g_ScriptId, x203500_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203500_g_MissionName)
						AddQuestText(sceneId,x203500_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203500_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 2,0 ) -- �ڶ��� 1 �򿪽��� 0 �رս���  
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1 ) -- �ڶ��� 1 �򿪽��� 0 �رս���  
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203500_g_ScriptId, x203500_g_MissionId);
			end
  elseif x203500_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203500_g_MissionName)
			AddQuestText(sceneId,x203500_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")  
			for i, item in pairs(x203500_g_ExtTarget) do
					AddQuestText( sceneId,item.target)
			end 
			if x203500_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203500_g_MissionHelp )
			end
			x203500_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203500_g_ScriptId, x203500_g_MissionId);
  end
	
end
--**********************************

function x203500_ProcAcceptCheck(sceneId, selfId, NPCId)

					return 1

end
--**********************************
function x203500_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203500_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203500_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203500_g_MissionId  )
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
		
		
		if x203500_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203500_g_MissionId, x203500_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203500_Msg2toplayer( sceneId, selfId,0)
						if x203500_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203500_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203500_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203500_g_MissionId) > 0 then
				return 
		end
	  	BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"���޷�����������") 
			EndQuestEvent()
			DispatchQuestTips(sceneId, selfId)
			
end
--**********************************
function x203500_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in pairs(x203500_g_BonusItem) do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in pairs(x203500_g_BonusChoiceItem) do
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
function x203500_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203500_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203500_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203500_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203500_g_MissionId) > 0 then
				x203500_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203500_g_MissionId)
				x203500_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in pairs(x203500_g_BonusItem) do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in pairs(x203500_g_BonusChoiceItem) do
					if item.item == selectRadioId then
	    			AddItem( sceneId, item.item, item.n )
				end
    	end
    		EndAddItem(sceneId,selfId)
   end
  local zhiye =GetZhiye( sceneId, selfId)+1
   CallScriptFunction( x203500_g_ScriptIdNext[zhiye], "ProcEventEntry", sceneId, selfId, NPCId, x203500_g_MissionIdNext[zhiye] )	
end

function x203500_GetBonus( sceneId, selfId,NpcID)
	  if x203500_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203500_g_ExpBonus);
  	end
		if x203500_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203500_g_BonusMoney1 )
	  end
		if x203500_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203500_g_BonusMoney2 )
	  end
		if x203500_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203500_g_BonusMoney3 )
		end
		if x203500_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203500_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203500_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203500_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203500_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203500_g_BonusMoney6)
		end
end

function x203500_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203500_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203500_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203500_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203500_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203500_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203500_g_MissionName.."��", 0, 3)
				if x203500_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203500_g_ExpBonus.."#cffcf00�Ľ���", 0, 2)
  			end
				if x203500_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203500_g_BonusMoney1.."��#cffcf00�Ľ���", 0, 2)
	  		end
				if x203500_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203500_g_BonusMoney2.."��#cffcf00�Ľ���", 0, 2)
	  		end
				if x203500_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00���#G��"..x203500_g_BonusMoney3.."��#cffcf00�Ľ���", 0, 2)
				end
				if x203500_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G��͢����ֵ"..x203500_g_BonusMoney4.."#cffcf00�Ľ���", 0, 2)
				end
				if x203500_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203500_g_BonusMoney5.."#cffcf00�Ľ���", 0, 2)
				end
				if x203500_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203500_g_BonusMoney6.."#cffcf00�Ľ���", 0, 2)
				end
		end
end

function x203500_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203500_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203500_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203500_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203500_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203500_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x203500_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203500_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203500_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203500_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203500_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203500_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end