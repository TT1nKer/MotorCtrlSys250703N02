
在每个电机机构上安装**限位开关或磁感应传感器**，系统启动时**自动运行归零流程**。归零完成后即建立数字-物理坐标映射。

#### 工作原理：

* 子控板接收主控“归零”指令
* 电机低速转动，寻找“零点”传感器
* 触发后立即停止，设置当前位置为“0”
* 可选：回退后二次精确归零（提高重复精度）

#### 适配传感器选型（根据场景）：

| 类型    | 优点           | 成本（每轴）   |
| ----- | ------------ | -------- |
| 微动开关  | 成本极低，抗干扰强    | ¥1 \~ ¥2 |
| 霍尔+磁铁 | 无机械磨损，易集成    | ¥2 \~ ¥3 |
| 光电开关  | 非接触式，寿命长，精度高 | ¥3 \~ ¥5 |

#### 接线示意：

* 每个传感器接入对应子控板 GPIO 输入口
* 子控板控制电机方向/步进，读取传感器状态
* ENA 控制可选用于手动解锁/锁定电机状态

#### 成本评估（以100轴为例）：

| 项目          | 单价   | 总成本估计      |
| ----------- | ---- | ---------- |
| 限位传感器+磁铁    | ¥2.5 | ¥250       |
| 线材与接口（简化）   | ¥1.0 | ¥100       |
| **合计/100轴** |      | **¥350左右** |

#### 优点：

* **自动化初始化，操作简便**
* 高可靠性，高精度，重复定位偏差可控制在±1步
* 遇断电可自动恢复位置，不依赖人工介入

#### 缺点：

* 布线略复杂（但可在子控板局部完成，集中管理）
* 成本略高于纯手动方案，但**远低于闭环系统或编码器方案**
