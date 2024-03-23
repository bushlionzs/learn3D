--MisDescBegin

x300612_g_ScriptId 	  = 300612
x300612_g_MissionKind 				= 	1                       --任务类型
x300612_g_ExtTarget					=	{ {type=20,n=1,target="马车"} }
x300612_MissionName = "【黑金】理赔"

--MisDescEnd	  
						
--子任务																	   
x300612_g_SubMissionID				=	{ { MissionId=7556,BaoDanId=13080017,ReturnMoney=2500 }, 
										  {	MissionId=7557,BaoDanId=13080018,ReturnMoney=5000 },
										  {	MissionId=7558,BaoDanId=13080019,ReturnMoney=7500 },
										  {	MissionId=7546,BaoDanId=13080020,ReturnMoney=15000 },
										  { MissionId=7547,BaoDanId=13080021,ReturnMoney=20000 },
										  { MissionId=7548,BaoDanId=13080022,ReturnMoney=25000 },
										}

function x300612_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x300612_g_ScriptId,x300612_MissionName,3);

end



--点击（按钮）点击该任务后执行此脚本
function x300612_ProcEventEntry( sceneId, selfId, targetId )

	BeginQuestEvent(sceneId)
	local Readme_1 ="\t朋友，在这种乱世之下，还是有保险比较可靠吧？虽然不能挽回全部损失，但总比血本无归要强很多，您说是吧？#r"
	local Readme_2="\t好吧，现在把#G理赔单#W拿来，我们马上对您进行赔付。"
	local Readme = Readme_1..Readme_2
	AddQuestText(sceneId,Readme)
	EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId, selfId, targetId, x300612_g_ScriptId, -1);

end

--**********************************
--接受
--**********************************
function x300612_ProcAcceptCheck( sceneId, selfId, targetId )
	
	local IsHaveBaoDan = 0

	for i,itm in x300612_g_SubMissionID do
		local ItemCount = GetItemCountInBag(sceneId, selfId,itm.BaoDanId)
		if ItemCount > 0 then
			IsHaveBaoDan = 1
			--删除理赔单
			DelItem(sceneId, selfId,itm.BaoDanId,ItemCount)	
			AddMoney(sceneId,selfId,0,ItemCount * itm.ReturnMoney) 	
			local Readme = "理赔成功，返回现银#R#{_MONEY"..ItemCount * itm.ReturnMoney.."}"

			BeginQuestEvent(sceneId)
			AddQuestText(sceneId,Readme)
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)		
			Msg2Player(sceneId,selfId,Readme,8,2)
		end
	end

	if IsHaveBaoDan == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"很抱歉，你没有理赔单")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
		Msg2Player(sceneId,selfId,"很抱歉，你没有理赔单",8,2)
	end
	
end

--**********************************
--接受
--**********************************
function x300612_ProcAccept( sceneId, selfId )
end

--完成任务
--返回1代表成功，0代表交任务失败
function x300612_ProcQuestSubmit( sceneId, selfId, targetId, selectId, MissionId )
end


--********************************************************************
--放弃
--********************************************************************
function x300612_ProcQuestAbandon( sceneId, selfId,MissionId )
end

