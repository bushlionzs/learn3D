
x300166_g_ScriptId = 300166
x300166_g_FarScriptId = 300160
x300166_g_BuffId = 7647

--�������ʱ����
function x300166_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300166_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300166_g_BuffId)
	end
end

--��Чʱ����
function x300166_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300166_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300166_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300166_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300166_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300166_ProcEventEntry( sceneId, selfId, bagIndex)
end


