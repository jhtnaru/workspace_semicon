`timescale 1ns / 1ps

// Binary → BCD 방식 → Decimal
module bin_to_dec (
    input [11:0] bin,       // 12-bit Binary Input
    output reg [15:0] bcd   // 16-bit BCD Output (4-bit X 4자리)
    );

    integer i;

    always @(bin) begin
        bcd = 0;            // Initial Value
        for (i = 0; i < 12; i = i + 1) begin
            // BCD Algorithm
            // 1st 단위 bit 자리별로 5 이상 → + 3
            if (bcd[3:0] >= 5)   bcd[3:0] = bcd[3:0] + 3;
            if (bcd[7:4] >= 5)   bcd[7:4] = bcd[7:4] + 3;
            if (bcd[11:8] >= 5)  bcd[11:8] = bcd[11:8] + 3;
            if (bcd[15:12] >= 5) bcd[15:12] = bcd[15:12] + 3;

            // 2nd 1-bit Left Shift + 새 bit Input
            bcd = {bcd[14:0], bin[11 - i]};
        end
    end
endmodule
