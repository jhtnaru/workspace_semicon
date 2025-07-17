`timescale 1ns / 1ps

module tb_mux_2_1;
    reg [1:0] d;
    reg s;
    wire f;

    mux_2_1 uut (.d(d), .s(s), .f(f));

    initial begin
        $display("Time | s | d  | f");
        $monitor("%4d | %b | %b | %b", $time, s, d, f);

        d = 2'b00; s = 0; #10;
                   s = 1; #10;
        d = 2'b01; s = 0; #10;
                   s = 1; #10;
        d = 2'b10; s = 0; #10;
                   s = 1; #10;
        d = 2'b11; s = 0; #10;
                   s = 1; #10;
        $finish;
    end
endmodule
