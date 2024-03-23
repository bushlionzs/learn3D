
x601003_g_ScriptId = 601003
x601003_g_Exp	=	8000;

--间隔发作时调用
function x601003_OnIntervalOverEvent( sceneId, selfId )
end

--生效时调用
function x601003_OnActiveEvent( sceneId, selfId )
	AddExp(sceneId, selfId, x601003_g_Exp);
	hf_DisplayAwardInfo(sceneId, selfId, -1, -1, -1, -1, 0, x601003_g_Exp, -1, 0);
end

--效果消散时调用
function x601003_OnFadeOutEvent( sceneId, selfId )
end