--���ܣ���������Trap
--Trap

x550316_g_ScriptId = 550316
x550316_g_TransPos="xianrenguexitfour"


--��ҽ���һ�� area ʱ����
function x550316_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550316_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550316_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550316_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550316_ProcEventEntry( sceneId, monsterobjid )

end

