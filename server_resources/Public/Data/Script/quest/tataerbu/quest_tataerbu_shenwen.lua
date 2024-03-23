--�ֵ��밮��6/8

--MisDescBegin
x223002_g_ScriptId = 223002
x223002_g_MissionIdPre =109
x223002_g_MissionId = 110
x223002_g_LevelLess	= 	20 
x223002_g_MissionIdNext = 111
x223002_g_Name	={"����","�����²" }
x223002_g_ExtTarget={{type=20,n=1,target="����@npc_103016"}}
x223002_g_MissionName="���糡������"
x223002_g_MissionTalk={"˵������ʲô���㣡","˵����ʵ����","˵����ʵ����"}
x223002_g_MissionInfo="\t����ץ�˸�����ķ�²��һ����С�Ӿ��Ǹ����ͷ���ɺ����ǲ��������Ļ�������Һú�������������"  --��������
x223002_g_MissionTarget=""		
x223002_g_MissionCompleted="\t�߼��ļ�������������ɵĽ������ĵ��ˣ����Լǵõ���ĵȼ�����Ժ󾭳�����ѧϰ�µļ��ܡ�\n\t�˲���һ�ڳԳ����ӣ�������ȴ��һ��һ�ڳԳ����ġ���֮�Ժ����ϰ�����ܳ�Ϊһ����ʦ��"
x223002_g_ContinueInfo={"\t��ɱ�ҡ��� ��ɱ�ҡ��� ��ʲô��˵�� ",
												"\t��ʵ��������������Ѿ������ˣ������ǵĽ���Ү�ɻ�˵���������պ��ң������� ������ ��Ϊ��ľ��̫ǿ���˶Խ��������������������������ǽ��ˣ�������ȫ������֮ʱ�����Ǵ�����ɱ����ֱ����ľ���Ӫ��",
												"\tС�ġ��� С��˵�Ķ���ʵ����Ҫ���а����٣����������\n\t�����㣬��ɱ�ң�����һ����С�Ĳ�����һ��СС��Уξ��Ҳ�Ƿ������£������޹ذ����� "}
x223002_g_MissionHelp =	""
x223002_g_DemandItem ={}
x223002_g_ExpBonus = 9340
x223002_g_BonusMoney1 =258
x223002_g_BonusMoney2 =0
x223002_g_BonusMoney3 =0
x223002_g_BonusMoney4 =0
x223002_g_BonusMoney5 =37
x223002_g_BonusMoney6 =0
x223002_g_BonusItem	=	{{item = 11000200,n=5}}
x223002_g_BonusChoiceItem ={}
x223002_g_NpcGUID = {{ guid = 103016, name = "�����²"} }
--MisDescEnd
--**********************************

function x223002_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	if IsQuestHaveDone(sceneId, selfId, x223002_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x223002_g_MissionIdPre) > 0 then
				if IsHaveQuest(sceneId,selfId, x223002_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x223002_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x223002_g_MissionId, state, -1 )
				end
	end
end

function x223002_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x223002_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x223002_g_ExpBonus )
		end
		if x223002_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x223002_g_BonusMoney1 )
		end
		if x223002_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x223002_g_BonusMoney2 )
		end
		if x223002_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x223002_g_BonusMoney3 )
		end
		if x223002_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x223002_g_BonusMoney4 )
		end
		if x223002_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x223002_g_BonusMoney5 )
		end
		if x223002_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x223002_g_BonusMoney6 )
		end
		for i, item in x223002_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x223002_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--������ں���

--**********************************

function x223002_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x223002_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x223002_g_MissionId) > 0 then
			if x223002_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which == -1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x223002_g_MissionName)
						AddQuestText(sceneId,x223002_g_ContinueInfo[1])
						AddQuestNumText(sceneId, MissionId, x223002_g_MissionTalk[1],0,0)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x223002_g_ScriptId, x223002_g_MissionId);
					elseif which ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x223002_g_MissionName)
						AddQuestText(sceneId,x223002_g_ContinueInfo[2])
						AddQuestNumText(sceneId, MissionId, x223002_g_MissionTalk[2],1,1)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x223002_g_ScriptId, x223002_g_MissionId);
						local misIndex = GetQuestIndexByID(sceneId,selfId,x223002_g_MissionId)  
						SetQuestByIndex(sceneId,selfId,misIndex,1,1)                                                
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x223002_g_MissionName)
						AddQuestText(sceneId,x223002_g_ContinueInfo[3])
						AddQuestText(sceneId," ")
						x223002_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x223002_g_ScriptId, x223002_g_MissionId);
			end
  elseif x223002_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x223002_g_MissionName)
			AddQuestText(sceneId,x223002_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x223002_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x223002_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x223002_g_MissionHelp )
			end
			x223002_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x223002_g_ScriptId, x223002_g_MissionId);
  end
end
--**********************************
function x223002_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x223002_g_MissionId) > 0 then
		return 0
	elseif IsQuestHaveDone(sceneId, selfId, x223002_g_MissionIdPre) <= 0 then
		return 0
	end
	return 1
end
--**********************************
function x223002_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x223002_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,1) == 1 then
	        return 1
	end
	return 0
end
--**********************************
function x223002_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x223002_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x223002_g_MissionId  )
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
		
		if x223002_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x223002_g_MissionId, x223002_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x223002_Msg2toplayer( sceneId, selfId,0)
						--if x223002_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x223002_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x223002_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x223002_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x223002_g_MissionId)
	  x223002_Msg2toplayer( sceneId, selfId,1)
end
--**********************************
function x223002_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x223002_g_BonusItem do
		AddBindItem( sceneId, item.item, item.n )
  end
  for j, item in x223002_g_BonusChoiceItem do
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
function x223002_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x223002_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x223002_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x223002_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x223002_g_MissionId) > 0 then
				x223002_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x223002_g_MissionId)
				x223002_GetBonus( sceneId, selfId,NPCId)
				--CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x223002_g_MissionIdNext )	
				BeginAddItem(sceneId)
				for i, item in x223002_g_BonusItem do
 						AddBindItem( sceneId, item.item, item.n )
				end
				for i, item in x223002_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    			end
    			EndAddItem(sceneId,selfId)
    			AddItemListToPlayer(sceneId,selfId)
   end
end

function x223002_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x223002_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x223002_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x223002_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x223002_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x223002_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x223002_g_MissionName.."��", 0, 3)
				if x223002_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x223002_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x223002_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x223002_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x223002_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x223002_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x223002_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x223002_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x223002_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x223002_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x223002_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x223002_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x223002_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x223002_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x223002_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x223002_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x223002_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x223002_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x223002_g_MissionId, 7, -1 )
		end
end

function x223002_GetBonus( sceneId, selfId,NpcID)
	  if x223002_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x223002_g_ExpBonus);
  	end
		if x223002_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x223002_g_BonusMoney1 )
	  end
		if x223002_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x223002_g_BonusMoney2 )
	  end
		if x223002_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x223002_g_BonusMoney3 )
		end
		if x223002_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x223002_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x223002_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x223002_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x223002_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x223002_g_BonusMoney6)
		end
end

--**********************************

function x223002_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end
--**********************************
function x223002_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x223002_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x223002_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x223002_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x223002_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x223002_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x223002_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x223002_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x223002_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x223002_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end





