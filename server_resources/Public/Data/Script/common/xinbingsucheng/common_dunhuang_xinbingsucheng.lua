

x310223_g_LevelMax					= 40

x310223_g_GameId					= 1023
x310223_g_NeedMoney					= 2000

--MisDescBegin

x310223_g_ScriptId 					= 	310223                  --�ű�ID

x310223_g_LevelLess					= 	25                      --�������ŵȼ�  <=0 ��ʾ������


x310223_g_MissionName				= 	"�±��ٳ�"

x310223_g_MaxKillNum				= 20

x310223_g_MaxCount					= 5


--MisDescEnd


function x310223_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	-- local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	-- if maxlevel < 60 then
		-- return
	-- end
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then
		local  missionState = GetQuestStateNM(sceneId, selfId, targetId, MissionId)
	AddQuestTextNM(sceneId, selfId, targetId, MissionId, missionState);
	end
	
end

--ѡ������
function x310223_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	if GetGameOpenById(x310223_g_GameId) ~= 1 then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�������ȼ���һ���ﵽ65�����ſɿ����±��ٳ�����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�������ȼ���һ���ﵽ65�����ſɿ����±��ٳ�����",8,2)	
		return
	end
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������

		x310223_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
		--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
	
	else --������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local killcount = GetQuestParam(sceneId, selfId, misIndex, 0)
		if killcount == x310223_g_MaxKillNum then
			x310223_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
		else
			x310223_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
		end
	end
end


--��������
function x310223_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ������������ֱ���˳�
		return 0
	end
	local  WorldID = GetWorldID(sceneId,selfId)
	local  toplevel = GetToplistCount(WorldID,0)
	local  guid,LevelMax = GetToplistInfo(WorldID,0,toplevel-1)
	if GetLevel(sceneId, selfId) < x310223_g_LevelLess then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "��ȼ����ͣ�������ȡ����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"��ȼ����ͣ�������ȡ����",8,2)
		return 0
	end

	if GetLevel(sceneId, selfId) > ( LevelMax-10) then
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "��ȼ����ߣ�������ȡ����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"��ȼ����ߣ�������ȡ����",8,2)
		return 0
	end 

	local daycount = x310223_GetDayCount(sceneId, selfId)
	if daycount >= x310223_g_MaxCount then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "ÿ��ֻ�ܽ�ȡ��δ���������������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	
	--local daycount = x310223_GetDayCount(sceneId, selfId)	
	if daycount > 0 then
		if IsEnoughGold(sceneId, selfId,x310223_g_NeedMoney) < 1 then
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "��Ľ�Ǯ���㣬�޷���ȡ����");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"��Ľ�Ǯ���㣬�޷���ȡ����",8,2)
			return 0
		end
	end

	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) -- ��ȡ������������Ϣ
	if ret > 0 then -- ������Խ��������
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������
		if ret > 0 then
			x310223_ProcQuestLogRefresh( sceneId, selfId, MissionId)
			if daycount > 0 then
				
				local goldMode = GetGoldMode(sceneId, selfId)
				
				if goldMode == 1 then
					local cash = GetMoney(sceneId, selfId,2)
					if cash >= x310223_g_NeedMoney then
						CostMoney(sceneId, selfId, 2, x310223_g_NeedMoney,322)
					end
				else
					local cash = GetMoney(sceneId, selfId,2)
					local bind = GetMoney(sceneId, selfId,3)
					if bind >= x310223_g_NeedMoney then
						CostMoney(sceneId, selfId, 3, x310223_g_NeedMoney)
					elseif cash >= x310223_g_NeedMoney then
						CostMoney(sceneId, selfId, 2, x310223_g_NeedMoney,322)
					end
				end
			end

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "������������:�����ˡ��±��ٳ�");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"������������:�����ˡ��±��ٳ�",8,2)
                        GamePlayScriptLog(sceneId, selfId, 1301)
			return 1
		elseif ret == -2 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "�����������޷���������");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0
		else
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "�����������");
			EndQuestEvent();		
			DispatchQuestTips(sceneId, selfId);
			return 0
		end
	elseif ret ==-1 then  --�ȼ�����
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "��ȼ����ͣ����ܽ�������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	elseif ret ==-2 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�������ȼ�����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	end

	return 0
end


--�������
function x310223_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end
    
	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- ��ȡ���������Ϣ
	if ret == 1 then -- ����ɹ����
		x310223_SetDayCount(sceneId, selfId)
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�����������:�����ˡ��±��ٳ�");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�����������:�����ˡ��±��ٳ�",8,2)

		x310223_GiveReward(sceneId,selfId)
		
		x310223_SetFirst(sceneId, selfId)
		
        GamePlayScriptLog(sceneId, selfId, 1302)
		--DelQuestNM( sceneId, selfId, MissionId )
		return 1 -- ���سɹ�
	else -- ���δ�ɹ����
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "����������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	return 0
end

function x310223_GiveReward(sceneId,selfId)

	local nExpBonus = x310223_GetExp( sceneId, selfId )
	
	AddExp(sceneId, selfId, nExpBonus)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	Msg2Player(sceneId,selfId,"#o���#R����"..nExpBonus.."��#o�Ľ���",4,2)
end


function x310223_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
		
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local submitGuid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	if npcGuid == submitGuid then	--�����NPC�����ֺ�������NPC��������ͬ������Ҳ�жϹ���
		local missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
		AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
	end
end

 

--********************************************************************
--����
--********************************************************************
function x310223_ProcQuestAbandon( sceneId, selfId,MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return -1;
	end

	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		x310223_SetFirst(sceneId, selfId)
		x310223_SetDayCount(sceneId, selfId)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "������������:�����ˡ��±��ٳ�");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"������������:�����ˡ��±��ٳ�",8,2)
	end
end

--ɱ������
function x310223_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	local ObjName = GetName(sceneId, objId)

	local HumenNum = GetMonsterOwnerCount( sceneId, objId ) --ȡ�������������ӵ�з���Ȩ������
		for i = 0, HumenNum-1 do
				local humanObjId = GetMonsterOwnerID( sceneId, objId, i ) --ȡ��ӵ�з���Ȩ���˵�objId
				
				if humanObjId ~= -1 then
					if  GetLevel(sceneId, humanObjId) - GetLevel(sceneId, objId) <= 5 then
					if  GetHp(sceneId, humanObjId) > 0 then
				    if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
						local strText = "";
						local misIndex = GetQuestIndexByID( sceneId, humanObjId, MissionId )
						local KilledNum = GetQuestParam( sceneId, humanObjId, misIndex, 0 )
										
					    if KilledNum == x310223_g_MaxKillNum-1 then
						    SetQuestByIndex( sceneId, humanObjId, misIndex, 0, KilledNum+1 )
											SetQuestByIndex( sceneId, humanObjId, misIndex, 7, 1 )
											BeginQuestEvent(sceneId)
											if ObjName == "" then
												strText = format( "#cffcf00�����ˡ��±��ٳɣ��������˹���(%d/%d)", KilledNum+1, x310223_g_MaxKillNum )
											else
												strText = format( "#cffcf00�����ˡ��±��ٳɣ���������%s(%d/%d)", ObjName, KilledNum+1, x310223_g_MaxKillNum )
											end
											AddQuestText( sceneId, strText )
											EndQuestEvent( sceneId )
											DispatchQuestTips( sceneId, humanObjId )
											x310223_ProcQuestLogRefresh( sceneId, humanObjId, MissionId)
									elseif KilledNum < x310223_g_MaxKillNum-1 then
											SetQuestByIndex( sceneId, humanObjId, misIndex, 0, KilledNum+1 )
											BeginQuestEvent(sceneId)
											if ObjName == "" then
												strText = format( "#cffcf00�����ˡ��±��ٳɣ��������˹���(%d/%d)", KilledNum+1, x310223_g_MaxKillNum )
											else
												strText = format( "#cffcf00�����ˡ��±��ٳɣ���������%s(%d/%d)", ObjName, KilledNum+1, x310223_g_MaxKillNum )
											end
											AddQuestText( sceneId, strText )
											EndQuestEvent( sceneId )
											DispatchQuestTips( sceneId, humanObjId )
											x310223_ProcQuestLogRefresh( sceneId, humanObjId, MissionId)
					    end
				    end
				    end
				    end
				end
				
				
		end

	
end

--��Ʒ�ı�
function x310223_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	return 0
end
---------------------------------------------------------------------------------------------------
--���������ܽ��
---------------------------------------------------------------------------------------------------
function x310223_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

function x310223_GetCost(sceneId, selfId)
	local daycount =x310223_GetDayCount(sceneId,selfId)
	if daycount > 0 then
		return 2000
	end
	return 0
end
---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x310223_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)
	local awardexp = x310223_GetExp( sceneId, selfId )
	
	BeginQuestEvent(sceneId)

	AddQuestText(sceneId,"#Y�����ˡ��±��ٳ�")
	--������Ϣ
	
	AddQuestText(sceneId,"   ���ȼ����а��һ���ﵽ#R65��#Wʱ���Ὺ���±��ٳ�����������Ĺ�֮���ì�ܽ��������ˣ�����Ҫ�����ʿ�����������ǵĹ��ҡ�������ѵ���±���Ҫ����һЩ��Ǯ�������Ը���Ը����õĻ����ҿ��԰�����Ѹ�ٱ��һ��ѵ�����ص�ʿ����\n\t����ȼ��������5�����ϵ�20ֻ�����Ϳ�������±���ѵ����")
	AddQuestText(sceneId," ")

	--����Ŀ��
	AddQuestText( sceneId,"#Y����Ŀ�꣺")
	AddQuestText( sceneId,"   ����ȼ��������5�����ϵ�20ֻ�����Ϳ�������±���ѵ����")
	 AddQuestText( sceneId, "\n#Y���񻨷ѣ�" )
        local cost = x310223_GetCost(sceneId, selfId)
        AddQuestText( sceneId, format( "��:#{_MONEY%d}", cost) )
	AddQuestText( sceneId,"   \n#GС��ʾ��\nÿ�������ȡ����±��ٳ����������������ҵȼ�Խ�ߣ���õľ���Ҳ��Խ�ࡣ���ڿ�����ȡ������ĵȼ�����Ϊ25�����ȼ�����Ϊ���ڵȼ����а�����͵ȼ�10����ÿ���һ����ȡ��������ѡ�")
	AddQuestText( sceneId," ")
	--AddQuestText(sceneId,"#Y��������")
	--AddQuestText(sceneId,"  ����ֵ��"..awardexp)
	--AddQuestText(sceneId," ")
	AddQuestExpBonus(sceneId,  awardexp);
			
	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x310223_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x310223_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	--local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	--local awardexp = 0
	--if maxlevel > 0 then
		--awardexp = maxlevel*16000
	--end
	
	BeginQuestEvent(sceneId)

	AddQuestText(sceneId,"#Y�����ˡ��±��ٳ�")
	--������Ϣ
	
	AddQuestText(sceneId,"   ʱ����ȣ��㻹�ǿ�ȥɱ�ְɡ�")
	AddQuestText(sceneId," ")

	--AddQuestText(sceneId,"#Y��������")
	--AddQuestText(sceneId,"  ����ֵ��"..awardexp)
	--AddQuestText(sceneId," ")
	--AddQuestExpBonus(sceneId,  awardexp);
			
	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x310223_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x310223_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local awardexp = x310223_GetExp( sceneId, selfId )
	
	BeginQuestEvent(sceneId)

	AddQuestText(sceneId,"#Y�����ˡ��±��ٳ�")
	--������Ϣ
	
	AddQuestText(sceneId,"   �ܺã��㱻֤����һ���ϸ���±���")
	AddQuestText(sceneId," ")

	--AddQuestText(sceneId,"  ����ֵ��"..awardexp)
	--AddQuestText(sceneId," ")
	AddQuestExpBonus(sceneId,  awardexp);
			
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x310223_g_ScriptId, MissionId);

end

function x310223_ProcQuestLogRefresh( sceneId, selfId, MissionId)

	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local killcount = GetQuestParam(sceneId, selfId, misIndex, 0);

	local str = "  ����20ֻ�ȼ��ʵ��Ĺ���("..killcount.."/"..tostring(x310223_g_MaxKillNum)..")";	
	BeginQuestEvent(sceneId)	
		local awardexp = x310223_GetExp( sceneId, selfId )

		AddQuestExpBonus(sceneId,  awardexp);
			
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							"�����ˡ��±��ٳ�",        -- ��������
							str,		--����Ŀ��
							"@npc_132164",			--����NPC
							"�����������Ͽ��Ը�����������",               --������
							"������Ĺ�֮���ì�ܽ��������ˣ�����Ҫ�����ʿ�����������ǵĹ��ҡ�������ѵ���±���Ҫ����һЩ��Ǯ�������Ը���Ը����õĻ����ҿ��԰�����Ѹ�ٱ��һ��ѵ�����ص�ʿ��������ȼ��������5�����ϵ�20ֻ�����Ϳ�������±���ѵ����",	--��������
							"ÿ�������ȡ����±��ٳ����������������ҵȼ�Խ�ߣ���õľ���Ҳ��Խ�ࡣ���ڿ�����ȡ������ĵȼ�����Ϊ25�����ȼ�����Ϊ���ڵȼ����а�����͵ȼ�10����ÿ���һ����ȡ��������ѡ�"					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		
	
end

---------------------------------------------------------------------------------------------------
--ȡ�ô������쵱ǰ����ɴ���
---------------------------------------------------------------------------------------------------
function x310223_GetDayCount(sceneId, selfId)
	if x310223_g_MaxCount > 0 then
		local today = GetDayOfYear()
		local lastday = GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATE[1], MD_XINBINGSUCHENG_DATE[2], MD_XINBINGSUCHENG_DATE[3])
		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATECOUNT[1], MD_XINBINGSUCHENG_DATECOUNT[2], MD_XINBINGSUCHENG_DATECOUNT[3])
		return daycount

	end
	return 0
end

---------------------------------------------------------------------------------------------------
--���µ�����������
---------------------------------------------------------------------------------------------------
function x310223_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATE[1], MD_XINBINGSUCHENG_DATE[2], MD_XINBINGSUCHENG_DATE[3])
	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATE[1], MD_XINBINGSUCHENG_DATE[2], MD_XINBINGSUCHENG_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATECOUNT[1], MD_XINBINGSUCHENG_DATECOUNT[2], MD_XINBINGSUCHENG_DATECOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATECOUNT[1], MD_XINBINGSUCHENG_DATECOUNT[2], MD_XINBINGSUCHENG_DATECOUNT[3])
		SetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_DATECOUNT[1], MD_XINBINGSUCHENG_DATECOUNT[2], MD_XINBINGSUCHENG_DATECOUNT[3], daycount+1)
	end
end

function x310223_GetFirst(sceneId, selfId)
	return GetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_FIRST[1], MD_XINBINGSUCHENG_FIRST[2], MD_XINBINGSUCHENG_FIRST[3])
end

function x310223_SetFirst(sceneId, selfId)
	SetQuestData(sceneId, selfId, MD_XINBINGSUCHENG_FIRST[1], MD_XINBINGSUCHENG_FIRST[2], MD_XINBINGSUCHENG_FIRST[3], 1)
end

function x310223_GetExp( sceneId, selfId )
	local level = GetLevel(sceneId, selfId)
	local maxlevel = GetTopListInfo_MaxLevel(GetWorldID(sceneId, selfId))
	local awardexp = 0
	if maxlevel > 0 then
		awardexp = maxlevel*129600
	end
	return awardexp
end