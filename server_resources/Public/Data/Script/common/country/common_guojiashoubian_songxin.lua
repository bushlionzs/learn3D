-------------------------
--Const
-------------------------

--MisDescBegin

x300738_g_ScriptId 					= 	300738                  --�ű�ID


x300738_g_MissionKind 				= 	1                       --��������
x300738_g_LevelLess					= 	40                      --�������ŵȼ�  <=0 ��ʾ������

x300738_g_MissionName				= 	""                --��������
x300738_g_MissionTarget				= 	""          --����Ŀ��
x300738_g_MissionInfo				= 	""            --������Ϣ
x300738_g_ContinueInfo				= 	""  --���������Ϣ
x300738_g_MissionCompleted			= 	""  --���������Ϣ
x300738_g_MissionHelp				=	""          --������ʾ��Ϣ

--Ŀ��
x300738_g_ExtTarget					=	{}


--����
x300738_g_ExpBonus		 			= 	0                    	--����������
x300738_g_BonusItem					=	{}	--��������Ʒ

x300738_g_BonusMoney1               = 	0       --������������
x300738_g_BonusMoney2               =   0       --�������ǰ�����
x300738_g_BonusMoney3               =   0       --�������󶨽��
x300738_g_BonusMoney4               =   0     --��������͢����
x300738_g_BonusMoney5               =   0     --��������������
x300738_g_BonusMoney6               =   0     --����������



x300738_g_BonusChoiceItem           =   {}


--MisDescEnd


x300738_g_DayCountLimited = 1

x300738_g_MissionBonusInfo			= 	"#Y��þ���#R%d#Y�Ľ�����"


x300738_g_Shoubian = {7563, 7569,7575,7584}
x300738_g_SendMail1 = {7564, 7570,7576,7585}
x300738_g_SendMail2 = {7565, 7571,7577,7586}

x300738_g_ShouBianCountryScene	= {51,151,251,351};

function x300738_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	----PrintStr("xcvxcsfsdf")
end

--ѡ������
function x300738_ProcEventEntry( sceneId, selfId, targetId, MissionId, index )
	--PrintStr("x300738_ProcEventEntry")

	if index ~= -1 then
		MissionId = index
	end

	--PrintNum(MissionId)

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		local missionId1 = 7564
		local missionId2 = 7570
		local missionId3 = 7576
		local missionId4 = 7585

		--local commitMissionId1 = 7565
		--local commitMissionId2 = 7571
		--local commitMissionId3 = 7577
		--local commitMissionId4 = 7586

		--local shoubian1 = 7584
		--local shoubian2 = 7563
		--local shoubian3 = 7575
		--local shoubian4 = 7569

		
		if IsHaveQuestNM( sceneId, selfId, missionId1 ) > 0 or IsHaveQuestNM( sceneId, selfId, missionId2 ) > 0 or IsHaveQuestNM( sceneId, selfId, missionId3 ) > 0 or IsHaveQuestNM( sceneId, selfId, missionId4 ) > 0 then			BeginQuestEvent(sceneId)
			local strText = "���Ѿ��ӹ��ˡ����ҡ������ر����񣬻�δ��ɣ������ٽ�ȡ"
			AddQuestText( sceneId, strText )
			EndQuestEvent( sceneId )
			DispatchQuestTips( sceneId, selfId )
			Msg2Player(sceneId,selfId,"���Ѿ��ӹ��ˡ����ҡ������ر����񣬻�δ��ɣ������ٽ�ȡ",8,2)
			return
		end

		local nCurrentDayCount = x300738_GetDayCount(sceneId, selfId)
		--PrintNum(nCurrentDayCount)
		if nCurrentDayCount>=x300738_g_DayCountLimited then
			--BeginQuestEvent(sceneId)
			--local strText = format("�������մ������ƣ���ǰ����%d���������ٽ�������", nCurrentDayCount)

			--AddQuestText( sceneId, strText )
			--EndQuestEvent( sceneId )
			--DispatchQuestTips( sceneId, selfId )
			--return
		end

		--��Ҫ����npc����û������������ʾ��
		local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
		if ret > 0 then	-- ������Խ��������
			--AddDispatchQuestInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����������Ϣ
			x300738_DispatchMissionInfo( sceneId, selfId, targetId, MissionId )
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
	else --������������( �����³̫��)
		local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
		if QuestCheckSubmitNM( sceneId, selfId, targetId, MissionId, misIndex ) > 0 then -- �������������
			--QuestComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ�����Ϣ
			x300738_DispatchCompletedInfo( sceneId, selfId, targetId,MissionId )
		else
			--QuestNotComplateInfoNM( sceneId, selfId, targetId, MissionId ) -- ��ʾ����δ�����Ϣ
			x300738_DispatchContinueInfo( sceneId, selfId, targetId,MissionId )
		end
	end
				
end

--��������
function x300738_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	----PrintStr("sdfsdf")
	if IsHaveQuestNM( sceneId, selfId, MissionId) >0 then
		return 0;
	end

	local nCurrentDayCount = x300738_GetDayCount(sceneId, selfId)

	if nCurrentDayCount>=x300738_g_DayCountLimited then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�ܱ�Ǹ�����Ѿ���ȡ���ˡ����ҡ������ر���������������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId,selfId,"�ܱ�Ǹ�����Ѿ���ȡ���ˡ����ҡ������ر���������������",8,2)
		return 0;
	end



	local ret = QuestCheckAcceptNM( sceneId, selfId, targetId, MissionId )
	
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
	
	if ret > 0 then	-- ������Խ�
	elseif ret ==-1 then  --�ȼ�����
		--hf_DisplayMissionAcceptErrorMessage(sceneId, selfId, ret);
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "��ȼ����ͣ����ܽ�������");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		return 0;
	elseif ret ==-2 then
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�������ȼ�����");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);

		return 0;

	end

	--CallScriptFunction(888891, "ProcQuestAccept", sceneId, selfId, targetId, MissionId)  --// ���ܹ����ر�����һ 

	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then	-- ������������ֱ���˳�
		return 0
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
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "������������:�����ҡ������ر�");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);

			Msg2Player(sceneId,selfId,"������������:�����ҡ������ر�",8,2)

			local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )
			return 1
		else
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

function x300738_SceneCheck(sceneId, selfId)


	local country = GetCurCountry(sceneId, selfId)
	if x300738_g_ShouBianCountryScene[country+1] == sceneId then
		return 1
	end
	return -1
end

function x300738_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	if  x300738_SceneCheck(sceneId, selfId)<0 then
		return
	end
	
	local missionId1 = 7564
	local missionId2 = 7570
	local missionId3 = 7576
	local missionId4 = 7585

	--PrintStr("sdfsdfcxv")    -- �����ʱ��������7564�� MissionList����������300378�ű��� ������npcΪ��³̫�ӣ� ���Ե㰢³̫�ӵ�ʱ�򣬻�������ProcQuestAttach
	if MissionId ~= missionId1 and MissionId ~= missionId2 and MissionId ~= missionId3 and MissionId ~= missionId4  then
		return
	end


	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û���������
		return
	end

	local npcName = GetName( sceneId, npcId )
	if npcName == "" then	--NPC���ֻ��ǿյ�ô
		return
	end

	local guid = GetQuestSubmitNPCGUIDNM( sceneId, selfId, misIndex )
	local  missionState = GetQuestStateNM(sceneId, selfId, npcId, MissionId)
	
	if guid == npcGuid then	--�����NPC�����ֺ�������NPC��������ͬ������Ҳ�жϹ���
		AddQuestTextNM( sceneId, selfId, npcId, MissionId, missionState, -1 ) -- ��ʾ������Ϣ
		
		
	end
	

	
	
	--CallScriptFunction(888891, "ProcQuestAttach", sceneId, selfId, npcId, npcGuid,misIndex, MissionId)
end

--�������
--����1����ɹ���0��������ʧ��
function x300738_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	
	
	local missionId1 = 7565
	local missionId2 = 7571
	local missionId3 = 7577
	local missionId4 = 7586
	
	if MissionId == missionId1 or MissionId == missionId2 or MissionId == missionId3 or MissionId == missionId4  then  --//����ǹ����ر���������2
		local ret = x300738_CheckSubmitSongxin2(sceneId, selfId,MissionId )
		if ret<=0 then
			return -1;
		end
		x300738_SetDayCount(sceneId, selfId)
		Msg2Player(sceneId,selfId,"�����������:�����ҡ������ر�",8,2)
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "�����������:�����ҡ������ر�");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		x300738_GiveReward(sceneId,selfId)
		DelQuestNM( sceneId, selfId, MissionId )
		return 1;
	end

	missionId1 = 7564
	missionId2 = 7570
	missionId3 = 7576
	missionId4 = 7585

	--PrintNum(MissionId)
	
	if MissionId == missionId1 or MissionId == missionId2 or MissionId == missionId3 or MissionId == missionId4  then  --//����ǹ����ر���������2
		
		 --Msg2Player(sceneId,selfId,"�ر�����1���",4,2)

		 
		 --PrintStr("scf")
		 DelQuestNM( sceneId, selfId, MissionId )


		 local country = GetCurCountry(sceneId, selfId);
		 
		 local iMissionID = x300738_g_Shoubian[country+1] ;
			

		 --local ret = AddQuestNM( sceneId, selfId, iMissionID ) ;
		 --if ret <= 0 then
		--	 Msg2Player(sceneId,selfId,"�����ر߳ɹ�",4,2)
		-- else
		--	Msg2Player(sceneId,selfId,"�����ر�ʧ��",4,2)
		-- end

		 CallScriptFunction(300734, "ProcQuestAccept", sceneId, selfId, targetId, iMissionID)
	end
	 

	--CallScriptFunction(888891, "ProcQuestSubmit", sceneId, selfId, targetId, selectId, MissionId )
end

function x300738_CheckSubmitSongxin2(sceneId, selfId,MissionId )
	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	
		return 0
	end

	return 1;
	
end


function x300738_GiveReward(sceneId,selfId)
	--��������
	local level = GetLevel(sceneId, selfId)
	local nExpBonus = 100*3.6*level*15;
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
		local Readme = "#o���#R����"..nExpBonus.."��#o�Ľ���#r#o���#R����50��#o�Ľ���"
  		Msg2Player(sceneId,selfId,Readme,4,2)
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret==1 then
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
		end
	end

	
end

--�������
function x300738_ProcQuestAbandon( sceneId, selfId, MissionId )
	--PrintNum(MissionId)
	local missionId1 = 7564
	local missionId2 = 7570
	local missionId3 = 7576
	local missionId4 = 7585
	if IsHaveQuestNM( sceneId, selfId, MissionId ) > 0 then
		DelQuestNM( sceneId, selfId, MissionId )

		local MissionName ="�����ҡ������ر�"
	
		local str = "�����������:"..MissionName;
		BeginQuestEvent(sceneId)
		AddQuestText( sceneId, str )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		Msg2Player( sceneId, selfId, str, 4, 2 )

		x300738_SetDayCount(sceneId, selfId)
		--CallScriptFunction(888891, "ProcQuestAbandon", sceneId, selfId, MissionId)
	end
end

function x300738_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
	CallScriptFunction(MISSION_SCRIPT, "ProcQuestItemChanged", sceneId, selfId, itemdataId, MissionId )
end

---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300738_GetDayCount(sceneId, selfId)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2],DQ_SHOUBIAN_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local daycount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2],DQ_SHOUBIAN_DAYCOUNT[3] );
	return daycount;
	

end

---------------------------------------------------------------------------------------------------
--���õ������
---------------------------------------------------------------------------------------------------
function x300738_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3], today)
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3], daycount+1)
	end
	
	
	
end


---------------------------------------------------------------------------------------------------
--���������ܽ��
---------------------------------------------------------------------------------------------------
function x300738_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300738_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId )

	BeginQuestEvent(sceneId)
		
		AddQuestText(sceneId,"#Y�����ҡ������ر�")
		AddQuestText( sceneId,"  �ҹ��������ŵй����ص�ɧ�ź���в����Ҫ��ҹ�ͬ��������������������Ҫ��������������������ȡ�����ر�������ɺ����һظ�����Ը����ܴ�����#r")

		AddQuestText(sceneId,"#Y����Ŀ�꣺")
		AddQuestText(sceneId,"  ��������������������ȡ�����ر����񣬳ɹ�����رߺ����һظ���������������ر�����#r" )
		
		AddQuestText(sceneId,"#Y����С��ʾ��")
		AddQuestText(sceneId,"  �����ڹ������ڼ�ظ�����ʱ���㽫���˫���Ľ�����")

	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300738_g_ScriptId, MissionId);
end

---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300738_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	BeginQuestEvent(sceneId)

		--������Ϣ
		AddQuestText(sceneId,"#Y".."�����ر�δ���")
		AddQuestText(sceneId,"aaaaaa")
		AddQuestText(sceneId," ")

		--����Ŀ��
		AddQuestText( sceneId,"#Y����Ŀ�꣺")
		AddQuestText( sceneId,"δ�����ʾbbbbbbb")
		AddQuestText( sceneId," ")

		AddQuestText(sceneId,"#Y������ʾ��")
		AddQuestText(sceneId,"δ���ccccccc" )
		AddQuestText(sceneId," ")
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300738_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300738_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	local bSendMail1 = 0
	for i,item in x300738_g_SendMail1 do
		if item== MissionId then
			bSendMail1 = 1
			break
		end
	end

	BeginQuestEvent(sceneId)
		if bSendMail1 ==1 then
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ������ر�#r")

			AddQuestText( sceneId,"  �ҹ������ٵй����ص�ɧ�ź���в����Ҫ��ҹ�ͬ������������������Ը����ܴ�������������һ��ʱ����#r")

			AddQuestText(sceneId,"#Y����Ŀ�꣺")
			AddQuestText(sceneId,"  ����������󣬾���һ��ʱ�伴�����һ㱨���飬���������õ������������ļ�ʱ����ɺ�ɫʱ�Ϳ�׼�����һظ��ˣ�����ʱ�䣬����ͻ�ʧ�ܣ�����ע��ʱ�䡣" )
	
			AddQuestText(sceneId,"#Y����С��ʾ��")
			AddQuestText(sceneId,"  �����ڼ����������߻�ʱ�������Զ��ó�ʧ��״̬��������������ȡ��#r")
			
		else
			local localexp = (GetLevel( sceneId, selfId )) * 100*3.6*15
			--������Ϣ
			AddQuestText(sceneId,"#Y�����ҡ������ر�#r")
			AddQuestText(sceneId,"  ��л��Ϊ���������Ĺ��ף��㽫��ô�ҵľ���")
			AddQuestText(sceneId," ")

			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..localexp.."��#r  ����ֵ��50��")
			
		end
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300738_g_ScriptId, MissionId);

end


---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300738_QuestLogRefresh( sceneId, selfId, MissionId)

	local bSendMail1 = 0
	for i,item in x300738_g_SendMail1 do
		if item== MissionId then
			bSendMail1 = 1
			break
		end
	end
	
		
	BeginQuestEvent(sceneId)
	
		if bSendMail1>0 then
			AddQuestLogCustomText( sceneId,
									"",						-- ����
									"�����ҡ������رߣ�1/3��",        -- ��������
									"  �����������������������Ǳ����Ĵ󽫣���������ʲô��Ҫ��æ�ģ�",		--����Ŀ��
									"@npc_129700",			--����NPC
									"",               --������
									"  �ҹ��������ŵй����ص�ɧ�ź���в����Ҫ��ҹ�ͬ��������������������ȥ�ұ�����������������������ʲôҪ��æ�ģ�",	--��������
									""					--����С��ʾ
									)
		else
			local level = GetLevel(sceneId, selfId)
			local ExpBonus = 100*3.6*15 * level
			if ExpBonus > 0 then
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 50 )
			end		
			AddQuestLogCustomText( sceneId,
									"",						-- ����
									"�����ҡ������رߣ�3/3��",        -- ��������
									"�ر������ĺ�³��",		--����Ŀ��
									"@npc_129058",			--����NPC
									"",               --������
									"�ѱ��������α����³��",	--��������
									"�����ڹ������ڼ�ظ�����ʱ���㽫���˫���Ľ�����"					--����С��ʾ
									)
		end
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
		

end

function x300738_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300738_QuestLogRefresh( sceneId, selfId, MissionId );
end



