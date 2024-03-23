--�ֵ��밮��6/8

--MisDescBegin
x203331_g_ScriptId = 203331
x203331_g_MissionIdPre = 821
x203331_g_MissionId = 823
x203331_g_LevelLess	= 	88 
x203331_g_MissionIdNext = -1
x203331_g_Name	={"������","�������Ǵ�" }
x203331_g_ExtTarget={{type=20,n=1,target="Ȱ��@npc_117009"}}
x203331_g_MissionName="���糡���߷���<��>"
x203331_g_MissionTalk={"�㲢������������Ϊ�У�","���Ǹ��������˵�����ô����","�ζ����������ͳ�ι�����"}
x203331_g_MissionInfo="\t�ҿ��������Ǵ󹫲�������Ը�����Ī˹�ƴ󹫣���������Ŀ�ŵ��ı��Ѻ�Ī˹�ƴ󹫵��˵���ѹ������������ȼ���˳�޵Ļ��棬��������Ȱ����˳�����ʱ����"  --��������
x203331_g_MissionTarget=""		
x203331_g_MissionCompleted="\t�߼��ļ�������������ɵĽ������ĵ��ˣ����Լǵõ���ĵȼ�����Ժ󾭳�����ѧϰ�µļ��ܡ�\n\t�˲���һ�ڳԳ����ӣ�������ȴ��һ��һ�ڳԳ����ġ���֮�Ժ����ϰ�����ܳ�Ϊһ����ʦ��"
x203331_g_ContinueInfo={"\t������������\n\t���ǵ����鲻���������ܣ� ",
												"\t�ң��ң���˵��û��������������̫���������ﻹ��һ�����˺ʹ󹫵����ϣ���\n\tĪ˹�ƴ���֪�������úͻ����󹫵Ĺ��ҹ�ϵ��Ҫ�������ü޸��ң�",
												"\t�ã��ҵ��������Ҳ�ܾ��ˣ�����������ұ���ѩ�޵�ʱ���ˣ� "}
x203331_g_MissionHelp =	""
x203331_g_DemandItem ={}
x203331_g_ExpBonus = 684000
x203331_g_BonusMoney1 =880
x203331_g_BonusMoney2 =0
x203331_g_BonusMoney3 =0
x203331_g_BonusMoney4 =0
x203331_g_BonusMoney5 =106
x203331_g_BonusMoney6 =0
x203331_g_BonusItem	=	{}
x203331_g_BonusChoiceItem ={}
x203331_g_NpcGUID = {{ guid = 117009, name = "�������Ǵ�"} }
--MisDescEnd
--**********************************

function x203331_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x203331_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203331_g_MissionIdPre) > 0 then
				if IsHaveQuest(sceneId,selfId, x203331_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203331_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203331_g_MissionId, state, -1 )
				end
	end
end

function x203331_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203331_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203331_g_ExpBonus )
		end
		if x203331_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203331_g_BonusMoney1 )
		end
		if x203331_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203331_g_BonusMoney2 )
		end
		if x203331_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203331_g_BonusMoney3 )
		end
		if x203331_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203331_g_BonusMoney4 )
		end
		if x203331_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203331_g_BonusMoney5 )
		end
		if x203331_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203331_g_BonusMoney6 )
		end
		for i, item in x203331_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x203331_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--������ں���

--**********************************

function x203331_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x203331_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203331_g_MissionId) > 0 then
			if x203331_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which == -1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203331_g_MissionName)
						AddQuestText(sceneId,x203331_g_ContinueInfo[1])
						AddQuestNumText(sceneId, MissionId, x203331_g_MissionTalk[1],0,0)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203331_g_ScriptId, x203331_g_MissionId);
					elseif which ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203331_g_MissionName)
						AddQuestText(sceneId,x203331_g_ContinueInfo[2])
						AddQuestNumText(sceneId, MissionId, x203331_g_MissionTalk[2],1,1)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x203331_g_ScriptId, x203331_g_MissionId);
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203331_g_MissionId)  
						SetQuestByIndex(sceneId,selfId,misIndex,1,1)                                                
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203331_g_MissionName)
						AddQuestText(sceneId,x203331_g_ContinueInfo[3])
						AddQuestText(sceneId," ")
						x203331_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203331_g_ScriptId, x203331_g_MissionId);
			end
  elseif x203331_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203331_g_MissionName)
			AddQuestText(sceneId,x203331_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x203331_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203331_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203331_g_MissionHelp )
			end
			x203331_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203331_g_ScriptId, x203331_g_MissionId);
  end
end
--**********************************
function x203331_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203331_g_MissionId) > 0 then
		return 0
	elseif IsQuestHaveDone(sceneId, selfId, x203331_g_MissionIdPre) <= 0 then
		return 0
	end
	return 1
end
--**********************************
function x203331_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203331_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,1) == 1 then
	        return 1
	end
	return 0
end
--**********************************
function x203331_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203331_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203331_g_MissionId  )
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
		
		if x203331_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203331_g_MissionId, x203331_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203331_Msg2toplayer( sceneId, selfId,0)
						--if x203331_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203331_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x203331_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203331_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203331_g_MissionId)
	  x203331_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x203331_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203331_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x203331_g_BonusChoiceItem do
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
function x203331_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203331_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203331_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203331_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203331_g_MissionId) > 0 then
				x203331_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203331_g_MissionId)
				x203331_GetBonus( sceneId, selfId,NPCId)
				--CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203331_g_MissionIdNext )	
   end
end

function x203331_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203331_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203331_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203331_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203331_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203331_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203331_g_MissionName.."��", 0, 3)
				if x203331_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203331_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x203331_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203331_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x203331_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x203331_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x203331_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x203331_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x203331_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x203331_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x203331_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203331_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x203331_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x203331_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x203331_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x203331_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203331_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203331_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203331_g_MissionId, 7, -1 )
		end
end

function x203331_GetBonus( sceneId, selfId,NpcID)
	  if x203331_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203331_g_ExpBonus);
  	end
		if x203331_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203331_g_BonusMoney1 )
	  end
		if x203331_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203331_g_BonusMoney2 )
	  end
		if x203331_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203331_g_BonusMoney3 )
		end
		if x203331_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203331_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203331_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203331_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203331_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203331_g_BonusMoney6)
		end
end

--**********************************

function x203331_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end
--**********************************
function x203331_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203331_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203331_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203331_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203331_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203331_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203331_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203331_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203331_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203331_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





