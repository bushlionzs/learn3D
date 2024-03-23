--���ܣ�ս����Ĭ�Ͻű�
--����ڳ�����

x300854_g_ScriptId = 300854
x300854_g_MissionName = "�����ڳ�"

--�޵�impact�ڱ��е�����,��ҽ���BUS����һ���޵�impact,
x300854_g_GodIndex = 1210

x300854_g_Carinfo = {
						{ CarType = 7,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 8,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 9,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 38,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 39,BaseAI = 3,AIScript = 3,Script = 300854 },
						{ CarType = 40,BaseAI = 3,AIScript = 3,Script = 300854 },



					}

x300854_g_MissionId = {
						{ ID = 7620,iCostMoney = 1000, GameId = 51 },
						{ ID = 7621,iCostMoney = 2000, GameId = 61 },
						{ ID = 7622,iCostMoney = 3000,GameId = 71 },
						{ ID = 7623,iCostMoney = 5000,GameId = 81 },
						{ ID = 7624,iCostMoney = 6000,GameId = 741 },
						{ ID = 7625,iCostMoney = 7500,GameId = 751 },
					  }

--**********************************

--������ں���

--**********************************

function x300854_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

end

--**********************************

--�о��¼�

--**********************************
function x300854_ProcEnumEvent(sceneId, selfId, targetId)
	--AddQuestNumText(sceneId, x300854_g_ScriptId, x300854_g_MissionName);
end


function x300854_OnCreateBus( sceneId, selfId,MissionId ,BusID)

    local PosX = 67
    local PosZ = 170
	local ObjID = CreateBus(sceneId, x300854_g_Carinfo[BusID].CarType, PosX, PosZ, x300854_g_Carinfo[BusID].BaseAI, x300854_g_Carinfo[BusID].AIScript, x300854_g_Carinfo[BusID].Script, selfId, x300854_g_GodIndex,MissionId,-1)
end

--����busd�ɹ�����
function x300854_OnCreateBusOK(sceneId, selfId, busId,targetId,MissionId)			
		SetBusTimerTick(sceneId , busId, 1000)
		SetBusWaitTime(sceneId , busId, 300)
		SetBusTimerOpen(sceneId, busId, 0)
		SetBusQuestID(sceneId,busId,MissionId)

		local CarName = GetName( sceneId, selfId ).."����"
		SetBusTitle(sceneId , busId, CarName)
		local camp = GetCurCamp(sceneId, selfId)
		SetBusCurCamp(sceneId, busId,camp)
end


function x300854_DeleteBus(sceneId, ObjId)

	DeleteBus(sceneId, ObjId,1)

end


--����������BUS
--selfId�����ID
--targetId��BUSID
function x300854_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"���Ѿ�������");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "���Ѿ�������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local BusSize = GetBusSize(sceneId,targetId)
	local MemberNum = GetBusMemberCount(sceneId,targetId)

	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"�������Ѿ���������");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�������Ѿ���������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--����BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

function x300854_OnIntoBusAfter(sceneId, selfId,BusID)

    if IsObjValid (sceneId,BusID) ~= 1 then
        return
    end

	local MissionId = GetBusQuestID(sceneId,BusID)

	local GameId = 71
	local iCostMoney = 1000
	for i,itm in x300854_g_MissionId do
		if itm.ID == MissionId then
			iCostMoney = itm.iCostMoney
			GameId 	= itm.GameId 
			break
		end
	end
	
	-- local num = CostMoney( sceneId , selfId ,1, iCostMoney,301)--�ɹ�����1 ʧ�ܷ���-1
	-- local num1 = CostMoney( sceneId , selfId ,0, iCostMoney,301)--�ɹ�����1 ʧ�ܷ���-1
	if SpendMoney( sceneId , selfId ,iCostMoney,301) ~= 1 then
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�ܱ�Ǹ���������е�����������������֧��Ѻ���޷���ȡ����" 
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
		-- else
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId,"�����������񣺡����ˡ��ٸ�Ѻ��")
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		-- local Readme = format("���ܹٸ�Ѻ�˳ɹ����۳�Ѻ��#R����#{_MONEY%d}��", iCostMoney)
		--local Readme1 = "���ܹٸ�Ѻ�˳ɹ�"
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, Readme1")
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		--Msg2Player(sceneId,selfId,Readme,8,2)
	else
		--local Readme1 = "���ܹٸ�Ѻ�˳ɹ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����������񣺡����ˡ��ٸ�Ѻ��")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = format("���ܹٸ�Ѻ�˳ɹ����۳�Ѻ��#R������������#{_MONEY%d}��", iCostMoney)
		--local Readme1 = "���ܹٸ�Ѻ�˳ɹ�"
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, Readme1")
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
	end
	
	--���ǰ������
	local FrontMissiontId1, FrontMissiontId2, FrontMissiontId3 = GetFrontQuestIdNM( sceneId, selfId, MissionId )
	if FrontMissiontId1 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId1 ) == 0 then
			return
		end
	end
	if FrontMissiontId2 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId2 ) == 0 then
			return
		end
	end
	if FrontMissiontId3 ~= -1 then
		if IsQuestHaveDoneNM( sceneId, selfId, FrontMissiontId3 ) == 0 then
			return
		end
	end

	if AddQuestNM( sceneId, selfId,MissionId) == 1 then
		
		--������д��־
		GamePlayScriptLog(sceneId,selfId,GameId)

		local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);	
	end

	local CarName = GetName( sceneId, selfId ).."����"
	SetBusTitle(sceneId , BusID, CarName)
	local camp = GetCurCamp(sceneId, selfId)
	SetBusCurCamp(sceneId, BusID,camp)

end


--����뿪BUS
--selfId�����ID
function x300854_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"���������ڣ��޷��뿪");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "���������ڣ��޷��뿪"
		Msg2Player(sceneId,selfId,Readme,8,2)
end


function x300854_OnDie(sceneId,BusId,idKiller)

    if IsObjValid (sceneId,BusId) ~= 1 then
        return
    end

	if idKiller == -1 then
		--��������Ŀǰֻ���ڽ����Ͷ�����ǰɾ���ڳ�
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300854_Abandon( sceneId, OwnerID  )
			local Readme = "���������ݻ�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "�����ݻ٣�");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	if IsObjValid(sceneId,idKiller)  == 0 then
		--��ЧOBJ
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300854_Abandon( sceneId, OwnerID  )
			local Readme = "���������ݻ�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "�����ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	local ObjType = GetObjType(sceneId,idKiller)	

	if ObjType == 3 then		-- ��PETɱ��
		ObjType = 1
		idKiller = GetOwnerID(sceneId, idKiller)
		if IsPlayerStateNormal(sceneId,idKiller)  == 0 then
			--����״̬������
			local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerID ~= -1 then
				x300854_Abandon( sceneId, OwnerID  )
				local Readme = "���������ݻ�"
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "�����ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
			end
			return
		end
	end

	if ObjType == 1 then     --�����ɱ��
		
		local BusMisId = GetBusQuestID( sceneId,BusId )

		local iCostMoney = 1000
		for i,itm in x300854_g_MissionId do
			if BusMisId == itm.ID then 
				iCostMoney = itm.iCostMoney
				break
			end
		end

		local OwnerCountry = GetBusCountryID(sceneId,BusId)
		local KillerCountry = GetCurCountry(sceneId,idKiller)
		if OwnerCountry == KillerCountry then	
					
			--PK�ͷ�
			local IsPunish = 0
			local OwnerId = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerId ~= -1 then
				IsPunish = CallScriptFunction( SCENE_SCRIPT_ID, "CashboxComputePKPunish", sceneId, OwnerId, idKiller )
				if IsKing( sceneId, idKiller ) ~= 1 and IsPunish == 1 then
					--�ǹ�������PK�ͷ�ֵ����0
					CallScriptFunction( SCENE_SCRIPT_ID, "KillerEnterPrison", sceneId, idKiller )
					IsPunish = 1
				else
					IsPunish = 0
				end			
			end
			
			if IsPunish==1 then
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "����ɱ�˱�������������PKֵ������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,format("����ɱ�˱�������������PKֵ������"),8,2)				
			else
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "����ɱ�˱�������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,format("����ɱ�˱�������"),8,2)			
			end

		else
	        --AddMoney(sceneId,idKiller,0,iCostMoney)

		  	BeginQuestEvent(sceneId);AddQuestText(sceneId, "����ɱ�˵й�������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
			Msg2Player(sceneId,idKiller,format("����ɱ�˵й�������"),8,2)	
		end

		local Country = "¥������"
		if KillerCountry == 0 then
			Country = "¥������"
		elseif KillerCountry == 1 then
			Country = "��ɽ����"
		elseif KillerCountry == 2 then
			Country = "��������"
		elseif KillerCountry == 3 then
			Country = "�ػ�����"
		else
			return
		end


		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then

			x300854_Abandon( sceneId, OwnerID  )

			local GuildTitle = ""
			if GetGuildID(sceneId,idKiller) ~= -1 then
				GuildTitle = GetGuildTitle(sceneId,idKiller)
			end
			local killerName = GetName(sceneId,idKiller)
			local Readme = "��������"..Country..GuildTitle.."�����"..killerName.."�ݻ٣��ٸ�Ѻ������ʧ�ܣ�"
			if IsHideName(sceneId,idKiller) > 0 then
				Readme = "��������"..HIDE_NAME.."�ݻ٣��ٸ�Ѻ������ʧ�ܣ�"
			end
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "�����ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)

		end
	else		--����ɱ��
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300854_Abandon( sceneId, OwnerID  )
			local Readme = "������������ݻ٣��ٸ�Ѻ������ʧ�ܣ�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "�����ݻ٣�");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
	end

end


function x300854_OnTime(sceneId,BusId)

end

function x300854_OnLifeTimeOut(sceneId,BusId)
    local selfId = GetBusMemberObjId(sceneId,BusId,0)
    if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300854_Abandon( sceneId, selfId  )
	end
	DeleteBus(sceneId, BusId,1)
end

function x300854_OnWaitTimeOut(sceneId,BusId)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)
	if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300854_Abandon( sceneId, selfId  )
		local strText = "�������뿪����Ŀ��ʱ����û���Ŀ���ѱ���ɱ�����Ļ���Ŀ����ʧ�ˣ�����ʧ�ܣ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�������뿪����Ŀ��ʱ����û���Ŀ���ѱ���ɱ�����Ļ���Ŀ����ʧ�ˣ�����ʧ�ܣ�"
		Msg2Player(sceneId,selfId,Readme,8,2)
	end
	DeleteBus(sceneId, BusId,1)
end

function x300854_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end




--********************************************************************
--����
--********************************************************************
function x300854_Abandon( sceneId, selfId )

	for i,itm in x300854_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, itm.ID) ~= 0 then	-- ������������
			DelQuestNM( sceneId, selfId, itm.ID)
			x300854_SetDayCount(sceneId, selfId)
			return
		end
	end

end

function x300854_CleaupMission( sceneId, selfId )

	for i,itm in x300854_g_MissionId do
		if IsHaveQuestNM( sceneId, selfId, itm.ID) ~= 0 then	-- ������������
			DelQuestNM( sceneId, selfId, itm.ID)
			local Readme = "�������뿪����Ŀ��ʱ����û���Ŀ���ѱ���ɱ�����Ļ���Ŀ����ʧ�ˣ�����ʧ�ܣ�"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, Readme);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
			x300854_SetDayCount(sceneId, selfId)
			return
		end
	end

end

function x300854_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
	local strText = "�ܱ�Ǹ���������뿪#G�ٸ���#W#o��Զ���ٸ�����ʧ����ֹͣǰ����"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, ownerId)
	Msg2Player(sceneId,ownerId,strText,8,2)
end
---------------------------------------------------------------------------------------------------
--���µ�����������
---------------------------------------------------------------------------------------------------
function x300854_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_DATE[1], MD_MYSELF_CONVOY_DATE[2], MD_MYSELF_CONVOY_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_DATE[1], MD_MYSELF_CONVOY_DATE[2], MD_MYSELF_CONVOY_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3])
		SetQuestData(sceneId, selfId, MD_MYSELF_CONVOY_COUNT[1], MD_MYSELF_CONVOY_COUNT[2], MD_MYSELF_CONVOY_COUNT[3], daycount+1)
	end
end
