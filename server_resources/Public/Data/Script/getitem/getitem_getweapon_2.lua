x950007_g_ScriptId = 950007

--以上是动态**************************************************************

--任务文本描述
x950007_g_MissionName="副手武器"


x950007_g_Items	=	{
										{
											{
												{id=10070000, num=1},
												{id=10070201, num=1},
												{id=10070204, num=1},
												{id=10070207, num=1},
												{id=10070209, num=1}
											}
										},
										{
											{
												{id=10080000, num=1},
												{id=10080201, num=1},
												{id=10080204, num=1},
												{id=10080207, num=1},
												{id=10080209, num=1}
											}
										},
										{
											{
												{id=10092201, num=1}
										
												
											}
										},
										{
											{
												{id=10102201, num=1}
											}
										},
										{
											{
												{id=10110000, num=1},
												{id=10110201, num=1},
												{id=10110204, num=1},
												{id=10110207, num=1},
												{id=10110209, num=1}
											}
										},
										{
											{
												{id=10120000, num=1},
												{id=10120201, num=1},
												{id=10120204, num=1},
												{id=10120207, num=1},
												{id=10120209, num=1}
												
											}
										}
									}

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x950007_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	local ret;
	local zhiye = GetZhiye(sceneId, selfId);
	local itemcount = 0;
		
	BeginAddItem(sceneId);
	for i, items in x950007_g_Items[zhiye+1] do
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
function x950007_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950007_g_ScriptId,x950007_g_MissionName);
end