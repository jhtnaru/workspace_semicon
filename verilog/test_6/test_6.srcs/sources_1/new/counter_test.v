`timescale 1ns / 1ps

// Binary → 4자리 BCD
module bin_to_dec (
    input [13:0] bin,       // 12-bit Binary Input
    output reg [15:0] bcd   // 16-bit BCD Output (4-bit X 4자리)
    );

    integer i;

    always @(bin) begin
        bcd = 0;            // Initial Value
        for (i = 0; i < 14; i = i + 1) begin
            // BCD Algorithm
            // 1st 단위 bit 자리별로 5 이상 → + 3
            if (bcd[3:0] >= 5)   bcd[3:0] = bcd[3:0] + 3;
            if (bcd[7:4] >= 5)   bcd[7:4] = bcd[7:4] + 3;
            if (bcd[11:8] >= 5)  bcd[11:8] = bcd[11:8] + 3;
            if (bcd[15:12] >= 5) bcd[15:12] = bcd[15:12] + 3;

            // 2nd 1-bit Left Shift + 새 bit Input
            bcd = {bcd[14:0], bin[13 - i]};
        end
    end
endmodule

// BCD 4자리 7-Segment 변환
module decoder_7seg_4 (
    input [15:0] bcd,
    input [1:0] sel,
    output reg [6:0] seg,
    output reg dp,
    output reg [3:0] com_an
    );

    reg [3:0] bcd_w;

    always @(*) begin
        case (sel)                  // 출력 위치 선택
            2'b00 : begin           // 1의 자리
                com_an = 4'b1110;
                bcd_w = bcd[3:0];
                dp = 1;
            end                     // 10의 자리
            2'b01 : begin
                com_an = 4'b1101;
                bcd_w = bcd[7:4];
                dp = 0;
            end                     // 100의 자리
            2'b10 : begin
                com_an = 4'b1011;
                bcd_w = bcd[11:8];
                dp = 1;
            end
            2'b11 : begin           // 1000의 자리
                com_an = 4'b0111;
                bcd_w = bcd[15:12];
                dp = 1;
            end
            default : begin         // 기본 출력 없음
                com_an = 4'b1111;
                bcd_w = bcd[3:0];
                dp = 1;
            end
        endcase
        case (bcd_w)       //GFEDCBA, Common-Anode
            4'b0000 : seg = 7'b1000000;       // 0
            4'b0001 : seg = 7'b1111001;       // 1
            4'b0010 : seg = 7'b0100100;       // 2
            4'b0011 : seg = 7'b0110000;       // 3
            4'b0100 : seg = 7'b0011001;       // 4
            4'b0101 : seg = 7'b0010010;       // 5
            4'b0110 : seg = 7'b0000010;       // 6
            4'b0111 : seg = 7'b1111000;       // 7
            4'b1000 : seg = 7'b0000000;       // 8
            4'b1001 : seg = 7'b0011000;       // 9
            default : seg = 7'b1111111;
        endcase
    end
endmodule

// 4자리 Up Counter, 0 ~ 9999
module up_counter_pos_4 (
    input clk,
    input reset_p,
    input enable,
    output reg [13:0] count
    );

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            count <= 0;
        end
        else if (enable) begin
            if (count >= 10000) begin   // 0 ~ 9999 Count
                count <= 0;
            end
            else begin
                count <= count + 1;     // enable = 1 일때만 count 증가
            end
        end
    end
endmodule

// 0.1초(=10㎐) 단위 4자리 Up Counter 출력
module up_counter_4_test (
    input clk,
    input sw_0,
    input sw_1,
    output [6:0] seg,
    output dp,
    output [3:0] com_an
    );

    reg [26:0] count_s = 1;
    reg clk_s;
    reg [9:0] count_f = 1;
    reg [1:0] sel = 2'b00;
    reg [13:0] count;
    wire [15:0] bcd;

    always @(posedge clk) begin
        if (sw_0) begin                             // Reset
            count_s <= 1;
            clk_s <= 0;
        end
        else begin
            if (count_s >= 5_000_000) begin        // 0.05초 마다 0 ↔ 1, 1주기 = 0.1초, 10㎐
                count_s <= 1;
                clk_s <= ~clk_s;
            end
            else begin
                count_s <= count_s + 1;             // Delay
            end
        end

        if (count_f >= 1_000) begin                 // 10㎲ 마다 출력 자리 변경
            count_f <= 1;
            sel <= sel + 1;                         // 2-bit 이므로 Overflow로 인해 0 ~ 3 반복
        end
        else begin
            count_f <= count_f + 1;                 // Delay
        end
    end

    // 0 ~ 9999 까지 Count
    always @(posedge clk_s or posedge sw_0) begin
        if (sw_0) begin
            count <= 0;
        end
        else if (sw_1) begin
            if (count >= 10000) begin   // 0 ~ 9999 Count
                count <= 0;
            end
            else begin
                count <= count + 1;     // enable = 1 일때만 count 증가
            end
        end
    end

    // up_counter_pos_4 UC1 (.clk(clk_s), .reset_p(sw_0), .enable(sw_1), .count(count));
    // Count된 Binary → 4자리 BCD 변환
    bin_to_dec BTC1 (.bin(count), .bcd(bcd));
    // sel에 따라 자리를 바꿔가며 출력
    decoder_7seg_4 SEG (.bcd(bcd), .sel(sel), .seg(seg), .dp(dp), .com_an(com_an));
endmodule