--MisDescBegin

x300761_g_ScriptId 	  = 300761
x300761_g_MissionKind 				= 	1                       --��������
x300761_g_Mis_Count   = 3--ÿ������Ĵ���
x300761_g_MissionId = 7031

-- ������ʾ
x300761_g_ExtTarget					=	{ {type=20,n=1,target="ս��"} }

x300761_g_ContinueInfo				= 	"\t����������Щ�����ˣ������й��Ĺ�Ʒ�Ͳ��ᰴʱ��ɡ�"
x300761_g_MissionCompleted			= 	"\t���Ѿ���ս����ȫ���͵��ˣ���������Ӧ�õĽ�����"

x300761_g_MissionName = "�����ˡ�ս������"
x300761_g_LevelLess = 70

x300761_g_BusScriptId = 300763

x300761_g_MissionTarget = "  ��ս������@npc_123829"
x300761_g_MissionInfo = "\t��֪��#G����ս#W��������Ϊ���ĵ�����#G��ս#W���Ҽ���һ����ʿ��ս�����͵�#G¥�����#W������#G��³ͼ#W�����㽫ս���ɹ����͸���֮�󣬻���#G�߶�#W��#G����#W������\n\tÿ��ÿ��ֻ�ɻ���#G����#Wս�������Ż���#G����#W��#G����#W����õ�#G����#WҲ��Խ��Խ�࣬��Ȼ��#G����#W������Ҳ��#G����#W�����λ��ͣ����軨��#R%d��#W������"
x300761_g_MissionHelp = "\t#G����;��������뿪ս����Զ��ս����������������ֹͣǰ����\n\t#G���ս���ܵ�Ϯ�����ݻ٣�����ʧ�ܣ�#G������뿪ս������5���ӣ�ս������ʧ������ʧ�ܣ�#G��ȡս���������ѵ��������᷵����#R�����ڼ�#Gֻ�����ӹ���ʵ������֣�#R������#G˫��������"
x300761_g_SubmitNPCGUID = 123829
x300761_g_NPCName = "@npc_123829"
x300761_g_Missionruse="��ս���͵�¥����ǵ�@npc_123829����"

--MisDescEnd
							

function x300761_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	local level = GetLevel(sceneId,selfId)
	
	if level < x300761_g_LevelLess then
		return
	end

	local bHaveMission = IsHaveQuestNM(sceneId, selfId, x300761_g_MissionId )
	local npcGuid = GetMonsterGUID(sceneId,targetId)
	if bHaveMission <= 0 then
		if x300761_g_SubmitNPCGUID ~= npcGuid then
			local state = GetQuestStateNM(sceneId,selfId,targetId,x300761_g_MissionId)
			AddQuestNumText(sceneId,x300761_g_MissionId,x300761_g_MissionName,state,0);
		end
	end

end

--�������ť������������ִ�д˽ű�
function x300761_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtIdx )

	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300761_g_MissionId)
	local npcGuid = GetMonsterGUID(sceneId,targetId)
	
	if x300761_g_SubmitNPCGUID ~= npcGuid then
	--������
		if(bHaveMission > 0) then
			local bDone = x300761_CheckSubmit(sceneId, selfId, targetId);
			if(bDone > 0) then
				if nExtIdx ~= -1 then
					x300761_DispatchCompletedInfo( sceneId, selfId, targetId,0) --���������ʾ
				end
			else
				if nExtIdx ~= -1 then
					x300761_DispatchContinueInfo( sceneId, selfId, targetId,0 ) --δ���������ʾ
				end
			end
		else
			if x300761_g_SubmitNPCGUID ~= npcGuid then
				x300761_DispatchMissionInfo( sceneId, selfId, targetId,0 )	--������Ϣ��ʾ
			else
				

				--���������Ϣ
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"��û�д�����")
				EndQuestEvent()
				DispatchQuestEventList(sceneId,selfId,targetId);
			end
		end
	else
	--������
		if(bHaveMission > 0) then
			x300761_DispatchCompletedInfo( sceneId, selfId, targetId,0) --���������ʾ
		-- else
		-- ���������Ϣ
			-- BeginQuestEvent(sceneId)
			-- AddQuestText(sceneId,"��û�д�����")
			-- EndQuestEvent()
			-- DispatchQuestEventList(sceneId,selfId,targetId);
		end
	end
	
end

--��ʾ������Ϣ
function x300761_DispatchMissionInfo( sceneId, selfId, NPCId,index )
	BeginQuestEvent( sceneId);
		--������Ϣ
		AddQuestText(sceneId, "#Y"..x300761_g_MissionName);
		AddQuestText(sceneId, format(x300761_g_MissionInfo,x300761_CalcCostMoney(sceneId, selfId)/1000) )
		--����Ŀ��
		AddQuestText( sceneId, "#Y����Ŀ�꣺")
		AddQuestText( sceneId, x300761_g_MissionTarget)
		AddQuestText( sceneId, " ")
		--��ʾ��Ϣ
		if x300761_g_MissionHelp ~= "" then
			AddQuestText(sceneId, "#Y������ʾ��")
			AddQuestText(sceneId, x300761_g_MissionHelp )
		end
		
		--������Ϣ
		--1������
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddQuestExpBonus( sceneId, experience)
		end

	EndQuestEvent(sceneId);

	DispatchQuestInfoNM(sceneId, selfId, NPCId, x300761_g_ScriptId,  x300761_g_MissionId);
end


---------------------------------------------------------------------------------------------------
--��ͻ��˷�������δ���
---------------------------------------------------------------------------------------------------
function x300761_DispatchContinueInfo( sceneId, selfId, NPCId,index )
	
	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x300761_g_MissionName)
		local info = format(x300761_g_MissionInfo,x300761_CalcCostMoney(sceneId, selfId)/1000)
		AddQuestText(sceneId,format("%s", info))
		AddQuestText(sceneId," ")

		--����Ŀ��
		AddQuestText( sceneId,"#Y��������")
		AddQuestText(sceneId, "δ���");

  		--��������Ϣ

		--1������
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddQuestExpBonus( sceneId, experience)
		end

	EndQuestEvent()
	DispatchQuestDemandInfo(sceneId, selfId, NPCId, x300761_g_ScriptId, x300761_g_MissionId,0);

end


---------------------------------------------------------------------------------------------------
--��ͻ��˷������������Ϣ
---------------------------------------------------------------------------------------------------
function x300761_DispatchCompletedInfo( sceneId, selfId, targetId,index )
	
	BeginQuestEvent(sceneId)

		--���������Ϣ
		AddQuestText(sceneId,"#Y"..x300761_g_MissionName)
		AddQuestText(sceneId,x300761_g_MissionCompleted)
		AddQuestText(sceneId," ")

		--1������
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddQuestExpBonus( sceneId, experience)
		end
			
	EndQuestEvent(sceneId)
	DispatchQuestContinueInfoNM(sceneId, selfId, targetId, x300761_g_ScriptId , x300761_g_MissionId);

end

--**********************************
--����
--**********************************
function x300761_ProcQuestAccept( sceneId, selfId, targetId, MissionId )
	if IsHideName(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��Ǹ������״̬���ܽӴ�����")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end
	
	if IsQuestFullNM( sceneId, selfId )==1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�ɽ�������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end

	local level = GetLevel(sceneId, selfId)
	if level < x300761_g_LevelLess then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���ĵȼ�������ȡ������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "���ĵȼ�������ȡ������" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
	if GetMoney(sceneId, selfId,0) < x300761_CalcCostMoney(sceneId, selfId) then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�����ϵ��������㣬������ȡս����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�����ϵ��������㣬������ȡս����"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0;		
	end

	if IsTeamFollow(sceneId, selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "��Ӹ���״̬�²����Խӻ�������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "��Ӹ���״̬�²����Խӻ�������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
	
	if IsBusMember(sceneId,selfId) == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "���Ѵ��ڻ���/Ѻ��״̬���޷���ȡ�µ�Ѻ������");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "���Ѵ��ڻ���/Ѻ��״̬���޷���ȡ�µ�Ѻ������" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end

	if x300761_GetDayCount(sceneId, selfId) >= x300761_g_Mis_Count then
		local Readme = "�ܱ�Ǹ����������������������������������ɣ�" 
	  	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,Readme );
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
		
	local bHaveMission	= IsHaveQuestNM(sceneId, selfId, x300761_g_MissionId);
	if(bHaveMission > 0) then
		return 0;
	end
	--��������־
	--GamePlayScriptLog(sceneId,selfId,1421)
	local count = x300761_GetDayCount(sceneId, selfId)
	CallScriptFunction( x300761_g_BusScriptId, "OnCreateBus", sceneId, selfId ,x300761_g_MissionId,count+1)

end

---------------------------------------------------------------------------------------------------
--��������Ƿ���ύ
---------------------------------------------------------------------------------------------------
function x300761_CheckSubmit(sceneId, selfId, targetId)
	
	local npcGuid = GetMonsterGUID(sceneId,targetId)

	if x300761_g_SubmitNPCGUID ~= npcGuid then
		return 0
	end

	return 1;

end

--**********************************
--����
--**********************************
function x300761_ProcAccept( sceneId, selfId )
	
end

--�������
--����1����ɹ���0��������ʧ��
function x300761_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )

	if IsQuestHaveDoneNM( sceneId, selfId, MissionId ) > 0 then --�����Ѿ����
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId) <= 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	--�ڳ��Ƿ�����Ч����
	local valid = IsValidMyselfBus(sceneId, selfId,MissionId)

	if valid == 0 then
        BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "�����͵�ս������̫Զ�ˣ��޷��ύ����");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�����͵�ս������̫Զ�ˣ��޷��ύ����"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return 0
	end
   
	--������
	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId)
	local ret = DelQuest( sceneId, selfId, MissionId) 
	if ret == 1 then -- ����ɹ����

		--������д��־
		GamePlayScriptLog(sceneId,selfId,1422)
		AddCountryStrength(sceneId, selfId, 1)	
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, "��ϲ����Ϊ����ʵ��������#R1��#O���֡�");
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId,selfId);
		Msg2Player(sceneId,selfId,"��ϲ����Ϊ����ʵ��������#R1��#O���֡�",8,2)	
		
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddExp(sceneId, selfId,experience)
			local exp1 = x300761_CalcExperience(sceneId, selfId)
			local Readme = "����������񣺡����ˡ�ս������#r���#R����"..exp1.."��#o�Ľ���"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "����������񣺡����ˡ�ս������");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "���#R����"..exp1.."��#o�Ľ���");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
			CallScriptFunction( 256223, "FinishYayun", sceneId, selfId)
		end
		        
		x300761_SetDayCount(sceneId, selfId)
		
		local BusID  =  GetBusId(sceneId, selfId)
		if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
			--���BUS������
			if GetBusQuestID(sceneId, BusID) == MissionId then
				DeleteBus(sceneId, BusID,1)
			end
		end 
		x300761_GuoYun(sceneId, selfId, MissionId)
	end

	return 0
end


--********************************************************************
--����
--********************************************************************
function x300761_ProcQuestAbandon( sceneId, selfId,MissionId )

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,x300761_g_MissionId );
	if bHaveMission > 0 then

		if IsBusMember(sceneId, selfId) == 1 then
			local BusID  =  GetBusId(sceneId, selfId)
			if BusID ~= -1 and IsObjValid (sceneId,BusID) == 1 then
				--���BUS������
				if GetBusQuestID(sceneId, BusID) == x300761_g_MissionId then
					DeleteBus(sceneId, BusID,1)
				end
			else
				local Readme = "�ܱ�Ǹ���������Ļ���Ŀ����ͬһ�������ܷ������������ҵ����Ļ���Ŀ����ѡ�������"
				BeginQuestEvent(sceneId)
				AddQuestText(sceneId, "���ڲ��ܷ�������");
				EndQuestEvent(sceneId)
				DispatchQuestTips(sceneId,selfId)
				Msg2Player(sceneId,selfId,Readme,8,2)
				return
			end				
		end

		local misIndex = GetQuestIndexByID(sceneId, selfId, x300761_g_MissionId); 
		DelQuest(sceneId, selfId, x300761_g_MissionId);
						
		--��������д��־
		GamePlayScriptLog(sceneId,selfId,1424)

		local Readme = "�����������񣺡����ˡ�ս������"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)

		x300761_SetDayCount(sceneId, selfId)
	end

end


function x300761_ProcQuestAttach( sceneId, selfId, npcId, npcGuid,misIndex, MissionId )
	
	local bHaveMission = IsHaveQuestNM(sceneId, selfId,x300761_g_MissionId )

	if bHaveMission > 0 then
		if npcGuid == x300761_g_SubmitNPCGUID then
			local state = GetQuestStateNM(sceneId,selfId,npcId,x300761_g_MissionId)
			AddQuestNumText(sceneId, x300761_g_MissionId, x300761_g_MissionName,7,0);
		end
	end

end

---------------------------------------------------------------------------------------------------
--������־ˢ��
---------------------------------------------------------------------------------------------------
function x300761_QuestLogRefresh( sceneId, selfId, MissionId)

	local bHaveMission = IsHaveQuestNM(sceneId, selfId,x300761_g_MissionId );
	if bHaveMission > 0 then
	
		BeginQuestEvent(sceneId)
		
		local experience = x300761_CalcExperience(sceneId, selfId)
		if experience > 0 then
			AddQuestExpBonus( sceneId, experience)
		end

		AddQuestLogCustomText( sceneId,
								"",						-- ����
								x300761_g_MissionName,        -- ��������
								x300761_g_MissionTarget,		--����Ŀ��
								x300761_g_NPCName,			--����NPC
								x300761_g_Missionruse,               --������
								format(x300761_g_MissionInfo,x300761_CalcCostMoney(sceneId, selfId)/1000),	--��������
								""					--����С��ʾ
								)
		EndQuestEvent(sceneId)
		DispatchQuestLogUpdate(sceneId, selfId, x300761_g_MissionId);
	end

end

function x300761_ProcQuestLogRefresh( sceneId, selfId, MissionId)
	x300761_QuestLogRefresh( sceneId, selfId, MissionId );
end

---------------------------------------------------------------------------------------------------
--ȡ�ô������쵱ǰ����ɴ���
---------------------------------------------------------------------------------------------------
function x300761_GetDayCount(sceneId, selfId)

	if x300761_g_Mis_Count > 0 then

		local today = GetDayOfYear()

		local lastday = GetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_DATE[1], MD_ZHANCHEYAYUN_DATE[2], MD_ZHANCHEYAYUN_DATE[3])

		if lastday ~= today then
			return 0
		end

		local daycount =  GetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_COUNT[1], MD_ZHANCHEYAYUN_COUNT[2], MD_ZHANCHEYAYUN_COUNT[3])
		return daycount

	end

	return 0
end

---------------------------------------------------------------------------------------------------
--���µ�����������
---------------------------------------------------------------------------------------------------
function x300761_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_DATE[1], MD_ZHANCHEYAYUN_DATE[2], MD_ZHANCHEYAYUN_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_DATE[1], MD_ZHANCHEYAYUN_DATE[2], MD_ZHANCHEYAYUN_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_COUNT[1], MD_ZHANCHEYAYUN_COUNT[2], MD_ZHANCHEYAYUN_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_COUNT[1], MD_ZHANCHEYAYUN_COUNT[2], MD_ZHANCHEYAYUN_COUNT[3])
		SetQuestData(sceneId, selfId, MD_ZHANCHEYAYUN_COUNT[1], MD_ZHANCHEYAYUN_COUNT[2], MD_ZHANCHEYAYUN_COUNT[3], daycount+1)
	end
end

--���㻨����Ǯ
function x300761_CalcCostMoney(sceneId, selfId)
	local count = x300761_GetDayCount(sceneId, selfId)
	if count == 0 then
		return 75000
	elseif count == 1 then
		return 150000
	elseif count == 2 then
		return 225000
	end
	return 0
end

--����ö��پ���
function x300761_CalcExperience(sceneId, selfId)
	local count = x300761_GetDayCount(sceneId, selfId)
	local level = GetLevel(sceneId,selfId)
	if count == 0 then
		if level < 80 then
			zhancheexp = level*30000
		elseif level >=80 and level < 90 then
			zhancheexp = level*30000*2
		elseif level >=90 and level <200 then
			zhancheexp = level*30000*2.6
		end
		return zhancheexp
	elseif count == 1 then
		if level < 80 then
			zhancheexp = level*60000
		elseif level >=80 and level < 90 then
			zhancheexp = level*60000*2
		elseif level >=90 and level <200 then
			zhancheexp = level*60000*2.6
		end
		return zhancheexp
	elseif count == 2 then
		if level < 80 then
			zhancheexp = level*100000
		elseif level >=80 and level < 90 then
			zhancheexp = level*100000*2
		elseif level >=90 and level <200 then
			zhancheexp = level*100000*2.6
		end
		return zhancheexp
	end
	return 0
end

function x300761_GuoYun(sceneId, selfId, MissionId)
	if CountryIsFortuneTime(sceneId, selfId, 0) > 0 then
		local country = GetCurCountry(sceneId, selfId)
		SetCountryQuestData(sceneId, country, CD_INDEX_GUOYUN_COUNT, 1, 1 )
	end
end
