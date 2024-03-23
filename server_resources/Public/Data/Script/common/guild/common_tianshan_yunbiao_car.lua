--���ܣ�ս����Ĭ�Ͻű�
--����ڳ�����

x300872_g_ScriptId = 300872
x300872_g_MissionName = "�����ڳ�"

--�޵�impact�ڱ��е�����,��ҽ���BUS����һ���޵�impact,
x300872_g_GodIndex = 1210
x300872_g_Carinfo = {CarType = 4,BaseAI = 3,AIScript = 3,Script = 300872 }

x300872_g_CostMoney = 10000
--**********************************

--������ں���

--**********************************

function x300872_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

end

--**********************************

--�о��¼�

--**********************************
function x300872_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	--AddQuestNumText(sceneId, x300872_g_ScriptId, x300872_g_MissionName);
end


function x300872_OnCreateBus( sceneId, selfId,MissionId )

  local PosX,PosZ = GetWorldPos(sceneId, selfId)
	local ObjID = CreateBus(sceneId, x300872_g_Carinfo.CarType, PosX, PosZ, x300872_g_Carinfo.BaseAI, x300872_g_Carinfo.AIScript, x300872_g_Carinfo.Script, selfId, x300872_g_GodIndex,MissionId,-1)
end

--����busd�ɹ�����
function x300872_OnCreateBusOK(sceneId, selfId, busId,targetId,MissionId)	

		SetBusTimerTick(sceneId , busId, 1000)
		SetBusWaitTime(sceneId , busId, 300)
		SetBusTimerOpen(sceneId, busId, 0)
		SetBusQuestID(sceneId,busId,MissionId)
		
		--�ڳ������˵İ󶨹�ϵδ�����ɹ�ǰ�İ�ȫ״̬
		SetBusCurCamp(sceneId, busId,20)
end


function x300872_DeleteBus(sceneId, ObjId)

	DeleteBus(sceneId, ObjId,1)

end


--����������BUS
--selfId�����ID
--targetId��BUSID
function x300872_OnIntoBusEvent(sceneId, selfId,targetId)
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"���Ѿ��ڻ���������");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local BusSize = GetBusSize(sceneId,targetId)
	local MemberNum = GetBusMemberCount(sceneId,targetId)

	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"�������Ѿ����˻�����");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )
	if IsOwner == 1 then
		--����BUS
		AddBusMember(sceneId, selfId,targetId)
	end
end


function x300872_OnIntoBusAfter(sceneId, selfId,BusID)
	AcceptGuildConvoy( sceneId, selfId,BusID )
	local CarName = GetName( sceneId, selfId ).."������"
	SetBusTitle(sceneId , BusID, CarName)
	local GuildId = GetGuildID(sceneId, selfId)
	local Guildname = GetGuildName(GuildId)
	local msg = format(""..Guildname.."�����ɹ���ȡ���ޣ�")
	LuaThisScenceM2Guild(sceneId,msg,GuildId,5,1)
	local camp = GetCurCamp(sceneId, selfId)
	SetBusCurCamp(sceneId, BusID,camp)

end


--����뿪BUS
--selfId�����ID
function x300872_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"�����ڻ������ޣ��޷��뿪");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
end


function x300872_OnTime(sceneId,BusId)

end

function x300872_OnLifeTimeOut(sceneId,BusId)

	AbandonGuildConvoyQuest(sceneId, BusId,7)
	local GuildID = GetBusGuildID(sceneId,BusId)
	local CurDaytime = GetDayTime()						--��ǰʱ��(��)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	DeleteBus(sceneId, BusId,1)
end

function x300872_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end

function x300872_OnWaitTimeOut(sceneId,BusId)
	
	AbandonGuildConvoyQuest(sceneId, BusId,6)	
	local GuildID = GetBusGuildID(sceneId,BusId)
	local CurDaytime = GetDayTime()						--��ǰʱ��(��)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)
	DeleteBus(sceneId, BusId,1)
	
end

function x300872_OnDie(sceneId,BusId,idKiller)

	AbandonGuildConvoyQuest(sceneId, BusId,5)
	local GuildID = GetBusGuildID(sceneId,BusId)
	local CurDaytime = GetDayTime()						--��ǰʱ��(��)
	SetGuildQuestData(sceneId,GuildID, GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME, CurDaytime)

	if idKiller == -1 then
		--��������Ŀǰֻ���ڽ����Ͷ�����ǰɾ���ڳ�
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			local Readme = "�����͵����ޱ�ɱ��"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ޱ���ɱ����");DispatchQuestTips(sceneId,OwnerID);EndQuestEvent(sceneId);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	if IsObjValid(sceneId,idKiller)  == 0 then
		--��ЧOBJ
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			local Readme = "�����͵����ޱ�ɱ��"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ޱ�ɱ��!");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
		end
		return
	end

	local ObjType = GetObjType(sceneId,idKiller)

	if ObjType == 3 then		-- ��PETɱ��
		ObjType = 1
		idKiller = GetOwnerID(sceneId, idKiller)
		if IsPlayerStateNormal(sceneId,idKiller)  == 0 then
			--״̬������
			local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerID ~= -1 then
				local Readme = "�����͵����ޱ�ɱ��"
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ޱ�ɱ��!");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,8,2)
			end
			return
		end
	end

	if ObjType == 1 then     --�����ɱ�� 
		local OwnerCountry = GetBusCountryID(sceneId,BusId)
		local KillerCountry = GetCurCountry(sceneId,idKiller)
		if OwnerCountry == KillerCountry then

			--PK�ͷ�
			local IsPunish = 0
			local OwnerId = GetBusMemberObjId(sceneId,BusId,0)
			if OwnerId ~= -1 then
				local IsPunish = CallScriptFunction( SCENE_SCRIPT_ID, "CashboxComputePKPunish", sceneId, OwnerId, idKiller )
				if IsKing( sceneId, idKiller ) ~= 1 and IsPunish == 1 then
					--�ǹ�������PK�ͷ�ֵ����0
					CallScriptFunction( SCENE_SCRIPT_ID, "KillerEnterPrison", sceneId, idKiller )
					IsPunish = 1
				else
					IsPunish = 0
				end
			end
			
			if IsPunish==1 then
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "����ɱ�˱��������ޣ�����PKֵ������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,"����ɱ�˱��������ޣ�����PKֵ������",8,2)				
			else
				BeginQuestEvent(sceneId);AddQuestText(sceneId, "����ɱ�˱���������");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
				Msg2Player(sceneId,idKiller,"����ɱ�˱���������",8,2)			
			end			

		else
	        AddMoney(sceneId,idKiller,0,x300872_g_CostMoney)
		  	BeginQuestEvent(sceneId);AddQuestText(sceneId, "����ɱ�˵й������ޣ�������˽�����");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,idKiller)
			Msg2Player(sceneId,idKiller,format("����ɱ�˵й������ޣ������������#{_MONEY%d}��", x300872_g_CostMoney),8,2)	
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
			
			local GuildTitle = ""
			if GetGuildID(sceneId,idKiller) ~= -1 then
				GuildTitle = GetGuildTitle(sceneId,idKiller)
			end
			local GuildTitle1 = GetGuildTitle(sceneId,OwnerID)
			local killerName = GetName(sceneId,idKiller)
			local Readme = "���ޱ�"..Country..GuildTitle.."�����"..killerName.."�ݻ٣�ȫ�廤�ͳ�Ա����ʧ�ܣ�"
			msg1 = "��ɽ����"..GuildTitle1.."�����ޱ�"..Country..GuildTitle.."��"..killerName.."��ɱ"
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_PLANE_SCROLL, 1)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_LEFTDOWN, 1)
			LuaAllScenceM2Wrold(sceneId, msg1, CHAT_MAIN_RIGHTDOWN, 1)
			if IsHideName(sceneId,idKiller) > 0 then
				Readme = "���ޱ�"..HIDE_NAME.."�ݻ٣�ȫ�廤�ͳ�Ա����ʧ�ܣ�"
			end
			
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ޱ��ݻ٣�");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,6,1)
		end
	else			--������ɱ��
		local OwnerID = GetBusMemberObjId(sceneId,BusId,0)
		if OwnerID ~= -1 then
			local Readme = "���ޱ�����ɱ����ȫ�廤�ͳ�Ա����ʧ�ܣ�"
			BeginQuestEvent(sceneId);AddQuestText(sceneId, "���ޱ�ɱ����");EndQuestEvent(sceneId);DispatchQuestTips(sceneId,OwnerID);Msg2Player(sceneId,OwnerID,Readme,6,1)		
		end

	end
	
end

