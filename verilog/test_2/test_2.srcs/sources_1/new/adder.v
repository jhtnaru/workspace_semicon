`timescale 1ns / 1ps

// 동작적 Half Adder, 2-bit 입력 → Sum, Carry 출력 반가산기
module half_adder_behavioral(
    input a,        // 1-bit Input a
    input b,        // 1-bit Input b
    output reg s,   // 합(Sum) 저장할 Register Type Output
    output reg c    // 자리올림(Carry) 저장할 Register Type Output
    );

    // a 또는 b 변하면 always Block 실행
    always @(a, b) begin
        case ({a, b})
            2'b00 : begin       // a = 0, b = 0 → Sum = 0, Carry = 0
                s = 0;
                c = 0;
            end
            2'b01 : begin       // a = 0, b = 1 → Sum = 1, Carry = 0
                s = 1;
                c = 0;
            end
            2'b10 : begin       // a = 1, b = 0 → Sum = 1, Carry = 0
                s = 1;
                c = 0;
            end
            2'b11 : begin       // a = 1, b = 1 → Sum = 0, Carry = 1
                s = 0;
                c = 1;
            end
        endcase
    end
endmodule

// 구조적 Half Adder
module half_adder_structual (
    input a, b,
    output s, c
    );

    xor (s, a, b);
    and (c, a, b);
endmodule

// Data Flow Half Adder
module half_adder_dataflow (
    input a, b,
    output s, c
    );

    // a, b 저장할 2-bit wire, 최대값 1 + 1 = 2(2'b10) 2-bit 필요
    wire [1:0] sum_value;

    // Verilog '+' 연산자는 Vector 생성해서 결과를 sum_value 저장
    // ex) a = 1, b = 1 → sum_value = 2'b10
    assign sum_value = a + b;

    // sum_value 최하위 bit(LSB) sum_value[0]을 s 할당, 결과값은 XOR 연산과 같음
    assign s = sum_value[0];    // Sum
    // sum_value 최상위 bit(MSB) sum_value[1]을 c 할당, 결과값은 AND 연산과 같음
    assign c = sum_value[1];    // Carry
endmodule

// N-bit Half Adder
module half_adder_N_bit # (parameter N = 8)(    // N 기본값 8-bit 의미
    input inc,                  // Add Value, 보통 1 또는 0
    input [N-1:0] load_data,    // Input Data, N-bit
    output [N-1:0] sum          // Output Sum Result, N-bit
    );

    wire [N-1:0] carry_out;     // 각 자리의 Carry Output 저장 배열

    half_adder_dataflow ha0 (   // 첫번째 bit(LSB)는 inc와 load_data[0]를 Haft Adder 연산
        .a(inc),
        .b(load_data),
        .s(sum[0]),
        .c(carry_out[0])
    );

    genvar i;                   // generate문 위한 변수 선언
    generate
        // Label "hagen"으로 Block 지정, hagen[1], [2], ..., [N-1] 식별 가능한 이름으로 구조화
        for (i = 1; i < N; i = i + 1) begin : hagen
            half_adder_dataflow ha (
                .a(carry_out[i - 1]),       // 이전 자리 Carry Input
                .b(load_data[i]),           // 현재 자리 Input bit
                .s(sum[i]),                 // 현재 자리 Sum
                .c(carry_out[i])            // 현재 자리 Carry, 다음 자리 전달
            );
        end
    endgenerate
endmodule

// 구조적 Full Adder
module full_adder_structual (
    input a, b, cin,            // Input bit 3ea, 이전 자리 Carry = cin
    output sum, carry
    );
    wire sum_0;         // First Half Adder Sum
    wire carry_0;       // First Half Adder Carry
    wire carry_1;       // Second Half Adder Carry

    // First Half Adder - Input a, b
    // First Output sum_0, carry_0 저장
    half_adder_structual ha0 (
        .a(a),
        .b(b),
        .s(sum_0),
        .c(carry_0)
    );

    // Second Half Adder - Input sum_0, cin
    // Second Output sum, carry_1 저장
    half_adder_structual ha1 (
        .a(sum_0),
        .b(cin),
        .s(sum),
        .c(carry_1)
    );

    // Final Carry는 두 Carry의 OR 연산(carry_0, carry_1), 
    or (carry, carry_0, carry_1);
endmodule

// 동작적 Full Adder
module full_adder_behavioral (
    input a, b, cin,
    output reg sum, carry
    );

    always @(a, b, cin) begin
        // Input 3-bit 하나로 묶어서 case 처리
        case ({a, b, cin})
            3'b000 : begin sum = 0; carry = 0; end      // 0 + 0 + 0 = sum 0, carry 0
            3'b001 : begin sum = 1; carry = 0; end      // 0 + 0 + 1 = sum 1, carry 0
            3'b010 : begin sum = 1; carry = 0; end      // 0 + 1 + 0 = sum 1, carry 0
            3'b011 : begin sum = 0; carry = 1; end      // 0 + 1 + 1 = sum 0, carry 1
            3'b100 : begin sum = 1; carry = 0; end      // 1 + 0 + 0 = sum 1, carry 0
            3'b101 : begin sum = 0; carry = 1; end      // 1 + 0 + 1 = sum 0, carry 1
            3'b110 : begin sum = 0; carry = 1; end      // 1 + 1 + 0 = sum 0, carry 1
            3'b111 : begin sum = 1; carry = 1; end      // 1 + 1 + 1 = sum 1, carry 1
        endcase
    end
endmodule

// Data Flow Full Adder
module full_adder_dataflow (
    input a, b, cin,
    output sum, carry
    );

    wire [1:0] sum_value;       // 2-bit wire → Sum Result, 하위 sum, 상위 carry

    assign sum_value = a + b + cin;

    assign sum = sum_value[0];
    assign carry = sum_value[1];
endmodule


// 구조적 4-bit Full Adder
module full_adder_4bit_structural (
    input [3:0] a, b,       // 4-bit Input
    input cin,              // First Carry Input
    output [3:0] sum,       // Result 4-bit
    output carry            // Final Carry(MSB)
    );
    
    wire [2:0] carry_w;     // Full Adder 내부 Carry 연결

    // 1st bit, cin과 함께 계산
    full_adder_structual fa0 (
        .a(a[0]),
        .b(b[0]),
        .cin(cin),
        .sum(sum[0]),
        .carry(carry_w[0])
    );

    // 2nd bit, 이전 자리 Carry(carry_w)을 cin으로 사용
    full_adder_structual fa1 (
        .a(a[1]),
        .b(b[1]),
        .cin(carry_w[0]),
        .sum(sum[1]),
        .carry(carry_w[1])
    );

    // 3rd bit
    full_adder_structual fa2 (
        .a(a[2]),
        .b(b[2]),
        .cin(carry_w[1]),
        .sum(sum[2]),
        .carry(carry_w[2])
    );

    // 4th bit
    full_adder_structual fa3 (
        .a(a[3]),
        .b(b[3]),
        .cin(carry_w[2]),
        .sum(sum[3]),
        .carry(carry)
    );
endmodule

// 구조적 4-bit Full Adder + Subtractor
module full_adder_sub_4bit_structural (
    input [3:0] a, b,       // 4-bit Input
    input s,                // Select Signal, 0 ADD, 1 SUB
    output [3:0] sum,       // 4-bit Result
    output carry            // Final Carry (Carry or Borrow)
    );

    wire [3:0] carry_w;     // 각 자리 중간 Carry
    wire [3:0] b_w;         // b Input과 s Signal XOR 결과, b의 보수 처리용

    // b[0]...[3]와 s의 XOR
    // Add Mode s = 0 → b_w = b 유지
    // Sub Mode s = 1 → b_w = b 반전 → 1의 보수
    xor (b_w[0], b[0], s);
    xor (b_w[1], b[1], s);
    xor (b_w[2], b[2], s);
    xor (b_w[3], b[3], s);

    // 4개의 Full Adder 이용 4-bit Add, Sub
    // 1st Adder 초기 Carry Input(cin)을 s 사용
    // Add Mode s = cin = 0
    // Sub Mode s = cin = 1, 1의 보수 + 1 → 2의 보수 연산
    full_adder_structual fa0 (.a(a[0]), .b(b_w[0]), .cin(s),          .sum(sum[0]), .carry(carry_w[0]));
    full_adder_structual fa1 (.a(a[1]), .b(b_w[1]), .cin(carry_w[0]), .sum(sum[1]), .carry(carry_w[1]));
    full_adder_structual fa2 (.a(a[2]), .b(b_w[2]), .cin(carry_w[1]), .sum(sum[2]), .carry(carry_w[2]));
    // full_adder_structual fa3 (.a(a[3]), .b(b_w[3]), .cin(carry_w[2]), .sum(sum[3]), .carry(carry));
    full_adder_structual fa3 (.a(a[3]), .b(b_w[3]), .cin(carry_w[2]), .sum(sum[3]), .carry(carry_w[3]));

    xor (carry, s, carry_w[3]);
endmodule

// Data Flow 4-bit Full Adder + Subtractor
module full_adder_sub_4bit_dataflow (
    input [3:0] a, b,
    input s,
    output [3:0] sum,
    output carry
    );

    wire [4:0] sum_value;

    assign sum_value = s ? a - b : a + b;
    assign sum = sum_value[3:0];
    // assign carry = s ? ~sum_value[4] : sum_value[4];
    assign carry = sum_value[4];
endmodule

// 동작적 4-bit Full Adder + Subtractor
module full_adder_sub_4bit_behavioral (
    input [3:0] a, b,
    input s,
    output reg [3:0] sum,
    output reg carry
    );

    reg [4:0] temp;         // 5-bit 임시 변수

    always @(*) begin       // * 모든게 변하면 동작
        if (s == 0) begin
            temp = a + b;
        end
        else begin
            temp = a - b;
        end

        sum = temp[3:0];
        // carry = s ? ~temp[4] : temp[4];
        carry = temp[4];
    end
endmodule