-------------------------------------------------
-- 现金副本
-------------------------------------------------
x700082_g_ScriptId = 700082



x700082_g_Fuben_list = { 
							{name="【队伍】三番祝家庄",		scriptid = 700030, starttime=0*60+0, endtime=24*60, levelmin=75, levelmax=100},
							{name="【队伍】三番财神殿",		scriptid = 700003, starttime=0*60+0, endtime=24*60, levelmin=60, levelmax=100},
							{name="【队伍】三番和氏璧",		scriptid = 700024, starttime=0*60+0, endtime=24*60, levelmin=40, levelmax=100},
							{name="【队伍】三番囚龙岛",		scriptid = 700028, starttime=0*60+0, endtime=24*60, levelmin=20, levelmax=100},
							
						}



x700082_g_Fuben_EnterInfoList = {
									"\t那时迁人送绰号“鼓上蚤”，见众好汉顺利攻入，连忙施展“缩骨法”，逃出牢笼，祝家庄内机关重重，处处伏兵，时迁虽出牢笼却未能逃出火坑……\n#Y开放时间：#W全天开放\n#Y友情提示：#W3人以上的队伍，才能进入该副本！#G同时每个队员需上交1个三番令！#R不要放过任何一个怪物，否则可能会导致您无法进入排行榜！\n#Y副本说明：#W完成一次本副本，你可以获得#G所有普通祝家庄3环副本的经验奖励！九旄战神出现几率也为普通祝家庄副本的3倍！但也将消耗您一天所有可进入的祝家庄3环副本次数！",

									"\t前日，陛下做了一奇梦，他梦见自己身处凌霄宝殿，天帝赐他一样异宝—金山大玉海，并告知凭此物可保江山万代不移。\n\t陛下醒来后，立刻命我等寻找那传说中的金山大玉海，经我多方探查，终于查明这活财神殿与金山大玉海有着千丝万缕的联系，护国天师玄灵道长已经先行带着他的弟子们进入这财神殿。\n\t可是方才玄灵道长的弟子回报，这活财神殿内竟然有我们大元精锐兵士，并且他们在山顶架设了火炮，欲图对天师不利！\n#Y开放时间：#W全天开放！\n#Y友情提示：#W3人以上的队伍，才能进入该副本！#G同时每个队员需上交1个三番令！#R不要放过任何一个怪物，否则可能会导致您无法进入排行榜！\n#Y副本说明：#W完成一次本副本，你可以获得#G所有普通财神殿3环副本的经验奖励！九旄战神出现几率也为普通财神殿副本的3倍！但也将消耗您一天所有可进入的财神殿3环副本次数！",

									"\t宋金大战后，镇国之宝和氏璧流落民间，百年后突然出现在了东海海眼之中，找到和氏璧的人只要能够降伏隐藏于和氏璧之中的八位枭雄的魂魄就能够窥透天机，预见未来百年之事。\n#Y开放时间：#W全天开放！\n#Y友情提示：#W3人以上的队伍，才能进入该副本！#G同时每个队员需上交1个三番令！#R不要放过任何一个怪物，否则可能会导致您无法进入排行榜！\n#Y副本说明：#W完成一次本副本，你可以获得#G所有普通和氏璧3环副本的经验奖励！九旄战神出现几率也为普通和氏璧副本的3倍！但也将消耗您一天所有可进入的和氏璧3环副本次数！",

									"\t自从郭宝玉将军战败于囚龙岛后，霹雳神火诀落入囚龙岛的魔龙军团手中，而随军大萨满临终前布下的结界随着时间的推移渐渐失效。一旦让魔龙军团脱困，霹雳神火诀将被欧洲诸国所利用，不久的将来，西方人将手持火器而来，中原大地将受到灭顶之灾。\n\t郭侃将军奉命前往囚龙岛调查祖父郭宝玉当年战败的原因，并取回遗失的“霹雳神火诀”，在这个时候，极度需要一群武艺高强，勇气十足的勇士，从囚龙岛进入龙穴，在魔龙的手中拿回“霹雳神火诀”。\n#Y开放时间：#W全天开放！\n#Y友情提示：#W3人以上的队伍，才能进入该副本！#G同时每个队员需上交1个三番令！#R不要放过任何一个怪物，否则可能会导致您无法进入排行榜！\n#Y副本说明：#W完成一次本副本，你可以获得#G所有普通囚龙岛3环副本的经验奖励！九旄战神出现几率也为普通囚龙岛副本的3倍！但也将消耗您一天所有可进入的囚龙岛3环副本次数！"																	
								 
								 }



function x700082_ProcEventEntry(sceneId, selfId, NPCId, MissionId,nIndex)	--点击该任务后执行此脚本
	
	if GetGameOpenById(1022)<=0 then
		x700082_ShowTips(sceneId, selfId, "此活动已关闭")
		return 0
	end

	if nIndex==nil then
		return 0
	end


	x700082_DispatchXianJinFubenInfo( sceneId, selfId, NPCId,nIndex )
	
end


--**********************************

--列举事件

--**********************************

function x700082_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

	if GetGameOpenById(1022)<=0 then
		
		return 0;
	end
	
	if IsPlayerStateNormal(sceneId,selfId ) <= 0 then
		return
	end


	local nIndex = 0




	local nLevel  = GetLevel(sceneId,selfId)


	for i,item in x700082_g_Fuben_list do
		nIndex = nIndex+1
		if nLevel>=item.levelmin and nLevel<=item.levelmax then
			AddQuestNumText(sceneId, x700082_g_ScriptId, item.name,14,nIndex)
		end
	end

	

	

	
	
	
			
end







function x700082_DispatchXianJinFubenInfo( sceneId, selfId, NPCId, nIndex )

	SetQuestData(sceneId, selfId, MD_XIANJIN_FUBEN_TALK_PARAM[1], MD_XIANJIN_FUBEN_TALK_PARAM[2],MD_XIANJIN_FUBEN_TALK_PARAM[3], nIndex );
	
	BeginQuestEvent(sceneId)

		
		AddQuestText(sceneId,"#Y"..x700082_g_Fuben_list[nIndex].name)
		AddQuestText(sceneId,x700082_g_Fuben_EnterInfoList[nIndex])
		
		

	EndQuestEvent()





	DispatchQuestInfo(sceneId, selfId, NPCId, x700082_g_ScriptId, -1);

	
	
end


---------------------------------------------------------------------------------------------------
--申请进入副本
---------------------------------------------------------------------------------------------------
function x700082_ProcAcceptCheck( sceneId, selfId, NPCId )

	if GetGameOpenById(1022)<=0 then
		
		return 0
	end

    return 1
end

----------------------------------------------------------------------------------------------
--点确定后
----------------------------------------------------------------------------------------------
function x700082_ProcAccept( sceneId, selfId )

	
	if GetGameOpenById(1022)<=0 then
		
		return 0
	end

	x700082_OnNpcTalkEnterFuben_XJ( sceneId, selfId)
	
end


------------------------------------------------------------------------
-- 领取buff接口
----------------------------------------------------------------------

function x700082_OnNpcTalkEnterFuben_XJ( sceneId, selfId)

	if GetGameOpenById(1022)<=0 then
		x700082_ShowTips(sceneId, selfId, "此活动已关闭")
		return 0
	end

	local nIndex = GetQuestData(sceneId, selfId, MD_XIANJIN_FUBEN_TALK_PARAM[1], MD_XIANJIN_FUBEN_TALK_PARAM[2],MD_XIANJIN_FUBEN_TALK_PARAM[3] );

	CallScriptFunction(FUBEN_COMMON_SCRIPT, "OnRequestEnterFuben", sceneId, selfId, 1, 0, x700082_g_Fuben_list[nIndex].scriptid);
	

	
end


function x700082_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end
