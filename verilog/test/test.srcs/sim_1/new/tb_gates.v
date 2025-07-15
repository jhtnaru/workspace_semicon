`timescale 1ns / 1ps

module tb_gates;
    reg a, b;
    wire q0, q1, q2, q3, q4, q5, q6;

    gates uut (.a(a), .b(b), .q0(q0), .q1(q1), .q2(q2), .q3(q3), .q4(q4), .q5(q5), .q6(q6));

    initial begin
        $display("Time\t a b | q0 q1 q2 q3 q4 q5 q6");
        $monitor("%4d\t %b %b |  %b  %b  %b  %b  %b  %b  %b", $time, a, b,
                    q0, q1, q2, q3, q4, q5, q6);

        a = 0; b = 0; #10;      // #10은 10ns 의미
        a = 0; b = 1; #10;
        a = 1; b = 0; #10;
        a = 1; b = 1; #10;
        $finish;
    end
endmodule
