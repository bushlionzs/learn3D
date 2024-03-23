
x601002_g_ScriptId = 601002
x601002_g_Exp	=	5000;

--间隔发作时调用
function x601002_OnIntervalOverEvent( sceneId, selfId )
end

--生效时调用
function x601002_OnActiveEvent( sceneId, selfId )
	AddExp(sceneId, selfId, x601002_g_Exp);
	hf_DisplayAwardInfo(sceneId, selfId, -1, -1, -1, -1, 0, x601002_g_Exp, -1, 0);
end

--效果消散时调用
function x601002_OnFadeOutEvent( sceneId, selfId )
end