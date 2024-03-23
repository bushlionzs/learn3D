
x310055_g_ScritpId  =  310055

x310055_g_UICommandID = 100
x310055_g_MissionName = "天龙魂兑换"
x310055_g_ContinueInfo="\t#W您有#R%d#W个@item_%d#W，可以兑换成#R%d#W个@item_%d#W，要进行兑换吗？"
x310055_g_ItemId_src = 12030026
x310055_g_ItemId_target  = 12030108

--------------------------------------------------------------------------------
--列举
--------------------------------------------------------------------------------
function x310055_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x310055_g_ScritpId, x310055_g_MissionName,3);
end

--------------------------------------------------------------------------------
--选中
--------------------------------------------------------------------------------
function x310055_ProcEventEntry( sceneId, selfId, targetId, MissionId )

	local nSrcItemCount = GetItemCountInBag( sceneId, selfId, x310055_g_ItemId_src)
	local nTargetItemCount = nSrcItemCount
	
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"#Y"..x310055_g_MissionName)
		AddQuestText(sceneId,format(x310055_g_ContinueInfo,nSrcItemCount,x310055_g_ItemId_src,nTargetItemCount,x310055_g_ItemId_target))
	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, targetId, x310055_g_ScritpId, -1)

end


--------------------------------------------------------------------------------
--接收检查
--------------------------------------------------------------------------------
function x310055_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

--------------------------------------------------------------------------------
--接收
--------------------------------------------------------------------------------
function x310055_ProcAccept(sceneId, selfId, targetId)

	local nSrcItemCount = GetItemCountInBag( sceneId, selfId, x310055_g_ItemId_src)	
	local nTargetItemCount = nSrcItemCount
	
	if nSrcItemCount > 0 then	
	
		local Ret = DelItemByIDInBag(sceneId,selfId,x310055_g_ItemId_src,nSrcItemCount)
		if Ret <= 0 then
 			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,format("#cffcf0删除%d个@item_%d失败",nSrcItemCount,x310055_g_ItemId_src))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
            return
		end

		BeginAddItem(sceneId)
			AddItem( sceneId, x310055_g_ItemId_target, nTargetItemCount )
		Ret = EndAddItem(sceneId,selfId)
		if Ret > 0 then
			AddItemListToPlayer(sceneId,selfId)
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,format("#cffcf00恭喜您，成功兑换了%d个@item_%d",nTargetItemCount,x310055_g_ItemId_target))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else			
			--回退
			BeginAddItem(sceneId)
				AddItem( sceneId, x310055_g_ItemId_src, nSrcItemCount )
			EndAddItem(sceneId,selfId)
					
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,format("#cffcf00抱歉，兑换%d个@item_%d失败",nTargetItemCount,x310055_g_ItemId_target))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			

		end
	else
        Msg2Player(sceneId, selfId, "您的背包中没有沉寂的天龙魂，无法兑换", 0, 2)
		Msg2Player(sceneId, selfId, "您的背包中没有沉寂的天龙魂，无法兑换", 0, 3)	
	end
	    
end

--function x310055_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
--end
--------------------------------------------------------------------------------
--放弃
--------------------------------------------------------------------------------
--function x310055_ProcQuestAbandon(sceneId, selfId, MissionId)
--end

--------------------------------------------------------------------------------
--提交检查
--------------------------------------------------------------------------------
--function x310055_CheckSubmit( sceneId, selfId, NPCId)
--end

--------------------------------------------------------------------------------
--提交
--------------------------------------------------------------------------------
--function x310055_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
--end
