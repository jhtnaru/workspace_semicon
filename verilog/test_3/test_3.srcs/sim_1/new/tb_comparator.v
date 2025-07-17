`timescale 1ns / 1ps

module tb_comparator;
    reg a, b;
    wire equal, greator, less;

    // comparator_behavioral uut (.a(a), .b(b), .equal(equal), .greator(greator), .less(less));
    // comparator_structural uut (.a(a), .b(b), .equal(equal), .greator(greator), .less(less));
    comparator_dataflow uut (.a(a), .b(b), .equal(equal), .greator(greator), .less(less));

    initial begin
        $display("Time\ta b | == > <");
        $monitor("%4d\t%b %b | %b  %b %b", $time, a, b, equal, greator, less);

        a = 0; b = 0; #10;      // equal
        a = 0; b = 1; #10;      // less
        a = 1; b = 0; #10;      // greator
        a = 1; b = 1; #10;      // equal
        $finish;
    end
endmodule

module tb_comparator_4bit;
    reg [3:0] a, b;
    wire equal, greator, less;

    // dut, Device Under Test
    // comparator_Nbit_behavioral #(.N(4)) dut (
    //     .a(a), .b(b), .equal(equal), .greator(greator), .less(less)
    // );
    // comparator_Nbit_structural #(.N(4)) dut (
    //     .a(a), .b(b), .equal(equal), .greator(greator), .less(less)
    // );
    comparator_Nbit_dataflow #(.N(4)) dut (
        .a(a), .b(b), .equal(equal), .greator(greator), .less(less)
    );

    integer i, j;

    initial begin
        $display("Time\ta    b    | == > <");
        $monitor("%4d\t%b %b | %b  %b %b", $time, a, b, equal, greator, less);

        // a 0 ~ 15, b 0 ~ 15 Test
        for (i = 0; i < 16; i = i + 1) begin
            for (j = 0;j < 16 ; j = j + 1) begin
                a = i;
                b = j;
                #10;
            end
        end
        $finish;
    end
endmodule
