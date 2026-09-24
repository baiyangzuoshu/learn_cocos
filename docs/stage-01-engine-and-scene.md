# 阶段一：引擎启动、场景与组件生命周期（第 1–2 周）

## 本阶段目标

能从入口追到每帧调度和场景切换，解释 `Scene`、`Node`、`Component` 的职责，并用一个最小项目验证组件生命周期。预计投入 16–20 小时。

## 源码入口与阅读顺序

1. [package.json](../2.4.15/resources/engine/package.json) 确认引擎版本；[index.js](../2.4.15/resources/engine/index.js)、[extends.js](../2.4.15/resources/engine/extends.js)、[modules.json](../2.4.15/resources/engine/modules.json) 了解入口、编辑器分支和模块装配。
2. [CCGame.js](../2.4.15/resources/engine/cocos2d/core/CCGame.js) 从 `_initEngine()` 追到主循环；[CCDirector.js](../2.4.15/resources/engine/cocos2d/core/CCDirector.js) 阅读 `mainLoop()`、`loadScene()` 和 `runSceneImmediate()`。
3. [CCScene.js](../2.4.15/resources/engine/cocos2d/core/CCScene.js)、[CCNode.js](../2.4.15/resources/engine/cocos2d/core/CCNode.js)、[CCComponent.js](../2.4.15/resources/engine/cocos2d/core/components/CCComponent.js) 了解数据与层级。
4. [node-activator.js](../2.4.15/resources/engine/cocos2d/core/node-activator.js) 与 [component-scheduler.js](../2.4.15/resources/engine/cocos2d/core/component-scheduler.js) 追踪激活、`start`、`update` 和 `lateUpdate`。

阅读时分别标出 `CC_EDITOR`、`CC_PREVIEW`、`CC_JSB`、`CC_NATIVERENDERER` 分支。编辑器里观察到的行为应在预览或运行时再次验证。

## 第 1 周：建立调用图

1. 新建独立的 Creator 2.4.15 练习项目，准备两个最简场景。
2. 给一个节点挂上日志组件，记录 `onLoad`、`onEnable`、`start`、`update`、`onDisable`、`onDestroy`。只记录前几帧的 `update`，避免日志淹没结果。
3. 在源码中画出“`CCGame` 初始化 → `CCDirector.mainLoop` → 组件调度 → 渲染”的一页调用图。
4. 从 `CCDirector.loadScene()` 追到 `Bundle.loadScene()`、`runSceneImmediate()`、`CCScene._activate()`、`NodeActivator.activateNode()`，在图中注明异步加载和同步激活的边界。
5. 运行项目并切换场景，比较日志与调用图；记录至少一个原先没有预料到的顺序或分支。

## 第 2 周：解释对象生命周期

1. 在两个场景中分别创建、禁用、重新启用和销毁节点，记录组件回调。
2. 追踪节点层级变化如何触发激活或停用；确认销毁是否延迟到本帧的安全时机。
3. 比较首次进入场景与再次进入场景的日志，解释对象是重新创建还是沿用。
4. 整理一份简短说明：`Scene`、`Node`、`Component` 各保存什么；`Director` 和两个调度器各负责什么。

## 交付与完成标准

- 一个能复现生命周期日志的练习项目和运行步骤。
- 两张不超过一页的调用图：帧循环、场景切换。
- 一份源码笔记，标注实际入口和关键分支；能解释 `onLoad`、`start`、`update`、`onDestroy` 在实验中的时序。
- 能回答：场景数据何时被激活？新组件何时进入调度？旧节点何时真正销毁？

完成后进入[阶段二：资源管线](stage-02-assets-and-runtime.md)。
