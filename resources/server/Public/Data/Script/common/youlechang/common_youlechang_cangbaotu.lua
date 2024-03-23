x310334_g_scriptId = 310334 
x310334_g_only =0
x310334_g_SelfPos				=	{ }
x310334_g_Item1Tab = 	{
							{item = 11000202, count = 20, },
							{item = 11050003, count = 20, },
							{item = 11030501, count = 20, },
							{item = 11030405, count = 20, },
							{
								{ item = 12030254, count = 3, },
								{ item = 12030255, count = 3, },
								{ item = 12030256, count = 3, },
							}
						} 
x310334_g_Item2Tab = 	{
							{item = 11000501, count = 5, },
							{item = 12041103, count = 5, },
							{item = 11000902, count = 1, },
							{item = 19010003, count = 1, },
							{item = 12041110, count = 3, },
							{item = 12041111, count = 3, },
							{item = 12041112, count = 3, },
							{item = 11990015, count = 4, },
						} 
x310334_g_Item3Tab = 	{
							{item = 12030511, count = 1, },
							{item = 12030512, count = 1, },
						}
							
x310334_g_Place = {
									{x= 81  ,y= 209 },
									{x= 44  ,y= 185 },
									{x= 94  ,y= 154 },
									{x= 52  ,y= 145 },
									{x= 52  ,y= 113 },
									{x= 32  ,y= 134 },
									{x= 40  ,y= 48 },
									{x= 56  ,y= 30 },
									{x= 46  ,y= 83 },
									{x= 62  ,y= 37 },
									{x= 172 ,y= 71 },
									{x= 143 ,y= 70 },
									{x= 202 ,y= 110 },
									{x= 208 ,y= 120 },
									{x= 142 ,y= 231 },
									{x= 107 ,y= 167 },
									{x= 114 ,y= 185 },
									{x= 205 ,y= 171 },
									{x= 190 ,y= 62 },
									{x= 115 ,y= 204 },
									}

function x310334_AddItem( sceneId, selfId, itemId, count, bBind )
	BeginAddItem( sceneId )
	if bBind == 0 then
		AddBindItem( sceneId, itemId, count )
	else
		AddItem( sceneId, itemId, count )
	end
	local ret = EndAddItem( sceneId, selfId )
	if ret > 0 then
		AddItemListToPlayer(sceneId,selfId)
		BeginQuestEvent(sceneId)
		local msg = format( "������%d��@item_%d��",count,itemId)
		AddQuestText(sceneId,msg)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		local name = GetName(sceneId,selfId)
		if name == nil then
			name = "Errorname"
		end
		if itemId == x310334_g_Item3Tab[1].item then --ȫ���㲥
			local msg = format(name.."�������˼�Ѱ�����%d��#G�����ƣ���������7�죩���",x310334_g_Item3Tab[1].count)
			LuaAllScenceM2Wrold (sceneId,msg, 5, 1)
		elseif itemId == x310334_g_Item3Tab[2].item then --ȫ���㲥
			local msg = format(name.."�������˼�Ѱ�����%d��#G�����ƣ���һɫ��7�죩���",x310334_g_Item3Tab[2].count)
			LuaAllScenceM2Wrold (sceneId,msg, 5, 1)
		end
		return 1
	else
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"��������������������")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return 0
	end	
end
	
function x310334_ProcEventEntry( sceneId, selfId, BagIndex )
	local bBind = 0
	if IsHaveSpecificImpact( sceneId, selfId, 9011) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9012) == 1 or IsHaveSpecificImpact( sceneId, selfId, 9013) == 1 then
		bBind = 1
	end

	local size = getn( x310334_g_Place)
	local guid = GetPlayerGUID( sceneId,selfId )
	local index = 1
	if x310334_g_SelfPos[guid] == nil then
		index = random( 1, size)
 	else
		index = x310334_g_SelfPos[guid] 
		if index < 1 or index > size then
			index = random( 1, size)
		end 
	end
	
	x310334_g_SelfPos[guid] = index
	--local index = random( 1, size)
	--if x310334_g_only ==0 then
		--x310334_g_only = random( 1, size)
	--end
	
	local posx =x310334_g_Place[index].x
	local posy =x310334_g_Place[index].y
	local x1,y1 = GetWorldPos( sceneId, selfId )
	local nDistance = (x1-posx)*(x1-posx) +(y1-posy)*(y1-posy)
	if nDistance >=5*5 or sceneId~=39 then
		x300334_ShowTips(sceneId, selfId, format("Ѱ��ͼ��ʾ�������������˼䡤����#G��%d,%d��#cffcf00����",posx,posy))
		return
	end		
	
	if GetBagSpace(sceneId, selfId) <= 0 then
		Msg2Player(sceneId, selfId, "�����������޷�ʹ�ô�Ѱ��ͼ", 0, 2)
		Msg2Player(sceneId, selfId, "�����������޷�ʹ�ô�Ѱ��ͼ", 0, 3)
		return
	end
	
	local rand = random(1, 100)
	local level = GetLevel(sceneId, selfId)
	local ret = 1
	if rand <= 10 then		
		ret = x310334_AddItem( sceneId, selfId, 12035000, 1, bBind )
	elseif rand > 10 and rand <= 17 then
		ret = x310334_AddItem( sceneId, selfId, 12035001, 1, bBind )	
	elseif rand > 17 and rand <= 20 then
		ret = x310334_AddItem( sceneId, selfId, 12035002, 1, bBind )	
	elseif rand > 20 and rand <= 79 then --ˮ����id��11000202��*20������ʯ��id��11050003��*20���ܻ�ʯ��id��11030501��*20����ľ������id��11020501��*20���߲��ߣ�id��11030405��*20���±���<70��-id��12030254��70<=level<80��:12030255 ��>=80����12030256��*3
		local num = getn(x310334_g_Item1Tab)
		local rate = random(1,num)
		if rate < num then
			ret = x310334_AddItem( sceneId, selfId, x310334_g_Item1Tab[rate].item, x310334_g_Item1Tab[rate].count, bBind )
		else
			if level < 70 then
				ret = x310334_AddItem( sceneId, selfId, x310334_g_Item1Tab[num][1].item, x310334_g_Item1Tab[num][1].count, bBind )
			elseif level < 80 then
				ret = x310334_AddItem( sceneId, selfId, x310334_g_Item1Tab[num][2].item, x310334_g_Item1Tab[num][2].count, bBind )
			else
				ret = x310334_AddItem( sceneId, selfId, x310334_g_Item1Tab[num][3].item, x310334_g_Item1Tab[num][3].count, bBind )
			end
		end
	elseif rand >79 and rand <= 99 then
		local num = getn(x310334_g_Item2Tab)
		local rate = random(1,num)
		ret = x310334_AddItem( sceneId, selfId, x310334_g_Item2Tab[rate].item, x310334_g_Item2Tab[rate].count, bBind )
		
	elseif rand == 100 then
		local num = getn(x310334_g_Item3Tab)
		local rate = random(1,num)
		ret = x310334_AddItem( sceneId, selfId, x310334_g_Item3Tab[rate].item, x310334_g_Item3Tab[rate].count, bBind )
		
			
	end
	
	if ret == 0 then
		return
	end
	
	DelItemByIndexInBag( sceneId, selfId, BagIndex, 1)
	--DelItem( sceneId, selfId, 12035015, 1); --ɾ����Ʒ
	x310334_g_SelfPos[guid] = nil

end

function x310334_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x310334_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x310334_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310334_OnDeplete( sceneId, selfId )

	return 0
end

function x310334_OnActivateOnce( sceneId, selfId )
end

function x310334_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end


function x300334_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end