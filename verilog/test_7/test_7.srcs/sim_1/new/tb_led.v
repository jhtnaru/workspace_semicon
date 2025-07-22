`timescale 1ns / 1ps

module tb_led_blink_1hz;
    reg clk;
    reg reset;
    wire [7:0] led;

    led_blink_1hz dut (.clk(clk), .reset(reset), .led(led));

    initial begin
        clk = 0;
        forever begin
            #5;
            clk = ~clk;
        end
    end

    initial begin
        reset = 1; #20;
        reset = 0; 
    end

    initial begin
        #(100_000_000 * 10);        // 10초 Simulation
        $finish;
    end
endmodule
