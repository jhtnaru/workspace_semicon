`timescale 1ns / 1ps

module sr_latch (
    input s,
    input r,
    output q,
    output not_q
    );

    wire not_s, not_r;

    not (not_s, s);
    not (not_r, r);

    nand (q, not_s, not_q);
    nand (not_q, not_r, q);

    // nor (q, r, not_q);
    // nor (not_q, s, q);
endmodule
