--MisDescBegin 
x300936_g_ScriptId 					= 	300936
x300936_g_MissionName				= 	"【领地介绍】" 
x300936_g_MissionInfo				= 	"【领地争夺战说明】" 
--MisDescEnd

function x300936_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300936_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【报名条件】#r #r#W"
		local Readme_2   = "1、本国有国王的情况下，才可报名。#r2、您必须是帮主#r3、#G周六13点到15点#W才可报名。#r4、每个领地#G最多#W可以有#G2个帮会报名争夺#W，报名时帮会实力高的帮会将顶替帮会实力低的帮会获得报名资格，同一块领地每个国家只能有一个帮会参加报名。#r "
		local Readme_3   = "5、国王、王国守护、已占领领地的帮主，无法报名。#r"
		local Readme = Readme_1..Readme_2..Readme_3
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300936_g_ScriptId, -1 );
end 

function x300936_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300936_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300936_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300936_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300936_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300936_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300936_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300936_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300936_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end