
x300174_g_ScriptId = 300174
x300174_g_FarScriptId = 300160
x300174_g_BuffId = 7645

--�������ʱ����
function x300174_OnIntervalOverEvent( sceneId, selfId)
	if sceneId == 14 then
		CallScriptFunction(x300174_g_FarScriptId, "OnIntervalOverEvent", sceneId, selfId, x300174_g_BuffId)
	end
end

--��Чʱ����
function x300174_OnActiveEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300174_g_FarScriptId, "OnActiveEvent", sceneId, selfId)
	end
end

--Ч����ɢʱ����
function x300174_OnFadeOutEvent( sceneId, selfId )
	if sceneId == 14 then
		CallScriptFunction(x300174_g_FarScriptId, "OnFadeOutEvent", sceneId, selfId, x300174_g_BuffId)
	end
end

--**********************************
--�¼��������
--**********************************
function x300174_ProcEventEntry( sceneId, selfId, bagIndex)
end


