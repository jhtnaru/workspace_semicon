`timescale 1ns / 1ps

module tb_ring_counter;
    reg clk, reset_p;
    wire [3:0] q;

    // ring_counter uut (.clk(clk), .reset_p(reset_p), .q(q));
    ring_counter_shift uut (.clk(clk), .reset_p(reset_p), .q(q));

    always #5 clk = ~clk;

    initial begin
        clk = 0; reset_p = 1; #10;
        reset_p = 0; #100;

        // 강제로 Input
        force uut.q = 4'b0110; #20;
        // default 동작 확인
        release uut.q; #20;
        $finish;
    end
endmodule

module tb_ring_counter_fnd;
    reg clk, reset_p;
    wire [3:0] q;

    // 확인 가능한 정도로 분주 시간 조정하여 Test
    ring_counter_fnd uut (.clk(clk), .reset_p(reset_p), .q(q));

    always #5 clk = ~clk;

    initial begin
        clk = 0; reset_p = 1; #10;
        reset_p = 0; #5000;
    end
endmodule


module tb_ring_counter_led;
    reg clk, reset_p;
    wire [15:0] led;

    // 확인 가능한 정도로 분주 시간 조정하여 Test
    ring_counter_led uut (.clk(clk), .reset_p(reset_p), .led(led));

    always #5 clk = ~clk;

    initial begin
        clk = 0; reset_p = 1; #10;
        reset_p = 0; #5000;
    end
endmodule
