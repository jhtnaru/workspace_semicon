`timescale 1ns / 1ps

module tb_nand_gate;
    reg a, b;
    wire q;

    nand_gate_behavioral uut (.a(a), .b(b), .q(q));
    // nand_gate_structual uut (.a(a), .b(b), .q(q));
    // nand_gate_dataflow uut (.a(a), .b(b), .q(q));

    initial begin
        $display("Time\t a b | q");
        $monitor("%4d\t %b %b | %b", $time, a, b, q);

        a = 0; b = 0; #10;
        a = 0; b = 1; #10;
        a = 1; b = 0; #10;
        a = 1; b = 1; #10;
        $finish;
    end
endmodule
