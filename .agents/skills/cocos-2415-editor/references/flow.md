# 已核对的源码地图：编辑器扩展可见部分

当前可见代码能够证明扩展骨架与消息流，但未完整呈现 Creator 编辑器实现。

- `2.4.15/resources/static/package-template/package.json`：声明扩展名称、`main`、菜单消息名及可停靠面板入口。
- `2.4.15/resources/static/package-template/main.js`：导出 `load`、`unload` 和 `messages`。`open` 消息调用 `Editor.Panel.open()`；另一个消息通过 `Editor.Ipc.sendToPanel()` 通知面板。
- `2.4.15/resources/static/package-template/panel/index.js`：`Editor.Panel.extend()` 声明面板界面与处理函数；按钮通过 `Editor.Ipc.sendToMain()` 向主进程发消息。
- `2.4.15/resources/builtin/asset-db-debugger/main.js`：内置扩展读取 `Editor.assetdb` 内部信息的示例。`_path2uuid` 等带下划线的字段属于实现细节，不能据此认定为稳定的公开 API。
- `2.4.15/resources/engine/editor/` 只包含此快照中部分面向编辑器的代码；`2.4.15/resources/app.asar` 打包了部分编辑器应用代码。

涉及场景编辑或资源导入时，检索相关的已安装扩展，并在 2.4.15 中验证实际方法。若无法看到方法定义，应说明这一限制，避免编造方法名。
