--注意：

--物品技能的逻辑只能使用基础技能和脚本来实现

--脚本:

--以下是脚本样例:


--3001.lua
------------------------------------------------------------------------------------------
--一般物品的默认脚本

--脚本号
x417003_g_scriptId = 417003 --临时写这个,真正用的时候一定要改.

--效果的ID
x417003_g_Impact1 = 7044 

--**********************************
--事件交互入口
--**********************************
function x417003_ProcEventEntry( sceneId, selfId, bagIndex,rorf )
	if rorf == 0 then
		SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x417003_g_Impact1, 0);
	end
end

