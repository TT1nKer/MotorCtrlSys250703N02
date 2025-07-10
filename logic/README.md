# 蛇形编码矩阵传输系统

这是一个完整的2D矩阵蛇形编码和传输系统，专为STM32等嵌入式系统设计，支持通过串口等通信协议将矩阵数据高效传输到从机设备。

## 系统特性

- ✅ **灵活的矩阵大小**：支持任意大小的2D矩阵
- ✅ **蛇形编码**：Zigzag模式编码，保留矩阵结构信息
- ✅ **可靠传输**：包含校验和、重试机制、ACK确认
- ✅ **内存管理**：多种内存分配策略，适合不同应用场景
- ✅ **完整协议**：标准化的数据包格式
- ✅ **易于使用**：简洁的API接口

## 文件结构

```
logic/
├── logic.h          # 头文件，包含所有函数声明和数据结构
├── logic.c          # 实现文件，包含所有核心功能
├── example_usage.c  # 使用示例和测试代码
└── README.md        # 本文档
```

## 快速开始

### 1. 基本使用

```c
#include "logic.h"

// 创建矩阵
int rows = 4, cols = 4;
int **matrix = allocate_matrix_continuous(rows, cols);

// 填充数据
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        matrix[i][j] = i * cols + j + 1;
    }
}

// 蛇形编码
int *zigzag_array = (int*)malloc(rows * cols * sizeof(int));
zigzag_encode_matrix(matrix, zigzag_array, rows, cols);

// 发送到从机
MatrixTransmitter transmitter = {
    .master_addr = 0x01,
    .slave_addr = 0x02,
    .sequence_num = 0,
    .max_retries = 3,
    .timeout_ms = 1000
};

int result = transmit_matrix_to_slave(&transmitter, matrix, rows, cols);

// 清理内存
free_matrix_continuous(matrix);
free(zigzag_array);
```

### 2. 从机接收

```c
// 从机端接收矩阵
int rows, cols;
int **matrix = NULL;
int result = receive_matrix_from_master(&matrix, &rows, &cols);

if (result == 0) {
    // 处理接收到的矩阵
    process_matrix(matrix, rows, cols);
    free_matrix_continuous(matrix);
}
```

## 核心功能

### 蛇形编码

蛇形编码将2D矩阵按Zigzag模式转换为一维数组：

```
原始矩阵 (4x4):
 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15 16

蛇形编码结果:
1 2 3 4 8 7 6 5 9 10 11 12 16 15 14 13
```

### 数据包格式

```
+--------+--------+--------+--------+--------+--------+--------+--------+
| 起始字节 | 目标地址 | 源地址  | 包类型  | 数据长度 | 矩阵行数 | 矩阵列数 | 序列号  |
+--------+--------+--------+--------+--------+--------+--------+--------+
|                          数据负载 (蛇形编码的矩阵数据)                    |
+--------+--------+--------+--------+--------+--------+--------+--------+
|                             校验和                                    |
+--------+--------+--------+--------+--------+--------+--------+--------+
```

## API 参考

### 矩阵分配函数

```c
// 连续内存分配（推荐）
int** allocate_matrix_continuous(int rows, int cols);
void free_matrix_continuous(int **matrix);

// 传统方法
int** allocate_matrix_traditional(int rows, int cols);
void free_matrix_traditional(int **matrix, int rows);

// 使用calloc（自动初始化为0）
int** allocate_matrix_calloc(int rows, int cols);

// 安全分配（带错误检查）
int** allocate_matrix_safe(int rows, int cols, int *error_code);
```

### 蛇形编码函数

```c
// 标准蛇形编码
void zigzag_encode_matrix(int **matrix, int *array, int rows, int cols);
void zigzag_decode_matrix(int *array, int **matrix, int rows, int cols);

// 1D数组版本
void zigzag_encode_matrix_1d(int *matrix, int *array, int rows, int cols);
void zigzag_decode_matrix_1d(int *array, int *matrix, int rows, int cols);
```

### 传输函数

```c
// 发送矩阵到从机
int transmit_matrix_to_slave(MatrixTransmitter *transmitter, 
                           int **matrix, int rows, int cols);

// 从机接收矩阵
int receive_matrix_from_master(int **matrix, int *rows, int *cols);
```

## 应用示例

### 电机控制系统

```c
// 3x3电机控制矩阵
int **motor_matrix = allocate_matrix_continuous(3, 3);
motor_matrix[0][0] = 100;  // 电机1速度
motor_matrix[0][1] = 150;  // 电机2速度
// ... 设置其他电机参数

MatrixTransmitter transmitter = {
    .master_addr = 0x01,
    .slave_addr = 0x02,
    .max_retries = 5,      // 电机控制需要高可靠性
    .timeout_ms = 500      // 快速响应
};

transmit_matrix_to_slave(&transmitter, motor_matrix, 3, 3);
```

### 传感器数据采集

```c
// 4x4传感器数据矩阵
int **sensor_matrix = allocate_matrix_continuous(4, 4);
// 填充传感器数据

MatrixTransmitter transmitter = {
    .master_addr = 0x01,
    .slave_addr = 0x03,
    .max_retries = 3,
    .timeout_ms = 2000     // 传感器数据可以慢一些
};

transmit_matrix_to_slave(&transmitter, sensor_matrix, 4, 4);
```

## 内存管理策略

### 1. 连续内存分配（推荐）

**优点：**
- 内存局部性好，缓存性能优秀
- 释放简单，只需要两次free
- 适合频繁访问的场景

**适用场景：**
- 电机控制系统
- 实时数据处理
- 性能关键的应用

### 2. 传统分配方法

**优点：**
- 每行独立分配，灵活性高
- 可以单独调整某行大小

**缺点：**
- 内存碎片化
- 释放复杂
- 缓存性能差

**适用场景：**
- 需要动态调整行大小的场景
- 内存受限的系统

### 3. 结构体封装

**优点：**
- 更安全的接口
- 自动管理矩阵大小信息
- 减少内存泄漏风险

**适用场景：**
- 大型项目
- 需要高可靠性的系统

## 通信协议

### 数据包类型

- `0x01`: 矩阵数据包
- `0x02`: 控制命令包
- `0x03`: ACK确认包
- `0x04`: NACK否定确认包

### 传输流程

1. **主机发送数据包**
   - 蛇形编码矩阵
   - 创建数据包
   - 发送数据包

2. **从机接收数据包**
   - 接收并验证数据包
   - 蛇形解码矩阵
   - 发送ACK确认

3. **错误处理**
   - 校验和验证
   - 超时重试
   - 序列号检查

## 编译和集成

### 1. 包含头文件

```c
#include "logic.h"
```

### 2. 实现硬件相关函数

需要在你的项目中实现以下函数：

```c
// UART通信函数
int uart_send_byte(uint8_t byte);
int uart_send_data(uint8_t *data, uint16_t length);
int uart_receive_byte(uint8_t *byte, uint16_t timeout_ms);
int uart_receive_data(uint8_t *data, uint16_t length);

// 延时函数
void delay_ms(uint16_t ms);

// 打印函数（调试用）
void printf(const char *format, ...);
```

### 3. 编译选项

```makefile
CFLAGS += -I./logic
SRCS += logic/logic.c
```

## 测试和验证

运行测试示例：

```c
// 测试蛇形编码
test_zigzag_encoding();

// 测试不同大小矩阵
test_different_matrix_sizes();

// 测试电机控制
motor_control_matrix_example();

// 测试传感器数据
sensor_data_matrix_example();
```

## 性能优化建议

1. **使用连续内存分配**：提高缓存命中率
2. **合理设置超时时间**：平衡可靠性和响应速度
3. **批量传输**：减少协议开销
4. **内存池**：避免频繁分配释放

## 故障排除

### 常见问题

1. **内存分配失败**
   - 检查系统内存是否充足
   - 使用`allocate_matrix_safe`进行错误检查

2. **传输失败**
   - 检查UART配置
   - 验证校验和计算
   - 增加重试次数

3. **数据错误**
   - 检查蛇形编码逻辑
   - 验证矩阵大小参数

### 调试技巧

1. 启用调试输出
2. 检查数据包格式
3. 验证校验和计算
4. 监控内存使用

## 许可证

本项目采用MIT许可证，详见LICENSE文件。

## 贡献

欢迎提交Issue和Pull Request来改进这个项目。

## 联系方式

如有问题或建议，请通过以下方式联系：

- 提交GitHub Issue
- 发送邮件至项目维护者

---

**注意：** 在实际使用前，请根据你的硬件平台实现相应的UART通信函数。 