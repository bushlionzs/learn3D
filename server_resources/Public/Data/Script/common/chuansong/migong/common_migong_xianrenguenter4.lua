--���ܣ����˹�Trap
--Trap



x550315_g_ScriptId = 550315
x550315_g_TransPos="xianrenguenterfour"


--��ҽ���һ�� area ʱ����
function x550315_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550315_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550315_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550315_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550315_ProcEventEntry( sceneId, monsterobjid )

end

