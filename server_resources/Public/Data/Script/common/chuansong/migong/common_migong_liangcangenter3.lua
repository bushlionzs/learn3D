--���ܣ���������Trap
--Trap



x550302_g_ScriptId = 550302
x550302_g_TransPos="liangcangenterthree"


--��ҽ���һ�� area ʱ����
function x550302_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550302_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550302_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550302_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550302_ProcEventEntry( sceneId, monsterobjid )

end

