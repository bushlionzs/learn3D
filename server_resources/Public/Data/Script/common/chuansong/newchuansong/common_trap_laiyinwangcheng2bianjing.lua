

x550102_g_ScriptId = 550102
x550102_g_TransPos="laiyinwangcheng2bianjing"


--��ҽ���һ�� area ʱ����
function x550102_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550102_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550102_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550102_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550102_ProcEventEntry( sceneId, monsterobjid )

end

