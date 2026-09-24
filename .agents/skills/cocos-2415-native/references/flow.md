# 已核对的源码导览：JSB 与原生对象

- `2.4.15/resources/cocos2d-x/cocos/scripting/js-bindings/manual/jsb_module_register.cpp`：`jsb_register_all_modules()` 获取 `se::ScriptEngine`，并添加引擎、手写绑定、图形层、渲染器、平台等模块的注册回调。不要忽略编译期分支，不能默认所有回调都会执行。
- `2.4.15/resources/cocos2d-x/cocos/scripting/js-bindings/manual/jsb_node.cpp`：手写的 Node 绑定涉及构造、终结处理、子节点操作、调度，以及通过 `se::State` 处理参数与返回值。应从某个具体的已注册方法出发，追踪到其 C++ 实现者。
- `2.4.15/resources/cocos2d-x/cocos/scripting/js-bindings/auto/`：生成的绑定代码。修改前先定位生成器输入。
- `2.4.15/resources/cocos2d-x/cocos/renderer/gfx/Texture2D.cpp`：`Texture2D::init()`、`update()`、`setImage()` 和析构函数可用于分析纹理生命周期。
- `2.4.15/resources/cocos2d-x/cocos/renderer/renderer/ForwardRenderer.cpp`：`render()`、`renderCamera()` 与各阶段的绘制提交是原生渲染入口。
- `2.4.15/resources/engine/cocos2d/core/renderer/index.js`：在 `CC_JSB && CC_NATIVERENDERER` 条件下，选择原生图形设备、场景、前向渲染器和渲染流程；否则构造 JS/WebGL 对象。将脚本操作映射到原生代码时，必须核对这一分支。

绘制跨语言调用关系时，分别记录脚本符号、注册函数、转换函数、原生实现者和对象生命周期。不要仅因 JS 与 C++ 类型名称相似，就推断两者存在直接调用。
