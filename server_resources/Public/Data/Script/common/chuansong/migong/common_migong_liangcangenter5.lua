--���ܣ���������Trap
--Trap

x550304_g_ScriptId = 550304
x550304_g_MissionName="��������"
x550304_g_TransPos="liangcangenterfive"


--��ҽ���һ�� area ʱ����
function x550304_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550304_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550304_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550304_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550304_ProcEventEntry( sceneId, monsterobjid )

end

