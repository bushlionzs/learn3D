--���ܣ���������Trap
--Trap



x550301_g_ScriptId = 550301
x550301_g_TransPos="liangcangenterone"


--��ҽ���һ�� area ʱ����
function x550301_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550301_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550301_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550301_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550301_ProcEventEntry( sceneId, monsterobjid )

end

