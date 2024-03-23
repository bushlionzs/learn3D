--�����ߡ���ȡҩ��

--MisDescBegin
x270003_g_ScriptId = 270003
x270003_g_MissionIdPre =3565
x270003_g_MissionId = 3566
x270003_g_LevelLess	= 	50 
x270003_g_MissionIdNext = 3567
x270003_g_Name	={}
x270003_g_ExtTarget={{type=20,n=1,target="��@npc_136255��Ҫһ̳�ſ�����@npc_136499��ʹ������ؤ����Ӻ�@npc_141008���õ�@itemid_13020310"}}
x270003_g_MissionName="�����ߡ���ȡҩ��"
x270003_g_MissionInfo="\tû��ʱ��ȥ��ҩ�̵�ҩ���ˣ��ҵ�ͽ�ܲ��ܵ��ˡ���Ȼҩ�Ķ���ؤ�������ˣ���ô��ȥ�����������������ɣ��������ҵ�ҩ�������黹û��Ū���֮ǰ�Ȳ�Ҫ��ؤ�ﶯ�֣����ĵĸ��Ҵ���һ��¹�׾��С�����п��صĻ���һ̳�ƻ����ܽ�����⡣ȥ���ҵ�ͽ�������Ҫһ̳�ſ�����֪�������ⶫ����"  --��������
x270003_g_MissionTarget=""		
x270003_g_MissionCompleted="\t�漰ʱ���������Щʱ���ҵ�����ͽ�����ǾȲ������ˣ�"					--�������npc˵���Ļ�
x270003_g_ContinueInfo="\t��ȥ��ؤ������"
x270003_g_MissionHelp =	""
x270003_g_DemandItem ={{id=13020309,num=1},{id=13020310,num=1}}
x270003_g_BonusMoney1 =376
x270003_g_BonusMoney2 =0
x270003_g_BonusMoney3 =0
x270003_g_BonusMoney4 =0
x270003_g_BonusMoney5 =61
x270003_g_BonusMoney6 =0
x270003_g_BonusItem	=	{}
x270003_g_BonusChoiceItem ={}
x270003_g_ExpBonus = 145000
x270003_g_doing = 0
x270003_g_gaibangkanshou = -1
x270003_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
x270003_g_NpcGUID ={{ guid = 136255, name = "�����"} }
x270003_g_GroupPoint	={ {type=10,id =14,target = "ҩ�Ķ�"} }
--MisDescEnd
--**********************************

function x270003_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270003_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270003_g_MissionId, state, -1 )
	end
end

function x270003_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270003_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270003_g_ExpBonus )
		end
		if x270003_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270003_g_BonusMoney1 )
		end
		if x270003_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270003_g_BonusMoney2 )
		end
		if x270003_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270003_g_BonusMoney3 )
		end
		if x270003_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270003_g_BonusMoney4 )
		end
		if x270003_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270003_g_BonusMoney5 )
		end
		if x270003_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270003_g_BonusMoney6 )
		end
		for i, item in x270003_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270003_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270003_ProcEventEntry(sceneId, selfId, NPCId, MissionId, which)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) > 0 then
		if which == -1 then
			if x270003_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270003_g_MissionName)
						AddQuestText(sceneId,x270003_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270003_g_ScriptId, x270003_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270003_g_MissionName)
						AddQuestText(sceneId,x270003_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270003_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270003_g_ScriptId, x270003_g_MissionId);
			end
		elseif which == 1 then
				if GetItemCount(sceneId,selfId,x270003_g_DemandItem[1].id) < x270003_g_DemandItem[1].num then
						BeginAddItem(sceneId)
						AddItem( sceneId, x270003_g_DemandItem[1].id, x270003_g_DemandItem[1].num )
  					local ret = EndAddItem(sceneId,selfId)
    				if ret > 0 then
    					AddItemListToPlayer(sceneId,selfId)
    					BeginQuestEvent(sceneId)
							AddQuestText(sceneId,"\tԭ��ʦ�������˼�һֱ��֪����͵�źȾƣ��´��Ҳ����ˣ�")
							EndQuestEvent()
							DispatchQuestEventList(sceneId, selfId, NPCId, x270003_g_ScriptId, x270003_g_MissionId);
							Msg2Player(sceneId, selfId, "�õ�һ̳#G�ſ���#Y   1/1", 0, 3)
    				else
    					Msg2Player(sceneId, selfId, "��������", 0, 3)
    				end
    		end
    end
  elseif x270003_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270003_g_MissionName)
			AddQuestText(sceneId,x270003_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270003_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270003_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270003_g_MissionHelp )
			end
			x270003_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270003_g_ScriptId, x270003_g_MissionId);
  end
	
end
--**********************************

function x270003_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270003_CheckSubmit( sceneId, selfId, NPCId)
		if GetItemCount(sceneId,selfId,x270003_g_DemandItem[2].id) >= x270003_g_DemandItem[2].num then
				local misIndex = GetQuestIndexByID(sceneId,selfId,x270003_g_MissionId)
				SetQuestByIndex(sceneId,selfId,misIndex,0,1)
	    	SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	      return 1
	  else
	  		local misIndex = GetQuestIndexByID(sceneId,selfId,x270003_g_MissionId)
				SetQuestByIndex(sceneId,selfId,misIndex,0,0)
	    	SetQuestByIndex(sceneId,selfId,misIndex,7,0)
	  end
	  return 0
	
end
--**********************************
function x270003_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270003_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270003_g_MissionId  )
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
		if x270003_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x270003_g_MissionId, x270003_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270003_Msg2toplayer( sceneId, selfId,0)
		  		end
	 	end                                                                    
	     
end
--**********************************

function x270003_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270003_g_MissionId)
	  x270003_Msg2toplayer( sceneId, selfId,1)
	  for i, item in x270003_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
		end
			
end
--**********************************
function x270003_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270003_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270003_g_BonusChoiceItem do
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
function x270003_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270003_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270003_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270003_g_MissionId) > 0 then
				x270003_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270003_g_MissionId)
				x270003_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270003_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270003_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		for i, item in x270003_g_DemandItem do
	  				DelItem( sceneId,selfId,item.id, item.num )
				end
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270003_g_MissionIdNext )	
end

function x270003_GetBonus( sceneId, selfId,NpcID)
	  if x270003_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270003_g_ExpBonus);
  	end
		if x270003_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270003_g_BonusMoney1 )
	  end
		if x270003_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270003_g_BonusMoney2 )
	  end
		if x270003_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270003_g_BonusMoney3 )
		end
		if x270003_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270003_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270003_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270003_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270003_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270003_g_BonusMoney6)
		end
end

function x270003_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270003_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270003_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270003_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270003_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270003_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270003_g_MissionName.."��", 0, 3)
				if x270003_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270003_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270003_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270003_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270003_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270003_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270003_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270003_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270003_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270003_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270003_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270003_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270003_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270003_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270003_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270003_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270003_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270003_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270003_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270003_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  local bFind  = 0
    for i ,item in x270003_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) > 0 then
			if GetItemCount(sceneId,selfId,x270003_g_DemandItem[1].id) < x270003_g_DemandItem[1].num then
				AddQuestNumText(sceneId, x270003_g_MissionId, "����һ̳�ſ�",0, 1)
			end
		end
end

function x270003_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270003_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270003_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270003_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270003_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270003_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270003_useitem(sceneId,selfId)
		local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )
		local distanceRet = 25 - (95 - PlayerPosX) * (95 - PlayerPosX) - (214 - PlayerPosZ) * (214 - PlayerPosZ)
		if distanceRet >= 0 then
				if x270003_g_doing==0   then
						x270003_g_PROTECTINFO.StartTime = GetCurrentTime()
						x270003_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270003, "OnScneneTimer", 1)
						if x270003_g_PROTECTINFO.ScneneTimerIndex >= 0 then
								x270003_g_doing = 1
								x270003_g_gaibangkanshou =FindMonsterByGUID( sceneId,136269)
								if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
										SetPatrolId(sceneId, x270003_g_gaibangkanshou, 0)
								end
						end
				end
				DelItem( sceneId,selfId,x270003_g_DemandItem[1].id, x270003_g_DemandItem[1].num )
				return 1
		else
				Msg2Player(sceneId, selfId, "�����޷�ʹ�������Ʒ", 0, 3)
				return 0
		end
end


function x270003_Growpoint(sceneId,selfId,which)
		if IsHaveQuest(sceneId,selfId, x270003_g_MissionId) <= 0 then
				return 1
		end
		if which ==0 then
				if x270003_g_doing > 0 then
					if GetItemCount(sceneId,selfId,x270003_g_DemandItem[2].id) < x270003_g_DemandItem[2].num then
							return 0
					else
							Msg2Player(sceneId, selfId, "���Ѿ��õ���ҩ��", 0, 3)
							return 1
					end
				else
					BeginQuestEvent(sceneId)
					AddQuestText(sceneId,"\t�����߽����ҩ�ģ��Ա߿��ص�ؤ�����һֱ�ڿ����㡣�������������˵Ļ����Ȳ���ؤ�﷢����ͻ����������취�������߰ɡ�")
					EndQuestEvent()
					DispatchQuestEventList(sceneId, selfId, selfId, x270003_g_ScriptId, x270003_g_MissionId);
					return 1
				end
		elseif which == 1 then
				if GetItemCount(sceneId,selfId,x270003_g_DemandItem[2].id) < x270003_g_DemandItem[2].num then
						BeginAddItem(sceneId)
						AddItem( sceneId, x270003_g_DemandItem[2].id, x270003_g_DemandItem[2].num )
  					local ret = EndAddItem(sceneId,selfId)
    				if ret > 0 then
    					AddItemListToPlayer(sceneId,selfId)
    					Msg2Player(sceneId, selfId, "�õ���#G¹��#Y   1/1", 0, 3)
    					x270003_CheckSubmit( sceneId, selfId)
    				else
    					Msg2Player(sceneId, selfId, "��������", 0, 3)
    				end
    		end
    		return 0
    end
		
end

function x270003_OnScneneTimer(sceneId)
	if x270003_g_gaibangkanshou < 0 then
			x270003_CloseTimer(sceneId, x270003_g_PROTECTINFO.ScneneTimerIndex)
			return
	end
	if x270003_g_doing==1   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 1   then
						x270003_g_doing = 2
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "����ľ�ζ����", -1)
						end
		end
	elseif x270003_g_doing==2   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 5   then
						x270003_g_doing = 3
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "һ����ʲô�˲�С�İѾ����������ˣ�", -1)
						end
		end
	elseif x270003_g_doing==3   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 9   then
						x270003_g_doing = 4
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "�����һ̳�ſ���������Ʋ�������������ˡ�", -1)
						end
		end
	elseif x270003_g_doing==4   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 13   then
						x270003_g_doing = 5
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "�ԾƵ��裬�������Σ�", -1)
						end
		end
	elseif x270003_g_doing==5   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 17   then
						x270003_g_doing = 6
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "Ʃ�糯¶��ȥ�տ�ࡣ", -1)
						end
		end
	elseif x270003_g_doing==6   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 21   then
						x270003_g_doing = 7
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "�����Կ�����˼������", -1)
						end
		end
	elseif x270003_g_doing==7   then
		if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 25   then
						x270003_g_doing = 8
						if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
								NpcTalk(sceneId, x270003_g_gaibangkanshou, "���Խ��ǣ�Ψ�жſ���", -1)
						end
		end
	elseif x270003_g_doing==8 then
			if GetCurrentTime() - x270003_g_PROTECTINFO.StartTime >= 42   then
				x270003_g_doing=9
				x270003_CloseTimer(sceneId, x270003_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x270003_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270003_g_doing =0
	if IsObjValid (sceneId,x270003_g_gaibangkanshou) == 1 then
			SetPatrolId(sceneId, x270003_g_gaibangkanshou, -1)
	end
	x270003_g_gaibangkanshou =-1
end