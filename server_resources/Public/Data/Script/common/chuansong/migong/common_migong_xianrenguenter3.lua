--���ܣ����˹�Trap
--Trap



x550313_g_ScriptId = 550313
x550313_g_TransPos="xianrenguenterthree"


--��ҽ���һ�� area ʱ����
function x550313_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550313_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550313_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550313_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550313_ProcEventEntry( sceneId, monsterobjid )

end

