--���ܣ�ս�����޸Ľű��ű�


x911112_g_ScriptId = 911112
x911112_g_MissionName = "�ɱ�����/�޵� �л�"



--**********************************

--������ں���

--**********************************

function x911112_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�

	local IsDriver = IsBusLeader(sceneId , selfId)
	
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local BusType  = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
		
		if BusType == 1 and BusIndex == 2 then
			local AIStr = "���ս�����ڿɱ�����״̬"
			if random(1,2) == 1 then
				SetBusAIType(sceneId, BusObjID, 7)
				AIStr = "���ս�����ڿɱ�����״̬"
			else
				SetBusAIType(sceneId, BusObjID, 3)
				AIStr = "���ս�������޵�״̬"
			end
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ã�ÿ����һ��ĸ��ʱ�����Ϊ���޵�״̬���������ɱ�������һ��ĸ��ʱ�����Ϊ���ɱ�����״̬���������ܹ������ݻ١�#GĿǰ"..AIStr.."#W��")
			EndQuestEvent( )	
			DispatchQuestEventList(sceneId,selfId,targetId)
			
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,AIStr);
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 3 then
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"�ڳ���ʱ��ϣ���ܹ����Ĺ���״̬");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 1 then
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"ϵͳBUS��ʱ��ϣ���ܹ����Ĺ���״̬");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
			
	end	
end


--**********************************

--�о��¼�

--**********************************
function x911112_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911112_g_ScriptId, x911112_g_MissionName);
end

function x911112_OnDie(sceneId,BusId,idKiller)
end