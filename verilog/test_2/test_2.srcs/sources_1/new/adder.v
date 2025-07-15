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
        for (i = 1; i < N; i = i + 1) begin : hagen     // Labe를 "hagen"으로 Block 지정
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
