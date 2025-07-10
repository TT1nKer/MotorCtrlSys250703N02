//central processor make 2d matrix to one dimension array in snake shape
// Function for fixed size matrix (original version)
void matrix_to_array(int matrix[3][3], int array[9])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            array[i * 3 + j] = matrix[i][j];
        }
    }
}

// Flexible version for any size matrix
void matrix_to_array_flexible(int **matrix, int *array, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            array[i * cols + j] = matrix[i][j];
        }
    }
}

// Alternative version using 1D array as 2D matrix
void matrix_to_array_1d(int *matrix, int *array, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            array[i * cols + j] = matrix[i * cols + j];
        }
    }
}

// Snake pattern conversion (alternating left-to-right and right-to-left)
void matrix_to_array_snake(int **matrix, int *array, int rows, int cols)
{
    int i, j;
    int index = 0;
    
    for (i = 0; i < rows; i++)
    {
        if (i % 2 == 0)  // Even rows: left to right
        {
            for (j = 0; j < cols; j++)
            {
                array[index++] = matrix[i][j];
            }
        }
        else  // Odd rows: right to left
        {
            for (j = cols - 1; j >= 0; j--)
            {
                array[index++] = matrix[i][j];
            }
        }
    }
}

// Snake pattern for 1D array as 2D matrix
void matrix_to_array_snake_1d(int *matrix, int *array, int rows, int cols)
{
    int i, j;
    int index = 0;
    
    for (i = 0; i < rows; i++)
    {
        if (i % 2 == 0)  // Even rows: left to right
        {
            for (j = 0; j < cols; j++)
            {
                array[index++] = matrix[i * cols + j];
            }
        }
        else  // Odd rows: right to left
        {
            for (j = cols - 1; j >= 0; j--)
            {
                array[index++] = matrix[i * cols + j];
            }
        }
    }
}

// ========== 蛇形编码矩阵传输系统 ==========

// 数据包类型定义
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

// ========== 蛇形编码核心函数 ==========

// 标准蛇形编码（Zigzag）
void zigzag_encode_matrix(int **matrix, int *array, int rows, int cols)
{
    int index = 0;
    int i, j;
    
    for (i = 0; i < rows; i++)
    {
        if (i % 2 == 0)  // 偶数行：从左到右
        {
            for (j = 0; j < cols; j++)
            {
                array[index++] = matrix[i][j];
            }
        }
        else  // 奇数行：从右到左
        {
            for (j = cols - 1; j >= 0; j--)
            {
                array[index++] = matrix[i][j];
            }
        }
    }
}

// 蛇形解码（从一维数组恢复矩阵）
void zigzag_decode_matrix(int *array, int **matrix, int rows, int cols)
{
    int index = 0;
    int i, j;
    
    for (i = 0; i < rows; i++)
    {
        if (i % 2 == 0)  // 偶数行：从左到右
        {
            for (j = 0; j < cols; j++)
            {
                matrix[i][j] = array[index++];
            }
        }
        else  // 奇数行：从右到左
        {
            for (j = cols - 1; j >= 0; j--)
            {
                matrix[i][j] = array[index++];
            }
        }
    }
}

// 1D数组版本的蛇形编码
void zigzag_encode_matrix_1d(int *matrix, int *array, int rows, int cols)
{
    int index = 0;
    int i, j;
    
    for (i = 0; i < rows; i++)
    {
        if (i % 2 == 0)  // 偶数行：从左到右
        {
            for (j = 0; j < cols; j++)
            {
                array[index++] = matrix[i * cols + j];
            }
        }
        else  // 奇数行：从右到左
        {
            for (j = cols - 1; j >= 0; j--)
            {
                array[index++] = matrix[i * cols + j];
            }
        }
    }
}

// 1D数组版本的蛇形解码
void zigzag_decode_matrix_1d(int *array, int *matrix, int rows, int cols)
{
    int index = 0;
    int i, j;
    
    for (i = 0; i < rows; i++)
    {
        if (i % 2 == 0)  // 偶数行：从左到右
        {
            for (j = 0; j < cols; j++)
            {
                matrix[i * cols + j] = array[index++];
            }
        }
        else  // 奇数行：从右到左
        {
            for (j = cols - 1; j >= 0; j--)
            {
                matrix[i * cols + j] = array[index++];
            }
        }
    }
}

// ========== 数据包处理函数 ==========

// 计算校验和
uint16_t calculate_checksum(uint8_t *data, uint16_t length)
{
    uint16_t checksum = 0;
    for (uint16_t i = 0; i < length; i++)
    {
        checksum += data[i];
    }
    return checksum;
}

// 创建矩阵数据包
DataPacket* create_matrix_packet(MatrixTransmitter *transmitter, 
                                int *zigzag_data, int rows, int cols)
{
    uint16_t data_size = rows * cols * sizeof(int);
    uint16_t total_size = sizeof(PacketHeader) + data_size + sizeof(uint16_t);
    
    DataPacket *packet = (DataPacket*)malloc(total_size);
    if (packet == NULL) return NULL;
    
    // 设置数据包头
    packet->header.start_byte = 0xAA;
    packet->header.dest_addr = transmitter->slave_addr;
    packet->header.src_addr = transmitter->master_addr;
    packet->header.packet_type = PACKET_TYPE_MATRIX_DATA;
    packet->header.data_length = data_size;
    packet->header.matrix_rows = rows;
    packet->header.matrix_cols = cols;
    packet->header.sequence_num = transmitter->sequence_num++;
    
    // 分配负载内存
    packet->payload = (uint8_t*)malloc(data_size);
    if (packet->payload == NULL) {
        free(packet);
        return NULL;
    }
    
    // 复制蛇形编码数据
    memcpy(packet->payload, zigzag_data, data_size);
    
    // 计算校验和
    packet->checksum = calculate_checksum((uint8_t*)&packet->header, 
                                        sizeof(PacketHeader));
    packet->checksum += calculate_checksum(packet->payload, data_size);
    
    return packet;
}

// 释放数据包内存
void free_data_packet(DataPacket *packet)
{
    if (packet) {
        if (packet->payload) {
            free(packet->payload);
        }
        free(packet);
    }
}

// ========== 通信协议函数 ==========

// 发送数据包（UART示例）
int send_data_packet(DataPacket *packet)
{
    // 发送起始字节
    if (uart_send_byte(packet->header.start_byte) != 0) return -1;
    
    // 发送数据包头
    if (uart_send_data((uint8_t*)&packet->header, sizeof(PacketHeader)) != 0) return -1;
    
    // 发送数据负载
    if (uart_send_data(packet->payload, packet->header.data_length) != 0) return -1;
    
    // 发送校验和
    if (uart_send_data((uint8_t*)&packet->checksum, sizeof(uint16_t)) != 0) return -1;
    
    return 0;
}

// 接收数据包
DataPacket* receive_data_packet(void)
{
    uint8_t start_byte;
    PacketHeader header;
    uint16_t checksum;
    
    // 等待起始字节
    if (uart_receive_byte(&start_byte, 1000) != 0 || start_byte != 0xAA) {
        return NULL;
    }
    
    // 接收数据包头
    if (uart_receive_data((uint8_t*)&header, sizeof(PacketHeader)) != 0) {
        return NULL;
    }
    
    // 分配数据包
    DataPacket *packet = (DataPacket*)malloc(sizeof(DataPacket));
    if (packet == NULL) return NULL;
    
    packet->header = header;
    packet->payload = (uint8_t*)malloc(header.data_length);
    if (packet->payload == NULL) {
        free(packet);
        return NULL;
    }
    
    // 接收数据负载
    if (uart_receive_data(packet->payload, header.data_length) != 0) {
        free_data_packet(packet);
        return NULL;
    }
    
    // 接收校验和
    if (uart_receive_data((uint8_t*)&checksum, sizeof(uint16_t)) != 0) {
        free_data_packet(packet);
        return NULL;
    }
    
    // 验证校验和
    uint16_t calculated_checksum = calculate_checksum((uint8_t*)&packet->header, 
                                                    sizeof(PacketHeader));
    calculated_checksum += calculate_checksum(packet->payload, header.data_length);
    
    if (calculated_checksum != checksum) {
        free_data_packet(packet);
        return NULL;
    }
    
    packet->checksum = checksum;
    return packet;
}

// ========== 矩阵传输主函数 ==========

// 发送矩阵到从机
int transmit_matrix_to_slave(MatrixTransmitter *transmitter, 
                           int **matrix, int rows, int cols)
{
    // 1. 蛇形编码矩阵
    int *zigzag_array = (int*)malloc(rows * cols * sizeof(int));
    if (zigzag_array == NULL) return -1;
    
    zigzag_encode_matrix(matrix, zigzag_array, rows, cols);
    
    // 2. 创建数据包
    DataPacket *packet = create_matrix_packet(transmitter, zigzag_array, rows, cols);
    if (packet == NULL) {
        free(zigzag_array);
        return -1;
    }
    
    // 3. 发送数据包
    int retry_count = 0;
    int success = 0;
    
    while (retry_count < transmitter->max_retries && !success) {
        if (send_data_packet(packet) == 0) {
            // 等待ACK
            DataPacket *ack_packet = receive_data_packet();
            if (ack_packet && ack_packet->header.packet_type == PACKET_TYPE_ACK) {
                success = 1;
                free_data_packet(ack_packet);
            } else if (ack_packet) {
                free_data_packet(ack_packet);
            }
        }
        
        if (!success) {
            retry_count++;
            delay_ms(transmitter->timeout_ms);
        }
    }
    
    // 4. 清理内存
    free_data_packet(packet);
    free(zigzag_array);
    
    return success ? 0 : -1;
}

// 从机接收矩阵
int receive_matrix_from_master(int **matrix, int *rows, int *cols)
{
    // 1. 接收数据包
    DataPacket *packet = receive_data_packet();
    if (packet == NULL) return -1;
    
    // 2. 检查数据包类型
    if (packet->header.packet_type != PACKET_TYPE_MATRIX_DATA) {
        free_data_packet(packet);
        return -1;
    }
    
    // 3. 提取矩阵信息
    *rows = packet->header.matrix_rows;
    *cols = packet->header.matrix_cols;
    
    // 4. 蛇形解码
    zigzag_decode_matrix((int*)packet->payload, matrix, *rows, *cols);
    
    // 5. 发送ACK
    PacketHeader ack_header = {
        .start_byte = 0xAA,
        .dest_addr = packet->header.src_addr,
        .src_addr = packet->header.dest_addr,
        .packet_type = PACKET_TYPE_ACK,
        .data_length = 0,
        .matrix_rows = 0,
        .matrix_cols = 0,
        .sequence_num = packet->header.sequence_num
    };
    
    uart_send_data((uint8_t*)&ack_header, sizeof(PacketHeader));
    
    // 6. 清理内存
    free_data_packet(packet);
    
    return 0;
}

// ========== 内存管理最佳实践 ==========

// 方法1: 传统方法 - 分配行指针数组，然后分配每行
int** allocate_matrix_traditional(int rows, int cols)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        return NULL;  // 分配失败
    }
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            // 如果某行分配失败，释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

// 释放传统方法分配的内存
void free_matrix_traditional(int **matrix, int rows)
{
    if (matrix == NULL) return;
    
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// 方法2: 连续内存分配 - 更高效，内存局部性好
int** allocate_matrix_continuous(int rows, int cols)
{
    // 分配行指针数组
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }
    
    // 一次性分配所有数据的内存
    int *data = (int *)malloc(rows * cols * sizeof(int));
    if (data == NULL) {
        free(matrix);
        return NULL;
    }
    
    // 设置每行的指针
    for (int i = 0; i < rows; i++) {
        matrix[i] = data + i * cols;
    }
    
    return matrix;
}

// 释放连续内存分配
void free_matrix_continuous(int **matrix)
{
    if (matrix == NULL) return;
    
    // 只需要释放数据内存（第一行指向的内存）
    free(matrix[0]);
    // 释放行指针数组
    free(matrix);
}

// 方法3: 使用calloc - 自动初始化为0
int** allocate_matrix_calloc(int rows, int cols)
{
    int **matrix = (int **)calloc(rows, sizeof(int *));
    if (matrix == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)calloc(cols, sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

// 方法4: 使用realloc动态调整大小
int** resize_matrix(int **matrix, int old_rows, int old_cols, int new_rows, int new_cols)
{
    int **new_matrix = allocate_matrix_continuous(new_rows, new_cols);
    if (new_matrix == NULL) {
        return NULL;
    }
    
    // 复制旧数据
    int copy_rows = (old_rows < new_rows) ? old_rows : new_rows;
    int copy_cols = (old_cols < new_cols) ? old_cols : new_cols;
    
    for (int i = 0; i < copy_rows; i++) {
        for (int j = 0; j < copy_cols; j++) {
            new_matrix[i][j] = matrix[i][j];
        }
    }
    
    // 释放旧内存
    free_matrix_continuous(matrix);
    
    return new_matrix;
}

// 方法5: 使用结构体封装，更安全
typedef struct {
    int **data;
    int rows;
    int cols;
} Matrix;

Matrix* create_matrix(int rows, int cols)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (matrix == NULL) {
        return NULL;
    }
    
    matrix->data = allocate_matrix_continuous(rows, cols);
    if (matrix->data == NULL) {
        free(matrix);
        return NULL;
    }
    
    matrix->rows = rows;
    matrix->cols = cols;
    return matrix;
}

void destroy_matrix(Matrix *matrix)
{
    if (matrix == NULL) return;
    
    free_matrix_continuous(matrix->data);
    free(matrix);
}

// 方法6: 错误处理和调试版本
int** allocate_matrix_safe(int rows, int cols, int *error_code)
{
    *error_code = 0;  // 0表示成功
    
    if (rows <= 0 || cols <= 0) {
        *error_code = 1;  // 无效参数
        return NULL;
    }
    
    // 检查是否会溢出
    if (rows > SIZE_MAX / sizeof(int *) || 
        cols > SIZE_MAX / sizeof(int) ||
        rows > SIZE_MAX / cols) {
        *error_code = 2;  // 内存溢出
        return NULL;
    }
    
    int **matrix = allocate_matrix_continuous(rows, cols);
    if (matrix == NULL) {
        *error_code = 3;  // 分配失败
    }
    
    return matrix;
}

// Example usage functions
void example_usage(void)
{
    // Example 1: Using dynamic allocation
    int rows = 4, cols = 5;
    int **matrix = (int **)malloc(rows * sizeof(int *));
    int *array = (int *)malloc(rows * cols * sizeof(int));
    
    // Allocate each row
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    
    // Fill matrix with sample data
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = i * cols + j + 1;  // 1, 2, 3, 4, 5...
        }
    }
    
    // Convert to array
    matrix_to_array_flexible(matrix, array, rows, cols);
    
    // Clean up
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(array);
    
    // Example 2: Using 1D array as 2D matrix
    int matrix_1d[4][5] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20}
    };
    int array_1d[20];
    
    matrix_to_array_1d((int *)matrix_1d, array_1d, 4, 5);
}

// 完整的内存管理示例
void memory_management_examples(void)
{
    printf("=== 内存管理示例 ===\n");
    
    // 示例1: 传统方法
    printf("1. 传统分配方法:\n");
    int **matrix1 = allocate_matrix_traditional(3, 4);
    if (matrix1) {
        matrix1[0][0] = 100;
        printf("  分配成功，matrix1[0][0] = %d\n", matrix1[0][0]);
        free_matrix_traditional(matrix1, 3);
    }
    
    // 示例2: 连续内存方法
    printf("2. 连续内存分配:\n");
    int **matrix2 = allocate_matrix_continuous(3, 4);
    if (matrix2) {
        matrix2[0][0] = 200;
        printf("  分配成功，matrix2[0][0] = %d\n", matrix2[0][0]);
        free_matrix_continuous(matrix2);
    }
    
    // 示例3: 使用calloc
    printf("3. 使用calloc:\n");
    int **matrix3 = allocate_matrix_calloc(3, 4);
    if (matrix3) {
        printf("  分配成功，matrix3[0][0] = %d (自动初始化为0)\n", matrix3[0][0]);
        free_matrix_traditional(matrix3, 3);
    }
    
    // 示例4: 结构体封装
    printf("4. 结构体封装:\n");
    Matrix *matrix4 = create_matrix(3, 4);
    if (matrix4) {
        matrix4->data[0][0] = 400;
        printf("  分配成功，matrix4->data[0][0] = %d\n", matrix4->data[0][0]);
        destroy_matrix(matrix4);
    }
    
    // 示例5: 安全分配
    printf("5. 安全分配:\n");
    int error_code;
    int **matrix5 = allocate_matrix_safe(3, 4, &error_code);
    if (matrix5) {
        printf("  分配成功，错误代码: %d\n", error_code);
        free_matrix_continuous(matrix5);
    } else {
        printf("  分配失败，错误代码: %d\n", error_code);
    }
}

// ========== 蛇形编码传输系统示例 ==========

void zigzag_transmission_example(void)
{
    printf("=== 蛇形编码传输系统示例 ===\n");
    
    // 1. 创建测试矩阵
    int rows = 4, cols = 4;
    int **matrix = allocate_matrix_continuous(rows, cols);
    
    // 填充测试数据
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
        }
    }
    
    printf("原始矩阵:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // 2. 蛇形编码
    int *zigzag_array = (int*)malloc(rows * cols * sizeof(int));
    zigzag_encode_matrix(matrix, zigzag_array, rows, cols);
    
    printf("蛇形编码结果: ");
    for (int i = 0; i < rows * cols; i++) {
        printf("%d ", zigzag_array[i]);
    }
    printf("\n");
    
    // 3. 蛇形解码验证
    int **decoded_matrix = allocate_matrix_continuous(rows, cols);
    zigzag_decode_matrix(zigzag_array, decoded_matrix, rows, cols);
    
    printf("解码后矩阵:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", decoded_matrix[i][j]);
        }
        printf("\n");
    }
    
    // 4. 初始化传输器
    MatrixTransmitter transmitter = {
        .master_addr = 0x01,
        .slave_addr = 0x02,
        .sequence_num = 0,
        .max_retries = 3,
        .timeout_ms = 1000
    };
    
    // 5. 传输矩阵（需要实际的UART函数）
    printf("准备传输矩阵到从机...\n");
    // int result = transmit_matrix_to_slave(&transmitter, matrix, rows, cols);
    // printf("传输结果: %s\n", result == 0 ? "成功" : "失败");
    
    // 6. 清理内存
    free_matrix_continuous(matrix);
    free_matrix_continuous(decoded_matrix);
    free(zigzag_array);
    
    printf("示例完成\n");
}
}