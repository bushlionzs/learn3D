--MisDescBegin 
x300937_g_ScriptId 					= 	300937
x300937_g_MissionName				= 	"【领地介绍】" 
x300937_g_MissionInfo				= 	"【领地争夺战说明】" 
--MisDescEnd

function x300937_ProcEnumEvent( sceneId, selfId, targetId )
end

function x300937_ProcEventEntry(sceneId, selfId,targetId)	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId)
		local Readme_1 = "#Y【领地争夺战规则】#r #r#W"
		local Readme_2  = "1、领地争夺战将于#G每周六16点开启#W，#G17点结束#W。#r"
		local Readme_3  = "2、在每周六16：00-17：00期间，与报名帮会国籍相同的成员击杀领地内的领地图腾，则该报名帮会暂时成为领地占领者，同时需要保护领地图腾不被其他国家国民击杀。#r"
		local Readme_4  = "3、#G在领地争夺战结束前#W，如果有其它报名帮会同国籍的国民击杀领地图腾，则领地占领者变更。#r"
		local Readme_5  = "4、#G到达领地争夺战结束时间时#W，击杀领地图腾并且成功保护住已占领的领地图腾的帮会获得该领地的拥有权。#r"
		local Readme_6  = "5、在领地图腾附近不可以使用帮会召集令，队伍召集令和神行符。#r#r"
		local Readme_7  = "6、领地图腾每10分钟会回复总血量的5%，若领地争夺结束时，没有帮会击杀领地图腾，则该领地为非占领状态。#r"
		local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5..Readme_6..Readme_7
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestInfo( sceneId, selfId, targetId, x300937_g_ScriptId, -1 );
end 

function x300937_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x300937_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x300937_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x300937_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x300937_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x300937_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300937_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x300937_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x300937_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end