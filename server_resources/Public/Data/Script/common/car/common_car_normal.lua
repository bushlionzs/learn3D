--���ܣ�ս����Ĭ�Ͻű�


x911111_g_ScriptId = 911111
x911111_g_MissionName = "��������BUS"

--�޵�impact�ڱ��е�����,��ҽ���BUS����һ���޵�impact,
x911111_g_GodIndex = 1210
x911111_g_Carinfo = {CarType = 2,BaseAI = 3,AIScript = 3,Script = 911111 }


--**********************************

--������ں���

--**********************************

function x911111_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	
	--����ս����
	local PosX,PosZ = GetWorldPos(sceneId, selfId)
	
	local ObjID = CreateBus(sceneId, x911111_g_Carinfo.CarType, PosX, PosZ, x911111_g_Carinfo.BaseAI, x911111_g_Carinfo.AIScript, x911111_g_Carinfo.Script, selfId, x911111_g_GodIndex,-1,targetId)
end
	
--**********************************

--bus�����ɹ�����

--**********************************
function x911111_OnCreateBusOK(sceneId,selfId,busId,targetId,MissionId)
	
	local CarName = GetName( sceneId, selfId ).." �Ĺ���BUS"
	SetBusTitle(sceneId , busId, CarName)
	SetBusTimerTick(sceneId , busId, 1000)
	SetBusWaitTime(sceneId , busId, 20)
	SetBusLifeTime(sceneId , busId, 300)
	SetBusTimerOpen(sceneId, busId, 0)
	SetBusLeaderFiatMode(sceneId, busId,1)
	
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"�㴴����һ������BUS��Ŀǰ����2�ˡ�5���Ӻ󣬽�BUS���Զ���ʧ������ճ�����20�룬��BUSҲ���Զ���ʧ��")
	EndQuestEvent()	
	DispatchQuestEventList(sceneId,selfId,targetId)
		
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"�㴴����һ������BUS");
	EndQuestEvent()
	DispatchQuestTips(sceneId,selfId)
end


--**********************************

--�о��¼�

--**********************************
function x911111_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911111_g_ScriptId, x911111_g_MissionName);
end



--ObjId:BUSID
function x911111_DeleteBus(sceneId, ObjId)
		
	DeleteBus(sceneId, ObjId,1)

end

--����������BUS
--selfId�����ID
--targetId��BUSID
function x911111_OnIntoBusEvent(sceneId, selfId,targetId)
			
	local InBus = IsBusMember(sceneId, selfId)
	if InBus == 1 then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"���Ѿ���BUS����");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return 
	end
			
	local BusSize = GetBusSize(sceneId,targetId) 
	local MemberNum = GetBusMemberCount(sceneId,targetId)
	
	if BusSize<=MemberNum  then
		BeginQuestEvent(sceneId)
		  	AddQuestText(sceneId,"ս���Ѿ�����Ϊ����");
		EndQuestEvent()
		DispatchQuestTips(sceneId,selfId)
		return
	end
	
	local IsOwner = IsTheBusOwner(sceneId, selfId, targetId )	
	if IsOwner == 1 then
		--����BUS
		AddBusMember(sceneId, selfId,targetId)
	else
		local BusSize = GetBusMemberCount( sceneId, targetId)	
		local BusMemberObjId
		local j = 0
		for i=1,BusSize do
			 BusMemberObjId = GetBusMemberObjId( sceneId,targetId,i-1)
			 if IsTheBusOwner(sceneId, BusMemberObjId, targetId ) == 1 then
			 	j = 1

			 end
		end
		if j == 0 then
			BeginQuestEvent(sceneId)
			  	AddQuestText(sceneId,"����BUS�����˻�û��ȥ�أ�������ȥ��");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
			return
		else
			--����BUS
			AddBusMember(sceneId, selfId,targetId)
		end 
	end
end

--����뿪BUS
--selfId�����ID
function x911111_OnLeaveBusEvent(sceneId, selfId,BusId)
	 DelBusMember(sceneId, selfId,BusId)
	--local MemberNum = GetBusMemberCount(sceneId,BusId)
	--if MemberNum == 0 then
	--	DeleteBus(sceneId, BusId,1)
	--end
end



function x911111_OnTime(sceneId,BusId)

end

function x911111_OnLifeTimeOut(sceneId,BusId)
	DeleteBus(sceneId, BusId,1)
end

function x911111_OnWaitTimeOut(sceneId,BusId)
	DeleteBus(sceneId, BusId,1)
end

function x911111_OnBusStopWhenOwnerFarAway(sceneId, ownerId)
end

function x911111_OnDie(sceneId,BusId,idKiller)
end