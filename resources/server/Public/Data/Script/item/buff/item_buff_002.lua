--注意：

--物品技能的逻辑只能使用基础技能和脚本来实现

--脚本:

--以下是脚本样例:


--3001.lua
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号
x417002_g_scriptId = 417002 --临时写这个,真正用的时候一定要改.

--效果的ID
x417002_g_Impact1 = 8712 

--**********************************
--事件交互入口
--**********************************
function x417002_ProcEventEntry( sceneId, selfId, bagIndex,rorf )
	if rorf == 1 then
		if sceneId == 0 then
				local x,z =GetWorldPos(sceneId,selfId)
				if x > 400 then
						local talkrandom =random(1,3)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "又有好玩的啦！", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "我藏在这你都能找到！你一定是耍赖了！", -1)
						elseif talkrandom == 3 then
							NpcTalk(sceneId, selfId, "你发现我了，不跟你玩了！", -1)
						end
				else
						local talkrandom =random(1,3)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "多谢施主搭救！", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "如果施主再晚来些，我就要去见佛祖了！", -1)
						elseif talkrandom == 3 then
							NpcTalk(sceneId, selfId, "阿弥陀佛！多谢施主！", -1)
						end
				end
		elseif sceneId == 56 or sceneId == 156 or sceneId == 256 or sceneId == 356 then
						local talkrandom =random(1,3)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "我刚刚还在想，如果袋子打开，出现的一个狼头该怎么办！", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "我还以为这次死定了，多谢勇士！", -1)
						elseif talkrandom == 3 then
							NpcTalk(sceneId, selfId, "果然那萨满没说错，我一定能活到80岁！", -1)
						end
		elseif sceneId == 64 or sceneId == 164 or sceneId == 264 or sceneId == 364 then
						local talkrandom =random(1,3)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "这是哪里？我应该怎么逃出去呢？", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "我在袋子里什么都看不见，但是听见了惨叫声！", -1)
						elseif talkrandom == 3 then
							NpcTalk(sceneId, selfId, "没想到还能活着出这袋子，谢谢你！", -1)
						end
		elseif sceneId == 67 or sceneId == 167 or sceneId == 267 or sceneId == 367 then
						local talkrandom =random(1,2)
						if talkrandom == 1 then
							NpcTalk(sceneId, selfId, "多谢恩公相救，算命的说我能活到80，果然不错……", -1)
						elseif talkrandom == 2 then
							NpcTalk(sceneId, selfId, "谢谢你救了我，我还以为死定了。", -1)
						end
							
		end
	end
end

