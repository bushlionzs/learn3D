--���ܣ���������Trap
--Trap

x550312_g_ScriptId = 550312
x550312_g_TransPos={"xianrenguexittwo1","xianrenguexittwo2","xianrenguexittwo3","xianrenguexittwo4"}


--��ҽ���һ�� area ʱ����
function x550312_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	local country = GetCurCountry(sceneId, selfId)
	if country == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550312_g_TransPos[1])
	elseif country == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550312_g_TransPos[2])
	elseif country == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550312_g_TransPos[3])
	elseif country == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550312_g_TransPos[4])
	end

end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550312_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550312_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550312_ProcEventEntry( sceneId, monsterobjid )

end

