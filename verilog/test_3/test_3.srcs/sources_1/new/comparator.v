`timescale 1ns / 1ps

// Data Flow Comparator
module comparator_dataflow (
    input a, b,         // 1-bit Input a, b
    output equal,       // a == b
    output greator,     // a > b
    output less         // a < b
    );

    assign equal = (a == b) ? 1'b1 : 1'b0;      // a == b, equal = 1
    assign greator = (a > b) ? 1'b1 : 1'b0;     // a > b, greator = 1
    assign less = (a < b) ? 1'b1 : 1'b0;        // a < b, less = 1
endmodule

// 구조적 Comparator
module comparator_structural (
    input a, b,
    output equal, greator, less
    );

    wire nota, notb;
    wire a_and_b, nota_and_notb;

    not (nota, a);                      // nota = ~a
    not (notb, b);                      // notb = ~b
    and (a_and_b, a, b);                // a_and_b = a & b
    and (nota_and_notb, nota, notb);    // nota_and_notb = ~a & ~b

    or (equal, a_and_b, nota_and_notb); // equal = (a & b) | (~a & ~b), XNOR
    and (greator, a, notb);             // greator = a & ~b
    and (less, nota, b);                // less = ~a & b
endmodule

// 동작적 Comparator
module comparator_behavioral (
    input a, b,
    output reg equal, greator, less
    );

    always @(a, b) begin
        equal = 0;
        greator = 0;
        less = 0;

        if (a == b) begin
            equal = 1;          // a == b, equal = 1
        end
        else if (a > b) begin
            greator = 1;        // a > b, greator = 1
        end
        else begin
            less = 1;           // a < b, less = 1
        end
    end
endmodule

// Data Flow N-bit Comparator
module comparator_Nbit_dataflow #(parameter N = 8) (
    input [N-1:0] a, b,
    output equal, greator, less
    );

    assign equal = (a == b) ? 1'b1 : 1'b0;
    assign greator = (a > b) ? 1'b1 : 1'b0;
    assign less = (a < b) ? 1'b1 : 1'b0;
endmodule

// 4-bit Comparator Test, Data Flow
module comparator_test_4bit (
    input [3:0] a, b,
    output equal, greator, less
    );

    comparator_Nbit_dataflow #(.N(4)) test (
        .a(a), .b(b), .equal(equal), .greator(greator), .less(less)
    );
endmodule

// 동작적 N-bit Comparator
module comparator_Nbit_behavioral #(parameter N = 8) (
    input [N-1:0] a, b,
    output reg equal, greator, less
    );

    always @(*) begin
        equal = 0;
        greator = 0;
        less = 0;

        if (a == b) begin
            equal = 1;
        end
        else if (a > b) begin
            greator = 1;
        end
        else if (a < b) begin
            less = 1;
        end
    end
endmodule

// 구조적 N-bit Comparator


