--���ܣ����˹�Trap
--Trap



x550311_g_ScriptId = 550311
x550311_g_TransPos="xianrenguentertwo"


--��ҽ���һ�� area ʱ����
function x550311_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550311_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550311_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550311_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550311_ProcEventEntry( sceneId, monsterobjid )

end

