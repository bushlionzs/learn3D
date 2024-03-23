--���ܣ�ս����Ĭ�Ͻű�
--MD_BUS_MISSION_COMPLETE_DATE 	= { 201, 0, 9 } --bus���ɵ�ʱ��
--MD_BUS_MISSION_PATROL1 				= { 201, 9, 7 } --bus�Ѳ�ߵ�1ID
--MD_BUS_MISSION_PATROL2 				= { 201, 16, 7 } --bus�Ѳ�ߵ�2ID
--MD_BUS_MISSION_PATROL3 				= { 201, 23, 7 } --bus�Ѳ�ߵ�3ID

x310080_g_ScriptId = 310080

--�޵�impact�ڱ��е�����,��ҽ���BUS����һ���޵�impact,
x310080_g_AddBuffId = 1210
x310080_g_BusGameImpact = 7043

x310080_g_AvoidItem	=	12030055

--TimerTick=10000�������޸� ������ܻ�ĵ�
x310080_g_Carinfo ={
			{CarType = 32,BaseAI = 3,AIScript = 3,Script = 310080, CarName = "�������䡪��·", TimerTick=10000},
			{CarType = 33,BaseAI = 3,AIScript = 3,Script = 310080, CarName = "��������", TimerTick=10000},
			{CarType = 34,BaseAI = 3,AIScript = 3,Script = 310080, CarName = "�������䡪��·", TimerTick=10000},
		}

x310080_g_ErrorMessage_AlreadyInBus	=	"�������޷��ϳ�"
x310080_g_ErrorMessage_BusFull			=	"�����Ѿ�û�п�λ�ˣ���ȴ���һ����"
x310080_g_ErrorMessage_buff					= "�����������ٳ�������"
x310080_g_AskForEnterMessage	=	"#Y���������䡿#W\n\t�Ƿ�Ҫ�ϳ���"

x310080_g_Bufflist  ={ 22090, 22091, 22092, 22093, 22094, 22095, 22096, 22097, 22098,22099}

x310080_g_ScenePatrol	=	{
													{sceneId=89, patrolId=4, PosX=241, PosZ=249, CarType = 32},
													{sceneId=89, patrolId=5, PosX=23, PosZ=144, CarType = 33},
													{sceneId=89, patrolId=6, PosX=113, PosZ=106, CarType = 34},
													{sceneId=189, patrolId=4, PosX=241, PosZ=249, CarType = 32},
													{sceneId=189, patrolId=5, PosX=232, PosZ=122, CarType = 33},
													{sceneId=189, patrolId=6, PosX=113, PosZ=106, CarType = 34},
													{sceneId=289, patrolId=4, PosX=241, PosZ=249, CarType = 32},
													{sceneId=289, patrolId=5, PosX=56.5, PosZ=149.7, CarType = 33},
													{sceneId=289, patrolId=6, PosX=113, PosZ=106, CarType = 34},
													{sceneId=389, patrolId=4, PosX=241, PosZ=249, CarType = 32},
													{sceneId=389, patrolId=5, PosX=161, PosZ=86, CarType = 33},
													{sceneId=389, patrolId=6, PosX=113, PosZ=106, CarType = 34}
												}

x310080_g_SceneInfo = {--ÿ������:����id,bus����
													{sceneId=89, 	countryID=0,BusFaceDir = 90},
													{sceneId=189, countryID=1,BusFaceDir = 270},
													{sceneId=289, countryID=2,BusFaceDir = 0},
													{sceneId=389, countryID=3,BusFaceDir = 190},
												}
																								
function x310080_GetCountryID(sceneId)

	for i, item in x310080_g_SceneInfo do
		if item.sceneId == sceneId then
			return item.countryID
		end
	end

	return -1
end												

function x310080_GetBusFaceDir(sceneId)

	for i, item in x310080_g_SceneInfo do
		if item.sceneId == sceneId then
			return item.BusFaceDir
		end
	end

	return 0
end	

function x310080_GetStartPos(sceneId, index)

	local count = 1
	for i, item in x310080_g_ScenePatrol do
		if item.sceneId == sceneId then
			if count < index then
				count = count + 1
			else
				return item.PosX, item.PosZ;
			end
		end
	end
	return 0, 0;

end

function x310080_g_SetPatrol(sceneId, targetId, patrolId)
	for i, item in x310080_g_ScenePatrol do
		if item.sceneId == sceneId then
			SetBusPatrolId(sceneId , targetId, patrolId);--item.patrolId);
		end
	end

end


function x310080_OnDelayTime(sceneId, targetId, paraDelayTime)

	x310080_g_SetPatrol(sceneId, targetId, paraDelayTime);
end

function x310080_GetRandomTime()
	return 30000
end

--**********************************
--����bus
--**********************************
function x310080_OnCreateBus(sceneId, countryID)

	local i=2;
	local PosX, PosZ = x310080_GetStartPos(sceneId, i);
	local nFaceDir = x310080_GetBusFaceDir(sceneId)
	
	--CreateBus˵��������10������Bus������id,û����-1;����11������Bus�ĻỰnpc,û����-1;����12��Bus�ĳ���û�в���
	--CreateBusֻ����GLServer���봴��Bus,�������ɹ�����MapServer����BUs�ɹ�,��ʱ�ص����󶨽ű���OnCreateBusOK����,�ݴ˽ű�����ҵ����
	
	CreateBus(sceneId, x310080_g_Carinfo[i].CarType, PosX, PosZ, x310080_g_Carinfo[i].BaseAI, x310080_g_Carinfo[i].AIScript, x310080_g_ScriptId, -1, x310080_g_AddBuffId, -1,-1,nFaceDir)
	
end

function x310080_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)

	local i=2;
	
	local countryID = x310080_GetCountryID(sceneId)	
		
	if countryID == -1 then
		return
	end

	SetBusTitle(sceneId , busId, x310080_g_Carinfo[i].CarName);
	SetBusCountryID(sceneId , busId, countryID);
	SetBusCurCamp(sceneId , busId, countryID);
	SetDelayTimeAfterCreate( sceneId, busId, 10000, i+3 );
	
	SetBusTimerTick(sceneId , busId, x310080_GetRandomTime());
	
	SetBusTimerOpen(sceneId, busId, 1);
	--��bus���޵�
	SendSpecificImpactToUnit(sceneId, busId, busId, busId, 7060, 0)
	
end

--**********************************
--������غ���
--**********************************

function x310080_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	local iLevel = GetLevel(sceneId, selfId)
	if iLevel < 20 then
		local str = "��ĵȼ�����20���޷��ϳ�";
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, str);
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId, selfId, str, CHAT_TYPE_NORMAL, CHAT_RIGHTDOWN);
		return 0
	end

	local bIsBusMoving = IsBusMoving(sceneId, targetId)
	if bIsBusMoving > 0 then
		local str = "�����Ѿ��������޷��ϳ�";
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, str);
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId, selfId, str, CHAT_TYPE_NORMAL, CHAT_RIGHTDOWN);
		return 0
	end
	--����ս����
	local str = x310080_g_AskForEnterMessage;
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,str)
	EndQuestEvent()
	DispatchQuestInfoNM(sceneId, selfId, targetId, 310080, -1);
	
end

function x310080_ProcAcceptCheck(sceneId, selfId, targetId)

	if IsHideName(sceneId, selfId) > 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��Ǹ������״̬�����ϳ���")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 
	end
	
	x310080_OnIntoBusEvent(sceneId, selfId, targetId);
end

function x310080_ProcAccept(sceneId, selfId, targetId)
	x310080_OnIntoBusEvent(sceneId, selfId, targetId);
end

function x310080_OnBusEnterScene(sceneId, targetId)
	--local PosX, PosZ = x310080_GetStartPos(sceneId);
	--SetBusPos(sceneId, targetId, PosX, PosZ)
	--x310080_g_SetPatrol(sceneId, targetId);

end

function x310080_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
x310080_ProcEventEntry(sceneId, selfId, targetId)
end

function x310080_CheckAndDisplayError(sceneId, selfId, targetId)

	local InBus = IsBusMember(sceneId, selfId)	
	local str;
	if InBus == 1 then
		str = x310080_g_ErrorMessage_AlreadyInBus;
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, str)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId, selfId, str, CHAT_TYPE_NORMAL, CHAT_RIGHTDOWN);
		return 0;
	end
			
	local BusSize = GetBusSize(sceneId,targetId) 
	local MemberNum = GetBusMemberCount(sceneId,targetId)
	
	if BusSize<=MemberNum  then
		str = x310080_g_ErrorMessage_BusFull;
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, str)
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId, selfId, str, CHAT_TYPE_NORMAL, CHAT_RIGHTDOWN);
		return 0;
	end
	
	for i, item in x310080_g_Bufflist do
			if IsHaveSpecificImpact( sceneId, selfId, item) == 1 then
				str = x310080_g_ErrorMessage_buff;
				BeginQuestEvent(sceneId)
					AddQuestText(sceneId, str)
				EndQuestEvent()
				DispatchQuestTips(sceneId, selfId)
				Msg2Player(sceneId, selfId, str, CHAT_TYPE_NORMAL, CHAT_RIGHTDOWN);
				return 0;
			end	
	end
	return 1
end

--**********************************
--ɾ��bus
--**********************************
--ObjId:BUSID
function x310080_DeleteBus(sceneId, busId)

	local busSize = GetBusSize(sceneId, busId)
	for	i = 0, busSize - 1 do
		local ObjID = GetBusMemberObjId(sceneId, busId, i)
		if ObjID ~= -1 then
			DelBusMember(sceneId, ObjID, busId)
			SetWanFaExpMult(  sceneId, ObjID,  0 )
			CancelSpecificImpact(sceneId,ObjID, 7060)
		end
	end
			
	DeleteBus(sceneId, busId,1)
	
end



---------------------------------------------------------------------------------------------------
--ȡ�õ�ǰ����
---------------------------------------------------------------------------------------------------
function x310080_RecordData(sceneId, selfId,index)
	SetQuestData(sceneId,selfId,MD_BUS_PATROL_RECORD[1],MD_BUS_PATROL_RECORD[2],MD_BUS_PATROL_RECORD[3],index + 1)
end

function x310080_GetRecordData(sceneId, selfId,index)
	local result = GetQuestData(sceneId, selfId, MD_BUS_PATROL_RECORD[1], MD_BUS_PATROL_RECORD[2],MD_BUS_PATROL_RECORD[3] )
	return result - 1
end

--**********************************
--����bus
--**********************************
--����������BUS
--selfId�����ID
--targetId��BUSID
function x310080_OnIntoBusEvent(sceneId, selfId, targetId)
	
	local bIsBusMoving = IsBusMoving(sceneId, targetId)
	if bIsBusMoving > 0 then
		local str = "�����Ѿ��������޷��ϳ�";
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, str);
		EndQuestEvent()
		DispatchQuestTips(sceneId, selfId);
		Msg2Player(sceneId, selfId, str, CHAT_TYPE_NORMAL, CHAT_RIGHTDOWN);
		return 0
	end

	--����BUS
	if x310080_CheckAndDisplayError(sceneId, selfId, targetId) > 0 then
		AddBusMember(sceneId, selfId, targetId);

		SendSpecificImpactToUnit(sceneId, sceneId, sceneId, sceneId, 7060, 0)
		CallScriptFunction( 203782, "FinishGongche", sceneId, selfId)
		CallScriptFunction( 203783, "FinishGongche", sceneId, selfId)
		CallScriptFunction( 203784, "FinishGongche", sceneId, selfId)
		CallScriptFunction( 203785, "FinishGongche", sceneId, selfId)
		--x310080_RecordData(sceneId, selfId, iIndex)
		--��¼���ϳ�����
		GamePlayScriptLog( sceneId, selfId, 391)
		return 1;
	end
	return 0;
end

--**********************************
--�뿪bus
--**********************************
--����뿪BUS
--selfId�����ID
function x310080_OnLeaveBusEvent(sceneId, selfId,BusId)
	 DelBusMember(sceneId, selfId,BusId)
	 CancelSpecificImpact(sceneId,selfId, 7060)
end

--**********************************
--bus timer
--**********************************
function x310080_OnTime(sceneId,BusId)

	local bIsBusMoving = IsBusMoving(sceneId, BusId)
	if bIsBusMoving <= 0 then
		return 0
	end

	local MemberNum = GetBusMemberCount(sceneId,BusId)

	if MemberNum <= 0 then
		x310080_DeleteBus( sceneId, BusId )
		return 0;
	end
	
	local pos
	for pos=0, tonumber(MemberNum ) do
		local targetId = GetBusMemberObjId(sceneId, BusId, pos)
		if targetId > 0 then
		
			local nLevel = GetLevel( sceneId, targetId )
			
			--��������
			local bonusExp = nLevel * 100
			AddExp( sceneId,targetId, bonusExp )
			local str = "��þ��飺"..bonusExp.."��"
			
			BeginQuestEvent( sceneId )
			AddQuestText( sceneId, str )
			EndQuestEvent()
			DispatchQuestTips( sceneId, targetId )

			--���⾭��
			local bonusExpExt = floor((MemberNum-1)* 0.14 * bonusExp)
			if bonusExpExt > 0 then
			
				AddExp( sceneId,targetId, bonusExpExt )
				str = "�����þ��飺"..bonusExpExt.."��"
					
				BeginQuestEvent( sceneId )
				AddQuestText( sceneId, str )
				EndQuestEvent()
				DispatchQuestTips( sceneId, targetId )
			end

			--��ý𿨽���
			local bonusMoney = nLevel * 3
			AddMoney( sceneId, targetId, 1, bonusMoney)
            str = format( "���������#{_MONEY%d}", bonusMoney)

			BeginQuestEvent( sceneId )
			AddQuestText( sceneId, str )
			EndQuestEvent()
			DispatchQuestTips( sceneId, targetId )
			
		end
	end

	
	StopBusTimer(sceneId,BusId)
	SetBusTimerTick(sceneId , BusId, x310080_GetRandomTime());
	
end


function x310080_OnLifeTimeOut(sceneId,BusId)

end

function x310080_OnWaitTimeOut(sceneId,BusId)
	x310080_DeleteBus( sceneId, BusId )
end

function x310080_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end

function x310080_OnDie(sceneId,BusId,idKiller)
end
