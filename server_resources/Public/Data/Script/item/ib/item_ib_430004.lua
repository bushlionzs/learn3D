--小喇叭扣除道具

--返回值说明：如果扣除失败 0 ，否则 1
------------------------------------------------------------------------------------------
--事件交互入口
--**********************************
function x430004_OnChatDeplete( sceneId, selfId, bChatType, bagIndex )
	local iMultTimes = IsBagItemMultTimes( sceneId, selfId, bagIndex )
	if iMultTimes <= 0 then
		return 0;
	end

	local itimes = GetBagItemMultTimes( sceneId, selfId, bagIndex );
	itimes = itimes - 1;
	if itimes <= 0 then
		--删除道具
		EraseItem( sceneId, selfId, bagIndex );
	else
		--减次
		SetBagItemMultTimes( sceneId, selfId, bagIndex, itimes );
	end
	return 1;
end
