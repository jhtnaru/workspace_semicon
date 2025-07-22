`timescale 1ns / 1ps

module tb_sr_latch;
    reg s, r;
    wire q, not_q;

    sr_latch uut (.s(s), .r(r), .q(q), .not_q(not_q));

    initial begin
        $display("Time\t| s | r | q | ~q");
        $monitor("%4d\t| %b | %b | %b | %b", $time, s, r, q, not_q);

        s = 0; r = 0; #10;
        s = 0; r = 1; #10;
        s = 1; r = 0; #10;
        s = 1; r = 1; #10;
        s = 0; r = 0; #10;
        s = 0; r = 1; #10;
        s = 1; r = 0; #10;
        s = 1; r = 1; #10;
        $finish;
    end
endmodule
