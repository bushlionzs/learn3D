--���ܣ���������Trap
--Trap



x550307_g_ScriptId = 550307
x550307_g_TransPos="liangcangexitthree"


--��ҽ���һ�� area ʱ����
function x550307_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550307_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550307_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550307_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550307_ProcEventEntry( sceneId, monsterobjid )

end

