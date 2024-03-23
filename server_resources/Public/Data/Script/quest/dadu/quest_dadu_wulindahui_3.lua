--�����ߡ�����

--MisDescBegin
x270006_g_ScriptId = 270006
x270006_g_MissionIdPre =3572
x270006_g_MissionId = 3573
x270006_g_LevelLess	= 	50 
x270006_g_MissionIdNext = 3574
x270006_g_Name	={}
x270006_g_ExtTarget={{type=20,n=1,target="Ū����������"}}
x270006_g_MissionName="�����ߡ�����"
x270006_g_MissionInfo="\t�ҹ���²�е�����վ��ֱ���Ӳ�����Щ���캦��֮�£�����Ӳ˵������Ϊ����Ҳû��ʲô�ý��͵ġ�\n\t�������棬����ذɣ����ִ��֮ʱ�����Ի�Դ�������������"  --��������
x270006_g_MissionTarget=""		
x270006_g_MissionCompleted="\t�������ۣ��Ҷ����ϴ�ʦ��ʱ���֣���ؤ��ű�ס����ؤ���������֮���������Ҿ���ؤ���ǧ�����ˡ�"					--�������npc˵���Ļ�
x270006_g_ContinueInfo="\t���黹û��Ū����������԰����꣡"
x270006_g_MissionHelp =	""
x270006_g_DemandItem ={}
x270006_g_BonusMoney1 =376
x270006_g_BonusMoney2 =0
x270006_g_BonusMoney3 =0
x270006_g_BonusMoney4 =0
x270006_g_BonusMoney5 =61
x270006_g_BonusMoney6 =0
x270006_g_BonusItem	=	{}
x270006_g_BonusChoiceItem ={}
x270006_g_ExpBonus = 145000
x270006_g_doing = 0
x270006_g_acceptid =-1
x270006_g_jiazhizhang = -1
x270006_g_guoponu = -1
x270006_g_heshang1 = -1
x270006_g_heshang2 =-1
x270006_g_heshang3 = -1
x270006_g_heshang4 = -1
x270006_g_zhangsanfeng = -1
x270006_g_fenglingshitai = -1
x270006_g_hezudao = -1
x270006_g_chenyouliang = -1
x270006_g_zhenzhizhang = -1
x270006_g_dingshangyi = -1
x270006_g_wangshisan = -1
x270006_g_lengxiaoqi = -1
x270006_g_lixuanyi = -1
x270006_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
--MisDescEnd
--**********************************

function x270006_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)


	if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionId) > 0 then
		return 
	end
	if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionIdPre)> 0 then
			local state = GetQuestStateNM(sceneId,selfId,NPCId,x270006_g_MissionId)
			AddQuestTextNM( sceneId, selfId, NPCId, x270006_g_MissionId, state, -1 )
	end
end

function x270006_DispatchMissionInfo( sceneId, selfId, NPCId )
		if x270006_g_ExpBonus> 0 then
			AddQuestExpBonus(sceneId, x270006_g_ExpBonus )
		end
		if x270006_g_BonusMoney1 > 0 then
			AddQuestMoneyBonus1(sceneId, x270006_g_BonusMoney1 )
		end
		if x270006_g_BonusMoney2 > 0 then
			AddQuestMoneyBonus2(sceneId, x270006_g_BonusMoney2 )
		end
		if x270006_g_BonusMoney3 > 0 then
			AddQuestMoneyBonus3(sceneId, x270006_g_BonusMoney3 )
		end
		if x270006_g_BonusMoney4 > 0 then
			AddQuestMoneyBonus4(sceneId, x270006_g_BonusMoney4 )
		end
		if x270006_g_BonusMoney5 > 0 then
			AddQuestMoneyBonus5(sceneId, x270006_g_BonusMoney5 )
		end
		if x270006_g_BonusMoney6 > 0 then
			AddQuestMoneyBonus6(sceneId, x270006_g_BonusMoney6 )
		end
		for i, item in x270006_g_BonusItem do
		   	AddQuestItemBonus(sceneId, item.item, item.n)
	  end
		for i, item in x270006_g_BonusChoiceItem do
	    	AddQuestRadioItemBonus(sceneId, item.item, item.n)
	  end
end
--**********************************

function x270006_ProcEventEntry(sceneId, selfId, NPCId, MissionId)	--����������ִ�д˽ű�
	if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionId) > 0 then
		return 
	end
	if IsHaveQuest(sceneId,selfId, x270006_g_MissionId) > 0 then
			if x270006_CheckSubmit(sceneId, selfId, NPCId) <= 0 then
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270006_g_MissionName)
						AddQuestText(sceneId,x270006_g_ContinueInfo)
						EndQuestEvent()
						DispatchQuestEventList(sceneId, selfId, NPCId, x270006_g_ScriptId, x270006_g_MissionId);
			else
						BeginQuestEvent(sceneId)
						AddQuestText(sceneId,"#Y"..x270006_g_MissionName)
						AddQuestText(sceneId,x270006_g_MissionCompleted)
						AddQuestText(sceneId," ")
						x270006_DispatchMissionInfo( sceneId, selfId, NPCId )
						EndQuestEvent()
						DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x270006_g_ScriptId, x270006_g_MissionId);
			end
  elseif x270006_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
			BeginQuestEvent(sceneId)
	  	AddQuestText(sceneId,"#Y"..x270006_g_MissionName)
			AddQuestText(sceneId,x270006_g_MissionInfo)
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			for i, item in x270006_g_ExtTarget do
					AddQuestText( sceneId,item.target)
			end 
			if x270006_g_MissionHelp ~= "" then
				AddQuestText(sceneId,"\n#GС��ʾ:#W")
				AddQuestText(sceneId,x270006_g_MissionHelp )
			end
			x270006_DispatchMissionInfo( sceneId, selfId, NPCId )
	  	EndQuestEvent()
			DispatchQuestInfoNM(sceneId, selfId, NPCId, x270006_g_ScriptId, x270006_g_MissionId);
  end
	
end
--**********************************

function x270006_ProcAcceptCheck(sceneId, selfId, NPCId)
		if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionIdPre)> 0 then
					return 1
		end
		return 0

end
--**********************************
function x270006_CheckSubmit( sceneId, selfId, NPCId)
		local misIndex = GetQuestIndexByID(sceneId, selfId, x270006_g_MissionId)
		if GetQuestParam(sceneId,selfId,misIndex,0) ==1 then 
	        return 1
	  end
	  return 0
	
end
--**********************************
function x270006_ProcQuestAccept( sceneId, selfId, NPCId, MissionId )
		if IsQuestHaveDone(sceneId, selfId, x270006_g_MissionId) > 0 then
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
		local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId,x270006_g_MissionId  )
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
		if x270006_ProcAcceptCheck(sceneId, selfId, NPCId) > 0 then
				if x270006_g_doing == 0 then
					local retmiss = AddQuest( sceneId, selfId, x270006_g_MissionId, x270006_g_ScriptId, 0, 0, 0)
					if retmiss ==0 then
						Msg2Player(sceneId, selfId, "��������ʧ�ܣ�", 0, 3)
						return 0
					else
		  			x270006_Msg2toplayer( sceneId, selfId,0)
		  			x270006_g_PROTECTINFO.StartTime = GetCurrentTime()
						x270006_g_PROTECTINFO.ScneneTimerIndex = SetTimer(sceneId, selfId, 270006, "OnScneneTimer", 1)
						if x270006_g_PROTECTINFO.ScneneTimerIndex >= 0 then
								x270006_g_doing = 1
								x270006_g_acceptid = selfId
								x270006_g_jiazhizhang=CreateMonster(sceneId, 3800,205.7862,206.0416,3,1,-1,-1,20,78000,180,"������ʦ")
								x270006_g_heshang1=CreateMonster(sceneId, 3822,204.2096,205.2391,3,1,-1,-1,20,93000,180,"�ռ�")
								x270006_g_heshang2=CreateMonster(sceneId, 3822,204.1044,203.7996,3,1,-1,-1,20,93000,180,"��ɫ")
								x270006_g_heshang3=CreateMonster(sceneId, 3822,204.2675,206.7597,3,1,-1,-1,20,93000,180,"��˼")
								x270006_g_heshang4=CreateMonster(sceneId, 3822,204.3732,208.2915,3,1,-1,-1,20,93000,180,"�տ�")
								x270006_g_zhangsanfeng=CreateMonster(sceneId, 3802,214.1412,217.6203,3,1,-1,-1,20,93000,180,"������")
								x270006_g_fenglingshitai=CreateMonster(sceneId, 3806,213.0141,217.4029,3,1,-1,-1,20,93000,180,"����ʦ̫")
								x270006_g_hezudao=CreateMonster(sceneId, 3804,215.0514,218.4295,3,1,-1,-1,20,93000,180,"�����")
								if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
										SetPatrolId(sceneId, x270006_g_jiazhizhang, 1)
								end
								if IsObjValid (sceneId,x270006_g_heshang1) == 1 then
										SetPatrolId(sceneId, x270006_g_heshang1, 3)
								end
								if IsObjValid (sceneId,x270006_g_heshang2) == 1 then
										SetPatrolId(sceneId, x270006_g_heshang2, 2)
								end
								if IsObjValid (sceneId,x270006_g_heshang3) == 1 then
										SetPatrolId(sceneId, x270006_g_heshang3, 4)
								end
								if IsObjValid (sceneId,x270006_g_heshang4) == 1 then
										SetPatrolId(sceneId, x270006_g_heshang4, 5)
								end
								if IsObjValid (sceneId,x270006_g_zhangsanfeng) == 1 then
										SetPatrolId(sceneId, x270006_g_zhangsanfeng, 6)
								end
								if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
										SetPatrolId(sceneId, x270006_g_fenglingshitai, 7)
								end
								if IsObjValid (sceneId,x270006_g_hezudao) == 1 then
										SetPatrolId(sceneId, x270006_g_hezudao, 8)
								end
								x270006_g_guoponu =FindMonsterByGUID( sceneId,136264)
								x270006_g_dingshangyi =FindMonsterByGUID( sceneId,136266)
								x270006_g_wangshisan =FindMonsterByGUID( sceneId,136267)
								x270006_g_lengxiaoqi =FindMonsterByGUID( sceneId,136268)
								x270006_g_lixuanyi =FindMonsterByGUID( sceneId,136265)
						end
					end
				else
					Msg2Player(sceneId, selfId, "������ʱ�޷����ܣ�", 0, 3)
				end

	 	end                                                                    
	     
end
--**********************************

function x270006_ProcQuestAbandon(sceneId, selfId, MissionId)
		if IsHaveQuest(sceneId,selfId, x270006_g_MissionId) <= 0 then
				return 
		end
		DelQuest(sceneId, selfId, x270006_g_MissionId)
	  x270006_Msg2toplayer( sceneId, selfId,1)
			
end
--**********************************
function x270006_CheckPlayerBagFull( sceneId ,selfId,selectRadioId )
	local result = 1
	local j = 0
	local bAdd = 0 --�Ƿ��Ѿ��ڹ̶���Ʒ������Ӽ�����Ѿ�������������
	BeginAddItem(sceneId)
	for j, item in x270006_g_BonusItem do
		AddItem( sceneId, item.item, item.n )
  end
  for j, item in x270006_g_BonusChoiceItem do
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
function x270006_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
	if IsHaveQuest(sceneId,selfId, x270006_g_MissionId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270006_CheckSubmit( sceneId, selfId, NPCId) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�дﵽ���������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif x270006_CheckPlayerBagFull( sceneId ,selfId,selectRadioId ) <= 0 then
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"����������")
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				return 0
	elseif DelQuest(sceneId, selfId, x270006_g_MissionId) > 0 then
				x270006_Msg2toplayer( sceneId, selfId,2)
				QuestCom(sceneId, selfId, x270006_g_MissionId)
				x270006_GetBonus( sceneId, selfId,NPCId)
				BeginAddItem(sceneId)
				for i, item in x270006_g_BonusItem do
 						AddItem( sceneId, item.item, item.n )
				end
				for i, item in x270006_g_BonusChoiceItem do
						if item.item == selectRadioId then
	    			    AddItem( sceneId, item.item, item.n )
						end
    		end
    		EndAddItem(sceneId,selfId)
    		--AddItemListToPlayer(sceneId,selfId)
   end
   CallScriptFunction( MISSION_SCRIPT, "ProcEventEntry", sceneId, selfId, NPCId, x270006_g_MissionIdNext )	
end

function x270006_GetBonus( sceneId, selfId,NpcID)
	  if x270006_g_ExpBonus > 0 then
			AddExp(sceneId, selfId, x270006_g_ExpBonus);
  	end
		if x270006_g_BonusMoney1 > 0 then
	    AddMoney( sceneId, selfId, 1, x270006_g_BonusMoney1 )
	  end
		if x270006_g_BonusMoney2 > 0 then
	    AddMoney( sceneId, selfId, 0, x270006_g_BonusMoney2 )
	  end
		if x270006_g_BonusMoney3 > 0 then
	    AddMoney( sceneId, selfId, 3, x270006_g_BonusMoney3 )
		end
		if x270006_g_BonusMoney4 > 0 then
		local nRongYu = GetRongYu( sceneId, selfId )
			nRongYu = nRongYu + x270006_g_BonusMoney4
			SetRongYu( sceneId, selfId, nRongYu )
		end
		if x270006_g_BonusMoney5 > 0 then
			local nShengWang = GetShengWang( sceneId, selfId )
			nShengWang = nShengWang + x270006_g_BonusMoney5
			SetShengWang( sceneId, selfId, nShengWang )
		end
		if x270006_g_BonusMoney6 > 0 then
			AddHonor(sceneId,selfId,x270006_g_BonusMoney6)
		end
end

function x270006_Msg2toplayer( sceneId, selfId,type)
		if type == 0 then
				Msg2Player(sceneId, selfId, "������������"..x270006_g_MissionName.."��", 0, 2)
		  	Msg2Player(sceneId, selfId, "������������"..x270006_g_MissionName.."��", 0, 3)
		elseif type == 1 then
				Msg2Player(sceneId, selfId, "������������"..x270006_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "������������"..x270006_g_MissionName.."��", 0, 3)
		elseif type == 2 then
				Msg2Player(sceneId, selfId, "�����������"..x270006_g_MissionName.."��", 0, 2)
				Msg2Player(sceneId, selfId, "�����������"..x270006_g_MissionName.."��", 0, 3)
				if x270006_g_ExpBonus > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270006_g_ExpBonus.."#Y�Ľ���", 0, 2)
  			end
				if x270006_g_BonusMoney1 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270006_g_BonusMoney1.."��#Y�Ľ���", 0, 2)
	  		end
				if x270006_g_BonusMoney2 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R����"..x270006_g_BonusMoney2.."��#Y�Ľ���", 0, 2)
	  		end
				if x270006_g_BonusMoney3 > 0 then
	  		  Msg2Player(sceneId, selfId, "#Y���#R��"..x270006_g_BonusMoney3.."��#Y�Ľ���", 0, 2)
				end
				if x270006_g_BonusMoney4 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R��͢����ֵ"..x270006_g_BonusMoney4.."#Y�Ľ���", 0, 2)
				end
				if x270006_g_BonusMoney5 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270006_g_BonusMoney5.."#Y�Ľ���", 0, 2)
				end
				if x270006_g_BonusMoney6 > 0 then
					Msg2Player(sceneId, selfId, "#Y���#R����"..x270006_g_BonusMoney6.."#Y�Ľ���", 0, 2)
				end
		end
end

function x270006_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)
end


function x270006_ProcAreaEntered(sceneId, selfId, zoneId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "ProcAreaEntered",sceneId, selfId, zoneId, MissionId )	

end

function x270006_ProcTiming(sceneId, selfId, ScriptId, MissionId)
	 CallScriptFunction( MISSION_SCRIPT, "ProcTiming",sceneId, selfId, ScriptId, MissionId )
		
end

function x270006_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcAreaLeaved",sceneId, selfId, ScriptId, MissionId)
end

function x270006_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	CallScriptFunction( MISSION_SCRIPT, "ProcQuestItemChanged",sceneId, selfId, itemdataId, MissionId )
end


function x270006_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	  
end

function x270006_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x270006_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x270006_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x270006_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x270006_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x270006_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end

function x270006_OnScneneTimer(sceneId)
	if x270006_g_doing==1   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 9   then
						x270006_g_doing = 2
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "��������ƶɮ������", -1)
						end
		end
	elseif x270006_g_doing==2   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 12   then
						x270006_g_doing = 3
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "������ʦ��������ĳҲҪȥ�ݷá�", -1)
						end
		end
	elseif x270006_g_doing==3   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 15   then
						x270006_g_doing = 4
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "������������������ȷ����ؤ����Ϊ��", -1)
						end
		end
	elseif x270006_g_doing==4   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 18   then
						x270006_g_doing = 5
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "��������֤�ݶ�ָ��ؤ�ϣ����������һ�������˵����", -1)
						end
		end
	elseif x270006_g_doing==5   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 22   then
						x270006_g_doing = 6
						if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
								NpcTalk(sceneId, x270006_g_fenglingshitai, "ʲô˵������֤��ɽ������ͽ��������", -1)
						end
		end
	elseif x270006_g_doing==6   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 25   then
						x270006_g_doing = 7
						if IsObjValid (sceneId,x270006_g_dingshangyi) == 1 then
								NpcTalk(sceneId, x270006_g_dingshangyi, "ʲô��ͽ��������˵�����Ļ������������ģ�", -1)
						end
		end
	elseif x270006_g_doing==7   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 28   then
						x270006_g_doing = 8
						if IsObjValid (sceneId,x270006_g_zhangsanfeng) == 1 then
								NpcTalk(sceneId, x270006_g_zhangsanfeng, "ʦ̫�侲��ƶ��Ҳ�����������Σ��ù�����������˵���װɡ�", -1)
						end
            x270006_g_chenyouliang=CreateMonster(sceneId, 28,219.5403,195.8635,3,1,-1,-1,20,50000,180,"������")
            if IsObjValid (sceneId,x270006_g_chenyouliang) == 1 then
            		SetPatrolId(sceneId, x270006_g_chenyouliang, 9)
            end
		end
	elseif x270006_g_doing==8   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 31   then
						x270006_g_doing = 9
						if IsObjValid (sceneId,x270006_g_chenyouliang) == 1 then
								NpcTalk(sceneId, x270006_g_chenyouliang, "����������ؤ�Ｘ���ֶ��⵽�䵱����ü�����ص��ɵ�Ϯ����", -1)
						end
		end
	elseif x270006_g_doing==9   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 33   then
						x270006_g_doing = 10
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "����", -1)
						end
						if IsObjValid (sceneId,x270006_g_zhangsanfeng) == 1 then
								NpcTalk(sceneId, x270006_g_zhangsanfeng, "����", -1)
						end
						if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
								NpcTalk(sceneId, x270006_g_fenglingshitai, "����", -1)
						end
						if IsObjValid (sceneId,x270006_g_hezudao) == 1 then
								NpcTalk(sceneId, x270006_g_hezudao, "����", -1)
						end
						if IsObjValid (sceneId,x270006_g_dingshangyi) == 1 then
								NpcTalk(sceneId, x270006_g_dingshangyi, "����", -1)
						end
						if IsObjValid (sceneId,x270006_g_wangshisan) == 1 then
								NpcTalk(sceneId, x270006_g_wangshisan, "����", -1)
						end
						if IsObjValid (sceneId,x270006_g_lengxiaoqi) == 1 then
								NpcTalk(sceneId, x270006_g_lengxiaoqi, "����", -1)
						end
						if IsObjValid (sceneId,x270006_g_lixuanyi) == 1 then
								NpcTalk(sceneId, x270006_g_lixuanyi, "����", -1)
						end
		end
	elseif x270006_g_doing==10   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 35   then
						x270006_g_doing = 11
						if IsObjValid (sceneId,x270006_g_lixuanyi) == 1 then
								NpcTalk(sceneId, x270006_g_lixuanyi, "ԭ�����Ǿ�����ͼ������ؤ��ã��Ǿ����ɣ�", -1)
						end
		end
	elseif x270006_g_doing==11   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 36   then
						x270006_g_doing = 12
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "�����£����¿ɵ��棿", -1)
						end
		end
	elseif x270006_g_doing==12   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 37   then
						x270006_g_doing = 13
						if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
								NpcTalk(sceneId, x270006_g_fenglingshitai, "���Ǳ�ת�����ߣ��������˵�����", -1)
						end
		end
	elseif x270006_g_doing==13   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 40   then
						x270006_g_doing = 14
						if IsObjValid (sceneId,x270006_g_lixuanyi) == 1 then
								NpcTalk(sceneId, x270006_g_lixuanyi, "˵ʲô˵�����۸������ſ��ˣ�", -1)
						end
		end
	elseif x270006_g_doing==14   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 43   then
						x270006_g_doing = 15
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "��Ȼؤ����˲���ϣ�����ֻ����Ϊ��Щ������ؤ����Ϊ�ˣ�", -1)
						end
            x270006_g_zhenzhizhang=CreateMonster(sceneId, 31,216,202,3,1,-1,-1,20,44000,90,"������ʦ")
		end
	elseif x270006_g_doing==15   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 47   then
						x270006_g_doing = 16
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "�������գ�ʩ�������������سɷ�", -1)
						end
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
            		SetMonsterDir(sceneId,x270006_g_jiazhizhang,270)
            end
		end
	elseif x270006_g_doing==16   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 50   then
						x270006_g_doing = 17
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "���Ȼ�����ˣ���������ˣ���", -1)
						end
		end
	elseif x270006_g_doing==17   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 53   then
						x270006_g_doing = 18
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "ƶɮ������Ϊһ��֮˽����ؤ���ɴ˴��裡ͽ���ǣ��Բ���", -1)
						end
		end
	elseif x270006_g_doing==18   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 56   then
						x270006_g_doing = 19
						if IsObjValid (sceneId,x270006_g_heshang1) == 1 then
								NpcTalk(sceneId, x270006_g_heshang1, "�����ӷ�", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang2) == 1 then
								NpcTalk(sceneId, x270006_g_heshang2, "�����ӷ�", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang3) == 1 then
								NpcTalk(sceneId, x270006_g_heshang3, "�����ӷ�", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang4) == 1 then
								NpcTalk(sceneId, x270006_g_heshang4, "�����ӷ�", -1)
						end
		end
	elseif x270006_g_doing==19   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 60   then
						x270006_g_doing = 20
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "վ��������ǰ�Ĳ���������ʦ��������ħ�̵Ľ�����", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang1) == 1 then
            		SendSpecificImpactToUnit(sceneId, x270006_g_heshang1, x270006_g_heshang1, x270006_g_heshang1, 3060, 0);
            end
		end
	elseif x270006_g_doing==20   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 64   then
						x270006_g_doing = 21
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "һ����ǰ��������ɮ�˶����˶���������������Ժ�����ҵ������ٿ������ִ�ᡣ", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang2) == 1 then
            		SendSpecificImpactToUnit(sceneId, x270006_g_heshang2, x270006_g_heshang2, x270006_g_heshang2, 3060, 0);
            end
		end
	elseif x270006_g_doing==21   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 68   then
						x270006_g_doing = 22
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "����Ŀ�ľ��ǳ�Ϊ�����������������޻�ؤ���������ַ�����", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang3) == 1 then
            		SendSpecificImpactToUnit(sceneId, x270006_g_heshang3, x270006_g_heshang3, x270006_g_heshang3, 3060, 0);
            end
		end
	elseif x270006_g_doing==22   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 72   then
						x270006_g_doing = 23
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "ƶɮ����������ǹ��ŵ�������һֱ���ܳ����������Ļ��ԡ�", -1)
						end
						if IsObjValid (sceneId,x270006_g_heshang4) == 1 then
            		SendSpecificImpactToUnit(sceneId, x270006_g_heshang4, x270006_g_heshang4, x270006_g_heshang4, 3060, 0);
            end
		end
	elseif x270006_g_doing==23   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 75   then
						x270006_g_doing = 24
						if IsObjValid (sceneId,x270006_g_jiazhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_jiazhizhang, "��������������ǰ�о���Σ����ϣ���Ҫ���㸶�����ۣ�", -1)
						end
		end
	elseif x270006_g_doing==24   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 78   then
						x270006_g_doing = 25
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "��������ƶɮ���������ˣ�", -1)
						end
		end
	elseif x270006_g_doing==25   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 81   then
						x270006_g_doing = 26
						if IsObjValid (sceneId,x270006_g_guoponu) == 1 then
								NpcTalk(sceneId, x270006_g_guoponu, "��ʦ���������ĳ�����֣���ȥ����ͽ�ܵ�����ɣ��˼��½�����ĳ����", -1)
						end
		end
	elseif x270006_g_doing==26   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 84   then
						x270006_g_doing = 27
						if IsObjValid (sceneId,x270006_g_zhenzhizhang) == 1 then
								NpcTalk(sceneId, x270006_g_zhenzhizhang, "��л��������ƶɮ�ȸ���ˣ�", -1)
						end
		end
	elseif x270006_g_doing==27   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 87   then
						x270006_g_doing = 28
						if IsObjValid (sceneId,x270006_g_zhangsanfeng) == 1 then
								NpcTalk(sceneId, x270006_g_zhangsanfeng, "���������ҵ���������£��������в�ǲ�ҵȱظ������𣬸�ǣ�", -1)
						end
		end
	elseif x270006_g_doing==28   then
		if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 90   then
						x270006_g_doing = 29
						if IsObjValid (sceneId,x270006_g_fenglingshitai) == 1 then
								NpcTalk(sceneId, x270006_g_fenglingshitai, "��ǣ�", -1)
						end
						if IsObjValid (sceneId,x270006_g_hezudao) == 1 then
								NpcTalk(sceneId, x270006_g_hezudao, "��ǣ�", -1)
						end
		end
	elseif x270006_g_doing==29 then
			if GetCurrentTime() - x270006_g_PROTECTINFO.StartTime >= 92   then
				if IsPlayerStateNormal(sceneId,x270006_g_acceptid) ==1 then
					if IsHaveQuest(sceneId,x270006_g_acceptid, x270006_g_MissionId) > 0 then
						local nPlayerX, nPlayerZ = GetWorldPos(sceneId, x270006_g_acceptid)
						local distance1 = floor(sqrt((216-nPlayerX)*(216-nPlayerX)+(206-nPlayerZ)*(206-nPlayerZ)))
						if distance1 <= 20 then
									local misIndex = GetQuestIndexByID(sceneId, x270006_g_acceptid, x270006_g_MissionId)
									SetQuestByIndex(sceneId,x270006_g_acceptid,misIndex,0,1)
									SetQuestByIndex(sceneId,x270006_g_acceptid,misIndex,7,1)
									BeginQuestEvent(sceneId)
									AddQuestText(sceneId,format("Ū����������   %d/1", GetQuestParam(sceneId,x270006_g_acceptid,misIndex,0) ))
									EndQuestEvent(sceneId)
									DispatchQuestTips(sceneId,x270006_g_acceptid)
						end
					end
				end
				x270006_g_doing=30
				x270006_CloseTimer(sceneId, x270006_g_PROTECTINFO.ScneneTimerIndex)
			end
	end
end


--**********************************
--�رռ�ʱ��
--**********************************
function x270006_CloseTimer( sceneId, TimerIndex )
	StopTimer(sceneId, TimerIndex)
	x270006_g_doing =0
	x270006_g_acceptid =-1
	x270006_g_jiazhizhang = -1
	x270006_g_guoponu = -1
	x270006_g_heshang1 = -1
	x270006_g_heshang2 =-1
	x270006_g_heshang3 = -1
	x270006_g_heshang4 = -1
	x270006_g_zhangsanfeng = -1
	x270006_g_fenglingshitai = -1
	x270006_g_hezudao = -1
	x270006_g_chenyouliang = -1
	x270006_g_zhenzhizhang = -1
	x270006_g_dingshangyi = -1
	x270006_g_wangshisan = -1
	x270006_g_lengxiaoqi = -1
	x270006_g_lixuanyi = -1
	x270006_g_PROTECTINFO={ScneneTimerIndex = -1,  StartTime = 0}
	
end