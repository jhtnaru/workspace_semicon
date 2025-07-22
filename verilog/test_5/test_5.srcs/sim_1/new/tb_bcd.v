`timescale 1ns / 1ps

module tb_bin_to_dec;
    reg [11:0] bin;
    wire [15:0] bcd;

    bin_to_dec uut (.bin(bin), .bcd(bcd));

    initial begin
        bin = 12'b0000_0000_0000; #10;  // 0
        bin = 12'b0000_0000_0001; #10;  // 1
        bin = 12'b0000_0000_1001; #10;  // 9
        bin = 12'b0000_0001_0100; #10;  // 20
        bin = 12'b0000_1011_1001; #10;  // 185
        bin = 12'b1011_0110_1101; #10;  // 2925
        bin = 12'b1111_1111_1111; #10;  // 4095
        $finish;
        // $stop;      // $finish 종료, $stop 일시정지, Debuggin, 중간점검 등
    end
    
    initial begin
        $display("Time\t| BIN                 → BCD");
        $monitor("%4d\t| %b (%4d) → %b (%0d%0d%0d%0d)",
            $time, bin, bin, bcd, bcd[15:12], bcd[11:8], bcd[7:4], bcd[3:0]);
    end
endmodule
