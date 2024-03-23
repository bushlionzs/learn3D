--***********************
--Const
--***********************
-------------------------

--MisDescBegin


x300860_g_MissionId 				= 	7569                     --����ID
x300860_g_ScriptId 					= 	300860                  --�ű�ID
x300860_g_MissionKind 				= 	1                       --��������
x300860_g_LevelLess					= 	30                      --�������ŵȼ�  <=0 ��ʾ������


x300860_g_MissionName				= 	"�����ҡ������ر�"
x300860_g_MissionTarget				= 	"�ҹ������ٵй����ص�ɧ�ź���в����Ҫ��ҹ�ͬ�����������߹ء���Ը����ܴ����������߹�һ��ʱ����"
x300860_g_MissionInfo				= 	"����������󣬾���һ��ʱ�伴�����һ㱨���飬���������õ�������������#G��ʱ��#W���#R��ɫ#Wʱ�Ϳ�׼������#G�ظ�#W�ˣ���#G���#Wʱ�䣬����ͻ�#Gʧ��#W������ע��ʱ�䡣"
x300860_g_ContinueInfo				= 	"�㻹�ڵ�ʲô����ȥ�ر�"
x300860_g_MissionCompleted			= 	"�ر����"
x300860_g_MissionHelp				=	"  #W�����ڼ����������߻�ʱ�������Զ��ó�ʧ��״̬��������������ȡ��"          --������ʾ��Ϣ

--Ŀ��
x300860_g_ExtTarget					=	{ {type=20,n=1,target="�ر�"}}

--����

x300860_g_ExpBonus					= 	0;--x300860_AddExpAward               	--����������
x300860_g_BonusItem					=	{}	--��������Ʒ

x300860_g_BonusMoney1               = 	0
x300860_g_BonusMoney2               =   0
x300860_g_BonusMoney3               =   0

x300860_g_BonusChoiceItem           =   {}


--MisDescEnd

x300860_g_Mission_Id				=	7569

x300860_g_DayCountLimited			=	3
x300860_g_BuffId					=	7765		


function x300860_GetMissionId( sceneId, selfId )
	return x300860_g_Mission_Id
end

function x300860_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	local level = GetLevel( sceneId,selfId )
    if level < x300860_g_LevelLess then
       return
    end

	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	
	
	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		
		AddQuestNumText(sceneId, myMissionId, x300860_g_MissionName,8,1);
	else
		local state = GetQuestStateNM(sceneId, selfId, targetId, myMissionId);

		
		AddQuestNumText(sceneId, myMissionId, x300860_g_MissionName,state,state);

	end


	
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300860_ProcEventEntry( sceneId, selfId, targetId, MissionId, nExt )
	local myMissionId = x300860_GetMissionId( sceneId, selfId )	
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) == 0 then
		x300860_DispatchMissionInfo( sceneId, selfId, targetId, myMissionId, 0 )
	else
		if nExt==7 then -- �������
			x300860_DispatchCompletedInfo( sceneId, selfId, targetId,myMissionId )
		
		else
			
			x300860_DispatchContinueInfo( sceneId, selfId, targetId,myMissionId )
		end
	end
end


function x300860_ProcAcceptCheck(sceneId, selfId, targetId, MissionId )

	return 1;

end

function x300860_CheckRequest(sceneId, selfId)
	local myMissionId = x300860_GetMissionId( sceneId, selfId )

	if GetLevel(sceneId, selfId) <x300860_g_LevelLess then
		x300860_ShowTips(sceneId, selfId, "��ȼ�����")
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, myMissionId ) > 0 then
		x300860_ShowTips(sceneId, selfId, "���Ѿ���������񣬽�������ʧ��")
		return 0;
	end

	if x300860_g_DayCountLimited >0 then
		local nDayCount = x300860_GetDayCount(sceneId, selfId)
		if nDayCount>= x300860_g_DayCountLimited then
			x300860_ShowTips(sceneId, selfId, "�ܱ�Ǹ�����Ѿ���ȡ���ˡ����ҡ������ر�����3�Σ������������ӣ�")
			return 0;
		end
	end

	return 1;

end

function x300860_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
	
	
	if x300860_CheckRequest(sceneId, selfId)<=0 then
		
		return 0;
	end

	local myMissionId = x300860_GetMissionId( sceneId, selfId )

	--------------------------- add for Mission full check --------------
	local bFullMission = IsQuestFullNM(sceneId,selfId)
	
	if bFullMission>0 then
		x300860_ShowTips(sceneId, selfId, "�����������޷���������")
		return 0
	end
	---------------------------- add end -------------------------------
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, myMissionId )
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

	local ret = AddQuestNM( sceneId, selfId, myMissionId ) -- ������������		
		
	if ret > 0 then
		local str = "������������:�����ҡ������ر�";
		x300860_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

		local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
		SetQuestByIndex( sceneId, selfId, misIndex, 5, 0 ) --Tick=0

		--CancelSpecificImpact( sceneId, selfId, x300860_g_BuffId)
		SendSpecificImpactToUnit(sceneId, selfId,selfId,selfId, x300860_g_BuffId,0 )

		
		return 1
	else
		
		x300860_ShowTips(sceneId, selfId, "�����������")
	
	end


end

function x300860_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x300860_ProcQuestAbandon( sceneId, selfId, MissionId )

	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local ret = DelQuestNM( sceneId, selfId, myMissionId )

	if ret>0 then

		local str = "������������:�����ҡ������ر�"
	    x300860_ShowTips(sceneId, selfId, str)
		Msg2Player(sceneId,selfId,str,8,2)

		CancelSpecificImpact(sceneId, selfId, x300860_g_BuffId);
		x300860_SetDayCount(sceneId, selfId)
	else
		x300860_ShowTips(sceneId, selfId, "��������ʧ��")
	end

	
end



function x300860_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	
	if x300860_CheckSubmit(sceneId, selfId )>0 then
		
		local ret = DelQuestNM( sceneId, selfId, myMissionId )

		if ret>0 then

			local str = "�����������:�����ҡ������ر�";
			x300860_ShowTips(sceneId, selfId, str)
			Msg2Player(sceneId,selfId,str,8,2)

			x300860_GiveReward(sceneId,selfId)

			
			x300860_SetDayCount(sceneId, selfId)
			x300860_SetSuccessCount(sceneId, selfId)

			CancelSpecificImpact( sceneId, selfId, x300860_g_BuffId)
			
		else
			x300860_ShowTips(sceneId, selfId, "������ʧ��")
		end
		
	end
end

function x300860_GiveReward(sceneId,selfId)
	--��������
	local level = GetLevel(sceneId, selfId)
	local ExpBonus1 = level*15000;
	local ExpBonus2 = level*15000;
	local ExpBonus = 0;
	if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			ExpBonus = ExpBonus1;
	elseif GetLevel(sceneId, selfId) >=70 then
			ExpBonus = ExpBonus2;
	end 
	local nDayCount = x300860_GetDayCount(sceneId, selfId)
    if nDayCount == 0 then
		local nExpBonus = floor(ExpBonus*0.15*0.3)
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 15);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����15��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		local Readme = "#o���#R����"..nExpBonus.."��#o�Ľ���#r#o���#R����15��#o�Ľ���"
  		Msg2Player(sceneId,selfId,Readme,4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "���#R�츳%s��#o�Ľ�����", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o���#R�츳"..refixtf.."��#o�Ľ���");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId, 15);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o�����������#R����"..nExpBonus.."��#o�Ľ���");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o������#R����15��#o�Ľ���");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o�����������#R����"..nExpBonus.."��#o�Ľ���",4,2)--#r#o������#R����15��#o�Ľ���",4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "������������츳#R%s��#o�Ľ�����", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o�����������#R�츳"..refixtf.."��#o�Ľ���");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
			-- local selfGuildId = GetGuildID(sceneId, selfId)
			-- local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
			
			-- if selfGuildId ~= -1 and countryGuildId == selfGuildId then
				-- AddExploit(sceneId,selfId,2)
				-- BeginQuestEvent(sceneId);
				-- AddQuestText(sceneId, "#o���#R��ѫ2��#o�Ľ���");
				-- EndQuestEvent();
				-- DispatchQuestTips(sceneId, selfId);	
				-- Msg2Player(sceneId,selfId,"#o���#R��ѫ2��#o�Ľ���",4,2)
			-- end
			
		end
	elseif nDayCount == 1 then
		local nExpBonus = floor(ExpBonus*0.5*0.3)
		AddExp(sceneId, selfId, nExpBonus);
		AddHonor(sceneId, selfId, 35);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����35��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		local Readme = "#o���#R����"..nExpBonus.."��#o�Ľ���#r#o���#R����35��#o�Ľ���"
  		Msg2Player(sceneId,selfId,Readme,4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "���#R�츳%s��#o�Ľ�����", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o���#R�츳"..refixtf.."��#o�Ľ���");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddHonor(sceneId, selfId, 35);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o�����������#R����"..nExpBonus.."��#o�Ľ���");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o������#R����35��#o�Ľ���");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);
			Msg2Player(sceneId,selfId,"#o�����������#R����"..nExpBonus.."��#o�Ľ���",4,2)--#r#o������#R����35��#o�Ľ���",4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "������������츳#R%s��#o�Ľ�����", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o�����������#R�츳"..refixtf.."��#o�Ľ���");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end			
			-- local selfGuildId = GetGuildID(sceneId, selfId)
			-- local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
			
			-- if selfGuildId ~= -1 and countryGuildId == selfGuildId then
				-- AddExploit(sceneId,selfId,2)
				-- BeginQuestEvent(sceneId);
				-- AddQuestText(sceneId, "#o���#R��ѫ2��#o�Ľ���");
				-- EndQuestEvent();
				-- DispatchQuestTips(sceneId, selfId);	
				-- Msg2Player(sceneId,selfId,"#o���#R��ѫ2��#o�Ľ���",4,2)			
			-- end
		end
	elseif nDayCount == 2 then
		local nExpBonus = floor(ExpBonus*0.5*0.7)
		AddExp(sceneId, selfId, nExpBonus);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����"..nExpBonus.."��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		
		local nExpBonus1 = 0

		
		--write log
		local msg = "guojiashoubian: name="..GetName(sceneId, selfId)..",guid="..GetPlayerGUID( sceneId,selfId )..",nSuccssCount="..x300860_GetSuccessCount(sceneId, selfId)

		WriteLog(1,msg)
		--write end


		if x300860_GetSuccessCount(sceneId, selfId)>=2 then
			nExpBonus1 = floor(ExpBonus*0.05)
			AddExp(sceneId, selfId, nExpBonus1);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o������#R����"..nExpBonus1.."��#o�Ľ���");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
		end

		AddHonor(sceneId, selfId, 50);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "#o���#R����50��#o�Ľ���");
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
		local Readme = ""
		if nExpBonus1==0 then
			Readme = "#o���#R����"..nExpBonus.."��#o�Ľ���#r#o���#R����50��#o�Ľ���"
		else
			Readme = "#o���#R����"..nExpBonus.."��#o�Ľ���#r#o���#R����50��#o�Ľ���#r������#R����"..nExpBonus1.."��#o�Ľ���"
  		
		end
		Msg2Player(sceneId,selfId,Readme,4,2)
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "���#R�츳%s��#o�Ľ�����", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o���#R�츳"..refixtf.."��#o�Ľ���");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
		local ret = CountryIsFortuneTime(sceneId,selfId,0)
		
		if ret == 1 then
			AddExp(sceneId, selfId, nExpBonus);
			--AddExp(sceneId, selfId, nExpBonus1);
			nExpBonus1 = 0;
			if x300860_GetSuccessCount(sceneId, selfId)>=2 then
				nExpBonus1 = floor(ExpBonus*0.05)
				AddExp(sceneId, selfId, nExpBonus1);
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o�����������#R����"..nExpBonus1.."��#o�Ľ���");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end

			--AddHonor(sceneId, selfId, 50);
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, "#o�����������#R����"..nExpBonus.."��#o�Ľ���");
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			
			--BeginQuestEvent(sceneId);
			--AddQuestText(sceneId, "#o������#R����50��#o�Ľ���");
			--EndQuestEvent();
			--DispatchQuestTips(sceneId, selfId);

			if nExpBonus1==0 then
				Msg2Player(sceneId,selfId,"#o�����������#R����"..nExpBonus.."��#o�Ľ���#o",4,2)--#r#o������#R����50��#o�Ľ���",4,2)
			else
				Msg2Player(sceneId,selfId,"#o�����������#R����"..nExpBonus.."��#o�Ľ���#o#r�����������#R����"..nExpBonus1.."��#o�Ľ���",4,2)--#r#o������#R����50��#o�Ľ���",4,2)
			end
			if GetLevel(sceneId, selfId) >=80 then
				local tf = 180
				local refixtf = AddInherenceExp( sceneId, selfId, tf)
				Msg2Player( sceneId, selfId, format( "������������츳#R%s��#o�Ľ�����", refixtf), 4, 2)
				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, "#o�����������#R�츳"..refixtf.."��#o�Ľ���");
				EndQuestEvent();
				DispatchQuestTips(sceneId, selfId);
			end
			-- local selfGuildId = GetGuildID(sceneId, selfId)
			-- local countryGuildId = GetCountryKingGuildId(sceneId, selfId)
			
			-- if selfGuildId ~= -1 and countryGuildId == selfGuildId then
				-- AddExploit(sceneId,selfId,2)
				-- BeginQuestEvent(sceneId);
				-- AddQuestText(sceneId, "#o���#R��ѫ2��#o�Ľ���");
				-- EndQuestEvent();
				-- DispatchQuestTips(sceneId, selfId);	
				-- Msg2Player(sceneId,selfId,"#o���#R��ѫ2��#o�Ľ���",4,2)
			-- end
			
		end
	end
end



function x300860_CheckSubmit(sceneId, selfId )
	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	if IsHaveQuestNM( sceneId, selfId, myMissionId ) <= 0 then	-- ������������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )
	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

	if bCompleted<=0 then
		return 0
	end

	return 1;
end








---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x300860_GetDayCount(sceneId, selfId)



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
function x300860_SetDayCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3], today)
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3], 1)
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2], DQ_SHOUBIAN_COUNT[3], 0)
	else
		local daycount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3])
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DAYCOUNT[1], DQ_SHOUBIAN_DAYCOUNT[2], DQ_SHOUBIAN_DAYCOUNT[3], daycount+1)
	end
	
	
	
end


---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ�ɹ�����
---------------------------------------------------------------------------------------------------
function x300860_GetSuccessCount(sceneId, selfId)



	local today = GetDayOfYear()
	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2],DQ_SHOUBIAN_DATE[3] );
	
	if lastday ~= today then
		return 0
	end

	local nCount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2],DQ_SHOUBIAN_COUNT[3] );
	return nCount;



	

end

---------------------------------------------------------------------------------------------------
--���õ���ɹ�����
---------------------------------------------------------------------------------------------------
function x300860_SetSuccessCount(sceneId, selfId)

	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3])

	if lastday ~= today then
		--SetQuestData(sceneId, selfId, DQ_SHOUBIAN_DATE[1], DQ_SHOUBIAN_DATE[2], DQ_SHOUBIAN_DATE[3], today)
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2], DQ_SHOUBIAN_COUNT[3], 1)
	else
		local nCount = GetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2], DQ_SHOUBIAN_COUNT[3])
		SetQuestData(sceneId, selfId, DQ_SHOUBIAN_COUNT[1], DQ_SHOUBIAN_COUNT[2], DQ_SHOUBIAN_COUNT[3], nCount+1)
	end
	
	
	
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷���������Ϣ
---------------------------------------------------------------------------------------------------
function x300860_DispatchMissionInfo( sceneId, selfId, NPCId, MissionId, nExt )

	
	
	BeginQuestEvent(sceneId)

		
	local nDayCount = x300860_GetDayCount(sceneId, selfId)
	--������Ϣ
	AddQuestText(sceneId,"#Y".."�����ҡ������ر�")
	AddQuestText(sceneId,"  �ҹ������ٵй����ص�ɧ�ź���в����Ҫ��ҹ�ͬ������������������Ը����ܴ�������������һ��ʱ����")
	AddQuestText(sceneId," ")

	--����Ŀ��
	AddQuestText( sceneId,"#Y����Ŀ�꣺")
	AddQuestText( sceneId,"  �����������������������@npc_128511����������ÿ��һ��ʱ�䣬���Զ���þ��齱��������һ��ʱ�伴�����һ㱨���飬���������õ����������ﵽ80��ʱ�ɻ���츳ֵ������")
	AddQuestText( sceneId," ")

	if nDayCount == 0 then
		local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.15*0.3
		local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.15*0.3
		local localexp = 0
		if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			localexp = localexp1;
		elseif GetLevel(sceneId, selfId) >=70 then
			localexp = localexp2;
		end 
		if GetLevel(sceneId, selfId) >=80 then
			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��15��#r  �츳ֵ��180��")
			AddQuestText(sceneId," ")	
		else
		AddQuestText(sceneId,"#Y��������")
		AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��15��")
		AddQuestText(sceneId," ")
		end	
	elseif nDayCount == 1 then	
		local localexp1 = (GetLevel( sceneId, selfId )) * 15000* 0.3*0.5
		local localexp2 = (GetLevel( sceneId, selfId )) * 15000* 0.3*0.5
		local localexp = 0
		if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			localexp = localexp1;
		elseif GetLevel(sceneId, selfId) >=70 then
			localexp = localexp2;
		end 
		if GetLevel(sceneId, selfId) >=80 then
			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��35��#r  �츳ֵ��180��")
			AddQuestText(sceneId," ")	
		else
		AddQuestText(sceneId,"#Y��������")
		AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��35��")
		AddQuestText(sceneId," ")
		end	
	elseif nDayCount == 2 then
		local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.5*0.7
		local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.5*0.7
		local localexp = 0
		if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
			localexp = localexp1;
		elseif GetLevel(sceneId, selfId) >=70 then
			localexp = localexp2;
		end 
		if GetLevel(sceneId, selfId) >=80 then
			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��50��#r  �츳ֵ��180��")
			AddQuestText(sceneId," ")	
		else
		AddQuestText(sceneId,"#Y��������")
		AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��50��")
		AddQuestText(sceneId," ")
		end	
	end
		
		

	EndQuestEvent()
	
	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300860_g_ScriptId, MissionId,0);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300860_DispatchContinueInfo( sceneId, selfId, NPCId,MissionId )

	BeginQuestEvent(sceneId)
		local nDayCount = x300860_GetDayCount(sceneId, selfId)
		AddQuestText(sceneId,"#Y�����ҡ������ر�#r")

		AddQuestText( sceneId,"  �����ر�ʱ��δ������ȥ����������#r")
	
		AddQuestText(sceneId,"#Y����С��ʾ��")
		AddQuestText(sceneId,"  ��@npc_128511����������ÿ��һ��ʱ�䣬���Զ���þ��齱����#r")
		if nDayCount == 0 then
			local localexp1 = (GetLevel( sceneId, selfId ))* 15000 *0.15*0.3
			local localexp2 = (GetLevel( sceneId, selfId ))* 15000 *0.15*0.3
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y��������")
				AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��15��#r  �츳ֵ��180��")
				AddQuestText(sceneId," ")	
			else
				AddQuestText(sceneId,"#Y��������")
				AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��15��")
				AddQuestText(sceneId," ")
			end	
			elseif nDayCount == 1 then	
			local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.3*0.5
			local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.3*0.5
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y��������")
				AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��35��#r  �츳ֵ��180��")
				AddQuestText(sceneId," ")	
			else
				AddQuestText(sceneId,"#Y��������")
				AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��35��")
				AddQuestText(sceneId," ")
			end	
			
			elseif nDayCount == 2 then
			local localexp1 = (GetLevel( sceneId, selfId ))* 15000*0.5*0.7
			local localexp2 = (GetLevel( sceneId, selfId ))* 15000*0.5*0.7
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y��������")
				AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��50��#r  �츳ֵ��180��")
				AddQuestText(sceneId," ")	
			else
				AddQuestText(sceneId,"#Y��������")
				AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��50��")
				AddQuestText(sceneId," ")
			end	
				
			
			end
		

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300860_g_ScriptId, MissionId,0);
	


end

---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300860_DispatchCompletedInfo( sceneId, selfId, NPCId,MissionId )
	

	BeginQuestEvent(sceneId)
		local nDayCount = x300860_GetDayCount(sceneId, selfId)
		--������Ϣ
		AddQuestText(sceneId,"#Y�����ҡ������ر�")
		AddQuestText(sceneId,"  �õģ��ǳ���л��������Э�����ر��������ǵı����ȶ���ࡣ")
		if nDayCount == 0 then
			local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.15*0.3
			local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.15*0.3
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y��������")
				AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��15��#r  �츳ֵ��180��")
				AddQuestText(sceneId," ")	
			else
			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��15��")
			AddQuestText(sceneId," ")
			end	
	
		elseif nDayCount == 1 then	
			local localexp1 = (GetLevel( sceneId, selfId )) * 15000* 0.3*0.5
			local localexp2 = (GetLevel( sceneId, selfId )) * 15000* 0.3*0.5
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end 
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y��������")
				AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��35��#r  �츳ֵ��180��")
				AddQuestText(sceneId," ")	
			else
			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��35��")
			AddQuestText(sceneId," ")
			end	
	
		elseif nDayCount == 2 then
			local localexp1 = (GetLevel( sceneId, selfId )) * 15000*0.5*0.7
			local localexp2 = (GetLevel( sceneId, selfId )) * 15000*0.5*0.7
			local localexp = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				localexp = localexp1;
			elseif GetLevel(sceneId, selfId) >=70 then
				localexp = localexp2;
			end
			if GetLevel(sceneId, selfId) >=80 then
				AddQuestText(sceneId,"#Y��������")
				AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��50��#r  �츳ֵ��180��")
				AddQuestText(sceneId," ")	
			else
			AddQuestText(sceneId,"#Y��������")
			AddQuestText(sceneId,"  ����ֵ��"..floor(localexp).."��#r  ����ֵ��50��")
			AddQuestText(sceneId," ")
			end	
		
	
	end

		--����Ŀ��
		--AddQuestText( sceneId,"#Y����Ŀ�꣺")
		--AddQuestText( sceneId,"�����ʾbbbbbbb")
		--AddQuestText( sceneId," ")

		--AddQuestText(sceneId,"#Y������ʾ��")
		--AddQuestText(sceneId,"���ccccccc" )
		--AddQuestText(sceneId," ")
		
		
	EndQuestEvent()
	DispatchQuestContinueInfoNM(sceneId, selfId, NPCId, x300860_g_ScriptId, MissionId);
	CallScriptFunction( 256289, "FinishShoubian", sceneId, selfId)
end





---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300860_QuestLogRefresh( sceneId, selfId, MissionId)
	local ret = x300860_CheckSubmit(sceneId, selfId )
	local str=""
	if ret==1 then
		str = "�ر�(1/1)"
	else
		str= "�ر�(0/1)"
	end
	
		
	BeginQuestEvent(sceneId)	
			local level = GetLevel(sceneId, selfId)
			local nExpBonus1 = level*15000
			local nExpBonus2 = level*15000
			local nExpBonus = 0
			if GetLevel(sceneId, selfId) >=30 and GetLevel(sceneId, selfId) < 70 then
				nExpBonus = nExpBonus1;
			elseif GetLevel(sceneId, selfId) >=70 then
				nExpBonus = nExpBonus2;
			end
			local nDayCount = x300860_GetDayCount(sceneId, selfId)
			if nDayCount == 0 then
				local level =GetLevel (sceneId,selfId)
				local ExpBonus = floor(nExpBonus *0.15*0.3)
				if level >=80 then
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 15 )
					AddQuestInherenceExpBonus(sceneId,180)
				else
					AddQuestExpBonus(sceneId,  ExpBonus);
					AddQuestMoneyBonus6(sceneId, 15 )
				end
			elseif nDayCount == 1 then
				local level =GetLevel (sceneId,selfId)
				local ExpBonus = floor(nExpBonus *0.5*0.3)
				if level >=80 then
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 35 )
					AddQuestInherenceExpBonus(sceneId,180)
				else
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 35 )
				end
			elseif nDayCount == 2 then
				local ExpBonus = floor(nExpBonus *0.5*0.7)
				if level >=80 then
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 50 )
					AddQuestInherenceExpBonus(sceneId,180)
				else
				AddQuestExpBonus(sceneId,  ExpBonus);
				AddQuestMoneyBonus6(sceneId, 50 )
			end		
			end		
		
	AddQuestLogCustomText( sceneId,
							"",						-- ����
							"�����ҡ������ر�",        -- ��������
							"  פ�ر���10����",		--����Ŀ��
							"@npc_128510",			--����NPC
							"",               --������
							"  �����������������������@npc_128511����������ÿ��һ��ʱ�䣬���Զ���þ��齱��������һ��ʱ�伴����@npc_128510�㱨���飬���������õ����������ﵽ80��ʱ�ɻ���츳ֵ������",	--��������
							"  �����ڹ������ڼ�ظ�����ʱ���㽫���˫���ľ��齱����"					--����С��ʾ
							)
	EndQuestEvent()
	DispatchQuestLogUpdate(sceneId, selfId, MissionId);
	

end

function x300860_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	
	x300860_QuestLogRefresh( sceneId, selfId, MissionId );
end

--// system function start
function x300860_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	
end

function x300860_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

function x300860_ProcessQuestFail(sceneId, selfId, MissionId)
end

function x300860_OnPlayerRelive(sceneId, selfId, nMode)
	
	local myMissionId = x300860_GetMissionId( sceneId, selfId )
	
	if IsHaveQuestNM(sceneId,selfId,myMissionId) <= 0 then
        return 
    end

	if nMode==nil then
		nMode =0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, myMissionId )


	if nMode==0 then
		if IsPlayerStateNormal(sceneId,selfId )<=0 then
			return
		end
	end

	


	

	local bCompleted = GetQuestParam( sceneId, selfId, misIndex, 7 )

	if bCompleted<1  then   --�������û�����
		
		if IsHaveSpecificImpact(sceneId, selfId, x300860_g_BuffId)<=0 then --���û��buff,���������Ѿ����
		
			SetQuestByIndex( sceneId, selfId, misIndex, 0, 1 )  
			SetQuestByIndex( sceneId, selfId, misIndex, 7, 1 )  
			x300860_QuestLogRefresh( sceneId, selfId, myMissionId)
			
			local msg =GetName(sceneId, selfId).."guojiashoubian: relive and no buff and set to completed"..nMode
			WriteLog(1,msg)
			
		end
	else  --������������
		--if IsHaveSpecificImpact(sceneId, selfId, x300860_g_BuffId)>0 then --����������buff, ˵�����쳣
		--
		--	SetQuestByIndex( sceneId, selfId, misIndex, 0, 0 )  
		--	SetQuestByIndex( sceneId, selfId, misIndex, 7, 0 )  
		--	x300860_QuestLogRefresh( sceneId, selfId, myMissionId)
		--	
		--end
	end
end

function x300860_OnPlayerLogin(sceneId, selfId)
	x300860_OnPlayerRelive(sceneId, selfId, 1)
end


--// system end




