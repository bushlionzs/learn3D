
x300185_g_ScriptId = 300185
x300185_g_FarScriptId = 300160
x300185_g_BuffId = 7665

--�������ʱ����
function x300185_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300185_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300185_g_BuffId)
	end
end

--��Чʱ����
function x300185_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300185_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300185_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300185_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300185_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300185_ProcEventEntry( sceneId, selfId, bagIndex)
end


