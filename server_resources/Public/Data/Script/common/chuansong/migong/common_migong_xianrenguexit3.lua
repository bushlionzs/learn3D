--���ܣ���������Trap
--Trap

x550314_g_ScriptId = 550314
x550314_g_TransPos="xianrenguexitthree"


--��ҽ���һ�� area ʱ����
function x550314_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550314_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550314_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550314_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550314_ProcEventEntry( sceneId, monsterobjid )

end

