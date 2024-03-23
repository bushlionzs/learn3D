--�����ߡ���ǽ֮��<��>

--MisDescBegin
x270013_g_ScriptId = 270013
x270013_g_MissionIdPre =3591
x270013_g_MissionId = 3592
x270013_g_LevelLess	= 	55 
x270013_g_MissionIdNext = 3593
x270013_g_Name	={}
x270013_g_ExtTarget={{type=20,n=3,target="��Ժ��@npc_143175���ҳ����Ƶ�ɣ�粢ɱ������"}}
x270013_g_MissionName="�����ߡ���ǽ֮��<��>"
x270013_g_MissionInfo="\t��ɣ����������۾��������˵��\n\t�Ҳ�֪������ô˵����£�������ߵ�һ��Ժ�ӣ���������������ġ��ҡ���������Զ��ʧ����ס����Ҫ���ɣ�������ȫ����ʧ��"  --��������
x270013_g_MissionTarget=""		
x270013_g_MissionCompleted="\t������ܿ�س���ɣ��ܲ���Ŀ����㣩\n\t�㣬��ѡ����ǡ�ȫ�������ˣ���"					--�������npc˵���Ļ�
x270013_g_ContinueInfo="\t���͹��£����͹��£�"
x270013_g_MissionHelp =	""
x270013_g_DemandItem ={}
x270013_g_BonusMoney1 =376
x270013_g_BonusMoney2 =0
x270013_g_BonusMoney3 =0
x270013_g_BonusMoney4 =0
x270013_g_BonusMoney5 =66
x270013_g_BonusMoney6 =0
x270013_g_BonusItem	=	{}
x270013_g_BonusChoiceItem ={}
x270013_g_ExpBonus = 171000
x270013_g_GroupPoint	={ {type=10,id =18,target = "��ɣ��"} }
--MisDescEnd
--**********************************

function x270013_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270013_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270013_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270013_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270013_g_MissionId, state, -1 )
	end
end

function x270013_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270013_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270013_g_ExpBonus )
		end
		if x270013_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270013_g_BonusMoney1 )
		end
		if x270013_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270013_g_BonusMoney2 )
		end
		if x270013_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270013_g_BonusMoney3 )
		end
		if x270013_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270013_g_BonusMoney4 )
		end
		if x270013_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270013_g_BonusMoney5 )
		end
		if x270013_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270013_g_BonusMoney6 )
		end
		for i, item in x270013_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270013_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270013_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270013_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270013_g_MissionId) > 0 then
			if x270013_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270013_g_MissionName)
						AddQuestText(sceneId,x270013_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270013_g_ScriptId, x270013_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270013_g_MissionName)
						AddQuestText(sceneId,x270013_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270013_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270013_g_ScriptId, x270013_g_MissionId);
			end
  elseif x270013_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270013_g_MissionName)
			AddQuestText(sceneId,x270013_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270013_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270013_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270013_g_MissionHelp )
			end
			x270013_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270013_g_ScriptId, x270013_g_MissionId);
  end
	
end
--**********************************

function x270013_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270013_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270013_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270013_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) >=3 then 
			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	        return 1
	  end
	  return 0
	
end
--**********************************
function x270013_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270013_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270013_g_MissionId  )
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
		if x270013_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270013_g_MissionId, x270013_g_ScriptId, 1, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270013_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270013_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270013_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270013_g_MissionId)
	  x270013_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x270013_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270013_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270013_g_BonusChoiceItem do
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
function x270013_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270013_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270013_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270013_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270013_g_MissionId) > 0 then
				x270013_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270013_g_MissionId)
				x270013_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270013_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270013_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270013_g_MissionIdNext )	
end

function x270013_GetBonus( sceneId, selfId,NpcID)
	  if x270013_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270013_g_ExpBonus);
  	end
		if x270013_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270013_g_BonusMoney1 )
	  end
		if x270013_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270013_g_BonusMoney2 )
	  end
		if x270013_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270013_g_BonusMoney3 )
		end
		if x270013_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270013_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270013_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270013_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270013_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270013_g_BonusMoney6)
		end
end

function x270013_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270013_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270013_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270013_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270013_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270013_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270013_g_MissionName.."��", 0, 3)
				if x270013_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270013_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270013_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270013_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270013_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270013_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270013_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270013_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270013_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270013_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270013_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270013_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270013_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270013_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270013_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
	if	objdataId ==3900 then
	 local KilledNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, KilledNum-1 do
			local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
            if humanObjId ~= -1 then
                 if IsHaveQuest(sceneId,humanObjId, x270013_g_MissionId) > 0 then
                    local misIndex = GetQuestIndexByID(sceneId,humanObjId,x270013_g_MissionId)
										if GetQuestParam(sceneId,humanObjId,misIndex,0) < 3 then
												SetQuestByIndex(sceneId,humanObjId,misIndex,0,GetQuestParam(sceneId,humanObjId,misIndex,0)+1)
												Msg2Player(sceneId, humanObjId, format("ɱ�����Ƶ�ɣ��   %d/3", GetQuestParam(sceneId,humanObjId,misIndex,0)), 0, 3)
												x270013_CheckSubmit( sceneId, humanObjId)
										end
                end
            end
		end
	end
end


function x270013_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )

end

function x270013_ProcTiming(sceneId, selfId, ScriptId, MissionId)
end

function x270013_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
end

function x270013_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270013_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )

end

function x270013_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270013_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270013_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270013_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270013_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270013_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270013_Growpoint(sceneId,selfId,which)
		if IsHaveQuest(sceneId,selfId, x270013_g_MissionId) <= 0 then
				return 1
		end
		if which ==0 then
				local misIndex = GetQuestIndexByID(sceneId,selfId,x270013_g_MissionId)
				if GetQuestParam(sceneId,selfId,misIndex,0) < 3 then
							return 0
				else
							Msg2Player(sceneId, selfId, "���Ѿ����������", 0, 3)
							return 1
				end
		elseif which == 1 then
			local x,z =GetWorldPos(sceneId,selfId)
			local creatid =CreateMonster(sceneId, 3900,x+1,z+1,5,1,-1,-1,21,20000,180,"���Ƶ�ɣ��")
			SendSpecificImpactToUnit(sceneId, creatid, creatid, creatid, 8712, 0);
     end
    		return 1
		
end