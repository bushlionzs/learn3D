

x550103_g_ScriptId = 550103
x550103_g_TransPos="kunlunwangcheng2bianjing"


--��ҽ���һ�� area ʱ����
function x550103_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550103_g_TransPos)
end

--�����һ�� area ����һ��ʱ��û����ʱ����
function x550103_ProcTiming( sceneId, monsterobjid )

end

--����뿪һ�� area ʱ����
function x550103_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550103_ProcEventEntry( sceneId, monsterobjid )

end

