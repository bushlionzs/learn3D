--注意：

--物品技能的逻辑只能使用基础技能和脚本来实现

--脚本:

--以下是脚本样例:


--3001.lua
------------------------------------------------------------------------------------------
--一般物品的默认脚本



--效果的ID
x417004_g_Impact1 = 7043
x417004_g_Impact_OK			=	7058
x417004_g_Impact_Failed	=	7059

--**********************************
--事件交互入口
--**********************************
function x417004_ProcEventEntry( sceneId, selfId, bagIndex,rorf )
	if rorf == 1 then
		local str
		local multExp = GetWanFaExpMult( sceneId, selfId )
	--检查有没有指定的buff,如果有，增加多倍经验，否则减少多倍经验
		if IsHaveSpecificImpact( sceneId, selfId, x417004_g_Impact1 ) > 0 then
			multExp = multExp - 0.1
			if multExp < 1.0 then multExp = 1.0 end
			str = "你被雷击中了！"
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x417004_g_Impact_Failed, 0)
		else
			multExp = multExp + 0.03
			str = "你成功躲避了雷击！"
			
			local bonusExp = floor(GetLevel( sceneId, selfId ) * 80 * multExp)
			AddExp( sceneId,selfId, bonusExp )
			str = str.."获得经验："..bonusExp
			SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x417004_g_Impact_OK, 0)
		end
		SetWanFaExpMult(  sceneId, selfId,  multExp )
		
		str = str.."当前经验倍率："..format("%.2f", multExp)

		BeginQuestEvent( sceneId )
		AddQuestText( sceneId, str )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId )
	end
end


