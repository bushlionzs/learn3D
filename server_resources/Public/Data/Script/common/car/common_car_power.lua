--���ܣ�ս�����޸Ľű��ű�


x911115_g_ScriptId = 911115
x911115_g_MissionName = "ϵͳ����"



--**********************************

--������ں���

--**********************************

function x911115_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local IsDriver = IsBusLeader(sceneId , selfId)
		
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local BusType  = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
	
		if BusType == 1 and BusIndex == 2 then			
				SetBusSysControl(sceneId, BusObjID, 1)
				local AIStr = "ϵͳ����"

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
			  AddQuestText(sceneId,"�ڳ��������Ǹ��������Ŷ");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 1 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"ϵͳBUS��Ҫϵͳ���ƣ���Ҫ���Ұ�");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	end	
end


--**********************************

--�о��¼�

--**********************************
function x911115_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911115_g_ScriptId, x911115_g_MissionName);
end

function x911115_OnDie(sceneId,BusId,idKiller)
end