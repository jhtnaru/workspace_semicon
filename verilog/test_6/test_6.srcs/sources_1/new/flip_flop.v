`timescale 1ns / 1ns

// D Flip-Flop
module D_flip_flop_basic (
    input clk,
    input d,
    output reg q
    );

    always @(posedge clk) begin     // Rising Edge 일때
        q <= d;     // q에 d 저장
    end
endmodule

// Negative edge D Flip-Flop
module D_flip_flop_neg (
    input clk,
    input d,
    input enable,       // 1일때만 Data Input
    input reset_p,      // 비동기 Reset Signal, Rising Edge 작동
    output reg q
    );

    always @(negedge clk or posedge reset_p) begin
        if (reset_p) begin      // 비동기 Signal reset_p == 1 → q = 0
            q <= 0;
        end
        else if (enable) begin  // enable == 1 → q = d
            q <= d;             // enable == 0 → q 이전값 유지
        end
    end
endmodule

// Positive edge D Flip-Flop
module D_flip_flop_pos (
    input clk,
    input d,
    input enable,       // 1일때만 Data Input
    input reset_p,      // 비동기 Reset Signal, Rising Edge 작동
    output reg q
    );

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin      // 비동기 Signal reset_p == 1 → q = 0
            q <= 0;
        end
        else if (enable) begin  // enable == 1 → q = d
            q <= d;             // enable == 0 → q 이전값 유지
        end
    end
endmodule

// Negative edge T Flip-Flop
module T_flip_flop_neg (
    input clk,
    input reset_p,
    input t,
    output reg q
    );

    always @(negedge clk or posedge reset_p) begin
        if (reset_p) begin
            q <= 1'b0;      // Non-Blocking 할당, q = 0 Blocking 할당
        end
        else begin
            if (t == 1'b1) begin
                q <= ~q;
            end
            else begin
                q <= q;
            end
        end
    end
endmodule

// Positive edge T Flip-Flop
module T_flip_flop_pos (
    input clk,
    input reset_p,
    input t,
    output reg q
    );

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            q <= 1'b0;      // Non-Blocking 할당
        end
        else begin
            if (t == 1'b1) begin
                q <= ~q;
            end
            else begin
                q <= q;
            end
        end
    end
endmodule

// Delay 적용 Negative edge T Flip-Flop
module T_flip_flop_neg_test (
    input clk,
    input reset_p,
    input t,
    output reg q
    );

    reg [26:0] counter = 1;
    reg clk_s = 0;

    always @(negedge clk or posedge reset_p) begin
        if (reset_p) begin
            counter <= 1;
            clk_s <= 0;
        end
        else begin
            if (counter >= 100) begin
                counter <= 1;
                clk_s = ~clk_s;
            end
            else begin
                counter <= counter + 1;
            end
        end
    end

    always @(negedge clk_s or posedge reset_p) begin
        if (reset_p) begin
            q <= 1'b0;      // Non-Blocking 할당, q = 0 Blocking 할당
        end
        else if (t) begin
            q <= ~q;
        end
    end
endmodule

// 비동기 Up-Counter, T Flip-Flop 4개 연결
// counter 가장 오른쪽 bit를 다음 자리 clock으로 이용
module up_counter_asyc (
    input clk,
    input reset_p,
    output [3:0] count
    );

    // 항상 Toggle t = 1
    T_flip_flop_neg T0 (.clk(clk),      .reset_p(reset_p), .t(1'b1), .q(count[0]));
    T_flip_flop_neg T1 (.clk(count[0]), .reset_p(reset_p), .t(1'b1), .q(count[1]));
    T_flip_flop_neg T2 (.clk(count[1]), .reset_p(reset_p), .t(1'b1), .q(count[2]));
    T_flip_flop_neg T3 (.clk(count[2]), .reset_p(reset_p), .t(1'b1), .q(count[3]));
endmodule

// 비동기 Down-Counter
module down_counter_asyc (
    input clk,
    input reset_p,
    output [3:0] count
    );

    T_flip_flop_pos T0 (.clk(clk),      .reset_p(reset_p), .t(1'b1), .q(count[0]));
    T_flip_flop_pos T1 (.clk(count[0]), .reset_p(reset_p), .t(1'b1), .q(count[1]));
    T_flip_flop_pos T2 (.clk(count[1]), .reset_p(reset_p), .t(1'b1), .q(count[2]));
    T_flip_flop_pos T3 (.clk(count[2]), .reset_p(reset_p), .t(1'b1), .q(count[3]));
endmodule

// Positive edge Up Counter
module up_counter_pos (
    input clk,
    input reset_p,
    input enable,
    output reg [3:0] count
    );

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            count <= 0;
        end
        else if (enable) begin
            count <= count + 1;     // enable = 1 일때만 count 증가
        end
    end
endmodule

// Positive edge Down Counter
module down_counter_pos (
    input clk,
    input reset_p,
    input enable,
    output reg [3:0] count
    );

    always @(posedge clk or posedge reset_p) begin
        if (reset_p) begin
            count <= 0;
        end
        else if (enable) begin
            count <= count - 1;     // enable = 1 일때만 count 증가
        end
    end
endmodule

// Delay 적용 Positive edge Up Counter
module up_counter_test (
    input clk,
    input sw_0,         // Reset
    input sw_1,         // Enable
    output [3:0] led
    );

    reg [26:0] psc = 1;
    reg clk_s = 0;

    always @(posedge clk or posedge sw_0) begin
        if (sw_0) begin
            psc <= 1;
            clk_s <= 0;
        end
        else begin
            if (psc >= 50_000_000) begin
                psc <= 1;
                clk_s = ~clk_s;
            end
            else begin
                psc <= psc + 1;
            end
        end
    end

    up_counter_pos U1 (.clk(clk_s), .reset_p(sw_0), .enable(sw_1), .count(led));
endmodule

// Negative edge Edge Detector
module edge_detector_neg (
    input clk, reset_p, cp,     // Clock, Reset, Input Signal 감지
    output p_edge, n_edge       // Rising, Falling 감지 출력
    );

    reg ff_cur, ff_old;         // cp 현재값과 이전값 저장할 Flip-Flop

    always @(negedge clk or posedge reset_p) begin
        if (reset_p) begin          // Reset Flip-Flop 초기화
            ff_cur <= 0;
            ff_old <= 0;
        end
        else begin                  // 이전값 저장하고 현재값 갱신
            ff_old <= ff_cur;
            ff_cur <= cp;
        end
    end

    // Rising 감지, 이전 0, 현재 1 이면 p_edge = 1
    // assign p_edge = ({ff_cur, ff_old} == 2'b10) ? 1 : 0;
    // Falling 감지, 이전 1, 현재 0 이면 n_edge = 1
    assign n_edge = ({ff_cur, ff_old} == 2'b01) ? 1 : 0;
endmodule


// Clock 100 Prescaler
module clock_div_100 (
    input clk,          // System Clock 100㎒
    input reset_p,
    output clk_div      // 100분주 → 1㎒
    );

    reg [6:0] cnt_sysclk = 1;
    reg pulse = 0;

    always @(negedge clk or posedge reset_p) begin
        if (reset_p) begin
            cnt_sysclk <= 1;
            pulse <= 0;
        end
        else begin
            if (cnt_sysclk >= 50) begin
                cnt_sysclk <= 1;
                pulse <= ~pulse;
            end
            else begin
                cnt_sysclk <= cnt_sysclk + 1;
            end
        end
    end

    assign clk_div = pulse;
endmodule

// Clock 1000 Prescaler
module clock_div_1000 (
    input clk,          // System Clock 100㎒
    input reset_p,
    output clk_div      // 100분주 → 1㎒
    );

    reg [9:0] cnt_sysclk = 1;
    reg pulse = 0;

    always @(negedge clk or posedge reset_p) begin
        if (reset_p) begin
            cnt_sysclk <= 1;
            pulse <= 0;
        end
        else begin
            if (cnt_sysclk >= 500) begin
                cnt_sysclk <= 1;
                pulse <= ~pulse;
            end
            else begin
                cnt_sysclk <= cnt_sysclk + 1;
            end
        end
    end

    assign clk_div = pulse;
endmodule

// Clock 100_000_000 Prescaler, 100㎒ → 1㎐
module clock_div_1hz (
    input clk,
    input reset_p,
    output clk_div
    );

    wire clk_1mhz;      // 100㎒ → 1㎒
    wire clk_1khz;      // 1㎒ → 1㎑

    // 1단 분주, 100분주, 100㎒ → 1㎒
    clock_div_100 U1 (.clk(clk), .reset_p(reset_p), .clk_div(clk_1mhz));
    // 2단 분주, 1000분주, 1㎒ → 1㎑
    clock_div_1000 U2 (.clk(clk_1mhz), .reset_p(reset_p), .clk_div(clk_1khz));
    // 3단 분주, 1000분주, 1㎑ → 1㎐
    clock_div_1000 U3 (.clk(clk_1khz), .reset_p(reset_p), .clk_div(clk_div));
endmodule

// 1㎐ LED On, Off
module led_test_1 (
    input clk, btnU,
    output reg led
    );

    wire clk_1hz;

    clock_div_1hz DIV (.clk(clk), .reset_p(btnU), .clk_div(clk_1hz));

    always @(posedge clk_1hz or posedge btnU) begin
        if (btnU) begin
            led <= 0;
        end
        else begin
            led <= ~led;
        end
    end
endmodule