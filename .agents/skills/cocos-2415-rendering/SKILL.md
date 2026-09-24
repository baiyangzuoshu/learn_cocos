---
name: cocos-2415-rendering
description: 追踪本工作区 Cocos Creator 2.4.15 从节点到绘制的流程、RenderFlow、合批及 WebGL、Canvas、原生渲染分支。
---

# Cocos Creator 2.4.15 渲染管线

先判断问题属于 WebGL、Canvas，还是 `CC_JSB && CC_NATIVERENDERER`。读取[渲染分支图](references/flow.md)后，只沿相关分支从节点或渲染组件追到提交与 gfx 设备。区分渲染数据生成、合批、材质状态和绘制提交。

讨论正确性或性能时，检查相关源码函数，并在指定平台做最小复现或测量。Web 预览结果不能证明原生行为；不要把这份 2.4.15 渲染器描述成 WebGPU、Vulkan 或 Metal 的实现。

安装快照的工作边界见 `2.4.15/AGENTS.md`。仅在指导学习练习时读取[阶段四学习计划](../../../docs/stage-04-native-and-rendering.md)。关键行为经 JSB 进入 C++ 时，同时使用原生层技能。
