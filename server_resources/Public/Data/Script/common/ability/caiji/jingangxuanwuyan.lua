--������

x540111_g_GrowpointId = 611 --��Ӧ������ID

x540111_g_AbilitySkillName = "�ɼ���ʯ" --��Ҫ�����������
x540111_g_AbilitySkillType = 12 --��Ҫ�������ID
x540111_g_AbilitySkillLevel = 7 --��Ҫ�������ID�ĵȼ�
--x540111_g_AbilitySkillLimit = 0 --��Ҫ�������ID��������
x540111_g_AddSkillLimit = 1 --�ɼ��ɹ���õ������ȵ���
x540111_g_SkillLMax_1 =150 --����1��ʱ����������
x540111_g_SkillLMax_2 =200 --����2��ʱ����������
x540111_g_SkillLMax_3 =250 --����3��ʱ����������
x540111_g_SkillLMax_4 =300	--����4��ʱ����������
x540111_g_SkillLMax_5 =350 --����5��ʱ����������
x540111_g_SkillLMax_6 =400 --����6��ʱ����������
x540111_g_SkillLMax_7 =450 --����7��ʱ����������
x540111_g_SkillLMax_8 =500 --����8��ʱ����������
x540111_g_SkillLMax = 0 --ʵ�ʵ�ǰ����������

x540111_g_CostVigorLow = 6		--�ɼ�����Ϊ��Ҫ����͵ȼ�ʱ�ɼ��ɹ�һ��ʱ�۳��Ļ�������
x540111_g_CostVigorHigh = 7   --�ɼ����ܴ�����Ҫ����͵ȼ�ʱ�ɼ��ɹ�һ��ʱ�۳��Ļ�������
x540111_g_CostVigor = 0       --ʵ�ʿ۳��Ļ�������

x540111_g_ItemNumLow = 1 --�չ���ʱ��ø����������п����Զ���һ����Ʒ
x540111_g_ItemNumHigh = 3 --��һ��ʱ��ø����������п����Զ���һ����Ʒ
x540111_g_ItemNumOver = 4 --����������ʱ��ø���������û�п��ܶ�����Ʒ
x540111_g_ItemNum = 0  --ʵ�ʻ�õ���Ʒ����

x540111_g_ItemIndex = 11030007 --��Ӧ�ռ���Ʒ��ID
x540111_g_ItemName = "ʥͽ����ʯ" 	--��Ӧ�ռ���Ʒ������
x540111_g_DoubleItemLow = 900 --��<��ǰ������>/300�Ŀ����Զ���һ����Ʒ
x540111_g_DoubleItemHigh = 1000 --��<��ǰ������>/400�Ŀ����Զ���һ����Ʒ

x540111_g_SpecialItemSkillLevel = 7   --���Բɼ���������Ʒ���������ܵȼ���-1��ʾʼ�ղɼ�����������Ʒ
x540111_g_SpecialItemLowPencent = 10 --ÿ�βɼ���������Ʒ�ĸ��ʣ�-1��ʾ��,���100
x540111_g_SpecialItemHighPencent = 10  --���100
x540111_g_SpecialItemIndex = 11030501 --ÿ�βɼ���������Ʒ��ID��-1��ʾ��,>0Ϊ��Ч��ֵ
x540111_g_SpecialItemName = "�ܻ�ʯ"  --ÿ�βɼ���������Ʒ�����ƣ��ձ�ʾ��
x540111_g_SpecialItemNum = 0 --ʵ�ʻ�õ�������Ʒ����





--���ɺ�����ʼ************************************************************************
function 	x540111_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x540111_g_GrowpointId, sceneId, 0, x540111_g_ItemIndex)
end
--���ɺ�������**********************************************************************


--��ǰ������ʼ&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x540111_OnOpen(sceneId,selfId,targetId)
	--SetPlayerVigor(sceneId,selfId,140)

	local SkillLevel = QueryPlayerAbilityLevel(sceneId,selfId ,x540111_g_AbilitySkillType)
	local SkillBaseLimit= GetAbilityExp(sceneId, selfId, x540111_g_AbilitySkillType)
	local SkillLimit = SkillBaseLimit + QueryItemAffAbility(sceneId,selfId)
	if SkillLevel == nil then
		TipsToPlayer(sceneId,selfId,"#Y�㻹û��ѧϰ#R"..x540111_g_AbilitySkillName)
	else
		if SkillLevel <= 0 then
			TipsToPlayer(sceneId,selfId,"#Y�㻹û��ѧϰ#R"..x540111_g_AbilitySkillName)
		else
			if SkillLevel >= x540111_g_AbilitySkillLevel then
				if SkillLevel == x540111_g_AbilitySkillLevel then
					x540111_g_CostVigor = x540111_g_CostVigorLow
				else
					x540111_g_CostVigor = x540111_g_CostVigorHigh
				end
				if GetPlayerVigor(sceneId,selfId) >=x540111_g_CostVigor then
					return 0
				else
					TipsToPlayer(sceneId,selfId,"#Y��������")
				end
			else
				TipsToPlayer(sceneId,selfId,"#Y"..x540111_g_AbilitySkillName.." �ȼ�����#R"..x540111_g_AbilitySkillLevel.."��")
			end
		end
	end
	return 1
end

--��ǰ��������&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--���պ�����ʼ########################################################################
function	 x540111_OnRecycle(sceneId,selfId,targetId)
   	local SkillLevel = QueryPlayerAbilityLevel(sceneId,selfId ,x540111_g_AbilitySkillType)
	local SkillBaseLimit= GetAbilityExp(sceneId, selfId, x540111_g_AbilitySkillType)
	local SkillLimit = SkillBaseLimit + QueryItemAffAbility(sceneId,selfId)
	if SkillLevel == nil then
		TipsToPlayer(sceneId,selfId,"#Y�㻹û��ѧϰ#R"..x540111_g_AbilitySkillName)
	else
		if SkillLevel <= 0 then
			TipsToPlayer(sceneId,selfId,"#Y�㻹û��ѧϰ#R"..x540111_g_AbilitySkillName)
		else
			if SkillLevel >= x540111_g_AbilitySkillLevel then
				local NowVigor = GetPlayerVigor(sceneId,selfId)
				if SkillLevel == x540111_g_AbilitySkillLevel then
					x540111_g_CostVigor = x540111_g_CostVigorLow
				else
					x540111_g_CostVigor = x540111_g_CostVigorHigh
				end
				if NowVigor >= x540111_g_CostVigor then
					BeginAddItem( sceneId )
						if SkillLevel >= x540111_g_AbilitySkillLevel + 2 then
							x540111_g_ItemNum = x540111_g_ItemNumOver 
						elseif SkillLevel >= x540111_g_AbilitySkillLevel + 1 then
							local x =random(1,x540111_g_DoubleItemHigh)
							if x <=  SkillLimit then
								x = 1
							else
								x = 0
							end
							x540111_g_ItemNum = x540111_g_ItemNumHigh + x 
						else
							local x =random(1,x540111_g_DoubleItemLow)
							if x <=  SkillLimit then
								x = 1
							else
								x = 0
							end
							x540111_g_ItemNum =x540111_g_ItemNumLow + x 
						end
						AddItem( sceneId, x540111_g_ItemIndex, x540111_g_ItemNum)
						if  SkillLevel == x540111_g_SpecialItemSkillLevel and x540111_g_SpecialItemSkillLevel > 0 then
							if random(1,100) <= x540111_g_SpecialItemLowPencent and x540111_g_SpecialItemIndex > 0 then
								x540111_g_SpecialItemNum = 1
								AddItem( sceneId, x540111_g_SpecialItemIndex, x540111_g_SpecialItemNum )	
							else
								x540111_g_SpecialItemNum = 0
							end
						elseif SkillLevel > x540111_g_SpecialItemSkillLevel and x540111_g_SpecialItemSkillLevel > 0 then
							if random(1,100) <= x540111_g_SpecialItemHighPencent and x540111_g_SpecialItemIndex > 0 then
								x540111_g_SpecialItemNum = 1
								AddItem( sceneId, x540111_g_SpecialItemIndex, x540111_g_SpecialItemNum )	
							else
								x540111_g_SpecialItemNum = 0
							end
						else	
							x540111_g_SpecialItemNum = 0
						end
					if SkillLevel == 1 then 
						x540111_g_SkillLMax = x540111_g_SkillLMax_1
					elseif SkillLevel == 2 then 
						x540111_g_SkillLMax = x540111_g_SkillLMax_2
					elseif SkillLevel == 3 then 
						x540111_g_SkillLMax = x540111_g_SkillLMax_3
					elseif SkillLevel == 4 then 
						x540111_g_SkillLMax = x540111_g_SkillLMax_4
					elseif SkillLevel == 5 then 
						x540111_g_SkillLMax = x540111_g_SkillLMax_5
					elseif SkillLevel == 6 then 
						x540111_g_SkillLMax = x540111_g_SkillLMax_6
					elseif SkillLevel == 7 then 
						x540111_g_SkillLMax = x540111_g_SkillLMax_7
					elseif SkillLevel == 8 then 
						x540111_g_SkillLMax = x540111_g_SkillLMax_8
					end
					local ret = EndAddItem( sceneId, selfId )
					if ret > 0 then
						AddItemListToPlayer(sceneId,selfId)
						if x540111_g_SpecialItemIndex > 0 and x540111_g_SpecialItemNum > 0 then
							TipsToPlayer (sceneId,selfId,"#Y���#G"..x540111_g_ItemNum.."��#Y"..x540111_g_ItemName.."��#G"..x540111_g_SpecialItemNum.."��#Y"..x540111_g_SpecialItemName)
						else
							TipsToPlayer (sceneId,selfId,"#Y���#G"..x540111_g_ItemNum.."��#Y"..x540111_g_ItemName)
						end
						TipsToPlayer (sceneId,selfId,"#Y����#G"..x540111_g_CostVigor.."��#Y����")
						if SkillLevel < x540111_g_AbilitySkillLevel + 2 then
							if SkillLevel > 8 then 
								SetAbilityExp(sceneId,selfId,x540111_g_AbilitySkillType,SkillBaseLimit + x540111_g_AddSkillLimit)
								TipsToPlayer (sceneId,selfId,"#Y"..x540111_g_AbilitySkillName.."���#G"..x540111_g_AddSkillLimit.."��#Y������")
							elseif SkillLevel > 0 and SkillLevel <= 8 then
								if SkillBaseLimit + x540111_g_AddSkillLimit <= x540111_g_SkillLMax then 
									SetAbilityExp(sceneId,selfId,x540111_g_AbilitySkillType,SkillBaseLimit + x540111_g_AddSkillLimit)
									TipsToPlayer (sceneId,selfId,"#Y"..x540111_g_AbilitySkillName.."���#G"..x540111_g_AddSkillLimit.."��#Y������")
								elseif SkillBaseLimit + x540111_g_AddSkillLimit > x540111_g_SkillLMax and SkillBaseLimit < x540111_g_SkillLMax then
									SetAbilityExp(sceneId,selfId,x540111_g_AbilitySkillType,x540111_g_SkillLMax)
									TipsToPlayer (sceneId,selfId,"#Y"..x540111_g_AbilitySkillName.."���#G"..x540111_g_SkillLMax-SkillBaseLimit.."��#Y������")
								else
									TipsToPlayer (sceneId,selfId,"�������Ѵ�����")
								end
							end
						end
						SetPlayerVigor(sceneId,selfId, NowVigor - x540111_g_CostVigor)
						return 1
					else
						BeginAddItem( sceneId )
						if SkillLevel >= x540111_g_AbilitySkillLevel + 2 then
							x540111_g_ItemNum = x540111_g_ItemNumOver 
						elseif SkillLevel >= x540111_g_AbilitySkillLevel + 1 then
							local x =random(1,x540111_g_DoubleItemHigh)
							if x <=  SkillLimit then
								x = 1
							else
								x = 0
							end
							x540111_g_ItemNum = x540111_g_ItemNumHigh + x 
						else
							local x =random(1,x540111_g_DoubleItemLow)
							if x <=  SkillLimit then
								x = 1
							else
								x = 0
							end
							x540111_g_ItemNum =x540111_g_ItemNumLow + x 
						end
						AddItem( sceneId, x540111_g_ItemIndex, x540111_g_ItemNum)
						local ret = EndAddItem( sceneId, selfId )
						if ret > 0 then
							AddItemListToPlayer(sceneId,selfId)
							TipsToPlayer (sceneId,selfId,"#Y���#G"..x540111_g_ItemNum.."��#Y"..x540111_g_ItemName)
							TipsToPlayer (sceneId,selfId,"���ڱ����ռ�����,û�еõ����⸽����Ʒ")
							TipsToPlayer (sceneId,selfId,"#Y����#G"..x540111_g_CostVigor.."��#Y����")
							if SkillLevel < x540111_g_AbilitySkillLevel + 2 then
								if SkillLevel > 8 then 
									SetAbilityExp(sceneId,selfId,x540111_g_AbilitySkillType,SkillBaseLimit + x540111_g_AddSkillLimit)
									TipsToPlayer (sceneId,selfId,"#Y"..x540111_g_AbilitySkillName.."���#G"..x540111_g_AddSkillLimit.."��#Y������")
								elseif SkillLevel > 0 and SkillLevel <= 8 then
									if SkillBaseLimit + x540111_g_AddSkillLimit <= x540111_g_SkillLMax then 
										SetAbilityExp(sceneId,selfId,x540111_g_AbilitySkillType,SkillBaseLimit + x540111_g_AddSkillLimit)
										TipsToPlayer (sceneId,selfId,"#Y"..x540111_g_AbilitySkillName.."���#G"..x540111_g_AddSkillLimit.."��#Y������")
									elseif SkillBaseLimit + x540111_g_AddSkillLimit > x540111_g_SkillLMax and SkillBaseLimit < x540111_g_SkillLMax then
										SetAbilityExp(sceneId,selfId,x540111_g_AbilitySkillType,x540111_g_SkillLMax)
										TipsToPlayer (sceneId,selfId,"#Y"..x540111_g_AbilitySkillName.."���#G"..x540111_g_SkillLMax-SkillBaseLimit.."��#Y������")
									else
										TipsToPlayer (sceneId,selfId,"�������Ѵ�����")
									end
								end
							end
							SetPlayerVigor(sceneId,selfId, NowVigor - x540111_g_CostVigor)
							return 1
						else					
							BeginQuestEvent(sceneId)
								AddQuestText(sceneId,"#Y�����ռ䲻�㣬�޷��õ��ɼ���Ʒ��")
							EndQuestEvent(sceneId)
							DispatchQuestTips(sceneId,selfId)
						end
					end
				else
					TipsToPlayer(sceneId,selfId,"#Y��������")
				end
			else
				TipsToPlayer(sceneId,selfId,"#Y"..x540111_g_AbilitySkillName.." �ȼ�����#R"..x540111_g_AbilitySkillLevel.."��")
			end
		end
	end
	return 0       	               
end
--���պ�������########################################################################



--�򿪺�����ʼ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x540111_OnProcOver(sceneId,selfId,targetId)

end
--�򿪺�������@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


function  TipsToPlayer (sceneId,selfId,str)
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,str)
	EndQuestEvent(sceneId)
	DispatchQuestTips(sceneId,selfId)
end