--���ܣ�ս����Ĭ�Ͻű�
--����ڳ�����

x300917_g_ScriptId = 300917
x300917_g_MissionName = "�����ڳ�"
x300917_g_Mis_Count   = 3
--�޵�impact�ڱ��е�����,��ҽ���BUS����һ���޵�impact,
x300917_g_GodIndex = 1210

x300917_g_Carinfo = {
						{ CarType = 42,BaseAI = 3,AIScript = 3,Script = 300917 },
						{ CarType = 43,BaseAI = 3,AIScript = 3,Script = 300917 },
						{ CarType = 44,BaseAI = 3,AIScript = 3,Script = 300917 }
					}

x300917_g_MissionId = 7034
x300917_g_GameId = 71

--**********************************

--������ں���

--**********************************

function x300917_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

end

--**********************************

--�о��¼�

--**********************************
function x300917_ProcEnumEvent(sceneId, selfId, targetId)
	--AddQuestNumText(sceneId, x300917_g_ScriptId, x300917_g_MissionName);
end


function x300917_OnCreateBus( sceneId, selfId,MissionId ,BusID)
  --local PosX,PosZ = GetWorldPos(sceneId, selfId)
    local PosX = 70
	local PosZ = 179
	local ObjID = CreateBus(sceneId, x300917_g_Carinfo[BusID].CarType, PosX, PosZ, x300917_g_Carinfo[BusID].BaseAI, x300917_g_Carinfo[BusID].AIScript, x300917_g_Carinfo[BusID].Script, selfId, x300917_g_GodIndex,MissionId,-1)
	
end
--����busd�ɹ�����
function x300917_OnCreateBusOK(sceneId, selfId, busId,targetId,MissionId)
		
		SetBusTimerTick(sceneId , busId, 1000)
		SetBusWaitTime(sceneId , busId, 300)
		SetBusTimerOpen(sceneId, busId, 0)
		SetBusQuestID(sceneId,busId,MissionId)

		local CarName = GetName( sceneId, selfId ).."��ս��"
		SetBusTitle(sceneId , busId, CarName)
		local camp = GetCurCamp(sceneId, selfId)
		SetBusCurCamp(sceneId, busId,camp)

end


function x300917_DeleteBus(sceneId, ObjId)

	DeleteBus(sceneId, ObjId,1)

end


--����������BUS
--selfId�����ID
--targetId��BUSID
function x300917_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"���Ѿ���ս����");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "���Ѿ���ս����"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local BusSize = GetBusSize(sceneId,targetId)
	local MemberNum = GetBusMemberCount(sceneId,targetId)

	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"����ս���Ѿ���������");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "����ս���Ѿ���������"
		Msg2Player(sceneId,selfId,Readme,8,2)
		return
	end

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--����BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end

function x300917_OnIntoBusAfter(sceneId, selfId,BusID)

    if IsObjValid (sceneId,BusID) ~= 1 then
        return
    end

	local MissionId = GetBusQuestID(sceneId,BusID)
	
	local iCostMoney = x300917_CalcCostMoney(sceneId, selfId)
	-- local num = CostMoney( sceneId , selfId ,1, iCostMoney,301)--�ɹ�����1 ʧ�ܷ���-1
	-- local num1 = CostMoney( sceneId , selfId ,0, iCostMoney,301)--�ɹ�����1 ʧ�ܷ���-1
	if CostMoney( sceneId , selfId ,0,iCostMoney,301) ~= 1 then
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�ܱ�Ǹ���������е��������㣬�޷���ȡ����" 
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
		AddQuestText(sceneId,"�����������񣺡����ˡ�ս������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		local Readme = format("����ս�����ͳɹ����۳�#R����#{_MONEY%d}��", iCostMoney)
		--local Readme1 = "���ܹٸ�Ѻ�˳ɹ�"
		-- BeginQuestEvent(sceneId)
		-- AddQuestText(sceneId, Readme1")
		-- EndQuestEvent(sceneId)
		-- DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		--��������־
		GamePlayScriptLog(sceneId,selfId,1423)
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
		GamePlayScriptLog(sceneId,selfId,1421)

		local misIndex = GetQuestIndexByID(sceneId, selfId, MissionId);
		SetQuestByIndex(sceneId, selfId, misIndex, 7, 0);	
	end

	local CarName = GetName( sceneId, selfId ).."��ս��"
	SetBusTitle(sceneId , BusID, CarName)
	local camp = GetCurCamp(sceneId, selfId)
	SetBusCurCamp(sceneId, BusID,camp)

end


--����뿪BUS
--selfId�����ID
function x300917_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"�����ڻ���ս�����޷��뿪");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		local Readme = "�����ڻ���ս�����޷��뿪"
		Msg2Player(sceneId,selfId,Readme,8,2)
end


function x300917_OnDie(sceneId,BusId,idKiller)

    if IsObjValid (sceneId,BusId) ~= 1 then
        return
    end

	if idKiller == -1 then
		--��������Ŀǰֻ���ڽ����Ͷ�����ǰɾ���ڳ�
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300917_Abandon( sceneId, OwnerID  )
			local Readme = "����ս�����ݻ�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "ս�����ݻ٣�");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	if IsObjValid(sceneId,idKiller)  == 0 then
		--��ЧOBJ
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300917_Abandon( sceneId, OwnerID  )
			local Readme = "����ս�����ݻ�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "ս�����ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
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
				x300917_Abandon( sceneId, OwnerID  )
				local Readme = "����ս�����ݻ�"
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "ս�����ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
			end
			return
		end
	end

	if ObjType == 1 then     --�����ɱ��
		
		local BusMisId = GetBusQuestID( sceneId,BusId )

		local iCostMoney = x300917_CalcAddMoney(sceneId, BusId)
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
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "����ɱ�˱�����ս��������PKֵ������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,format("����ɱ�˱�����ս��������PKֵ������"),8,2)				
			else
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "����ɱ�˱�����ս��");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,format("����ɱ�˱�����ս��"),8,2)			
			end

		else
	        AddMoney(sceneId,idKiller,0,iCostMoney)

		  	BeginQuestEvent(sceneId);AddQuestText(sceneId, "����ɱ�˵й���ս����");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
			Msg2Player(sceneId,idKiller,format("����ɱ�˵й���ս����"),8,2)	
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

			x300917_Abandon( sceneId, OwnerID  )

			local GuildTitle = ""
			if GetGuildID(sceneId,idKiller) ~= -1 then
				GuildTitle = GetGuildTitle(sceneId,idKiller)
			end
			local killerName = GetName(sceneId,idKiller)
			local Readme = "����ս����"..Country..GuildTitle.."�����"..killerName.."�ݻ٣�ս����������ʧ�ܣ�"
			if IsHideName(sceneId,idKiller) > 0 then
				Readme = "����ս����"..HIDE_NAME.."�ݻ٣�ս����������ʧ�ܣ�"
			end
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "ս�����ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)

		end
	else		--����ɱ��
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			x300917_Abandon( sceneId, OwnerID  )
			local Readme = "����ս��������ݻ٣�ս����������ʧ�ܣ�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "ս�����ݻ٣�");EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
	end

end


function x300917_OnTime(sceneId,BusId)

end

function x300917_OnLifeTimeOut(sceneId,BusId)
    local selfId = GetBusMemberObjId(sceneId,BusId,0)
    if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300917_Abandon( sceneId, selfId  )
	end
	DeleteBus(sceneId, BusId,1)
end

function x300917_OnWaitTimeOut(sceneId,BusId)
	local selfId = GetBusMemberObjId(sceneId,BusId,0)
	if(IsPlayerStateNormal(sceneId, selfId) ~= 0) then
		x300917_Abandon( sceneId, selfId  )
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

function x300917_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end




--********************************************************************
--����
--********************************************************************
function x300917_Abandon( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, x300917_g_MissionId) ~= 0 then	-- ������������
		DelQuestNM( sceneId, selfId, x300917_g_MissionId)
		x300917_SetDayCount(sceneId, selfId)
		return
	end

end

function x300917_CleaupMission( sceneId, selfId )

	if IsHaveQuestNM( sceneId, selfId, x300917_g_MissionId) ~= 0 then	-- ������������
		DelQuestNM( sceneId, selfId, x300917_g_MissionId)
		local Readme = "�������뿪����Ŀ��ʱ����û���Ŀ���ѱ���ɱ�����Ļ���Ŀ����ʧ�ˣ�����ʧ�ܣ�"
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, Readme);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		Msg2Player(sceneId,selfId,Readme,8,2)
		x300917_SetDayCount(sceneId, selfId)
		return
	end

end

function x300917_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
	local strText = "�ܱ�Ǹ���������뿪#Gս��#W#o��Զ��ս����������ֹͣǰ����"
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, strText);
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId, ownerId)
	Msg2Player(sceneId,ownerId,strText,8,2)
end

---------------------------------------------------------------------------------------------------
--ȡ�ô������쵱ǰ����ɴ���
---------------------------------------------------------------------------------------------------
function x300917_GetDayCount(sceneId, selfId)

	if x300917_g_Mis_Count > 0 then

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
function x300917_SetDayCount(sceneId, selfId)
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
function x300917_CalcCostMoney(sceneId, selfId)
	local count = x300917_GetDayCount(sceneId, selfId)
	if count == 0 then
		return 75000
	elseif count == 1 then
		return 150000
	elseif count == 2 then
		return 225000
	end
	return 0
end

--���㽱������Ǯ
function x300917_CalcAddMoney(sceneId, BusId)
	local nBusIndex = GetBusIndex(sceneId,BusId)
	if nBusIndex == x300917_g_Carinfo[1].CarType then
			return 52500
	elseif nBusIndex == x300917_g_Carinfo[2].CarType then
			return 105000
	elseif nBusIndex == x300917_g_Carinfo[3].CarType then
			return 157500
	end
	return 0
end