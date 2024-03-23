--���ܣ�ս����Ĭ�Ͻű�
--����ڳ�����

x300760_g_ScriptId = 300760
x300760_g_MissionName = "����������"

--�޵�impact�ڱ��е�����,��ҽ���BUS����һ���޵�impact,
x300760_g_GodIndex = 1210
x300760_g_Carinfo = {
						{ CarType = 3,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 5,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 6,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 35,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 36,BaseAI = 3,AIScript = 3,Script = 300760 },
						{ CarType = 37,BaseAI = 3,AIScript = 3,Script = 300760 },
					}

x300760_g_MissionId = {
						{ ID = 7556,iCostMoney =5000 ,AcceptId = 281 },
						{ ID = 7557,iCostMoney = 10000, AcceptId = 291 },
						{ ID = 7558, iCostMoney = 15000, AcceptId = 301 },
						{ ID = 7546, iCostMoney = 30000, AcceptId = 761 },
						{ ID = 7547, iCostMoney = 40000, AcceptId = 771 },
						{ ID = 7548, iCostMoney = 50000, AcceptId = 781 },
					  }

x300760_g_MainScriptId = 300757

--**********************************

--������ں���

--**********************************

function x300760_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

end

--**********************************

--�о��¼�

--**********************************
function x300760_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	--AddQuestNumText(sceneId, x300760_g_ScriptId, x300760_g_MissionName);
end


function x300760_OnCreateBus( sceneId,selfId,MissionId,BusID )

  local PosX,PosZ = GetWorldPos(sceneId, selfId)

	local ObjID = CreateBus(sceneId, x300760_g_Carinfo[BusID].CarType, PosX, PosZ, x300760_g_Carinfo[BusID].BaseAI, x300760_g_Carinfo[BusID].AIScript, x300760_g_Carinfo[BusID].Script, selfId, x300760_g_GodIndex,MissionId,-1)
end

--**********************************

--bus�����ɹ�����

--**********************************
function x300760_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)	

	SetBusTimerTick(sceneId , busId, 1000)
	SetBusWaitTime(sceneId , busId, 300)
	SetBusTimerOpen(sceneId, busId, 0)
	SetBusQuestID(sceneId,busId,MissionId)

	local CarName = GetName( sceneId, selfId ).."�ķ�����"
	SetBusTitle(sceneId , busId, CarName)
	local camp = GetCurCamp(sceneId, selfId)
	SetBusCurCamp(sceneId, busId,camp)

end


function x300760_DeleteBus(sceneId, ObjId)

	DeleteBus(sceneId, ObjId,1)

end


--����������BUS
--selfId�����ID
--targetId��BUSID
function x300760_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"���Ѿ��з������ˣ�");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "���Ѿ��з������ˣ�"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local BusSize = GetBusSize(sceneId,targetId)
	local MemberNum = GetBusMemberCount(sceneId,targetId)

	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"�����������Ѿ���������");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�����������Ѿ���������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--����BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

function x300760_OnIntoBusAfter(sceneId, selfId,BusID)

    if IsObjValid (sceneId,BusID) ~= 1 then
        return
    end

	local MissionId = GetBusQuestID(sceneId,BusID)

	for i,itm in x300760_g_MissionId do

		if MissionId == itm.ID then
			local bRet = CallScriptFunction( x300760_g_MainScriptId, "CostMoney", sceneId, selfId, MissionId)
			if bRet == 1 then

				if AddQuest(sceneId, selfId, MissionId,x300760_g_MainScriptId,0,0,0,1) == 1 then
					--������д��־
					GamePlayScriptLog(sceneId,selfId,itm.AcceptId)

					--local misIndex = CallScriptFunction( x300760_g_MainScriptId, "GetQuestIndexByID", sceneId, selfId, MissionId)
					local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
					SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);
					CallScriptFunction( x300760_g_MainScriptId, "QuestLogRefresh", sceneId, selfId, MissionId)	
					local CarName = GetName( sceneId, selfId ).."�ķ�����"
					SetBusTitle(sceneId , BusID, CarName)

					local camp = GetCurCamp(sceneId, selfId)
					SetBusCurCamp(sceneId, BusID,camp)
				end
			end

			break

		end
	end

end

--����뿪BUS
--selfId�����ID
function x300760_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"�����ڻ����У��޷��뿪");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�����ڻ����У��޷��뿪"
		Msg2Player(sceneId,selfId,Readme,8,2)
end


function x300760_OnDie(sceneId,BusId,idKiller)

    if IsObjValid (sceneId,BusId) ~= 1 then
        return
    end

	if idKiller == -1 then
		--��������Ŀǰֻ���ڽ����Ͷ�����ǰɾ���ڳ�
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300760_Abandon( sceneId, OwnerID  )
			local Readme = "#R���ķ��������ݻ٣�Ѻ������ʧ�ܣ�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "���������ݻ٣�");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	if IsObjValid(sceneId,idKiller)  == 0 then
		--��ЧOBJ
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300760_Abandon( sceneId, OwnerID  )
			local Readme = "���ķ��������ݻ�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "���������ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	local ObjType = GetObjType(sceneId,idKiller)

	if ObjType == 3 then		-- ��PETɱ��
		ObjType = 1
		idKiller = GetOwnerID(sceneId, idKiller)
		if IsPlayerStateNormal(sceneId,idKiller)  == 0 then
			local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerID ~= -1 then
			--״̬������
				x300760_Abandon( sceneId, OwnerID  )
				local Readme = "���������ݻ�"
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "�����ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
			end
			return
		end
	end

	if ObjType == 1 then		--�����ɱ��
	
		local BusMisId = GetBusQuestID( sceneId,BusId )

		local iCostMoney = 10000
		for i,itm in x300760_g_MissionId do
			
			if BusMisId == itm.ID then		-- ������������
				iCostMoney = itm.iCostMoney
				break
			end
		end
		local iCostMoney2 =iCostMoney/2
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
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ݻ��˱����ķ�����������PKֵ������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,"���ݻ��˱����ķ�����������PKֵ������",8,2)				
			else
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ݻ��˱����ķ�����");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,"���ݻ��˱����ķ�����������PKֵ������", 8,2)			
			end			

		else
	        AddMoney(sceneId,idKiller,0,iCostMoney2)
		  	BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ݻ��˵й��ķ�������������˽�����");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
			Msg2Player(sceneId,idKiller,format("���ݻ��˵й��ķ������������������#{_MONEY%d}��", iCostMoney2),8,2)

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
			
			x300760_Abandon( sceneId, OwnerID  )

			local GuildTitle = ""
			if GetGuildID(sceneId,idKiller) ~= -1 then
				GuildTitle = GetGuildTitle(sceneId,idKiller)
			end
			local killerName = GetName(sceneId,idKiller)
			local Readme = "���ķ�������"..Country..GuildTitle.."�����"..killerName.."�ݻ٣��ڽ�Ѻ������ʧ�ܣ�"
			if IsHideName(sceneId,idKiller) > 0 then
				Readme = "���ķ�������"..HIDE_NAME.."�ݻ٣��ڽ�Ѻ������ʧ�ܣ�"
			end
		
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "���������ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
	else		--����ɱ��
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300760_Abandon( sceneId, OwnerID  )
			local Readme = "���ķ�����������ݻ٣�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "���������ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
	end

end


function x300760_OnTime(sceneId,BusId)

end

function x300760_OnLifeTimeOut(sceneId,BusId)
    local selfId = GetBusMemberObjId(sceneId,BusId,0)
    if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300760_Abandon( sceneId, selfId  )
	end
	DeleteBus(sceneId, BusId,1)
end

function x300760_OnWaitTimeOut(sceneId,BusId)

	local selfId = GetBusMemberObjId(sceneId,BusId,0)
	if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300760_Abandon( sceneId, selfId  )
		local strText = "�������뿪����Ŀ��ʱ����û���Ŀ���ѱ���ɱ�����Ļ���Ŀ����ʧ�ˣ�����ʧ�ܣ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,strText,8,2)
	end
	DeleteBus(sceneId, BusId,1)
end

function x300760_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
	local strText = "�ܱ�Ǹ���������뿪#G�˽������#W#o��Զ����������ʧ����ֹͣǰ����"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, ownerId)
	Msg2Player(sceneId,ownerId,strText,8,2)
end




--********************************************************************
--����
--********************************************************************
function x300760_Abandon( sceneId, selfId )

	for i,itm in x300760_g_MissionId do
		
		if IsHaveQuestNM( sceneId, selfId, itm.ID) ~= 0 then	-- ������������
			
			DelQuestNM( sceneId, selfId, itm.ID)
			x300760_SetDayCount(sceneId, selfId)
			return
		end
	end

end

--********************************************************************
--����
--********************************************************************
function x300760_CleaupMission( sceneId, selfId )

	for i,itm in x300760_g_MissionId do
		
		if IsHaveQuestNM( sceneId, selfId, itm.ID) ~= 0 then	-- ������������
			
			DelQuestNM( sceneId, selfId, itm.ID)
			local Readme = "�������뿪����Ŀ��ʱ����û���Ŀ���ѱ���ɱ�����Ļ���Ŀ����ʧ�ˣ�����ʧ�ܣ�"
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, Readme);
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			Msg2Player(sceneId,selfId,Readme,8,2)
			x300760_SetDayCount(sceneId, selfId)
			return
		end
	end

end

---------------------------------------------------------------------------------------------------
--���µ�����������
---------------------------------------------------------------------------------------------------
function x300760_SetDayCount(sceneId, selfId)
	local today = GetDayOfYear()

	local lastday = GetQuestData(sceneId, selfId, MD_PAO_QIAN_DATE[1], MD_PAO_QIAN_DATE[2], MD_PAO_QIAN_DATE[3])

	if lastday ~= today then
		SetQuestData(sceneId, selfId, MD_PAO_QIAN_DATE[1], MD_PAO_QIAN_DATE[2], MD_PAO_QIAN_DATE[3], today)
		SetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3], 1)
	else
		local daycount = GetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3])
		SetQuestData(sceneId, selfId, MD_PAO_QIAN_COUNT[1], MD_PAO_QIAN_COUNT[2], MD_PAO_QIAN_COUNT[3], daycount+1)
	end
end