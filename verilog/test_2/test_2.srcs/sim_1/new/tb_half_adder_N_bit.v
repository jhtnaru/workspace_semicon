`timescale 1ns / 1ps

module tb_half_adder_N_bit;
    parameter N = 8;

    reg inc;
    reg [N-1:0] load_data;
    wire [N-1:0] sum;

    half_adder_N_bit #(N) uut (
        .inc(inc),
        .load_data(load_data),
        .sum(sum)
    );

    initial begin
        $display("Time\tinc\tload_data\t|\tsum");
        $monitor("%4d\t%b\t%b\t|\t%b", $time, inc, load_data, sum);

        // Test
        inc = 0; load_data = 8'b00000000; #10;
        inc = 1; load_data = 8'b00000000; #10;
        inc = 1; load_data = 8'b00000001; #10;
        inc = 1; load_data = 8'b00001111; #10;
        inc = 1; load_data = 8'b11111111; #10;
        inc = 0; load_data = 8'b10101010; #10;
        inc = 1; load_data = 8'b10101010; #10;
        #10 $finish;
    end
endmodule
