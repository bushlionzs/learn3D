x950006_g_ScriptId = 950006

--以上是动态**************************************************************

--任务文本描述
x950006_g_MissionName="主手武器"


x950006_g_Items	=	{
										{
											{
												{id=10010000, num=1},
												{id=10010201, num=1},
												{id=10010204, num=1},
												{id=10010207, num=1},
												{id=10010209, num=1}
											
											}
										},
										{
											{
												{id=10020000, num=1},
												{id=10020201, num=1},
												{id=10020204, num=1},
												{id=10020207, num=1},
												{id=10020209, num=1}
											}
										},
										{
											{
												{id=10030000, num=1},
												{id=10030201, num=1},
												{id=10030204, num=1},
												{id=10030207, num=1},
												{id=10031106, num=1}
											}
										},
										{
											{
												{id=10040000, num=1},
												{id=10040201, num=1},
												{id=10040204, num=1},
												{id=10040207, num=1},
												{id=10040209, num=1}
											}
										},
										{
											{
												{id=10050000, num=1},
												{id=10050201, num=1},
												{id=10050204, num=1},
												{id=10050207, num=1},
												{id=10050209, num=1}
												
											}
										},
										{
											{
												{id=10060000, num=1},
												{id=10060201, num=1},
												{id=10060204, num=1},
												{id=10060207, num=1},
												{id=10060209, num=1}
												
											}
										}
									}

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x950006_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	local ret;
	local zhiye = GetZhiye(sceneId, selfId);
	local itemcount = 0;
		
	BeginAddItem(sceneId);
	for i, items in x950006_g_Items[zhiye+1] do
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
function x950006_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x950006_g_ScriptId,x950006_g_MissionName);
end