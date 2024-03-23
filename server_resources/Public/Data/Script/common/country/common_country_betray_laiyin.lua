x300821_g_ScriptId	= 300821
x300821_g_curCountryID = 1
x300821_g_CountryTransPos = {
							[0] = {sceneid=50,posX=128,posZ=30},
							[1] = {sceneid=150,posX=128,posZ=30},
							[2] = {sceneid=250,posX=128,posZ=30},
							[3] = {sceneid=350,posX=128,posZ=30},
							}

function x300821_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
end

--�������ť������������ִ�д˽ű�
function x300821_ProcEventEntry( sceneId, selfId, targetId)		

	BeginQuestEvent(sceneId)

		local Readme_1 = "#Y�����ҡ�ǰ����ɽ#r#W #r"	
		local Readme_2 = "   ��ȷʵ��������еĹ�����ǰ����ɽ������չô��#r"
		local Readme_3 ="#G��ʾ������������������ʧ�����󣬲ſ��Խ��й����ı䣺#r"
		local Readme_4 ="#G1.����ʱ�������ߣ���ת����ͼ����ʱ��δ��ʧ��#r2.���ڻ���״̬ʱ��#r3.���ڱ���״̬�С�#r4.�������й��ҹ�ְ��#r5.�������˳���ᡣ#r"
		local Readme_5 ="#G6.�������״̬�¡�#r7.��������ɻ�������ϵ���������#r8.�����������޻�ʦͽ��ϵ��#r9.�����ϴθı����ʱ��С��һ�ܡ�"
		--local Readme_3 = "\t ȷ�Ϸ������������ѵ������𣿲߻�����....#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
		AddQuestText( sceneId,Readme)

	EndQuestEvent(sceneId)

	DispatchQuestEventList(sceneId,selfId,targetId);
	DispatchQuestInfo( sceneId, selfId, targetId, 300821, -1 );

end



--�����ȷ����
function x300821_ProcAcceptCheck( sceneId, selfId, NPCId )

	-- ֻ�ܵ�����
	-- if GetCountryRank(x300821_g_curCountryID) ~= 3 then
		-- BeginQuestEvent(sceneId)
		-- local strText = "�ܱ�Ǹ����Ŀǰֻ��ǰ��������"
		-- AddQuestText( sceneId, strText )
		-- EndQuestEvent( sceneId )
		-- DispatchQuestTips( sceneId, selfId )
		-- return			
	-- end

	--1.����״̬
	if IsPlayerMutexState(sceneId, selfId,PLAYER_STATE_PROTECTTIME) == 1 then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ�������ڴ��ڱ���״̬�����״̬��ʧ����ܷ���������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end
	
	--2.�ܱ�������
	
	--3.����״̬
	if IsPlayerMutexState(sceneId, selfId,PLAYER_STATE_CRASHBOX) == 1 then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ���������ڻ���״̬�����ܷ���������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end	
	
	--4.����
	if IsPlayerMutexState(sceneId, selfId,PLAYER_STATE_TIESAN) == 1 		--��������
		or IsHaveSpecificImpact(sceneId, selfId,7702) == 1				--����������BUFF
		or IsPlayerMutexState(sceneId, selfId,PLAYER_STATE_TONGQUBUFF) == 1	--ͯȤ������BUFF
		then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ���������ڱ���״̬�����ܷ���������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return			
	end
	
	--5.�й��ҹ�ְ
	if CountryGetOfficial(sceneId, selfId) ~= 0 then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ���������ȴ�ȥ�������ְ�񣬲ſ��Է���������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return			
	end
	
	--6.�а��
	if GetGuildID(sceneId, selfId) ~= -1 then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ���������������ᣬ�ſ��Է���������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return			
	end
	
	--7.������
	if GetQuestCount(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ���������Ƚ������ϵ�������ɻ�������ſ��Է���������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return			
	end
	
	--8.�з��޹�ϵ
	if IsMarried(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ���������Ƚ�����޹�ϵ���ſ��Է���������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end
	
	--9.��ʦͽ��ϵ
	if IsHaveMaster(sceneId, selfId) == 1 
		or IsHavePrentice(sceneId, selfId) == 1  then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ���������Ƚ��ʦͽ��ϵ���ſ��Է���������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return		
	end
	
	--10.�ж���
	if HasTeam(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ�����������˳����飬�ſ��Է���������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return	
	end
	
	--11.�ϴ��ѹ�7���ڣ������ٴ��ѹ�
	local lastDay = GetQuestData(sceneId,selfId,MD_COUNTRY_BETRAY_LASTDAY[1], MD_COUNTRY_BETRAY_LASTDAY[2],MD_COUNTRY_BETRAY_LASTDAY[3])
	local curDay = GetDayTime()
	local diffDay = x300821_GetDiffDay(lastDay,curDay)
	if diffDay < 7 then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ����������7���ڲ����ٴη�������"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return
	end
	
	--���м���ͨ��
	return 1
	
end


--**********************************
--����
--**********************************
function x300821_ProcAccept( sceneId, selfId )

	-- ��ʼ���Ĺ�������
	-- 1.�۳���Ǯ
	local nCost = x300821_GetBetrayCost()
	if x300821_CostMoney(sceneId, selfId, nCost ) == 0 then
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ�������ϵ��ֽ�����֧�����������ķ��ã�"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		return	
	end
	
	-- 2.��GLServer����Ϣ��GL�յ��󣬸����û��Ĺ���ID��ˢ�¹����ڲ����ݣ�ˢ���û�������а�
	SendCountryBetrayMsg( sceneId, selfId, x300821_g_curCountryID, x300821_g_ScriptId )

end

--**********************************
--GLServer���ؽ��ʱ�����õĻص�����
--**********************************
function x300821_OnCountryBetrayResult( sceneId, selfId, result )

	-- ʧ�ܣ�
	if result == 0 then
		
		BeginQuestEvent(sceneId)
		local strText = "�ܱ�Ǹ���������ڲ����󣬸ı����ʧ�ܣ�"
		AddQuestText( sceneId, strText )
		EndQuestEvent( sceneId )
		DispatchQuestTips( sceneId, selfId )
		
		-- ���Ѿ��۳��Ľ�Ǯ�����û�
		local nCost = x300821_GetBetrayCost()
		AddMoney( sceneId, selfId, 3, nCost )
		
		return
	end
	
	-- �ɹ���
	--1.֪ͨ�ͻ���
	BeginQuestEvent(sceneId)
	local strText = "��ϲ�����ѳɹ��ı����Ϊ"..GetCountryName(x300821_g_curCountryID)
	AddQuestText( sceneId, strText )
	EndQuestEvent( sceneId )
	DispatchQuestTips( sceneId, selfId )	
	
	--2.�����ѹ�ʱ��
	local curDay = GetDayTime()
	SetQuestData(sceneId,selfId,MD_COUNTRY_BETRAY_LASTDAY[1], MD_COUNTRY_BETRAY_LASTDAY[2],MD_COUNTRY_BETRAY_LASTDAY[3], curDay )
	
	--3.���˵��¹��ҵ����ǣ�ͬʱ����NextScene�ĳ������Է����͹����е��ߡ�
	local newSceneId 	= x300821_g_CountryTransPos[x300821_g_curCountryID].sceneid
	local newPosX		= x300821_g_CountryTransPos[x300821_g_curCountryID].posX
	local newPosZ		= x300821_g_CountryTransPos[x300821_g_curCountryID].posZ
	SetPlayerNextSceneInfo(sceneId, selfId, newSceneId, newPosX, newPosZ)
	NewWorld(sceneId, selfId, newSceneId, newPosX, newPosZ, x300821_g_ScriptId)
	
end

--**********************************
--����
--**********************************
function x300821_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--����
--**********************************
function x300821_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--����Ƿ�����ύ
--**********************************
function x300821_CheckSubmit( sceneId, selfId )
end
--**********************************
--�ύ
--**********************************
function x300821_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--ɱ����������
--**********************************
function x300821_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--���������¼�
--**********************************
function x300821_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--���߸ı�
--**********************************
function x300821_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end


-- ȡ���ѹ���Ҫ�Ľ�Ǯ������λ��
function x300821_GetBetrayCost( )

	local nRank = GetCountryRank(x300821_g_curCountryID)
	local nCost = 0
	
	if nRank == 0 then 
		nCost = 50000		--ǿ��
	elseif nRank == 1 or nRank == 2 then 
		nCost = 50000		--�еȹ�
	elseif nRank == 3 then 
		nCost = 50000		--����
	end	
	
	return nCost
	
end

--�۳���ҽ𿨻��ֽ�
function x300821_CostMoney( sceneId, selfId, value )
	local nGoldMode = GetGoldMode( sceneId, selfId )
	
	--if nGoldMode == 1 then		--�����ֽ����
		if CostMoney(sceneId, selfId, 2, value,303) == -1 then
			return 0
		end
	
	-- elseif nGoldMode == 0 then	--���Ƚ𿨽���
		-- if CostMoney(sceneId, selfId, 3, value,303) == -1 then
			-- if CostMoney(sceneId, selfId, 2, value,303) == -1 then
				-- return 0
			-- end
		-- end
	
	-- else						--δ֪�Ľ���ģʽ
		-- return 0
	-- end

	return 1
end

--����ʱ���
function x300821_GetDiffDay( lastDay, curDay )
	local diffDay = 0;
	local lastYear = floor(lastDay/1000);
	local curYear = floor(curDay/1000);
	local lastDayofYear = mod(lastDay,1000);
	local curDayOfYear = mod(curDay,1000);
	local DayCount = 365;

	if mod(lastYear,4)==0 then
		DayCount = 366;
	end
	
	if curDay<lastDay then
		diffDay = 0
	elseif curYear == lastYear then
		diffDay = curDay - lastDay
	elseif curYear < lastYear then
		diffDay = 0
	elseif curYear > lastYear then
		diffDay = (curYear-lastYear)*DayCount + curDayOfYear - lastDayofYear;
	end
	
	return diffDay
end