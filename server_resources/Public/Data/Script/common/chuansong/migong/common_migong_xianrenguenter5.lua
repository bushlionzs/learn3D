--���ܣ����˹�Trap
--Trap



x550317_g_ScriptId = 550317
x550317_g_TransPos="xianrenguenterfive"


--��ҽ���һ�� area ʱ����
function x550317_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550317_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550317_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550317_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550317_ProcEventEntry( sceneId, monsterobjid )

end

