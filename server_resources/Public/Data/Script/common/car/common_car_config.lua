--���ܣ�ս�����޸Ľű��ű�


x911114_g_ScriptId = 911114
x911114_g_MissionName = "����BUS�Ƿ���Ҫ˾��ȷ�� �л�"



--**********************************

--������ں���

--**********************************

function x911114_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local IsDriver = IsBusLeader(sceneId , selfId)
	
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local BusType  = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
		
		if BusType == 1 and BusIndex == 2 then	
			local AIStr = "�������BUS����Ҫͨ����ȷ��"
			if random(1,2) == 1 then
				SetBusLeaderFiatMode(sceneId, BusObjID, 0)
				AIStr = "�������BUS����Ҫͨ����ȷ��"
			else
				SetBusLeaderFiatMode(sceneId, BusObjID, 1)
				AIStr = "�������BUS��Ҫͨ����ȷ��"
			end
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ã�ÿ����һ��ĸ��ʱ�����Ϊ������BUS��Ҫ˾��ȷ�ϡ���һ��ĸ��ʱ�����Ϊ������BUS����Ҫ˾��ȷ�ϡ���#GĿǰ"..AIStr.."#W��")
			EndQuestEvent( )	
			DispatchQuestEventList(sceneId,selfId,targetId)
			
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,AIStr);
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 3 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"�ڳ��Ǻ�רһ�ģ���������ñ����������ģ����ԡ���");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 1 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"ϵͳBUS��û˾������������ô�������ԡ���");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	end	
end


--**********************************

--�о��¼�

--**********************************
function x911114_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911114_g_ScriptId, x911114_g_MissionName);
end


function x911114_OnDie(sceneId,BusId,idKiller)
end