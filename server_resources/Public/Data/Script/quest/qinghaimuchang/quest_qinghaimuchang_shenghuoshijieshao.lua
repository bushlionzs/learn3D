--�����֡�ʥ��ʹ��ʶְҵ

--MisDescBegin
x203572_g_ScriptId = 203572
x203572_g_MissionIdPre =3400
x203572_g_MissionId = 3424
x203572_g_LevelLess	= 	1 
x203572_g_MissionIdNext = 3441
--x203572_g_Name	={"����","��³˹" }
x203572_g_ExtTarget={{type=20,n=3,target="��@npc_131001�ֽ�ְҵ��չ"}}
x203572_g_MissionName="�����֡���ʶְҵ"
x203572_g_MissionTalk={"ʥ��ʹ����״","ʥ��ʹ���ص�","����ܳ�Ϊ��ʦ"}
x203572_g_MissionInfo="\t��Ϊһ��������������ˣ����ȱ���Ҫ���Լ���ְҵ����ȷ����ʶ��\n\t�ҵ��������߹������ʱ�������磬����ʶ�㡣��һ������Ϊ�������й����ְҵ��ָ�㡣"  --��������
x203572_g_MissionTarget="��@npc_131001�ֽ�ְҵ��չ"		
x203572_g_MissionCompleted="\t�����书���ǳ�Ϧ����ֻ�г�֮�Ժ����ϰ�����ܳ�Ϊһ����ʦ��"
x203572_g_ContinueInfo={"\tʥ��ʹ���Բ�˹�����Ǽ��Ź����ؽ�սʤ�ڰ������Ѻʹ��۶�����ʱ�ģ��ڰ��ؽ���ȥ������һ��������",
												"\tʥ��ʹ�ֳ�ˮ���֡������Ѷϵ�ʥ�����ʥ������е������书���������£�����ʥ����塣",
												"\t���ܾ�Ϊ�����˺����ܣ���Ϊ��Ŀ�깥�����ܣ���λʱ������˺��ߡ�\n"}
x203572_g_MissionHelp =	"#G�����������#R���#G���@npc_131001�������Ի��������Ե�������ϵ�#RQ#G�����������б�ѡ����Ҫ��ɵ����񣬵��#R����Ŀ��#G�е���ɫ�����������Զ�Ѱ·��"
x203572_g_DemandItem ={}
x203572_g_ExpBonus = 23
x203572_g_BonusMoney1 =11
x203572_g_BonusMoney2 =0
x203572_g_BonusMoney3 =0
x203572_g_BonusMoney4 =0
x203572_g_BonusMoney5 =12
x203572_g_BonusMoney6 =0
x203572_g_BonusItem	=	{}
x203572_g_BonusChoiceItem ={}
x203572_g_NpcGUID = {{ guid = 131001, name = "����"} }
--x203572_g_Skill	= {{id=123, level=1, pos=4},{id=132, level=1, pos=3}}
--MisDescEnd

--**********************************

function x203572_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 ) 
	if IsQuestHaveDone(sceneId, selfId, x203572_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x203572_g_MissionIdPre) > 0 then
		if GetZhiye( sceneId, selfId)==7 then
				if IsHaveQuest(sceneId,selfId, x203572_g_MissionId) <= 0 then
						local state = GetQuestStateNM(sceneId,selfId,NPCId,x203572_g_MissionId)
						AddQuestTextNM( sceneId, selfId, NPCId, x203572_g_MissionId, state, -1 )
					  CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,1 )					 
				end
		end
	end
end

function x203572_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x203572_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x203572_g_ExpBonus )
		end
		if x203572_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x203572_g_BonusMoney1 )
		end
		if x203572_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x203572_g_BonusMoney2 )
		end
		if x203572_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x203572_g_BonusMoney3 )
		end
		if x203572_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x203572_g_BonusMoney4 )
		end
		if x203572_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x203572_g_BonusMoney5 )
		end
		if x203572_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x203572_g_BonusMoney6 )
		end
		for i, item in x203572_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.id, item.num)
	  end
		for i, item in x203572_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

--������ں���

--**********************************

function x203572_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--����������ִ�д˽ű�
   local misIndex = GetQuestIndexByID(sceneId,selfId,x203572_g_MissionId)
   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,0 )
	if IsQuestHaveDone(sceneId, selfId, x203572_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x203572_g_MissionId) > 0 then
			if x203572_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
					if which == -1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203572_g_MissionName) 
						AddQuestText(sceneId,x203572_g_ContinueInfo[1])
						AddQuestNumText(sceneId, MissionId, x203572_g_MissionTalk[1],0,0)
						EndQuestEvent()	
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 16,1 )		
						DispatchQuestEventList(sceneId, selfId, NPCId, x203572_g_ScriptId, x203572_g_MissionId); 
						
					elseif which ==0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203572_g_MissionName)
						AddQuestText(sceneId,x203572_g_ContinueInfo[2])
						AddQuestNumText(sceneId, MissionId, x203572_g_MissionTalk[2],1,1)
						EndQuestEvent()
						SetQuestByIndex(sceneId,selfId,misIndex,0,1)
						DispatchQuestEventList(sceneId, selfId, NPCId, x203572_g_ScriptId, x203572_g_MissionId);
					elseif which ==1 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203572_g_MissionName)
						AddQuestText(sceneId,x203572_g_ContinueInfo[3])
						AddQuestNumText(sceneId, MissionId, x203572_g_MissionTalk[3],0,2)
						EndQuestEvent()
						SetQuestByIndex(sceneId,selfId,misIndex,0,2)
						DispatchQuestEventList(sceneId, selfId, NPCId, x203572_g_ScriptId, x203572_g_MissionId);
						local misIndex = GetQuestIndexByID(sceneId,selfId,x203572_g_MissionId)  
						SetQuestByIndex(sceneId,selfId,misIndex,1,1)                                                
	    			SetQuestByIndex(sceneId,selfId,misIndex,7,1)
					end
			else
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 16,0)
						CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,1)
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x203572_g_MissionName)
						AddQuestText(sceneId,x203572_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x203572_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						SetQuestByIndex(sceneId,selfId,misIndex,0,3)
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x203572_g_ScriptId, x203572_g_MissionId);
			end
  elseif x203572_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
    CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 5,0 )
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x203572_g_MissionName)
			AddQuestText(sceneId,x203572_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺") 
			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 1,1 )	
			for i, item in x203572_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x203572_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x203572_g_MissionHelp )
			end
			x203572_DispatchMissionInfo( sceneId, selfId, NPCId )
			EndQuestEvent()
		
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x203572_g_ScriptId, x203572_g_MissionId);
			CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,1 )
  end
end
--**********************************
function x203572_ProcAcceptCheck(sceneId, selfId, NPCId)
	if IsQuestHaveDone(sceneId, selfId, x203572_g_MissionId) > 0 then
		return 0
	elseif IsQuestHaveDone(sceneId, selfId, x203572_g_MissionIdPre) <= 0 then
		return 0
	end
	return 1
end
--**********************************
function x203572_CheckSubmit( sceneId, selfId, NPCId)
	local misIndex = GetQuestIndexByID(sceneId,selfId,x203572_g_MissionId)
	if GetQuestParam(sceneId,selfId,misIndex,1) == 1 then
	        return 1
	end
	return 0
end
--**********************************
function x203572_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x203572_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x203572_g_MissionId  )
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
		if x203572_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
					local retmiss = AddQuest( sceneId, selfId, x203572_g_MissionId, x203572_g_ScriptId, 0, 0, 0,1)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x203572_Msg2toplayer( sceneId, selfId,0)
						--if x203572_CheckSubmit(sceneId, selfId, NPCId) > 0 then
								local misIndex = GetQuestIndexByID(sceneId,selfId,x203572_g_MissionId)                                                  
	    					SetQuestByIndex(sceneId,selfId,misIndex,7,1)
	    					CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 4,0 )
	    			--end
		  		end
	 	end                                                                    
	     
end
--**********************************
function x203572_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x203572_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x203572_g_MissionId)
	  x203572_Msg2toplayer( sceneId, selfId,1)
	  
end
--**********************************
function x203572_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x203572_g_BonusItem do
		AddItem( sceneId, item.id, item.num )
  end
  for j, item in x203572_g_BonusChoiceItem do
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
function x203572_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x203572_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203572_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x203572_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x203572_g_MissionId) > 0 then
				x203572_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x203572_g_MissionId)
				QuestCom(sceneId, selfId, 3440)
				x203572_GetBonus( sceneId, selfId,NPCId)
				--if HaveSkill(sceneId, selfId,x203572_g_Skill[1].id)<=0 then
					--AddSkillToPlayer(sceneId, selfId, x203572_g_Skill[1].id, x203572_g_Skill[1].level, x203572_g_Skill[1].pos)
				--end
				--if HaveSkill(sceneId, selfId,x203572_g_Skill[2].id)<=0 then
					--AddSkillToPlayer(sceneId, selfId, x203572_g_Skill[2].id, x203572_g_Skill[2].level, x203572_g_Skill[2].pos)
				--end       
			  --CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 17,1 ) 
			   CallScriptFunction( UTILITY_SCRIPT, "ShowNewUITips", sceneId, selfId, 3,0)
				CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x203572_g_MissionIdNext )	
   end
end

function x203572_GetBonus( sceneId, selfId,NpcID)
	  if x203572_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x203572_g_ExpBonus);
  	end
		if x203572_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x203572_g_BonusMoney1 )
	  end
		if x203572_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x203572_g_BonusMoney2 )
	  end
		if x203572_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x203572_g_BonusMoney3 )
		end
		if x203572_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x203572_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x203572_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x203572_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x203572_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x203572_g_BonusMoney6)
		end
end

function x203572_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x203572_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x203572_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x203572_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x203572_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x203572_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x203572_g_MissionName.."��", 0, 3)
				if x203572_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203572_g_ExpBonus.."#cffcf00�Ľ���", 0, 2)
  			end
				if x203572_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203572_g_BonusMoney1.."��#cffcf00�Ľ���", 0, 2)
	  		end
				if x203572_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203572_g_BonusMoney2.."��#cffcf00�Ľ���", 0, 2)
	  		end
				if x203572_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#cffcf00���#G��"..x203572_g_BonusMoney3.."��#cffcf00�Ľ���", 0, 2)
				end
				if x203572_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G��͢����ֵ"..x203572_g_BonusMoney4.."#cffcf00�Ľ���", 0, 2)
				end
				if x203572_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203572_g_BonusMoney5.."#cffcf00�Ľ���", 0, 2)
				end
				if x203572_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#cffcf00���#G����"..x203572_g_BonusMoney6.."#cffcf00�Ľ���", 0, 2)
				end
		end
end

function x203572_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
    local bFind  = 0
    for i ,item in x203572_g_NpcGUID do
        if item.guid == npcGuid then
            bFind = 1
            break
        end
    end
    if bFind == 0 then
        return
    end
		if IsHaveQuest(sceneId,selfId, x203572_g_MissionId) > 0 then
				local state = GetQuestStateNM(sceneId,selfId,npcId,x203572_g_MissionId)
				AddQuestTextNM( sceneId, selfId, npcId, x203572_g_MissionId, 7, -1 )
		end
end

--**********************************

function x203572_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end
--**********************************
function x203572_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x203572_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x203572_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x203572_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x203572_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x203572_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x203572_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x203572_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x203572_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x203572_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end