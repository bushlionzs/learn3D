--�����֡��ҵ���¹����

--MisDescBegin
x203644_g_ScriptId = 203644
x203644_g_MissionIdPre ={3303,3329,3330,3331,3332,3333,3334,3335,3336,3337,3338,3339}
x203644_g_MissionId = {3305,3353,3354,3355,3356,3357,3358,3359,3360,3361,3362,3363}
x203644_g_LevelLess	= 	1
x203644_g_MissionIdNext = 3308
x203644_g_Name	={}
x203644_g_ExtTarget={{type=20,n=1,target="�ҵ�@npc_128016"}}
x203644_g_MissionName="�����֡���¹����"
x203644_g_MissionInfo="\t����±���֮�󣬼ǵð��¡�B�����򿪱������Ҽ������ոջ�õ��������Ϳ���װ�����������ˡ�\n\t��¹�������ڶ������ȴ�����ĵ�����"  --��������
x203644_g_MissionTarget="�ҵ�@npc_128016"		
x203644_g_MissionCompleted="\t��û�뵽����ô������ˣ�\n\t��������ǰ����λ��������õ��˲����ջ񰡡� "					--�������npc˵���Ļ�
x203644_g_ContinueInfo=""
x203644_g_MissionHelp =	"#G���¡�B�����򿪱������Ҽ�����Ϳ���װ����ոջ�õ�������#W"
x203644_g_DemandItem ={}
x203644_g_ExpBonus = 163
x203644_g_BonusMoney1 =5
x203644_g_BonusMoney2 =0
x203644_g_BonusMoney3 =0
x203644_g_BonusMoney4 =0
x203644_g_BonusMoney5 =12
x203644_g_BonusMoney6 =0
x203644_g_BonusItem	=	{}
x203644_g_BonusChoiceItem ={}
x203644_g_NpcGUID ={{ guid = 128016, name = "��¹����"} }
--MisDescEnd     
--x203644_g_ScriptIdNext ={203402,203403,203404,203405,203406,203407}
--**********************************

function x203644_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	local zhiye = GetZhiye( sceneId, selfId)+1
	if IsQuestHaveDone(sceneId, selfId, x203644_g_MissionId[zhiye]) > 0 then
		return 
	end
	local zhiye =GetZhiye( sceneId, selfId)+1
	if IsQuestHaveDone(sceneId, selfId, x203644_g_MissionIdPre[zhiye])> 0 then
		
			if IsHaveQuest(sceneId,selfId, x203644_g_MissionId[zhiye]) <= 0 then						
				local state = GetQuestStateNM(sceneId,selfId,NPCId,x203644_g_MissionId[zhiye])
				AddQuestTextNM( sceneId, selfId, NPCId, x203644_g_MissionId[zhiye], state, -1 )
				 --CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,1 ) 		
			end
	end
		
end

function x203644_DispatchMissionInfo( sceneId, selfId, NPCId )
		local zhiye = GetZhiye( sceneId, selfId)+1
		if x203644_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203644_g_ExpBonus )
		end
		if x203644_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203644_g_BonusMoney1 )
		end
		if x203644_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203644_g_BonusMoney2 )
		end
		if x203644_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203644_g_BonusMoney3 )
		end
		if x203644_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203644_g_BonusMoney4 )
		end
		if x203644_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203644_g_BonusMoney5 )
		end
		if x203644_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203644_g_BonusMoney6 )
		end
		for i, item in x203644_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x203644_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x203644_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	local zhiye = GetZhiye( sceneId, selfId)+1
	if IsQuestHaveDone(sceneId, selfId, x203644_g_MissionId[zhiye]) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203644_g_MissionId[zhiye]) > 0 then
			if x203644_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203644_g_MissionName)
						AddQuestText(sceneId,x203644_g_MissionCompleted)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203644_g_ScriptId, x203644_g_MissionId[zhiye]);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203644_g_MissionName)
						AddQuestText(sceneId,x203644_g_MissionCompleted)
						AddQuestText(sceneId," ")
						--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1 )  
						x203644_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )  
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203644_g_ScriptId, x203644_g_MissionId[zhiye]);
			end
  elseif x203644_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203644_g_MissionName)
			AddQuestText(sceneId,x203644_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺") 		  
			for i, item in x203644_g_ExtTarget do  	
			AddQuestText( sceneId,item.target)		
			end 
			if x203644_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203644_g_MissionHelp )
			end
			x203644_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203644_g_ScriptId, x203644_g_MissionId[zhiye]);
			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,0 )
			--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 ) 	
  end
	
end
--**********************************

function x203644_ProcAcceptCheck(sceneId, selfId, NPCId)
		
						return 1
		

end
--**********************************
function x203644_CheckSubmit( sceneId, selfId, NPCId)

	        return 1
	
end
--**********************************
function x203644_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		local zhiye = GetZhiye( sceneId, selfId)+1
		if IsQuestHaveDone(sceneId, selfId, x203644_g_MissionId[zhiye]) > 0 then
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
	--	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203644_g_MissionId[zhiye]  )
	--	if FrontMissiontId1 ~= -1 then
	--		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
	--			return 0
	--		end
	--	end
	--	if FrontMissiontId2 ~= -1 then
	--		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
	--			return 0
	--		end
	--	end
	--	if FrontMissiontId3 ~= -1 then
	--		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
	--			return 0
	--		end
	--	end
		if x203644_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203644_g_MissionId[zhiye], x203644_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then                                          ------����ʧ�� ==0 ��1 �ɹ�                                                                  
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203644_Msg2toplayer( sceneId, selfId,0)
						--if x203644_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203644_g_MissionId[zhiye])       ---- ȡ������״̬                                               
	    					SetQuestByIndex(sceneId,selfId,misIndex,0,1)                                 ---0��1 ���� 0/1
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)                                 ---7,1  ������״̬��Ϊ���
	    					--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )   
	    					--CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 )   
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x203644_ProcQuestAbandon(sceneId, selfId, MissionId)
		local zhiye = GetZhiye( sceneId, selfId)+1
		if IsHaveQuest(sceneId,selfId, x203644_g_MissionId[zhiye]) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203644_g_MissionId[zhiye])
	  x203644_Msg2toplayer( sceneId, selfId,1) 
			
end
--**********************************
function x203644_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local zhiye = GetZhiye( sceneId, selfId)+1
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ�������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203644_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x203644_g_BonusChoiceItem do
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
function x203644_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	local zhiye = GetZhiye( sceneId, selfId)+1
	if IsHaveQuest(sceneId,selfId, x203644_g_MissionId[zhiye]) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203644_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203644_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203644_g_MissionId[zhiye]) > 0 then
				x203644_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203644_g_MissionId[zhiye])
				QuestCom(sceneId, selfId, 3307)
				x203644_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x203644_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x203644_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   local zhiye =GetZhiye( sceneId, selfId)+1
   CallScriptFunction( 203639, "ProcEventEntry", sceneId, selfId, NPCId, x203644_g_MissionIdNext )	
end

function x203644_GetBonus( sceneId, selfId,NpcID)
		local zhiye = GetZhiye( sceneId, selfId)+1
	  if x203644_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203644_g_ExpBonus);
  	end
		if x203644_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203644_g_BonusMoney1 )
	  end
		if x203644_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203644_g_BonusMoney2 )
	  end
		if x203644_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203644_g_BonusMoney3 )
		end
		if x203644_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203644_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203644_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203644_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203644_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203644_g_BonusMoney6)
		end
end

function x203644_Msg2toplayer( sceneId, selfId,type)
		local zhiye = GetZhiye( sceneId, selfId)+1
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203644_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203644_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203644_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203644_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203644_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203644_g_MissionName.."��", 0, 3)
				if x203644_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203644_g_ExpBonus.."#cffcf00�Ľ���", 0, 2)
  			end
				if x203644_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203644_g_BonusMoney1.."��#cffcf00�Ľ���", 0, 2)
	  		end
				if x203644_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203644_g_BonusMoney2.."��#cffcf00�Ľ���", 0, 2)
	  		end
				if x203644_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00���#G��"..x203644_g_BonusMoney3.."��#cffcf00�Ľ���", 0, 2)
				end
				if x203644_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G��͢����ֵ"..x203644_g_BonusMoney4.."#cffcf00�Ľ���", 0, 2)
				end
				if x203644_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203644_g_BonusMoney5.."#cffcf00�Ľ���", 0, 2)
				end
				if x203644_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203644_g_BonusMoney6.."#cffcf00�Ľ���", 0, 2)
				end
		end
end

function x203644_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x203644_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203644_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203644_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203644_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203644_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
		local zhiye = GetZhiye( sceneId, selfId)+1
	  local bFind  = 0
    for i ,item in x203644_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203644_g_MissionId[zhiye]) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203644_g_MissionId[zhiye])        ---ȡ������״̬ ������״̬���Ӱ�ť AddQuestTextNM
				AddQuestTextNM( sceneId, selfId, npcId, x203644_g_MissionId[zhiye], state, -1 )
		end
end

function x203644_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203644_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203644_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203644_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203644_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203644_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end