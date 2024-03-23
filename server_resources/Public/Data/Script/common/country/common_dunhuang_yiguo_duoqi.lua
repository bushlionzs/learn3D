

--MisDescBegin

x300882_g_ScriptId =  300882 					


x300882_g_MissionKind 				= 	1                       --��������
x300882_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������





x300882_g_MissionName				= 	"�й�����"
x300882_g_MissionTarget				= 	""
x300882_g_MissionInfo				= 	""
x300882_g_ContinueInfo				= 	""
x300882_g_MissionCompleted			= 	""
x300882_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300882_g_ExtTarget					=	{ {type=20,n=1,target="�й�����"}}

--����

x300882_g_ExpBonus					= 	0;--x300882_AddExpAward               	--����������
x300882_g_BonusItem					=	{}	--��������Ʒ

x300882_g_BonusMoney1               = 	0
x300882_g_BonusMoney2               =   0
x300882_g_BonusMoney3               =   0

x300882_g_BonusChoiceItem           =   {}


--MisDescEnd


x300882_g_CountryDunhuang = 351 --�ĸ����ҵĳ���id
x300882_g_CountryLoulan = 51
x300882_g_CountryKunlun = 251
x300882_g_CountryLaiyin = 151

x300882_g_MissionId1 = 7689
x300882_g_MissionId2 = 7686
x300882_g_MissionId3 = 7688
x300882_g_MissionId4 = 7687


x300882_g_DayCountLimited			= 1


x300882_g_MissionBonusInfo			= 	"#Y��þ���#R%d#Y�Ľ�����"

function x300882_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
end

--ѡ������
function x300882_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )

	if index ~= -1 then
		MissionId = index
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- ������Խ��������
			--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
			x300882_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
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
		if x300882_IsSuccessed( sceneId, selfId, MissionId )>0 then
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
			x300882_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
			x300882_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
end


--��������
function x300882_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if	IsHaveQuestNM( sceneId, selfId, x300882_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300882_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300882_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300882_g_MissionId4 ) > 0 then
			BeginQuestEvent(sceneId)
			local strText = "���Ѿ��ӹ��ˡ����ҡ��й��������񣬻�δ��ɣ������ٽ�ȡ"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"���Ѿ��ӹ��ˡ����ҡ��й��������񣬻�δ��ɣ������ٽ�ȡ",8,2)
			return
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ������������ֱ���˳�
		return 0
	end
	
	local nDayCount =0;

	if MissionId == x300882_g_MissionId1 then
		nDayCount = x300882_GetDayCount(sceneId, selfId, DQ_DUOQI_DUNHUANG_DATE,DQ_DUOQI_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId2 then
		nDayCount = x300882_GetDayCount(sceneId, selfId, DQ_DUOQI_LOULAN_DATE,DQ_DUOQI_LOULAN_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId3 then
		nDayCount = x300882_GetDayCount(sceneId, selfId, DQ_DUOQI_KUNLUN_DATE,DQ_DUOQI_KUNLUN_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId4 then
		nDayCount = x300882_GetDayCount(sceneId, selfId, DQ_DUOQI_LAIYIN_DATE,DQ_DUOQI_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	if nDayCount>=x300882_g_DayCountLimited then
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
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������
		if ret > 0 then
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "������������:�����ҡ��й�����");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"������������:�����ҡ��й�����",8,2)
			GamePlayScriptLog(sceneId, selfId, 141)
			return 1
		elseif ret == 0 then
			local strText = "�������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -1 then
			local strText = "��������,�����������������"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		elseif ret == -2 then
			local strText = "�����������������ʧ��"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, strText);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
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
function x300882_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local ret = x300882_IsSuccessed( sceneId, selfId, MissionId ); --QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
	if ret > 0 then -- ����������
		
		return x300882_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	end
	return 0
end

--�������
function x300882_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
		--��ʾ����������
		if MissionId == x300882_g_MissionId1 then
			x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_DUNHUANG_DATE,DQ_DUOQI_DUNHUANG_DAYCOUNT)
		elseif MissionId == x300882_g_MissionId2 then
			x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_LOULAN_DATE,DQ_DUOQI_LOULAN_DAYCOUNT)
		elseif MissionId == x300882_g_MissionId3 then
			x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_KUNLUN_DATE,DQ_DUOQI_KUNLUN_DAYCOUNT)
		elseif MissionId == x300882_g_MissionId4 then
			x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_LAIYIN_DATE,DQ_DUOQI_LAIYIN_DAYCOUNT)
		else
			return -1;
		end

		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�����������:�����ҡ��й�����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�����������:�����ҡ��й�����",8,2)
		
		
		x300882_GiveReward(sceneId,selfId)
		DelQuestNM( sceneId, selfId, MissionId )
		GamePlayScriptLog(sceneId, selfId, 142)
 
		CancelSpecificImpact(sceneId, selfId, 7702);
	
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
			local strMsg = format("CGL:<Info>x300882_MissionComplate sceneId=%d,country=%d", sceneId, country )
    		WriteLog( 1, strMsg )
		end
		
	return 0
end

function x300882_GiveReward(sceneId,selfId)
	local level = GetLevel(sceneId, selfId)
	local nExpBonus1 = 100*3*level*5;
	local nExpBonus2 = level*2200;
	local nExpBonus = 0;
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		nExpBonus = nExpBonus1;
	elseif GetLevel(sceneId, selfId) >=70 then
		nExpBonus = nExpBonus2;
	end
    if nExpBonus > 0 then
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 100);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();		
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����100��#o�Ľ���");
		EndQuestEvent();		
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o���#R����"..nExpBonus.."��#o�Ľ���#r#o���#R����100��#o�Ľ���",4,2)
  		CallScriptFunction( 256271, "Finishduoqi", sceneId, selfId)
		local ret = CountryIsFortuneTime(sceneId,selfId,1)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId,100);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o�����������#R����"..nExpBonus.."��#o�Ľ���");
			EndQuestEvent();		
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o������#R����100��#o�Ľ���");
			--EndQuestEvent();		
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o�����������#R����"..nExpBonus.."��#o�Ľ���",4,2)
			--CallScriptFunction( 256271, "Finishduoqi", sceneId, selfId)
			
			--�ݵ���⽱��
			local nCountry = GetCurCountry(sceneId,selfId)
			local nLairdCount,nLairdSumLevel =  CallScriptFunction(888888,"GetCountryLairdSceneInfo",sceneId,nCountry)
			if nLairdCount > 0 then
			
				local nLairdExpBonus = floor((nLairdSumLevel*0.02)*nExpBonus)
				local nLairdHornorBonus = floor((nLairdSumLevel*0.02)*100)
				
				
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


function x300882_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
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
function x300882_ProcQuestAbandon( sceneId, selfId,MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then
		return -1;
	end

	if MissionId == x300882_g_MissionId1 then
		x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_DUNHUANG_DATE,DQ_DUOQI_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId2 then
		x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_LOULAN_DATE,DQ_DUOQI_LOULAN_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId3 then
		x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_KUNLUN_DATE,DQ_DUOQI_KUNLUN_DAYCOUNT)
	elseif MissionId == x300882_g_MissionId4 then
		x300882_SetDayCount(sceneId, selfId, DQ_DUOQI_LAIYIN_DATE,DQ_DUOQI_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	local ret = 0
	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		CancelSpecificImpact(sceneId, selfId, 7702);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "������������:�����ҡ��й�����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"������������:�����ҡ��й�����",8,2)
	end
end

--ɱ������
function x300882_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	

end

function x300882_IsSuccessed( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		local iRet = GetQuestParam(sceneId, selfId, misIndex, 0);
		----PrintStr(iRet)
		if iRet>0 then
			if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
				return 1;
			end
		end
	end

	return 0
end


--��Ʒ�ı�
function x300882_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	return 0
end

function x300882_CountryCheck( sceneId, selfId, MissionId )
	if MissionId == x300882_g_MissionId1 then
		if sceneId == x300882_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300882_g_MissionId2 then
		if sceneId == x300882_g_CountryLoulan then
			return 1
		end
	elseif MissionId == x300882_g_MissionId3 then
		if sceneId == x300882_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300882_g_MissionId4 then
		if sceneId == x300882_g_CountryLaiyin then
			return 1
		end
	end
	
	return -1
end


function x300882_OnLogInOrDie( sceneId, selfId )
	local MissionId = x300882_g_MissionId1
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
			CancelSpecificImpact(sceneId, selfId, 7702);
			x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"���ĵй�����������ʧ�ܣ�����������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���ĵй�����������ʧ�ܣ�����������",8,2)
			SetQuestParam( sceneId,selfId,MissionId,7,0)
		end
	end
	
	local MissionId = x300882_g_MissionId2
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
			CancelSpecificImpact(sceneId, selfId, 7702);
			x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"���ĵй�����������ʧ�ܣ�����������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���ĵй�����������ʧ�ܣ�����������",8,2)
			SetQuestParam( sceneId,selfId,MissionId,7,0)
		end
	end
	
	local MissionId = x300882_g_MissionId3
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
			CancelSpecificImpact(sceneId, selfId, 7702);
			x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"���ĵй�����������ʧ�ܣ�����������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���ĵй�����������ʧ�ܣ�����������",8,2)
			SetQuestParam( sceneId,selfId,MissionId,7,0)
		end
	end
	
	local MissionId = x300882_g_MissionId4
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		if IsHaveSpecificImpact( sceneId, selfId, 7702 ) > 0 then
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 2 )
			CancelSpecificImpact(sceneId, selfId, 7702);
			x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
			BeginQuestEvent(sceneId);AddQuestText(sceneId,"���ĵй�����������ʧ�ܣ�����������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,selfId);
			Msg2Player(sceneId,selfId,"���ĵй�����������ʧ�ܣ�����������",8,2)
			SetQuestParam( sceneId,selfId,MissionId,7,0)
		end
	end
  
end

function x300882_ProcQuestLogRefresh( sceneId,selfId,MissionId)
	--local misIndex = GetQuestIndexByID( sceneId, selfId, missionId )	
	--local instData1 = GetQuestParam( sceneId, selfId, misIndex, 0 )
	--local instDataStr1 = format("(%d/1)", instData1 )

	--local str_npc = "#G������ܴ�Ԫ˧"
	--local str_target = "#G�й�����#W"..instDataStr1
	
	local nRet = x300882_IsSuccessed( sceneId, selfId, MissionId )
	local str = "";

	if MissionId == x300882_g_MissionId1 then
		if nRet>0 then
			str = "  ��@npc_30015���ػͱ�����ȡ@npc_30031��1/1��"
		else
			str = "  ��@npc_30015���ػͱ�����ȡ@npc_30031��0/1��"
		end
	elseif MissionId == x300882_g_MissionId2 then
		if nRet>0 then
			str = "  ��@npc_30012��¥��������ȡ@npc_30028��1/1��"
		else
			str = "  ��@npc_30012��¥��������ȡ@npc_30028��0/1��"
		end
	elseif MissionId == x300882_g_MissionId3 then
		if nRet>0 then
			str = "  ��@npc_30014�����ر�����ȡ@npc_30030��1/1��"
		else
			str = "  ��@npc_30014�����ر�����ȡ@npc_30030��0/1��"
		end
	elseif MissionId == x300882_g_MissionId4 then
		if nRet>0 then
			str = "  ��@npc_30013����ɽ������ȡ@npc_30029��1/1��"
		else
			str = "  ��@npc_30013����ɽ������ȡ@npc_30029��0/1��"
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
			AddQuestMoneyBonus6(sceneId, 100 )
		end		
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							"�����ҡ��й�����",        -- ��������
							str,		--����Ŀ��
							"@npc_134502",			--����NPC
							"ͨ��@npc_134511Ǳ��й�����������126��123��������ȡ���졣",               --������
							"���ߣ�����Ϊ�ϡ�����Ҫ������˵�ʿ������õİ취Ī���ڶ�ȡ���ǵľ��죡",	--��������
							"�����ڳ������ڼ�ظ�����ʱ���㽫���˫���Ľ�����������ʧ��ʱ������������ȥ�й���������ʹ�����ս�죡"					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);

end


---------------------------------------------------------------------------------------------------
--���һ�����������������
---------------------------------------------------------------------------------------------------
function x300882_GetLastDay(sceneId, selfId, nMDIndex, nOffset, nSize)
	local lastday = GetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize)
	return lastday
end

---------------------------------------------------------------------------------------------------
--���һ��������������˼���
---------------------------------------------------------------------------------------------------
function x300882_GetLastDayCount(sceneId, selfId, nMDIndex, nOffset, nSize)
	local daycount =  GetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize)
	return daycount
end

---------------------------------------------------------------------------------------------------
--��������������˼���
---------------------------------------------------------------------------------------------------
function x300882_GetDayCount(sceneId, selfId, nMDDayIndex, nMDCountIndex)
	local today = GetDayOfYear()
	local lastday = x300882_GetLastDay(sceneId, selfId, nMDDayIndex[1], nMDDayIndex[2], nMDDayIndex[3])

	--����ͬһ��
	if today ~= lastday then
		return 0
	end

	local daycount = x300882_GetLastDayCount(sceneId, selfId, nMDCountIndex[1], nMDCountIndex[2], nMDCountIndex[3])
	return daycount
end

---------------------------------------------------------------------------------------------------
--�������һ�����������������
---------------------------------------------------------------------------------------------------
function x300882_SetLastDay(sceneId, selfId, nMDIndex, nOffset, nSize, day)
	SetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize, day)
end

---------------------------------------------------------------------------------------------------
--����������Ĵ���
---------------------------------------------------------------------------------------------------
function x300882_SetLastDayCount(sceneId, selfId, nMDIndex, nOffset, nSize, count)
	SetQuestData(sceneId, selfId, nMDIndex, nOffset, nSize, count)
end

---------------------------------------------------------------------------------------------------
--���ý������˶��ٴ�
---------------------------------------------------------------------------------------------------
function x300882_SetDayCount(sceneId, selfId, nMDDayIndex, nMDCountIndex)
	local today = GetDayOfYear()
	local lastday = x300882_GetLastDay(sceneId, selfId, nMDDayIndex[1], nMDDayIndex[2], nMDDayIndex[3])

	--�ϴ���ɵ����ڲ��ǽ���
	if today ~= lastday then
		x300882_SetLastDay(sceneId, selfId, nMDDayIndex[1], nMDDayIndex[2], nMDDayIndex[3], today)
		x300882_SetLastDayCount(sceneId, selfId, nMDCountIndex[1], nMDCountIndex[2], nMDCountIndex[3], 1)
		return
	end

	--�ϴ���ɵ������ǽ���
	local daycount = x300882_GetLastDayCount(sceneId, selfId, nMDDayIndex[1], nMDDayIndex[2], nMDDayIndex[3]) + 1
	x300882_SetLastDayCount(sceneId, selfId, nMDCountIndex[1], nMDCountIndex[2], nMDCountIndex[3], daycount)

end


function x300882_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300882_g_MissionId1 then
			AddQuestText(sceneId,"#Y�����ҡ��ػͶ���")
			--������Ϣ
			
			AddQuestText(sceneId,"   �ػͱ����ı�������ʹ�������ƹ������Ŷػʹ���ľ��죬������ȡ�˶ػ;��첢�������飬������ǿ�Ҷ�ҡ�ػ͵ľ��ģ�Ҳ�ܴ������Ҿ���ʿ����")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_134511�����͵��ػͱ���������������ʹ����ȡ�й����졣")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId2 then
			AddQuestText(sceneId,"#Y�����ҡ�¥������")
			--������Ϣ
			
			AddQuestText(sceneId,"   ¥�������ı�������ʹ�������ƹ�������¥������ľ��죬������ȡ��¥�����첢�������飬������ǿ�Ҷ�ҡ¥���ľ��ģ�Ҳ�ܴ������Ҿ���ʿ����")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_134511�����͵�¥������������������ʹ����ȡ�й����졣")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId3 then
			AddQuestText(sceneId,"#Y�����ҡ����ض���")
			--������Ϣ
			
			AddQuestText(sceneId,"   ���ر����ı�������ʹ�������ƹ����������ش���ľ��죬������ȡ�����ؾ��첢�������飬������ǿ�Ҷ�ҡ���صľ��ģ�Ҳ�ܴ������Ҿ���ʿ����")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_134511�����͵����ر���������������ʹ����ȡ�й����졣")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId4 then
			AddQuestText(sceneId,"#Y�����ҡ���ɽ����")
			--������Ϣ
			
			AddQuestText(sceneId,"   ��ɽ�����ı�������ʹ�������ƹ���������ɽ����ľ��죬������ȡ����ɽ���첢�������飬������ǿ�Ҷ�ҡ��ɽ�ľ��ģ�Ҳ�ܴ������Ҿ���ʿ����")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_134511�����͵���ɽ����������������ʹ����ȡ�й����졣")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			AddQuestText(sceneId," ")
			
		else
			return -1;
		end
		
	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300882_g_ScriptId, MissionId,0);
end

--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300882_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300882_g_MissionId1 then
			AddQuestText(sceneId,"#Y�����ҡ��ػͶ���")
			AddQuestText(sceneId,"   �ܺã����Ƕ����ľ����ֶ���һ�档")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId2 then
			AddQuestText(sceneId,"#Y�����ҡ�¥������")
			AddQuestText(sceneId,"   �ܺã����Ƕ����ľ����ֶ���һ�档")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			
		elseif MissionId == x300882_g_MissionId3 then
			AddQuestText(sceneId,"#Y�����ҡ����ض���")
			AddQuestText(sceneId,"   �ܺã����Ƕ����ľ����ֶ���һ�档")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			
		elseif MissionId == x300882_g_MissionId4 then
			AddQuestText(sceneId,"#Y�����ҡ���ɽ����")
			AddQuestText(sceneId,"   �ܺã����Ƕ����ľ����ֶ���һ�档")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			
		else
			return -1;
		end	
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300882_g_ScriptId, MissionId);

end

--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300882_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*5*3
	local localexp2 = (GetLevel( sceneId, selfId )) * 2200
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300882_g_MissionId1 then
			AddQuestText(sceneId,"#Y�����ҡ��ػͶ���")
		--������Ϣ
			
			AddQuestText(sceneId,"   ��ô���ѵ��㿴���Ƕػ;����µ������������������ӣ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId2 then
			AddQuestText(sceneId,"#Y�����ҡ�¥������")
		--������Ϣ
			
			AddQuestText(sceneId,"   ��ô���ѵ��㿴����¥�������µ������������������ӣ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId3 then
			AddQuestText(sceneId,"#Y�����ҡ����ض���")
		--������Ϣ
			
			AddQuestText(sceneId,"   ��ô���ѵ��㿴�������ؾ����µ������������������ӣ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300882_g_MissionId4 then
			AddQuestText(sceneId,"#Y�����ҡ���ɽ����")
		--������Ϣ
			
			AddQuestText(sceneId,"   ��ô���ѵ��㿴������ɽ�����µ������������������ӣ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��100��")
			AddQuestText(sceneId," ")
			
		else
			return -1;
		end	
	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300882_g_ScriptId, MissionId,0);
	
end