-------------------------------------------------
-- 祝家庄2 npc对话： 五行对话(2)
-------------------------------------------------

x700047_CSP_B_BOSS2		=	36

x700047_g_ScriptId = 700047


x700047_Fuben_ScriptId = 700031

x700047_g_TalkTitle = "木曰曲直"
x700047_g_TalkContent = "\t 此木屈伸有度，似乎内有灵气游动，不知打开会有什么东西出现。看来这就是扈三娘的五行异术的“木”。"

function x700047_ProcEventEntry(sceneId, selfId, NPCId, MissionId,which)	--点击该任务后执行此脚本
	
	
	x700047_DispatchTalkInfo( sceneId, selfId, NPCId,which )
	
end


--**********************************

--列举事件

--**********************************

function x700047_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
	
	local bCreatMonster2 = GetFubenData_Param(sceneId, x700047_CSP_B_BOSS2 ) ;


	if bCreatMonster2<=0 then
	
		AddQuestNumText(sceneId, x700047_g_ScriptId, x700047_g_TalkTitle,3,1)
	end
			
end



function x700047_DispatchTalkInfo( sceneId, selfId, NPCId, nParam )

	BeginQuestEvent(sceneId)

		--任务信息
		AddQuestText(sceneId,"#Y"..x700047_g_TalkTitle)
		AddQuestText(sceneId,x700047_g_TalkContent)
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700047_g_ScriptId, -1);
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700047_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700047_ProcAccept( sceneId, selfId )

	
	CallScriptFunction( x700047_Fuben_ScriptId, "OnNpcTalk3", sceneId, selfId) ;
	
end

