
x300167_g_ScriptId = 300167
x300167_g_FarScriptId = 300160
x300167_g_BuffId = 7648

--�������ʱ����
function x300167_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300167_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300167_g_BuffId)
	end
end

--��Чʱ����
function x300167_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300167_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300167_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300167_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300167_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300167_ProcEventEntry( sceneId, selfId, bagIndex)
end


