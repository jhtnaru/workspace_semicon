`timescale 1ns / 1ps

module tb_not_gate;
    reg a;
    wire q;

    not_gate_behavioral uut (.a(a), .q(q));
    // not_gate_structual uut (.a(a), .q(q));
    // not_gate_dataflow uut (.a(a), .q(q));

    initial begin
        $display("Time\t a | q");
        $monitor("%4d\t %b | %b", $time, a, q);

        a = 0; #10;
        a = 1; #10;
        $finish;
    end
endmodule
