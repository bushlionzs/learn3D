--���ܣ�ս�����޸Ľű��ű�


x911113_g_ScriptId = 911113
x911113_g_MissionName = "�ɳ����� �л�"



--**********************************

--������ں���

--**********************************

function x911113_ProcEventEntry(sceneId, selfId, targetId)	--����������ִ�д˽ű�
	local IsDriver = IsBusLeader(sceneId , selfId)
	
	if IsDriver == 1 then
		local BusObjID = GetBusId(sceneId,selfId)
		local Size = GetBusSize(sceneId, BusObjID)
		local MemCount = GetBusMemberCount(sceneId, BusObjID)
		local BusType  = GetBusType(sceneId, BusObjID)
		local BusIndex = GetBusIndex(sceneId, BusObjID)	
		
		if BusType == 1 and BusIndex == 2 then	
			Size = Size + 1
			if Size > 10 then
				Size = MemCount
				if Size == 0 then
					Size = 1
				end
			end
			SetBusMemberNum(sceneId, BusObjID, Size)
			local AIStr = "���BUS���Գ���"..Size.."��"
			
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,"�����ã�ÿ�����BUS���Գ�����������#R��1#W��������10��ʱ���᷵�ص��㵱ǰBUS�ڵ����������¼�����#GĿǰ"..AIStr.."#W��")
			EndQuestEvent()	
			DispatchQuestEventList(sceneId,selfId,targetId)
			
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,AIStr);
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 3 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"�ڳ��Ǻ�רһ�ģ���û�иı�����һ˵�����ԡ���");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		elseif BusIndex == 1 then	
			BeginQuestEvent(sceneId)
			  AddQuestText(sceneId,"ϵͳBUS��׼������ʻ");
			EndQuestEvent()
			DispatchQuestTips(sceneId,selfId)
		end
	end
end


--**********************************

--�о��¼�

--**********************************
function x911113_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	AddQuestNumText(sceneId, x911113_g_ScriptId, x911113_g_MissionName);
end

function x911113_OnDie(sceneId,BusId,idKiller)
end