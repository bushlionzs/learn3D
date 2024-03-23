
x601001_g_ScriptId = 601001
x601001_g_Exp	=	3000;

--间隔发作时调用
function x601001_OnIntervalOverEvent( sceneId, selfId )
end

--生效时调用
function x601001_OnActiveEvent( sceneId, selfId )
	AddExp(sceneId, selfId, x601001_g_Exp);
	hf_DisplayAwardInfo(sceneId, selfId, -1, -1, -1, -1, 0, x601001_g_Exp, -1, 0);
end

--效果消散时调用
function x601001_OnFadeOutEvent( sceneId, selfId )
end