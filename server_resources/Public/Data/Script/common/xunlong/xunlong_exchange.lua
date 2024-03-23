
x310055_g_ScritpId  =  310055

x310055_g_UICommandID = 100
x310055_g_MissionName = "������һ�"
x310055_g_ContinueInfo="\t#W����#R%d#W��@item_%d#W�����Զһ���#R%d#W��@item_%d#W��Ҫ���жһ���"
x310055_g_ItemId_src = 12030026
x310055_g_ItemId_target  = 12030108

--------------------------------------------------------------------------------
--�о�
--------------------------------------------------------------------------------
function x310055_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x310055_g_ScritpId, x310055_g_MissionName,3);
end

--------------------------------------------------------------------------------
--ѡ��
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
--���ռ��
--------------------------------------------------------------------------------
function x310055_ProcAcceptCheck(sceneId, selfId, NPCId)
	return 1
end

--------------------------------------------------------------------------------
--����
--------------------------------------------------------------------------------
function x310055_ProcAccept(sceneId, selfId, targetId)

	local nSrcItemCount = GetItemCountInBag( sceneId, selfId, x310055_g_ItemId_src)	
	local nTargetItemCount = nSrcItemCount
	
	if nSrcItemCount > 0 then	
	
		local Ret = DelItemByIDInBag(sceneId,selfId,x310055_g_ItemId_src,nSrcItemCount)
		if Ret <= 0 then
 			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,format("#cffcf0ɾ��%d��@item_%dʧ��",nSrcItemCount,x310055_g_ItemId_src))
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
				AddQuestText(sceneId,format("#cffcf00��ϲ�����ɹ��һ���%d��@item_%d",nTargetItemCount,x310055_g_ItemId_target))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else			
			--����
			BeginAddItem(sceneId)
				AddItem( sceneId, x310055_g_ItemId_src, nSrcItemCount )
			EndAddItem(sceneId,selfId)
					
			BeginQuestEvent(sceneId)
				AddQuestText(sceneId,format("#cffcf00��Ǹ���һ�%d��@item_%dʧ��",nTargetItemCount,x310055_g_ItemId_target))
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
			

		end
	else
        Msg2Player(sceneId, selfId, "���ı�����û�г��ŵ������꣬�޷��һ�", 0, 2)
		Msg2Player(sceneId, selfId, "���ı�����û�г��ŵ������꣬�޷��һ�", 0, 3)	
	end
	    
end

--function x310055_ProcQuestAccept(sceneId, selfId, targetId, MissionId)
--end
--------------------------------------------------------------------------------
--����
--------------------------------------------------------------------------------
--function x310055_ProcQuestAbandon(sceneId, selfId, MissionId)
--end

--------------------------------------------------------------------------------
--�ύ���
--------------------------------------------------------------------------------
--function x310055_CheckSubmit( sceneId, selfId, NPCId)
--end

--------------------------------------------------------------------------------
--�ύ
--------------------------------------------------------------------------------
--function x310055_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)
--end
