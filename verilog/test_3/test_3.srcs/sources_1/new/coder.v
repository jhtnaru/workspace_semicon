`timescale 1ns / 1ps

// 동작적 2X4 Decoder
module decoder_2X4_behavioral (
    input [1:0] code,
    output reg [3:0] signal
    );

    // if문 이용
    // always @(code) begin
    //     if (code == 2'b00) begin signal = 4'b0001; end 
    //     else if (code == 2'b01) begin signal = 4'b0010; end
    //     else if (code == 2'b10) begin signal = 4'b0100; end
    //     else begin signal = 4'b1000; end
    // end

    // case문 이용
    always @(code) begin
        case (code)
            2'b00 : signal = 4'b0001;
            2'b01 : signal = 4'b0010;
            2'b10 : signal = 4'b0100;
            2'b11 : signal = 4'b1000;
            default : signal = 4'b0000;
        endcase
    end
endmodule

// Data Flow 2X4 Decoder
module decoder_2X4_dataflow (
    input [1:0] code,
    output [3:0] signal
    );

    // assign signal = (code == 2'b00) ? 4'b0001 :
    //                 (code == 2'b01) ? 4'b0010 :
    //                 (code == 2'b10) ? 4'b0100 : 4'b1000;

    assign signal[0] = (~code[1]) & (~code[0]);
    assign signal[1] = (~code[1]) & ( code[0]);
    assign signal[2] = ( code[1]) & (~code[0]);
    assign signal[3] = ( code[1]) & ( code[0]);
endmodule

// 구조적 2X4 Decoder
module decoder_2X4_structural (
    input [1:0] code,
    output [3:0] signal
    );

    wire n0, n1;        // NOT 신호

    not u_not0 (n0, code[0]);
    not u_not1 (n1, code[1]);

    and u_and0 (signal[0], n1, n0);
    and u_and1 (signal[1], n1, code[0]);
    and u_and2 (signal[2], code[1], n0);
    and u_and3 (signal[3], code[1], code[0]);
endmodule

// 7-Segment Decoder
module decoder_7seg (
    input [3:0] hex_value,
    output reg [6:0] seg_7,
    output reg dp,
    output reg [3:0] com_an
    );

    always @(hex_value) begin
        com_an = 4'b0000;
        dp = 1;
        case (hex_value)       //GFEDCBA, Common-Anode
            4'b0000 : seg_7 = 7'b1000000;       // 0
            4'b0001 : seg_7 = 7'b1111001;       // 1
            4'b0010 : seg_7 = 7'b0100100;       // 2
            4'b0011 : seg_7 = 7'b0110000;       // 3
            4'b0100 : seg_7 = 7'b0011001;       // 4
            4'b0101 : seg_7 = 7'b0010010;       // 5
            4'b0110 : seg_7 = 7'b0000010;       // 6
            4'b0111 : seg_7 = 7'b1111000;       // 7
            4'b1000 : seg_7 = 7'b0000000;       // 8
            4'b1001 : seg_7 = 7'b0011000;       // 9
            4'b1010 : seg_7 = 7'b0001000;       // A
            4'b1011 : seg_7 = 7'b0000011;       // B
            4'b1100 : seg_7 = 7'b1000110;       // C
            4'b1101 : seg_7 = 7'b0100001;       // D
            4'b1110 : seg_7 = 7'b0000110;       // E
            4'b1111 : seg_7 = 7'b1001110;       // F
        endcase
    end
endmodule

// 동작적 4X2 Encoder
module encoder_4X2_behavioral (
    output reg [1:0] code,      // 2-bit Output, Input 중 켜진 위치를 이진수 Output
    input [3:0] signal          // 4-bit Input, 4개 신호 중 하나만 1이라고 가정
    );

    // always @(signal) begin      // signal 변하면 동작
    //     if (signal == 4'b0001) begin            // signal 1의 위치 → code
    //         code = 2'b00;
    //     end
    //     else if (signal == 4'b0010) begin
    //         code = 2'b01;
    //     end
    //     else if (signal == 4'b0100) begin
    //         code = 2'b10;
    //     end
    //     else if (signal == 4'b1000) begin
    //         code = 2'b11;
    //     end
    //     else begin
    //         code = 2'b00;
    //     end
    // end

    always @(signal) begin
        case (signal)
            4'b0001 : code = 2'b00;
            4'b0010 : code = 2'b01;
            4'b0100 : code = 2'b10;
            4'b1000 : code = 2'b11;
            default : code = 2'b00;
        endcase
    end
endmodule

// Data Flow 4X2 Encoder
module encoder_4X2_dataflow (
    output [1:0] code,
    input [3:0] signal
    );

    assign code = (signal == 4'b0001) ? 2'b00 :
                  (signal == 4'b0010) ? 2'b01 :
                  (signal == 4'b0100) ? 2'b10 :
                  (signal == 4'b1000) ? 2'b11 : 2'b00;
endmodule

// 구조적 4X2 Encoder
module encoder_4X2_structural (
    output [1:0] code,
    input [3:0] signal
    );
    
    wire a0, a1;
    
    // Signal 0100 or 1000 → code[1] = 1
    or or1 (a1, signal[2], signal[3]);
    // Signal 0010 or 1000 → code[0] = 1
    or or0 (a0, signal[1], signal[3]);

    assign code = {a1, a0};
endmodule