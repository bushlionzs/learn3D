--�����ߡ�׷����Դ<��>

--MisDescBegin
x270001_g_ScriptId = 270001
x270001_g_MissionIdPre =3538
x270001_g_MissionId = 3539
x270001_g_LevelLess	= 	40 
x270001_g_MissionIdNext = 3534
x270001_g_Name	={}
x270001_g_ExtTarget={{type=20,n=1,target="��������@npc_141392��͵��̸��"}}
x270001_g_MissionName="�����ߡ�׷����Դ<��>"
x270001_g_MissionInfo="\t�¶���ʥ���ʧ�������£����Ǿ���һ����ã����ǰݻ������������ǰ��β�漸�����Ź�����ε��ˣ������˰ݻ������һ����Ἰ�����ܾۼ�ͬ��һ���ط���֪��ıʲô����Щ�������������ܿ����Ƕ��ҽ̲���������͸ϻ���̳��������������Ҽ����������ǵĶ�����\n\t��ס���򲻿ɴ�ݾ��ߣ�һ���ջ��뼴�̻ر���������"  --��������
x270001_g_MissionTarget=""		
x270001_g_MissionCompleted="\t�����������ա��ٺ١���Ц˵����\n\t�ߺߣ��벻���ݻ�̾����䵽��ݻ�����ֽ�������ͬ�����ۣ���ݻ��ֻ������Щ������С�㼯���ɣ�����Ϊ�塣��δ����ݻ�̣�Ϊ�˽⿪ʥ��������ܣ���Ȼ��ͬ����������ʹ��ɱ�֣�"					--�������npc˵���Ļ�
x270001_g_ContinueInfo="\t���кη��֣�"
x270001_g_MissionHelp =	""
x270001_g_DemandItem ={}
x270001_g_BonusMoney1 =376
x270001_g_BonusMoney2 =0
x270001_g_BonusMoney3 =0
x270001_g_BonusMoney4 =0
x270001_g_BonusMoney5 =51
x270001_g_BonusMoney6 =0
x270001_g_BonusItem	=	{}
x270001_g_BonusChoiceItem ={}
x270001_g_ExpBonus = 93000
x270001_g_doing = 0
x270001_g_acceptid =0
x270001_g_bosimingjiao = -1
x270001_g_zhongtudiren = -1
x270001_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x270001_g_NpcGUID ={{ guid = 141300, name = "������"} }
x270001_g_GroupPoint	={ {type=10,id =13,target = "�ݶ�"} } --ֻ����id��type���Ǵ��������������
--MisDescEnd
--**********************************

function x270001_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270001_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270001_g_MissionIdPre)> 0 then
		if IsHaveQuest(sceneId,selfId, x270001_g_MissionId) <= 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270001_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270001_g_MissionId, state, -1 )
		end
	end
end

function x270001_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270001_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270001_g_ExpBonus )
		end
		if x270001_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270001_g_BonusMoney1 )
		end
		if x270001_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270001_g_BonusMoney2 )
		end
		if x270001_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270001_g_BonusMoney3 )
		end
		if x270001_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270001_g_BonusMoney4 )
		end
		if x270001_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270001_g_BonusMoney5 )
		end
		if x270001_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270001_g_BonusMoney6 )
		end
		for i, item in x270001_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270001_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270001_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270001_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270001_g_MissionId) > 0 then
			if x270001_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270001_g_MissionName)
						AddQuestText(sceneId,x270001_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270001_g_ScriptId, x270001_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270001_g_MissionName)
						AddQuestText(sceneId,x270001_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270001_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270001_g_ScriptId, x270001_g_MissionId);
			end
  elseif x270001_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270001_g_MissionName)
			AddQuestText(sceneId,x270001_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270001_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270001_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270001_g_MissionHelp )
			end
			x270001_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270001_g_ScriptId, x270001_g_MissionId);
  end
	
end
--**********************************

function x270001_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270001_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270001_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270001_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
end
--**********************************
function x270001_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270001_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270001_g_MissionId  )
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
		
		if x270001_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270001_g_MissionId, x270001_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270001_Msg2toplayer( sceneId, selfId,0)
						if x270001_CheckSubmit(sceneId, selfId, NPCId) > 0 then
							local misIndex = GetQuestIndexByID(sceneId,selfId,x270001_g_MissionId)                                                  
	    				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    				SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    			end
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270001_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270001_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270001_g_MissionId)
	  x270001_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x270001_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270001_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270001_g_BonusChoiceItem do
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
function x270001_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270001_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270001_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270001_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270001_g_MissionId) > 0 then
				x270001_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270001_g_MissionId)
				x270001_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270001_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270001_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   --CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270001_g_MissionIdNext )	
end

function x270001_GetBonus( sceneId, selfId,NpcID)
	  if x270001_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270001_g_ExpBonus);
  	end
		if x270001_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270001_g_BonusMoney1 )
	  end
		if x270001_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270001_g_BonusMoney2 )
	  end
		if x270001_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270001_g_BonusMoney3 )
		end
		if x270001_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270001_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270001_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270001_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270001_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270001_g_BonusMoney6)
		end
end

function x270001_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270001_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270001_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270001_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270001_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270001_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270001_g_MissionName.."��", 0, 3)
				if x270001_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270001_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270001_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270001_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270001_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270001_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270001_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270001_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270001_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270001_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270001_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270001_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270001_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270001_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270001_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270001_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270001_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270001_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270001_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270001_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270001_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270001_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x270001_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x270001_g_MissionId, state, -1 )
		end
end

function x270001_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270001_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270001_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270001_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270001_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270001_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270001_Growpoint( sceneId, selfId,openorremove)
		if IsHaveQuest(sceneId,selfId, x270001_g_MissionId) <= 0 then
				return 1
		end
		if IsHaveQuest(sceneId,selfId, 7537) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)
						return 0
		elseif IsHaveQuest(sceneId,selfId, 7538) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)
						return 0
		elseif IsHaveQuest(sceneId,selfId, 7539) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)
						return 0
		elseif IsHaveSpecificImpact(sceneId, selfId, 7516) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)
						return 0
		elseif IsHaveSpecificImpact(sceneId, selfId, 7517) > 0 then
						Msg2Player(sceneId, selfId, "�����ڵ�״̬�޷���������", 0, 3)
						return 0
		end
		local misIndex = GetQuestIndexByID(sceneId,selfId,x270001_g_MissionId)
		if openorremove == 0 then
			if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then
					return 0
			else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t��С��������\n\t���Ѿ�֪������Ҫ���ˣ������ٵ�������ȥ�����ˡ�")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId);
					return 1
			end
		elseif openorremove == 1 then
			if GetQuestParam(sceneId,selfId,misIndex,0) ==0 then
				if x270001_g_doing == 0 then
					x270001_g_PROTECTINFO.StartTime = GetCurrentTime()
					x270001_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270001, "OnScneneTimer", 1)
					if x270001_g_PROTECTINFO.ScneneTimerIndex >= 0 then
							x270001_g_doing = 1
							x270001_g_acceptid = selfId
							x270001_g_bosimingjiao=CreateMonster(sceneId, 15004,161.3730,117.1914,3,1,-1,-1,20,41000,180,"���վ�")
							x270001_g_zhongtudiren=FindMonsterByGUID( sceneId,141320)
							if IsObjValid (sceneId,x270001_g_bosimingjiao) == 1 then
									SetPatrolId(sceneId, x270001_g_bosimingjiao, 16)
							end
							if IsObjValid (sceneId,x270001_g_zhongtudiren) == 1 then
									SetPatrolId(sceneId, x270001_g_zhongtudiren, 17)
							end
							return 1
					end
				else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t��ո�Ҫ�����𣬷��������Ѿ���һ������")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId);
					return 0
				end
			else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t��С��������\n\t���Ѿ�֪������Ҫ���ˣ������ٵ�������ȥ�����ˡ�")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId);
					return 0
			end
		end
end

function x270001_OnScneneTimer(sceneId)
	if x270001_g_bosimingjiao < 0 then
			x270001_CloseTimer(sceneId, x270001_g_PROTECTINFO.ScneneTimerIndex)
	elseif x270001_g_zhongtudiren < 0 then
			x270001_CloseTimer(sceneId, x270001_g_PROTECTINFO.ScneneTimerIndex)
	end
	if x270001_g_doing==1   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime <= 1   then
			if IsPlayerStateNormal(sceneId,x270001_g_acceptid) ==1 then
				SetPos(sceneId,x270001_g_acceptid,159,104)
				SendSpecificImpactToUnit(sceneId, x270001_g_acceptid, x270001_g_acceptid, x270001_g_acceptid, 8704, 0);
			end
		elseif GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 5   then
						x270001_g_doing = 2
						if IsObjValid (sceneId,x270001_g_bosimingjiao) == 1 then
								NpcTalk(sceneId, x270001_g_zhongtudiren, "�������ˣ�", -1)
						end
		end
	elseif x270001_g_doing==2   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 8   then
						x270001_g_doing = 3
						if IsObjValid (sceneId,x270001_g_zhongtudiren) == 1 then
								NpcTalk(sceneId, x270001_g_bosimingjiao, "�����Ѿ����������ٶ��ˣ��ټ������˲������ף�", -1)
						end
		end
	elseif x270001_g_doing==3   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 11   then
						x270001_g_doing = 4
						if IsObjValid (sceneId,x270001_g_bosimingjiao) == 1 then
								NpcTalk(sceneId, x270001_g_bosimingjiao, "���ã�ʱ�仹���ü���������Ĺ���Ӧ��û��ô��ָ���", -1)
						end
		end
	elseif x270001_g_doing==4   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 14   then
						x270001_g_doing = 5
						if IsObjValid (sceneId,x270001_g_zhongtudiren) == 1 then
								NpcTalk(sceneId, x270001_g_zhongtudiren, "���ǵ��˻���һЩû�е������Ǿ��ڱ���ĸߵؼ��ϣ����˶��������Ǿͷ���������", -1)
						end
		end
	elseif x270001_g_doing==5   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 17   then
						x270001_g_doing = 6
						if IsObjValid (sceneId,x270001_g_bosimingjiao) == 1 then
								NpcTalk(sceneId, x270001_g_bosimingjiao, "����ˣ�ҹ���ζ࣬������̽������������վ�Э������ʲô��", -1)
						end
		end
	elseif x270001_g_doing==6   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 20   then
						x270001_g_doing = 7
						if IsObjValid (sceneId,x270001_g_zhongtudiren) == 1 then
								NpcTalk(sceneId, x270001_g_zhongtudiren, "�㲻��˵��Ķ�������������û�취����𣿻��ǵ��˶������׵�Щ�á�", -1)
						end
		end
	elseif x270001_g_doing==7   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 23   then
						x270001_g_doing = 8
						if IsObjValid (sceneId,x270001_g_bosimingjiao) == 1 then
								NpcTalk(sceneId, x270001_g_bosimingjiao, "�ðɣ�������׼������֮��͵�ȼ�����ɫ�źţ���ʱ�������վ�����һ��ɱ�롣", -1)
						end
		end
	elseif x270001_g_doing==8   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 26   then
						x270001_g_doing = 9
						if IsObjValid (sceneId,x270001_g_zhongtudiren) == 1 then
								NpcTalk(sceneId, x270001_g_zhongtudiren, "������ס���ǵ�Э�飬�����������������������ǵģ��õ�֮�����ǻ������뿪��", -1)
						end
		end
	elseif x270001_g_doing==9   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 29   then
						x270001_g_doing = 10
						if IsObjValid (sceneId,x270001_g_bosimingjiao) == 1 then
								NpcTalk(sceneId, x270001_g_bosimingjiao, "��Ȼ�������������Һ��������ĵؽ�����Ұ��һ��Ҫ������Щ��ɫ������", -1)
						end
		end
	elseif x270001_g_doing==10   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 32   then
						x270001_g_doing = 11
						if IsObjValid (sceneId,x270001_g_zhongtudiren) == 1 then
								NpcTalk(sceneId, x270001_g_zhongtudiren, "�ף��������ô��������Щ��һ�����������Щ��", -1)
            		SetMonsterDir(sceneId,x270001_g_zhongtudiren,60)
            end
		end
	elseif x270001_g_doing==11   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 35   then
						x270001_g_doing = 12
						if IsObjValid (sceneId,x270001_g_bosimingjiao) == 1 then
								NpcTalk(sceneId, x270001_g_bosimingjiao, "��ʲô�𣡵�ʱ�����Ҳ�����ǰݻ�̵ģ��Ͻ�ȥ�ټ������ȥ��", -1)
						end
						if IsObjValid (sceneId,x270001_g_zhongtudiren) == 1 then
           	 		SetMonsterDir(sceneId,x270001_g_zhongtudiren,120)
            end
		end
	elseif x270001_g_doing==12   then
		if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 38   then
						x270001_g_doing = 13
						if IsObjValid (sceneId,x270001_g_zhongtudiren) == 1 then
								NpcTalk(sceneId, x270001_g_zhongtudiren, "�ã����ǵ����ǵ���Ϣ�ɣ�", -1)
								SetPos(sceneId,x270001_g_zhongtudiren,154,102)
						end
		end
	elseif x270001_g_doing==13 then
			if GetCurrentTime() - x270001_g_PROTECTINFO.StartTime >= 41   then
				if IsPlayerStateNormal(sceneId,x270001_g_acceptid) ==1 then
									local misIndex = GetQuestIndexByID(sceneId, x270001_g_acceptid, x270001_g_MissionId)
									SetQuestByIndex(sceneId,x270001_g_acceptid,misIndex,0,1)
									SetQuestByIndex(sceneId,x270001_g_acceptid,misIndex,7,1)
									BeginQuestEvent(sceneId)
									AddQuestText(sceneId,format("͵���ݻ�̵�̸��   %d/1", GetQuestParam(sceneId,x270001_g_acceptid,misIndex,0) ))
									EndQuestEvent(sceneId)
									DispatchQuestTips(sceneId,x270001_g_acceptid)
									CancelSpecificImpact(sceneId,x270001_g_acceptid,8704)
				end
				x270001_g_doing=14
				x270001_CloseTimer(sceneId, x270001_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x270001_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270001_g_doing =0
	x270001_g_acceptid =-1
	x270001_g_bosimingjiao = -1
	x270001_g_zhongtudiren = -1
	x270001_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}

end