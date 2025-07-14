`timescale 1ns / 1ps

// 동작적 : 동작을 Code 표현, 복잡한 Logic 처리에 유리
// 구조적 : Gate 연결해서 회로 구조 표현, 실제 회로 구조 이해에 적합
// Data Flow : 출력 = 입력 서술, 간단한 조합논리회로에 적합

// AND Gate
module and_gate(
    input a, b,
    output reg q
    );

    always @(a, b) begin
        case ({a, b})
            2'b00 : q = 0;
            2'b01 : q = 0;
            2'b10 : q = 0;
            2'b11 : q = 1;
        endcase
    end
endmodule

// 동작적 AND Gate, always Block과 case문, if문 이용해서 회로 동작(행동) 기술
module and_gate_behavioral (
    input a, b,
    output reg q
    );

    always @(a or b) begin                  // a, b 중 하나라도 변경되면 Block 실행
        if (a == 1'b1 && b == 1'b1) begin   // a, b 모두 1이면
            q = 1'b1;                       // q에 1 저장
        end
        else begin                          // 아니면
            q = 1'b0;                       // q에 0 저장
        end
    end
endmodule

// 구조적 AND Gate, Gate(AND) 이용해서 회로 구조 기술, Hardware 구성요소를 직접 Instance 생성
module and_gate_structual (
    input a, b,
    output q                                // wire type 사용
    );

    and U1(q, a, b);                        // AND gate Instance 생성
endmodule

// Data Flow AND Gate, assign문으로 출력과 입력간의 논리 기술, Data Flow 중심
module and_gate_dataflow (
    input a, b,
    output q
    );

    assign q = a & b;
endmodule

// OR Gate
module or_gate (
    input a, b,
    output reg q
    );

    always @(a, b) begin
        case ({a, b})
            2'b00 : q = 0;
            2'b01 : q = 1;
            2'b10 : q = 1;
            2'b11 : q = 1;
        endcase
    end
endmodule

// 동작적 OR Gate
module or_gate_behavioral (
    input a, b,
    output reg q
    );

    always @(a, b) begin
        if (a == 1'b1 || b == 1'b1) begin
            q = 1'b1;
        end
        else begin
            q = 1'b0;
        end
    end
endmodule

// 구조적 OR Gate
module or_gate_structual (
    input a, b,
    output q
);

    or U1(q, a, b);
endmodule

// Data Flow OR Gate
module or_gate_dataflow (
    input a, b,
    output q
    );

    assign q = a | b;
endmodule
