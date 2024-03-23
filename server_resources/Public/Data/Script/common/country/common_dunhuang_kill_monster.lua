
--MisDescBegin

x300879_g_ScriptId 					= 	300879                  --�ű�ID


x300879_g_MissionKind 				= 	1                       --��������
x300879_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������





x300879_g_MissionName				= 	"�й���ɱ"
x300879_g_MissionTarget				= 	""
x300879_g_MissionInfo				= 	""
x300879_g_ContinueInfo				= 	""
x300879_g_MissionCompleted			= 	""
x300879_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300879_g_ExtTarget					=	{ {type=20,n=10,target="��ô�ɱ"}}

--����

x300879_g_ExpBonus					= 	0;--x300879_AddExpAward               	--����������
x300879_g_BonusItem					=	{}	--��������Ʒ

x300879_g_BonusMoney1               = 	0
x300879_g_BonusMoney2               =   0
x300879_g_BonusMoney3               =   0

x300879_g_BonusChoiceItem           =   {}


--MisDescEnd


x300879_g_KillMissionId =  7007

x300879_g_DayCountLimited   = 1

x300879_g_Mis_Count = 1
x300879_g_ItemID = 13010021         --�ϳɺ����ƷID
x300879_g_NeedItem1 = 13011007 --���Ҫ������Ʒ
x300879_g_NeedItem2 = 13011008
x300879_g_NeedItemID = 13011009
--x300879_g_Fail = MD_COUNTRY_KILLMONSTER_ABANDON
x300879_g_LevelNeeded = 100

x300879_g_MissionId1 = 7659
x300879_g_MissionId2 = 7650
x300879_g_MissionId3 = 7656
x300879_g_MissionId4 = 7653
x300879_g_CountryDunhuang =  351--�ĸ����ҵĳ���id
x300879_g_CountryLouLan =  51
x300879_g_CountryKunlun = 251
x300879_g_CountryLaiYin = 151


x300879_g_NeedItemCount = 1


x300879_g_MissionBonusInfo			= 	"#Y��þ���#R%d#Y�Ľ�����"
         
function x300879_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

end

--ѡ������
function x300879_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )

	----PrintStr("x300879_ProcEventEntry")

	if index ~= -1 then
		MissionId = index
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		
		--��Ҫ����npc����û������������ʾ��
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- ������Խ��������
			--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
			x300879_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
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
		if x300879_CheckSubmit( sceneId, selfId, MissionId ) > 0 then -- �������������
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
			x300879_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
			x300879_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
				
end

function x300879_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )

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

--�������
--����1����ɹ���0��������ʧ��
function x300879_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	--if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then
	if x300879_CheckSubmit( sceneId, selfId, MissionId )>0 then
		x300879_MissionComplate(sceneId, selfId, targetId, selectId, MissionId)
	end

	return 0
end

function x300879_CheckSubmit( sceneId, selfId, MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId) == 0 then
		return 0;
	end

	if MissionId ~= x300879_g_MissionId1 and MissionId ~= x300879_g_MissionId2 and MissionId ~= x300879_g_MissionId3 and MissionId ~= x300879_g_MissionId4 then
		return 0;
	end

	local ItemCnt = GetItemCount( sceneId, selfId, x300879_g_NeedItemID )

	if ItemCnt<x300879_g_NeedItemCount then
		return 0;
	end

	return 1;


end

--********************************************************************
--����
--********************************************************************
function x300879_ProcQuestAbandon( sceneId, selfId,MissionId )
	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local n = GetItemCount( sceneId, selfId, x300879_g_NeedItemID );

	if MissionId == x300879_g_MissionId1 then
		x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_DUNHUANG_DATE,DQ_SHAGUAI_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId2 then
		x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_LOULAN_DATE,DQ_SHAGUAI_LOULAN_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId3 then
		x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_KUNLUN_DATE,DQ_SHAGUAI_KUNLUN_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId4 then
		x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_LAIYIN_DATE,DQ_SHAGUAI_LAIYIN_DAYCOUNT)
	else
		return -1;
	end
	
	if n > 0 then
		DelItem(sceneId, selfId,x300879_g_NeedItemID,n)
		
	end


	DelQuestNM( sceneId, selfId, MissionId )
	    BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "������������:�����ҡ��й���ɱ");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"������������:�����ҡ��й���ɱ",8,2)


end


--********************************************************************
--����
--********************************************************************
function x300879_ProcQuestAccept( sceneId, selfId, targetId, MissionId )

	
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ������������ֱ���˳�
		return 0
	end


	if	IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId4 ) > 0 then
		BeginQuestEvent(sceneId)
		local strText = "���Ѿ��ӹ��ˡ����ҡ��й���ɱ���񣬻�δ��ɣ������ٽ�ȡ"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		Msg2Player(sceneId,selfId,"���Ѿ��ӹ��ˡ����ҡ��й���ɱ���񣬻�δ��ɣ������ٽ�ȡ",8,2)
		return
	end

	local nDayCount =0;

	if MissionId == x300879_g_MissionId1 then
		nDayCount = x300879_GetDayCount(sceneId, selfId, DQ_SHAGUAI_DUNHUANG_DATE,DQ_SHAGUAI_DUNHUANG_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId2 then
		nDayCount = x300879_GetDayCount(sceneId, selfId, DQ_SHAGUAI_LOULAN_DATE,DQ_SHAGUAI_LOULAN_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId3 then
		nDayCount = x300879_GetDayCount(sceneId, selfId, DQ_SHAGUAI_KUNLUN_DATE,DQ_SHAGUAI_KUNLUN_DAYCOUNT)
	elseif MissionId == x300879_g_MissionId4 then
		nDayCount = x300879_GetDayCount(sceneId, selfId, DQ_SHAGUAI_LAIYIN_DATE,DQ_SHAGUAI_LAIYIN_DAYCOUNT)
	else
		return -1;
	end

	if nDayCount>=x300879_g_DayCountLimited then
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
			--hf_MissionAfterAccept(sceneId, selfId, MissionId);
			--hf_DisplayAcceptMessage(sceneId, selfId, MissionId);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "������������:�����ҡ��й���ɱ");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"������������:�����ҡ��й���ɱ",8,2)
			return 1
		else
			--hf_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
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



--ɱ������
function x300879_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
	
	----PrintStr(objdataId)
	if x300879_CountryCheck( sceneId, selfId, MissionId ) < 0 then
		return -1;
	end

	if objdataId ~= 9510 then
		return -1;
	end

	local sign = 0;
	local ItemCount=0;
	local ItemID=0;
	local ItemRand=0;
	local ItemDropNum=0;
	local droprand = 0;
	--����ID, �Լ���ID, �����λ�ú�, ����objId, ����ID
	local NeedKilledNum, InstIndex, ObjName = GetQuestNeedKillObjInfoNM( sceneId, selfId, MissionId, objdataId, objId )
	
	----PrintNum(NeedKilledNum)
	----PrintNum(InstIndex)
	----PrintStr(ObjName)


		if NeedKilledNum >= 0 then
			local x,z = GetWorldPos(sceneId,selfId)
			
			local KilledNum =  GetNearCountryCount(sceneId, selfId,x,z,20)  
			
			
			for i = 0, KilledNum-1 do
				local humanObjId = GetNearCountryMember(sceneId, selfId,i) --ȡ��ӵ�з���Ȩ���˵�objId
				--PrintNum(humanObjId)
				if humanObjId ~= -1 then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if GetHp(sceneId, humanObjId) > 0 then
							if IsHaveQuestNM( sceneId, humanObjId, MissionId ) > 0 then	--��������ӵ������
								------PrintNum(77)
								if InstIndex >= 0 then
									if sign == 0 then
										------PrintNum(88)
										ItemCount, ItemID, ItemRand, ItemDropNum = GetQuestItemNM( sceneId, humanObjId, MissionId, InstIndex )
										----PrintNum(ItemCount)
										----PrintNum(ItemID)
										----PrintNum(ItemRand)
										----PrintNum(ItemDropNum)
										droprand = random(100)
										sign = 1;
									end
									
											--Ҫ�ռ��ĸ�������ƷID�������ʣ�һ��������
									if HaveItem( sceneId, humanObjId, ItemID ) <  x300879_g_NeedItemCount then --���û�������Ʒ 
									
										if ItemCount > 0 then
											
											if droprand<= ItemRand then
											
												BeginAddItem(sceneId)
												AddItem( sceneId, ItemID, 1 )
												local ret = EndAddItem(sceneId,humanObjId)
												if ret > 0 then
													--AddItemListToPlayer(sceneId,selfId)
													AddItemListToPlayer(sceneId,humanObjId)
													
												else
													BeginQuestEvent(sceneId)
													AddQuestText(sceneId,"��Ʒ���������޷��õ�������Ʒ��")
													EndQuestEvent(sceneId)
													DispatchQuestTips(sceneId,humanObjId)
												end
											end
												
										end
										
									end
								end
							end
						end
					end
				end
			end
		end

	return 0
	
end


--��Ʒ�ı�
function x300879_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )--Ѱ�Ҳ��ϵ�������ɺ�����Ӻϳ�����

	----PrintStr("x300879_ProcQuestItemChanged")
	----PrintNum(itemdataId)
	----PrintNum(MissionId)
	--if x300879_CountryCheck( sceneId, selfId, MissionId ) < 0 then
	--	return 
	--end

	if IsPlayerStateNormal(sceneId, selfId) == 0 then
		return 
	end

	if GetHp(sceneId, selfId) <= 0 then
		return
	end

	
	if MissionId == nil or MissionId < 0 then
        return 
    end
    
    if IsHaveQuestNM(sceneId,selfId,MissionId) <= 0 then
        return 
    end

	local NeedNum, ObjIndex = GetQuestNeedItemNumNM( sceneId, selfId, MissionId, itemdataId )
	--
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )

	if NeedNum > 0 then
		local Num = GetItemCount( sceneId, selfId, itemdataId ) 
		if Num < x300879_g_NeedItemCount then --��û���������
			--BeginQuestEvent(sceneId)
			local strText = format("��ɱ���˱�������: %d/%d#r�������Ʒ��������", Num, NeedNum)
			if strText == nil then
				strText = "";
			end
			--AddQuestText( sceneId, strText )
			--EndQuestEvent( sceneId )
			--DispatchQuestTips( sceneId, selfId )
   			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, Num )         --by zheng
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )
			x300879_QuestLogRefresh( sceneId, selfId, MissionId)
		elseif Num >= x300879_g_NeedItemCount then
			--�Ѿ��������
			BeginQuestEvent(sceneId)
			local strText = format( "��ɱ���˱�������: %d/%d", Num, NeedNum )
			if strText == nil then
				strText = "";
			end
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			BeginQuestEvent(sceneId)
			AddQuestText( sceneId, "�������Ʒ��������" )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			--PrintNum(ObjIndex)
			SetQuestByIndex( sceneId, selfId, misIndex, ObjIndex, x300879_g_NeedItemCount )         --by zheng

			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			x300879_QuestLogRefresh( sceneId, selfId, MissionId)
		end
	end
	return 0
	
end


function x300879_MissionComplate(sceneId, selfId, targetId, selectId, MissionId)

    if MissionId == nil or MissionId < 0 then
        return 0
    end
    
    if IsHaveQuestNM( sceneId,selfId,MissionId )<= 0 then
        return 0
    end
    

	local ret = QuestComplateNM( sceneId, selfId, targetId, MissionId, selectId ) -- ��ȡ���������Ϣ
	if ret == 1 then -- ����ɹ����
		if MissionId == x300879_g_MissionId1 then
			x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_DUNHUANG_DATE,DQ_SHAGUAI_DUNHUANG_DAYCOUNT)
		elseif MissionId == x300879_g_MissionId2 then
			x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_LOULAN_DATE,DQ_SHAGUAI_LOULAN_DAYCOUNT)
		elseif MissionId == x300879_g_MissionId3 then
			x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_KUNLUN_DATE,DQ_SHAGUAI_KUNLUN_DAYCOUNT)
		elseif MissionId == x300879_g_MissionId4 then
			x300879_SetDayCount(sceneId, selfId, DQ_SHAGUAI_LAIYIN_DATE,DQ_SHAGUAI_LAIYIN_DAYCOUNT)
		else
			return -1;
		end
		
		local ItemCnt = GetItemCount( sceneId, selfId, x300879_g_NeedItemID )
		if ItemCnt > 0 then --˫������
			DelItem(sceneId, selfId,x300879_g_NeedItemID,ItemCnt)	
		else	
		end	
		--��ʾ����������
		--hf_DisplayCompleteMessage(sceneId, selfId, MissionId);
		--hf_DisplayAwardInfo(sceneId, selfId, targetId, MissionId, selectId)--��ʾ��ҽ�Ǯ���������Ľ�����Ϣ
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "�����������:�����ҡ��й���ɱ");
		EndQuestEvent();
		Msg2Player(sceneId,selfId,"�����������:�����ҡ��й���ɱ",8,2)

		DispatchQuestTips(sceneId, selfId);


		x300879_GiveReward(sceneId,selfId)
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
			local strMsg = format("CGL:<Info>x300879_MissionComplate sceneId=%d,country=%d", sceneId, country )
    		WriteLog( 1, strMsg )
		end
		
		return 1 -- ���سɹ�
	else -- ���δ�ɹ����
		--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(sceneId, selfId, ret);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "������ɴ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0
	end
	return 0

end

function x300879_GiveReward(sceneId,selfId)

	local level = GetLevel(sceneId, selfId)
	local nExpBonus1 = 100*2.6*level*5;
	local nExpBonus2 = 1750*level;
	local nExpBonus = 0;
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		nExpBonus = nExpBonus1;
	elseif GetLevel(sceneId, selfId) >=70 then
		nExpBonus = nExpBonus2;
	end
    if nExpBonus > 0 then
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 50);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����50��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
  		Msg2Player(sceneId,selfId,"#o���#R����"..nExpBonus.."��#o�Ľ���#r#o���#R����50��#o�Ľ���",4,2)
  			CallScriptFunction( 256271, "Finishcisha", sceneId, selfId)
		local ret = CountryIsFortuneTime(sceneId,selfId,1)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId, 50);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o�����������#R����"..nExpBonus.."��#o�Ľ���");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o������#R����50��#o�Ľ���");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o�����������#R����"..nExpBonus.."��#o�Ľ���",4,2)--#r#o������#R����50��#o�Ľ���",4,2)
			
			--�ݵ���⽱��
			local nCountry = GetCurCountry(sceneId,selfId)
			local nLairdCount,nLairdSumLevel =  CallScriptFunction(888888,"GetCountryLairdSceneInfo",sceneId,nCountry)
			if nLairdCount > 0 then
			
				local nLairdExpBonus = floor((nLairdSumLevel*0.02)*nExpBonus)
				local nLairdHornorBonus = floor((nLairdSumLevel*0.02)*50)
				
				
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

function x300879_OnLogInOrDie( sceneId, selfId )
	
   x300879_OnMissionFailed( sceneId, selfId )
end



function x300879_OnMissionFailed( sceneId, selfId )
	
	x300879_CountryKillOnDie(sceneId, selfId)

end

function x300879_CountryKillOnDie( sceneId, selfId )
	
	if 0==0 then
		return
	end
	

	
	local MissionId = -1
	if IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId1 ) > 0 then
		MissionId = x300879_g_MissionId1
	elseif IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId2 ) > 0 then
		MissionId = x300879_g_MissionId2
	elseif IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId3 ) > 0 then
		MissionId = x300879_g_MissionId3
	elseif IsHaveQuestNM( sceneId, selfId, x300879_g_MissionId4 ) > 0 then
		MissionId = x300879_g_MissionId4
	end
	if MissionId  ~= -1 then
		if GetItemCount( sceneId, selfId,x300879_g_NeedItemID ) > 0 then  --//����������
			return 0;
		end
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )
		SetQuestByIndex( sceneId, selfId, misIndex, 1, 0 )
	end
	
end

function x300879_CountryCheck( sceneId, selfId, MissionId )
	if MissionId == x300879_g_MissionId1 then
		if sceneId == x300879_g_CountryDunhuang then
			return 1
		end
	elseif MissionId == x300879_g_MissionId2 then
		if sceneId == x300879_g_CountryLouLan then
			return 1
		end
	elseif MissionId == x300879_g_MissionId3 then
		if sceneId == x300879_g_CountryKunlun then
			return 1
		end
	elseif MissionId == x300879_g_MissionId4 then
		if sceneId == x300879_g_CountryLaiYin then
			return 1
		end
	end
	return -1
end

function x300879_ProcQuestLogRefresh( sceneId,selfId,missionId)
	--local sceneName = CallScriptFunction( 300700, "GetSceneName", sceneId, selfId )
	local str = "#G������ܴ�Ԫ˧"
    BeginQuestEvent(sceneId)
        AddQuestLogCustomText( sceneId,
                                "",                    -- ����
                                "",                 -- ��������
                                "",               --����Ŀ��
                                str,                         --����NPC
                                "",                   --������
                                "",                --��������
                                ""        --����С��ʾ
                                )

	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, missionId);
end


---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300879_GetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)



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
function x300879_SetDayCount(sceneId, selfId, nDayIndex, nDayCountIndex)

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
function x300879_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300879_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId)

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5	
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300879_g_MissionId1 then
			AddQuestText(sceneId,"#Y�����ҡ��ػʹ�ɱ")
			--������Ϣ
			
			AddQuestText(sceneId,"   �ػ͵ı��������������������������ǣ��ڶػͱ����ģ�36��53����Ѳ�顣�ô�������������Ǳ������ɵ�������������Ȼ�������˰�������Я������ö#G������#W��������")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_134511�����͵��ػͱ�����ɱ���ػͱ�����36��53�����ı�����������ý����")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300879_g_MissionId2 then
			AddQuestText(sceneId,"#Y�����ҡ�¥����ɱ")
			--������Ϣ
			
			AddQuestText(sceneId,"   ¥���ı��������������������������ǣ���¥�������ģ�211��173����Ѳ�顣�ô�������������Ǳ������ɵ�������������Ȼ�������˰�������Я������ö#G������#W��������")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_134511�����͵�¥��������ɱ��¥��������211��173�����ı�����������ý����")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300879_g_MissionId3 then
			AddQuestText(sceneId,"#Y�����ҡ����ش�ɱ")
			--������Ϣ
			
			AddQuestText(sceneId,"   ���صı��������������������������ǣ������ر����ģ�212��58����Ѳ�顣�ô�������������Ǳ������ɵ�������������Ȼ�������˰�������Я������ö#G������#W��������")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_134511�����͵����ر�����ɱ�����ر�����212��58�����ı�����������ý����")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")
			
		elseif MissionId == x300879_g_MissionId4 then
			AddQuestText(sceneId,"#Y�����ҡ���ɽ��ɱ")
			--������Ϣ
			
			AddQuestText(sceneId,"   ��ɽ�ı��������������������������ǣ�����ɽ�����ģ�36��201����Ѳ�顣�ô�������������Ǳ������ɵ�������������Ȼ�������˰�������Я������ö#G������#W��������")
			AddQuestText(sceneId," ")

			--����Ŀ��
			AddQuestText( sceneId,"#Y����Ŀ�꣺")
			AddQuestText( sceneId,"  �ڱ��������ҵ�@npc_134511�����͵���ɽ������ɱ����ɽ������36��201�����ı�����������ý����")
			AddQuestText( sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")

		else
			return -1;
		end
		
			
		
		

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300879_g_ScriptId, MissionId,0);
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300879_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end
		if MissionId == x300879_g_MissionId1 then
			AddQuestText(sceneId,"#Y�����ҡ��ػʹ�ɱ")
		--������Ϣ
			
			AddQuestText(sceneId,"   �㻹��ĥ��ʲô�������Ƕػͱ������������ˣ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300879_g_MissionId2 then
			AddQuestText(sceneId,"#Y�����ҡ�¥����ɱ")
		--������Ϣ
			
			AddQuestText(sceneId,"   �㻹��ĥ��ʲô��������¥���������������ˣ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300879_g_MissionId3 then
			AddQuestText(sceneId,"#Y�����ҡ����ش�ɱ")
		--������Ϣ
			
			AddQuestText(sceneId,"   �㻹��ĥ��ʲô�����������ر������������ˣ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300879_g_MissionId4 then
			AddQuestText(sceneId,"#Y�����ҡ���ɽ��ɱ")
		--������Ϣ
			
			AddQuestText(sceneId,"   �㻹��ĥ��ʲô����������ɽ�������������ˣ�")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")
		else
			return -1;
		end
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300879_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300879_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
	local localexp1 = (GetLevel( sceneId, selfId )) * 100*2.6*5
	local localexp2 = (GetLevel( sceneId, selfId )) * 1750
	local localexp = 0
	if GetLevel(sceneId, selfId) >=40 and GetLevel(sceneId, selfId) < 70 then
		localexp = localexp1;
	elseif GetLevel(sceneId, selfId) >=70 then
		localexp = localexp2;
	end	
		if MissionId == x300879_g_MissionId1 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ��ػʹ�ɱ")
			AddQuestText(sceneId,"   ��л��ɵ�����ػ͵ı����������˴���Թ��������Ĺ��׼����Ҷ���Ϊ�����")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")
		elseif MissionId == x300879_g_MissionId2 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ�¥����ɱ")
			AddQuestText(sceneId,"   ��л��ɵ�����¥���ı����������˴���Թ��������Ĺ��׼����Ҷ���Ϊ�����")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
		elseif MissionId == x300879_g_MissionId3 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ����ش�ɱ")
			AddQuestText(sceneId,"   ��л��ɵ��������صı����������˴���Թ��������Ĺ��׼����Ҷ���Ϊ�����")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
		elseif MissionId == x300879_g_MissionId4 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ���ɽ��ɱ")
			AddQuestText(sceneId,"   ��л��ɵ�������ɽ�ı����������˴���Թ��������Ĺ��׼����Ҷ���Ϊ�����")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
		else
			return -1;
		end

		
		
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300879_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300879_QuestLogRefresh( sceneId, selfId, MissionId)

	
	local ret = x300879_CheckSubmit( sceneId, selfId, MissionId )

	
	
	local str = "";

	if MissionId == x300879_g_MissionId1 then
		if ret>0 then
			str = "  ��@npc_30015���ػͱ���ɱ��@npc_30023��1/1��"
		else
			str = "  ��@npc_30015���ػͱ���ɱ��@npc_30023��0/1��"
		end
	elseif MissionId == x300879_g_MissionId2 then
		if ret>0 then
			str = "  ��@npc_30012��¥������ɱ��@npc_30020��1/1��"
		else
			str = "  ��@npc_30012��¥������ɱ��@npc_30020��0/1��"
		end
	elseif MissionId == x300879_g_MissionId3 then
		if ret>0 then
			str = "  ��@npc_30014�����ر���ɱ��@npc_30022��1/1��"
		else
			str = "  ��@npc_30014�����ر���ɱ��@npc_30022��0/1��"
		end
	elseif MissionId == x300879_g_MissionId4 then
		if ret>0 then
			str = "  ��@npc_30013����ɽ����ɱ��@npc_30021��1/1��"
		else
			str = "  ��@npc_30013����ɽ����ɱ��@npc_30021��0/1��"
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
			AddQuestMoneyBonus6(sceneId, 50 )
		end		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							"�����ҡ��й���ɱ",        -- ��������
							str,		--����Ŀ��
							"@npc_134505",			--����NPC
							"ͨ��@npc_134511Ǳ��й�����ɱ������������\n¥�������������꣨211��173��\n��ɽ�����������꣨36��201��\n���ر����������꣨212��58��\n�ػͱ����������꣨36��53��",               --������
							"\t���գ��й��ı�������ͻȻ�����˴�������Ѳ���������������������ҹ���̽��ʧ���ء�\n\t���������������������ȥ��������Ǳ��й�����ɱ���ǵ�������������֣�����������������������������ң�",	--��������
							"�����ڳ������ڼ�ظ�����ʱ���㽫���˫���Ľ�����"					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		

end

function x300879_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300879_QuestLogRefresh( sceneId, selfId, MissionId );
end
