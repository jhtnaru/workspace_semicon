`timescale 1ns / 1ns

// Button 1 btn_start_stop, Button 2 btn_reset
// 0.1초 단위 증가 (10㎐), MM:SS 형식

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
            if (count == 500_000) begin     // 500_000
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
    output reg clk_div_s
    );
    
    reg [15:0] count = 1;

    always @(posedge clk) begin
        if (count == 2_500) begin          // 25_000
            count <= 1;
            clk_div_s <= ~clk_div_s;
        end
        else begin
            count <= count + 1;
        end
    end
endmodule

//
module stopwatch_counter (
    input clk_div, reset_p,
    input btn_start_stop, btn_reset,
    output reg [3:0] ssub_secs, sub_secs,
    output reg [3:0] sec_ones, sec_tens,
    output reg [3:0] min_ones, min_tens,
    output reg [3:0] hour_ones, hour_tens,
    output reg [3:0] ampm
    );

    parameter IDEL     = 2'b00;             // 대기
    parameter RUNNING  = 2'b01;             // 동작
    parameter PAUSED   = 2'b10;             // 일시정지
    reg [1:0] cur_state, next_state;

    // 초 증가
    always @(posedge clk_div or posedge reset_p) begin
        if (reset_p) begin
            cur_state <= IDEL;
        end
        else begin
            cur_state <= next_state;
        end
    end

    always @(*) begin
        case (cur_state)
            IDEL : begin
                // 대기일때 Button 누르면 Running
                next_state = btn_start_stop ? RUNNING : IDEL;
            end
            RUNNING : begin
                next_state = btn_start_stop ? PAUSED : RUNNING;
            end
            PAUSED : begin
                if (btn_reset) begin
                    next_state = IDEL;
                end
                else if (btn_start_stop) begin
                    next_state = RUNNING;
                end
                else begin
                    next_state = PAUSED;
                end
            end
            default : next_state = IDEL;
        endcase
    end

    always @(posedge clk_div or posedge reset_p) begin
        if (reset_p || btn_reset || cur_state == IDEL) begin
            ssub_secs <= 0;
            sub_secs <= 0;
            sec_ones <= 0;
            sec_tens <= 0;
            min_ones <= 0;
            min_tens <= 0;
            hour_ones <= 0;
            hour_tens <= 0;
        end
        else if (cur_state == RUNNING) begin
            if(ssub_secs == 9) begin
                ssub_secs <= 0;
                if (sub_secs == 9) begin
                    sub_secs <= 0;
                    if (sec_ones == 9) begin
                        sec_ones <= 0;
                        if (sec_tens == 5) begin
                            sec_tens <= 0;
                            if (min_ones == 9) begin
                                min_ones <= 0;
                                if (min_tens == 5) begin
                                    min_tens <= 0;
                                    if (hour_tens == 0) begin
                                        if (hour_ones == 9) begin
                                            hour_ones <= 0;
                                            hour_tens <= 1;
                                        end
                                        else begin
                                            hour_ones <= hour_ones + 1;
                                        end
                                    end
                                    else if (hour_tens == 1) begin
                                        if (hour_ones == 0) begin
                                            hour_ones <= 1;
                                        end
                                        else if (hour_ones == 1) begin
                                            hour_ones <= 2;
                                            ampm <= ~ampm;
                                        end
                                        else if (hour_ones == 2) begin
                                            hour_ones <= 1;
                                            hour_tens <= 0;
                                        end
                                    end
                                end
                                else begin
                                    min_tens <= min_tens + 1;
                                end
                            end
                            else begin
                                min_ones <= min_ones + 1;
                            end
                        end
                        else begin
                            sec_tens <= sec_tens + 1;
                        end
                    end
                    else begin
                        sec_ones <= sec_ones + 1;
                    end
                end
                else begin
                    sub_secs <= sub_secs + 1;
                end
            end
            else begin
                ssub_secs <= ssub_secs + 1;
            end
        end
    end
endmodule


module button_debounce (
    input clk,
    input btn_in,
    output reg btn_out
    );

    reg [23:0] count = 0;
    reg btn_sync_0 = 0, btn_sync_1 = 0;
    reg btn_state = 0;
    // wire stable = (count == 1_000_000);

    // 동기화
    always @(posedge clk) begin
        btn_sync_0 <= btn_in;
        btn_sync_1 <= btn_sync_0;
    end

    // Counter 기반 Debounce
    always @(posedge clk) begin
        if (btn_sync_1 != btn_state) begin
            count <= count + 1;
            if (count >= 1_000_000) begin
                btn_state <= btn_sync_1;
                btn_out <= btn_sync_1;
                count <= 0;
            end
        end
        else begin
            count <= 0;
        end
    end
endmodule

// 출력 자리 변경해가며 자리와 숫자 출력
module display_scan_controller (
    input clk_div_s,
    input [3:0] s_1st, s_2nd, s_3rd, s_4th,
    output reg [1:0] scan_count,
    output reg [3:0] select_digit
    );

    always @(posedge clk_div_s) begin
        scan_count <= scan_count + 1;       // 0 ~ 3 반복
    end

    always @(*) begin
        case (scan_count)                       // 출력 자리에 맞춰 숫자 결정
            2'd0 : select_digit = s_1st;
            2'd1 : select_digit = s_2nd;
            2'd2 : select_digit = s_3rd;
            2'd3 : select_digit = s_4th;
            default : select_digit = 0;
        endcase
    end
endmodule

// 입력된 숫자를 seg 출력 변수로 수정
module seg_decoder_a (
    input [1:0] scan_count,
    input [3:0] digit_in,
    output reg [6:0] seg_out,
    output reg dp_out
    );

    always @(*) begin
        case (digit_in)
            4'd0 : seg_out = 7'b1000000;
            4'd1 : seg_out = 7'b1111001;
            4'd2 : seg_out = 7'b0100100;
            4'd3 : seg_out = 7'b0110000;
            4'd4 : seg_out = 7'b0011001;
            4'd5 : seg_out = 7'b0010010;
            4'd6 : seg_out = 7'b0000010;
            4'd7 : seg_out = 7'b1111000;
            4'd8 : seg_out = 7'b0000000;
            4'd9 : seg_out = 7'b0011000;
            default : seg_out = 7'b1111111;
        endcase
        case (scan_count)
            2'd0 : dp_out = 0;
            2'd1 : dp_out = 1;
            2'd2 : dp_out = 0;
            2'd3 : dp_out = 1;
            default : dp_out = 1;
        endcase
    end
endmodule

module seg_decoder_c (
    input [1:0] scan_count,
    input [3:0] digit_in,
    output reg [6:0] seg_out,
    output reg dp_out
    );

    always @(*) begin
        case (digit_in)
            4'd0 : seg_out = 7'b0111111;
            4'd1 : seg_out = 7'b0000110;
            4'd2 : seg_out = 7'b1011011;
            4'd3 : seg_out = 7'b1001111;
            4'd4 : seg_out = 7'b1100110;
            4'd5 : seg_out = 7'b1101101;
            4'd6 : seg_out = 7'b1111101;
            4'd7 : seg_out = 7'b0000111;
            4'd8 : seg_out = 7'b1111111;
            4'd9 : seg_out = 7'b1100111;
            4'd10 : seg_out = 7'b1011111;
            4'd11 : seg_out = 7'b1110011;
            4'd12 : seg_out = 7'b1010101;
            default : seg_out = 7'b0000000;
        endcase
        case (scan_count)
            2'd0 : dp_out = 1;
            2'd1 : dp_out = 0;
            2'd2 : dp_out = 1;
            2'd3 : dp_out = 0;
            default : dp_out = 0;
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


module stopwatch_top (
    input clk, reset_p,
    input btn_start_stop, btn_reset,
    input sw_1,
    output [6:0] seg,
    output dp,
    output [7:0] JB,
    output [3:0] an,
    output [3:0] JC,
    output reg [15:0] led
    );

    wire clk_div, clk_div_s;

    wire [3:0] ssub_secs, sub_secs;
    wire [3:0] sec_ones, sec_tens;
    wire [3:0] min_ones, min_tens;
    wire [3:0] hour_ones, hour_tens;
    wire [3:0] ampm;
    reg [3:0] ampm_r;
    reg [3:0] sec_r;

    wire [1:0] scan_count_1, scan_count_2;
    wire [3:0] select_digit_1, select_digit_2;
    wire btn_ss_clean, btn_re_clean;


    clock_divider U1 (.clk(clk), .reset_p(reset_p), .clk_div(clk_div));
    clock_divider_seg U2 (.clk(clk), .clk_div_s(clk_div_s));
    
    button_debounce B1 (.clk(clk), .btn_in(btn_start_stop), .btn_out(btn_ss_clean));
    button_debounce B2 (.clk(clk), .btn_in(btn_reset), .btn_out(btn_re_clean));
    
    stopwatch_counter U3 (.clk_div(clk_div), .reset_p(reset_p),
                        .btn_start_stop(btn_ss_clean), .btn_reset(btn_re_clean),
                        .ssub_secs(ssub_secs), .sub_secs(sub_secs),
                        .sec_ones(sec_ones), .sec_tens(sec_tens),
                        .min_ones(min_ones), .min_tens(min_tens),
                        .hour_ones(hour_ones), .hour_tens(hour_tens),
                        .ampm(ampm));

    always @(ampm) begin
        if (ampm == 4'b0000) begin
            ampm_r = 4'b1010;
        end
        else if (ampm == 4'b1111) begin
            ampm_r = 4'b1011;
        end
    end

    always @(posedge clk_div or posedge reset_p) begin
        if (reset_p) begin
            led <= 16'b0000_0000_0000_0000;
        end
        else begin
            led <= 16'b0000_0000_0000_0000;
            sec_r <= sec_tens + 10;
            led[sec_ones] <= 1'b1;
            led[sec_r] <= 1'b1;
        end
    end

    display_scan_controller U4 (.clk_div_s(clk_div_s),
                        .s_1st(sec_ones), .s_2nd(sec_tens),
                        .s_3rd(min_ones), .s_4th(min_tens),
                        .scan_count(scan_count_1), .select_digit(select_digit_1));
    seg_decoder_a U5 (.scan_count(scan_count_1), .digit_in(select_digit_1), .seg_out(seg), .dp_out(dp));
    anode_selector U6 (.scan_count(scan_count_1), .an_out(an));

    display_scan_controller U7 (.clk_div_s(clk_div_s),
                        .s_1st(hour_ones), .s_2nd(hour_tens),
                        .s_3rd(4'b1100), .s_4th(ampm_r),
                        .scan_count(scan_count_2), .select_digit(select_digit_2));
    seg_decoder_c U8 (.scan_count(scan_count_2), .digit_in(select_digit_2), .seg_out(JB[6:0]), .dp_out(JB[7]));
    anode_selector U9 (.scan_count(scan_count_2), .an_out(JC));
endmodule


module stopwatch_top_2 (
    input clk, reset_p,
    input btn_start_stop, btn_reset,
    input sw_1,
    output [6:0] seg,
    output dp,
    output [7:0] JB,
    output [3:0] an,
    output [3:0] JC,
    output reg [15:0] led
    );

    reg clk_div, clk_div_1, clk_div_2, clk_div_s;
    reg [26:0] count_1 = 1;
    reg [26:0] count_2 = 1;
    reg [26:0] count_s = 1;

    wire [3:0] ssub_secs, sub_secs;
    wire [3:0] sec_ones, sec_tens;
    wire [3:0] min_ones, min_tens;
    wire [3:0] hour_ones, hour_tens;
    wire [3:0] ampm;
    reg [3:0] ampm_r;
    reg [3:0] sec_r;

    reg [3:0] s_1st_1, s_2nd_1, s_3rd_1, s_4th_1;

    wire [1:0] scan_count_1, scan_count_2;
    wire [3:0] select_digit_1, select_digit_2;
    wire btn_ss_clean, btn_re_clean;

    always @(posedge clk) begin
        if (reset_p) begin
            count_1 <= 1;
            count_2 <= 1;
            clk_div <= 0;
            clk_div_1 <= 0;
            clk_div_2 <= 0;
        end
        else begin
            if (count_1 == 500_000) begin
                count_1 <= 1;
                clk_div_1 <= ~ clk_div_1;
            end
            else begin
                count_1 <= count_1 + 1;
            end
            if (count_2 == 5_000) begin
                count_2 <= 1;
                clk_div_2 <= ~ clk_div_2;
            end
            else begin
                count_2 <= count_2 + 1;
            end
            if (count_s == 2_500) begin
                count_s <= 1;
                clk_div_s <= ~ clk_div_s;
            end
            else begin
                count_s <= count_s + 1;
            end
        end

        if (sw_1 == 0) begin
            clk_div <= clk_div_1;
        end
        else if (sw_1 == 1) begin
            clk_div <= clk_div_2;
        end
    end

    button_debounce B1 (.clk(clk), .btn_in(btn_start_stop), .btn_out(btn_ss_clean));
    button_debounce B2 (.clk(clk), .btn_in(btn_reset), .btn_out(btn_re_clean));
    
    stopwatch_counter U3 (.clk_div(clk_div), .reset_p(reset_p),
                        .btn_start_stop(btn_ss_clean), .btn_reset(btn_re_clean),
                        .ssub_secs(ssub_secs), .sub_secs(sub_secs),
                        .sec_ones(sec_ones), .sec_tens(sec_tens),
                        .min_ones(min_ones), .min_tens(min_tens),
                        .hour_ones(hour_ones), .hour_tens(hour_tens),
                        .ampm(ampm));

    always @(ampm) begin
        if (ampm == 4'b0000) begin
            ampm_r = 4'b1010;
        end
        else if (ampm == 4'b1111) begin
            ampm_r = 4'b1011;
        end
    end

    always @(posedge clk_div or posedge reset_p) begin
        if (reset_p) begin
            led <= 16'b0000_0000_0000_0000;
        end
        else begin
            led <= 16'b0000_0000_0000_0000;
            sec_r <= sec_tens + 10;
            led[sec_ones] <= 1'b1;
            led[sec_r] <= 1'b1;
        end
    end

    display_scan_controller U4 (.clk_div_s(clk_div_s),
                        .s_1st(sec_ones), .s_2nd(sec_tens),
                        .s_3rd(min_ones), .s_4th(min_tens),
                        .scan_count(scan_count_1), .select_digit(select_digit_1));
    seg_decoder_a U5 (.scan_count(scan_count_1), .digit_in(select_digit_1), .seg_out(seg), .dp_out(dp));
    anode_selector U6 (.scan_count(scan_count_1), .an_out(an));

    display_scan_controller U7 (.clk_div_s(clk_div_s),
                        .s_1st(hour_ones), .s_2nd(hour_tens),
                        .s_3rd(4'b1100), .s_4th(ampm_r),
                        .scan_count(scan_count_2), .select_digit(select_digit_2));
    seg_decoder_c U8 (.scan_count(scan_count_2), .digit_in(select_digit_2), .seg_out(JB[6:0]), .dp_out(JB[7]));
    anode_selector U9 (.scan_count(scan_count_2), .an_out(JC));
endmodule