# 阶段二：资源管线与运行时动态内容（第 3–4 周）

## 本阶段目标

追踪 Bundle、资源请求、下载、解析、依赖、缓存和释放；做出可反复切换关卡的运行时实验。预计投入 16–20 小时。延续[阶段一](stage-01-engine-and-scene.md)的双场景项目。

## 源码入口与阅读顺序

1. [CCAssetManager.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/CCAssetManager.js) 看公开入口与管线装配；[bundle.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/bundle.js) 看资源及场景的 Bundle 入口。
2. [pipeline.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/pipeline.js)、[task.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/task.js)、[preprocess.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/preprocess.js)、[fetch.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/fetch.js)、[load.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/load.js) 看请求如何逐阶段处理。
3. [downloader.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/downloader.js)、[parser.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/parser.js)、[depend-util.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/depend-util.js)、[shared.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/shared.js) 看格式扩展、依赖和共享缓存。
4. [releaseManager.js](../2.4.15/resources/engine/cocos2d/core/asset-manager/releaseManager.js) 与 [CCDirector.js](../2.4.15/resources/engine/cocos2d/core/CCDirector.js) 的 `runSceneImmediate()` 一起读，追踪旧场景释放。

## 第 3 周：加载链路

1. 把两个关卡和各自资源组织为可加载的 Bundle；记录 Bundle、场景名、资源路径及它们的依赖。
2. 从 `Bundle.loadScene()` 追踪一次成功请求，画出“请求描述 → 定位 → 获取 → 解析 → 依赖 → 可用资源”的流程。不要把预加载、下载和实例化画成同一个步骤。
3. 分别运行首次加载、再次加载、错误路径、缺失资源四种情况，记录完成回调、错误信息及缓存状态。
4. 选一种资源，说明使用路径、UUID 和远程 URL 请求时，处理入口有何区别；只陈述实际跑通的情况。

## 第 4 周：释放与动态切换

1. A、B 两个关卡反复切换 20 次；记录每次切换后的活动节点数、已加载资源数及可观察的内存变化。
2. 对照 `ReleaseManager._autoRelease()`，解释旧场景资源为何保留或释放。特别检查被持久节点、其他场景或手动引用仍使用的资源。
3. 用一份关卡配置改变敌人/道具数量，实现无需修改引擎代码的动态内容更新。
4. 制造一次加载失败，要求当前关卡仍可继续使用，并把失败原因输出到日志。

本阶段的“动态加载”是 Bundle、配置和对象层的实验。原生 `AssetsManagerEx` 更新和整个应用热更新属于其他层次，笔记中应分别命名。

## 交付与完成标准

- 一张加载图和一张释放图，节点能对应到具体源码函数。
- A/B 关卡切换 Demo、四种加载情形的日志，以及 20 次切换的记录。
- 能解释“已下载”“已解析”“已实例化”“可释放”的区别，并指出一次失败发生在哪个阶段。
- 无用资源没有随切换次数持续累积；若有增长，记录复现步骤与尚未定位的引用。

完成后进入[阶段三：编辑器自动化](stage-03-editor-automation.md)。
