
x300183_g_ScriptId = 300183
x300183_g_FarScriptId = 300160
x300183_g_BuffId = 7666

--�������ʱ����
function x300183_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300183_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300183_g_BuffId)
	end
end

--��Чʱ����
function x300183_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300183_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300183_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300183_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300183_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300183_ProcEventEntry( sceneId, selfId, bagIndex)
end


