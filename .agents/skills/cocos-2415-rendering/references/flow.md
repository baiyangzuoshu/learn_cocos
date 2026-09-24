# 已核对的源码地图：渲染

除非另有说明，下述路径相对于 `2.4.15/resources/engine/`。追踪一帧之前，先确定渲染分支。

## 运行时分支选择

- `cocos2d/core/renderer/index.js`：`initWebGL()` 加载 WebGL assembler 与 model batcher。在 `CC_JSB && CC_NATIVERENDERER` 条件下，它使用已有的原生 gfx 设备、场景、前向渲染器与渲染流程；否则创建 JS 侧 gfx 设备、场景、前向渲染器及 `ModelBatcher`。
- 同一文件的 `initCanvas()` 创建 Canvas 设备、渲染组件处理器和 Canvas 前向渲染器。`render(ecScene, dt)` 对场景调用所选渲染流程，并从设备读取绘制调用数量。
- `cocos2d/core/CCDirector.js`：`mainLoop()` 在更新阶段之后调用 `renderer.render(this._scene, deltaTime)`。编辑器与运行时循环分支不同。

## WebGL 节点到绘制的路径

- `cocos2d/core/CCNode.js`：变更变换、颜色、透明度、层级等状态会设置渲染流程标记；部分赋值受 `!CC_NATIVERENDERER` 条件限制。
- `cocos2d/core/renderer/render-flow.js`：不同标记对应的函数更新变换或渲染数据，并对渲染组件调用 `comp._assembler.fillBuffers(comp, _batcher)`。`RenderFlow.render()` 遍历根节点，再调用 `_forward.render(_batcher._renderScene, dt)`。
- `cocos2d/core/renderer/webgl/model-batcher.js`：分析绘制调用或合批时，检查 batcher 对缓冲区和模型的管理。
- `cocos2d/renderer/renderers/forward-renderer.js` 与 `cocos2d/renderer/gfx/`：模型生成后，在这里继续检查提交和设备行为。

分析原生绘制时，改查 `2.4.15/resources/cocos2d-x/cocos/renderer/renderer/ForwardRenderer.cpp` 和 `cocos/renderer/gfx/`，再核对进入它们的 JSB/原生流程。同名的 Web 与 C++ 渲染器属于不同平台路径，并非无条件串联的一条调用链。
