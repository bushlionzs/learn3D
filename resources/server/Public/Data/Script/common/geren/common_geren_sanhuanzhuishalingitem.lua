
x270356_g_scriptId = 270356

x270356_g_MissionScriptTab 		= 	{ 270350,270351,270352,270353}		--四个国家的任务脚本号

function x270356_ProcEventEntry( sceneId, selfId, bagIndex )
	print("x270356_ProcEventEntry")
	local nCountryId = GetCurCountry(sceneId,selfId )
	local bCplay =  CallScriptFunction( x270356_g_MissionScriptTab[nCountryId+1], "DenoteMonsterPosition", sceneId, selfId, bagIndex )
end

function x270356_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑

 end

function x270356_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
 
end

function x270356_OnConditionCheck( sceneId, selfId )
	return 0
end

function x270356_OnDeplete( sceneId, selfId )
	return 0
end

function x270356_OnActivateOnce( sceneId, selfId )
	print("x270356_OnActivateOnce")
end

function x270356_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end
