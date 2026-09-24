# 阶段四：C++、JSB 与渲染（第 7–8 周）

## 本阶段目标

沿一个具体对象追踪 JS/TS 到原生 C++ 的边界，以及从节点变更到绘制提交的路径；完成一次可测量的优化或问题分析。预计投入 16–20 小时。

## 源码入口与阅读顺序

1. [JSB 节点绑定](../2.4.15/resources/cocos2d-x/cocos/scripting/js-bindings/manual/jsb_node.cpp) 与 [JSB 模块注册](../2.4.15/resources/cocos2d-x/cocos/scripting/js-bindings/manual/jsb_module_register.cpp)：选择一个确实存在的绑定，追踪参数与返回值。
2. [JS 渲染流程](../2.4.15/resources/engine/cocos2d/core/renderer/render-flow.js)、[渲染器入口](../2.4.15/resources/engine/cocos2d/core/renderer/index.js)：追踪节点渲染标志、组件和批处理。
3. [原生纹理](../2.4.15/resources/cocos2d-x/cocos/renderer/gfx/Texture2D.cpp) 与 [原生 ForwardRenderer](../2.4.15/resources/cocos2d-x/cocos/renderer/renderer/ForwardRenderer.cpp)：观察原生侧资源和绘制提交。

Web、Canvas 与原生渲染分支并不相同。画图时注明当前实验运行的平台，不把 JS 文件与同名 C++ 文件直接视为同一条调用栈。

## 第 7 周：跨语言链路

1. 选一个节点或纹理相关调用，找到公开 JS/TS 入口、平台条件和对应的 JSB 绑定。
2. 记录参数如何转换、谁持有原生对象、何时释放；对无法从当前源码直接证明的部分明确标为待验证。
3. 画一张“脚本入口 → 绑定 → C++ 对象”的调用图，并用日志或调试器核对至少一段链路。

## 第 8 周：渲染与测量

1. 从节点属性变化追到渲染标志，再追到 `RenderFlow`、批处理和绘制提交。
2. 选一个小问题，例如不必要的节点创建或纹理重复创建；固定测试场景与采样方法，记录修改前的调用次数、帧耗时或内存。
3. 在独立练习项目中做最小改动并复测；没有可用原生构建时，可完成 Web 侧实验和原生源码分析，不声称已验证原生性能。
4. 写出收益、测量误差与适用平台。

## 交付与完成标准

- 一张 JS/TS→JSB→C++ 链路图、一张节点→渲染提交图。
- 一份可复现的测量记录，包含平台、场景、修改前后数据和局限。
- 能说清某个资源的创建、持有和释放责任；能区分 Web 与原生侧的结论。

完成后进入[阶段五：集成与作品集](stage-05-integration-and-portfolio.md)。
