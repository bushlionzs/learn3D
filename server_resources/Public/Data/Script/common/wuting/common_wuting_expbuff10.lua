
x300181_g_ScriptId = 300181
x300181_g_FarScriptId = 300160
x300181_g_BuffId = 7667

--�������ʱ����
function x300181_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300181_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300181_g_BuffId)
	end
end

--��Чʱ����
function x300181_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300181_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300181_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300181_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300181_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300181_ProcEventEntry( sceneId, selfId, bagIndex)
end


