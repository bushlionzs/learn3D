--���ܣ�ս�����޸Ľű��ű�


x911116_g_ScriptId = 911116
x911116_g_MissionName = "�ڳ�/BUS �л�"



--**********************************

--������ں���

--**********************************

function x911116_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local IsDriver = IsBusLeader(sceneId , selfId)
	
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local BusType = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
		
		if BusType == 1 and BusIndex == 2 then	
			local AIStr = "����ڳ�ת��ΪBUS"
			if BusType == 1 then
				BusChangeState(sceneId, BusObjID)
				AIStr = "����ڳ�ת��ΪBUS"
				local CarName = GetName( sceneId, selfId ).." ��BUS"
				SetBusTitle(sceneId , BusObjID, CarName)
			elseif BusType == 0 then 
				BusChangeState(sceneId, BusObjID)
				AIStr = "���BUSת��Ϊ�ڳ�"
				local CarName = GetName( sceneId, selfId ).." ���ڳ�"
				SetBusTitle(sceneId , BusObjID, CarName)
			end
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ã���������Ƶĳ����ڳ���BUS֮���л�����#GĿǰ"..AIStr.."#W��")
			EndQuestEvent( )	
			DispatchQuestEventList(sceneId,selfId,targetId)
			
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,AIStr);
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	end	
end


--**********************************

--�о��¼�

--**********************************
function x911116_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911116_g_ScriptId, x911116_g_MissionName);
end


function x911116_OnDie(sceneId,BusId,idKiller)
end