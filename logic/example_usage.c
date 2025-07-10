#include "logic.h"
#include <stdio.h>

// ========== 主机端示例代码 ==========

// 主机发送矩阵到从机
void master_send_matrix_example(void)
{
    printf("=== 主机发送矩阵示例 ===\n");
    
    // 1. 初始化传输器
    MatrixTransmitter transmitter = {
        .master_addr = 0x01,    // 主机地址
        .slave_addr = 0x02,     // 从机地址
        .sequence_num = 0,      // 序列号从0开始
        .max_retries = 3,       // 最大重试3次
        .timeout_ms = 1000      // 超时1秒
    };
    
    // 2. 创建测试矩阵（4x4）
    int rows = 4, cols = 4;
    int **matrix = allocate_matrix_continuous(rows, cols);
    if (!matrix) {
        printf("矩阵分配失败\n");
        return;
    }
    
    // 3. 填充测试数据
    printf("创建测试矩阵:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // 4. 蛇形编码
    int *zigzag_array = (int*)malloc(rows * cols * sizeof(int));
    if (!zigzag_array) {
        printf("蛇形数组分配失败\n");
        free_matrix_continuous(matrix);
        return;
    }
    
    zigzag_encode_matrix(matrix, zigzag_array, rows, cols);
    
    printf("蛇形编码结果: ");
    for (int i = 0; i < rows * cols; i++) {
        printf("%d ", zigzag_array[i]);
    }
    printf("\n");
    
    // 5. 发送矩阵到从机
    printf("发送矩阵到从机...\n");
    int result = transmit_matrix_to_slave(&transmitter, matrix, rows, cols);
    
    if (result == 0) {
        printf("矩阵发送成功！\n");
    } else {
        printf("矩阵发送失败！\n");
    }
    
    // 6. 清理内存
    free_matrix_continuous(matrix);
    free(zigzag_array);
}

// ========== 从机端示例代码 ==========

// 从机接收矩阵
void slave_receive_matrix_example(void)
{
    printf("=== 从机接收矩阵示例 ===\n");
    
    // 1. 等待接收矩阵数据
    printf("等待接收矩阵数据...\n");
    
    int rows, cols;
    int **matrix = NULL;
    
    // 2. 接收矩阵
    int result = receive_matrix_from_master(&matrix, &rows, &cols);
    
    if (result == 0 && matrix != NULL) {
        printf("矩阵接收成功！\n");
        printf("矩阵大小: %dx%d\n", rows, cols);
        
        // 3. 显示接收到的矩阵
        printf("接收到的矩阵:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%2d ", matrix[i][j]);
            }
            printf("\n");
        }
        
        // 4. 处理矩阵数据（这里可以添加你的具体应用逻辑）
        process_received_matrix(matrix, rows, cols);
        
        // 5. 清理内存
        free_matrix_continuous(matrix);
    } else {
        printf("矩阵接收失败！\n");
    }
}

// 处理接收到的矩阵（示例函数）
void process_received_matrix(int **matrix, int rows, int cols)
{
    printf("处理接收到的矩阵...\n");
    
    // 示例：计算矩阵元素和
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += matrix[i][j];
        }
    }
    printf("矩阵元素和: %d\n", sum);
    
    // 示例：找到最大值
    int max_val = matrix[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > max_val) {
                max_val = matrix[i][j];
            }
        }
    }
    printf("矩阵最大值: %d\n", max_val);
}

// ========== 完整系统测试示例 ==========

// 测试蛇形编码和解码
void test_zigzag_encoding(void)
{
    printf("=== 蛇形编码测试 ===\n");
    
    // 1. 创建测试矩阵
    int rows = 4, cols = 4;
    int **original_matrix = allocate_matrix_continuous(rows, cols);
    int **decoded_matrix = allocate_matrix_continuous(rows, cols);
    
    // 填充测试数据
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original_matrix[i][j] = i * cols + j + 1;
        }
    }
    
    printf("原始矩阵:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", original_matrix[i][j]);
        }
        printf("\n");
    }
    
    // 2. 蛇形编码
    int *zigzag_array = (int*)malloc(rows * cols * sizeof(int));
    zigzag_encode_matrix(original_matrix, zigzag_array, rows, cols);
    
    printf("蛇形编码: ");
    for (int i = 0; i < rows * cols; i++) {
        printf("%d ", zigzag_array[i]);
    }
    printf("\n");
    
    // 3. 蛇形解码
    zigzag_decode_matrix(zigzag_array, decoded_matrix, rows, cols);
    
    printf("解码后矩阵:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", decoded_matrix[i][j]);
        }
        printf("\n");
    }
    
    // 4. 验证编码解码是否正确
    int is_correct = 1;
    for (int i = 0; i < rows && is_correct; i++) {
        for (int j = 0; j < cols; j++) {
            if (original_matrix[i][j] != decoded_matrix[i][j]) {
                is_correct = 0;
                break;
            }
        }
    }
    
    printf("编码解码测试: %s\n", is_correct ? "通过" : "失败");
    
    // 5. 清理内存
    free_matrix_continuous(original_matrix);
    free_matrix_continuous(decoded_matrix);
    free(zigzag_array);
}

// 测试不同大小的矩阵
void test_different_matrix_sizes(void)
{
    printf("=== 不同大小矩阵测试 ===\n");
    
    int test_sizes[][2] = {
        {2, 2}, {3, 3}, {4, 4}, {3, 5}, {5, 3}, {6, 4}
    };
    
    for (int test = 0; test < 6; test++) {
        int rows = test_sizes[test][0];
        int cols = test_sizes[test][1];
        
        printf("\n测试 %dx%d 矩阵:\n", rows, cols);
        
        // 创建矩阵
        int **matrix = allocate_matrix_continuous(rows, cols);
        int *zigzag_array = (int*)malloc(rows * cols * sizeof(int));
        
        // 填充数据
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = i * cols + j + 1;
            }
        }
        
        // 蛇形编码
        zigzag_encode_matrix(matrix, zigzag_array, rows, cols);
        
        printf("编码结果: ");
        for (int i = 0; i < rows * cols; i++) {
            printf("%d ", zigzag_array[i]);
        }
        printf("\n");
        
        // 清理内存
        free_matrix_continuous(matrix);
        free(zigzag_array);
    }
}

// ========== 实际应用示例 ==========

// 电机控制矩阵传输示例
void motor_control_matrix_example(void)
{
    printf("=== 电机控制矩阵传输示例 ===\n");
    
    // 假设这是一个3x3的电机控制矩阵
    // 矩阵元素代表不同电机的速度控制值
    int rows = 3, cols = 3;
    int **motor_matrix = allocate_matrix_continuous(rows, cols);
    
    // 设置电机控制值
    motor_matrix[0][0] = 100;  // 电机1速度
    motor_matrix[0][1] = 150;  // 电机2速度
    motor_matrix[0][2] = 200;  // 电机3速度
    motor_matrix[1][0] = 120;  // 电机4速度
    motor_matrix[1][1] = 180;  // 电机5速度
    motor_matrix[1][2] = 160;  // 电机6速度
    motor_matrix[2][0] = 140;  // 电机7速度
    motor_matrix[2][1] = 170;  // 电机8速度
    motor_matrix[2][2] = 190;  // 电机9速度
    
    printf("电机控制矩阵:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", motor_matrix[i][j]);
        }
        printf("\n");
    }
    
    // 初始化传输器
    MatrixTransmitter transmitter = {
        .master_addr = 0x01,
        .slave_addr = 0x02,
        .sequence_num = 0,
        .max_retries = 5,      // 电机控制需要更可靠
        .timeout_ms = 500      // 更快的响应时间
    };
    
    // 发送电机控制矩阵
    printf("发送电机控制矩阵到从机...\n");
    int result = transmit_matrix_to_slave(&transmitter, motor_matrix, rows, cols);
    
    if (result == 0) {
        printf("电机控制矩阵发送成功！\n");
    } else {
        printf("电机控制矩阵发送失败！\n");
    }
    
    free_matrix_continuous(motor_matrix);
}

// 传感器数据矩阵传输示例
void sensor_data_matrix_example(void)
{
    printf("=== 传感器数据矩阵传输示例 ===\n");
    
    // 假设这是一个4x4的传感器数据矩阵
    // 矩阵元素代表不同传感器的读数
    int rows = 4, cols = 4;
    int **sensor_matrix = allocate_matrix_continuous(rows, cols);
    
    // 模拟传感器数据
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // 模拟温度传感器数据 (20-30度)
            sensor_matrix[i][j] = 20 + (i * cols + j) % 10;
        }
    }
    
    printf("传感器数据矩阵:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", sensor_matrix[i][j]);
        }
        printf("\n");
    }
    
    // 初始化传输器
    MatrixTransmitter transmitter = {
        .master_addr = 0x01,
        .slave_addr = 0x03,    // 传感器从机地址
        .sequence_num = 0,
        .max_retries = 3,
        .timeout_ms = 2000     // 传感器数据可以慢一些
    };
    
    // 发送传感器数据矩阵
    printf("发送传感器数据矩阵到从机...\n");
    int result = transmit_matrix_to_slave(&transmitter, sensor_matrix, rows, cols);
    
    if (result == 0) {
        printf("传感器数据矩阵发送成功！\n");
    } else {
        printf("传感器数据矩阵发送失败！\n");
    }
    
    free_matrix_continuous(sensor_matrix);
}

// ========== 主函数示例 ==========

int main(void)
{
    printf("蛇形编码矩阵传输系统测试\n");
    printf("========================\n\n");
    
    // 1. 测试蛇形编码
    test_zigzag_encoding();
    printf("\n");
    
    // 2. 测试不同大小矩阵
    test_different_matrix_sizes();
    printf("\n");
    
    // 3. 电机控制示例
    motor_control_matrix_example();
    printf("\n");
    
    // 4. 传感器数据示例
    sensor_data_matrix_example();
    printf("\n");
    
    // 5. 主机发送示例
    master_send_matrix_example();
    printf("\n");
    
    // 6. 从机接收示例
    slave_receive_matrix_example();
    printf("\n");
    
    printf("所有测试完成！\n");
    return 0;
} 