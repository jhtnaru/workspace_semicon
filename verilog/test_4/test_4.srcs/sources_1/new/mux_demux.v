`timescale 1ns / 1ps

// Multiplexer - 다수의 Input 중 Select Signal 따라서 하나의 Output 선택
// Data Flow 1 of 2 Multiplexer
module mux_2_1_dataflow (
    input [1:0] d,      // 2-bit Input Signal
    input s,
    output f
    );

    assign f = s ? d[1] : d[0]; // s = 0 → d[0], s = 1 → d[1] 출력
endmodule

// 동작적 1 of 2 Multiplexer
module mux_2_1_behavioral (
    input [1:0] d,
    input s,
    output reg f
    );

    always @(d or s) begin
        if (s == 1'b1) begin
            f = d[1];
        end
        else begin
            f = d[0];
        end
    end
endmodule

// 구조적 1 of 2 Multiplexer
module mux_2_1_structural (
    input [1:0] d,
    input s,
    output f
    );

    wire s_n;           // s의 NOT
    wire and_out_0;     // 1st AND Gate Output
    wire and_out_1;     // 2nd AND Gate Output

    not (s_n, s);
    and (and_out_0, d[0], s_n);
    and (and_out_1, d[1], s);
    
    or (f, and_out_0, and_out_1);
endmodule

// Data Flow 1 of 4 Multiplexer
module mux_4_1_dataflow (
    input [3:0] d,
    input [1:0] s,      // 2-bit Select Signal
    output f
    );

    assign f = d[s];    // s 가르키는 d 배열 원소 출력
endmodule

// 동작적 1 of 4 Multiplexer
module mux_4_1_behavioral (
    input [3:0] d,
    input [1:0] s,
    output reg f
    );

    always @(d or s) begin
        case (s)
            2'b00 : f = d[0];
            2'b01 : f = d[1];
            2'b10 : f = d[2];
            2'b11 : f = d[3];
            default : f = d[0];
            // default : f = 1'bx;     // 정의되지 않은 값 처리
        endcase
    end
endmodule

// 구조적 1 of 4 Multiplexer
module mux_4_1_structural (
    input [3:0] d,
    input [1:0] s,
    output f
    );
    
    // wire mux_out_0;     // 1st 1 of 2 MUX Output
    // wire mux_out_1;     // 2nd 1 of 2 MUX Output
    wire [1:0] mux_out;

    // mux_2_1_structural m0 (.d({d[1], d[0]}), .s(s[0]), .f(mux_out_0));
    // mux_2_1_structural m1 (.d({d[3], d[2]}), .s(s[0]), .f(mux_out_1));
    mux_2_1_structural m0 (.d(d[1:0]), .s(s[0]), .f(mux_out[0]));
    mux_2_1_structural m1 (.d(d[3:2]), .s(s[0]), .f(mux_out[1]));
    mux_2_1_structural m2 (.d(mux_out[1:0]), .s(s[1]), .f(f));
endmodule

// Data Flow 1 of 8 Multiplexer
module mux_8_1_dataflow (
    input [7:0] d,
    input [2:0] s,
    output f
    );

    assign f = d[s];
endmodule

// 동작적 1 of 8 Multiplexer
module mux_8_1_behavioral (
    input [7:0] d,
    input [2:0] s,
    output reg f
    );
    
    always @(d or s) begin
        case (s)
            3'b000 : f = d[0];
            3'b001 : f = d[1];
            3'b010 : f = d[2];
            3'b011 : f = d[3];
            3'b100 : f = d[4];
            3'b101 : f = d[5];
            3'b110 : f = d[6];
            3'b111 : f = d[7];
            default : f = d[0];
        endcase
    end
endmodule

// 구조적 1 of 8 Multiplexer
module mux_8_1_structural (
    input [7:0] d,
    input [2:0] s,
    output f
    );

    wire [1:0] mux_out;

    mux_4_1_structural m0 (.d(d[3:0]), .s(s[1:0]), .f(mux_out[0]));
    mux_4_1_structural m1 (.d(d[7:4]), .s(s[1:0]), .f(mux_out[1]));
    mux_2_1_structural m2 (.d(mux_out[1:0]), .s(s[2]), .f(f));
endmodule

// 동작적 1 of 2 Demultiplexer
module demux_1_2_behavioral (
    input d,
    input s,
    output reg [1:0] f
    );

    always @(*) begin
        case (s)        // s = 0 → out[0] = d, s = 1 → out[1] = d
            1'b0 : f = {1'b0, d};
            1'b1 : f = {d, 1'b0};
            default : f = 2'b00;
        endcase
    end
endmodule

// 구조적 1 of 2 Demultiplexer
module demux_1_2_structural (
    input d,
    input s,
    output [1:0] f
    );

    wire s_n;
    not (s_n, s);

    and (f[0], d, s_n);
    and (f[1], d, s);
endmodule

// Data Flow 1 of 2 Demultiplexer
module demux_1_2_dataflow (
    input d,
    input s,
    output [1:0] f
    );

    wire [1:0] out;

    assign f = {1'b0, d} << s;
    // assign f = (s == 1'b0) ? {1'b0, d} : {d, 1'b0};
endmodule

// 동작적 1 of 4 Demultiplexer
module demux_1_4_behavioral (
    input d,
    input [1:0] s,
    output reg [3:0] f
    );

    always @(*) begin
        case (s)
            2'b00 : f = {3'b000, d};
            2'b01 : f = {2'b00, d, 1'b0};
            2'b10 : f = {1'b0, d, 2'b00};
            2'b11 : f = {d, 3'b000};
            default : f = 4'b0000;
        endcase
    end
endmodule

// 구조적 1 of 4 Demultiplexer
module demux_1_4_structural (
    input d,
    input [1:0] s,
    output [3:0] f
    );

    wire [1:0] s_n;
    not (s_n[0], s[0]);
    not (s_n[1], s[1]);

    and (f[0], d, s_n[0], s_n[1]);
    and (f[1], d, s[0], s_n[1]);
    and (f[2], d, s_n[0], s[1]);
    and (f[3], d, s[0], s[1]);
endmodule

// Data Flow 1 of 4 Demultiplexer
module demux_1_4_dataflow (
    input d,
    input [1:0] s,
    output [3:0] f
    );

    assign f = {3'b000, d} << s;
    // Select Signal 따라 d 전달, 나머지 0
    // assign f = (s == 2'b00) ? {3'b000, d} :             // s = 00 → f[0] = d, f = 000d
    //            (s == 2'b01) ? {2'b00, d, 1'b0} :        // s = 01 → f[1] = d, f = 00d0
    //            (s == 2'b10) ? {1'b0, d, 2'b00} :        // s = 10 → f[2] = d, f = 0d00
    //            (s == 2'b11) ? {d, 3'b000} : 4'b0000;    // s = 11 → f[3] = d, f = d000
endmodule

// 동작적 1 of 8 Demultiplexer
module demux_1_8_behavioral (
    input d,
    input [2:0] s,
    output reg [7:0] f
    );

    always @(*) begin
        f = 8'b0000_0000;
        case (s)
            3'b000 : f[0] = d;
            3'b001 : f[1] = d;
            3'b010 : f[2] = d;
            3'b011 : f[3] = d;
            3'b100 : f[4] = d;
            3'b101 : f[5] = d;
            3'b110 : f[6] = d;
            3'b111 : f[7] = d;
            default : f = 8'b0000_0000;
        endcase
    end
endmodule

// 구조적 1 of 8 Demultiplexer
module demux_1_8_structural (
    input d,
    input [2:0] s,
    output [7:0] f
    );
    
    wire [2:0] s_n;
    not (s_n[0], s[0]);
    not (s_n[1], s[1]);
    not (s_n[2], s[2]);

    and (f[0], d, s_n[0], s_n[1], s_n[2]);
    and (f[1], d, s[0], s_n[1], s_n[2]);
    and (f[2], d, s_n[0], s[1], s_n[2]);
    and (f[3], d, s[0], s[1], s_n[2]);
    and (f[4], d, s_n[0], s_n[1], s[2]);
    and (f[5], d, s[0], s_n[1], s[2]);
    and (f[6], d, s_n[0], s[1], s[2]);
    and (f[7], d, s[0], s[1], s[2]);
endmodule

// Data Flow 1 of 8 Demultiplexer
module demux_1_8_dataflow (
    input d,
    input [2:0] s,
    output [7:0] f
    );

    assign f = {7'b0000000, d} << s;
endmodule

// 동작적 1 of 4 Multiplexer → 1 of 4 Demultiplexer
module mux_demux_4_1_4_behavioral (
    input [3:0] d,
    input [1:0] mux_s,
    input [1:0] demux_s,
    output reg [3:0] f
    );
    
    reg mux_f;

    always @(*) begin
        case (mux_s)
            2'b00 : mux_f = d[0];
            2'b01 : mux_f = d[1];
            2'b10 : mux_f = d[2];
            2'b11 : mux_f = d[3];
            default : mux_f = 1'b0;
        endcase
        f = 4'b0000;
        case (demux_s)
            2'b00 : f[0] = mux_f;
            2'b01 : f[1] = mux_f;
            2'b10 : f[2] = mux_f;
            2'b11 : f[3] = mux_f;
            default : f = 4'b0000;
        endcase
    end
endmodule

// 구조적 1 of 4 Multiplexer → 1 of 4 Demultiplexer
module mux_demux_4_1_4_structural (
    input [3:0] d,
    input [1:0] mux_s,
    input [1:0] demux_s,
    output [3:0] f
    );
    
    wire mux_f;

    mux_4_1_structural mux4 (.d(d), .s(mux_s), .f(mux_f));
    demux_1_4_structural demux4 (.d(mux_f), .s(demux_s), .f(f));
endmodule

// Data Flow 1 of 4 Multiplexer → 1 of 4 Demultiplexer
module mux_demux_4_1_4_dataflow (
    input [3:0] d,          // MUX Input
    input [1:0] mux_s,      // MUX Select Signal
    input [1:0] demux_s,    // DEMUX Select Signal
    output [3:0] f          // DEMUX Output
    );

    wire mux_f;             // MUX Output

    assign mux_f = d[mux_s];
    assign f = {3'b000, mux_f} << demux_s;
endmodule
