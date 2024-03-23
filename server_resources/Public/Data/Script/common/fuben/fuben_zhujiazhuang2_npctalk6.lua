-------------------------------------------------
-- 祝家庄2 npc对话： 五行对话(5)
-------------------------------------------------

x700050_CSP_B_BOSS5		=	39

x700050_g_ScriptId = 700050


x700050_Fuben_ScriptId = 700031

x700050_g_TalkTitle = "土爰稼穑"
x700050_g_TalkContent = "\t 此物厚重无华，似乎内有灵气游动，不知打开会有什么东西出现。看来这就是扈三娘的五行异术的“土”。"

function x700050_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	
	
	x700050_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--列举事件

--**********************************

function x700050_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700050_CSP_B_BOSS5 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700050_g_ScriptId, x700050_g_TalkTitle,3,1)
	end
			
end



function x700050_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x700050_g_TalkTitle)
		AddQuestText(sceneId,x700050_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700050_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700050_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700050_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700050_Fuben_ScriptId, "OnNpcTalk6", sceneId, selfId) ;
	
end

