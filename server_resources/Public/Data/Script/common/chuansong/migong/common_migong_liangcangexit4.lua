--���ܣ���������Trap
--Trap



x550308_g_ScriptId = 550308
x550308_g_TransPos="liangcangexitfour"


--��ҽ���һ�� area ʱ����
function x550308_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550308_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550308_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550308_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550308_ProcEventEntry( sceneId, monsterobjid )

end

