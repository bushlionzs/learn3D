--���ܣ���������Trap
--Trap


x550309_g_ScriptId = 550309
x550309_g_TransPos="liangcangexitfive"


--��ҽ���һ�� area ʱ����
function x550309_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550309_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550309_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550309_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550309_ProcEventEntry( sceneId, monsterobjid )

end

