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
    // and (a_and_b, a, b);                // a_and_b = a & b
    // and (nota_and_notb, nota, notb);    // nota_and_notb = ~a & ~b

    // or (equal, a_and_b, nota_and_notb); // equal = (a & b) | (~a & ~b), XNOR
    xnor (equal, a, b);
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

// 구조적 4-bit Comparator
module comparator_4bit_structural (
    input [3:0] a, b,
    output equal, greator, less
    );
    
    wire [3:0] e_w, g_w, l_w;
    wire [2:0] eg_w, el_w;

    comparator_structural com0 (.a(a[0]), .b(b[0]), .equal(e_w[0]), .greator(g_w[0]), .less(l_w[0]));
    comparator_structural com1 (.a(a[1]), .b(b[1]), .equal(e_w[1]), .greator(g_w[1]), .less(l_w[1]));
    comparator_structural com2 (.a(a[2]), .b(b[2]), .equal(e_w[2]), .greator(g_w[2]), .less(l_w[2]));
    comparator_structural com3 (.a(a[3]), .b(b[3]), .equal(e_w[3]), .greator(g_w[3]), .less(l_w[3]));

    and (equal, e_w[0], e_w[1], e_w[2], e_w[3]);

    and (eg_w[2], e_w[3], g_w[2]);
    and (eg_w[1], e_w[3], e_w[2], g_w[1]);
    and (eg_w[0], e_w[3], e_w[2], e_w[1], g_w[0]);
    or (greator, g_w[3], eg_w[2], eg_w[1], eg_w[0]);

    and (el_w[2], e_w[3], l_w[2]);
    and (el_w[1], e_w[3], e_w[2], l_w[1]);
    and (el_w[0], e_w[3], e_w[2], e_w[1], l_w[0]);
    or (less, l_w[3], el_w[2], el_w[1], el_w[0]);
endmodule
