
x300191_g_ScriptId = 300191
x300191_g_FarScriptId = 300160
x300191_g_BuffId = 7668

--�������ʱ����
function x300191_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300191_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300191_g_BuffId)
	end
end

--��Чʱ����
function x300191_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300191_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300191_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300191_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300191_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300191_ProcEventEntry( sceneId, selfId, bagIndex)
end


