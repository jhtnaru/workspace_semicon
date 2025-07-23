`timescale 1ns / 1ps

module tb_edge_detector;
    reg clk, reset_p, cp;
    wire p_edge_pos, n_edge_pos;
    wire p_edge_neg, n_edge_neg;

    edge_detector_pos uut_p (.clk(clk), .reset_p(reset_p), .cp(cp),
                            .p_edge(p_edge_pos), .n_edge(n_edge_pos));
    edge_detector_neg uut_n (.clk(clk), .reset_p(reset_p), .cp(cp),
                            .p_edge(p_edge_neg), .n_edge(n_edge_neg));

    always #5 clk = ~clk;

    initial begin
        clk = 0; reset_p = 1; cp = 0; #12
        reset_p = 0; #10;
        cp = 1; #20;
        cp = 0; #15;
        cp = 1; #25;
        cp = 0; #25;
        cp = 1; #10;
        cp = 0; #23;
        $stop;
    end
endmodule
