#ifndef LOGIC_H
#define LOGIC_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// ========== 基础矩阵转换函数 ==========

// 固定大小矩阵转换
void matrix_to_array(int matrix[3][3], int array[9]);

// 灵活大小矩阵转换
void matrix_to_array_flexible(int **matrix, int *array, int rows, int cols);
void matrix_to_array_1d(int *matrix, int *array, int rows, int cols);

// 蛇形模式转换
void matrix_to_array_snake(int **matrix, int *array, int rows, int cols);
void matrix_to_array_snake_1d(int *matrix, int *array, int rows, int cols);

// ========== 蛇形编码核心函数 ==========

// 标准蛇形编码（Zigzag）
void zigzag_encode_matrix(int **matrix, int *array, int rows, int cols);
void zigzag_decode_matrix(int *array, int **matrix, int rows, int cols);

// 1D数组版本的蛇形编码
void zigzag_encode_matrix_1d(int *matrix, int *array, int rows, int cols);
void zigzag_decode_matrix_1d(int *array, int *matrix, int rows, int cols);

// ========== 数据包类型定义 ==========

#define PACKET_TYPE_MATRIX_DATA    0x01
#define PACKET_TYPE_CONTROL_CMD    0x02
#define PACKET_TYPE_ACK            0x03
#define PACKET_TYPE_NACK           0x04

// 数据包头结构
typedef struct {
    uint8_t start_byte;      // 起始字节 0xAA
    uint8_t dest_addr;       // 目标地址
    uint8_t src_addr;        // 源地址
    uint8_t packet_type;     // 数据包类型
    uint16_t data_length;    // 数据长度
    uint8_t matrix_rows;     // 矩阵行数
    uint8_t matrix_cols;     // 矩阵列数
    uint8_t sequence_num;    // 序列号
} PacketHeader;

// 完整数据包结构
typedef struct {
    PacketHeader header;     // 数据包头
    uint8_t *payload;        // 数据负载
    uint16_t checksum;       // 校验和
} DataPacket;

// 蛇形编码矩阵传输器
typedef struct {
    uint8_t master_addr;     // 主机地址
    uint8_t slave_addr;      // 从机地址
    uint8_t sequence_num;    // 当前序列号
    uint8_t max_retries;     // 最大重试次数
    uint16_t timeout_ms;     // 超时时间(ms)
} MatrixTransmitter;

// ========== 数据包处理函数 ==========

// 计算校验和
uint16_t calculate_checksum(uint8_t *data, uint16_t length);

// 创建矩阵数据包
DataPacket* create_matrix_packet(MatrixTransmitter *transmitter, 
                                int *zigzag_data, int rows, int cols);

// 释放数据包内存
void free_data_packet(DataPacket *packet);

// ========== 通信协议函数 ==========

// 发送数据包（UART示例）
int send_data_packet(DataPacket *packet);

// 接收数据包
DataPacket* receive_data_packet(void);

// ========== 矩阵传输主函数 ==========

// 发送矩阵到从机
int transmit_matrix_to_slave(MatrixTransmitter *transmitter, 
                           int **matrix, int rows, int cols);

// 从机接收矩阵
int receive_matrix_from_master(int **matrix, int *rows, int *cols);

// ========== 内存管理函数 ==========

// 传统方法
int** allocate_matrix_traditional(int rows, int cols);
void free_matrix_traditional(int **matrix, int rows);

// 连续内存分配（推荐）
int** allocate_matrix_continuous(int rows, int cols);
void free_matrix_continuous(int **matrix);

// 使用calloc
int** allocate_matrix_calloc(int rows, int cols);

// 动态调整大小
int** resize_matrix(int **matrix, int old_rows, int old_cols, int new_rows, int new_cols);

// 结构体封装
typedef struct {
    int **data;
    int rows;
    int cols;
} Matrix;

Matrix* create_matrix(int rows, int cols);
void destroy_matrix(Matrix *matrix);

// 安全分配
int** allocate_matrix_safe(int rows, int cols, int *error_code);

// ========== 示例函数 ==========

// 基础使用示例
void example_usage(void);

// 内存管理示例
void memory_management_examples(void);

// 蛇形编码传输系统示例
void zigzag_transmission_example(void);

// ========== 辅助函数声明 ==========

// 这些函数需要在具体的硬件平台中实现
// UART通信函数
int uart_send_byte(uint8_t byte);
int uart_send_data(uint8_t *data, uint16_t length);
int uart_receive_byte(uint8_t *byte, uint16_t timeout_ms);
int uart_receive_data(uint8_t *data, uint16_t length);

// 延时函数
void delay_ms(uint16_t ms);

// 打印函数（用于调试）
void printf(const char *format, ...);

#endif // LOGIC_H 