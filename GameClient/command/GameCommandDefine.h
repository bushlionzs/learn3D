/*$T Client/Game/Command/GameCommandDefine.h GC 1.140 08/23/09 04:52:40 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


/*
 * ;
 * 游戏命令系统 ;
 * ;
 * ;
 * 描述： Nick 080314 向lua脚本发送的消息的枚举定义，
 * lua脚本使用了与枚举值对应的整数。
 * 所以新添加枚举值一定要加到最后。以避免lua脚本消息出错。 Nick 080327
 * 新增在脚本里AddCommand用与GAME_COMMAND_ID对应的字符串的功能。
 * 所以该枚举可以随意加了。
 */
#ifndef _GAME_COMMAND_DEFINE_H_
#define _GAME_COMMAND_DEFINE_H_
enum GAME_COMMAND_ID
{
	/* 游戏通用操作 */
	GCD_APPLICATION_INITED,						/* 游戏程序初始化 */

	/* 场景 */
	GCD_ON_SCENE_TRANS,							/* 场景转移 */
	GCD_SCENE_TRANSED,							/* 场景转移后 */

	/* arg0- 小地图的名称 */
	GCD_SCENE_TELEPORT,							/* 同场景内的切换 */

	/*
	 * GCD_ON_SCENE_UPDATED, // 场景更新(一般用于玩家城市) ;
	 * // arg0- 小地图的名称
	 */
	GCD_SCENE_NAME_TIP,							/* 变换场景后显示场景名 */

	GCD_ON_SERVER_TRANS,						/* 服务器转移 */

	GCD_PLAYER_ENTER_WORLD,						/* 进入世界 */
	GCD_PLAYER_LEAVE_WORLD,						/* 退出世界 */

	GCD_TEAM_CHANG_WORLD,						/* 队友改变场景了 */
	GCD_SKILL_CHANGED,							/* 玩家的某项技能发生改变, */

	/* arg0 - 技能id */
	GCD_PACKAGE_ITEM_CHANGED,					/* 包裹中的某个物品发生改变 */

	/* arg0 - 物品在包裹中的编号 */
	GCD_MAINTARGET_CHANGED,						/* 主选择对象更改 */

	/* arg0 - 对象ServerId */
	GCD_MAINTARGET_OPEND,						/* 当target 窗口选择是队友的情况， 打开窗口 */
	GCD_MAINTARGET_BUFF_REFRESH,				/* 刷新主目标buff */
	GCD_UPDATE_TARGET2,							/* 刷新主目标的目标 */

	GCD_TOGLE_SKILL_BOOK,						/* 打开/关闭技能书 */
	GCD_CLOSE_SKILL_BOOK,						/* 关闭技能书 */

	GCD_TOGLE_PET_PAGE,							/* 打开宠物界面 */
	GCD_TOGLE_LIFE_PAGE,						/* 打开生活技能界面 */
	GCD_TOGLE_COMMONSKILL_PAGE,					/* 打开普通技能界面 */
	GCD_SKILL_UPDATE,							/* 玩家技能数据发生改变 */

	GCD_TOGLE_CONTAINER,						/* 打开/关闭包裹 */

	/* 此枚举的位置不能变换，脚本中使用 22 */
	GCD_TIME_ENENT,								/* 时间事件 */

	/* 角色属性 */
	GCD_UNIT_HP,								/* 某个单元的HP发生变化 */

	/*
	 * arg0 - 单元名称 ;
	 * "player" - 玩家自己 ;
	 * "target" - 主目标 ;
	 * "pet" - 自己的宠物 ;
	 * "party*" - 队友(1-4) ;
	 * "partypet*" - 队友的宠物(1-4) ;
	 * ..
	 */
	GCD_UNIT_MP,								/* 某个单元的MANA发生变化 */

	/* arg0 - 单元名称(同上) */
	GCD_UNIT_RAGE,								/* 某个单元的怒气发生变化 */

	/* arg0 - 单元名称(同上) */
	GCD_UNIT_MAX_RAGE,							/* 最大怒气 */

	GCD_UNIT_RAGE_RESPEED,						/* 怒气恢复速度 */

	/*
	 * GCD_UNIT_TALENT, //某个单元的天赋等级发生变化 ;
	 * arg0 - 单元名称(同上) ;
	 * arg1 - 天赋名称
	 */
	GCD_UNIT_EXP,								/* 某个单元的经验值发生变化 */

	/* arg0 - 单元名称(同上) */
	GCD_UNIT_MONEY,								/* 某个单元的钱发生变化 */

	/* arg0 - 单元名称(同上) */
	GCD_UNIT_RACE_ID,							/* 数据表中的ID */
	GCD_UNIT_NAME,								/* 角色的名字，从服务器传来 */
	GCD_UNIT_CAMP_ID,							/* 阵营ID */
	GCD_UNIT_LEVEL,								/* 等级 */
	GCD_UNIT_MOVE_SPEED,						/* 移动的速度 */
	GCD_UNIT_FIGHT_STATE,						/* 战斗状态 */
	GCD_UNIT_MAX_EXP,							/* 最大EXP */
	GCD_UNIT_TITLE,								/* 称号 */
	GCD_UNIT_STRIKEPOINT,						/* 连击点 */
	GCD_UNIT_RELATIVE,							/* 归属问题 */

	/* 一级战斗属性 */
	GCD_UNIT_STR,								/* 外功 */
	GCD_UNIT_SPR,								/* 内功 */
	GCD_UNIT_CON,								/* 身法 */
	GCD_UNIT_INT,								/* 体魄 */
	GCD_UNIT_DEX,								/* 智慧 */
	GCD_UNIT_POINT_REMAIN,						/* 剩余待分配点数 */

	/* 二级战斗属性 */
	GCD_UNIT_ATT_NEAR,							/* 近攻 */
	GCD_UNIT_DEF_NEAR,							/* 近防 */
	GCD_UNIT_ATT_FAR,							/* 远攻 */
	GCD_UNIT_DEF_FAR,							/* 远防 */

	/* GCD_UNIT_ATT_PHYSICS, // 物理攻击力 */
	GCD_UNIT_ATT_MAGIC,							/* 魔法攻击力 */

	/* GCD_UNIT_DEF_PHYSICS, // 物理防御力 */
	GCD_UNIT_DEF_MAGIC,							/* 魔法防御力 */
	GCD_UNIT_MAX_HP,							/* 最大生命点 */
	GCD_UNIT_MAX_MP,							/* 最大魔法点 */
	GCD_UNIT_HP_RE_SPEED,						/* HP恢复速度 点/秒 */
	GCD_UNIT_MP_RE_SPEED,						/* MP恢复速度 点/秒 */
	GCD_UNIT_TOUGHNESS,							/* 韧性 */
	GCD_UNIT_HIT,								/* 命中率 */
	GCD_UNIT_MISS,								/* 闪避率 */
	GCD_UNIT_CRIT_RATE,							/* 会心率 */
	GCD_UNIT_CRIT_HURT,							/* 爆击伤害 */
	GCD_UNIT_ATT_SPEED,							/* 攻击速度 */
	GCD_UNIT_ATT_COLD,							/* 冰攻击 */
	GCD_UNIT_DEF_COLD,							/* 冰防御 */
	GCD_UNIT_ATT_FIRE,							/* 火攻击 */
	GCD_UNIT_DEF_FIRE,							/* 火防御 */
	GCD_UNIT_ATT_LIGHT,							/* 电攻击 */
	GCD_UNIT_DEF_LIGHT,							/* 电防御 */
	GCD_UNIT_ATT_POSION,						/* 毒攻击 */
	GCD_UNIT_DEF_POSION,						/* 毒防御 */
	GCD_UNIT_VIGOR,								/* 活力值 */
	GCD_UNIT_MAX_VIGOR,							/* 活力值上限 */
	GCD_UNIT_REGENE_VIGOR,						/* 活力回复速度 */
	GCD_UNIT_ENERGY,							/* 精力值 */
	GCD_UNIT_MAX_ENERGY,						/* 精力值上限 */
	GCD_UNIT_HOT,								/* 魅力 */
	GCD_UNIT_INHERENCE,							/* 天赋 */
	GCD_UNIT_PVP2V2_LEVEL,						/* 竞技场排名 */
	GCD_UNIT_PVP2V2_MARK,						/* 竞技场积分 */
    GCD_UNIT_FEAST_SCORE,                       /* 节日积分 */

	GCD_UNIT_NEARATT_REDUCE,					/* 近程减免 */
	GCD_UNIT_FARATT_REDUCE,						/* 远程减免 */
	GCD_UNIT_MAGICATT_REDUCE,					/* 魔法减免 */

	GCD_UNIT_DREAD_RESIST,						/* 恐惧抗性 */
	GCD_UNIT_COMA_RESIST,						/* 昏迷抗性 */
	GCD_UNIT_HUSH_RESIST,						/* 沉默抗性 */
	GCD_UNIT_UNARM_RESIST,						/* 缴械抗性 */
	GCD_UNIT_ATTACKSPEED_RESIST,				/* 减攻速抗性 */
	GCD_UNIT_SKILLSPEED_RESIST,					/* 减施速抗性 */
	GCD_UNIT_MOVEREDUCE_RESIST,					/* 减移速抗性 */

	GCD_UNIT_MENPAI,							/* 职业号 */
	GCD_UNIT_HAIR_MESH,							/* -> TABLE_CHARACTER_HAIR_GEO */
	GCD_UNIT_HAIR_COLOR,						/* 头发颜色 */
	GCD_UNIT_FACE_MESH,							/* -> TABLE_CHARACTER_HEAD_GEO char_head.tab */
	GCD_UNIT_FACE_IMAGE,						/* 头像信息改变 */
	GCD_UNIT_EQUIP_VER,							/* 角色的装备状态版本号，用于和服务器同步数据的依据 */
	GCD_UNIT_EQUIP,								/* 装备表(含武器) */
	GCD_UNIT_EQUIP_WEAPON,						/* 武器 */
	GCD_UNIT_Honor_FIRE,
	GCD_UNIT_CTShengWang_FIRE,
	GCD_UNIT_JHShengWang_FIRE,
	GCD_SHOW_CONTEXMENU,						/* 显示右键菜单 */

	/*
	 * arg0 - 菜单类 ;
	 * "player" - 玩家自己 ;
	 * "other_player" - 其他玩家 ;
	 * "npc" - npc ;
	 * arg1 - 鼠标位置_x ;
	 * arg2 - 鼠标位置_y
	 */
	GCD_TOGLE_COMPOSE_WINDOW,					/* 打开关闭合成界面 */

	GCD_TOGLE_CONSOLE,							/* 显示控制台 */

	GCD_ON_SKILL_ACTIVE,						/* 某个技能开始使用 */

	/* arg0 - 技能ID */
	GCD_POSITION_MODIFY,						/* 人物得位置改变了 */

	GCD_CHAT_MESSAGE,							/* 得到聊天信息 */

	/*
	 * | arg0 - 聊天类型 | "here" - 附近玩家 | "scene" - 场景 | "sys" - 系统 | "team"
	 * - 队伍 | "guild" - 帮会 | "user" - 自建 | "private" - 私聊 | | arg1
	 * 说话者的名字 | | arg2 - 说话内容 |
	 */
	GCD_CHAT_MESSAGE2,							/* 信息反馈 [ ZG 2008-6-6 ] */
	GCD_CHAT_CHANNEL_CHANGED,					/* 聊天频道发生改变 */
	GCD_CHAT_CHANGE_PRIVATENAME,				/* 修改聊天中的密语对象 */
	GCD_CHAT_ITEMLINK,							/* 聊天中物品连接 */
	GCD_CHAT_QUESTLINK,						/* 聊天中任务连接 */
	GCD_CHAT_HORSELINK,							/* 聊天中坐骑连接 */
	GCD_CHAT_SKILLLINK,							/* 聊天中坐骑连接 */
	GCD_CHAT_TAB_CREATE,						/* 创建聊天页面 */
	GCD_CHAT_TAB_CREATE_FINISH,					/* 创建聊天页面完成 */
	GCD_CHAT_TAB_CONFIG,						/* 配置聊天页面 */
	GCD_CHAT_TAB_CONFIG_FINISH,					/* 配置聊天页面完成 */
	GCD_CHAT_FACEMOTION_SELECT,					/* 聊天表情选择 */
	GCD_CHAT_TEXTCOLOR_SELECT,					/* 聊天文字颜色选择 */
	GCD_SHOW_CHATCOLOR_SELECT,					/* 聊天文字颜色选择界面 */
	GCD_CHAT_CONTEX_MENU,						/* 聊天相关的快捷菜单 */
	GCD_CHAT_ACTSET,							/* 聊天动作命令 */
	GCD_CHAT_ACTSETNEW,							/* 聊天动作命令新 */
	GCD_CHAT_ACT_SELECT,						/* 聊天动作命令界面显示 */
	GCD_CHAT_ACT_HIDE,							/* 聊天动作命令界面关闭，因为动作命令界面比较特殊，需要支持托拽。 */
	GCD_CHAT_PINGBI_LIST,						/* 聊天屏蔽界面 */
	GCD_CHAT_PINGBI_UPDATE,						/* 屏蔽列表更新 */
	GCD_CHAT_ADJUST_MOVE_CTL,					/* 通知聊天窗口调整大小 */
	GCD_CHAT_INPUTLANGUAGE_CHANGE,				/* 输入法变更 */
	GCD_CHAT_SHOWUSERINFO,						/* 聊天查看玩家信息界面 */
	GCD_CHAT_LOAD_TAB_CONFIG,					/* 聊天页面配置信息 */
	GCD_CHAT_INPUT_STATE,						/* 聊天输入状态 */
	GCD_CHAT_SHOW_CHATFILTERUI,					/* 过滤界面 */
	GCD_CHAT_PopChatEditBox,					/* 弹出聊天输入框 */
	GCD_CHAT_COPYTEXT,
	GCD_CHAT_PASTETXT,
	GCD_CHAT_RAPID_REPLY,						/* !< 快速回复事件 */
	GCD_CHAT_RAPID_PERSONAL,					/* !< 快速私聊。 */
	GCD_CHAT_CLEAR,								/* !< 清除聊天记录。 */

	GCD_ACCELERATE_KEYSEND,						/* 键盘快捷键发送 */

	GCD_UI_SHOWHIDE,							/* 显示/隐藏主界面 */

	GCD_LOOT_OPENED,							/* 箱子打开 */
	GCD_LOOT_SLOT_CLEARED,						/* 箱子中的某个位置清空 */

	/* arg0 - 箱子中的位置 */
	GCD_LOOT_CLOSED,							/* 箱子关闭 */

	GCD_PROGRESSBAR_SHOW,						/* 进度条显示 */
	GCD_PROGRESSBAR_HIDE,						/* 进度条隐藏 */
	GCD_PROGRESSBAR_WIDTH,						/* 进度条宽度调整 */

	/* arg0 - 调整到的百分比 1 < x < 100 */
	GCD_CHANGE_BAR,								/* 改变工具条上的Action */

	/*
	 * arg0 - Bar类型 ;
	 * arg1 - Index ;
	 * arg2 - ActionItem ID
	 */
	GCD_UPDATE_BAR,								/* 刷新快捷栏上的Action状态 */

	GCD_TOGLE_QUEST,							/* 接收任务界面 */
	GCD_UPDATE_QUEST,							/* 刷新任务列表 */
	GCD_REPLY_QUEST,							/* 提交任务界面 */
	GCD_UPDATE_REPLY_QUEST,					/* 刷新提交任务界面 */
	GCD_UPDATE_TIME_QUEST,					/* 刷新任务中的时间倒计时 */
	GCD_UPDATE_TIME_QUEST_SET_QUEST_NAME,	/* 设置倒计时任务的名字 */
	GCD_UPDATE_TIME_QUEST_SET_TOTAL_TIME,		/* 设置倒计时任务的总时间长度 */
	GCD_UPDATE_TIME_QUEST_SET_EVENT_TIME,		/* 设置倒计时任务事件触发时间 */

	GCD_TOGLE_LARGEMAP,								/* 关闭打开大地图 */
	GCD_TOGLE_SCENEMAP,								/* 关闭打开大地图 */
	GCD_OPEN_MINIMAP,								/* 打开小地图 */
	GCD_OPEN_MINIMAPEXP,							/* 打开扩展小地图 */
	GCD_AUTO_FIND_PATH,
	GCD_SHOW_MINIMAP_BUTTON,						/* 显示/隐藏小地图 */

	GCD_QUEST_EVENTLIST,							/* 打开和npc第一次对话时的可执行脚本列表 */
	GCD_QUEST_INFO,									/* 打开和npc第二次对话(在接任务时，看到的任务信息，等待接受) */
	GCD_QUEST_REGIE,								/* 漕运任务 */
	GCD_QUEST_CONTINUE_DONE,						/* 接受任务后，再次和npc对话，所得到的任务需求信息，(任务完成) */
	GCD_QUEST_CONTINUE_NOTDONE,						/* 接受任务后，再次和npc对话，所得到的任务需求信息，(任务未完成) */
	GCD_QUEST_AFTER_CONTINUE,						/* 点击“继续之后”，奖品选择界面 */
	GCD_QUEST_TIPS,									/* 游戏过程中的任务进展提示信息 */
	GCD_QUEST_INPUT_PASSWD_COMMAND,					/* 通过输入命令打开物品操作 */
	GCD_QUESTLOG_AUTO_FIND_PATH,					/* 自动寻路和与NPC对话 */
	GCD_EVENTLIST_HIDE,								/* 离开探索区域后关闭EventList */

	GCD_TOGLE_COMPOSEITEM,							/* 打开/关闭 合成界面 */

	/* arg0 - 生活技能的名称 */
	GCD_TOGLE_COMPOSEGEM,							/* 打开/关闭 宝石合成界面 */
	GCD_ON_LIFEABILITY_ACTIVE,						/* 某个生活技能开始使用 */

	/*
	 * arg0 - 技能ID ;
	 * arg1 - 配方 ;
	 * arg2 - 平?
	 */
	GCD_NEW_DEBUGMESSAGE,							/* 新的debug string弹出，在屏幕上用listbox显示。 */
	GCD_QUICK_CHANGE_EQUIP,						/* 打开关闭一键换装界面 */
	GCD_UPDATE_QUICK_CHANGE,						/* 更新一键换装界面 */
	GCD_QUICK_CHANGE_SUCCESS,						/* 一键换装成功 */
	GCD_QUICK_UPDATE_FRAME,							/* 购买商品时，如果打开了一健换装界面，更新此界面 */

	/* 人物属性界面 */
	GCD_UPDATE_EQUIP,								/* 更新装备 */
	GCD_OPEN_BOOTH,									/* 打开货架栏 */
	GCD_CLOSE_BOOTH,								/* 关闭货架栏 */
	GCD_MANUAL_ATTR_SUCCESS_EQUIP,					/* 手动调节属性成功. */
	GCD_CUR_TITLE_CHANGEED,							/* 当前人物的称号改变了. */

	GCD_UPDATE_BOOTH,								/* 货架更新 */

	GCD_OPEN_CHARACTOR,								/* 打开人物属性栏 */
	GCD_OPEN_EQUIP,									/* 打开装备栏 */
	GCD_TOGLE_JOINSCHOOL,							/* 打开加入职业的对话框 */

	/* Nick 2007.11.22 */
	GCD_OPEN_MAIN_FUNC_BTN,							/* 主功能按钮，用于打开8个主功能按钮 */

	GCD_OPEN_ADD_HOLE,								/* 打开打孔界面 */
	GCD_UPDATE_ADD_HOLE,							/* 更新打孔界面 */
	GCD_ADD_HOLE_SUCCESS,							/* 成功打孔 */

	GCD_OPEN_BANG_DING,								/* 打开绑定界面 */
	GCD_UPDATE_BANG_DING,							/* 更新绑定界面 */
	GCD_ADD_BANG_DING_SUCCESS,						/* 绑定成功 */

	GCD_OPEN_DA_XING,								/* 打开打星界面 */
	GCD_UPDATE_DA_XING,								/* 更新打星界面 */
	GCD_OPEN_DA_XING_SUCCESS,						/* 打星成功 */

	GCD_OPEN_RING_FUSION,							/* 打开戒指熔炼界面 */
	GCD_UPDATE_RING_FUSION,							/* 更新戒指熔炼界面 */
	GCD_OPEN_STARS_FUSION,							/* 打开星辰熔炼界面*/

	GCD_OPEN_SP_REPAIR,								/* 打开特修界面 */
	GCD_UPDATE_SP_REPAIR,							/* 更新特修界面 */
	GCD_OPEN_SP_REPAIR_SUCCESS,						/* 特修成功 */
	GCD_OPEN_REPAIR_SURE,							/* 弹出修理消费提示对话框 */

	GCD_OPEN_SYNTHESIZE,							/* 打开合成与打造对话框 */
	GCD_CLOSE_SYNTHESIZE,							/* 关闭合成与打造对话框 */

	GCD_OPEN_EQUIP_REWORK,							/* 打开改造对话框 */

	GCD_CLOSE_EQUIP_REWORK,							/* 关闭改造对话框 */

	GCD_OPEN_EQUIP_DISASS,							/* 打开拆解装备对话框 */
	GCD_UPDATE_EQUIP_DISASS,						/* 更新 */
	GCD_CLOSE_EQUIP_DISASS,							/* 关闭拆解装备对话框 */

	GCD_UPDATE_CONTAINER,							/* 包裹状态更新 */
	GCD_IMPACT_SELF_UPDATE,							/* 自己的特效更新 */
	GCD_IMPACT_SELF_UPDATE_TIME,					/* 自己的特效时间的更新 */
	GCD_IMPACT_SELF_CLEANUP,						/* 清除 */

	GCD_TOGLE_SKILLSTUDY,							/* 技能天赋的学习和升级 */
	GCD_SKILLSTUDY_SUCCEED,							/* 技能天赋学习成功 */

	GCD_TOGLE_ABILITY_STUDY,						/* 生活技能学习界面 */
	GCD_TOGLE_ABILITY_STUDY_CLOSE,					/* 关闭生活技能学习界面 */
	GCD_OPEN_AGNAME,								/* 打开选择称号界面 */
	GCD_CLOSE_AGNAME,								/* 关闭选择称号界面 */

	GCD_TOGLE_BANK,									/* 打开银行界面 */
	GCD_UPDATE_BANK,								/* 更新银行界面 */
	GCD_TOGLE_BANKPET,								/* 打开银行坐骑界面 */
	GCD_UPDATE_BANKPET,								/* 更新银行坐骑界面 */
	GCD_TOGLE_INPUT_MONEY,							/* 打开输入钱的界面 */
	GCD_CLOSE_INPUT_MONEY,							/* 关闭输入金钱界面 */
	GCD_OPEN_BANK_EVENT,							/* 判断银行密码保护 */

	GCD_RECEIVE_EXCHANGE_APPLY,					/* 收到交易请求 */
	GCD_STOP_EXCHANGE_TIP,							/* 停止交易请求提示 */
	GCD_OPEN_EXCHANGE_FRAME,						/* 打开交易对话筐 */
	GCD_UPDATE_EXCHANGE,							/* 更新交易界面 */
	GCD_CANCEL_EXCHANGE,							/* 取消交易 */
	GCD_SUCCEED_EXCHANGE_CLOSE,					/* 交易成功，通知关闭交易界面（可能还会关闭相关界面） */
	GCD_EXCHANGE_INPUT_MONEY,						/* 交易框输入的money */
	GCD_PACKET_OPEN_SALE,							/* 密码保护摆摊交易 */
	GCD_EQUIP_LEVELUP_CANCEL_BIND,					

	GCD_UPDATE_PET_PAGE,							/* 刷新宠物界面 */
	GCD_UPDATE_LIFESKILL_PAGE,						/* 刷新生活技能界面 */
	GCD_OPEN_COMPOSE_ITEM,							/* 打开制作物品界面 */
	GCD_UPDATE_COMPOSE_ITEM,						/* 刷新制作物品界面 */
	GCD_OPEN_COMPOSE_GEM,							/* 打开镶嵌界面 */
	GCD_OPEN_REPLACE_GEM,							/* 替换界面 */
	GCD_UPDATE_COMPOSE_EQUIP,						/* 刷新镶嵌界面 */
	GCD_UPDATE_COMPOSE_GEM,							/* 刷新镶嵌界面 */
	GCD_COMPOSE_GEM_SUCCESS,						/* 刷新镶嵌界面 */
	GCD_ENCHASE_CONFIRM_DLG,						/* 镶嵌确认界面 */

	GCD_AFFIRM_SHOW,								/* 打开放弃任务确认界面 */

	GCD_OPEN_STALL_SALE,							/* 摆摊(卖) */
	GCD_OPEN_STALL_BUY,								/* 摆摊(买) */
	GCD_OPEN_STALL_BUY_GOLDSURE,					/* 金币摊位确定打开 */
	GCD_UPDATE_STALL_BUY,							/* 更新(卖) */
	GCD_UPDATE_STALL_SALE,							/* 更新(买) */
	GCD_OPEN_STALL_RENT_FRAME,						/* 摆摊(租金税率提示) */
	GCD_STALL_SALE_SELECT,							/* 摆摊(卖)时有选中摊位上的物品 */
	GCD_STALL_BUY_SELECT,							/* 摆摊(买)时有选中摊位上的物品 */
	GCD_OPEN_STALL_MESSAGE,							/* 摆摊(信息发布界面) */
	GCD_CLOSE_STALL_MESSAGE,						/* 摆摊(关系消息界面) */

	GCD_OPEN_DISCARD_ITEM_FRAME,					/* 销毁物品 */
	GCD_OPEN_CANNT_DISCARD_ITEM,					/* 不能销毁物品 */

	GCD_SHOW_SPLIT_ITEM,							/* 打开拆分武平对话框 */
	GCD_HIDE_SPLIT_ITEM,							/* 关闭拆分武平对话框 */

	GCD_TOGLE_FRIEND_INFO,							/* 打开关闭好友列表对话框 */
	GCD_TOGLE_FRIEND,								/* 打开关闭好友对话框 */
	GCD_UPDATE_FRIEND,								/* 跟新好友数据了 */
	GCD_UPDATE_FRIEND_INFO,							/* 好友数据界面打开 */
	GCD_MENU_UPDATE_FRIENDCUSTOMGROUP,				/* 更新好友自定义组菜单(自定义1--自定义5) */
	GCD_OPEN_EMAIL,									/* 打开信件界面 */
	GCD_OPEN_EMAIL_WRITE,							/* 打开信件界面 */
	GCD_CLOSE_EMAIL_WRITE,							/* 关闭信件界面 */
	GCD_HAVE_MAIL,									/* 有邮件 */
	GCD_SEND_MAIL,									/* 发送邮件 */
	GCD_UPDATE_EMAIL,								/* 刷新当前邮件 */
	GCD_FRIEND_SET,									/* 设置 */
	GCD_MOOD_CHANGE,								/* 心情改变了 */
	GCD_OPEN_HISTROY,								/* 玩家历史消息 */

	GCD_OPEN_XIAOLABA,								/* 小喇叭广播电台 */

	/* 好友搜索 */
	GCD_OPEN_FRIEND_SEARCH,							/* 搜索好友界面 */

	/* 系统设置相关 */
	GCD_TOGLE_SYSTEMFRAME,							/* 打开系统主界面 */
	GCD_TOGLE_VIEWSETUP,							/* 打开视频设置界面 */
	GCD_TOGLE_SOUNDSETUP,							/* 打开声音设置界面 */
	GCD_TOGLE_UISETUP,								/* 打开界面设置 */
	GCD_TOGLE_INPUTSETUP,							/* 打开按键设置 */
	GCD_TOGLE_GAMESETUP,							/* 游戏性设置 */
	GCD_UPDATE_VIEWSETUP,							// 更新视频设置界面

	/* 设置自定义键盘 */
	GCD_KEYBOARD_SET_KEY,							/* 设置键值 */
	GCD_KEYBOARD_SWAP_KEY,							/* 交换键值 */
	GCD_KEYBOARD_SET_REPEAT,						/* 存在重复设置 */
	GCD_KEYBOARD_CANCEL,							/* 取消重定义该快捷键 */
	GCD_KEYBOARD_OVERWRITE,							/* 被覆盖快捷键 */

	/* 玩家商店 */
	GCD_PS_OPEN_OTHER_SHOP,							/* 打开别人的商店 */
	GCD_PS_OPEN_MY_SHOP,							/* 打开自己的商店 */
	GCD_PS_OPEN_CREATESHOP,							/* 打开创建商店界面 */
	GCD_PS_CLOSE_CREATESHOP,						/* 关闭创建商店界面 */
	GCD_PS_OPEN_SHOPLIST,							/* 打开商店列表界面 */
	GCD_PS_SELF_ITEM_CHANGED,						/* 自己商店内物品发生改变 */
	GCD_PS_OTHER_SELECT,							/* 选中一个物品 */
	GCD_PS_SELF_SELECT,								/* 选中一个商品 */

	GCD_PS_UPDATE_MY_SHOP,							/* 更新自己商店的数据 */
	GCD_PS_UPDATE_OTHER_SHOP,						/* 更新商店的数据 */

	GCD_PS_OPEN_OTHER_TRANS,						/* 打开自己的盘出状态中的商店 */
	GCD_PS_UPDATE_OTHER_TRANS,						/* 更新 */
	GCD_PS_OTHER_TRANS_SELECT,						/* 选中 */

	GCD_OPEN_PS_MESSAGE_FRAME,						/* 玩家商店操作中需要弹出的确认对话框 */

	GCD_PS_OPEN_MESSAGE,							/* 打开玩家商店的消息框 */
	GCD_PS_UPDATE_MESSAGE,							/* 更新玩家商店的消息框 */

	GCD_OPEN_PET_LIST,								/* 交易等过程使用的宠物列表 */
	GCD_VIEW_EXCHANGE_PET,							/* 交易等过程中显示宠物 */
	GCD_CLOSE_PET_LIST,								/* 交易等过程结束的时候关闭宠物列表界面 */
	GCD_UPDATE_PET_LIST,							/* 更新宠物列表界面 */
	GCD_HORSE_IS_DELETED,							/* 骑乘被放生或收回 */
    GCD_OPEN_ITEM_LIST,                             /* 打开任务提交物品界面 */
    GCD_CLOSE_ITEM_LIST,                            /* 关闭任务提交物品界面 */

	GCD_OPEN_PRIVATE_INFO,							/* 打开玩家信息对话框 */
	GCD_OPEN_OTHER_INFO,							/* 打开玩家资料界面 */
	GCD_UPDATE_PRIVATE_INFO,						/* 更新玩家资料 */
	GCD_PRIVATE_INFO_MODIFY,						/* 玩家资料有修改 */

	GCD_OPEN_CALLOF_PLAYER,							/* 打开有人要拉你的对话框 */
	GCD_NET_CLOSE,									/* 断开连接 */

	GCD_OPEN_ITEM_COFFER,							/* 打开锁定物品界面 */

	GCD_PS_INPUT_MONEY,								/* 弹出玩家商店的输入钱的框 */

	/* 组队相关事件 */
	GCD_TEAM_OPEN_TEAMINFO_DLG,						/* 打开队伍信息对话框. */

	/*
	 * ;
	 * arg0 - 正整数, 从0开始 ;
	 * 0 : 有人邀请你加入队伍 ;
	 * 1 : 有人申请加入队伍 ;
	 * 2 : 打开队伍信息 ;
	 * -1: 关闭对话?
	 */
	GCD_TEAM_NOTIFY_APPLY,							/* 通知队长, 有人申请加入队伍. */

	/*
	 * ;
	 * arg0 - 正整数, 从0开始 ;
	 * 0 : 有人邀请你加入队伍 ;
	 * 1 : 有人申请加入队伍 ;
	 * 申请的人的具体信息从申请的信息队列中获?
	 */
	GCD_TEAM_APPLY,									/* 有人申请你加入队伍. */

	/*
	 * ;
	 * arg0 - 字符串 ;
	 * 申请的人.
	 */
	GCD_TEAM_INVITE,								/* 有人邀请你加入队伍. */

	/*
	 * ;
	 * arg0 - 字符串 ;
	 * 邀请你的人.
	 */
	GCD_TEAM_CLEAR_UI,								/* 清空界面 */

	/*
	 * ;
	 * 无参?
	 */
	GCD_TEAM_REFRESH_UI,							/* 刷新界面 */

	/*
	 * ;
	 * 无参数
	 */
	GCD_TEAM_MEMBER_ENTER,							/* 有新的队员进入 */

	/*
	 * ;
	 * arg0 - 正整数, 从1 开始 ;
	 * 在ui界面中的显示位置
	 */
	GCD_TEAM_UPTEDATA_MEMBER_INFO,					/* 更新队员信息 */

	/*
	 * arg0 - 正整数, 从1 开始 ;
	 * 在ui界面中的显示位?
	 */
	GCD_TEAM_MESSAGE,								/* 队伍信息提示信息 */

	/*
	 * arg0 - 字符串 ;
	 * 需要提示的信息. ;
	 * 注意, 这条消息包含了提示给界面的信息 ;
	 * 如: xxx离开队伍 ;
	 * xxx已经在一个队伍中
	 */
	GCD_TEAM_MEMBER_INVITE,							/* 队员邀请某一个人加入队伍请求队长同意 */

	/*
	 * ;
	 * arg0 - 队员名字 ;
	 * arg1 - 被邀请人的名?
	 */
	GCD_TEAM_FOLLOW_INVITE,							/* 队长邀请队员进入组队跟随模式 */

	/*
	 * ;
	 * arg0 - 队长名?
	 */
	GCD_TEAM_REFRESH_MEMBER,						/* 刷新队员信息 */

	/*
	 * ;
	 * arg0 - 队员的位置索引
	 */
	GCD_CHANGE_TEAM_ITEM_DISTRIB_MODE,				/* 改变分配模式 */

	/* 以下以后需要删除 */
	GCD_ON_TEAM_ENTER_MEMBER,						/* 有新队员入队 */

	GCD_SHOW_TEAM_YES_NO,							/* 打开同意组队窗口. */

	GCD_SHOW_TEAM_MEMBER_INFO,						/* 显示队员的详细信息. */

	GCD_SHOW_TEAM_MEMBER_NAME,						/* 在左边的队友列表框中显示队友的名字 */

	GCD_HIDE_ALL_PLAYER,							/* 自己离开队伍后, 隐藏所有的队友界面 */

	/* 队员的详细信息 */
	GCD_SHOW_TEAM_MEMBER_NICK,						/* 名字 */

	GCD_SHOW_TEAM_MEMBER_FAMILY,					/* 职业 */
	GCD_SHOW_TEAM_MEMBER_LEVEL,						/* 等级 */
	GCD_SHOW_TEAM_MEMBER_POS,						/* 位置 */
	GCD_SHOW_TEAM_MEMBER_HP,						/* hp */
	GCD_SHOW_TEAM_MEMBER_MP,						/* mp */
	GCD_SHOW_TEAM_MEMBER_ANGER,						/* 怒气 */
	GCD_SHOW_TEAM_MEMBER_DEAD_LINK,					/* 连线信息 */
	GCD_SHOW_TEAM_MEMBER_DEAD,						/* 死亡信息. */

	GCD_UPDATE_TEAM_MEMBER,							/* 更新队员信息 */

	/*
	 * arg0 - 队员序号（队伍中，自己不占用序号） ;
	 * arg1 - 队员 guid（用于取得该队员信息）
	 */
	GCD_SHOW_TEAM_FUNC_MENU_MEMBER,					/* 显示队员的功能菜单 */
	GCD_SHOW_TEAM_FUNC_MENU_LEADER,					/* 显示队长的功能菜单 */

	/*
	 * ;
	 * 组队相关事件 ;
	 * ;
	 * 登录相关 ;
	 */
	GCD_GAMELOGIN_SHOW_SYSTEM_INFO_CLOSE_NET,		/* 显示系统信息 */

	/*
	 * ;
	 * arg0 - 字符串 : 需要提示的系统信息. ;
	 * 点击确认按钮后断开网络。
	 */
	GCD_GAMELOGIN_SHOW_SYSTEM_INFO,					/* 显示系统信息 */

	/*
	 * ;
	 * arg0 - 字符串 : 需要提示的系统信息.
	 */
	GCD_GAMELOGIN_CLOSE_SYSTEM_INFO,				/* 显示队长的功能菜单 */

	GCD_GAMELOGIN_OPEN_SELECT_SERVER,				/* 关闭选择服务器界面 */

	GCD_GAMELOGIN_CLOSE_SELECT_SERVER,				/* 关闭选择服务器界面 */

	GCD_GAMELOGIN_OPEN_COUNT_INPUT,					/* 打开帐号输入界面 */
	GCD_GAMELOGIN_CLOSE_COUNT_INPUT,				/* 关闭帐号输入界面 */
	GCD_GAMELOGIN_NOTIFY_COUNT_INPUT,				/* 通知账号为输入状态 */

	GCD_GAMELOGIN_SHOW_SYSTEM_INFO_NO_BUTTON,		/* 显示系统信息, 不显示按钮 */

	/*
	 * ;
	 * arg0 - 字符串 : 需要提示的系统信息
	 */
	GCD_GAMELOGIN_OPEN_SELECT_CHARACTOR,			/* 显示人物选择界面 */

	GCD_GAMELOGIN_CLOSE_SELECT_CHARACTOR,			/* 关闭人物选择界面 */

	GCD_GAMELOGIN_OPEN_CREATE_CHARACTOR,			/* 显示人物创建界面 */

	GCD_GAMELOGIN_CLOSE_CREATE_CHARACTOR,			/* 关闭人物创建界面 */

	GCD_GAMELOGIN_REFRESH_ROLE_SELECT_CHARACTOR,	/* 刷新人物信息 */

	GCD_GAMELOGIN_CLOSE_BACK_GROUND,				/* 关闭背景界面 */

	GCD_GAMELOGIN_SYSTEM_INFO_YESNO,				/* 系统信息提示 yes_no 界面. */

	/*
	 * ;
	 * 参数0, 提示的字符串 ;
	 * 参数1, 对话框的类型 ;
	 * 0 -- 是否退出游戏 ;
	 * 1 -- 是否删除角色 ;
	 * 2 -- 是否更换帐?
	 */
	GCD_GAMELOGIN_SELECT_LOGIN_SERVER,				/* 选择一个login server */

	/*
	 * ;
	 * 参数0, iAreaIndex 区域索引 ;
	 * 参数1, iLoginServer 区域索引
	 */
	GCD_GAMELOGIN_CLEAR_ACCOUNT,					/* 清空帐号显示. */
	GCD_GAMELOGIN_SELECT_AREA,						/* 清空帐号显示. */
	GCD_GAMELOGIN_SELECT_LOGINSERVER,				/* 清空帐号显示. */
	GCD_GAMELOGIN_CREATE_CLEAR_NAME,				/* 清空创建角色的名字。 */
	GCD_GAMELOGIN_CREATE_ROLE_OK,					/* 创建角色成功。 */

	/*
	 * ;
	 * 登录相关 ;
	 */
	GCD_SUPERTOOLTIP,							/* Tooltips */

	/*
	 * | arg0 - 显示/隐藏 1,0 | arg1 - 类型 "skill", "lifeability", "item", "talent",
	 * "pet_skill" | arg2, arg3 - 鼠标位置 | ;
	 * 复活界面相
	 */
	GCD_RELIVE_SHOW,							/* 显示复活界面 */

	/*
	 * arg0 - 是否有复活的按钮 ;
	 * arg1 - 剩余时间
	 */
	GCD_RELIVE_HIDE,							/* 隐藏复活界面 */

	GCD_RELIVE_REFESH_TIME,						/* 刷新灵魂出窍的时间 */

	/* 显示时间 */
	GCD_RELIVE_ACTIVE,							/* 重新激活复活界面的按钮 */

	GCD_OBJECT_CARED_EVENT,						/* 某逻辑对象的某些发生改变 */

	/*
	 * | arg0 - Object的ID | arg1 - 类型 | distance: 距离发生改变 (arg2距离) |
	 * destroy: 被销毁 |
	 */
	GCD_UPDATE_MAP,								/* 更新地图 */
	GCD_UPDATE_NPC_MAP,							/* 更新NPC地图列表 */
	GCD_UPDATE_TRANSFER_MAP,					/* 更新传送地图列表 */

	GCD_UPDATE_SUPERTOOLTIP,
	GCD_UI_COMMAND,
	GCD_OTHERPLAYER_UPDATE_EQUIP,
	GCD_TOGLE_ONLINEUSER_EQUIP_ALL,
	GCD_VARIABLE_CHANGED,						/* 某个全局变量发生改变， */

	/* | arg0 - 变量名 | arg1 - 新的变量值 */
	GCD_TIME_UPDATE,							/* 由时间系统定时触发的事件 */
	GCD_FRIEND_INFO,							/* 打开好友详细信息 */

	GCD_UPDATE_TARGETPET_PAGE,					/* 打开targetpet ui */
	GCD_UPDATE_PETSKILLSTUDY,					/* 更新宠物技能学习界面 */

	GCD_UPDATE_PETINVITEFRIEND,					/* 更新宠物征友板界面 */
	GCD_REPLY_QUEST_PET,						/* 宠物刷新 */

	GCD_GUILD_CREATE,							/* 帮会创建事件 */
	GCD_GUILD_CREATE_CONFIRM,					/* 帮会创建确认事件 */
	GCD_GUILD_SHOW_LIST,						/* 显示帮会列表事件 */
	GCD_GUILD_SHOW_MEMBERINFO,					/* 显示自己帮会成员管理界面 */
	GCD_GUILD_TOGGLE,							/* 玩家按下帮会快捷键事件 */
	GCD_GUILD_UPDATE_MEMBERINFO,				/* 更新帮会成员的信息 */
	GCD_GUILD_SHOW_DETAILINFO,					/* 显示自己帮会详细信息界面 */
	GCD_GUILD_SHOW_APPOINTPOS,					/* 显示自己帮会可用职位界面 */
	GCD_GUILD_DESTORY_CONFIRM,					/* 删除帮会确认事件 */
	GCD_GUILD_QUIT_CONFIRM,						/* 退出帮会确认事件 */
	GCD_GUILD_FORCE_CLOSE,						/* 强制帮会相关界面关闭事件 */
	GCD_GUILD_INVITE_OBJECT,					/* 邀请对话框 */
	GCD_GUILD_NOTIFY_INTIVE,					/* 通知收到帮会邀请 */
	GCD_GUILD_INTIVE_CONFIRM,					/* 邀请确认 */
	GCD_GUILD_EVENT,							/* 帮会中唯一的事件，事件中有type来区分具体的事件，这样子所有的事件都统一处理
												 * add by wujianping */
	GCD_GUILD_MODIFY_TITLE,						/* 修改成员称号 */
	GCD_GUILD_MOVE_USER_TO_FAMILY,				/* 转移成员到一个家族，通知UI界面弹出一个可以输入家族名字的ui */
	GCD_GUILD_CREATE_FAMILY,					/* 创建家族 */
	GCD_GUILD_CREATE_FAMILY_CONFIRM,			/* 创建家族确认 */
	GCD_GUILD_DESTORY_FAMILY_CONFIRM,			/* 删除家族确认 */
	GCD_GUILD_LEVEL_UP,							/* 帮会升级事件 */
	GCD_GUILD_SHOW_LIST_CARENPC,				/* 打开帮会列表时关系NPC */
	GCD_INPUT_PASSWD_COMMAND,					/* 通过输入密码打开帮会界面 */

	GCD_CLOSE_QUEST_REPLY,						/* 关闭任务提交UI */
	GCD_TOGLE_TARGET_EQUIP_PAGE,				/* 开启查看对方角色装备界面 */
	GCD_CLOSE_TARGET_EQUIP,						/* 关闭。。。。。。。。。。 */
	GCD_TOGLE_TARGET_EQUIP_ALL,					/* 开启查看对方角色属性 */
	GCD_TOGLE_TARGET_EQUIP_ALL_FOR_AROUNDPLAYER,
	GCD_CLOSE_TARGET_EQUIP_ALL,					/* 关闭。。。。。。。。 */
	GCD_CHANGE_TARGET_EQUIP_ALL_PAGE,			/* 切换。。。。。。。。 */
	GCD_VIEW_RESOLUTION_CHANGED,				/* 屏幕分辨率变化时的通知消息 */
	GCD_CLOSE_SYNTHESIZE_ENCHASE,				/* 关闭合成UI和镶嵌UI */
	GCD_TOGGLE_PETLIST,							/* 打开和关闭宠物列表 */
	GCD_PET_FREE_CONFIRM,						/* 放生宠物确认 */

	/* 坐骑相关 */
	GCD_TOGLE_MOUNT_PAGE,						/* 打开/关闭骑宠界面 */
	GCD_OPEN_MOUNT_PAGE,						/* 打开骑宠界面 */
	GCD_CLOSE_MOUNT_PAGE,						/* 关闭骑宠界面 */
	GCD_MOUNT_ATTR_UPDATE,						/* 更新骑宠属性 */
	GCD_MOUNT_MATING_SUCCESS,					/* 交配成功事件 */
	GCD_MOUNT_COMPOSE_SUCCESS,					/* 合成成功事件 */
	GCD_MOUNT_COMPOSE_LOCKPASS_ITEM_UPDATE,		/* 更新合成物品 */
	GCD_MOUNT_COMPOSE_REPENT_ITEM_UPDATE,		/* 更新合成物品 */
	GCD_MOUNT_ATTR_LINK,						/* 坐骑连接显示 */
	GCD_MOUNT_HAPPINESS_UPDATE,					/* 骑乘快乐度更新 */
	GCD_MOUNT_TIMER_UPDATE,						/* 骑乘合成定时器更新 */
	GCD_MOUNT_TIMER_STOP,						/* 骑乘合成定时器停止 */
	GCD_MOUNT_SKILL_SLOT_NOT_ENOUGH,			/* 骑乘合成时技能糟不够 */

	GCD_TOGLE_TARGET_MOUNT_PAGE,				/* 打开或关闭目标坐骑界面 */
	GCD_TARGET_MOUNT_ATTR_UPDATE,				/* 更新目标坐骑属性 */

	GCD_TOGLE_MOUNT_STUDY_PAGE,					/* 打开或关闭骑宠学习界面 */
	GCD_MOUNT_STUDY_ITEM_UPDATE,				/* 更新骑宠学习物品 */

	GCD_TOGLE_MOUNT_FEED_PAGE,					/* 打开或关闭气冲喂养界面 */
	GCD_MOUNT_FEED_ITEM_UPDATE,					/* 更新骑宠喂养物品 */

	GCD_TOGLE_MOUNT_TRAIN_PAGE,					/* 打开或关闭骑宠驯养界面 */
	GCD_MOUNT_TRAIN_ITEM_UPDATE,				/* 更新驯养物品 */

	GCD_TOGLE_MOUNT_IDENTIFY_PAGE,				/* 打开或关闭骑宠鉴定界面 */

	GCD_TOGLE_MOUNT_MATING_PAGE,				/* 打开骑宠繁殖界面 */
	GCD_CLOSE_MOUNT_MATING_PAGE,				/* 关闭骑宠繁殖界面 */
	GCD_MY_MOUNT_MATING_LOCKED,					/* 自己的交配骑宠锁定 */
	GCD_OTHER_MOUNT_MATING_LOCKED,				/* 他人的交配骑宠锁定 */
	GCD_REQUEST_TOGLE_MOUNT_MATING_PAGE,		/* 申请开启繁殖界面 */
	GCD_GAIN_MATING_MOUNT,						/* 领取繁殖坐骑 */
	GCD_TOGLE_MOUNT_COMPOSE_PAGE,				/* 打开骑宠合成界面 */
	GCD_TOGLE_MOUNT_COMPOSE_PAGE2,				/* 打开骑宠合成第二个界面 */
	GCD_TOGLE_MOUNT_COMPOSE_START,				/* 打开骑宠合成,关闭其它骑乘界面 */
	GCD_CLOSE_MOUNT_COMPOSE_PAGE,				/* 关闭骑宠合成界面 */
	GCD_HORSE_PASSIVITY_SKILL_REPLACE_CONFIRM,	/* 骑乘被动技能替换 */
	GCD_HORSE_SKILL_UP_CONFIRM,					/* 骑乘技能升级 */
	GCD_HORSE_SKILL_REPLACE_CONFIRM,			/* 骑乘技能 */
	GCD_HORSE_SKILL_REPLACE_MULTI_CONFIRM,		/* 骑乘技能 */
	GCD_HORSE_TOCHILD_CONFIRM,					/* 骑乘还童 */

	GCD_OPEN_BUY_CONFIRM,						/* 打开商店买入确认界面 */
	GCD_OPEN_SALE_CONFIRM,						/* 打开商店卖出确认界面 */

	GCD_SEARCH_MASTER,						/* 找师傅 */
	GCD_SEARCH_PRENTICE,					/* 找徒弟 */
	GCD_REQUEST_MARRY,						/* 结婚 */

	/* 用户创建分组输入名称的事件 */
	GCD_FRIEND_CREATE_GROUP,

	/* 好友搜索结果 */
	GCD_OPEN_FRIEND_SEARCH_REASON,

	/* 添加好友新组 */
	GCD_ADD_GROUP,
	GCD_QUICK_CHANGCD_NAME,					/* 一键换装命名 */

	GCD_ITEM_LINK,							/* 物品链接 arg0：物品名称 */
	GCD_QUEST_LINK,							/* 任务连接 */
	GCD_HORSE_LINK,							/* 坐骑连接 */
	GCD_SKILL_LINK,							/* 技能连接 */
	GCD_QUEST_SUPER_TOOLTIP_SHOW,			/* 任务连接显示界面 */
	GCD_SKILL_SUPER_TOOLTIP_SHOW,			/* 技能连接显示界面 */

	GCD_TOGLE_MOUNT_CHILD_PAGE,				/* 打开或关闭骑宠还童界面 */
	GCD_MOUNT_CHILD_ITEM_UPDATE,			/* 更新骑宠还童物品 */

	/* 显示好友的详细信息 */
	GCD_SHOW_FRIEND_INFO,
	GCD_EQUIP_SWAPCARD_OPEN,				/* 打开装备牌型交换界面 */
	GCD_EQUIP_SWAPCARD_UPDATA,				/* 更新装备牌型交换界面 */
	GCD_EQUIP_SWAPCARD_SUCESS,				/* 装备牌型交换成功 */

	GCD_EQUIP_CHANGECARD_OPEN,				/* 打开装备牌型改造界面 */
	GCD_EQUIP_CHANGECARD_UPDATA,			/* 更新装备牌型改造界面 */
	GCD_EQUIP_CHANGECARD_SUCESS,			/* 装备牌型改造成功 */

	GCD_EQUIP_ALL_OPEN,						/* 打开个人装备 个人属性 个人称号 一键换装 骑乘属性 个人资料 */

	GCD_SHOW_TITLE,							/* 显示称号界面 */
	GCD_UPDATE_TITLE,						/* 更新称号界面 */

	GCD_PERSONAL_MESSAGE,					/* 人物消息 */
	GCD_SYSTEM_MESSAGE,						/* 系统消息 */
	GCD_PARALLEL_MESSAGE,					/* 水平消息 */

	GCD_SHOW_SYSTEM_PROMPT,					/* 系统信息提示图标 */

	/* GCD_SYSTEM_PROMPT_UPDATE, // 更新系统信息提示图标 */
	GCD_OPERATE_SYSTEM_PROMPT,
	GCD_SHOW_SUPERTOOLTIP_TITLE,			/* 显示称号提示 */
	GCD_SHOW_COMPARETOOLTIP,				/* 物品链接 // */
	GCD_SHOW_COMPARETOOLTIP_REPOS,			/* 物品链接重新定位 */
	GCD_UNITE_GF_SHOW,						/* 好友和帮会的联合 */
	GCD_MASTER_OR_PRENTICE,					/* 师徒 */

	/*
	 * 是否设置二级保护密码 ;
	 * ;
	 * GCD_MINORPASSWORD_OPEN_SET_PASSWORD_DLG, // 打开设置二级密码界面 ;
	 * GCD_MINORPASSWORD_OPEN_UNLOCK_PASSWORD_DLG, // 打开unlock密码界面。 ;
	 * GCD_MINORPASSWORD_OPEN_CHANGCD_PASSWORD_DLG, // 更改密码界面
	 */
	GCD_OPEN_SYSTEM_TIP_INFO_DLG,			/* 提示系统信息对话框。 */

	GCD_INPUT_PASSWORD_DLG,					/* 输入二级密码界面 */

	GCD_INPUT_SUPER_PW_DLG,					/* 输入超级密码界面 */

	GCD_INPUT_FIND_PLAYER_ITEM_DLG,				// 追踪符窗口


	/*
	 * ;
	 * 是否设置二级保护密码 ;
	 */
	GCD_RICH_SAFE_GUARD,					/* 保护范围界面 */
	GCD_RICH_SAFE_TIME,						/* 安全时限弹出界面 */
	GCD_UPDATE_RICH_SAFE_TIME,				/* 更新安全时限 */
	GCD_RICH_SET_PASSWORD,					/* 设置密码、修改密码界面 */
	GCD_RICH_MODIFY_PASSWORD,
	GCD_RICH_SETUP,							/* 财产保护功能设置界面 */
	GCD_OPEN_RICHES_PROTECT_FRAME,			/* 财产保护提示界面 */
	GCD_RICH_TEMP_CANCEL_PASSWORD,			/* 临时取消密码 */
	GCD_RICH_CANCEL_PASSWORD,				/* 取消密码 */
	GCD_RICH_CHECK_PASSWORD,				/* 检测输入密码 */
	GCD_RICH_SAFE_TIME_TIP,					/* 安全时间提示 */
	GCD_RICH_DELETE_PWD_TIME_TIP,			/* 删除密码保护的剩余时间上线提示 */

	/* temp 整和界面用， 等合到一个界面里就不用了 */
	GCD_TEMP_CLOSE_FRIEND,
	GCD_TEMP_CLOSE_GUILD,
	GCD_ADD_FRIEND,
	GCD_FRIEND_EVENT,
	GCD_FRIEND_CONFIRM_EVENT,
	GCD_EQUIP_ALL_CLOSE,					/* 关闭个人装备 个人属性 个人称号 一键换装 骑乘属性 个人资料 */
	GCD_AUTOREPLY_RECV_MSG,					/* 收到其他玩家发过来得聊天消息 */

	GCD_TOGLE_PLAYER_ATTR_PAGE,				/* 打开人物详细属性界面 */
	GCD_CLOSE_PLAYER_ATTR_PAGE,				/* 关闭人物详细属性界面 */
	GCD_TOGLE_PLAYER_ATTR2_PAGE,
	GCD_CLOSE_PLAYER_ATTR2_PAGE,
	GCD_OPEN_DAY_TIPS,						/* 打开每日提醒功能界面 */
	GCD_UPDATE_DATE_TIME,					/* 更新每日提醒日期和时间 */
	GCD_UPDATE_DAY_TIPS,					/* 更新每日提醒内容 */
	GCD_UPDATE_DAY_TIPS_DISPLAYLIST,		/* 更新每日提醒可显示列表 */
	GCD_UPDATE_CALENDAR,					/* 更新月历内容 */
	GCD_QUIT_UPDATE_CALENDAR,				/* 更新退出月历内容 */

	GCD_OPEN_TOP_LIST,						/* 打开排行榜界面 */
	GCD_UPDATE_TOP_LIST,					/* 更新排行榜界面 */

	/* arg0：为0表示填充排行榜名称为1表示填充排行榜数据 */
	GCD_LEVEL_TOP_LIST,						/* 等级排行榜 */
	GCD_MONEY_TOP_LIST,						/* 财富排行榜 */
	GCD_NO_TOPLIST_INFO,					/* 没有排行榜信息 */
	GCD_UPDATE_TOPLIST_PERSONINFO,			/* 更新排行榜个人信息 */

	GCD_OPEN_QUEST_SCOUT,					/* 打开任务跟踪界面 */
	GCD_UPDATE_QUEST_SCOUT,					/* 更新任务跟踪界面 */
	GCD_UPDATA_EQUIP_ALL_POS,				/* 更新6个界面位置 〈个人装备 个人属性 个人称号 一键换装 骑乘属性 个人资料〉 */

	GCD_COUNTRY_EVENT,						/* 国家中唯一的事件，事件中有type来区分具体的事件，这样子所有的事件都统一处理
											 * add by wujianping */
	GCD_COUNTRY_MANAGER_REQUEST_INFO,		/* 请求国家信息 */
	GCD_COUNTRY_MANAGER_INFO,				/* 国家信息 */
	GCD_COUNTRY_MANAGER_ADJUST_AUTH,		/* 国家官职调整 */
	GCD_INPUT_COUNTRY_DLG,					/* 输入国家官职 */
	GCD_COUNTRY_MANAGER_CREATE_KING,		/* 产生国王 */
	GCD_COUNTRY_KING_CREATE_CONFIRM,		/* 确认产生国王 */
	GCD_COUNTRY_MANAGER_KING_COLLECT,		/* 募捐 */

	GCD_SHOW_EQUIP_CONTEXMENU,				/* 显示装备右键菜单 */

	/*
	 * arg0 - 菜单类 ;
	 * arg1 - 鼠标位置_x ;
	 * arg2 - 鼠标位置_
	 */
	GCD_CLOSE_EQUIP_CONTEXMENU,
	GCD_FILL_TEAM_MEMBER,					/* 填充队员信息 */
	GCD_FILL_TEAM_INFO,						/* 填充队伍信息 */
	GCD_FILL_TEAMSEARCH_INFO,				/* 填充寻求组队信息 */

	GCD_GUILD_KICK_CONFIRM,					/* 帮会踢人确认 */

	GCD_MOUNT_FRIEND_SETUI_SHOW,			/* 骑乘征友设定界面 */
	GCD_MOUNT_FRIEND_SEARCHUI_SHOW,			/* 骑乘征友查询界面 */
	GCD_MOUNT_FRIEND_VIEWUI_SHOW,			/* 骑乘查看界面 */
	GCD_MOUNT_FRIEND_INITINFO,				/* 查看界面信息显示 */
	GCD_SAMECITY_PLAYER_UPDATEUI,			/* 同城玩家界面更新 */

	GCD_TOGLE_CHATQUERY,					/* [ ZG ] 聊天历史记录 */

	GCD_TOGLE_SUBTRAIN_PAGE,				/* 带练界面 */
	GCD_UPDATE_SUBTRAIN_PAGE,
	GCD_PK_MODE_CHANGED,					/* by soongxl */

	GCD_SUB_TRAIN_EXP_DLG,					/* 提取经验确认界面 */
	GCD_SUB_TRAIN_GETEXP_DLG,				/* 有经验未提取提示 */
	GCD_CLOSE_STALL_SALE,					/* 摆摊(卖) */
	GCD_STALL_SAVE_DLG,						/* 摆摊保存 */

	GCD_SHORTCUT_KEYDOWN,					/* !< 快捷键按下事件 */
	GCD_SHORTCUT_KEYUP,						/* !< 快捷键松开事件 */

	GCD_EXTENT_SHORTCUT,					/* !< 081103（齐亮）扩展快捷键事件 */
	GCD_SHORTCUT_RIGHTBAR,					/* !< 右侧快捷栏快捷键消息 */
	GCD_RIDE_EXTENT_SHORTCUT,				/* !< 骑乘快捷栏快捷键事件 */

	GCD_EXTEND_SHORTCUT_SHOW,				/* 扩展快捷栏 */

	GCD_GUAJI_SHOW,							/* 挂机界面 */
	GCD_GUAJI_UPDATE,
	GCD_TOGGLE_GUAJI,						/* 081105（齐亮）切换挂机开关 */

	GCD_DOUBLEACTION_REQUEST,				/* 双人动作请求 */

	GCD_OPEN_DONATEPUTOUT,					/* 发起募捐 [ ZG ] */
	GCD_OPEN_DONATE,						/* 提交募捐界面 [ ZG ] */
	GCD_COUNTRY_DELATE,						/* 弹劾界面 [ ZG ] */
	GCD_COUNTRY_VOTEON,						/* 公民投票 [ ZG ] */
	GCD_OTHER_TEAM_INFO,					/* 对方队伍信息界面 [ ZG ] */
	GCD_OTHER_TEAM_INFO_HIDE,				/* 比武界面关闭 */

	GCD_EXT_PACKAGE_OPEN,					/* by soongxl 扩展包打开 */
	GCD_DOUBLEACTION_CANCEL,				/* 取消双人动作 */

	GCD_SEND_MOOD_ANIM,						/* 发送表情动作 */

	GCD_TOGLE_TREASUREBOX_PAGE,				/* 打开宝箱界面 */
	GCD_CLOSE_TREASUREBOX_PAGE,				/* 关闭宝箱界面 */
	GCD_TREASUREBOX_UPDATE,					/* 更新宝箱界面 */
	GCD_TREASUREBOX_GETITEM_RESULT,			/* 获得物品的结果 */

	GCD_CREATE_BUS,							/* 创建bus */
	GCD_OPEN_BUS,							/* 打开bus */
	GCD_UPDATE_BUS,							/* 更新bus信息 */
	GCD_OPEN_CASHBUS,						/* 打开镖车 */

	GCD_OPEN_REGISTRATION,					/* 打开注册帐号界面 */
	GCD_UPDATA_EQUIP_REWORK,
	GCD_HIDE_TOOLTIP,
	GCD_UNLOCK_ITEM_ONLEAVE,				/* 解锁物品 */

	GCD_NAME_INPUT_ERROR,					/* 输入的名字不合法 */
	GCD_NAME_INPUT_EMPTY,					/* 输入的名字为空 */

	GCD_UPDATA_SELF_ATTR,					/* 更新属性 */
	GCD_LOGIN_KEYPRESS,						/* 登陆时键盘快捷键发送 */

	GCD_EFFECT_UI_OPEN,						/* 开启特效ui */
	GCD_EFFECT_UI_CLOSE,
	GCD_MENTAL_GAME_ASK_SIGNUP,				/* 答题 */
	GCD_MENTAL_GAME_INTERFACE,
	GCD_MENTAL_GAME_THINK,
	GCD_MENTAL_GAME_QUIZ,
	GCD_MENTAL_GAME_SCORE,					/* 刷新分数 */
	GCD_MENTAL_GAME_WENCAI,					/* 刷新文采 */
	GCD_MENTAL_GAME_SORTID,					/* 得到排名 */
	GCD_MENTAL_GAME_FINISHED,				/* 答题结束 */
	GCD_MENTAL_GAME_ANSWER_RESULT,			/* 答题结果 */
	GCD_MENTAL_GAME_CLOSE_INTERFACE,		/* 答题关闭界面 */
	GCD_MENTAL_GAME_BUY_ITEM,				/* 答题购买道具*/

	GCD_TOGLE_VALIDATE,						/* 打开|关闭防外挂认证窗口 */
	GCD_UPDATE_VALIDATE,					/* 更新防外挂认证窗口 */

	GCD_OPEN_CONVOYBUS,						/* 打开帮会运镖界面 */
	GCD_ASK_GUILDCONVOY,					/* 询问帮会运镖 */
	GCD_ASK_GUILDCONVOY_QUEST,				/* 询问是否接受帮会运镖任务 */

	GCD_TOGLE_GUILDCONVOY_INFOLIST,			/* 打开/关闭帮会运镖界面 */
	GCD_GUILDCONVOY_INFO_UPDATE,			/* 更新 */

	GCD_QUIT_GAME_CONFIRM,					/* 退出游戏确认 */
	GCD_RETURN_LOGIN_CONFIRM,
	GCD_QUIT_GAME_TIME_UPDATA,				/* 退出或返回登陆的时间更新 */

	GCD_RECONNECT_SERVER,					/* 重新连接服务器 */
	GCD_RECONNECT_SERVER_UPDATA,			/* 重新连接服务器的时间更新 */

	GCD_UPDATE_PING,						/* 更新游戏里的ping值 */
	GCD_THIRD_SHORTCUT_SHOW,				/* 第三快捷键 */
	GCD_UNIT_MONEYMODE,
	GCD_TOGLE_MOUNT_CLEARPOINT,				/* 打开/关闭骑乘洗点界面 */
	GCD_MOUNT_CLEARPOINT_ITEM_UPDATE,		/* 刷新物品 */

	GCD_ASK_INTO_BUS,						/* 请求进入战车 */
	GCD_INVITE_TO_BUS,						/* 邀请进入战车 */
	GCD_UPDATE_BUS_STATE,					/* 更新bus按钮状态 */

	GCD_OPEN_NPC_FINDPATH,					/* NPC自动寻路 */
	GCD_OPEN_WORLDMAP,						/* 世界地图 */
	GCD_OPEN_TRIP_MAP,						/* 传送门（马车夫传送） */

	GCD_WINDOW_SHOW,
	GCD_ESCAPE_HIDE_MESSAGE,				/* ESC统一隐藏消息 */

	GCD_OPEN_GOLD_EXCHANGE,					/* 金子兑换 */
	GCD_CLOSE_GOLD_EXCHANGE,				/* 金子兑换 */
	GCD_OPEN_GOLDCARD_EXCHANGE,				/* 金卡兑换 */
	GCD_CLOSE_GOLDCARD_EXCHANGE,			/* 金卡兑换 */

	GCD_OPEN_QUIZQUEST_INTERFACE,			/* 开启科举大富翁界面 */
	GCD_CLOSE_QUIZQUEST_INTERFACE,			/* 关闭科举大富翁界面 */
	GCD_FLASH_QUIZQUEST_TIME,				/* 刷新科举大富翁时间 */

	GCD_UPDATE_MIXTURE,						/* 更新道具合成面板（合成红绳等） */
	GCD_UPDATE_MIXTURE_SUCC,				/* 任务道具合成成功时 */
	GCD_UPDATE_MIXTURE_FAIL,				/* 任务道具合成完成但是未成功 */

	GCD_UNIT_FASHIONMODE,
	GCD_WINDOW_INPUT_KEY,					/* 单个窗口处理键盘事件 */
	GCD_WINDOW_INPUT_MOUSE,					/* 单个窗口处理鼠标事件 */

	GCD_ASK_COUNTRY_DESTROY_ISSUE,			/* 国王拉人 */

	GCD_ASK_GUILD_BATTLE,					/* 帮会战 */
	GCD_OPEN_BATTLE_INTERFACE,				/* 开启战场信息面板 */
	GCD_REFRESH_BATTLE_INFO,				/* 更新战场信息面板 */

	GCD_TOGLE_MOUNT_TF_PAGE,				/* 开启坐骑变身界面 */
	GCD_MOUNT_TF_ITEM_UPDATE,				/* 更新坐骑变身道具 */

	GCD_PLAY_IMPACT,						/* 播放一个特效 */
	GCD_RICH_MODIFY_PASSWORD_CLOSE,
	GCD_UNLOAD_OPERATOR_ITEM,
	GCD_TOGLE_VIEWSKILL_PAGE,				/* 开启/关闭技能查看界面 */
	GCD_VIEWSKILL_UPDATE,					/* 更新 */
	GCD_OPEN_VIEWSKILL_PAGE,
	GCD_SCENEMAP_FLASH_POINT,				/* 场景图闪烁某点 */
	GCD_SCENEMAP_COUNTRYFIGHTALARM,			/* 国家人员被杀地图显示信息 */
	GCD_SCENEMAP_COUNTRYFIGHTCLICK,			/* 国家人员被杀显示信息点击事件 */

	GCD_SUPERTOOLTIPCMPF,
	GCD_UPDATE_SUPERTOOLTIPCMPF,
	GCD_HIDE_TOOLTIPCMPF,
	GCD_SUPERTOOLTIPCMPS,
	GCD_UPDATE_SUPERTOOLTIPCMPS,
	GCD_HIDE_TOOLTIPCMPS,
	GCD_MIDDLE_BOTTOM_SCROLL_MESSAGE,		/* 中间下部的滚动框 */
	GCD_MIDDLE_BOTTOM_TEXT_MESSAGE,			/* 中间下部的文本框 */
	GCD_MIDDLE_ANIM_MESSAGE,				/* 中间的动画框 */

	GCD_LOCKKEYBOARD_INPUT,					/* 锁定、解锁键盘字母键，字母键事件 */

	GCD_GUARD_INFO,							/* 召唤兽信息 */
	GCD_GUARDER_CHANGED,
	GCD_OPEN_GUILD_BATTLE_STATISTIC,		/* 打开帮战统计界面 */
	GCD_CLOSE_GUILD_BATTLE_STATISTIC,		/* 关闭帮战统计界面 */
	GCD_UPDATE_GUILD_BATTLE_STATISTIC,		/* 更新帮战编译界面 */

	GCD_OPEN_EXERCISESCOUT,					/* 打开每日提示活动追踪 */
	GCD_CLOSE_EXERCISESCOUT,				/* 关闭每日提示活动追踪 */
	GCD_UPDATE_EXERCISESCOUT,				/* 更新每日提示活动追踪 */
	GCD_OPEN_DISMANTLE_EQUIP_FRAME,			/* 拆解确认 */
	GCD_OPEN_BIND_EQUIP_FRAME,				/* 绑定确认 */
	GCD_UNIT_Updata_BangGong,
	GCD_UNIT_Updata_ShengWang,
	GCD_OPEN_ACTIVE_SHOP_ITEM_FRAME,
	GCD_ASK_KING_BATTLE,					/* 国王争夺战 -CZG */
	GCD_DAMAGE_TIP,							/* 伤害提示 */
	GCD_ADVANCED_ROSE,						/* 高级玫瑰花特效（QL） */

	GCD_OPEN_CHECKOUT,						// 打开校验码界面
	GCD_OPEN_SCENE_ANSWER,					/* 开启副本问答 */
	GCD_SET_CHECKOUT,						// 设置参数
	GCD_REFURBISH_CHECKOUT,					/* 重刷校验码界面 */
	
	GCD_CAPTCHA_OPEN,						// 图形验证窗口
	GCD_CAPTCHA_TIME_EVENT,					// 

	GCD_OPEN_HELP,							/* 打开新手帮助界面 */
	GCD_OPEN_GOLD_BUTTON,
	GCD_CLOSE_GOLD_BUTTON,
	GCD_ENABLE_IB_SHOP_BUTTON,
	GCD_RICH_SAFE_GUARD_CLEAR,				/* 清理密保 */
	GCD_LEVEL_UP,							/* 人物升级 */

	GCD_POS_CARED_EVENT,					/* 跟位置相关的距离操作 */
	GCD_ENABLE_IB_SHOP_BUTTON_ANI,			/* 置现金商店按铵动画效果有效 */

	GCD_MOREKEY_VIEW_RESET,					/* 重置扩展快捷栏图标 */
	GCD_CHAR_RENAME,						/* 角色重命名 */
	GCD_UPDATE_RENAME_FLAG,					/* 更新重命名标记 */
	GCD_START_OPEN_BOX_STATE,				/* 进入开启宝箱状态 */

	GCD_ASK_COUNTRY_BATTLE_LITE,			/* 进入小国战 */
	GCD_ASK_COUNTRY_BATTLE_LITE_KINGISSUE,	/* 小国战拉人 */
	GCD_ASK_WORLDCUP_JOIN,					/* 帮会世界杯拉人 */

	GCD_UPDATE_SHORTCUT_KEY,				/* 更新快捷键 */

	/* 现金寄售相关 */
	GCD_OPEN_WORLD_IB_SHOP_SELL,			/* 打开寄售界面 */
	GCD_CLOSE_WORLD_IB_SHOP_SELL,			/* 关闭寄售界面 */
	GCD_OPEN_WORLD_IB_SHOP_BUY,				/* 打开购买界面 */
	GCD_OPEN_GOLD_SALE_MESSAGE,				/* 寄售确认对话框 */

	GCD_TIRED_SCENE_INFO,					/* 疲劳场景提示信息 */
	GCD_OPEN_STALL_BUY_CONFIRM,				/* 摆摊购买确认 */
	GCD_OPEN_SUPERTOOLTIPABILITY,			/* 打开提示 */
	GCD_CLOSE_SUPERTOOLTIPABILITY,			/* 关闭提示 */
	GCD_UNIT_UPDATA_GOODBADVALUE,			/* 刷新善恶值 */

	GCD_LOCKED_SHORTCUT,					/* 锁定快捷栏 */

	GCD_PASSWORD_CARD_OPEN,					/* 密保卡 */
	GCD_PASSWORD_CARD_CLOSE,
	GCD_PASSPOD,							/* 动态密保 */
	GCD_OPEN_DESTROY_TASK_ITEM,
	GCD_UPDATA_DESTROY_TASK_ITEM,
	GCD_DESTROY_TASK_ITEM,					/* 删除任务道具 */

	GCD_DIALOG_SHOW,						/* 开启对话 */
	GCD_DIALOG_UPDATE,						/* 更新对话 */
	GCD_DIALOG_SEND,						/* 发送对话 */
	GCD_DIALOG_OPEN_HISTORY,				/* 对话历史 */
	GCD_DIALOG_ITEM_LINK,					/* 物品超链接 */
	GCD_DIALOG_QUEST_LINK,					/* 任务超链接 */
	GCD_DIALOG_HORSE_LINK,					/* 马超链接 */
	GCD_DIALOG_SKILL_LINK,					/* 技能超链接 */
	GCD_OPEN_EQUIP_COLOR_CHANGE,			/* 打开黄装升紫装界面 */
	GCD_UPDATE_EQUIP_COLOR_CHANGE,			/* 更新黄装升紫装界面 */
	GCD_OPEN_EQUIP_PURPLE_REWORK,			/* 打开紫装洗属性界面 */
	GCD_UPDATE_EQUIP_PURPLE_REWORK,			/* 更新紫装洗属性界面 */
	GCD_UPDATE_EQUIP_COLOR_CHANGE_RESULT,	/* 黄装升紫装结果 */
	GCD_UPDATE_EQUIP_PURPLE_REWORK_RESULT,	/* 紫装洗属性结果 */

	GCD_DUEL_INVITE,						/* 决斗邀请 */

	GCD_OPEN_DELQUESTITEM,				/* 删除任务道具 */
	GCD_LOCKITEM,						/* 加锁 */
	GCD_UNLOCKITEM,						/* 解锁 */

	GCD_SHOW_SUPERTOOLTIP_ACTIVATION,	/* 任务属性tip界面 */

	GCD_TOGLE_AUTO_USE_DRUG,			/* 开启/关闭 自动吃药 */
	GCD_UPDATE_AUTO_USE_DRUG,			/* 更新 */

	GCD_OPEN_PAY_MESSAGEBOX,			/* 开启充值信息框 */

	GCD_UNIT_UPDATA_PVP2V2MARK,			/* 刷新英雄会积分 */

	/* 宝石合成和升级相关 */
	GCD_OPEN_GEM_LEVELUP,
	GCD_UPDATE_GEM_LEVELUP,
	GCD_GEM_LEVELUP_RESULT,
	GCD_OPEN_GEM_SYN,
	GCD_UPDATE_GEM_SYN,
	GCD_GEM_SYN_RESULT,

	/* 宝石拆卸 */
	GCD_OPEN_GEM_UNINST,
	GCD_GEM_UNINST_RESULT,

	/* 装备复制养成 */
	GCD_OPEN_EQUIP_COPY,
	GCD_UPDATE_EQUIP_COPY,
	GCD_EQUIP_COPY_RESULT,
	GCD_IBSHOP_OPEN,					/* 打开金币商店 */
	GCD_IBSHOP_CLOSE,					/* 关闭金币商店 */
	GCD_IBSHOP_UPDATE,					/* 更新金币商店 */
	GCD_OPEN_EQUIP_COPY_OTHER,

	GCD_OEQUIP_COPY_FRAME, //装备复制确认
	GCD_STUDY_SKILL_MSG ,	//学习9级技能确认

	GCD_ASK_IF_REGISTER_MIBAOKA,		/* 密保卡绑定*/
	GCD_EQUIP_WANFA_FRAME,		
	GCD_EQUIP_WANFA_FRAME_OK,
	GCD_OPEN_EQUIP_RECALL,
	GCD_EQUIP_RECALL_RESULT,
	GCD_UPDATE_EQUIP_RECALL,
	GCD_OPEN_ITEM_RECALL,
	GCD_UPDATE_ITEM_RECALL,
	GCD_TEAMMEMBER_CALL_UP,			//队员召集
	GCD_TRANSPOS_UPDATE,			//使用传送符传送

	GCD_SHOW_EQUIP_CHANGE_EFFECT,	// 显示换装时的特效

    GCD_SHOW_TOP_MESSAGEBOX,        // 显示顶级模态对话框
    GCD_EXIT_TIMER_UPDATE,          // 强制退回登录界面定时器更新事件

	GCD_OPEN_STOCK_FRAME,						/* 打开股票主界面 */
	GCD_UPDATE_STOCK_TOP_LIST,					/* 更新大盘信息 */
	GCD_UPDATE_ACC_MONEY,						/* 更新股票账户余额 */
	GCD_UPDATE_STOCK_RECPRD,					/* 更新股票交易历史记录 */
	GCD_UPDATE_STOCK_MARKET,					/* 更新股票上架列表 */
	GCD_OPEN_STOCK_BUY_SURE_FRAME,				/* 打开股票交易确认框"*/
	GCD_NEW_PLAYER_UI_TIPS,						/* 新手UI界面提示*/
	GCD_OPEN_1LEVEL_REMIND_FRAME,				/*打开一级提醒框*/
	GCD_TRANSPOS_SET_FRAME,							/*传送符定位确认*/
	
	//蓝属性吸收
	GCD_OPEN_BULL_IN,					
	GCD_UPDATE_BULL_IN,
	GCD_BULL_IN_RESULT,
	//蓝属性附加
	GCD_OPEN_BULL_ADD,					
	GCD_UPDATE_BULL_ADD,
	GCD_BULL_ADD_RESULT,

	GCD_UPDATE_LOGIN_SAFE_INFO,		// 显示登录密保信息
	GCD_TOGLE_SAFE_SET,				// 游戏内的密保设置
	GCD_SHOW_SAFE_DETAIL_INFO,		// 显示密保详细信息

	GCD_OPEN_AWARD_FRAME,			// 打开领奖对话框

	GCD_OPEN_EQUIPPRODUCE,		// 打开打造装备对话框
	GCD_CLOSE_EQUIPPRODUCE,		// 关闭打造装备对话框
	GCD_ABILITY_COOLDOWN_TIME_ENENT,	//生活技能冷却
	GCD_ABILITY_COOLDOWN_ADD_TIMER,		//生活技能冷却
	GCD_RETURN_SELECT_ROLE,				//返回登陆界面

    GCD_OPEN_PROFESSION_SWITCH_UI,      // （2010-03-24：ql）打开职业转换界面
    GCD_ADD_PROFESSION_SWITCH_ITEM,     // （2010-03-26：ql）添加职业转换物品到转换界面

	GCD_OPEN_EQUIPSWITCH,		// 打开转化装备界面
	GCD_UPDATE_EQUIPSWITCH,		// 更新转化装备界面
	GCD_CLOSE_EQUIPSWITCH,		// 关闭转化装备界面

	GCD_OPEN_BLUE_INTENSIFY,	//打开蓝属性强化界面
	GCD_UPDATE_BLUE_INTENSIFY,	//更新蓝属性强化界面
	GCD_UPDATE_BLUE_INTENSIFY_ATTR,	//更新蓝属性强化界面中的蓝属性值
	GCD_CLOSE_BLUE_INTENSIFY,	//关闭蓝属性强化界面

	GCD_OPEN_BLUE_RESET,		//打开蓝属性还童界面
	GCD_UPDATE_BLUE_RESET,		//更新蓝属性还童界面
	GCD_UPDATE_BLUE_RESET_ATTR,	//更新蓝属性还童界面中的蓝属性值
	GCD_CLOSE_BLUE_RESET,		//关闭蓝属性还童界面

	GCD_KING_ZHAOJI, //国王发布召集令
	GCD_UPDATE_GUILD_LAIRD_INFO,//更新帮会据点信息

	GCD_STALL_ITEM_BUY,			// 摆摊物品购买
	GCD_IB_STALL_ITEM_BUY,

	GCD_STALL_PET_BUY,			// 摆摊骑乘购买
	GCD_IB_STALL_PET_BUY,

	GCD_SHOW_LOAD_BACKDROP,		// 显示进度条
	GCD_UPDATE_LOAD_PROGRESS,	// 更新进度条

	GCD_UPDATE_BATTLE_MAP,		// 更新战场地图

	GCD_CAPSLOCK_KEYDOWN,		//  CapsLock键按下事件

	GCD_UNIT_MOVE_MOVE,			// 移动模式

    GCD_COUNTRY_PRECONTRACT_OPEN,   // 打开国务预约界面

	GCD_GAMELOGIN_OPEN_VIEW_SETUP,	// 打开登录界面的显示设置界面
	GCD_GAMELOGIN_CLOSE_VIEW_SETUP,	// 关闭登录界面的显示设置界面
	
	GCD_OPEN_WORLD_DIRECTORY,		// 打开江湖指南
	GCD_UPDATE_WORLD_DIRECTORY,		// 更新江湖指南

	GCD_OPEN_CHANGE_APPEARANCE,		//打开更换形象
	GCD_UPDATE_CHAR_CHANGE_APPEARACE_RESULT,  //更换形象结果

	GCD_TO_OPEN_SHOP,//打开NPC商店

	GCD_OPEN_SELFGIFT,	//打开天赋界面
	GCD_CLOSE_SELFGIFT,	//关闭天赋界面

	GCD_CLOSE_SCENE_TRANS,	// 关闭场景传送幕布

	GCD_OPEN_SELF_GIFT,		// 开启个人天赋界面
	GCD_UPDATE_SELF_GIFT,	// 更新个人天赋界面

	GCD_OPEN_GUILD_GIFT,	// 开启帮会天赋界面
	GCD_UPDATE_GUILD_GIFT,	// 更新帮会天赋界面

	GCD_OPEN_BLUE_SYN,	 // 打开护身符补色
	GCD_UPDATE_BLUE_SYN, // 更新护身符补色
	GCD_CLOSE_BLUE_SYN,	 // 关闭护身符补色
	GCD_BLUE_SYN_RESULT, //护身符补色结果

	GCD_GUILD_SKILL_GUILD_LEVEL_UP,
	GCD_GUILD_SKILL_GUILD_EXP,
	GCD_GUILD_SKILL_GUILD_MONEY,
	GCD_GUILD_SKILL_CHAR_INHERENCE_LEVEL,
	GCD_GUILD_SKILL_CHAR_MONEY,
	GCD_GUILD_SKILL_CHAR_BANGGONG,
	GCD_GUILD_SKILL_CHAR_SHENGWANG,
	GCD_GUILD_SKILL_CHAR_WEIWANG,
	GCD_GUILD_SKILL_CHAR_ITEM,

	GCD_OPEN_SUIT_DA_XING,//打开时装打星

	GCD_GAMELOGIN_ENTER_SUCCEED,	// 登录进入成功

	GCD_TO_OPEN_QINGJIAN,	// 增加朝廷请柬与江湖请柬的互斥与互斥提示

	GCD_OPEN_BALANCE_GIFT,	// 平衡天赋
	GCD_UPDATE_BALANCE_GIFT,

	GCD_OPEN_NEW_EQUIPPRODUCE,   //打开橙装打造
	GCD_UPDATE_NEW_EQUIPPRODUCE, //更新橙装打造
	GCD_CLOSE_NEW_EQUIPPRODUCE,  //关闭橙装打造
	GCD_NEW_EQUIPPRODUCE_RESULT, //橙装打造结果
	
	GCD_OPEN_EQUIP_CONST_BIND,          //打开星座装备界面
	GCD_UPDATE_EQUIP_CONST_BIND,        //更新星装铭刻界面
	GCD_UPDATE_EQUIP_CONST_BIND_RESULT, //更新星座铭刻结果

    GCD_OPEN_INH_ATTACK,                // 打开天赋专攻界面
    GCD_OPEN_INH_DEFEND,                // 打开天赋专防界面

    GCD_UPDATE_INH_ATTACK,              // 更新专攻信息
    GCD_UPDATE_INH_DEFEND,              // 更新专防信息
    GCD_INH_ATTACK_RESET,               // 专攻重置确认
    
    GCD_UNIT_BATTLEHONOUR,	// 战场荣誉

    GCD_INH_ATTACK_CONFIRM,             // 专攻天赋点数分配确认

	GCD_OPEN_HONOR_BIND,		//荣誉铭刻
	GCD_GUILD_SEND_MAIL,		//群发邮件

	GCD_DRAG_SHOP_ITEM_TO_BAG,	/* 将商店的物品搬动到背包 */

	GCD_OPEN_XINNIAN,			// 打开新年字符提交

	GCD_AGREE_COUNTRY_COLLEAGUE_YES_NO_TO_ACQUIRE, //需要国王确认是否需要结盟
	GCD_AGREE_COUNTRY_COLLEAGUE_YES_NO,			   //国王同意结盟
	

	GCD_OPEN_GUILD_BUSSKILL_STUDY,		/* 打开帮会神兽技能研究界面 */
	GCD_UPDATE_GUILD_BUSKILL,			/* 更新帮会神兽技能研究界面 */
	GCD_UPDATE_GUILD_BUSSKILL_TOOLBAR,	/* 更新帮会神兽技能快捷栏 */

    GCD_DAILIAN_CONFIRM,                // 打开代炼确认消息框
    GCD_WUTING_MANAGEMENT,              // 舞厅托管
    GCD_WUTING_PRECONTRACT,             // 舞厅预约

};	/* define */

struct sCommand;
typedef void (__stdcall *HANDLE_COMMAND_FUNC) (const sCommand *pCommand, uint32 dwOwnerData);

struct sCommandData
{
	GAME_COMMAND_ID										idCommand;		/* 事件定义枚举 */
	LPCTSTR												szCommand;		/* 字符串事件描述 */
	BOOL												bDelayProcess;	/* 延缓处理，放入慢速队列 */
	std::list<std::pair<HANDLE_COMMAND_FUNC, uint32> >	FuncNotifyList;
};

struct sCommand
{
	sCommandData		*m_pCommandData;
	std::vector<STRING> m_ValueVector;

	bool operator == (const sCommand &other) const
	{
		if(other.m_pCommandData != m_pCommandData) return false;
		if(other.m_ValueVector.size() != m_ValueVector.size()) return false;

		for(auto i = 0; i < m_ValueVector.size(); i++)
		{
			if(m_ValueVector[i] != other.m_ValueVector[i]) return false;
		}
		return true;
	}
};
#endif /* _GAME_COMMAND_DEFINE_H_ */

/*
 * 修改记录： 080305 GCD_GUILD_INVITE_OBJECT 080306 GCD_GUILD_NOTIFY_INTIVE
 * GCD_GUILD_INTIVE_CONFIRM GCD_GUILD_MODIFY_TITLE 080308 GCD_GUILD_CREATE_FAMILY
 * GCD_GUILD_CREATE_FAMILY_CONFIRM GCD_GUILD_DESTORY_FAMILY_CONFIRM 080314
 * GCD_OPEN_FRIEND_SEARCH 080318 GCD_FRIEND_CREATE_GROUP 080319
 * GCD_OPEN_FRIEND_SEARCH_REASON 080320 GCD_OPEN_BUY_CONFIRM 080320
 * GCD_OPEN_SALE_CONFIRM 080324 GCD_QUICK_CHANGCD_NAME 080325 GCD_ADD_GROUP 080327
 * GCD_ITEM_LINK 080331 GCD_SHOW_TITLE GCD_UPDATE_TITLE 080402
 * GCD_SHOW_FRIEND_INFO 080407 GCD_PERSONAL_MESSAGE // 人物消息 GCD_SYSTEM_MESSAGE
 * // 系统消息 GCD_SHOW_SYSTEM_PROMPT 080410 GCD_SHOW_SUPERTOOLTIP_TITLE, //
 * 显示称号提示 GCD_RICH_SAFE_GUARD, // 保护范围界面 GCD_RICH_SAFE_TIME, //
 * 安全时限弹出界面 GCD_RICH_SET_PASSWORD, // 设置密码、修改密码界面
 * GCD_RICH_SETUP, // 财产保护功能设置界面 GCD_UNITE_GF_SHOW 080418
 * GCD_INPUT_PASSWD_COMMAND 080331 GCD_OPEN_DAY_TIPS GCD_UPDATE_DAYTIPS_TIME
 * GCD_UPDATE_DAY_TIPS GCD_UPDATE_CALENDAR GCD_OPEN_TOP_LIST 080410
 * GCD_UPDATE_TOP_LIST 080417 GCD_OPEN_QUEST_SCOUT GCD_UPDATE_QUEST_SCOUT
 * 080331 GCD_OPEN_DAY_TIPS GCD_UPDATE_DAYTIPS_TIME GCD_UPDATE_DAY_TIPS
 * GCD_UPDATE_CALENDAR GCD_OPEN_TOP_LIST 080410 GCD_UPDATE_TOP_LIST 080417
 * GCD_OPEN_QUEST_SCOUT GCD_UPDATE_QUEST_SCOUT 080421 GCD_OPEN_BANK_EVENT
 * GCD_QUEST_INPUT_PASSWD_COMMAND GCD_PACKET_OPEN_SALE GCD_COUNTRY_MANAGER_INFO,
 * // 国家信息 GCD_COUNTRY_MANAGER_ADJUST_AUTH, // 国家官职调整 080422
 * GCD_INPUT_COUNTRY_DLG GCD_COUNTRY_KING_CREATE_CONFIRM 080425
 * GCD_COUNTRY_MANAGER_CREATE_KING GCD_COUNTRY_MANAGER_REQUEST_INFO 080516
 * GCD_FILL_TEAM_MEMBER, // 填充队员信息 GCD_FILL_TEAM_INFO, // 填充队伍信息
 * 080519 GCD_GUILD_KICK_CONFIRM, // 帮会踢人确认 080521 GCD_KEYBOARD_SET_KEY, //
 * 设置键值 080522 GCD_KEYBOARD_SET_REPEAT GCD_KEYBOARD_SWAP_KEY
 * GCD_EXTEND_SHORTCUT_SHOW, // 扩展快捷栏 GCD_GUAJI_SHOW, // 挂机界面 080520
 * GCD_MOUNT_FRIEND_SETUI_SHOW //骑乘征友设定界面事件 080521
 * GCD_QUESTLOG_AUTO_FIND_PATH, // 自动寻路和与NPC对话 080603 GCD_CHAT_INPUT_STATE
 * // 聊天输入的状态 080606 GCD_SCENE_NAME_TIP 080711 GCD_NAME_INPUT_ERROR, //
 * 输入的名字不合法 GCD_NAME_INPUT_EMPTY, // 输入的名字为空 080721
 * GCD_RICH_SAFE_TIME_TIP, // 安全时间提示 080801 GCD_TOGLE_VALIDATE //
 * 打开|关闭防外挂认证窗口 GCD_UPDATE_VALIDATE // 更新防外挂认证窗口 080805
 * GCD_QUIT_GAME_CONFIRM // 退出游戏确认 080812 GCD_SEND_MOOD_ANIM, //
 * 发送表情动作 GCD_PARALLEL_MESSAGE, // 水平消息 081010 GCD_QUICK_UPDATE_FRAME //
 * 重绘一健换装界面 GCD_RICH_SAFE_GUARD_CLEAR //清理密保
 */
