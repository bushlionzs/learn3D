--���ܣ����˹�Trap
--Trap

x550318_g_ScriptId = 550318
x550318_g_TransPos="xianrenguexitfive"


--��ҽ���һ�� area ʱ����
function x550318_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550318_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550318_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550318_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550318_ProcEventEntry( sceneId, monsterobjid )

end

