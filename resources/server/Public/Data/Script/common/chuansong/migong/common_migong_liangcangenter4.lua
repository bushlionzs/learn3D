--���ܣ���������Trap
--Trap



x550303_g_ScriptId = 550303
x550303_g_TransPos="liangcangenterfour"


--��ҽ���һ�� area ʱ����
function x550303_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550303_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550303_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550303_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550303_ProcEventEntry( sceneId, monsterobjid )

end

