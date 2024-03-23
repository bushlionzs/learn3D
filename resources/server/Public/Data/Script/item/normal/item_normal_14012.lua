--脚本号
x414012_g_scriptId = 414012 --临时写这个,真正用的时候一定要改.
x414012_g_keyID = 12101001 --临时写这个,真正用的时候一定要改.
x414012_g_keyname = "符文钥匙" --临时写这个,真正用的时候一定要改.


--需要的等级

--**********************************
--事件交互入口
--**********************************
function x414012_ProcEventEntry( sceneId, selfId, bagIndex )
	local HaveKey = HaveItemInBag(sceneId,selfId,x414012_g_keyID)
	
	if HaveKey > 0 then
		OpenRndomBox ( sceneId, selfId, 13, 13, 5, 13, 5, 13, 5, 13, 3, 13, 2) 
		DelItem(sceneId,selfId,x414012_g_keyID,1)
		EraseItem(sceneId,selfId,bagIndex)
		BeginQuestEvent(sceneId)
			local strText = "#Y你使用一把"..x414012_g_keyname.."，开启了一个宝箱"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		BeginQuestEvent(sceneId)
			local strText = "#Y开启宝箱，需要"..x414012_g_keyname.."一把"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	end
end

--**********************************
--这个物品的使用过程是否类似于技能：
--系统会在执行开始时检测这个函数的返回值，如果返回失败则忽略后面的类似技能的执行。
--返回1：技能类似的物品，可以继续类似技能的执行；返回0：忽略后面的操作。
--**********************************
function x414012_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持
end
