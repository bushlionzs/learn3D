--���ܣ���������Trap
--Trap

x550300_g_ScriptId = 550300
x550300_g_TransPos="liangcangenterone"


--��ҽ���һ�� area ʱ����
function x550300_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550300_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550300_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550300_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550300_ProcEventEntry( sceneId, monsterobjid )

end

