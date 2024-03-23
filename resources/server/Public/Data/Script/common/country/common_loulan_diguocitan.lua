
--�й�����
 
--MisDescBegin



--MisDescBegin

x300732_g_ScriptId 					= 	300732                  --�ű�ID


x300732_g_MissionKind 				= 	1                       --��������
x300732_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������





x300732_g_MissionName				= 	"�й�����"
x300732_g_MissionTarget				= 	""
x300732_g_MissionInfo				= 	""
x300732_g_ContinueInfo				= 	""
x300732_g_MissionCompleted			= 	""
x300732_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300732_g_ExtTarget					=	{ {type=20,n=1,target="ɱ�����峣"}}

--����

x300732_g_ExpBonus					= 	0;--x300732_AddExpAward               	--����������
x300732_g_BonusItem					=	{}	--��������Ʒ

x300732_g_BonusMoney1               = 	0
x300732_g_BonusMoney2               =   0
x300732_g_BonusMoney3               =   0

x300732_g_BonusChoiceItem           =   {}


--MisDescEnd

x300732_g_CountryDunhuang = 351 --�ĸ����ҵĳ���id
x300732_g_CountryLoulan = 51
x300732_g_CountryKunlun = 251
x300732_g_CountryLaiyin = 151

x300732_g_MissionId1 = 7579		-- �ػ�
x300732_g_MissionId2 = 7561		-- ¥��
x300732_g_MissionId3 = 7573		-- ����
x300732_g_MissionId4 = 7567		-- ��ɽ

x300732_g_DayCountLimited			= 1


x300732_g_MissionBonusInfo			= 	"#Y��þ���#R%d#Y�Ľ�����"

function x300732_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
end

--ѡ������
function x300732_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )

	if index ~= -1 then
		MissionId = index
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- ������Խ��������
			--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
			x300732_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
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
	else --������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		--if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- �������������
		if x300732_IsSuccessed( sceneId, selfId, MissionId )>0 then
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
			x300732_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
			x300732_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
end


--��������
function x300732_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ������������ֱ���˳�
		return 0
	end

	if	IsHaveQuestNM( sceneId, selfId, x300732_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300732_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300732_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300732_g_MissionId4 ) > 0 then
		BeginQuestEvent(sceneId)
		local strText = "���Ѿ��ӹ��ˡ����ҡ��й��������񣬻�δ��ɣ������ٽ�ȡ��"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		Msg2Player(sceneId,selfId,"���Ѿ��ӹ��ˡ����ҡ��й��������񣬻�δ��ɣ������ٽ�ȡ��",8,2)
		return
	end

	local nDayCount =0;

	if MissionId == x300732_g_MissionId1 then
		nDayCount = x300732_GetDayCount(sceneId, selfId, DQ_CITAN_DUNHUANG_DATE,DQ_CITAN_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId2 then
		nDayCount = x300732_GetDayCount(sceneId, selfId, DQ_CITAN_LOULAN_DATE,DQ_CITAN_LOULAN_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId3 then
		nDayCount = x300732_GetDayCount(sceneId, selfId, DQ_CITAN_KUNLUN_DATE,DQ_CITAN_KUNLUN_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId4 then
		nDayCount = x300732_GetDayCount(sceneId, selfId, DQ_CITAN_LAIYIN_DATE,DQ_CITAN_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	if nDayCount>=x300732_g_DayCountLimited then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "���մ�������1�Σ�����������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0;
	end
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
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

	
	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId ) -- ��ȡ������������Ϣ
	if ret > 0 then -- ������Խ��������
	
		--------------------------- add for Mission full check --------------
		local bFullMission = IsQuestFullNM(sceneId,selfId)
		
		if bFullMission>0 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "�����������޷���������");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			return 0
		end
		---------------------------- add end -------------------------------
		
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������
		
		if ret > 0 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "������������:�����ҡ��й�����");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"������������:�����ҡ��й�����",8,2)
			return 1
		else
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "�����������");
			EndQuestEvent();		
			DispatchQuestTips(sceneId, selfId);
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
--����1����ɹ���0��������ʧ��
function x300732_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local ret = x300732_IsSuccessed( sceneId, selfId, MissionId ); --QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
	if ret > 0 then -- ����������
		
		return x300732_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	end
	return 0
end

--�������
function x300732_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end

    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end

	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- ��ȡ���������Ϣ
	if ret == 1 then -- ����ɹ����
		--��ʾ����������
		if MissionId == x300732_g_MissionId1 then
			x300732_SetDayCount(sceneId, selfId, DQ_CITAN_DUNHUANG_DATE,DQ_CITAN_DUNHUANG_DAYCOUNT)
		elseif MissionId == x300732_g_MissionId2 then
			x300732_SetDayCount(sceneId, selfId, DQ_CITAN_LOULAN_DATE,DQ_CITAN_LOULAN_DAYCOUNT)
		elseif MissionId == x300732_g_MissionId3 then
			x300732_SetDayCount(sceneId, selfId, DQ_CITAN_KUNLUN_DATE,DQ_CITAN_KUNLUN_DAYCOUNT)
		elseif MissionId == x300732_g_MissionId4 then
			x300732_SetDayCount(sceneId, selfId, DQ_CITAN_LAIYIN_DATE,DQ_CITAN_LAIYIN_DAYCOUNT)
		else
			return -1;
		end

		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�����������:�����ҡ��й�����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�����������:�����ҡ��й�����",8,2)

		x300732_GiveReward(sceneId,selfId)
		DelQuestNM( sceneId, selfId, MissionId )

		--����ʵ����1��
		AddCountryStrength(sceneId, selfId, 1)
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "��ϲ����Ϊ����ʵ��������#R1��#O���֡�");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"��ϲ����Ϊ����ʵ��������#R1��#O���֡�",8,2)				

		if CountryIsFortuneTime(sceneId, selfId, 1) > 0 then
			local country = GetCurCountry(sceneId, selfId)
			SetCountryQuestData(sceneId, country, CD_INDEX_CHUGUO_COUNT, 1, 1 )
	
			-- local selfGuildId = GetGuildID(sceneId, selfId)
			-- local countryGuildId = GetCountryKingGuildId(sceneId, selfId)

			-- if selfGuildId ~= -1 and countryGuildId == selfGuildId then
				--��ѫ��1��
				AddExploit(sceneId, selfId, 1)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o���#R��ѫ1��#o�Ľ���");
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId,selfId);
				Msg2Player(sceneId,selfId,"#o���#R��ѫ1��#o�Ľ���",8,2)
			-- end
			
			--����־
			local strMsg = format("CGL:<Info>x300732_MissionComplate sceneId=%d,country=%d", sceneId, country )
    		WriteLog( 1, strMsg )
		end
		
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

function x300732_GiveReward(sceneId,selfId)

	local level = GetLevel(sceneId, selfId)
	local nExpBonus1 = 100*5*level*3;
	local nExpBonus2 = level*2200;
	local nExpBonus = 0;
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		nExpBonus = nExpBonus1;
	elseif GetLevel(sceneId, selfId) >=70 then
		nExpBonus = nExpBonus2;
	end
    if nExpBonus > 0 then
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 75);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����75��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o���#R����"..nExpBonus.."��#o�Ľ���#r#o���#R����75��#o�Ľ���",4,2)
  		CallScriptFunction( 256268, "Finishchujian", sceneId, selfId)
		local ret = CountryIsFortuneTime(sceneId,selfId,1)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId, 75);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o�����������#R����"..nExpBonus.."��#o�Ľ���");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o������#R����75��#o�Ľ���");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o�����������#R����"..nExpBonus.."��#o�Ľ���",4,2)--#r#o������#R����75��#o�Ľ���",4,2)
			--CallScriptFunction( 256268, "Finishchujian", sceneId, selfId)
			
			--�ݵ���⽱��
			local nCountry = GetCurCountry(sceneId,selfId)
			local nLairdCount,nLairdSumLevel =  CallScriptFunction(888888,"GetCountryLairdSceneInfo",sceneId,nCountry)
			if nLairdCount > 0 then
			
				local nLairdExpBonus = floor((nLairdSumLevel*0.02)*nExpBonus)
				local nLairdHornorBonus = floor((nLairdSumLevel*0.02)*75)
				
				
				AddExp(sceneId, selfId, nLairdExpBonus);
				AddHonor(sceneId, selfId, nLairdHornorBonus);
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o������ؼӳɻ��#R����"..nLairdExpBonus.."��#o�Ľ���");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o������ؼӳɻ��#R����"..nLairdHornorBonus.."��#o�Ľ���");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
		  		Msg2Player(sceneId,selfId,"#o������ؼӳɻ��#R����"..nLairdExpBonus.."��#o�Ľ���#r#o������ؼӳɻ��#R����"..nLairdHornorBonus.."��#o�Ľ���",4,2)
				
			end
		end
	end

end


function x300732_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û���������
		return
	end
		
	--local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	--local submitGuid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	--if npcGuid == submitGuid then	--�����NPC�����ֺ�������NPC��������ͬ������Ҳ�жϹ���
		--local missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
		--AddQuestTextNM( sceneId, selfId, -1, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
	--end
end

 

--********************************************************************
--����
--********************************************************************
function x300732_ProcQuestAbandon( sceneId, selfId,MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return -1;
	end

	if MissionId == x300732_g_MissionId1 then
		x300732_SetDayCount(sceneId, selfId, DQ_CITAN_DUNHUANG_DATE,DQ_CITAN_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId2 then
		x300732_SetDayCount(sceneId, selfId, DQ_CITAN_LOULAN_DATE,DQ_CITAN_LOULAN_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId3 then
		x300732_SetDayCount(sceneId, selfId, DQ_CITAN_KUNLUN_DATE,DQ_CITAN_KUNLUN_DAYCOUNT)
	elseif MissionId == x300732_g_MissionId4 then
		x300732_SetDayCount(sceneId, selfId, DQ_CITAN_LAIYIN_DATE,DQ_CITAN_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "������������:�����ҡ��й�����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"������������:�����ҡ��й�����",8,2)
	end
end

--ɱ������
function x300732_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	
	
	if x300732_CountryCheck( sceneId, selfId, MissionId ) < 0 then
		return -1;
	end

	if objdataId ~= 9525 then
		return -1;
	end

	--if x300732_IsSuccessed( sceneId, selfId, MissionId )>0 then
	--	return -1;
	--end

	local x,z = GetWorldPos(sceneId,selfId)
	local KilledNum =  GetNearCountryCount(sceneId, selfId,x,z,20)  

	--local KilledNum = GetMonsterOwnerCount( sceneId, objId )

	----PrintNum(KilledNum)
	----PrintNum(selfId)
	
	for i = 0, KilledNum-1 do
		local humanObjId = GetNearCountryMember(sceneId, selfId,i);--GetMonsterOwnerID( sceneId, objId, i )
		----PrintNum(humanObjId)
		if humanObjId ~= -1 then
			if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
				if GetHp(sceneId, humanObjId) > 0 then
					if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
						x300732_OnKillTheNpc( sceneId, humanObjId, MissionId )
					end
				end
			end
		end
	end

	
end

function x300732_IsSuccessed( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local iRet = GetQuestParam(sceneId, selfId, misIndex, 0);
		----PrintStr(iRet)
		if iRet>0 then
			return 1;
		end
		return 0;
	else
		return 0;
	end
end

function x300732_OnKillTheNpc(sceneId, selfId, MissionId)
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
	--�Ѿ��������
		if x300732_IsSuccessed( sceneId, selfId, MissionId ) >0 then
			return 0;
		end
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		BeginQuestEvent(sceneId)
		local strText = "��ɱ�������峣��1/1";
		if strText == nil then
			strText = "";
		end
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		Msg2Player(sceneId,selfId,"��ɱ�������峣��",8,2)
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )
		
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
		x300732_QuestLogRefresh( sceneId, selfId, MissionId)
	end	

end


--��Ʒ�ı�
function x300732_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	return 0
end

function x300732_CountryCheck( sceneId, selfId, MissionId )
	if MissionId == x300732_g_MissionId1 then
		if sceneId == x300732_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300732_g_MissionId2 then
		if sceneId == x300732_g_CountryLoulan then
			return 1
		end
	elseif MissionId == x300732_g_MissionId3 then
		if sceneId == x300732_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300732_g_MissionId4 then
		if sceneId == x300732_g_CountryLaiyin then
			return 1
		end
	end
	
	return -1
end


function x300732_OnLogInOrDie( sceneId, selfId )
	
   x300732_OnMissionFailed( sceneId, selfId )
end



function x300732_OnMissionFailed( sceneId, selfId )
	
	x300732_DiGuoCiTanOnDie(sceneId, selfId)


end


function x300732_DiGuoCiTanOnDie(sceneId, selfId)
	
	if 0==0 then
		return
	end

	local MissionId = x300732_g_MissionId1
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
	end
	
	MissionId = x300732_g_MissionId2
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
	end
	
	MissionId = x300732_g_MissionId3
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
	end
	
	MissionId = x300732_g_MissionId4
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
	end
end




---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300732_GetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)


	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, nDayIndex[1], nDayIndex[2],nDayIndex[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2],nDayCountIndex[3] );
	return daycount;
	

end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x300732_SetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)

	

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, nDayIndex[1], nDayIndex[2], nDayIndex[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, nDayIndex[1], nDayIndex[2], nDayIndex[3], today)
		SetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2], nDayCountIndex[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2], nDayCountIndex[3])
		SetQuestData(sceneId, selfId, nDayCountIndex[1], nDayCountIndex[2], nDayCountIndex[3], daycount+1)
	end
	
	
	
end


---------------------------------------------------------------------------------------------------
--���������ܽ��
---------------------------------------------------------------------------------------------------
function x300732_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300732_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3	
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300732_g_MissionId1 then
			AddQuestText(sceneId,"#Y�����ҡ��ػͳ���")
			--������Ϣ
			
			AddQuestText(sceneId,"   �������ǵĶ෬��̽�����������峣����װ����һ���̻�Ĵ��ƹ񣬲����ڶػ������������������粻�˳٣������̳������ɵ�����ͽ��")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_125509�����͵��ػͱ�����ɱ���ػͱ����Ĵ��ƹ����峣��")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300732_g_MissionId2 then
			AddQuestText(sceneId,"#Y�����ҡ�¥������")
			--������Ϣ
			
			AddQuestText(sceneId,"   �������ǵĶ෬��̽�����������峣����װ����һ���̻�Ĵ��ƹ񣬲�����¥�������������������粻�˳٣������̳������ɵ�����ͽ��")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_125509�����͵�¥��������ɱ��¥�������Ĵ��ƹ����峣��")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300732_g_MissionId3 then
			AddQuestText(sceneId,"#Y�����ҡ����س���")
			--������Ϣ
			
			AddQuestText(sceneId,"   �������ǵĶ෬��̽�����������峣����װ����һ���̻�Ĵ��ƹ񣬲��������������������������粻�˳٣������̳������ɵ�����ͽ��")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_125509�����͵����ر�����ɱ�����ر����Ĵ��ƹ����峣��")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300732_g_MissionId4 then
			AddQuestText(sceneId,"#Y�����ҡ���ɽ����")
			--������Ϣ
			
			AddQuestText(sceneId,"   �������ǵĶ෬��̽�����������峣����װ����һ���̻�Ĵ��ƹ񣬲�������ɽ�����������������粻�˳٣������̳������ɵ�����ͽ��")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_125509�����͵���ɽ������ɱ����ɽ�����Ĵ��ƹ����峣��")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
			
		else
			return -1;
		end
		
			
		
		

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300732_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300732_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300732_g_MissionId1 then
			AddQuestText(sceneId,"#Y�����ҡ��ػͳ���")
		--������Ϣ
			
			AddQuestText(sceneId,"   ʱ����ȣ��㻹�ǿ�ȥ�ػ������ɡ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId2 then
			AddQuestText(sceneId,"#Y�����ҡ�¥������")
		--������Ϣ
			
			AddQuestText(sceneId,"   ʱ����ȣ��㻹�ǿ�ȥ¥�������ɡ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId3 then
			AddQuestText(sceneId,"#Y�����ҡ����س���")
		--������Ϣ
			
			AddQuestText(sceneId,"   ʱ����ȣ��㻹�ǿ�ȥ���������ɡ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId4 then
			AddQuestText(sceneId,"#Y�����ҡ���ɽ����")
		--������Ϣ
			
			AddQuestText(sceneId,"   ʱ����ȣ��㻹�ǿ�ȥ��ɽ�����ɡ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		else
			return -1;
		end
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300732_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300732_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300732_g_MissionId1 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ��ػͳ���")
			AddQuestText(sceneId,"   �������ͽӦ�е��³�������Ϊ���ǹ�������һ����")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId2 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ�¥������")
			AddQuestText(sceneId,"   �������ͽӦ�е��³�������Ϊ���ǹ�������һ����")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId3 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ����س���")
			AddQuestText(sceneId,"   �������ͽӦ�е��³�������Ϊ���ǹ�������һ����")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300732_g_MissionId4 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ���ɽ����")
			AddQuestText(sceneId,"   �������ͽӦ�е��³�������Ϊ���ǹ�������һ����")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		else
			return -1;
		end

		
		
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300732_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300732_QuestLogRefresh( sceneId, selfId, MissionId)

	local nRet = x300732_IsSuccessed( sceneId, selfId, MissionId )
	local str = "";

	if MissionId == x300732_g_MissionId1 then
		if nRet>0 then
			str = "  ��@npc_30003���ػͱ���ɱ��@npc_30019��1/1��"
		else
			str = "  ��@npc_30003���ػͱ���ɱ��@npc_30019��0/1��"
		end
	elseif MissionId == x300732_g_MissionId2 then
		if nRet>0 then
			str = "  ��@npc_30000��¥������ɱ��@npc_30016��1/1��"
		else
			str = "  ��@npc_30000��¥������ɱ��@npc_30016��0/1��"
		end
	elseif MissionId == x300732_g_MissionId3 then
		if nRet>0 then
			str = "  ��@npc_30002�����ر���ɱ��@npc_30018��1/1��"
		else
			str = "  ��@npc_30002�����ر���ɱ��@npc_30018��0/1��"
		end
	elseif MissionId == x300732_g_MissionId4 then
		if nRet>0 then
			str = "  ��@npc_30001����ɽ����ɱ��@npc_30017��1/1��"
		else
			str = "  ��@npc_30001����ɽ����ɱ��@npc_30017��0/1��"
		end
	else
		return -1;
	end
		
	BeginQuestEvent(sceneId)	
		local level = GetLevel(sceneId, selfId)
		local ExpBonus1 = 100*5*3 * level
		local ExpBonus2 = 2200 * level
		local ExpBonus = 0
		if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
			ExpBonus = ExpBonus1;
		elseif GetLevel(sceneId, selfId) >=70 then
			ExpBonus = ExpBonus2;
		end
	    if ExpBonus > 0 then
			AddQuestExpBonus(sceneId,  ExpBonus);
			AddQuestMoneyBonus6(sceneId, 75 )
		end		
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							"�����ҡ��й�����",        -- ��������
							str,		--����Ŀ��
							"@npc_125501",			--����NPC
							"ͨ��@npc_125509Ǳ��й������������ƹ����峣ɱ����\n¥���������ƹ����꣨36��203��\n��ɽ�������ƹ����꣨215��216��\n���ر������ƹ����꣨43��45��\n�ػͱ������ƹ����꣨225��35��",               --������
							"�벻�����������й�����̽ͳ�����峣�������˷�²��Ȼ���������ǣ������������������Ǵ�����̽����Ϣ������ֻ�иɵ����ˣ����ܷ�ֹ���ǿ��ľ�Ӫ�������̽�������״ݻ١�",	--��������
							"�����ڳ������ڼ�ظ�����ʱ���㽫���˫���Ľ�����"					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		

end

function x300732_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300732_QuestLogRefresh( sceneId, selfId, MissionId );
end