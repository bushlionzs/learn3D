
x300162_g_ScriptId = 300162
x300162_g_FarScriptId = 300160
x300162_g_BuffId = 7646

--�������ʱ����
function x300162_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300162_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300162_g_BuffId)
	end
end

--��Чʱ����
function x300162_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300162_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300162_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300162_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300162_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300162_ProcEventEntry( sceneId, selfId, bagIndex)
end


