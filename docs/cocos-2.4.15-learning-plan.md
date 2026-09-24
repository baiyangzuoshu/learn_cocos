# 基于 Cocos Creator 2.4.15 源码的岗位学习计划

目标是完成一个可展示的项目：**结构化关卡描述 → 校验 → 编辑器生成或预览 → 构建资源 → 运行时加载与替换 → 失败回退**。计划按每周约 8–10 小时、共 10 周安排；每个阶段都有独立文档，可以按完成标准推进，不必机械地按日期切换。

| 周次 | 阶段 | 本阶段交付 |
| --- | --- | --- |
| 1–2 | [阶段一：引擎启动、场景与组件生命周期](stage-01-engine-and-scene.md) | 帧循环和场景切换调用图；生命周期实验 |
| 3–4 | [阶段二：资源管线与运行时动态内容](stage-02-assets-and-runtime.md) | 加载/释放流程图；双关卡切换 Demo |
| 5–6 | [阶段三：编辑器扩展与资源校验](stage-03-editor-automation.md) | 结构化关卡校验与批量导入插件 |
| 7–8 | [阶段四：C++、JSB 与渲染](stage-04-native-and-rendering.md) | 跨语言及渲染链路图；一次可复现的测量 |
| 9–10 | [阶段五：集成、AI 内容接入与作品集](stage-05-integration-and-portfolio.md) | 完整项目、错误回退、README 与演示录屏 |

## 源码技能

各技能的 `SKILL.md` 说明适用问题和分析方法；`references/flow.md` 保存本地 2.4.15 源码入口与已核对的分支。提问时可直接点名技能，例如“用 `cocos-2415-assets` 追踪场景切换时的资源释放”。

- [启动与场景生命周期](../.agents/skills/cocos-2415-startup/SKILL.md)
- [资源管线与释放](../.agents/skills/cocos-2415-assets/SKILL.md)
- [渲染管线](../.agents/skills/cocos-2415-rendering/SKILL.md)
- [编辑器扩展](../.agents/skills/cocos-2415-editor/SKILL.md)
- [JSB 与原生层](../.agents/skills/cocos-2415-native/SKILL.md)

## 学习方法

每次从公开入口追到内部管理器和数据对象，画出实际调用路径，再用最小项目验证。笔记应区分源码事实、实验结果和推断；尤其注意 `CC_EDITOR`、`CC_PREVIEW`、`CC_JSB`、`CC_NATIVERENDERER` 对行为的影响。每阶段完成独立文档中的练习与验收后，再进入下一阶段。

仓库根目录的 `2.4.15/` 是 Creator 安装目录，包含 JS 引擎、`cocos2d-x` 原生源码和扩展模板；部分编辑器实现封装在 `resources/app.asar`。实验应放在独立 Creator 项目中。岗位提到的 PinK 编辑器及 WebGPU、Vulkan、Metal，需要后续用目标岗位实际采用的版本补充学习。

**开始位置：**打开[阶段一](stage-01-engine-and-scene.md)，先完成第 1 周的双场景生命周期实验。
