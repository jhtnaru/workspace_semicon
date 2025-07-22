`timescale 1ns / 1ps

module tb_mux_2_1;
    reg [1:0] d;
    reg s;
    wire f;

    // mux_2_1_behavioral uut (.d(d), .s(s), .f(f));
    mux_2_1_structural uut (.d(d), .s(s), .f(f));
    // mux_2_1_dataflow uut (.d(d), .s(s), .f(f));

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

module tb_mux_4_1;
    reg [3:0] d;
    reg [1:0] s;
    wire f;

    // mux_4_1_behavioral uut (.d(d), .s(s), .f(f));
    mux_4_1_structural uut (.d(d), .s(s), .f(f));
    // mux_4_1_dataflow uut (.d(d), .s(s), .f(f));

    initial begin
        $display("Time\t| s  | d    | f");
        $monitor("%4d\t| %b | %b | %b", $time, s, d, f);

        d = 4'b0001;
        s = 2'b00; #10;
        s = 2'b01; #10;
        s = 2'b10; #10;
        s = 2'b11; #10;
        d = 4'b0010;
        s = 2'b00; #10;
        s = 2'b01; #10;
        s = 2'b10; #10;
        s = 2'b11; #10;
        d = 4'b0100;
        s = 2'b00; #10;
        s = 2'b01; #10;
        s = 2'b10; #10;
        s = 2'b11; #10;
        d = 4'b1000;
        s = 2'b00; #10;
        s = 2'b01; #10;
        s = 2'b10; #10;
        s = 2'b11; #10;
        $finish;
    end
endmodule

module tb_mux_8_1;
    reg [7:0] d;
    reg [2:0] s;
    wire f;

    // mux_8_1_behavioral uut (.d(d), .s(s), .f(f));
    mux_8_1_structural uut (.d(d), .s(s), .f(f));
    // mux_8_1_dataflow uut (.d(d), .s(s), .f(f));

    initial begin
        $display("Time\t| s   | d        | f");
        $monitor("%4d\t| %b | %b | %b", $time, s, d, f);

        d = 8'b11001010;
        s = 3'b000; #10;
        s = 3'b001; #10;
        s = 3'b010; #10;
        s = 3'b011; #10;
        s = 3'b100; #10;
        s = 3'b101; #10;
        s = 3'b110; #10;
        s = 3'b111; #10;
        $finish;
    end
endmodule

module tb_demux_1_2;
    reg d;
    reg s;
    wire [1:0] f;

    // demux_1_2_behavioral uut (.d(d), .s(s), .f(f));
    // demux_1_2_structural uut (.d(d), .s(s), .f(f));
    demux_1_2_dataflow uut (.d(d), .s(s), .f(f));

    initial begin
        $display("Time\t| s | d | f");
        $monitor("%4d\t| %b | %b | %b", $time, s, d, f);

        d = 1'b0;
        s = 1'b0; #10;
        s = 1'b1; #10;
        d = 1'b1;
        s = 1'b0; #10;
        s = 1'b1; #10;
        $finish;
    end
endmodule

module tb_demux_1_4;
    reg d;
    reg [1:0] s;
    wire [3:0] f;

    // demux_1_4_behavioral uut (.d(d), .s(s), .f(f));
    // demux_1_4_structural uut (.d(d), .s(s), .f(f));
    demux_1_4_dataflow uut (.d(d), .s(s), .f(f));
    
    initial begin
        $display("Time\t| s  | d | f");
        $monitor("%4d\t| %b | %b | %b", $time, s, d, f);

        d = 1'b0;
        s = 2'b00; #10;
        s = 2'b01; #10;
        s = 2'b10; #10;
        s = 2'b11; #10;
        d = 1'b1;
        s = 2'b00; #10;
        s = 2'b01; #10;
        s = 2'b10; #10;
        s = 2'b11; #10;
        $finish;
    end
endmodule

module tb_demux_1_8;
    reg d;
    reg [2:0] s;
    wire [7:0] f;

    // demux_1_8_behavioral uut (.d(d), .s(s), .f(f));
    // demux_1_8_structural uut (.d(d), .s(s), .f(f));
    demux_1_8_dataflow uut (.d(d), .s(s), .f(f));

    integer i, j;

    initial begin
        $display("Time\t| s   | d | f");
        $monitor("%4d\t| %b | %b | %b", $time, s, d, f);
        
        for (i = 0; i < 2; i = i + 1) begin
            for (j = 0; j < 8; j = j + 1) begin
                d = i;
                s = j;
                #10;
            end
        end
        $finish;
    end
endmodule

module tb_mux_demux;
    reg [3:0] d;
    reg [1:0] mux_s;
    reg [1:0] demux_s;
    wire [3:0] f;

    // mux_demux_4_1_4_behavioral uut (.d(d), .mux_s(mux_s), .demux_s(demux_s), .f(f));
    // mux_demux_4_1_4_structural uut (.d(d), .mux_s(mux_s), .demux_s(demux_s), .f(f));
    mux_demux_4_1_4_dataflow uut (.d(d), .mux_s(mux_s), .demux_s(demux_s), .f(f));

    integer i, j;

    initial begin
        $display("Time\t| d    | m_s | d_s | f");
        $monitor("%4d\t| %b | %b  | %b  | %b", $time, d, mux_s, demux_s, f);

        d = 4'b1001;
        for (i = 0; i < 4; i = i + 1) begin
            for (j = 0; j < 4; j = j + 1) begin
                mux_s = i;
                demux_s = j;
                #10;
            end
        end
        $finish;
    end
endmodule