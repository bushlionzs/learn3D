x950008_g_ScriptId = 950008

--以上是动态**************************************************************

--任务文本描述
x950008_g_MissionName="其他主手武器"


x950008_g_Items	=	{
										{
											{
												{id=10012201, num=1},
												{id=10012204, num=1},
												{id=10012208, num=1},
												{id=10013001, num=1},
												{id=10014001, num=1}
											
											}
										},
										{
											{
												{id=10022201, num=1},
												{id=10022204, num=1},
												{id=10022207, num=1},
												{id=10022210, num=1},
												{id=10023003, num=1}
											}
										},
										{
											{
												{id=10032201, num=1},
												{id=10032204, num=1},
												{id=10032207, num=1},
												{id=10032210, num=1},
												{id=10033003, num=1}
											}
										},
										{
											{
												{id=10042201, num=1},
												{id=10042204, num=1},
												{id=10042207, num=1},
												{id=10042210, num=1},
												{id=10043003, num=1}
											}
										},
										{
											{
												{id=10052201, num=1},
												{id=10052204, num=1},
												{id=10052207, num=1},
												{id=10052210, num=1},
												{id=10053003, num=1}
												
											}
										},
										{
											{
												{id=10062201, num=1},
												{id=10062204, num=1},
												{id=10062207, num=1},
												{id=10062210, num=1},
												{id=10063003, num=1}
												
											}
										}
									}


--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x950008_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	local ret;
	local zhiye = GetZhiye(sceneId, selfId);
	local itemcount = 0;
		
	BeginAddItem(sceneId);
	for i, items in x950008_g_Items[zhiye+1] do
		for j, item in items do
			AddItem( sceneId, item.id, item.num );
			itemcount = itemcount + 1;
		end
	end
	ret = EndAddItem(sceneId,selfId);
	if ret > 0 and itemcount > 0 then
		AddItemListToPlayer(sceneId,selfId);
	end
	
end

--**********************************
--列举事件
--**********************************
function x950008_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950008_g_ScriptId,x950008_g_MissionName);
end