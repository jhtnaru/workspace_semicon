`timescale 1ns / 1ns

// Clock 분주 100㎒ → 1㎐, 0 ~ 59 Counter
// BCD 변환 00분00초, Segment 구분

// Clock 분주
module clock_divider (
    input clk, reset_p,
    output reg clk_div
    );

    reg [26:0] count = 1;       // 1억 까지 분주 가능

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            count <= 1;
            clk_div <= 0;
        end
        else begin
            if (count == 50_000_000) begin      // 0.5초 High ↔ Low, 1주기 1초 = 1㎐
                count <= 1;
                clk_div <= ~clk_div;
            end
            else begin
                count <= count + 1;
            end
        end
    end
endmodule

// Segment Scan Clock 분주
module clock_divider_seg (
    input clk,
    input reset_p,
    output reg clk_div_s
    );
    
    reg [15:0] count = 1;

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            count <= 1;
            clk_div_s <= 0;
        end
        else begin
            if (count == 25_000) begin          // 250㎲ High ↔ Low, 1주기 500㎲ = 2㎑
                count <= 1;
                clk_div_s <= ~clk_div_s;
            end
            else begin
                count <= count + 1;
            end
        end
    end
endmodule

// Time Counter, Second, Minute 구분, 10의 자리 0 ~ 5 + 1의 자리 0 ~ 9
module time_counter (
    input clk_div, reset_p,
    output reg [3:0] sec_ones, sec_tens,      // 초 1, 10의 자리
    output reg [3:0] min_ones, min_tens       // 분 1, 10의 자리
    );

    // 초 증가
    always @(posedge clk_div or posedge reset_p) begin
        if (reset_p) begin
            sec_ones <= 0;
            sec_tens <= 0;
        end
        else begin
            if (sec_ones == 9) begin
                sec_ones <= 0;
                if (sec_tens == 5) begin
                    sec_tens <= 0;
                end
                else begin
                    sec_tens <= sec_tens + 1;
                end
            end
            else begin
                sec_ones <= sec_ones + 1;
            end
        end
    end

    // 분 증가
    always @(posedge clk_div or posedge reset_p) begin
        if (reset_p) begin
            min_ones <= 0;
            min_tens <= 0;
        end
        else if (sec_tens == 5 && sec_ones == 9) begin
            if (min_ones == 9) begin
                min_ones <= 0;
                if (min_tens == 5) begin
                    min_tens <= 0;
                end
                else begin
                    min_tens <= min_tens + 1;
                end
            end
            else begin
                min_ones <= min_ones + 1;
            end
        end
    end
endmodule

// 출력 자리 변경해가며 자리와 숫자 출력
module display_scan_controller (
    input clk_div_s, reset_p,
    input [3:0] sec_ones, sec_tens,
    input [3:0] min_ones, min_tens,
    output reg [1:0] scan_count,
    output reg [3:0] select_digit
    );

    always @(posedge clk_div_s or posedge reset_p) begin
        if (reset_p) begin
            scan_count <= 0;
        end
        else begin
            scan_count <= scan_count + 1;       // 0 ~ 3 반복
        end
    end

    always @(*) begin
        case (scan_count)                       // 출력 자리에 맞춰 숫자 결정
            2'd0 : select_digit = sec_ones;
            2'd1 : select_digit = sec_tens;
            2'd2 : select_digit = min_ones;
            2'd3 : select_digit = min_tens;
            default : select_digit = 0;
        endcase
    end
endmodule

// 입력된 숫자를 seg 출력 변수로 수정
module seg_decoder (
    input [3:0] digit_in,
    output reg [7:0] seg_out
    );

    always @(*) begin
        case (digit_in)
            4'd0 : seg_out = 8'b11000000;
            4'd1 : seg_out = 8'b11111001;
            4'd2 : seg_out = 8'b10100100;
            4'd3 : seg_out = 8'b10110000;
            4'd4 : seg_out = 8'b10011001;
            4'd5 : seg_out = 8'b10010010;
            4'd6 : seg_out = 8'b10000010;
            4'd7 : seg_out = 8'b11111000;
            4'd8 : seg_out = 8'b10000000;
            4'd9 : seg_out = 8'b10011000;
            default : seg_out = 8'b11111111;
        endcase
    end
endmodule

// 입력된 자리를 an 출력 변수로 수정
module anode_selector (
    input [1:0] scan_count,
    output reg [3:0] an_out
    );

    always @(*) begin
        case (scan_count)
            2'd0 : an_out = 4'b1110;
            2'd1 : an_out = 4'b1101;
            2'd2 : an_out = 4'b1011;
            2'd3 : an_out = 4'b0111;
            default : an_out = 4'b1111;
        endcase
    end
endmodule

// 시계 Main Module
module digital_clock_top (
    input clk, reset_p,
    output [7:0] seg,
    output [3:0] an
    );
    
    wire clk_div;
    wire clk_div_s;
    wire [3:0] sec_ones_out, sec_tens_out;
    wire [3:0] min_ones_out, min_tens_out;
    wire [1:0] scan_count_out;
    wire [3:0] select_digit;

    clock_divider U1 (.clk(clk), .reset_p(reset_p), .clk_div(clk_div));
    clock_divider_seg U2 (.clk(clk), .reset_p(reset_p), .clk_div_s(clk_div_s));
    time_counter U3 (.clk_div(clk_div), .reset_p(reset_p),
                    .sec_ones(sec_ones_out), .sec_tens(sec_tens_out),
                    .min_ones(min_ones_out), .min_tens(min_tens_out));
    display_scan_controller U4 (.clk_div_s(clk_div_s), .reset_p(reset_p),
                    .sec_ones(sec_ones_out), .sec_tens(sec_tens_out),
                    .min_ones(min_ones_out), .min_tens(min_tens_out),
                    .scan_count(scan_count_out), .select_digit(select_digit));
    seg_decoder U5 (.digit_in(select_digit), .seg_out(seg));
    anode_selector U6 (.scan_count(scan_count_out), .an_out(an));
endmodule