--���ܣ���������Trap
--Trap

x550306_g_ScriptId = 550306
x550306_g_TransPos="liangcangexittwo"


--��ҽ���һ�� area ʱ����
function x550306_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550306_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550306_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550306_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550306_ProcEventEntry( sceneId, monsterobjid )

end

