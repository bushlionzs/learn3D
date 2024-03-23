--�й������ű�
--MisDescBegin

x300733_g_ScriptId 					= 	300733                  --�ű�ID


x300733_g_MissionKind 				= 	1                       --��������
x300733_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������





x300733_g_MissionName				= 	"�й��鱨"
x300733_g_MissionTarget				= 	""
x300733_g_MissionInfo				= 	""
x300733_g_ContinueInfo				= 	""
x300733_g_MissionCompleted			= 	""
x300733_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300733_g_ExtTarget					=	{ {type=20,n=10,target="����鱨"}}

--����

x300733_g_ExpBonus					= 	0;--x300733_AddExpAward               	--����������
x300733_g_BonusItem					=	{}	--��������Ʒ

x300733_g_BonusMoney1               = 	0
x300733_g_BonusMoney2               =   0
x300733_g_BonusMoney3               =   0

x300733_g_BonusChoiceItem           =   {}


--MisDescEnd

x300733_g_LevelNeeded = 65

x300733_g_DayCountLimited	=  1

x300733_g_MissionId1 = 7580  
x300733_g_MissionId2 = 7562
x300733_g_MissionId3 = 7574
x300733_g_MissionId4 = 7568
x300733_g_CountryDunhuang =  351--�ĸ����ҵĳ���id
x300733_g_CountryLouLan =  51
x300733_g_CountryKunlun = 251
x300733_g_CountryLaiYin = 151

x300733_g_NeedItemID = 13011006
x300733_g_NeedItemCount = 1

x300733_g_MissionBonusInfo  = 	"#Y��þ���#R%d#Y�Ľ�����"
              
function x300733_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
end


function x300733_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end

	if MissionId ~= x300733_g_MissionId1 and MissionId ~= x300733_g_MissionId2 and MissionId ~= x300733_g_MissionId3 and MissionId ~= x300733_g_MissionId4 then
		return 0;
	end

	local ItemCnt = GetItemCount( sceneId, selfId, x300733_g_NeedItemID )

	if ItemCnt<x300733_g_NeedItemCount then
		return 0;
	end

	return 1;


end

--ѡ������
function x300733_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	
	if index ~= -1 then
		MissionId = index
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
	
		if	IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId4 ) > 0 then
			--BeginQuestEvent(sceneId)
			--local strText = "���Ѿ��ӹ��ˡ����ҡ��й��鱨���񣬻�δ��ɣ������ٽ�ȡ��"
			--AddQuestText( sceneId, strText )
			--EndQuestEvent( sceneId )
			--DispatchQuestTips( sceneId, selfId )
			--Msg2Player(sceneId,selfId,"���Ѿ��ӹ��ˡ����ҡ��й��鱨���񣬻�δ��ɣ������ٽ�ȡ��",8,2)
			--return
		end
		--��Ҫ����npc����û������������ʾ��
			local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
			if ret > 0 then	-- ������Խ��������
				--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
				x300733_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
			elseif ret ==-1 then  --�ȼ�����
				--hf_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
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
		if x300733_CheckSubmit( sceneId, selfId, MissionId )>0 then
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
			x300733_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
			x300733_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
		
end

--��������
function x300733_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ������������ֱ���˳�
		return 0
	end

	--PrintStr(MissionId)

	if	IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300733_g_MissionId4 ) > 0 then
			BeginQuestEvent(sceneId)
			local strText = "���Ѿ��ӹ��ˡ����ҡ��й��鱨���񣬻�δ��ɣ������ٽ�ȡ��"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"���Ѿ��ӹ��ˡ����ҡ��й��鱨���񣬻�δ��ɣ������ٽ�ȡ��",8,2)
			return
	end

	local nDayCount =0;

	if MissionId == x300733_g_MissionId1 then
		nDayCount = x300733_GetDayCount(sceneId, selfId, DQ_MIBAO_DUNHUANG_DATE,DQ_MIBAO_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId2 then
		nDayCount = x300733_GetDayCount(sceneId, selfId, DQ_MIBAO_LOULAN_DATE,DQ_MIBAO_LOULAN_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId3 then
		nDayCount = x300733_GetDayCount(sceneId, selfId, DQ_MIBAO_KUNLUN_DATE,DQ_MIBAO_KUNLUN_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId4 then
		nDayCount = x300733_GetDayCount(sceneId, selfId, DQ_MIBAO_LAIYIN_DATE,DQ_MIBAO_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	if nDayCount>=x300733_g_DayCountLimited then
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
			return 0;
		end
		---------------------------- add end -------------------------------
	
		ret = AddQuestNM( sceneId, selfId, MissionId ) -- ������������
		if ret > 0 then
			--hf_MissionAfterAccept(sceneId, selfId, MissionId);
			--hf_DisplayAcceptMessage(sceneId, selfId, MissionId);
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "������������:�����ҡ��й��鱨");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"������������:�����ҡ��й��鱨",8,2)

			return 1
		else
			--hf_DisplayAddMissionErrorMessage(sceneId, selfId, ret);
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "�����������");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
		end
	elseif ret ==-1 then  --�ȼ�����
		--hf_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
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
function x300733_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local ret = x300733_CheckSubmit( sceneId, selfId, MissionId ) --QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
	if ret > 0 then -- ����������
		return x300733_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	end
	return 0
end

--�������
function x300733_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end
    
	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- ��ȡ���������Ϣ
	if ret == 1 then -- ����ɹ����
		--��ʾ����������


		local ItemCnt = GetItemCount( sceneId, selfId, x300733_g_NeedItemID )
		if ItemCnt > 0 then --����
			DelItem(sceneId, selfId,x300733_g_NeedItemID,ItemCnt)	
		else	
		end	
		--��ʾ����������

		if MissionId == x300733_g_MissionId1 then
			x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_DUNHUANG_DATE,DQ_MIBAO_DUNHUANG_DAYCOUNT)
		elseif MissionId == x300733_g_MissionId2 then
			x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_LOULAN_DATE,DQ_MIBAO_LOULAN_DAYCOUNT)
		elseif MissionId == x300733_g_MissionId3 then
			x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_KUNLUN_DATE,DQ_MIBAO_KUNLUN_DAYCOUNT)
		elseif MissionId == x300733_g_MissionId4 then
			x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_LAIYIN_DATE,DQ_MIBAO_LAIYIN_DAYCOUNT)
		else
			return -1;
		end

		--hf_DisplayCompleteMessage(sceneId, selfId, MissionId);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�����������:�����ҡ��й��鱨");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�����������:�����ҡ��й��鱨",8,2)
		
		x300733_GiveReward(sceneId,selfId)
		DelQuestNM( sceneId, selfId, MissionId )
	
		--����ʵ����1��
		AddCountryStrength(sceneId, selfId, 1)	
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "��ϲ����Ϊ����ʵ��������#R1��#o���֡�");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"��ϲ����Ϊ����ʵ��������#R1��#o���֡�",8,2)		
		
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
		
			local strMsg = format("CGL:<Info>x300733_MissionComplate sceneId=%d,country=%d", sceneId, country )
    		WriteLog( 1, strMsg )
		end
		
		--hf_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId)--��ʾ��ҽ�Ǯ���������Ľ�����Ϣ
		return 1 -- ���سɹ�
	else -- ���δ�ɹ����
		--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(sceneId, selfId, ret);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "����������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	return 0
end


function x300733_GiveReward(sceneId,selfId)

	local level = GetLevel(sceneId, selfId)
	local nExpBonus1 = 100*2.6*level*5;
	local nExpBonus2 = level*1750;
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
  		CallScriptFunction( 256268, "Finishqingbao", sceneId, selfId)
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
			Msg2Player(sceneId,selfId,"#o�����������#R����"..nExpBonus.."��#o�Ľ���",4,2)
			--CallScriptFunction( 256268, "Finishqingbao", sceneId, selfId)
			
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

function x300733_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

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
function x300733_ProcQuestAbandon( sceneId, selfId,MissionId )
	local ret = 0

	if MissionId == x300733_g_MissionId1 then
		x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_DUNHUANG_DATE,DQ_MIBAO_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId2 then
		x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_LOULAN_DATE,DQ_MIBAO_LOULAN_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId3 then
		x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_KUNLUN_DATE,DQ_MIBAO_KUNLUN_DAYCOUNT)
	elseif MissionId == x300733_g_MissionId4 then
		x300733_SetDayCount(sceneId, selfId, DQ_MIBAO_LAIYIN_DATE,DQ_MIBAO_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	ret = DelQuestNM( sceneId, selfId, MissionId )
	if ret == 1 then
		--hf_DisplayAbandonMessage(sceneId, selfId, MissionId);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "������������:�����ҡ��й��鱨");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"������������:�����ҡ��й��鱨",8,2)
	end
end

--ɱ������
function x300733_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end


--��Ʒ�ı�
function x300733_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--Ѱ�Ҳ��ϵ�������ɺ�����Ӻϳ�����
    
    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return 0
    end
    
	--CallScriptFunction( 888891, "ProcQuestItemChanged", sceneId, selfId, itemdataId, MissionId )
	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId )
		--x888891_DisplayMissionGetItemMessage(sceneId, selfId, itemdataId, Num, NeedNum);
		if Num < NeedNum then --��û���������
 			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			x300733_ProcQuestLogRefresh( sceneId, selfId, MissionId)
		elseif Num >= NeedNum then
			--�Ѿ��������
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, NeedNum )         --by zheng
			local MisCareNPC = QuestCareNPCNM( sceneId, selfId, misIndex )
			if MisCareNPC == 0 then --�����Զ����
				local ret = QuestCheckSubmitNM( sceneId, selfId, selfId, MissionId, misIndex ) -- ��ȡ�����������Ϣ
				if ret > 0 then -- ����������
					x300733_ProcQuestLogRefresh( sceneId, selfId, MissionId)
					return x300733_MissionComplate( sceneId, selfId, selfId, -1, MissionId )
				end
			end

			x300733_ProcQuestLogRefresh( sceneId, selfId, MissionId)
		end
	end

end


function x300733_CountryCheck( sceneId, selfId, MissionId )
	if MissionId == x300733_g_MissionId1 then
		if sceneId == x300733_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300733_g_MissionId2 then
		if sceneId == x300733_g_CountryLouLan then
			return 1
		end
	elseif MissionId == x300733_g_MissionId3 then
		if sceneId == x300733_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300733_g_MissionId4 then
		if sceneId == x300733_g_CountryLaiYin then
			return 1
		end
	end

	return -1
	
end

function x300733_OnLogInOrDie( sceneId, selfId )
	
   x300733_OnMissionFailed( sceneId, selfId )
end



function x300733_OnMissionFailed( sceneId, selfId )
	
	x300733_DiGuoQiangLiangOnDie(sceneId, selfId)

end

function x300733_DiGuoQiangLiangOnDie( sceneId, selfId )
	if 0==0 then
		return
	end

	local MissionId = x300733_g_MissionId1
	local itemId = x300733_g_NeedItemID;
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		
		local ItemCnt = GetItemCount( sceneId, selfId, itemId )
		if ItemCnt > 0 then 
			--DelItem(sceneId, selfId,itemId,1)
		else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		end
		return
	end
	MissionId = x300733_g_MissionId2
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		
		local ItemCnt = GetItemCount( sceneId, selfId, itemId )
		if ItemCnt > 0 then 
			--DelItem(sceneId, selfId,itemId,1)
		else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		end
		return
	end
	MissionId = x300733_g_MissionId3
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		
		local ItemCnt = GetItemCount( sceneId, selfId, itemId )
		if ItemCnt > 0 then 
			--DelItem(sceneId, selfId,itemId,1)
		else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		end
		return
	end
	MissionId = x300733_g_MissionId4
	if IsHaveQuestNM( sceneId, selfId,MissionId  ) > 0 then	-- ������������
		
		local ItemCnt = GetItemCount( sceneId, selfId, itemId )
		if ItemCnt > 0 then 
			--DelItem(sceneId, selfId,itemId,1)
		else
			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		end
		return
	end
end


---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300733_GetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)



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
function x300733_SetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)

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
function x300733_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300733_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300733_g_MissionId1 then
			AddQuestText(sceneId,"#Y�����ҡ��ػ��鱨")
			--������Ϣ
			
			AddQuestText(sceneId,"   ���ǵ�һλ��̽�������ڶػͱ���ʶ������ݣ��鼱֮�£���������Ҫ���鱨�����˶ػͰ�����\n\t����鱨�����ŵй���Ҫ�����ĵ�������������ǰ���ػͰ��������鱨���ܵ�ȡ��������Ȼ����ҪС�����£��Ҳ������ɳ���һλ��ʿȥ�ظ�ͬ����ʹ����")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_125509�����͵��ػͱ��������ػͰ�����ȡ�ܱ���")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")

		elseif MissionId == x300733_g_MissionId2 then
			AddQuestText(sceneId,"#Y�����ҡ�¥���鱨")
			--������Ϣ
			
			AddQuestText(sceneId,"   ���ǵ�һλ��̽��������¥������ʶ������ݣ��鼱֮�£���������Ҫ���鱨������¥��������\n\t����鱨�����ŵй���Ҫ�����ĵ�������������ǰ��¥�����������鱨���ܵ�ȡ��������Ȼ����ҪС�����£��Ҳ������ɳ���һλ��ʿȥ�ظ�ͬ����ʹ����")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_125509�����͵�¥����������¥��������ȡ�ܱ���")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300733_g_MissionId3 then
			AddQuestText(sceneId,"#Y�����ҡ������鱨")
			--������Ϣ
			
			AddQuestText(sceneId,"   ���ǵ�һλ��̽�����������ر���ʶ������ݣ��鼱֮�£���������Ҫ���鱨���������ذ�����\n\t����鱨�����ŵй���Ҫ�����ĵ�������������ǰ�����ذ��������鱨���ܵ�ȡ��������Ȼ����ҪС�����£��Ҳ������ɳ���һλ��ʿȥ�ظ�ͬ����ʹ����")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_125509�����͵����ر����������ذ�����ȡ�ܱ���")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300733_g_MissionId4 then
			AddQuestText(sceneId,"#Y�����ҡ���ɽ�鱨")
			--������Ϣ
			
			AddQuestText(sceneId,"   ���ǵ�һλ��̽����������ɽ����ʶ������ݣ��鼱֮�£���������Ҫ���鱨��������ɽ������\n\t����鱨�����ŵй���Ҫ�����ĵ�������������ǰ����ɽ���������鱨���ܵ�ȡ��������Ȼ����ҪС�����£��Ҳ������ɳ���һλ��ʿȥ�ظ�ͬ����ʹ����")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_125509�����͵���ɽ����������ɽ������ȡ�ܱ���")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
			
		else
			return -1;
		end
		
			
		
		

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300733_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300733_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300733_g_MissionId1 then
			AddQuestText(sceneId,"#Y�����ҡ��ػ��鱨")
		--������Ϣ
			
			AddQuestText(sceneId,"   ʱ��ÿ��ȥһ�֣��鱨�Ͷ�һ�ֱ�¶��Σ�ա�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId2 then
			AddQuestText(sceneId,"#Y�����ҡ�¥���鱨")
		--������Ϣ
			
			AddQuestText(sceneId,"   ʱ��ÿ��ȥһ�֣��鱨�Ͷ�һ�ֱ�¶��Σ�ա�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId3 then
			AddQuestText(sceneId,"#Y�����ҡ������鱨")
		--������Ϣ
			
			AddQuestText(sceneId,"   ʱ��ÿ��ȥһ�֣��鱨�Ͷ�һ�ֱ�¶��Σ�ա�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId4 then
			AddQuestText(sceneId,"#Y�����ҡ���ɽ�鱨")
		--������Ϣ
			
			AddQuestText(sceneId,"   ʱ��ÿ��ȥһ�֣��鱨�Ͷ�һ�ֱ�¶��Σ�ա�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		else
			return -1;
		end


	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300733_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300733_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5	
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300733_g_MissionId1 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ��ػ��鱨")
			AddQuestText(sceneId,"   ̫���ˣ���������鱨�����ǾͶԶػͱ����ľ�����������ָ�ơ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId2 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ�¥���鱨")
			AddQuestText(sceneId,"   ̫���ˣ���������鱨�����ǾͶ�¥�������ľ�����������ָ�ơ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId3 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ������鱨")
			AddQuestText(sceneId,"   ̫���ˣ���������鱨�����ǾͶ����ر����ľ�����������ָ�ơ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300733_g_MissionId4 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ���ɽ�鱨")
			AddQuestText(sceneId,"   ̫���ˣ���������鱨�����ǾͶ���ɽ�����ľ�����������ָ�ơ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��75��")
			AddQuestText(sceneId," ")
		else
			return -1;
		end

		
		
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300733_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300733_QuestLogRefresh( sceneId, selfId, MissionId)

	
	local ret = x300733_CheckSubmit( sceneId, selfId, MissionId )

	
	
	local str = "";

	if MissionId == x300733_g_MissionId1 then
		
		if ret>0 then
			str = "  ��@npc_30003���ػͰ�����ȡ@npc_30027��1/1��"
		else
			str = "  ��@npc_30003���ػͰ�����ȡ@npc_30027��0/1��"
		end
	elseif MissionId == x300733_g_MissionId2 then
		if ret>0 then
			str = "  ��@npc_30000��¥��������ȡ@npc_30024��1/1��"
		else
			str = "  ��@npc_30000��¥��������ȡ@npc_30024��0/1��"
		end
	elseif MissionId == x300733_g_MissionId3 then
		if ret>0 then
			str = "  ��@npc_30002�����ذ�����ȡ@npc_30026��1/1��"
		else
			str = "  ��@npc_30002�����ذ�����ȡ@npc_30026��0/1��"
		end
	elseif MissionId == x300733_g_MissionId4 then
		if ret>0 then
			str = "  ��@npc_30001����ɽ������ȡ@npc_30025��1/1��"
		else
			str = "  ��@npc_30001����ɽ������ȡ@npc_30025��0/1��"
		end
	else
		return -1;
	end
		
	BeginQuestEvent(sceneId)	
	local level = GetLevel(sceneId, selfId)
		local ExpBonus1 = 100*2.6*5 * level
		local ExpBonus2 = 1750 * level
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
							"�����ҡ��й��鱨",        -- ��������
							str,		--����Ŀ��
							"@npc_125502",			--����NPC
							"ͨ��@npc_125509Ǳ��й�����������ȡ��Ҫ���鲢���鱨�ͻر�����\n¥�������鱨���꣨156��131��\n��ɽ�����鱨���꣨111��133��\n���ذ����鱨���꣨152��137��\n�ػͰ����鱨���꣨116��134��",               --������
							"֪��֪�ˣ���ս���������ǵ���̽�������ͻ�һЩ��Ҫ���鱨��",	--��������
							"�����ڳ������ڼ�ظ�����ʱ���㽫���˫���Ľ�����"					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		

end

function x300733_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300733_QuestLogRefresh( sceneId, selfId, MissionId );
end


function x300733_OnGetTargetItem( sceneId, selfId, MissionId)
	
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
	x300733_QuestLogRefresh( sceneId, selfId, MissionId)
end