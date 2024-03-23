--���ܣ�ս����Ĭ�Ͻű�


x911117_g_ScriptId = 911117
x911117_g_MissionName = "�����ڳ�"

--�޵�impact�ڱ��е�����,��ҽ���BUS����һ���޵�impact,
x911117_g_GodIndex = 1210
x911117_g_Carinfo = {CarType = 3,BaseAI = 3,AIScript = 3,Script = 911117 }


--**********************************

--������ں���

--**********************************

function x911117_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	
	--���󴴽�ս����
	local PosX,PosZ = GetWorldPos(sceneId, selfId)

	local ObjID = CreateBus(sceneId, x911117_g_Carinfo.CarType, PosX, PosZ, x911117_g_Carinfo.BaseAI, x911117_g_Carinfo.AIScript, x911117_g_Carinfo.Script, selfId, x911117_g_GodIndex,-1,targetId)
	
end

--**********************************

--bus�����ɹ�����

--**********************************
function x911117_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)
	
	local CarName = GetName( sceneId, selfId ).." ���ڳ�"
	SetBusTitle(sceneId , busId, CarName)
	SetBusTimerTick(sceneId ,busId, 1000)
	SetBusWaitTime(sceneId , busId, 5)
	SetBusLifeTime(sceneId , busId, 120)
	SetBusTimerOpen(sceneId, busId, 0)
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"�㴴����һ���ڳ��������Զ��������ƶ���������뿪������15�׳���5���ӣ����ڳ������Զ���ʧ��2���Ӻ󣬸��ڳ�Ҳ�����Զ���ʧ��")
	EndQuestEvent( )	
	DispatchQuestEventList(sceneId,selfId,targetId)
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"�㴴����һ���ڳ�");
	EndQuestEvent()
	DispatchQuestTips(sceneId,selfId)
end



function x911117_DeleteBus(sceneId, ObjId)
		
	DeleteBus(sceneId, ObjId,1)

end


--**********************************

--�о��¼�

--**********************************
function x911117_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911117_g_ScriptId, x911117_g_MissionName);
end



--ObjId:BUSID
function x911117_DeleteBus(sceneId, ObjId)
		
	DeleteBus(sceneId, ObjId,1)

end

--����������BUS
--selfId�����ID
--targetId��BUSID
function x911117_OnIntoBusEvent(sceneId, selfId,targetId)
--	print("123")
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"���Ѿ����ڳ���");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return 
	end
			
	local BusSize = GetBusSize(sceneId,targetId) 
	local MemberNum = GetBusMemberCount(sceneId,targetId)
	
	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"�����ڳ��Ѿ���������");
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

--����뿪BUS
--selfId�����ID
function x911117_OnLeaveBusEvent(sceneId, selfId,BusId)
		BeginQuestEvent(sceneId)
		  AddQuestText(sceneId,"���������ڣ��޷��뿪");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
end


function x911117_OnTime(sceneId,BusId)

end

function x911117_OnLifeTimeOut(sceneId,BusId)
	DeleteBus(sceneId, BusId,1)
end

function x911117_OnWaitTimeOut(sceneId,BusId)
	DeleteBus(sceneId, BusId,1)
end

function x911117_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end

function x911117_OnDie(sceneId,BusId,idKiller)
end