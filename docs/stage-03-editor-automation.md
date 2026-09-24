# 阶段三：编辑器扩展与资源校验（第 5–6 周）

## 本阶段目标

制作 Creator 2.4.15 编辑器扩展原型，让结构化关卡描述经过校验后批量进入场景。预计投入 16–20 小时；优先复用[阶段二](stage-02-assets-and-runtime.md)的关卡资源。

## 源码入口与阅读顺序

1. [package-template/package.json](../2.4.15/resources/static/package-template/package.json)：扩展清单、菜单和面板声明。
2. [package-template/main.js](../2.4.15/resources/static/package-template/main.js)：扩展主进程生命周期与消息。
3. [package-template/panel/index.js](../2.4.15/resources/static/package-template/panel/index.js)：面板、事件与主进程通信。
4. [deserialize.js](../2.4.15/resources/engine/cocos2d/core/platform/deserialize.js) 与 [CCClass.js](../2.4.15/resources/engine/cocos2d/core/platform/CCClass.js)：理解引擎对象的属性与反序列化边界。它们不是编辑器场景操作 API；具体编辑器操作仍须以 2.4.15 可用接口验证。

安装目录中的 `resources/app.asar` 封装了部分编辑器实现，因此这份源码不能充当完整编辑器内部实现说明。先用模板打通扩展通信，再用小实验核对场景和资源 API。

## 第 5 周：扩展骨架和数据契约

1. 在独立项目中安装由模板改出的扩展，验证菜单打开面板、面板发消息、主进程回消息。
2. 定义 `schemaVersion`、节点标识、父子关系、组件白名单、资源标识及必要参数。先手写两份合法 JSON 和三份非法 JSON。
3. 加入校验：未知版本、缺字段、重复节点标识、非法组件、找不到的资源。错误报告要包含字段位置及原因。
4. 通过项目资源系统解析资源引用，避免直接生成或篡改 `.meta` 与 UUID。

## 第 6 周：批量应用与幂等

1. 先显示“将新增、更新、删除哪些节点”的预览，再执行导入。
2. 用稳定节点标识匹配已有节点；同一份 JSON 重复执行，不产生重复节点。
3. 在执行前完成全部校验；失败时保留原场景并返回可读错误。
4. 用至少 20 个节点的输入验证批量处理，并记录执行时间与错误数量。

## 交付与完成标准

- 一个可打开的编辑器面板与使用说明。
- 一份关卡 JSON 格式说明、合法和非法样例、校验结果截图。
- 成功导入、缺失资源、重复导入三种演示；重复导入后节点数及引用关系不变。
- 能解释编辑器消息流、资源标识解析过程，以及哪些能力仍需查看更完整的编辑器实现。

此阶段输入由人手写；在[阶段五](stage-05-integration-and-portfolio.md)再把 AI 生成结果接到同一个数据契约上。
