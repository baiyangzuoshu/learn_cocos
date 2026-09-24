# 已核对的源码地图：资源加载与释放

除非另有说明，下述路径相对于 `2.4.15/resources/engine/cocos2d/core/asset-manager/`。此图用于定位实现模块；实际路径会因请求类型、缓存状态和平台而异。

## 入口与管线

- `CCAssetManager.js`：构造函数设置 `pipeline = pipeline.append(preprocess).append(load)` 和 `fetchPipeline = fetchPipeline.append(preprocess).append(fetch)`。公开入口包括 `loadAny()`、`preloadAny()`、`loadBundle()`、`releaseAsset()`。
- `bundle.js`：`Bundle.loadScene()` 与 `preloadScene()` 通过 Bundle 元数据解析场景名。查找或归属不明时检查 `config.js`。
- `pipeline.js` 与 `task.js`：分阶段异步执行；修改管线前，先确认错误发生在哪个阶段。
- `preprocess.js`、`fetch.js`、`load.js`：分别参与请求预处理、获取与加载。预加载完成不代表资源已解析并实例化。
- `downloader.js` 与 `parser.js`：都提供 `register(type, handler)` 扩展接口。文件已有数据却无法得到可用资源时，继续查 `factory.js` 和 `deserialize.js`。
- `shared.js`、`cache.js`、`depend-util.js`：分别涉及已加载对象、中间缓存与依赖关系。

## 场景与释放

- `../CCDirector.js`：`loadScene()` 找到所属 Bundle，调用 `bundle.loadScene()`；成功后调用 `runSceneImmediate()`。
- `../CCDirector.js`：`runSceneImmediate()` 仅在非编辑器环境调用 `cc.assetManager._releaseManager._autoRelease(oldScene, scene, game._persistRootNodes)`，随后销毁旧场景并激活新场景。
- `releaseManager.js`：`_autoRelease()` 考虑新旧场景的依赖与常驻节点。`CCAssetManager.js` 中的 `releaseAsset()` 委托 `releaseManager.tryRelease(asset, true)`；强制释放仍被使用的资源可能破坏使用方。

排查顺序：识别请求形式及所属 Bundle → 查找 → 获取/下载 → 解析 → 依赖/创建对象 → 缓存 → 引用/释放。记录第一个失败阶段，不要把所有失败都归因于下载。
