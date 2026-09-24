# 已核对的源码地图：启动与场景生命周期

`2.4.15/resources/engine/package.json` 标明版本为 `2.4.15`。下述路径相对于 `2.4.15/resources/engine/`。这些是源码定位信息，不代表各平台分支会同时执行。

## 启动与帧循环

- `index.js` 创建全局 `cc`，加载 `predefine`、兼容层和 `cocos2d/core/predefine`；编辑器主进程会跳过 `require('./cocos2d')`，随后加载 `extends.js`。
- `extends.js` 加载核心模块和动画模块；`CC_EDITOR && Editor.isMainProcess` 分支加载编辑器资源类，另一分支加载运行时模块。`modules.json` 列出构建使用的可选模块入口及依赖。
- `cocos2d/core/CCGame.js`：`_initEngine()` 初始化引擎；`_runMainLoop()` 根据分支进入 `cc.director.mainLoop()` 或 `director.mainLoop(now)`。引用精确顺序前需检查对应分支。
- `cocos2d/core/CCDirector.js`：`mainLoop` 分别实现编辑器与非编辑器路径。两者都会调度组件阶段；非编辑器路径还会在更新后执行延迟销毁。不要把两条路径合并成一条时间线。
- `cocos2d/core/component-scheduler.js`：`startPhase()`、`updatePhase(dt)`、`lateUpdatePhase(dt)` 负责组件调度。

## 场景切换

- `cocos2d/core/CCDirector.js`：`loadScene(sceneName, ...)` 查找包含场景元数据的 Bundle，调用 `bundle.loadScene()`；成功后进入 `runSceneImmediate()`。
- `runSceneImmediate()` 接收 `Scene` 或 `SceneAsset`，调用 `scene._load()`、重新挂接常驻节点，在非编辑器环境执行 `_autoRelease(oldScene, scene, ...)`，销毁旧场景并激活新场景。回调和事件的精确顺序应以此函数为准。
- `cocos2d/core/CCScene.js`：`_activate(active)` 调用 `cc.director._nodeActivator.activateNode(this, active)`。
- `cocos2d/core/node-activator.js`：`activateNode()` 遍历节点并安排组件生命周期回调。

常用检索：`rg -n 'mainLoop|_initEngine|_runMainLoop|loadScene|runSceneImmediate' 2.4.15/resources/engine/cocos2d/core` 和 `rg -n 'activateNode|startPhase|updatePhase|lateUpdatePhase' 2.4.15/resources/engine/cocos2d/core`。
