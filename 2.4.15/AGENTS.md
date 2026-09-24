# Cocos Creator 2.4.15 源码工作说明

本文件作用于 `2.4.15/` 及其子目录。这是 Cocos Creator 的 Windows 安装快照，不是单一的引擎仓库。工作区根目录的 `../docs/cocos-2.4.15-learning-plan.md` 是学习总览；涉及某一阶段时，先看对应的 `../docs/stage-0*.md`。

## 先确认范围

- `resources/engine/package.json` 中的 JS 引擎版本是 `2.4.15`。分析启动或模块装配前，依次查看 `resources/engine/index.js`、`resources/engine/extends.js`、`resources/engine/modules.json`。
- `resources/engine/` 是 JS/TS 引擎源码；`resources/cocos2d-x/` 是原生 C++ 与 JSB；`resources/static/package-template/` 是编辑器扩展模板；`resources/builtin/` 是随安装包提供的扩展和适配器。
- `resources/app.asar` 封装了部分编辑器主体实现。不要根据扩展模板推断编辑器内部的完整实现；找不到的实现应明确说明边界。
- 顶层 `.exe`、`.dll`、`.pak`、`resources/app.asar`、`resources/engine/bin/` 和第三方 `node_modules/` 不是日常源码修改入口。定位代码时优先限定到相关源码目录，避免遍历整个安装包。
- 这份 2.x 源码不能直接证明岗位所提 PinK 编辑器或 WebGPU、Vulkan、Metal 的具体实现。回答这些问题时说明版本差异，不把其他版本 API 套用到 2.4.15。

## 追踪代码的顺序

1. 从公开入口定位行为，例如 `cc.game`、`cc.director`、`cc.assetManager`、`Bundle` 或渲染组件。
2. 沿调用链追到管理器、任务/状态对象和最终数据；同时查找失败、释放或销毁路径。
3. 区分 `CC_EDITOR`、`CC_PREVIEW`、`CC_JSB`、`CC_NATIVERENDERER` 以及 `Editor.isMainProcess` 分支。编辑器主进程、预览、Web、原生的行为分别核实。
4. 结论标明源码文件与函数；把源码事实、运行实验和推断分开写。文档与源码冲突时，以本地版本中的实际代码为准。
5. 影响可选功能或构建结果时查看 `resources/engine/modules.json` 和 `resources/engine/gulp/tasks/engine.js` 的依赖关系。

## 子系统入口

- 启动与帧循环：`resources/engine/cocos2d/core/CCGame.js`、`CCDirector.js`。
- 场景与组件：`CCScene.js`、`CCNode.js`、`components/CCComponent.js`、`node-activator.js`、`component-scheduler.js`。
- 资源：`resources/engine/cocos2d/core/asset-manager/CCAssetManager.js`、`bundle.js`、`pipeline.js`、`task.js`、`preprocess.js`、`fetch.js`、`load.js`、`downloader.js`、`parser.js`、`depend-util.js`、`releaseManager.js`。
- 渲染：`resources/engine/cocos2d/core/renderer/` 与 `resources/engine/cocos2d/renderer/`；原生侧见 `resources/cocos2d-x/cocos/renderer/`。
- JSB：`resources/cocos2d-x/cocos/scripting/js-bindings/`。不要只凭相似文件名假定 JS 和 C++ 代码位于同一调用路径。
- 编辑器扩展：`resources/static/package-template/`。先跑通清单、主进程消息和面板，再核对 2.4.15 实际可用的编辑器 API。

## 修改与实验

- 默认把安装目录作为阅读材料。学习 Demo、编辑器扩展与测试样例放在独立 Creator 项目；需要修改引擎时，优先在独立副本中实验。若任务明确要求改此目录，修改真实源码并说明该安装快照的影响范围。
- 保持周边代码的 CommonJS/ES module 边界、回调和错误传递方式，不做无关迁移或大范围格式化。
- 对资源类型扩展，先检查 `downloader.register()`、`parser.register()` 等现有扩展点。对场景/Bundle 改动，同时检查 `Director` 的切场景和 `releaseManager` 的旧资源释放。
- 不手动删除 `.meta` 或随意改 UUID、资源依赖关系。不要直接改生成的 `engine/bin/` 文件；改源码后再通过相应构建流程生成。
- 对动态内容与 AI 生成内容，先定义结构化输入、版本、校验和错误回退，再接入编辑器或运行时。区分 Bundle 加载、资源替换和应用级热更新。

## 验证与汇报

- 优先用最小可复现项目及相关测试验证改动：正常路径、失败路径、重复执行，并在资源改动后验证释放或再次加载。
- `resources/engine/package.json` 定义 `npm test`；`resources/engine/README.md` 记载 `gulp build` 和测试准备步骤。运行前确认依赖是否存在；构建可能改写 `engine/bin/`，因此优先在副本中执行。不要为了阅读任务安装依赖或触发全量构建。
- 原生改动只有在对应平台构建和运行后才能声称已验证；Web 预览结果不等于原生验证。
- 汇报时写清修改位置、运行平台、验证命令或操作、实际结果、未运行的检查及原因。
