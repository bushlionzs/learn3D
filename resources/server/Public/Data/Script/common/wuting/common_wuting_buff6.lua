
x300176_g_ScriptId = 300176
x300176_g_FarScriptId = 300160
x300176_g_BuffId = 7644

--�������ʱ����
function x300176_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300176_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300176_g_BuffId)
	end
end

--��Чʱ����
function x300176_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300176_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300176_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300176_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300176_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300176_ProcEventEntry( sceneId, selfId, bagIndex)
end


