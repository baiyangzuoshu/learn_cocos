---
name: cocos-2415-assets
description: 追踪或修改本工作区 Cocos Creator 2.4.15 的 Bundle 加载、资源管线、依赖、缓存与释放。
---

# Cocos Creator 2.4.15 资源管理

先读[资源流程图](references/flow.md)，确定入口与管理模块，再按具体请求形式检查本地实现：UUID、Bundle 路径、场景名、远程 URL 或预加载。从公开 API 出发，同时追踪成功、失败以及完成后的资源归属。

分析场景切换时，把 `Bundle.loadScene()`、`CCDirector.runSceneImmediate()` 与 `ReleaseManager._autoRelease()` 连起来看。解释时区分下载、解析、依赖解析、实例化、缓存查询和释放。扩展文件类型时，先检查 `downloader.register()` 与 `parser.register()`，再考虑修改管线内部。

相关源码位于 `2.4.15/resources/engine/`；安装快照的工作边界见 `2.4.15/AGENTS.md`。先核对源码，再根据改动范围验证首次请求、重复请求、失败、依赖和释放。不要通过修改生成的 `bin/` 文件或 `.meta`/UUID 关系来绕过资源问题。

仅在学习任务中读取[阶段二学习计划](../../../docs/stage-02-assets-and-runtime.md)。
