`timescale 1ns / 1ps

module tb_D_flip_flop;
    reg clk;
    reg d;
    wire q;

    D_flip_flop_basic uut (.clk(clk), .d(d), .q(q));

    // Clock 생성, 주기 10ns(0.00000001s) = 주파수 100000000㎒
    initial begin
        clk = 0;
        forever begin
            #5 clk = ~clk;
        end
    end

    initial begin
        d = 0;
        $display("Time\t| clk |  d  |  q");
        $monitor("%4d\t|  %b  |  %b  |  %b", $time, clk, d, q);
        #10 d = 1;
        #10 d = 0;
        #10 d = 1;
        #10 $finish;
    end
endmodule

module tb_D_flip_flop_test;
    reg clk;
    reg d;
    reg enable;
    reg reset_p;
    wire q;

    // D_flip_flop_neg dut (
    //     .clk(clk),
    //     .d(d),
    //     .enable(enable),
    //     .reset_p(reset_p),
    //     .q(q)
    // );

    D_flip_flop_pos dut (
        .clk(clk),
        .d(d),
        .enable(enable),
        .reset_p(reset_p),
        .q(q)
    );

    initial begin
        clk = 0;
        forever begin
            #5 clk = ~clk;
        end
    end

    initial begin
        d = 0; reset_p = 1; enable = 0; #12;
        reset_p = 0; #10;
        enable = 1; d = 1; #10;
        d = 0; #10;
        d = 1; #10;
        enable = 0; d = 0; #20;
        enable = 1; d = 1; #10;
        reset_p = 1; #10;
        reset_p = 0; #10;
        $stop;
    end

    initial begin
        $display("Time\t| clk | d | en | re | q");
        $monitor("%4d\t| %b   | %b | %b  | %b  | %b", $time, clk, d, enable, reset_p, q);
    end
endmodule

module tb_T_flip_flop;
    reg clk, reset_p, t;
    wire q;

    // T_flip_flop_neg uut (.clk(clk), .reset_p(reset_p), .t(t), .q(q));
    T_flip_flop_pos uut (.clk(clk), .reset_p(reset_p), .t(t), .q(q));

    initial begin
        clk = 0;
        forever begin
            #5 clk = ~clk;
        end
    end

    initial begin
        reset_p = 1; t = 0; #10;
        reset_p = 0; t = 1; #20;
        t = 0; #10;
        t = 1; #20;
        reset_p = 1; #10;
        reset_p = 0; t = 1; #30;
        $finish;
    end

    initial begin
        $display("Time\t| clk | t | re | q");
        $monitor("%4d\t|  %b  | %b | %b  | %b", $time, clk, t, reset_p, q);
    end
endmodule

module tb_counter_asyc;
    reg clk, reset_p;
    wire [3:0] count;

    // up_counter_asyc uut (.clk(clk), .reset_p(reset_p), .count(count));
    down_counter_asyc uut (.clk(clk), .reset_p(reset_p), .count(count));

    always #5 clk = ~clk;

    initial begin
        $display("Time\t| clk | re | count");
        $monitor("%4d\t|  %b  | %b  | %b", $time, clk, reset_p, count);
        clk = 0;
        reset_p = 1; #10;
        reset_p = 0; #190;
        $finish;
    end
endmodule

module tb_up_counter_pos;
    reg clk, reset_p, enable;
    wire [3:0] count;

    up_counter_pos uut (.clk(clk), .reset_p(reset_p), .enable(enable), .count(count));

    initial begin
        clk = 0;
        forever begin
            #5 clk = ~clk;
        end
    end

    initial begin
        reset_p = 1; enable = 0;    #10;
        reset_p = 0;                #10;
        enable = 1;                 #180;
        enable = 0;                 #10;
        reset_p = 1;                #10;
        reset_p = 0;                #10;
        $finish;
    end
endmodule

module tb_down_counter_pos;
    reg clk, reset_p, enable;
    wire [3:0] count;

    down_counter_pos uut (.clk(clk), .reset_p(reset_p), .enable(enable), .count(count));

    initial begin
        clk = 0;
        forever begin
            #5 clk = ~clk;
        end
    end

    initial begin
        reset_p = 1; enable = 0;    #10;
        reset_p = 0;                #10;
        enable = 1;                 #180;
        enable = 0;                 #10;
        reset_p = 1;                #10;
        reset_p = 0;                #10;
        $finish;
    end
endmodule