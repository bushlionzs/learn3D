
x300165_g_ScriptId = 300165
x300165_g_FarScriptId = 300160
x300165_g_BuffId = 7650

--�������ʱ����
function x300165_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300165_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300165_g_BuffId)
	end
end

--��Чʱ����
function x300165_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300165_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300165_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300165_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300165_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300165_ProcEventEntry( sceneId, selfId, bagIndex)
end


