--���ܣ����˹�Trap
--Trap

x550310_g_ScriptId = 550310
x550310_g_TransPos={"xianrenguexitone1","xianrenguexitone2","xianrenguexitone3","xianrenguexitone4"}


--��ҽ���һ�� area ʱ����
function x550310_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	local country = GetCurCountry(sceneId, selfId)
	if country == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550310_g_TransPos[1])
	elseif country == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550310_g_TransPos[2])
	elseif country == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550310_g_TransPos[3])
	elseif country == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550310_g_TransPos[4])
	end

end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550310_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550310_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550310_ProcEventEntry( sceneId, monsterobjid )

end

