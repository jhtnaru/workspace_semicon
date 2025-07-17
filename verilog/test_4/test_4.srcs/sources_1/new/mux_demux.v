`timescale 1ns / 1ps

module mux_2_1 (
    input [1:0] d,      // 2 Input Signal
    input s,
    output f
    );

    assign f = s ? d[1] : d[0]; // s = 0 → d[0], s = 1 → d[1] 출력
endmodule
